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
#include <SimpleITKTestHarness.h>
#include <SimpleITK.h>

#include <cmath>
#include <numeric>

namespace sitk = itk::simple;

namespace
{

double
MeanSquaredDifference(const sitk::Image & a, const sitk::Image & b)
{
  sitk::StatisticsImageFilter stats;
  stats.Execute(sitk::Square(sitk::Subtract(a, b)));
  return stats.GetMean();
}

// Mean of each displacement component where the label image is 1.
std::vector<double>
MeanDisplacementInMask(const sitk::Image & field, const sitk::Image & mask)
{
  std::vector<double> mean;
  for (unsigned int d = 0; d < field.GetDimension(); ++d)
  {
    sitk::LabelStatisticsImageFilter stats;
    stats.Execute(sitk::VectorIndexSelectionCast(field, d), mask);
    mean.push_back(stats.GetMean(1));
  }
  return mean;
}

} // namespace


class sitkSyNRegistrationMethodTest : public ::testing::Test
{
protected:
  void
  SetUp() override
  {
    fixed = sitk::ReadImage(dataFinder.GetFile("Input/BrainProtonDensitySliceBorder20.png"), sitk::sitkFloat32);

    // moving(x) = fixed(x + shift), so the expected displacement from the
    // fixed domain to the moving domain is -shift.
    sitk::TranslationTransform shiftTx(2, shift);
    moving = sitk::Resample(fixed, fixed, shiftTx, sitk::sitkLinear, 0.0);

    brainMask = sitk::Cast(sitk::Greater(fixed, 50.0), sitk::sitkUInt8);
  }

  sitk::Image         fixed;
  sitk::Image         moving;
  sitk::Image         brainMask;
  std::vector<double> shift{ 3.0, -2.0 };
};


TEST(Registration, SyNImageRegistrationMethod_Basic)
{
  sitk::SyNImageRegistrationMethod R;

  EXPECT_EQ("SyNImageRegistrationMethod", R.GetName());
  std::cout << R.ToString();

  EXPECT_EQ(sitk::sitkLinear, R.GetInterpolator());
  EXPECT_EQ(std::vector<unsigned int>({ 100, 70, 50, 20 }), R.GetNumberOfIterationsPerLevel());
  EXPECT_EQ(0.2, R.GetLearningRate());
  EXPECT_EQ(1e-6, R.GetConvergenceThreshold());
  EXPECT_EQ(10u, R.GetConvergenceWindowSize());
  EXPECT_EQ(3.0, R.GetGaussianSmoothingVarianceForTheUpdateField());
  EXPECT_EQ(0.0, R.GetGaussianSmoothingVarianceForTheTotalField());
  EXPECT_TRUE(R.GetDownsampleImagesForMetricDerivatives());
  EXPECT_FALSE(R.GetAverageMidPointGradients());
  EXPECT_TRUE(R.GetInitialTransformInPlace());
  EXPECT_EQ(std::vector<double>(1, 1.0), R.GetMetricSamplingPercentagePerLevel());

  R.SetLearningRate(0.1);
  EXPECT_EQ(0.1, R.GetLearningRate());
  R.SetConvergenceThreshold(1e-7);
  EXPECT_EQ(1e-7, R.GetConvergenceThreshold());
  R.SetConvergenceWindowSize(5);
  EXPECT_EQ(5u, R.GetConvergenceWindowSize());
  R.SetGaussianSmoothingVarianceForTheUpdateField(2.0);
  EXPECT_EQ(2.0, R.GetGaussianSmoothingVarianceForTheUpdateField());
  R.SetGaussianSmoothingVarianceForTheTotalField(0.5);
  EXPECT_EQ(0.5, R.GetGaussianSmoothingVarianceForTheTotalField());
  R.DownsampleImagesForMetricDerivativesOff();
  EXPECT_FALSE(R.GetDownsampleImagesForMetricDerivatives());
  R.AverageMidPointGradientsOn();
  EXPECT_TRUE(R.GetAverageMidPointGradients());
  R.SetNumberOfIterationsPerLevel({ 5, 3 });
  EXPECT_EQ(std::vector<unsigned int>({ 5, 3 }), R.GetNumberOfIterationsPerLevel());

  // Values before any execution.
  EXPECT_EQ(0u, R.GetCurrentLevel());
  EXPECT_EQ(0u, R.GetCurrentIteration());
  EXPECT_EQ(0.0, R.GetMetricValue());
  EXPECT_EQ(0u, R.GetMetricNumberOfValidPoints());
  EXPECT_EQ("", R.GetStopConditionDescription());

  // Only displacement field transforms are accepted.
  sitk::AffineTransform affine(2);
  EXPECT_THROW(R.SetInitialTransform(affine), sitk::GenericException);

  sitk::DisplacementFieldTransform dispTx(2);
  EXPECT_NO_THROW(R.SetInitialTransform(dispTx, false));
  EXPECT_FALSE(R.GetInitialTransformInPlace());
}


TEST_F(sitkSyNRegistrationMethodTest, Translation2D)
{
  sitk::SyNImageRegistrationMethod R;
  R.SetNumberOfIterationsPerLevel({ 40, 30, 20, 10 });

  unsigned int iterationCount = 0;
  unsigned int levelCount = 0;
  R.AddCommand(sitk::sitkIterationEvent, [&R, &iterationCount] {
    ++iterationCount;
    EXPECT_GE(R.GetCurrentIteration(), 1u);
    EXPECT_LT(R.GetCurrentLevel(), 4u);
    EXPECT_TRUE(std::isfinite(R.GetMetricValue()));
    EXPECT_GT(R.GetMetricNumberOfValidPoints(), 0u);
  });
  R.AddCommand(sitk::sitkMultiResolutionIterationEvent, [&R, &levelCount] {
    EXPECT_EQ(levelCount, R.GetCurrentLevel());
    EXPECT_EQ(0u, R.GetCurrentIteration());
    ++levelCount;
  });

  sitk::DisplacementFieldTransform tx = R.Execute(fixed, moving);
  std::cout << R.GetStopConditionDescription() << std::endl;

  EXPECT_EQ(4u, levelCount);
  EXPECT_GE(iterationCount, 4u);
  EXPECT_LE(iterationCount, 100u);
  EXPECT_EQ(3u, R.GetCurrentLevel());
  EXPECT_LE(R.GetCurrentIteration(), 10u);
  EXPECT_NE(std::string::npos, R.GetStopConditionDescription().find("level 3"));

  // Forward and inverse fields are on the fixed image grid.
  EXPECT_EQ(fixed.GetSize(), tx.GetDisplacementField().GetSize());
  EXPECT_EQ(fixed.GetSize(), tx.GetInverseDisplacementField().GetSize());

  // The recovered displacement inside the brain approximates -shift.
  std::vector<double> mean = MeanDisplacementInMask(tx.GetDisplacementField(), brainMask);
  EXPECT_NEAR(-shift[0], mean[0], 0.5);
  EXPECT_NEAR(-shift[1], mean[1], 0.5);

  std::vector<double> inverseMean = MeanDisplacementInMask(tx.GetInverseDisplacementField(), brainMask);
  EXPECT_NEAR(shift[0], inverseMean[0], 0.5);
  EXPECT_NEAR(shift[1], inverseMean[1], 0.5);

  // Warping the moving image with the result reproduces the fixed image.
  const double before = MeanSquaredDifference(fixed, moving);
  const double after = MeanSquaredDifference(fixed, sitk::Resample(moving, fixed, tx, sitk::sitkLinear, 0.0));
  std::cout << "MSD before: " << before << " after: " << after << std::endl;
  EXPECT_LT(after, 0.25 * before);

  // Inverse consistency of the two fields at interior points.
  sitk::Transform inverse = tx.GetInverse();
  for (const auto & p : { std::vector<double>{ 100.0, 120.0 }, std::vector<double>{ 80.0, 150.0 } })
  {
    std::vector<double> q = inverse.TransformPoint(tx.TransformPoint(p));
    EXPECT_NEAR(p[0], q[0], 0.1);
    EXPECT_NEAR(p[1], q[1], 0.1);
  }
}


TEST_F(sitkSyNRegistrationMethodTest, InitialTransformInPlace)
{
  sitk::SyNImageRegistrationMethod R;
  R.SetShrinkFactorsPerLevel({ 4, 1 });
  R.SetSmoothingSigmasPerLevel({ 1.0, 0.0 });
  R.SetNumberOfIterationsPerLevel({ 5, 3 });

  // Not in place: the user's transform is left untouched.
  sitk::DisplacementFieldTransform notInPlace(2);
  R.SetInitialTransform(notInPlace, false);
  sitk::DisplacementFieldTransform result = R.Execute(fixed, moving);
  EXPECT_EQ(std::vector<unsigned int>({ 0, 0 }), notInPlace.GetDisplacementField().GetSize());
  EXPECT_EQ(fixed.GetSize(), result.GetDisplacementField().GetSize());
  EXPECT_EQ(fixed.GetSize(), result.GetInverseDisplacementField().GetSize());

  // The fields are defined on the grid of the last level.
  R.SetShrinkFactorsPerLevel({ 4, 2 });
  result = R.Execute(fixed, moving);
  const std::vector<unsigned int> halfSize = sitk::Shrink(fixed, { 2, 2 }).GetSize();
  EXPECT_EQ(halfSize, result.GetDisplacementField().GetSize());
  EXPECT_EQ(halfSize, result.GetInverseDisplacementField().GetSize());
  R.SetShrinkFactorsPerLevel({ 4, 1 });

  // In place: the user's transform is the result.
  sitk::DisplacementFieldTransform inPlace(2);
  R.SetInitialTransform(inPlace, true);
  result = R.Execute(fixed, moving);
  EXPECT_EQ(fixed.GetSize(), inPlace.GetDisplacementField().GetSize());
  EXPECT_EQ(fixed.GetSize(), inPlace.GetInverseDisplacementField().GetSize());
  EXPECT_EQ(inPlace.GetParameters(), result.GetParameters());

  // A transform with an existing field is resumed from that field.
  sitk::Image field(fixed.GetSize(), sitk::sitkVectorFloat64);
  field.CopyInformation(fixed);
  sitk::DisplacementFieldTransform withField(field);
  R.SetInitialTransform(withField, true);
  EXPECT_NO_THROW(R.Execute(fixed, moving));
  EXPECT_EQ(fixed.GetSize(), withField.GetInverseDisplacementField().GetSize());
}


TEST_F(sitkSyNRegistrationMethodTest, InitialFieldSeedsRegistration)
{
  sitk::SyNImageRegistrationMethod R;
  R.SetShrinkFactorsPerLevel({ 1 });
  R.SetSmoothingSigmasPerLevel({ 0.0 });
  R.SetNumberOfIterationsPerLevel({ 0 });

  sitk::Image zero(fixed.GetSize(), sitk::sitkFloat64);
  sitk::Image field = sitk::Compose(sitk::Add(zero, 1.5), sitk::Subtract(zero, 0.5));
  field.CopyInformation(fixed);
  sitk::DisplacementFieldTransform initial(field);
  R.SetInitialTransform(initial, false);

  // Without iterations the result is the supplied deformation.
  sitk::DisplacementFieldTransform result = R.Execute(fixed, moving);
  std::vector<double>              mean = MeanDisplacementInMask(result.GetDisplacementField(), brainMask);
  EXPECT_NEAR(1.5, mean[0], 1e-6);
  EXPECT_NEAR(-0.5, mean[1], 1e-6);
}


TEST_F(sitkSyNRegistrationMethodTest, ReuseCoarseResult)
{
  sitk::SyNImageRegistrationMethod R;
  R.SetShrinkFactorsPerLevel({ 4, 2 });
  R.SetSmoothingSigmasPerLevel({ 1.0, 0.0 });
  R.SetNumberOfIterationsPerLevel({ 5, 3 });

  const std::vector<unsigned int>  halfSize = sitk::Shrink(fixed, { 2, 2 }).GetSize();
  sitk::DisplacementFieldTransform tx = R.Execute(fixed, moving);
  ASSERT_EQ(halfSize, tx.GetDisplacementField().GetSize());

  // Running again from the coarse result keeps the fixed image pyramid.
  R.SetInitialTransform(tx, true);
  sitk::DisplacementFieldTransform again = R.Execute(fixed, moving);
  EXPECT_EQ(halfSize, again.GetDisplacementField().GetSize());
  EXPECT_EQ(halfSize, again.GetInverseDisplacementField().GetSize());
}


TEST_F(sitkSyNRegistrationMethodTest, Metrics)
{
  sitk::SyNImageRegistrationMethod R;
  R.SetShrinkFactorsPerLevel({ 4, 1 });
  R.SetSmoothingSigmasPerLevel({ 1.0, 0.0 });
  R.SetNumberOfIterationsPerLevel({ 3, 3 });
  R.SetMetricFixedMask(brainMask);
  R.SetMetricMovingMask(brainMask);

  using Setter = std::function<void(sitk::SyNImageRegistrationMethod &)>;
  const std::vector<std::pair<std::string, Setter>> metrics = {
    { "ANTSNeighborhoodCorrelation", [](auto & r) { r.SetMetricAsANTSNeighborhoodCorrelation(3); } },
    { "Correlation", [](auto & r) { r.SetMetricAsCorrelation(); } },
    { "Demons", [](auto & r) { r.SetMetricAsDemons(); } },
    { "JointHistogramMutualInformation", [](auto & r) { r.SetMetricAsJointHistogramMutualInformation(); } },
    { "MeanSquares", [](auto & r) { r.SetMetricAsMeanSquares(); } },
    { "MattesMutualInformation", [](auto & r) { r.SetMetricAsMattesMutualInformation(); } },
  };

  for (const auto & [name, setter] : metrics)
  {
    SCOPED_TRACE(name);
    setter(R);
    sitk::DisplacementFieldTransform tx = R.Execute(fixed, moving);
    EXPECT_EQ(fixed.GetSize(), tx.GetDisplacementField().GetSize());
    EXPECT_EQ(fixed.GetSize(), tx.GetInverseDisplacementField().GetSize());
    EXPECT_TRUE(std::isfinite(R.GetMetricValue()));
    EXPECT_EQ(1u, R.GetCurrentLevel());
    EXPECT_EQ(3u, R.GetCurrentIteration());
    EXPECT_GT(R.GetMetricNumberOfValidPoints(), 0u);
    std::cout << name << ": " << R.GetMetricValue() << " " << R.GetStopConditionDescription() << std::endl;
  }
}


TEST_F(sitkSyNRegistrationMethodTest, Exceptions)
{
  sitk::SyNImageRegistrationMethod noLevels;
  noLevels.SetShrinkFactorsPerLevel({});
  noLevels.SetSmoothingSigmasPerLevel({});
  noLevels.SetNumberOfIterationsPerLevel({});
  EXPECT_THROW(noLevels.Execute(fixed, moving), sitk::GenericException);

  sitk::SyNImageRegistrationMethod R;

  R.SetNumberOfIterationsPerLevel({ 5, 3 });
  EXPECT_THROW(R.Execute(fixed, moving), sitk::GenericException);

  R.SetNumberOfIterationsPerLevel({ 5, 3, 2, 1 });
  R.SetSmoothingSigmasPerLevel({ 1.0 });
  EXPECT_THROW(R.Execute(fixed, moving), sitk::GenericException);

  R.SetSmoothingSigmasPerLevel({ 3.0, 2.0, 1.0, 0.0 });
  EXPECT_THROW(R.Execute(fixed, sitk::Cast(moving, sitk::sitkFloat64)), sitk::GenericException);
  EXPECT_THROW(R.Execute(sitk::Cast(fixed, sitk::sitkUInt8), sitk::Cast(moving, sitk::sitkUInt8)),
               sitk::GenericException);
}


TEST(Registration, SyNImageRegistrationMethod_3D)
{
  auto makeBlob = [](const std::vector<double> & center) {
    sitk::GaussianImageSource source;
    source.SetSize({ 32, 32, 32 });
    source.SetMean(center);
    source.SetSigma({ 4.0, 4.0, 4.0 });
    source.SetScale(100.0);
    source.SetOutputPixelType(sitk::sitkFloat32);
    return source.Execute();
  };

  sitk::Image fixed = makeBlob({ 16.0, 16.0, 16.0 });
  sitk::Image moving = makeBlob({ 17.0, 15.0, 16.0 });

  sitk::SyNImageRegistrationMethod R;
  R.SetShrinkFactorsPerLevel({ 2, 1 });
  R.SetSmoothingSigmasPerLevel({ 1.0, 0.0 });
  R.SetNumberOfIterationsPerLevel({ 10, 5 });
  R.SetMetricAsMeanSquares();

  sitk::DisplacementFieldTransform tx = R.Execute(fixed, moving);
  EXPECT_EQ(fixed.GetSize(), tx.GetDisplacementField().GetSize());
  EXPECT_EQ(fixed.GetSize(), tx.GetInverseDisplacementField().GetSize());

  const double before = MeanSquaredDifference(fixed, moving);
  const double after = MeanSquaredDifference(fixed, sitk::Resample(moving, fixed, tx, sitk::sitkLinear, 0.0));
  EXPECT_LT(after, before);
}
