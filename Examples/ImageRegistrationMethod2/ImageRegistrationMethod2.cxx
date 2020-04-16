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
#include <numeric>

namespace sitk = itk::simple;



class IterationUpdate
  : public sitk::Command
{
public:
  IterationUpdate( const sitk::ImageRegistrationMethod &m)
    : m_Method(m)
    {}

  void Execute( ) override
    {
      // use sitk's output operator for std::vector etc..
      using sitk::operator<<;

      // stash the stream state
      std::ios  state(NULL);
      state.copyfmt(std::cout);
      std::cout << std::fixed << std::setfill(' ') << std::setprecision( 5 );
      std::cout << std::setw(3) << m_Method.GetOptimizerIteration();
      std::cout << " = " << std::setw(7) << m_Method.GetMetricValue();
      std::cout << " : " << m_Method.GetOptimizerPosition() << std::endl;

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
  fixed = sitk::Normalize( fixed );
  fixed = sitk::DiscreteGaussian( fixed, 2.0 );

  sitk::Image moving = sitk::ReadImage( argv[2], sitk::sitkFloat32 );
  moving = sitk::Normalize( moving );
  moving = sitk::DiscreteGaussian( moving, 2.0);


  sitk::ImageRegistrationMethod R;
  R.SetMetricAsJointHistogramMutualInformation( );

  const double learningRate = 1;
  const unsigned int numberOfIterations = 200;
  const double convergenceMinimumValue = 1e-4;
  const unsigned int convergenceWindowSize=5;
  R.SetOptimizerAsGradientDescentLineSearch ( learningRate,
                                              numberOfIterations,
                                              convergenceMinimumValue,
                                              convergenceWindowSize);

  R.SetInitialTransform( sitk::TranslationTransform( fixed.GetDimension() ) );
  R.SetInterpolator( sitk::sitkLinear );

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
