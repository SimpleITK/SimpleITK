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

/// A SimpleITK example demonstrating image registration using optimizer weights.

#include <SimpleITK.h>
#include <iostream>
#include <stdlib.h>
#include <vector>

namespace sitk = itk::simple;

int
main(int argc, char * argv[])
{
  using sitk::operator<<;

  if (argc < 4)
  {
    std::cout << "Usage: " << argv[0] << " <fixedImageFile> <movingImageFile> <outputTransformFile>" << std::endl;
    return 1;
  }

  sitk::Image fixedImage = sitk::ReadImage(argv[1], sitk::sitkFloat32);
  sitk::Image movingImage = sitk::ReadImage(argv[2], sitk::sitkFloat32);

  // initialization
  sitk::Transform transform = sitk::CenteredTransformInitializer(
    fixedImage, movingImage, sitk::Euler3DTransform(), sitk::CenteredTransformInitializerFilter::GEOMETRY);

  // registration
  sitk::ImageRegistrationMethod registrationMethod;
  registrationMethod.SetMetricAsCorrelation();
  registrationMethod.SetMetricSamplingStrategy(registrationMethod.NONE);
  registrationMethod.SetInterpolator(sitk::sitkLinear);
  registrationMethod.SetOptimizerAsGradientDescent(1.0,  // learningRate
                                                   300,  // numberOfIterations
                                                   1e-6, // convergenceMinimumValue
                                                   10);  // convergenceWindowSize
  registrationMethod.SetOptimizerScalesFromPhysicalShift();
  registrationMethod.SetInitialTransform(transform, true); // inPlace=true

  // Set optimizer weights: [0, 0, 1, 1, 1, 1] - disable rotation around x and y axes
  std::vector<double> weights = { 0, 0, 1, 1, 1, 1 };
  registrationMethod.SetOptimizerWeights(weights);

  registrationMethod.Execute(fixedImage, movingImage);

  std::cout << "-------" << std::endl;
  std::cout << "Final transform parameters: " << transform.GetParameters() << std::endl;
  std::cout << "Optimizer stop condition: " << registrationMethod.GetOptimizerStopConditionDescription() << std::endl;
  std::cout << "Iteration: " << registrationMethod.GetOptimizerIteration() << std::endl;
  std::cout << "Metric value: " << registrationMethod.GetMetricValue() << std::endl;

  sitk::WriteTransform(transform, argv[3]);

  return 0;
}
