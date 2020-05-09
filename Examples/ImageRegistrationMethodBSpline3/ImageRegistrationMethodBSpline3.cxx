/*=========================================================================
*
*  Copyright NumFOCUS
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*         http://www.apache.org/licenses/LICENSE-2.0.txt
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*=========================================================================*/

// This one header will include all SimpleITK filters and external
// objects.
#include <SimpleITK.h>
#include <iostream>
#include <stdlib.h>
#include <iomanip>

namespace sitk = itk::simple;

// use sitk's output operator for std::vector etc..
using sitk::operator<<;


class IterationUpdate
  : public sitk::Command
{
public:
  IterationUpdate( const sitk::ImageRegistrationMethod &m, const sitk::BSplineTransform &tx)
    : m_Method(m),
      m_BSplineTransform(tx)
    {}

  // Override method from parent which is called at for the requested event
  void Execute( ) override
    {
      if (m_Method.GetOptimizerIteration() == 0)
        {
        // The BSpline is resized before the first optimizer
        // iteration is completed per level. Print the transform object
        // to show the adapted BSpline transform.
        std::cout << m_BSplineTransform.ToString() << std::endl;
        }

      // stash the stream state
      std::ios  state(NULL);
      state.copyfmt(std::cout);
      std::cout << std::fixed << std::setfill(' ') << std::setprecision( 5 );
      std::cout << std::setw(3) << m_Method.GetOptimizerIteration();
      std::cout << " = " << std::setw(10) << m_Method.GetMetricValue() << std::endl;
      std::cout.copyfmt(state);
    }

private:
  const sitk::ImageRegistrationMethod &m_Method;
  const sitk::BSplineTransform &m_BSplineTransform;

};


class MultiResolutionIterationUpdate
  : public sitk::Command
{
public:
  MultiResolutionIterationUpdate( const sitk::ImageRegistrationMethod &m)
    : m_Method(m)
    {}

  // Override method from parent which is called at for the requested event
  void Execute( ) override
    {
      // The sitkMultiResolutionIterationEvent occurs before the
      // resolution of the transform. This event is used here to print
      // the status of the optimizer from the previous registration level.
      if (m_Method.GetCurrentLevel() > 0)
        {
        std::cout << "Optimizer stop condition: " << m_Method.GetOptimizerStopConditionDescription() << std::endl;
        std::cout << " Iteration: " << m_Method.GetOptimizerIteration() << std::endl;
        std::cout << " Metric value: " << m_Method.GetMetricValue() << std::endl;
        }

      std::cout << "--------- Resolution Changing ---------" << std::endl;
    }

private:
  const sitk::ImageRegistrationMethod &m_Method;
};




int main(int argc, char *argv[])
{

  if ( argc < 4 )
    {
    std::cerr << "Usage: " << argv[0] << " <fixedImageFilter> <movingImageFile> <outputTransformFile>" << std::endl;
    return 1;
    }

  sitk::Image fixed = sitk::ReadImage( argv[1], sitk::sitkFloat32 );

  sitk::Image moving = sitk::ReadImage( argv[2], sitk::sitkFloat32 );

  std::vector<unsigned int> transformDomainMeshSize(fixed.GetDimension(), 2);

  sitk::BSplineTransform tx = sitk::BSplineTransformInitializer(fixed, transformDomainMeshSize);

  std::cout << "Initial Number of Parameters:" << tx.GetNumberOfParameters() << std::endl;


  sitk::ImageRegistrationMethod R;
  R.SetMetricAsJointHistogramMutualInformation();


  const double learningRate = 5.0;
  const unsigned int numberOfIterations = 100u;
  const double convergenceMinimumValue = 1e-4;
  const unsigned int convergenceWindowSize = 5;
  R.SetOptimizerAsGradientDescentLineSearch( learningRate,
                                             numberOfIterations,
                                             convergenceMinimumValue,
                                             convergenceWindowSize);

  R.SetInterpolator(sitk::sitkLinear);

  std::vector<unsigned int> scaleFactors = { 1, 2, 5 };
  const bool inPlace = true;
  R.SetInitialTransformAsBSpline(tx,
                                 inPlace,
                                 scaleFactors);

  std::vector<unsigned int> shrinkFactors = { 4, 2, 1 };
  R.SetShrinkFactorsPerLevel( shrinkFactors );

  std::vector<double> smoothingSigmas = { 4.0, 2.0, 1.0 };
  R.SetSmoothingSigmasPerLevel( smoothingSigmas );

  IterationUpdate cmd1(R, tx);
  R.AddCommand( sitk::sitkIterationEvent, cmd1);

  MultiResolutionIterationUpdate cmd2(R);
  R.AddCommand( sitk::sitkMultiResolutionIterationEvent, cmd2);

  sitk::Transform outTx = R.Execute( fixed, moving );

  std::cout << "-------" << std::endl;
  std::cout << outTx.ToString() << std::endl;
  std::cout << "Optimizer stop condition: " << R.GetOptimizerStopConditionDescription() << std::endl;
  std::cout << " Iteration: " << R.GetOptimizerIteration() << std::endl;
  std::cout << " Metric value: " << R.GetMetricValue() << std::endl;

  sitk::WriteTransform(outTx, argv[3]);

  return 0;
}
