#include "SimpleITKTestHarness.h"
#include "sitkImageFileReader.h"
#include "sitkCastImageFilter.h"
#include "sitkElastixImageFilter.h"
#include "sitkTransformixImageFilter.h"

namespace itk
{
namespace simple
{

bool
stfxIsEmpty(const Image image)
{
  return (image.GetWidth() == 0 && image.GetHeight() == 0);
}


TEST(TransformixImageFilter, ObjectOrientedInterface)
{
  Image fixedImage = Cast(ReadImage(dataFinder.GetFile("Input/BrainProtonDensitySliceBorder20.png")), sitkFloat32);
  Image movingImage =
    Cast(ReadImage(dataFinder.GetFile("Input/BrainProtonDensitySliceShifted13x17y.png")), sitkFloat32);

  ElastixImageFilter silx;
  silx.SetFixedImage(fixedImage);
  silx.SetMovingImage(movingImage);
  silx.Execute();

  TransformixImageFilter stfx;
  EXPECT_EQ(stfx.GetName(), "TransformixImageFilter");
  EXPECT_EQ(stfx.GetTransformParameterMaps().size(), 0u);

  ASSERT_THROW(stfx.Execute(), GenericException);
  EXPECT_NO_THROW(stfx.SetMovingImage(movingImage));
  ASSERT_THROW(stfx.Execute(), GenericException);

  EXPECT_NO_THROW(stfx.SetTransformParameterMaps(silx.GetTransformParameterMaps()));
  EXPECT_NO_THROW(stfx.Execute());
  EXPECT_FALSE(stfxIsEmpty(stfx.GetResultImage()));

  EXPECT_NO_THROW(stfx.Execute());
  EXPECT_FALSE(stfxIsEmpty(stfx.GetResultImage()));

  EXPECT_NO_THROW(stfx.Execute());
  EXPECT_FALSE(stfxIsEmpty(stfx.GetResultImage()));
}


TEST(TransformixImageFilter, ProceduralInterface)
{
  Image fixedImage = Cast(ReadImage(dataFinder.GetFile("Input/BrainProtonDensitySliceBorder20.png")), sitkFloat32);
  Image movingImage =
    Cast(ReadImage(dataFinder.GetFile("Input/BrainProtonDensitySliceShifted13x17y.png")), sitkFloat32);
  Image resultImage;

  ElastixImageFilter silx;
  silx.SetFixedImage(fixedImage);
  silx.SetMovingImage(movingImage);
  silx.SetParameter("MaximumNumberOfIterations", "8.0");
  silx.Execute();

  std::string outputDirectory = ".";

  EXPECT_NO_THROW(resultImage = Transformix(movingImage, silx.GetTransformParameterMaps()[0]));
  EXPECT_FALSE(stfxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Transformix(movingImage, silx.GetTransformParameterMaps()[0], true));
  EXPECT_FALSE(stfxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Transformix(movingImage, silx.GetTransformParameterMaps()[0], true, outputDirectory));
  EXPECT_FALSE(stfxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Transformix(movingImage, silx.GetTransformParameterMaps()[0], false, outputDirectory));
  EXPECT_FALSE(stfxIsEmpty(resultImage));

  EXPECT_NO_THROW(resultImage = Transformix(movingImage, silx.GetTransformParameterMaps()));
  EXPECT_FALSE(stfxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Transformix(movingImage, silx.GetTransformParameterMaps(), true));
  EXPECT_FALSE(stfxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Transformix(movingImage, silx.GetTransformParameterMaps(), true, outputDirectory));
  EXPECT_FALSE(stfxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Transformix(movingImage, silx.GetTransformParameterMaps(), false, outputDirectory));
  EXPECT_FALSE(stfxIsEmpty(resultImage));

  ElastixImageFilter::ParameterMapVectorType parameterMapVector = silx.GetTransformParameterMaps();
  parameterMapVector[parameterMapVector.size() - 1]["WriteResultImage"] =
    ElastixImageFilter::ParameterValueVectorType(1, "false");
  EXPECT_NO_THROW(resultImage = Transformix(movingImage, silx.GetTransformParameterMaps()));
  EXPECT_FALSE(stfxIsEmpty(resultImage));
}

TEST(TransformixImageFilter, ComputeDeformationField)
{
  Image fixedImage = Cast(ReadImage(dataFinder.GetFile("Input/BrainProtonDensitySliceBorder20.png")), sitkFloat32);
  Image movingImage =
    Cast(ReadImage(dataFinder.GetFile("Input/BrainProtonDensitySliceShifted13x17y.png")), sitkFloat32);
  Image resultImage;

  ElastixImageFilter silx;
  silx.SetFixedImage(fixedImage);
  silx.SetMovingImage(movingImage);
  silx.SetParameter("MaximumNumberOfIterations", "20");
  silx.Execute();

  TransformixImageFilter stfx;
  stfx.SetTransformParameterMaps(silx.GetTransformParameterMaps());
  stfx.ComputeDeformationFieldOn();

  // Note: SetMovingImage appears necessary for `itk::TransformixFilter` (not for the old
  // `elx::TransformixFilter`, which was being used by SuperElastix/SimpleElastix, by Kasper Marstal),
  // to avoid "ITK ERROR: TransformixFilter(...): Input MovingImage is required but not set."
  stfx.SetMovingImage(movingImage);

  stfx.Execute();

  Image                 deformationField = stfx.GetDeformationField();
  std::vector<uint32_t> index;
  index.push_back(10);
  index.push_back(10);
  auto deformationVector = deformationField.GetPixelAsVectorFloat32(index);

  // Check that deformation field is non-zero
  EXPECT_GT(deformationVector[0], 1.0);
  EXPECT_GT(deformationVector[1], 1.0);
}

#if SITK_MAX_DIMENSION >= 4

TEST(TransformixImageFilter, Transformation4D)
{
  Image fixedImage = ReadImage(dataFinder.GetFile("Input/4D.nii.gz"));
  Image movingImage1 = ReadImage(dataFinder.GetFile("Input/4D.nii.gz"));
  Image movingImage2 = ReadImage(dataFinder.GetFile("Input/4D.nii.gz"));
  Image resultImage1;
  Image resultImage2;

  ElastixImageFilter silx;
  silx.SetParameterMap("groupwise");
  silx.SetParameter("MaximumNumberOfIterations", "8.0");
  silx.SetParameter("FinalGridSpacingInPhysicalUnits", "32.0");
  silx.SetFixedImage(fixedImage);
  silx.SetMovingImage(movingImage1);
  resultImage1 = silx.Execute();

  silx.PrintParameterMap(silx.GetTransformParameterMaps());

  TransformixImageFilter stfx;
  stfx.SetMovingImage(movingImage2);
  stfx.SetTransformParameterMaps(silx.GetTransformParameterMaps());
  resultImage2 = stfx.Execute();
}

#endif

} // namespace simple
} // namespace itk
