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

/// A SimpleITK example demonstrating image registration using the exhaustive optimizer.

#include <SimpleITK.h>
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <cmath>

#ifndef M_PI
#  define M_PI 3.14159265358979323846
#endif

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

    if (m_Method.GetOptimizerIteration() == 0)
    {
      std::cout << "Scales: " << m_Method.GetOptimizerScales() << std::endl;
    }
    // stash the stream state
    std::ios state(NULL);
    state.copyfmt(std::cout);
    std::cout << std::fixed << std::setfill(' ') << std::setprecision(5);
    std::cout << std::setw(3) << m_Method.GetOptimizerIteration();
    std::cout << " = " << std::setw(7) << m_Method.GetMetricValue();
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
    std::cout << "Usage: " << argv[0] << " <fixedImageFile> <movingImageFile> <outputTransformFile>" << std::endl;
    return 1;
  }

  sitk::Image fixedImage = sitk::ReadImage(argv[1], sitk::sitkFloat32);
  sitk::Image movingImage = sitk::ReadImage(argv[2], sitk::sitkFloat32);

  sitk::ImageRegistrationMethod R;

  R.SetMetricAsMattesMutualInformation(50); // numberOfHistogramBins

  int             samplePerAxis = 12;
  sitk::Transform tx;

  if (fixedImage.GetDimension() == 2)
  {
    tx = sitk::Euler2DTransform();
    // Set the number of samples (radius) in each dimension, with a default step size of 1.0
    std::vector<unsigned int> exhaustiveSteps = { static_cast<unsigned int>(samplePerAxis / 2), 0, 0 };
    R.SetOptimizerAsExhaustive(exhaustiveSteps);
    // Utilize the scale to set the step size for each dimension
    std::vector<double> scales = { 2.0 * M_PI / samplePerAxis, 1.0, 1.0 };
    R.SetOptimizerScales(scales);
  }
  else if (fixedImage.GetDimension() == 3)
  {
    tx = sitk::Euler3DTransform();
    std::vector<unsigned int> exhaustiveSteps = { static_cast<unsigned int>(samplePerAxis / 2),
                                                  static_cast<unsigned int>(samplePerAxis / 2),
                                                  static_cast<unsigned int>(samplePerAxis / 4),
                                                  0,
                                                  0,
                                                  0 };
    R.SetOptimizerAsExhaustive(exhaustiveSteps);
    std::vector<double> scales = {
      2.0 * M_PI / samplePerAxis, 2.0 * M_PI / samplePerAxis, 2.0 * M_PI / samplePerAxis, 1.0, 1.0, 1.0
    };
    R.SetOptimizerScales(scales);
  }

  // Initialize the transform with a translation and the center of rotation from the moments of intensity.
  tx = sitk::CenteredTransformInitializer(fixedImage, movingImage, tx);

  R.SetInitialTransform(tx);
  R.SetInterpolator(sitk::sitkLinear);

  IterationUpdate cmd(R);
  R.AddCommand(sitk::sitkIterationEvent, cmd);

  sitk::Transform outTx = R.Execute(fixedImage, movingImage);

  std::cout << "-------" << std::endl;
  std::cout << outTx.ToString() << std::endl;
  std::cout << "Optimizer stop condition: " << R.GetOptimizerStopConditionDescription() << std::endl;
  std::cout << " Iteration: " << R.GetOptimizerIteration() << std::endl;
  std::cout << " Metric value: " << R.GetMetricValue() << std::endl;

  sitk::WriteTransform(outTx, argv[3]);

  if (getenv("SITK_NOSHOW") == nullptr)
  {
    sitk::ResampleImageFilter resampler;
    resampler.SetReferenceImage(fixedImage);
    resampler.SetInterpolator(sitk::sitkLinear);
    resampler.SetDefaultPixelValue(1);
    resampler.SetTransform(outTx);

    sitk::Image out = resampler.Execute(movingImage);

    sitk::Image simg1 = sitk::Cast(sitk::RescaleIntensity(fixedImage), sitk::sitkUInt8);
    sitk::Image simg2 = sitk::Cast(sitk::RescaleIntensity(out), sitk::sitkUInt8);
    sitk::Image cimg = sitk::Compose(simg1, simg2, sitk::Divide(sitk::Add(simg1, simg2), 2));
    sitk::Show(cimg, "ImageRegistrationExhaustive Composition");
  }

  return 0;
}
