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


class IterationUpdate : public sitk::Command
{
public:
  IterationUpdate(const sitk::ImageRegistrationMethod & m)
    : m_Method(m)
  {}

  void
  Execute() override
  {
    // use sitk's output operator for std::vector etc..
    using sitk::operator<<;

    // stash the stream state
    std::ios state(NULL);
    state.copyfmt(std::cout);
    std::cout << std::fixed << std::setfill(' ') << std::setprecision(5);
    std::cout << std::setw(3) << m_Method.GetOptimizerIteration();
    std::cout << " = " << std::setw(10) << m_Method.GetMetricValue();
    std::cout << " : " << m_Method.GetOptimizerPosition() << std::endl;

    std::cout.copyfmt(state);
  }

private:
  const sitk::ImageRegistrationMethod & m_Method;
};


int
main(int argc, char * argv[])
{
  if (argc < 4)
  {
    std::cout << "Usage: " << argv[0]
              << " <fixedImageFile> <movingImageFile> <outputTransformFile> [numberOfBins] [samplingPercentage]"
              << std::endl;
    return 1;
  }

  sitk::Image fixed = sitk::ReadImage(argv[1], sitk::sitkFloat32);
  sitk::Image moving = sitk::ReadImage(argv[2], sitk::sitkFloat32);

  unsigned int numberOfBins = 24;
  double       samplingPercentage = 0.10;

  if (argc > 4)
  {
    numberOfBins = atoi(argv[4]);
  }
  if (argc > 5)
  {
    samplingPercentage = atof(argv[5]);
  }

  sitk::ImageRegistrationMethod R;
  R.SetMetricAsMattesMutualInformation(numberOfBins);
  R.SetMetricSamplingPercentage(samplingPercentage);
  R.SetMetricSamplingStrategy(sitk::ImageRegistrationMethod::RANDOM);
  R.SetOptimizerAsRegularStepGradientDescent(1.0, 0.001, 200);
  R.SetInitialTransform(sitk::TranslationTransform(fixed.GetDimension()));
  R.SetInterpolator(sitk::sitkLinear);

  IterationUpdate cmd(R);
  R.AddCommand(sitk::sitkIterationEvent, cmd);

  sitk::Transform outTx = R.Execute(fixed, moving);

  std::cout << "-------" << std::endl;
  std::cout << outTx.ToString() << std::endl;
  std::cout << "Optimizer stop condition: " << R.GetOptimizerStopConditionDescription() << std::endl;
  std::cout << " Iteration: " << R.GetOptimizerIteration() << std::endl;
  std::cout << " Metric value: " << R.GetMetricValue() << std::endl;

  sitk::WriteTransform(outTx, argv[3]);

  sitk::ResampleImageFilter resampler;
  resampler.SetReferenceImage(fixed);
  resampler.SetInterpolator(sitk::sitkLinear);
  resampler.SetDefaultPixelValue(100);
  resampler.SetTransform(outTx);

  sitk::Image out = resampler.Execute(moving);
  sitk::Image simg1 = sitk::Cast(sitk::RescaleIntensity(fixed), sitk::sitkUInt8);
  sitk::Image simg2 = sitk::Cast(sitk::RescaleIntensity(out), sitk::sitkUInt8);
  sitk::Image cimg = sitk::Compose(simg1, simg2, sitk::Divide(sitk::Add(simg1, simg2), 2));

  // Show the composition image if SITK_NOSHOW environment variable is not set
  if (getenv("SITK_NOSHOW") == nullptr)
  {
    sitk::Show(cimg, "ImageRegistration4 Composition");
  }

  return 0;
}
