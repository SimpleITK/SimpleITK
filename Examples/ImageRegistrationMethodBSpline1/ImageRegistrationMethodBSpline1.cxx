/*=========================================================================
*
*  Copyright Insight Software Consortium
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
  IterationUpdate( const sitk::ImageRegistrationMethod &m)
    : m_Method(m)
    {}

  virtual void Execute( )
    {
      // use sitk's output operator for std::vector etc..
      using sitk::operator<<;

      if (m_Method.GetOptimizerIteration() == 0)
        {
        std::cout << m_Method.ToString() << std::endl;
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

  std::vector<unsigned int> transformDomainMeshSize(fixed.GetDimension(),8);

  sitk::BSplineTransform tx = sitk::BSplineTransformInitializer(fixed, transformDomainMeshSize);

  std::cout << "Initial Parameters:" << tx.GetParameters() << std::endl;


  sitk::ImageRegistrationMethod R;
  R.SetMetricAsCorrelation();

  const double gradientConvergenceTolerance = 1e-5;
  const unsigned int maximumNumberOfIterations = 100;
  const unsigned int maximumNumberOfCorrections = 5;
  const unsigned int maximumNumberOfFunctionEvaluations = 1000;
  const double costFunctionConvergenceFactor = 1e+7;
  R.SetOptimizerAsLBFGSB(gradientConvergenceTolerance,
                         maximumNumberOfIterations,
                         maximumNumberOfCorrections,
                         maximumNumberOfFunctionEvaluations,
                         costFunctionConvergenceFactor);
  R.SetInitialTransform(tx, true);
  R.SetInterpolator(sitk::sitkLinear);

  IterationUpdate cmd(R);
  R.AddCommand( sitk::sitkIterationEvent, cmd);

  sitk::Transform outTx = R.Execute( fixed, moving );

  std::cout << "-------" << std::endl;
  std::cout << outTx.ToString() << std::endl;
  std::cout << "Optimizer stop condition: " << R.GetOptimizerStopConditionDescription() << std::endl;
  std::cout << " Iteration: " << R.GetOptimizerIteration() << std::endl;
  std::cout << " Metric value: " << R.GetMetricValue() << std::endl;

  sitk::WriteTransform(outTx, argv[3]);

  return 0;
}
