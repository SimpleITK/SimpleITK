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

      // stash the stream state
      std::ios  state(NULL);
      state.copyfmt(std::cout);
      std::cout << std::fixed << std::setfill(' ') << std::setprecision( 5 );
      if ( m_Method.GetOptimizerIteration() == 0 )
        {
        std::cout << "\tLevel: " << std::setw(3) << m_Method.GetCurrentLevel() << std::endl;
        std::cout << "\tScales: " << m_Method.GetOptimizerScales() << std::endl;
        }
      std::cout << '#' << m_Method.GetOptimizerIteration() << std::endl;
      std::cout << "\tMetric Value: " <<  m_Method.GetMetricValue() << std::endl;
      std::cout << "\tLearning Rate: " << m_Method.GetOptimizerLearningRate() << std::endl;
      if (m_Method.GetOptimizerConvergenceValue() != std::numeric_limits<double>::max())
        {
        std::cout << "\tConvergence Value: " << std::scientific << m_Method.GetOptimizerConvergenceValue() << std::endl;
        }
      std::cout.copyfmt(state);
    }

private:
  const sitk::ImageRegistrationMethod &m_Method;

};

class MultiResolutionIterationUpdate
  : public sitk::Command
{
public:
  MultiResolutionIterationUpdate( const sitk::ImageRegistrationMethod &m)
    : m_Method(m)
    {}

  virtual void Execute( )
    {
      // use sitk's output operator for std::vector etc..
      using sitk::operator<<;

      // stash the stream state
      std::ios  state(NULL);
      state.copyfmt(std::cout);
      std::cout << std::fixed << std::setfill(' ') << std::setprecision( 5 );
      std::cout << "\tStop Condition: " << m_Method.GetOptimizerStopConditionDescription() << std::endl;
      std::cout << "============= Resolution Change =============" << std::endl;
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

  sitk::Transform initialTx = sitk::CenteredTransformInitializer(fixed, moving, sitk::AffineTransform(fixed.GetDimension()));

  sitk::ImageRegistrationMethod R;

  {
  std::vector<unsigned int> shrinkFactors;
  shrinkFactors.push_back(3);
  shrinkFactors.push_back(2);
  shrinkFactors.push_back(1);

  std::vector<double> smoothingSigmas;
  smoothingSigmas.push_back(2.0);
  smoothingSigmas.push_back(1.0);
  smoothingSigmas.push_back(1.0);

  R.SetShrinkFactorsPerLevel(shrinkFactors);
  R.SetSmoothingSigmasPerLevel(smoothingSigmas);
  }

  R.SetMetricAsJointHistogramMutualInformation(20);
  R.MetricUseFixedImageGradientFilterOff();
  R.MetricUseFixedImageGradientFilterOff();

  {
  double learningRate=1.0;
  unsigned int numberOfIterations=100;
  double convergenceMinimumValue = 1e-6;
  unsigned int convergenceWindowSize = 10;
  sitk::ImageRegistrationMethod::EstimateLearningRateType estimateLearningRate = R.EachIteration;
  R.SetOptimizerAsGradientDescent( learningRate,
                                   numberOfIterations,
                                   convergenceMinimumValue,
                                   convergenceWindowSize,
                                   estimateLearningRate
    );
  }
  R.SetOptimizerScalesFromPhysicalShift();

  R.SetInitialTransform(initialTx, true);

  R.SetInterpolator(sitk::sitkLinear);

  IterationUpdate cmd(R);
  R.AddCommand( sitk::sitkIterationEvent, cmd);

  MultiResolutionIterationUpdate cmd2(R);
  R.AddCommand( sitk::sitkMultiResolutionIterationEvent, cmd2);

  sitk::Transform outTx = R.Execute( fixed, moving );

  std::cout << "-------" << std::endl;
  std::cout << outTx.ToString() << std::endl;
  std::cout << "Optimizer stop condition: " << R.GetOptimizerStopConditionDescription() << std::endl;
  std::cout << " Iteration: " << R.GetOptimizerIteration() << std::endl;
  std::cout << " Metric value: " << R.GetMetricValue() << std::endl;


  sitk::Image displacementField = sitk::Image(fixed.GetSize(), sitk::sitkVectorFloat64);
  displacementField.CopyInformation(fixed);
  sitk::DisplacementFieldTransform displacementTx(displacementField);
  const double varianceForUpdateField=0.0;
  const double varianceForTotalField=1.5;
  displacementTx.SetSmoothingGaussianOnUpdate(varianceForUpdateField,
                                              varianceForTotalField);



  R.SetMovingInitialTransform(outTx);
  R.SetInitialTransform(displacementTx, true);

  R.SetMetricAsANTSNeighborhoodCorrelation(4);
  R.MetricUseFixedImageGradientFilterOff();
  R.MetricUseFixedImageGradientFilterOff();

  {
  std::vector<unsigned int> shrinkFactors;
  shrinkFactors.push_back(3);
  shrinkFactors.push_back(2);
  shrinkFactors.push_back(1);

  std::vector<double> smoothingSigmas;
  smoothingSigmas.push_back(2.0);
  smoothingSigmas.push_back(1.0);
  smoothingSigmas.push_back(1.0);

  R.SetShrinkFactorsPerLevel(shrinkFactors);
  R.SetSmoothingSigmasPerLevel(smoothingSigmas);
  }

  R.SetOptimizerScalesFromPhysicalShift();

  {
  double learningRate=1.0;
  unsigned int numberOfIterations=300;
  double convergenceMinimumValue = 1e-6;
  unsigned int convergenceWindowSize = 10;
  sitk::ImageRegistrationMethod::EstimateLearningRateType estimateLearningRate = R.EachIteration;
  R.SetOptimizerAsGradientDescent( learningRate,
                                   numberOfIterations,
                                   convergenceMinimumValue,
                                   convergenceWindowSize,
                                   estimateLearningRate
    );
  }
  outTx.AddTransform( R.Execute(fixed, moving) );

  std::cout << "-------" << std::endl;
  std::cout << outTx.ToString() << std::endl;
  std::cout << "Optimizer stop condition: " << R.GetOptimizerStopConditionDescription() << std::endl;
  std::cout << " Iteration: " << R.GetOptimizerIteration() << std::endl;
  std::cout << " Metric value: " << R.GetMetricValue() << std::endl;


  sitk::WriteTransform(outTx, argv[3]);

  return 0;
}
