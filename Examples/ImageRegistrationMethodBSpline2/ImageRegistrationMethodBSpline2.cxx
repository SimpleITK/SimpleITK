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

// A SimpleITK example demonstrating image registration using the
// BSplineTransform and the MattesMutualInformation metric.

#include <SimpleITK.h>
#include <iostream>
#include <stdlib.h>
#include <iomanip>

namespace sitk = itk::simple;

class IterationUpdate
{
public:
  IterationUpdate(const sitk::ImageRegistrationMethod & m)
    : m_Method(m)
  {}

  void
  Execute()
  {
    std::cout << std::setw(3) << m_Method.GetOptimizerIteration();
    std::cout << " = " << std::setw(10) << std::setprecision(5) << m_Method.GetMetricValue() << std::endl;
    std::cout << "\t#: " << m_Method.GetOptimizerPosition().size() << std::endl;
  }

private:
  const sitk::ImageRegistrationMethod & m_Method;
};

int
main(int argc, char * argv[])
{

  if (argc < 4)
  {
    std::cerr << "Usage: " << argv[0] << " <fixedImageFile> <movingImageFile> <outputTransformFile>" << std::endl;
    return 1;
  }

  sitk::Image fixed = sitk::ReadImage(argv[1], sitk::sitkFloat32);
  sitk::Image moving = sitk::ReadImage(argv[2], sitk::sitkFloat32);

  std::vector<unsigned int> transformDomainMeshSize(moving.GetDimension(), 10);
  sitk::Transform           tx = sitk::BSplineTransformInitializer(fixed, transformDomainMeshSize);

  std::cout << "Initial Parameters:" << std::endl;
  std::vector<double> initialParams = tx.GetParameters();
  std::cout << "[";
  std::cout << std::setprecision(5) << std::fixed << initialParams[0];
  for (size_t i = 1; i < initialParams.size(); i++)
  {
    std::cout << ", " << std::setprecision(5) << std::fixed << initialParams[i];
  }
  std::cout << "]" << std::endl;

  sitk::ImageRegistrationMethod R;
  R.SetMetricAsMattesMutualInformation(50);

  double       learningRate = 5.0;
  unsigned int numberOfIterations = 100;
  double       convergenceMinimumValue = 1e-4;
  unsigned int convergenceWindowSize = 5;
  R.SetOptimizerAsGradientDescentLineSearch(
    learningRate, numberOfIterations, convergenceMinimumValue, convergenceWindowSize);
  R.SetOptimizerScalesFromPhysicalShift();
  R.SetInitialTransform(tx);
  R.SetInterpolator(sitk::sitkLinear);

  R.SetShrinkFactorsPerLevel(std::vector<unsigned int>{ 6, 2, 1 });
  R.SetSmoothingSigmasPerLevel(std::vector<double>{ 6.0, 2.0, 1.0 });

  IterationUpdate cmd1(R);
  R.AddCommand(sitk::sitkIterationEvent, [&cmd1]() { cmd1.Execute(); });

  R.AddCommand(sitk::sitkMultiResolutionIterationEvent,
               []() { std::cout << "--------- Resolution Changing ---------" << std::endl; });

  sitk::Transform outTx = R.Execute(fixed, moving);

  std::cout << "-------" << std::endl;
  std::cout << outTx.ToString() << std::endl;
  std::cout << "Optimizer stop condition: " << R.GetOptimizerStopConditionDescription() << std::endl;
  std::cout << " Iteration: " << R.GetOptimizerIteration() << std::endl;
  std::cout << " Metric value: " << R.GetMetricValue() << std::endl;

  sitk::WriteTransform(outTx, argv[3]);

  if (getenv("SITK_NOSHOW") == NULL)
  {
    sitk::ResampleImageFilter resampler;
    resampler.SetReferenceImage(fixed);
    resampler.SetInterpolator(sitk::sitkLinear);
    resampler.SetDefaultPixelValue(100);
    resampler.SetTransform(outTx);

    sitk::Image out = resampler.Execute(moving);
    sitk::Image simg1 = sitk::Cast(sitk::RescaleIntensity(fixed), sitk::sitkUInt8);
    sitk::Image simg2 = sitk::Cast(sitk::RescaleIntensity(out), sitk::sitkUInt8);
    sitk::Image cimg = sitk::Compose(simg1, simg2, sitk::Divide(sitk::Add(simg1, simg2), 2.0));
    sitk::Show(cimg, "ImageRegistrationMethodBSpline2 Composition");
  }

  return 0;
}
