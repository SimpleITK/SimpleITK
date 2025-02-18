#include "SimpleITKTestHarness.h"
#include "sitkCastImageFilter.h"
#include "sitkElastixImageFilter.h"
#include "sitkImageFileReader.h"
#include "sitkImageFileWriter.h"
#include "sitkBinaryThresholdImageFilter.h"

#include <fstream>

namespace itk
{
namespace simple
{

bool
silxIsEmpty(const Image image)
{
  return (image.GetWidth() == 0 && image.GetHeight() == 0);
}

TEST(ElastixImageFilter, Instantiation) { ElastixImageFilter silx; }

TEST(ElastixImageFilter, DefaultParameterMaps)
{
  Image fixedImage = ReadImage(dataFinder.GetFile("Input/BrainProtonDensitySliceBorder20.png"));
  Image movingImage = ReadImage(dataFinder.GetFile("Input/BrainProtonDensitySliceShifted13x17y.png"));
  Image resultImage;

  ElastixImageFilter silx;
  EXPECT_NO_THROW(silx.SetFixedImage(fixedImage));
  EXPECT_NO_THROW(silx.SetMovingImage(movingImage));

  EXPECT_NO_THROW(silx.SetParameterMap(GetDefaultParameterMap("translation")));
  EXPECT_NO_THROW(silx.Execute());
  EXPECT_NO_THROW(resultImage = silx.GetResultImage());
  EXPECT_FALSE(silxIsEmpty(resultImage));

  EXPECT_NO_THROW(silx.SetParameterMap(GetDefaultParameterMap("rigid")));
  EXPECT_NO_THROW(silx.Execute());
  EXPECT_NO_THROW(resultImage = silx.GetResultImage());
  EXPECT_FALSE(silxIsEmpty(resultImage));

  EXPECT_NO_THROW(silx.SetParameterMap(GetDefaultParameterMap("affine")));
  EXPECT_NO_THROW(silx.Execute());
  EXPECT_NO_THROW(resultImage = silx.GetResultImage());
  EXPECT_FALSE(silxIsEmpty(resultImage));

  EXPECT_NO_THROW(silx.SetParameterMap(GetDefaultParameterMap("nonrigid")));
  EXPECT_NO_THROW(silx.Execute());
  EXPECT_NO_THROW(resultImage = silx.GetResultImage());
  EXPECT_FALSE(silxIsEmpty(resultImage));

  EXPECT_NO_THROW(silx.SetParameterMap(GetDefaultParameterMap("bspline")));
  EXPECT_NO_THROW(silx.Execute());
  EXPECT_NO_THROW(resultImage = silx.GetResultImage());
  EXPECT_FALSE(silxIsEmpty(resultImage));
}

TEST(ElastixImageFilter, Registration2D)
{
  Image fixedImage = ReadImage(dataFinder.GetFile("Input/BrainProtonDensitySliceBorder20.png"));
  Image movingImage = ReadImage(dataFinder.GetFile("Input/BrainProtonDensitySliceShifted13x17y.png"));
  Image resultImage;

  ElastixImageFilter silx;
  EXPECT_NO_THROW(silx.SetFixedImage(fixedImage));
  EXPECT_NO_THROW(silx.SetMovingImage(movingImage));
  EXPECT_NO_THROW(resultImage = silx.Execute());
  EXPECT_FALSE(silxIsEmpty(resultImage));
}

TEST(ElastixImageFilter, Masks)
{
  Image fixedImage = ReadImage(dataFinder.GetFile("Input/BrainProtonDensitySliceBorder20.png"));
  Image fixedMask = BinaryThreshold(Cast(fixedImage, sitkUInt8));
  Image fixedMaskInvalidType = Cast(fixedImage, sitkFloat32);
  Image movingImage = ReadImage(dataFinder.GetFile("Input/BrainProtonDensitySliceShifted13x17y.png"));
  Image movingMask = BinaryThreshold(Cast(movingImage, sitkUInt8));
  Image movingMaskInvalidType = Cast(movingImage, sitkFloat32);
  Image resultImage;

  ElastixImageFilter silx;
  EXPECT_NO_THROW(silx.SetParameter("ImageSampler", "RandomSparseMask"));
  EXPECT_NO_THROW(silx.SetParameter("MaximumNumberOfIterations", "1"));
  EXPECT_NO_THROW(silx.SetFixedImage(fixedImage));
  EXPECT_NO_THROW(silx.SetFixedMask(fixedMask));
  EXPECT_NO_THROW(silx.SetMovingImage(movingImage));
  EXPECT_NO_THROW(resultImage = silx.Execute());
  EXPECT_FALSE(silxIsEmpty(resultImage));

  // Only accept masks of pixel type unsigned char
  EXPECT_NO_THROW(silx.SetFixedMask(fixedMask));
  EXPECT_NO_THROW(silx.SetMovingMask(movingMaskInvalidType));
  EXPECT_THROW(silx.Execute(), GenericException);
  EXPECT_NO_THROW(silx.SetMovingMask(movingMask));
  EXPECT_NO_THROW(silx.Execute());
  EXPECT_NO_THROW(silx.SetFixedMask(fixedMaskInvalidType));
  EXPECT_THROW(silx.Execute(), GenericException);
}

TEST(ElastixImageFilter, ProceduralInterface)
{
  Image fixedImage = ReadImage(dataFinder.GetFile("Input/BrainProtonDensitySliceBorder20.png"));
  Image fixedMask = BinaryThreshold(Cast(fixedImage, sitkUInt8));
  Image fixedMaskInvalidType = Cast(fixedImage, sitkFloat32);
  Image movingImage = ReadImage(dataFinder.GetFile("Input/BrainProtonDensitySliceShifted13x17y.png"));
  Image movingMask = BinaryThreshold(Cast(movingImage, sitkUInt8));
  Image resultImage;

  std::string defaultParameterMapName = "translation";
  std::string outputDirectory = ".";

  EXPECT_NO_THROW(resultImage = Elastix(fixedImage, movingImage));
  EXPECT_FALSE(silxIsEmpty(resultImage));

  typedef ElastixImageFilter::ParameterMapVectorType   ParameterMapVectorType;
  typedef ElastixImageFilter::ParameterValueVectorType ParameterValueVectorType;
  ElastixImageFilter::ParameterMapType                 parameterMap = GetDefaultParameterMap(defaultParameterMapName);
  parameterMap["MaximumNumberOfIterations"] = ParameterValueVectorType(1, "1");
  EXPECT_NO_THROW(resultImage = Elastix(fixedImage, movingImage, parameterMap));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Elastix(fixedImage, movingImage, parameterMap, true));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Elastix(fixedImage, movingImage, parameterMap, false));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Elastix(fixedImage, movingImage, parameterMap, true, true));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Elastix(fixedImage, movingImage, parameterMap, false, false));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Elastix(fixedImage, movingImage, parameterMap, true, false));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Elastix(fixedImage, movingImage, parameterMap, false, true));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Elastix(fixedImage, movingImage, parameterMap, true, true, outputDirectory));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Elastix(fixedImage, movingImage, parameterMap, false, false, outputDirectory));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Elastix(fixedImage, movingImage, parameterMap, true, false, outputDirectory));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Elastix(fixedImage, movingImage, parameterMap, false, true, outputDirectory));
  EXPECT_FALSE(silxIsEmpty(resultImage));

  ParameterMapVectorType parameterMapVector;
  parameterMapVector.push_back(GetDefaultParameterMap(defaultParameterMapName));
  parameterMapVector[0]["MaximumNumberOfIterations"] = ParameterValueVectorType(1, "1");
  parameterMapVector.push_back(GetDefaultParameterMap("rigid"));
  parameterMapVector[1]["MaximumNumberOfIterations"] = ParameterValueVectorType(1, "1");
  EXPECT_NO_THROW(resultImage = Elastix(fixedImage, movingImage, parameterMapVector));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Elastix(fixedImage, movingImage, parameterMapVector, true));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Elastix(fixedImage, movingImage, parameterMapVector, false));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Elastix(fixedImage, movingImage, parameterMapVector, true, true));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Elastix(fixedImage, movingImage, parameterMapVector, false, false));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Elastix(fixedImage, movingImage, parameterMapVector, true, false));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Elastix(fixedImage, movingImage, parameterMapVector, false, true));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Elastix(fixedImage, movingImage, parameterMapVector, true, true, outputDirectory));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Elastix(fixedImage, movingImage, parameterMapVector, false, false, outputDirectory));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Elastix(fixedImage, movingImage, parameterMapVector, true, false, outputDirectory));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Elastix(fixedImage, movingImage, parameterMapVector, false, true, outputDirectory));
  EXPECT_FALSE(silxIsEmpty(resultImage));

  EXPECT_NO_THROW(resultImage =
                    Elastix(fixedImage, movingImage, defaultParameterMapName, fixedMask, movingMask, true, true));
  EXPECT_FALSE(silxIsEmpty(resultImage));

  EXPECT_NO_THROW(resultImage = Elastix(fixedImage, movingImage, parameterMap));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Elastix(fixedImage, movingImage, parameterMap, fixedMask, movingMask, true));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Elastix(fixedImage, movingImage, parameterMap, fixedMask, movingMask, false));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Elastix(fixedImage, movingImage, parameterMap, fixedMask, movingMask, true, true));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Elastix(fixedImage, movingImage, parameterMap, fixedMask, movingMask, false, false));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Elastix(fixedImage, movingImage, parameterMap, fixedMask, movingMask, true, false));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Elastix(fixedImage, movingImage, parameterMap, fixedMask, movingMask, false, true));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage =
                    Elastix(fixedImage, movingImage, parameterMap, fixedMask, movingMask, true, true, outputDirectory));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(
    resultImage = Elastix(fixedImage, movingImage, parameterMap, fixedMask, movingMask, false, false, outputDirectory));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(
    resultImage = Elastix(fixedImage, movingImage, parameterMap, fixedMask, movingMask, true, false, outputDirectory));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Elastix(fixedImage, movingImage, parameterMap, false, true, outputDirectory));
  EXPECT_FALSE(silxIsEmpty(resultImage));

  EXPECT_NO_THROW(resultImage = Elastix(fixedImage, movingImage, parameterMapVector, fixedMask, movingMask));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Elastix(fixedImage, movingImage, parameterMapVector, fixedMask, movingMask, true));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Elastix(fixedImage, movingImage, parameterMapVector, fixedMask, movingMask, false));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage =
                    Elastix(fixedImage, movingImage, parameterMapVector, fixedMask, movingMask, true, true));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage =
                    Elastix(fixedImage, movingImage, parameterMapVector, fixedMask, movingMask, false, false));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage =
                    Elastix(fixedImage, movingImage, parameterMapVector, fixedMask, movingMask, true, false));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage =
                    Elastix(fixedImage, movingImage, parameterMapVector, fixedMask, movingMask, false, true));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Elastix(
                    fixedImage, movingImage, parameterMapVector, fixedMask, movingMask, true, true, outputDirectory));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Elastix(
                    fixedImage, movingImage, parameterMapVector, fixedMask, movingMask, false, false, outputDirectory));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Elastix(
                    fixedImage, movingImage, parameterMapVector, fixedMask, movingMask, true, false, outputDirectory));
  EXPECT_FALSE(silxIsEmpty(resultImage));
  EXPECT_NO_THROW(resultImage = Elastix(
                    fixedImage, movingImage, parameterMapVector, fixedMask, movingMask, false, true, outputDirectory));
  EXPECT_FALSE(silxIsEmpty(resultImage));

  EXPECT_NO_THROW(PrintParameterMap(parameterMapVector));
}

TEST(ElastixImageFilter, MultipleFixedAndMovingImages)
{
  Image fixedImage0 = ReadImage(dataFinder.GetFile("Input/BrainProtonDensitySliceBorder20.png"));
  Image fixedImage1 = ReadImage(dataFinder.GetFile("Input/BrainProtonDensitySliceBorder20.png"));
  Image movingImage0 = ReadImage(dataFinder.GetFile("Input/BrainProtonDensitySliceShifted13x17y.png"));
  Image movingImage1 = ReadImage(dataFinder.GetFile("Input/BrainProtonDensitySliceShifted13x17y.png"));
  Image resultImage;

  ElastixImageFilter silx;
  silx.SetParameterMap("translation");
  silx.SetParameter("Registration", "MultiMetricMultiResolutionRegistration");
  silx.AddParameter("ImageSampler", silx.GetParameter(0, "ImageSampler"));
  silx.AddParameter("Interpolator", silx.GetParameter(0, "Interpolator"));
  silx.AddParameter("FixedImagePyramid", silx.GetParameter(0, "FixedImagePyramid"));
  silx.AddParameter("MovingImagePyramid", silx.GetParameter(0, "MovingImagePyramid"));
  silx.AddParameter("Metric", silx.GetParameter(0, "Metric"));

  EXPECT_NO_THROW(silx.AddFixedImage(fixedImage0));
  EXPECT_NO_THROW(silx.AddFixedImage(fixedImage1));
  EXPECT_NO_THROW(silx.AddMovingImage(movingImage0));
  EXPECT_NO_THROW(silx.AddMovingImage(movingImage1));
  EXPECT_NO_THROW(resultImage = silx.Execute());
  EXPECT_NO_THROW(resultImage = silx.Execute());
  EXPECT_FALSE(silxIsEmpty(resultImage));
}

TEST(ElastixImageFilter, RegistrationWithPointSets)
{
  // We generate the point sets manually
  std::string   fixedPointSetFileName = dataFinder.GetOutputFile("FixedPointSet.pts");
  std::ofstream fixedPointSetFile(fixedPointSetFileName.c_str(), std::ofstream::out);
  fixedPointSetFile << "point\n";
  fixedPointSetFile << "1\n";
  fixedPointSetFile << "128.0 128.0\n";
  fixedPointSetFile.close();

  std::string   movingPointSetFileName = dataFinder.GetOutputFile("MovingPointSet.pts");
  std::ofstream movingPointSetFile(movingPointSetFileName.c_str(), std::ofstream::out);
  movingPointSetFile << "point\n";
  movingPointSetFile << "1\n";
  movingPointSetFile << "115.0 111.0\n";
  movingPointSetFile.close();

  Image fixedImage = ReadImage(dataFinder.GetFile("Input/BrainProtonDensitySliceBorder20.png"));
  Image movingImage = ReadImage(dataFinder.GetFile("Input/BrainProtonDensitySliceShifted13x17y.png"));
  Image resultImage;

  ElastixImageFilter silx;
  silx.SetParameterMap("translation");
  silx.SetParameter("Registration", "MultiMetricMultiResolutionRegistration");
  silx.AddParameter("Metric", "CorrespondingPointsEuclideanDistanceMetric");
  silx.SetParameter("Metric0Weight", "0.0");

  EXPECT_NO_THROW(silx.SetFixedImage(fixedImage));
  EXPECT_NO_THROW(silx.SetFixedPointSetFileName(fixedPointSetFileName));
  EXPECT_NO_THROW(silx.SetMovingImage(movingImage));
  EXPECT_NO_THROW(silx.SetMovingPointSetFileName(movingPointSetFileName));
  EXPECT_NO_THROW(resultImage = silx.Execute());
  EXPECT_FALSE(silxIsEmpty(resultImage));
}

TEST(ElastixImageFilter, InitialTransform)
{
  std::string initialTransformParameterFileName = dataFinder.GetOutputFile("InitialTransformTestParameterFile.txt");
  Image       fixedImage = ReadImage(dataFinder.GetFile("Input/BrainProtonDensitySliceBorder20.png"));
  Image       movingImage = ReadImage(dataFinder.GetFile("Input/BrainProtonDensitySliceShifted13x17y.png"));
  Image       resultImage1;
  Image       resultImage2;

  ElastixImageFilter silx1;
  EXPECT_NO_THROW(silx1.SetFixedImage(fixedImage));
  EXPECT_NO_THROW(silx1.SetMovingImage(movingImage));
  EXPECT_NO_THROW(resultImage1 = silx1.Execute());
  EXPECT_FALSE(silxIsEmpty(resultImage1));
  WriteParameterFile(silx1.GetTransformParameterMap()[0], initialTransformParameterFileName);

  ElastixImageFilter silx2;
  EXPECT_NO_THROW(silx2.SetFixedImage(fixedImage));
  EXPECT_NO_THROW(silx2.SetMovingImage(movingImage));
  EXPECT_NO_THROW(silx2.SetInitialTransformParameterFileName(initialTransformParameterFileName));
  EXPECT_NO_THROW(resultImage2 = silx2.Execute());
  EXPECT_FALSE(silxIsEmpty(resultImage2));
}


TEST(ElastixImageFilter, SameFixedImageForMultipleRegistrations)
{
  Image fixedImage = ReadImage(dataFinder.GetFile("Input/BrainProtonDensitySliceBorder20.png"));
  Image movingImage1 = ReadImage(dataFinder.GetFile("Input/BrainProtonDensitySliceShifted13x17y.png"));
  Image movingImage2 = ReadImage(dataFinder.GetFile("Input/BrainProtonDensitySliceShifted13x17y.png"));
  Image resultImage1;
  Image resultImage2;

  ElastixImageFilter silx;
  EXPECT_NO_THROW(silx.SetFixedImage(fixedImage));
  EXPECT_NO_THROW(silx.SetMovingImage(movingImage1));
  EXPECT_NO_THROW(resultImage1 = silx.Execute());
  EXPECT_FALSE(silxIsEmpty(resultImage1));
  EXPECT_NO_THROW(silx.SetMovingImage(movingImage2));
  EXPECT_NO_THROW(resultImage2 = silx.Execute());
  EXPECT_FALSE(silxIsEmpty(resultImage2));
}

TEST(ElastixImageFilter, Registration3D)
{
  Image fixedImage = ReadImage(dataFinder.GetFile("Input/OAS1_0001_MR1_mpr-1_anon.nrrd"));
  Image movingImage = ReadImage(dataFinder.GetFile("Input/OAS1_0002_MR1_mpr-1_anon.nrrd"));
  Image resultImage;

  ElastixImageFilter silx;
  silx.SetParameter("MaximumNumberOfIterations", "1");
  EXPECT_NO_THROW(silx.SetFixedImage(fixedImage));
  EXPECT_NO_THROW(silx.SetMovingImage(movingImage));
  EXPECT_NO_THROW(resultImage = silx.Execute());
  EXPECT_FALSE(silxIsEmpty(resultImage));
}

TEST(ElastixImageFilter, SetNumberOfThreads)
{
  Image fixedImage = ReadImage(dataFinder.GetFile("Input/BrainProtonDensitySliceBorder20.png"));
  Image movingImage = ReadImage(dataFinder.GetFile("Input/BrainProtonDensitySliceShifted13x17y.png"));

  ElastixImageFilter silx;
  EXPECT_NO_THROW(silx.SetFixedImage(fixedImage));
  EXPECT_NO_THROW(silx.SetMovingImage(movingImage));
  EXPECT_NO_THROW(silx.SetParameter("MaximumNumberOfIterations", "1"));
  EXPECT_NO_THROW(silx.SetNumberOfThreads(1));
  EXPECT_NO_THROW(silx.Execute());
}


// Tests GetParameter(key) when exactly one parameter map is present.
TEST(ElastixImageFilter, GetParameterWhenOneParameterMapIsPresent)
{
  const ElastixImageFilter::ParameterKeyType         key = "key";
  const ElastixImageFilter::ParameterValueVectorType values{ "1", "2", "3" };
  const ElastixImageFilter::ParameterMapType         parameterMap{ { key, values } };

  ElastixImageFilter silx;
  silx.SetParameterMap(parameterMap);

  EXPECT_EQ(silx.GetParameter(key), values);
}

} // namespace simple
} // namespace itk
