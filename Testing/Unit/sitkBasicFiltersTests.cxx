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

#include <sitkImage.h>
#include <sitkImageFileReader.h>
#include <sitkImageFileWriter.h>
#include <sitkHashImageFilter.h>
#include <sitkGaussianImageSource.h>
#include <sitkRecursiveGaussianImageFilter.h>
#include <sitkCastImageFilter.h>
#include <sitkPixelIDValues.h>
#include <sitkStatisticsImageFilter.h>
#include <sitkExtractImageFilter.h>
#include <sitkFastMarchingBaseImageFilter.h>
#include <sitkInverseDeconvolutionImageFilter.h>
#include <sitkTikhonovDeconvolutionImageFilter.h>
#include <sitkWienerDeconvolutionImageFilter.h>
#include <sitkLandweberDeconvolutionImageFilter.h>
#include <sitkProjectedLandweberDeconvolutionImageFilter.h>
#include <sitkRichardsonLucyDeconvolutionImageFilter.h>
#include <sitkScalarToRGBColormapImageFilter.h>
#include <sitkJoinSeriesImageFilter.h>
#include <sitkGradientAnisotropicDiffusionImageFilter.h>
#include <sitkCurvatureAnisotropicDiffusionImageFilter.h>
#include <sitkLabelMapContourOverlayImageFilter.h>
#include <sitkPatchBasedDenoisingImageFilter.h>
#include <sitkConnectedThresholdImageFilter.h>
#include <sitkMergeLabelMapFilter.h>
#include <sitkDiffeomorphicDemonsRegistrationFilter.h>
#include <sitkFastSymmetricForcesDemonsRegistrationFilter.h>
#include <sitkOtsuThresholdImageFilter.h>
#include <sitkBSplineTransformInitializerFilter.h>
#include <sitkCenteredTransformInitializerFilter.h>
#include <sitkCenteredVersorTransformInitializerFilter.h>
#include <sitkLandmarkBasedTransformInitializerFilter.h>
#include <sitkAdditionalProcedures.h>
#include <sitkCommand.h>
#include <sitkResampleImageFilter.h>
#include <sitkSignedMaurerDistanceMapImageFilter.h>
#include <sitkDICOMOrientImageFilter.h>
#include <sitkPasteImageFilter.h>
#include <sitkN4BiasFieldCorrectionImageFilter.h>

#include "itkVectorImage.h"
#include "itkVector.h"
#include "itkRecursiveGaussianImageFilter.h"
#include "itkExtractImageFilter.h"
#include "itkFastMarchingImageFilterBase.h"
#include "itkScalarToRGBColormapImageFilter.h"
#include "itkInverseDeconvolutionImageFilter.h"
#include "itkTikhonovDeconvolutionImageFilter.h"
#include "itkWienerDeconvolutionImageFilter.h"
#include "itkLandweberDeconvolutionImageFilter.h"
#include "itkProjectedLandweberDeconvolutionImageFilter.h"
#include "itkRichardsonLucyDeconvolutionImageFilter.h"
#include "itkLabelMapContourOverlayImageFilter.h"
#include "itkPatchBasedDenoisingImageFilter.h"
#include "itkConnectedThresholdImageFilter.h"
#include "itkMergeLabelMapFilter.h"
#include "itkDiffeomorphicDemonsRegistrationFilter.h"
#include "itkFastSymmetricForcesDemonsRegistrationFilter.h"

#include "sitkShow.h"

#include "sitkVersorRigid3DTransform.h"
#include "sitkSimilarity3DTransform.h"
#include "sitkAffineTransform.h"
#include "sitkEuler2DTransform.h"
#include "sitkSimilarity2DTransform.h"
#include "sitkVersorTransform.h"
#include "sitkScaleVersor3DTransform.h"

TEST(BasicFilter,FastSymmetricForcesDemonsRegistrationFilter_ENUMCHECK) {
  using ImageType = itk::Image<float,3>;
  using DisplacementType = itk::Image<itk::Vector<float,3>,3>;
  using ITKType = itk::FastSymmetricForcesDemonsRegistrationFilter<ImageType,ImageType,DisplacementType>::DemonsRegistrationFunctionType;

  EXPECT_EQ( (int)ITKType::Symmetric, (int)itk::simple::FastSymmetricForcesDemonsRegistrationFilter::Symmetric);
  EXPECT_EQ( (int)ITKType::Fixed, (int)itk::simple::FastSymmetricForcesDemonsRegistrationFilter::Fixed);
  EXPECT_EQ( (int)ITKType::WarpedMoving, (int)itk::simple::FastSymmetricForcesDemonsRegistrationFilter::WarpedMoving);
  EXPECT_EQ( (int)ITKType::MappedMoving, (int)itk::simple::FastSymmetricForcesDemonsRegistrationFilter::MappedMoving);
}


TEST(BasicFilter,DiffeomorphicDemonsRegistrationFilter_ENUMCHECK) {
  using ImageType = itk::Image<float,3>;
  using DisplacementType = itk::Image<itk::Vector<float,3>,3>;
  using ITKType = itk::DiffeomorphicDemonsRegistrationFilter<ImageType,ImageType,DisplacementType>::DemonsRegistrationFunctionType;

  EXPECT_EQ( (int)ITKType::Symmetric, (int)itk::simple::DiffeomorphicDemonsRegistrationFilter::Symmetric);
  EXPECT_EQ( (int)ITKType::Fixed, (int)itk::simple::DiffeomorphicDemonsRegistrationFilter::Fixed);
  EXPECT_EQ( (int)ITKType::WarpedMoving, (int)itk::simple::DiffeomorphicDemonsRegistrationFilter::WarpedMoving);
  EXPECT_EQ( (int)ITKType::MappedMoving, (int)itk::simple::DiffeomorphicDemonsRegistrationFilter::MappedMoving);
}

TEST(BasicFilters,MergeLabelMap_ENUMCHECK) {
  using ITKType = itk::MergeLabelMapFilter< itk::LabelMap< itk::LabelObject<int, 3> > >;
  EXPECT_EQ( (int)ITKType::MethodChoice::KEEP, (int)itk::simple::MergeLabelMapFilter::Keep);
  EXPECT_EQ( (int)ITKType::MethodChoice::AGGREGATE, (int)itk::simple::MergeLabelMapFilter::Aggregate);
  EXPECT_EQ( (int)ITKType::MethodChoice::PACK, (int)itk::simple::MergeLabelMapFilter::Pack);
  EXPECT_EQ( (int)ITKType::MethodChoice::STRICT, (int)itk::simple::MergeLabelMapFilter::Strict);
}

TEST(BasicFilters,ScalarToRGBColormap_ENUMCHECK) {
  using ITKType = itk::ScalarToRGBColormapImageFilter< itk::Image<float,3>, itk::Image< itk::RGBPixel<float>,3> >;
  EXPECT_EQ( (int)ITKType::ColormapEnumType::Red, (int)itk::simple::ScalarToRGBColormapImageFilter::Red);
  EXPECT_EQ( (int)ITKType::ColormapEnumType::Green, (int)itk::simple::ScalarToRGBColormapImageFilter::Green);
  EXPECT_EQ( (int)ITKType::ColormapEnumType::Blue, (int)itk::simple::ScalarToRGBColormapImageFilter::Blue);
  EXPECT_EQ( (int)ITKType::ColormapEnumType::Grey, (int)itk::simple::ScalarToRGBColormapImageFilter::Grey);
  EXPECT_EQ( (int)ITKType::ColormapEnumType::Hot, (int)itk::simple::ScalarToRGBColormapImageFilter::Hot);
  EXPECT_EQ( (int)ITKType::ColormapEnumType::Cool, (int)itk::simple::ScalarToRGBColormapImageFilter::Cool);
  EXPECT_EQ( (int)ITKType::ColormapEnumType::Spring, (int)itk::simple::ScalarToRGBColormapImageFilter::Spring);
  EXPECT_EQ( (int)ITKType::ColormapEnumType::Summer, (int)itk::simple::ScalarToRGBColormapImageFilter::Summer);
  EXPECT_EQ( (int)ITKType::ColormapEnumType::Autumn, (int)itk::simple::ScalarToRGBColormapImageFilter::Autumn);
  EXPECT_EQ( (int)ITKType::ColormapEnumType::Winter, (int)itk::simple::ScalarToRGBColormapImageFilter::Winter);
  EXPECT_EQ( (int)ITKType::ColormapEnumType::Copper, (int)itk::simple::ScalarToRGBColormapImageFilter::Copper);
  EXPECT_EQ( (int)ITKType::ColormapEnumType::Jet, (int)itk::simple::ScalarToRGBColormapImageFilter::Jet);
  EXPECT_EQ( (int)ITKType::ColormapEnumType::HSV, (int)itk::simple::ScalarToRGBColormapImageFilter::HSV);
  EXPECT_EQ( (int)ITKType::ColormapEnumType::OverUnder, (int)itk::simple::ScalarToRGBColormapImageFilter::OverUnder);
}

TEST(BasicFilters,RecursiveGaussian_ENUMCHECK) {
  using ITKRecursiveGausianType = itk::RecursiveGaussianImageFilter< itk::Image<float,3> >;
  EXPECT_EQ( (int)ITKRecursiveGausianType::OrderEnumType::ZeroOrder, (int)itk::simple::RecursiveGaussianImageFilter::ZeroOrder );
  EXPECT_EQ( (int)ITKRecursiveGausianType::OrderEnumType::FirstOrder, (int)itk::simple::RecursiveGaussianImageFilter::FirstOrder );
  EXPECT_EQ( (int)ITKRecursiveGausianType::OrderEnumType::SecondOrder, (int)itk::simple::RecursiveGaussianImageFilter::SecondOrder );
}

TEST(BasicFilters,Extract_ENUMCHECK) {
  using ITKExtractType = itk::ExtractImageFilter< itk::Image<float,3>, itk::Image<float,3> >;
  EXPECT_EQ( (int)ITKExtractType::DirectionCollapseStrategyEnum::DIRECTIONCOLLAPSETOUNKOWN, (int)itk::simple::ExtractImageFilter::DIRECTIONCOLLAPSETOUNKOWN );
  EXPECT_EQ( (int)ITKExtractType::DirectionCollapseStrategyEnum::DIRECTIONCOLLAPSETOIDENTITY, (int)itk::simple::ExtractImageFilter::DIRECTIONCOLLAPSETOIDENTITY );
  EXPECT_EQ( (int)ITKExtractType::DirectionCollapseStrategyEnum::DIRECTIONCOLLAPSETOSUBMATRIX, (int)itk::simple::ExtractImageFilter::DIRECTIONCOLLAPSETOSUBMATRIX );
  EXPECT_EQ( (int)ITKExtractType::DirectionCollapseStrategyEnum::DIRECTIONCOLLAPSETOGUESS, (int)itk::simple::ExtractImageFilter::DIRECTIONCOLLAPSETOGUESS );
}

TEST(BasicFilters,FastMarching_ENUMCHECK) {
  using ITKType = itk::FastMarchingImageFilterBase< itk::Image<float,3>, itk::Image<float,3> >;
  EXPECT_EQ( (int) ITKType::Nothing, (int) itk::simple::FastMarchingBaseImageFilter::Nothing );
  EXPECT_EQ( (int) ITKType::NoHandles, (int) itk::simple::FastMarchingBaseImageFilter::NoHandles );
  EXPECT_EQ( (int) ITKType::Strict, (int) itk::simple::FastMarchingBaseImageFilter::Strict );
}

TEST(BasicFilters,InverseDeconvolution_ENUMCHECK) {
  using ITKType = itk::InverseDeconvolutionImageFilter< itk::Image<float,3>, itk::Image<float,3> >;
  EXPECT_EQ( (int) ITKType::OutputRegionModeEnum::SAME, (int) itk::simple::InverseDeconvolutionImageFilter::SAME );
  EXPECT_EQ( (int) ITKType::OutputRegionModeEnum::VALID, (int) itk::simple::InverseDeconvolutionImageFilter::VALID );
}

TEST(BasicFilters,TikhonovDeconvolution_ENUMCHECK) {
  using ITKType = itk::TikhonovDeconvolutionImageFilter< itk::Image<float,3>, itk::Image<float,3> >;
  EXPECT_EQ( (int) ITKType::OutputRegionModeEnum::SAME, (int) itk::simple::TikhonovDeconvolutionImageFilter::SAME );
  EXPECT_EQ( (int) ITKType::OutputRegionModeEnum::VALID, (int) itk::simple::TikhonovDeconvolutionImageFilter::VALID );
}

TEST(BasicFilters,WienerDeconvolution_ENUMCHECK) {
  using ITKType = itk::WienerDeconvolutionImageFilter< itk::Image<float,3>, itk::Image<float,3> >;
  EXPECT_EQ( (int) ITKType::OutputRegionModeEnum::SAME, (int) itk::simple::WienerDeconvolutionImageFilter::SAME );
  EXPECT_EQ( (int) ITKType::OutputRegionModeEnum::VALID, (int) itk::simple::WienerDeconvolutionImageFilter::VALID );
}

TEST(BasicFilters,LandweberDeconvolution_ENUMCHECK) {
  using ITKType = itk::LandweberDeconvolutionImageFilter< itk::Image<float,3>, itk::Image<float,3> >;
  EXPECT_EQ( (int) ITKType::OutputRegionModeEnum::SAME, (int) itk::simple::LandweberDeconvolutionImageFilter::SAME );
  EXPECT_EQ( (int) ITKType::OutputRegionModeEnum::VALID, (int) itk::simple::LandweberDeconvolutionImageFilter::VALID );
}

TEST(BasicFilters,ProjectedLandweberDeconvolution_ENUMCHECK) {
  using ITKType = itk::ProjectedLandweberDeconvolutionImageFilter< itk::Image<float,3>, itk::Image<float,3> >;
  EXPECT_EQ( (int) ITKType::OutputRegionModeEnum::SAME, (int) itk::simple::ProjectedLandweberDeconvolutionImageFilter::SAME );
  EXPECT_EQ( (int) ITKType::OutputRegionModeEnum::VALID, (int) itk::simple::ProjectedLandweberDeconvolutionImageFilter::VALID );
}

TEST(BasicFilters,RichardsonLucyDeconvolution_ENUMCHECK) {
  using ITKType = itk::RichardsonLucyDeconvolutionImageFilter< itk::Image<float,3>, itk::Image<float,3> >;
  EXPECT_EQ( (int) ITKType::OutputRegionModeEnum::SAME, (int) itk::simple::RichardsonLucyDeconvolutionImageFilter::SAME );
  EXPECT_EQ( (int) ITKType::OutputRegionModeEnum::VALID, (int) itk::simple::RichardsonLucyDeconvolutionImageFilter::VALID );
}

TEST(BasicFilters,LabelMapContourOverlay_ENUMCHECK) {
  using ITKType = itk::LabelMapContourOverlayImageFilter< itk::LabelMap<itk::LabelObject<int,3> >, itk::Image<float,3>, itk::VectorImage<int,3> >;
  EXPECT_EQ( (int) ITKType::PLAIN, (int)         itk::simple::LabelMapContourOverlayImageFilter::PLAIN );
  EXPECT_EQ( (int) ITKType::CONTOUR, (int)       itk::simple::LabelMapContourOverlayImageFilter::CONTOUR );
  EXPECT_EQ( (int) ITKType::SLICE_CONTOUR, (int) itk::simple::LabelMapContourOverlayImageFilter::SLICE_CONTOUR );


  EXPECT_EQ( (int) ITKType::HIGH_LABEL_ON_TOP, (int) itk::simple::LabelMapContourOverlayImageFilter::HIGH_LABEL_ON_TOP );
  EXPECT_EQ( (int) ITKType::LOW_LABEL_ON_TOP, (int) itk::simple::LabelMapContourOverlayImageFilter::LOW_LABEL_ON_TOP );

}

TEST(BasicFilters,PatchBasedBaseDenoising_ENUMCHECK) {
  using ITKType = itk::PatchBasedDenoisingImageFilter< itk::Image<float,3>, itk::Image<float,3> >;
  EXPECT_EQ( (int) ITKType::NOMODEL, (int) itk::simple::PatchBasedDenoisingImageFilter::NOMODEL );
  EXPECT_EQ( (int) ITKType::GAUSSIAN, (int) itk::simple::PatchBasedDenoisingImageFilter::GAUSSIAN );
  EXPECT_EQ( (int) ITKType::RICIAN, (int) itk::simple::PatchBasedDenoisingImageFilter::RICIAN );
  EXPECT_EQ( (int) ITKType::POISSON, (int) itk::simple::PatchBasedDenoisingImageFilter::POISSON );
}


TEST(BasicFilters,ConnectedThreshold_ENUMCHECK) {
  using ITKType = itk::ConnectedThresholdImageFilter< itk::Image<float,3>, itk::Image<float,3> >;
  EXPECT_EQ( (int) ITKType::FaceConnectivity, (int) itk::simple::ConnectedThresholdImageFilter::FaceConnectivity );
  EXPECT_EQ( (int) ITKType::FullConnectivity, (int) itk::simple::ConnectedThresholdImageFilter::FullConnectivity );
}

TEST(BasicFilter,GradientAnisotropicDiffusion_EstimateOptimalTimeStep) {
  // This test is to check the correctness of the
  // EstimateOptimalTimeStep

  namespace sitk = itk::simple;

  sitk::Image img;
  ASSERT_NO_THROW( img = sitk::ReadImage( dataFinder.GetFile ( "Input/RA-Float.nrrd" ) ) ) << "Reading input Image.";

  std::vector<double> spacing( 3, 1.0 );

  img.SetSpacing( spacing );
  sitk::GradientAnisotropicDiffusionImageFilter filter;

  filter.SetTimeStep( 0 );

  EXPECT_EQ( filter.EstimateOptimalTimeStep( img ), 0.125 );
  EXPECT_EQ( filter.GetTimeStep(), 0.125 );

  spacing[0] = 2.0;
  spacing[1] = 2.0;
  spacing[2] = 10.0;
  img.SetSpacing( spacing );

  EXPECT_EQ( filter.EstimateOptimalTimeStep( img ), 0.25 );
  EXPECT_EQ( filter.GetTimeStep(), 0.25 );

  img = sitk::Image( 100, 100, sitk::sitkUInt32 );

  spacing[0] = 10.0;
  spacing[1] = 100.0;
  img.SetSpacing( spacing );

  EXPECT_EQ( filter.EstimateOptimalTimeStep( img ), 2.5 );
  EXPECT_EQ( filter.GetTimeStep(), 2.5 );

}


TEST(BasicFilter,CurvatureAnisotropicDiffusion_EstimateOptimalTimeStep) {
  // This test is to check the correctness of the
  // EstimateOptimalTimeStep

  namespace sitk = itk::simple;

  sitk::Image img;
  ASSERT_NO_THROW( img = sitk::ReadImage( dataFinder.GetFile ( "Input/RA-Float.nrrd" ) ) ) << "Reading input Image.";

  std::vector<double> spacing( 3, 1.0 );
  img.SetSpacing( spacing );

  sitk::CurvatureAnisotropicDiffusionImageFilter filter;

  filter.SetTimeStep( 0 );

  EXPECT_EQ( filter.EstimateOptimalTimeStep( img ), 0.0625 );
  EXPECT_EQ( filter.GetTimeStep(), 0.0625 );

  spacing[0] = 2.0;
  spacing[1] = 2.0;
  spacing[2] = 10.0;
  img.SetSpacing( spacing );

  EXPECT_EQ( filter.EstimateOptimalTimeStep( img ), 0.125 );
  EXPECT_EQ( filter.GetTimeStep(), 0.125 );

  img = sitk::Image( 100, 100, sitk::sitkUInt32 );

  spacing[0] = 10.0;
  spacing[1] = 100.0;
  img.SetSpacing( spacing );

  EXPECT_EQ( filter.EstimateOptimalTimeStep( img ), 1.25 );
  EXPECT_EQ( filter.GetTimeStep(), 1.25 );

}

TEST(BasicFilters,ImageFilter) {
  namespace sitk = itk::simple;

  sitk::CastImageFilter caster;
  sitk::ImageFilter &filter = caster;

  filter.DebugOn();
}

TEST(BasicFilters,ProcessObject_Debug) {
  namespace sitk = itk::simple;

  sitk::CastImageFilter caster;
  sitk::ProcessObject &filter = caster;

  EXPECT_FALSE(filter.GetGlobalDefaultDebug());
  EXPECT_FALSE(filter.GetDebug());

  filter.DebugOff();
  EXPECT_FALSE(filter.GetDebug());
  EXPECT_FALSE(filter.GetGlobalDefaultDebug());

  filter.DebugOn();
  EXPECT_TRUE(filter.GetDebug());
  EXPECT_FALSE(filter.GetGlobalDefaultDebug());

  filter.GlobalDefaultDebugOn();
  EXPECT_TRUE(filter.GetDebug());
  EXPECT_TRUE(filter.GetGlobalDefaultDebug());

  filter.GlobalDefaultDebugOff();
  EXPECT_TRUE(filter.GetDebug());
  EXPECT_FALSE(filter.GetGlobalDefaultDebug());

  filter.GlobalDefaultDebugOn();

  sitk::CastImageFilter caster2;
  EXPECT_TRUE(caster2.GetDebug());
  EXPECT_TRUE(caster2.GetGlobalDefaultDebug());

}

TEST(BasicFilters,ProcessObject_NumberOfThreads) {
  namespace sitk = itk::simple;

  sitk::CastImageFilter caster;
  sitk::ProcessObject &filter = caster;

  unsigned int gNum = filter.GetGlobalDefaultNumberOfThreads();
  EXPECT_NE(filter.GetGlobalDefaultNumberOfThreads(), 0u);
  EXPECT_NE(filter.GetNumberOfThreads(), 0u);
  EXPECT_EQ(filter.GetNumberOfThreads(), filter.GetGlobalDefaultNumberOfThreads());

  filter.SetNumberOfThreads(3);
  EXPECT_EQ(3u, filter.GetNumberOfThreads());
  EXPECT_EQ(gNum, filter.GetGlobalDefaultNumberOfThreads());

  filter.SetGlobalDefaultNumberOfThreads(gNum+1);
  EXPECT_EQ(gNum+1, filter.GetGlobalDefaultNumberOfThreads());
  EXPECT_EQ(3u, filter.GetNumberOfThreads());

  sitk::CastImageFilter caster2;
  EXPECT_EQ(gNum+1, caster2.GetNumberOfThreads());
  EXPECT_EQ(gNum+1, caster2.GetGlobalDefaultNumberOfThreads());
}

TEST(BasicFilters,Cast) {
  itk::simple::HashImageFilter hasher;
  itk::simple::ImageFileReader reader;

  reader.SetFileName ( dataFinder.GetFile ( "Input/RA-Float.nrrd" ) );
  itk::simple::Image image = reader.Execute();
  ASSERT_NE ( image.GetITKBase(), nullptr );
  hasher.SetHashFunction ( itk::simple::HashImageFilter::MD5 );
  EXPECT_EQ ( "3ccccde44efaa3d688a86e94335c1f16", hasher.Execute ( image ) );

  EXPECT_EQ ( image.GetPixelIDValue(), itk::simple::sitkFloat32 );
  EXPECT_EQ ( image.GetPixelID(), itk::simple::sitkFloat32 );
  EXPECT_EQ ( image.GetPixelIDTypeAsString(), "32-bit float" );

  using MapType = std::map<std::string,itk::simple::PixelIDValueEnum>;
  MapType mapping;
  mapping["2f27e9260baeba84fb83dd35de23fa2d"] = itk::simple::sitkUInt8;
  mapping["2f27e9260baeba84fb83dd35de23fa2d"] = itk::simple::sitkInt8;
  mapping["a963bd6a755b853103a2d195e01a50d3"] = itk::simple::sitkUInt16;
  mapping["a963bd6a755b853103a2d195e01a50d3"] = itk::simple::sitkInt16;
  mapping["6ceea0011178a955b5be2d545d107199"] = itk::simple::sitkUInt32;
  mapping["6ceea0011178a955b5be2d545d107199"] = itk::simple::sitkInt32;
  mapping["efa4c3b27349b97b02a64f3d2b5ca9ed"] = itk::simple::sitkUInt64;
  mapping["efa4c3b27349b97b02a64f3d2b5ca9ed"] = itk::simple::sitkInt64;
  mapping["3ccccde44efaa3d688a86e94335c1f16"] = itk::simple::sitkFloat32;
  mapping["ac0228acc17038fd1f1ed28eb2841c73"] = itk::simple::sitkFloat64;
  mapping["226dabda8fc07f20e2b9e44ca1c83955"] = itk::simple::sitkComplexFloat32;
  mapping["e92cbb187a92610068d7de0cb23364db"] = itk::simple::sitkComplexFloat64;
  mapping["2f27e9260baeba84fb83dd35de23fa2d"] = itk::simple::sitkVectorUInt8;
  mapping["2f27e9260baeba84fb83dd35de23fa2d"] = itk::simple::sitkVectorInt8;
  mapping["a963bd6a755b853103a2d195e01a50d3"] = itk::simple::sitkVectorUInt16;
  mapping["a963bd6a755b853103a2d195e01a50d3"] = itk::simple::sitkVectorInt16;
  mapping["6ceea0011178a955b5be2d545d107199"] = itk::simple::sitkVectorUInt32;
  mapping["6ceea0011178a955b5be2d545d107199"] = itk::simple::sitkVectorInt32;
  mapping["efa4c3b27349b97b02a64f3d2b5ca9ed"] = itk::simple::sitkVectorUInt64;
  mapping["efa4c3b27349b97b02a64f3d2b5ca9ed"] = itk::simple::sitkVectorInt64;
  mapping["3ccccde44efaa3d688a86e94335c1f16"] = itk::simple::sitkVectorFloat32;
  mapping["ac0228acc17038fd1f1ed28eb2841c73"] = itk::simple::sitkVectorFloat64;
  mapping["sitkLabelUInt8"] = itk::simple::sitkLabelUInt8;
  mapping["sitkLabelUInt16"] = itk::simple::sitkLabelUInt16;
  mapping["sitkLabelUInt32"] = itk::simple::sitkLabelUInt32;
  mapping["sitkLabelUInt64"] = itk::simple::sitkLabelUInt64;

  bool failed = false;

  // Loop over the map, load each file, and compare the hash value
  for ( MapType::iterator it = mapping.begin(); it != mapping.end(); ++it )
    {
    itk::simple::PixelIDValueEnum pixelID = it->second;
    std::string hash = it->first;

    std::cerr << std::flush;
    std::cerr << std::flush;
    if ( pixelID == itk::simple::sitkUnknown )
      {
      std::cerr << "Enum value: " << pixelID << " (" << hash << ") is unknown and not instantiated" << std::endl;
      continue;
      }

    std::cerr << "Testing casting to pixelID: " << pixelID << " is " << itk::simple::GetPixelIDValueAsString ( pixelID ) << std::endl;

    try
      {
      itk::simple::CastImageFilter caster;
      itk::simple::Image test = caster.SetOutputPixelType ( pixelID ).Execute ( image );

      hasher.SetHashFunction ( itk::simple::HashImageFilter::MD5 );
      EXPECT_EQ ( hash, hasher.Execute ( test ) ) << "Cast to " << itk::simple::GetPixelIDValueAsString ( pixelID );

      }
    catch ( ::itk::simple::GenericException &e )
      {

      // hashing currently doesn't work for label images
      if ( hash.find( "sitkLabel" ) == 0 )
        {
        std::cerr << "Hashing currently is not implemented for Label Images" << std::endl;
        }
      else
        {
        failed = true;
        std::cerr << "Failed to hash: " << e.what() << std::endl;
        }

      continue;
      }

  }
  EXPECT_FALSE ( failed ) << "Cast failed, or could not take the hash of the imoge";

}

TEST(BasicFilters,HashImageFilter) {
  itk::simple::HashImageFilter hasher;
  std::string out = hasher.ToString();
  EXPECT_TRUE ( out.find("itk::simple::HashImageFilter") != std::string::npos );
  EXPECT_TRUE ( out.find("HashFunction: SHA1") != std::string::npos );
  EXPECT_TRUE ( out.find("Debug:") != std::string::npos );
  EXPECT_TRUE ( out.find("NumberOfThreads:") != std::string::npos );
  EXPECT_EQ ( itk::simple::HashImageFilter::SHA1, hasher.SetHashFunction ( itk::simple::HashImageFilter::SHA1 ).GetHashFunction() );
  EXPECT_EQ ( itk::simple::HashImageFilter::MD5, hasher.SetHashFunction ( itk::simple::HashImageFilter::MD5 ).GetHashFunction() );
}


TEST(BasicFilters,BSplineTransformInitializer) {
  namespace sitk = itk::simple;

  sitk::BSplineTransformInitializerFilter filter;

  EXPECT_EQ ( "BSplineTransformInitializerFilter", filter.GetName() );
  EXPECT_EQ ( std::vector<uint32_t>(3,1u), filter.GetTransformDomainMeshSize() );
  EXPECT_EQ ( std::vector<uint32_t>(3,10u), filter.SetTransformDomainMeshSize(std::vector<uint32_t>(3,10u)).GetTransformDomainMeshSize() );

  const double cs = 0.5*itk::Math::sqrt2; // cos(pi/4) = sin(pi/4)
  sitk::Image img( 100, 100, sitk::sitkUInt32 );
  img.SetDirection(v4(cs,-cs,cs,cs) );
  img.SetSpacing( v2(2,2) );


  sitk::BSplineTransform outTx = filter.Execute( img );
  EXPECT_EQ ( std::vector<uint32_t>(2,10u), outTx.GetTransformDomainMeshSize() );
  EXPECT_VECTOR_DOUBLE_NEAR ( v4(cs,-cs,cs,cs), outTx.GetTransformDomainDirection(), 1e-6 );
   EXPECT_VECTOR_DOUBLE_NEAR ( v2(0, -1.7677669525146484 ), outTx.GetTransformDomainOrigin(), 1e-6 );
  EXPECT_VECTOR_DOUBLE_NEAR ( v2(10.025, 20.05), outTx.GetTransformDomainPhysicalDimensions(), 1e6);
  EXPECT_EQ ( 10u, outTx.GetFixedParameters().size() );

  // 3D
  img = sitk::Image(10,10,10,  sitk::sitkUInt32 );

  outTx = sitk::BSplineTransformInitializer( img, std::vector<uint32_t>(3,5u) );
  EXPECT_EQ( std::vector<uint32_t>(3,5u), outTx.GetTransformDomainMeshSize() );

  // check that it's identity
  EXPECT_VECTOR_DOUBLE_NEAR( outTx.TransformPoint( v3(0.0,0.0,0.0) ), v3(0.0,0.0,0.0), 1e-17);
  EXPECT_VECTOR_DOUBLE_NEAR( outTx.TransformPoint( v3(1.123,0.0,2.0) ), v3(1.123,0.0,2.0), 1e-17);
  EXPECT_VECTOR_DOUBLE_NEAR( outTx.TransformPoint( v3(0.0,0.0,5.0) ), v3(0.0,0.0,5.0), 1e-17);
  EXPECT_VECTOR_DOUBLE_NEAR( outTx.TransformPoint( v3(5.0,7.0,9.0) ), v3(5.0,7.0,9.0), 1e-17);

}

TEST(BasicFilters, BSplineTransformInitializerRequestedRegion) {
  namespace sitk = itk::simple;

  //check that changing the image's requested region does not change
  //the BSplineTransformInitializer
  sitk::Image img( 482, 360, 141, sitk::sitkFloat32 );
  img.SetSpacing( v3(0.97656, 0.97656, 2) );
  std::vector<unsigned int> extractSize(3);
  extractSize[0] = 482;
  extractSize[1] = 0;
  extractSize[2] = 141;
  std::vector<int> extractIndex(3);
  extractIndex[0] = 0;
  extractIndex[1] = 176;
  extractIndex[2] = 0;

  std::vector<uint32_t> transformDomainMeshSize(3);
  transformDomainMeshSize[0] = 9;
  transformDomainMeshSize[1] = 7;
  transformDomainMeshSize[2] = 6;
  sitk::BSplineTransform transformBefore(3), transformAfter(3);
  transformBefore = sitk::BSplineTransformInitializer( img, transformDomainMeshSize );

  sitk::Extract(img, extractSize, extractIndex);

  transformAfter = sitk::BSplineTransformInitializer( img, transformDomainMeshSize );

  //the extract filter should not have any effect on the
  //BSplineTransformInitializer, it only changed the image's
  //requested region
  EXPECT_VECTOR_DOUBLE_NEAR( transformBefore.GetTransformDomainPhysicalDimensions(), transformAfter.GetTransformDomainPhysicalDimensions(), 1e-17 );
  EXPECT_VECTOR_DOUBLE_NEAR( transformBefore.GetTransformDomainOrigin(), transformAfter.GetTransformDomainOrigin(), 1e-17 );

}

TEST(BasicFilters,CenteredTransformInitializer) {
  namespace sitk = itk::simple;

  sitk::CenteredTransformInitializerFilter filter;

  EXPECT_EQ ( "CenteredTransformInitializerFilter", filter.GetName() );
  EXPECT_EQ ( sitk::CenteredTransformInitializerFilter::MOMENTS, filter.GetOperationMode() );
  filter.GeometryOn();
  EXPECT_EQ ( sitk::CenteredTransformInitializerFilter::GEOMETRY, filter.GetOperationMode() );
  filter.MomentsOn();
  EXPECT_EQ ( sitk::CenteredTransformInitializerFilter::MOMENTS, filter.GetOperationMode() );

  sitk::Image fixed = sitk::ReadImage( dataFinder.GetFile( "Input/BrainProtonDensitySliceBorder20.png") );
  sitk::Image moving = sitk::ReadImage( dataFinder.GetFile( "Input/BrainProtonDensitySliceShifted13x17y.png" ) );

  sitk::Transform tx = sitk::Transform(2, sitk::sitkAffine);

  sitk::Transform outTx = filter.Execute( fixed, moving , tx );

  std::vector<double> params = outTx.GetFixedParameters();

  ASSERT_EQ( 2u, params.size() );
  EXPECT_EQ( 0.0, tx.GetFixedParameters()[0] );
  EXPECT_EQ( 0.0, tx.GetFixedParameters()[1] );
  EXPECT_FLOAT_EQ ( 111.20356, params[0] );
  EXPECT_FLOAT_EQ ( 131.59097, params[1] );


  tx = sitk::Transform(2, sitk::sitkEuler);

  outTx = sitk::CenteredTransformInitializer( fixed, moving, tx );

  params = outTx.GetFixedParameters();

  ASSERT_EQ( 2u, params.size() );
  EXPECT_EQ( 0.0, tx.GetFixedParameters()[0] );
  EXPECT_EQ( 0.0, tx.GetFixedParameters()[1] );
  EXPECT_FLOAT_EQ ( 111.20356, params[0] );
  EXPECT_FLOAT_EQ ( 131.59097, params[1] );

}


TEST(BasicFilters,CenteredVersorTransformInitializer) {
  namespace sitk = itk::simple;

  sitk::CenteredVersorTransformInitializerFilter filter;

  EXPECT_EQ ( "CenteredVersorTransformInitializerFilter", filter.GetName() );
  EXPECT_EQ ( filter.GetComputeRotation(), false );
  EXPECT_EQ ( filter.ComputeRotationOn().GetComputeRotation(), true );
  EXPECT_EQ ( filter.ComputeRotationOff().GetComputeRotation(), false );

  // generate a few basic test images from gaussian blobs

  sitk::GaussianImageSource source;
  source.SetOutputPixelType( sitk::sitkFloat32 );
  source.SetSize( std::vector< unsigned int >(3, 128) );
  source.SetMean( v3(64.0, 64.0, 64.0) );
  source.SetSigma( v3( 10.0, 15.0, 20.0) );

  const sitk::Image g1 = source.Execute();

  source.SetMean( v3(63.0, 62.0, 61.0) );
  const sitk::Image g2 = source.Execute();

  source.SetMean( v3(63.0, 62.0, 61.0) );
  source.SetSigma( v3( 15.0, 20.0, 10) );
  const sitk::Image g3 = source.Execute();

  {
  sitk::VersorRigid3DTransform tx;

  filter.ComputeRotationOff();
  tx = sitk::VersorRigid3DTransform( filter.Execute(g1, g2, sitk::VersorRigid3DTransform() ) );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.GetTranslation(), v3(-1.0,-2.0,-3.0), 0.1 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.GetCenter(), v3(64.0,64.0,64.0), 0.1 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.GetVersor(), v4(0.0, 0.0,0.0,1.0), 1e-15 );
  tx = sitk::VersorRigid3DTransform( filter.Execute(g1, g3, sitk::VersorRigid3DTransform() ) );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.GetTranslation(), v3(-1.0,-2.0,-3.0), 0.1 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.GetCenter(), v3(64.0,64.0,64.0), 0.1 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.GetVersor(), v4(0.0, 0.0,0.0,1.0), 1e-15 );

  filter.ComputeRotationOn();
  tx = sitk::VersorRigid3DTransform( filter.Execute(g1, g2, sitk::VersorRigid3DTransform() ) );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.GetTranslation(), v3(-1.0,-2.0,-3.0), 0.1 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.GetCenter(), v3(64.0,64.0,64.0), 0.1 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.GetVersor(), v4(0.0, 0.0,0.0,1.0), 1e-5 );
  tx = sitk::VersorRigid3DTransform( filter.Execute(g1, g3, sitk::VersorRigid3DTransform() ) );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.GetTranslation(), v3(-1.0,-2.0,-3.0), 0.1 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.GetCenter(), v3(64.0,64.0,64.0), 0.1 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.GetVersor(), v4(-0.5, -0.5,0.5,0.5), 1e-5 );
  }

  {
  sitk::Similarity3DTransform tx;

  filter.ComputeRotationOff();
  tx = sitk::Similarity3DTransform( filter.Execute(g1, g2, sitk::Similarity3DTransform() ) );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.GetTranslation(), v3(-1.0,-2.0,-3.0), 0.1 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.GetCenter(), v3(64.0,64.0,64.0), 0.1 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.GetVersor(), v4(0.0, 0.0,0.0,1.0), 1e-15 );
  tx = sitk::Similarity3DTransform( filter.Execute(g1, g3, sitk::Similarity3DTransform() ) );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.GetTranslation(), v3(-1.0,-2.0,-3.0), 0.1 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.GetCenter(), v3(64.0,64.0,64.0), 0.1 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.GetVersor(), v4(0.0, 0.0,0.0,1.0), 1e-15 );

  filter.ComputeRotationOn();
  tx = sitk::Similarity3DTransform( filter.Execute(g1, g2, sitk::Similarity3DTransform() ) );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.GetTranslation(), v3(-1.0,-2.0,-3.0), 0.1 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.GetCenter(), v3(64.0,64.0,64.0), 0.1 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.GetVersor(), v4(0.0, 0.0,0.0,1.0), 1e-5 );
  tx = sitk::Similarity3DTransform( filter.Execute(g1, g3, sitk::Similarity3DTransform() ) );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.GetTranslation(), v3(-1.0,-2.0,-3.0), 0.1 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.GetCenter(), v3(64.0,64.0,64.0), 0.1 );
  EXPECT_VECTOR_DOUBLE_NEAR( tx.GetVersor(), v4(-0.5, -0.5,0.5,0.5), 1e-5 );
  }

  EXPECT_THROW( sitk::CenteredVersorTransformInitializer(g1, g2, sitk::Transform(2,sitk::sitkSimilarity)), sitk::GenericException );
  EXPECT_THROW( sitk::CenteredVersorTransformInitializer(g1, g2, sitk::Transform(3,sitk::sitkVersor)), sitk::GenericException );
  EXPECT_THROW( sitk::CenteredVersorTransformInitializer(g1, g2, sitk::Transform(3,sitk::sitkAffine)), sitk::GenericException );
  EXPECT_THROW( sitk::CenteredVersorTransformInitializer(g1, g2, sitk::Transform(3,sitk::sitkQuaternionRigid)), sitk::GenericException );
  EXPECT_THROW( sitk::CenteredVersorTransformInitializer(g1, g2, sitk::Transform(3,sitk::sitkTranslation)), sitk::GenericException );


}



TEST(BasicFilters,LandmarkBasedTransformInitializer) {
  namespace sitk = itk::simple;

  sitk::LandmarkBasedTransformInitializerFilter filter;


  const double points2d[] = { 0.0,0.0, 1.0,1.0, 1.0,0.0, 1.1,1.0,  2.34, 10.98};

  std::vector<double> fixedPoints(&points2d[0], &points2d[10]);
  std::vector<double> movingPoints(&points2d[0], &points2d[10]);


  sitk::Transform out;

  filter.SetFixedLandmarks( fixedPoints );
  filter.SetMovingLandmarks( movingPoints );


  EXPECT_EQ ( "LandmarkBasedTransformInitializerFilter", filter.GetName() );

  out = filter.Execute( sitk::Euler2DTransform() );
  EXPECT_VECTOR_DOUBLE_NEAR(v3(0.0, 0.0, 0.0), out.GetParameters(), 1e-15);

  out = filter.Execute( sitk::Similarity2DTransform() );
  EXPECT_VECTOR_DOUBLE_NEAR(v4(1.0, 0.0, 0.0, 0.0), out.GetParameters(), 1e-15);


  EXPECT_ANY_THROW( filter.Execute( sitk::VersorTransform() ) );

  out = filter.Execute( sitk::VersorRigid3DTransform() );
  EXPECT_VECTOR_DOUBLE_NEAR(v6(0.0, 0.0, 0.0, 0.0, 0.0, 0.0), out.GetParameters(), 1e-15);

  out = filter.Execute( sitk::ScaleVersor3DTransform() );
  EXPECT_VECTOR_DOUBLE_NEAR(v9(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0), out.GetParameters(), 1e-15);


  out = filter.Execute( sitk::AffineTransform(2) );
  EXPECT_VECTOR_DOUBLE_NEAR(v6(1.0, 0.0, 0.0, 1.0, 0.0, 0.0), out.GetParameters(), 1e-8);

  const double fixedImagePoints3d[] = {127.53915086334257, 102.12639903012848, 44.0,
                                       198.641578144495, 101.59971438360141, 44.0,
                                       156.82957119036902, 215.70110997158648, 48.0,
                                       176.63477775277258, 144.97363079485118, 64.0};

  const double movingImagePoints3d[] = {181.40169895047495, 242.55513079230616, 24.0,
                                        112.90638157274341, 246.938831104481, 24.0,
                                        141.07588005861425, 134.62809649982117, 28.0,
                                        126.66162032855607, 208.7334122120106, 44.0};
  fixedPoints.clear();
  fixedPoints.insert(fixedPoints.begin(), &fixedImagePoints3d[0], &fixedImagePoints3d[12]);
  movingPoints.clear();
  movingPoints.insert(movingPoints.begin(), &movingImagePoints3d[0], &movingImagePoints3d[12]);
  filter.SetFixedLandmarks( fixedPoints );
  filter.SetMovingLandmarks( movingPoints );

  out = filter.Execute( sitk::AffineTransform(3) );

  EXPECT_VECTOR_DOUBLE_NEAR(v12(-9.64081213e-01, -1.01003445e-01, -1.54009453e-01,
                                5.44421946e-02, -9.73501195e-01, 2.60861955e-01,
                                -2.64945988e-14, -3.95920761e-14, 1.00000000e+00,
                                321.45133233, 323.55386506, -20.0), out.GetParameters(), 1e-8);

  const double pointsBSplineTest2D[] = {0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 1.1, 1.0, 2.34, 10.98};
  fixedPoints.clear();
  fixedPoints.insert(fixedPoints.begin(), &pointsBSplineTest2D[0], &pointsBSplineTest2D[10]);
  movingPoints.clear();
  movingPoints.insert(movingPoints.begin(), &pointsBSplineTest2D[0], &pointsBSplineTest2D[10]);
  filter.SetFixedLandmarks( fixedPoints );
  filter.SetMovingLandmarks( movingPoints );
  filter.SetBSplineNumberOfControlPoints( 5 );

  // Image isn't set so we expect an exception
  EXPECT_ANY_THROW( filter.Execute( sitk::BSplineTransform( 2 ) ) );

  std::vector< double > spacing;
  spacing.push_back(0.5);
  spacing.push_back(1);
  std::vector< double > origin;
  origin.push_back(-5.0);
  origin.push_back(-5.0);
  sitk::Image referenceImage( 25, 50, sitk::sitkFloat32 );
  referenceImage.SetSpacing( spacing );
  referenceImage.SetOrigin( origin );
  filter.SetReferenceImage( referenceImage );

  // Expecting the identity transform (BSpline parameters are all zero)
  out = filter.Execute(sitk::BSplineTransform(2));
  EXPECT_VECTOR_DOUBLE_NEAR(std::vector<double>(out.GetParameters().size(), 0.0), out.GetParameters(), 1e-25);

  // Translate the moving points in the x direction
  double dxSize = 3.5;
  for( unsigned int i = 0; i<movingPoints.size(); i+=2 )
    {
    movingPoints[i]+=dxSize;
    }
  filter.SetMovingLandmarks( movingPoints );

  out = filter.Execute( sitk::BSplineTransform(2) );

  // Transform the fixed points using the estimated BSpline transform
  // and compare the to moving points.
  for( unsigned int i = 0; i<fixedPoints.size(); i+=2 )
    {
    EXPECT_VECTOR_DOUBLE_NEAR( out.TransformPoint(v2(fixedPoints[i], fixedPoints[i+1])), v2(movingPoints[i], movingPoints[i+1]), 0.1 );
    }

  // The ITK filter only supports BSplines of order 3. Unfortunately,
  // because the transform is templated we don't have a way for
  // obtaining the spline order so we just check that ITK throws the
  // expected exception when we use a spline order of 2.
  EXPECT_ANY_THROW( filter.Execute( sitk::BSplineTransform( 2, 2 ) ) );
}


TEST(BasicFilters,Cast_Commands) {
  // test cast filter with a bunch of commands

  namespace sitk = itk::simple;
  sitk::Image img = sitk::ReadImage( dataFinder.GetFile ( "Input/RA-Short.nrrd" ) );
  EXPECT_EQ ( "a963bd6a755b853103a2d195e01a50d3", sitk::Hash(img, sitk::HashImageFilter::MD5));

  sitk::CastImageFilter caster;
  caster.SetOutputPixelType( sitk::sitkInt32 );

  ProgressUpdate progressCmd(caster);
  caster.AddCommand(sitk::sitkProgressEvent, progressCmd);

  CountCommand abortCmd(caster);
  caster.AddCommand(sitk::sitkAbortEvent, abortCmd);

  CountCommand deleteCmd(caster);
  caster.AddCommand(sitk::sitkDeleteEvent, deleteCmd);

  CountCommand endCmd(caster);
  caster.AddCommand(sitk::sitkEndEvent, endCmd);

  CountCommand iterCmd(caster);
  caster.AddCommand(sitk::sitkIterationEvent, iterCmd);

  CountCommand startCmd(caster);
  caster.AddCommand(sitk::sitkStartEvent, startCmd);

  CountCommand userCmd(caster);
  caster.AddCommand(sitk::sitkUserEvent, userCmd);


  sitk::Image out = caster.Execute(img);
  EXPECT_EQ ( "6ceea0011178a955b5be2d545d107199", sitk::Hash(out, sitk::HashImageFilter::MD5));

  EXPECT_EQ ( 1.0f, caster.GetProgress() );
  EXPECT_EQ ( 1.0f, progressCmd.m_Progress );
  EXPECT_EQ ( 0, abortCmd.m_Count );
  EXPECT_EQ ( 1, deleteCmd.m_Count );
  EXPECT_EQ ( 1, endCmd.m_Count );
  EXPECT_EQ ( 0, iterCmd.m_Count );
  EXPECT_EQ ( 1, startCmd.m_Count );
  EXPECT_EQ ( 0, userCmd.m_Count );

}

TEST(BasicFilters,SignedMaurerDistanceMap_Abort) {
  // test the abort functionality
  // With ITKv5 the abort functionality does not work well with many basic image filters since they no longer report
  // detailed progress. This filter is a composite filter
  namespace sitk = itk::simple;
  sitk::Image img = sitk::ReadImage( dataFinder.GetFile ( "Input/RA-Short.nrrd" ) );
  EXPECT_EQ ( "a963bd6a755b853103a2d195e01a50d3", sitk::Hash(img, sitk::HashImageFilter::MD5));

  sitk::SignedMaurerDistanceMapImageFilter stats;
  stats.SetNumberOfThreads(16);

  float abortAtProgress = 0.35f;

  AbortAtCommand abortAtCommand(stats,abortAtProgress);
  stats.AddCommand(sitk::sitkProgressEvent, abortAtCommand);

  ProgressUpdate progressCmd(stats);
  stats.AddCommand(sitk::sitkProgressEvent, progressCmd);

  CountCommand abortCmd(stats);
  stats.AddCommand(sitk::sitkAbortEvent, abortCmd);

  CountCommand deleteCmd(stats);
  stats.AddCommand(sitk::sitkDeleteEvent, deleteCmd);

  CountCommand endCmd(stats);
  stats.AddCommand(sitk::sitkEndEvent, endCmd);

  CountCommand iterCmd(stats);
  stats.AddCommand(sitk::sitkIterationEvent, iterCmd);

  CountCommand startCmd(stats);
  stats.AddCommand(sitk::sitkStartEvent, startCmd);

  CountCommand userCmd(stats);
  stats.AddCommand(sitk::sitkUserEvent, userCmd);

  EXPECT_ANY_THROW( stats.Execute(img) );

  EXPECT_EQ ( 1, abortCmd.m_Count );
  EXPECT_EQ ( 1, deleteCmd.m_Count );
  EXPECT_EQ ( 0, endCmd.m_Count );
  EXPECT_EQ ( 0, iterCmd.m_Count );
  EXPECT_EQ ( 1, startCmd.m_Count );
  EXPECT_EQ ( 0, userCmd.m_Count );
  EXPECT_LE( abortAtProgress, progressCmd.m_Progress );

}

TEST(BasicFilters,ResampleImageFilter_AdditionalProcedures)
{
  namespace sitk = itk::simple;

  sitk::Image img;
  ASSERT_NO_THROW( img = sitk::ReadImage( dataFinder.GetFile ( "Input/RA-Float.nrrd" ) ) ) << "Reading input Image.";

  sitk::Transform xf = sitk::Transform(); // identity transform

  // self reference image
   sitk::Image out = sitk::Resample( img,
                                     xf,
                                     sitk::sitkNearestNeighbor );
  EXPECT_EQ( "b187541bdcc89843d0a25a3761f344c358f3518a", sitk::Hash( out )) << " Procedural Interface 1 identity transform.";

  // additional parameter reference image
   out = sitk::Resample( img,
                         img,
                         xf,
                         sitk::sitkNearestNeighbor );
  EXPECT_EQ( "b187541bdcc89843d0a25a3761f344c358f3518a", sitk::Hash( out )) << " Procedural Interface 2 identity transform.";

  // manual specification of output domain
 out = sitk::Resample( img,
                       img.GetSize(),
                       xf,
                       sitk::sitkNearestNeighbor,
                       img.GetOrigin(),
                       img.GetSpacing(),
                       img.GetDirection() );
  EXPECT_EQ( "b187541bdcc89843d0a25a3761f344c358f3518a", sitk::Hash( out )) << " Procedural Interface 3 identity transform.";
}

TEST(BasicFilters,ResampleImageFilter_DefaultParameters)
{
  namespace sitk = itk::simple;

  sitk::Image img(10,10,sitk::sitkUInt8);
  sitk::ResampleImageFilter filter;

  sitk::Image result = filter.Execute(img);

  // Resample with default parameters returns a 0x0 image
  EXPECT_EQ ( 0u, result.GetWidth() );
  EXPECT_EQ ( 0u, result.GetHeight() );
}


TEST(BasicFilters,OtsuThreshold_CheckNamesInputCompatibility)
{
  namespace sitk = itk::simple;

  sitk::Image input(10,10,sitk::sitkFloat32);
  sitk::Image mask1(10,10,10,sitk::sitkUInt8);
  sitk::Image mask2(11,10,sitk::sitkUInt8);

  // check that if the dimension or size does not match an exception
  // is thrown.
  EXPECT_THROW( sitk::OtsuThreshold(input, mask1), sitk::GenericException );
  EXPECT_THROW( sitk::OtsuThreshold(input, mask2), sitk::GenericException );
}

TEST(BasicFilters, DICOMOrientImageFilter_Direction)
{
  namespace sitk= itk::simple;

  auto directionLPS= v9(1.0,0.0,0.0,
                        0.0,1.0,
                        0.0,0.0,0.0,1.0);
  auto directionRAS= v9(-1.0,0.0,0.0,
                        0.0,-1.0,0.0,
                        0.0,0.0,1.0);

  EXPECT_EQ(directionLPS,
            sitk::DICOMOrientImageFilter::GetDirectionCosinesFromOrientation("LPS"));
  EXPECT_EQ("LPS",  sitk::DICOMOrientImageFilter::GetOrientationFromDirectionCosines(directionLPS));

  EXPECT_EQ(v9(-1.0,0.0,0.0, 0.0,-1.0,0.0, 0.0,0.0,1.0),
            sitk::DICOMOrientImageFilter::GetDirectionCosinesFromOrientation("RAS"));
  EXPECT_EQ("RAS",sitk::DICOMOrientImageFilter::GetOrientationFromDirectionCosines(directionRAS));

}


TEST(BasicFilters, ExtractImageFilter_2D)
{
  namespace sitk = itk::simple;

  sitk::Image input( {10, 10}, sitk::sitkUInt8);
  sitk::Image output;

  sitk::ExtractImageFilter extractor;

  extractor.SetIndex({0,0});
  extractor.SetSize({10,10});
  ASSERT_NO_THROW(output = extractor.Execute(input));
  EXPECT_EQ(sitk::Hash(input), sitk::Hash(output));
  EXPECT_EQ(input.GetSize(), output.GetSize());

  extractor.SetIndex({0,0,0});
  extractor.SetSize({10,10,10});
  ASSERT_NO_THROW(output = extractor.Execute(input));
  EXPECT_EQ(sitk::Hash(input), sitk::Hash(output));
  EXPECT_VECTOR_NEAR(input.GetSize(), output.GetSize(), 1e-20);

  extractor.SetIndex({0});
  extractor.SetSize({10,10,10});
  ASSERT_ANY_THROW(output = extractor.Execute(input));

  extractor.SetIndex({0,0,0});
  extractor.SetSize({10});
  ASSERT_ANY_THROW(output = extractor.Execute(input));

  extractor.SetIndex({0,0,0});
  extractor.SetSize({0,0});
  ASSERT_ANY_THROW(output = extractor.Execute(input));

  extractor.SetIndex({0,0,0});
  extractor.SetSize({10, 0});
  ASSERT_ANY_THROW(output = extractor.Execute(input));

  extractor.SetIndex({0,0,0});
  extractor.SetSize({0, 10});
  ASSERT_ANY_THROW(output = extractor.Execute(input));

}


TEST(BasicFilters, ExtractImageFilter_3D)
{
  namespace sitk = itk::simple;

  sitk::Image input( {10, 10, 10}, sitk::sitkUInt8);
  input.SetOrigin( {1.0, 2.0, 3.0});
  sitk::Image output;

  sitk::ExtractImageFilter extractor;

  extractor.SetIndex({0,0,0});
  extractor.SetSize({10,10,10});
  ASSERT_NO_THROW(output = extractor.Execute(input));
  EXPECT_EQ(sitk::Hash(input), sitk::Hash(output));
  EXPECT_EQ(input.GetSize(), output.GetSize());
  EXPECT_VECTOR_NEAR(input.GetSize(), output.GetSize(), 1e-20);
  EXPECT_VECTOR_NEAR(input.GetOrigin(), output.GetOrigin(), 1e-20);

  extractor.SetIndex({0,0,0,0});
  extractor.SetSize({10,10,10,10});
  ASSERT_NO_THROW(output = extractor.Execute(input));
  EXPECT_EQ(sitk::Hash(input), sitk::Hash(output));
  EXPECT_VECTOR_NEAR(input.GetSize(), output.GetSize(), 1e-20);
  EXPECT_VECTOR_NEAR(input.GetOrigin(), output.GetOrigin(), 1e-20);

  extractor.SetIndex({0,0,0});
  extractor.SetSize({0,10,10});
  ASSERT_NO_THROW(output = extractor.Execute(input));
  EXPECT_VECTOR_NEAR( v2(10,10), output.GetSize(), 1e-20);
  EXPECT_VECTOR_NEAR(v2(2.0, 3.0), output.GetOrigin(), 1e-20);

  extractor.SetIndex({0,0,0});
  extractor.SetSize({0,10,10});
  ASSERT_NO_THROW(output = extractor.Execute(input));
  EXPECT_VECTOR_NEAR(v2(10,10), output.GetSize(), 1e-20);
  EXPECT_VECTOR_NEAR(v2(2.0, 3.0), output.GetOrigin(), 1e-20);

  extractor.SetIndex({0,0,0});
  extractor.SetSize({10,0,10});
  ASSERT_NO_THROW(output = extractor.Execute(input));
  EXPECT_VECTOR_NEAR(v2(10,10), output.GetSize(), 1e-20);
  EXPECT_VECTOR_NEAR(v2(1.0, 3.0), output.GetOrigin(), 1e-20);

  extractor.SetIndex({0,0,0});
  extractor.SetSize({10,10,0});
  ASSERT_NO_THROW(output = extractor.Execute(input));
  EXPECT_VECTOR_NEAR(v2(10,10), output.GetSize(), 1e-20);
  EXPECT_VECTOR_NEAR(v2(1.0, 2.0), output.GetOrigin(), 1e-20);


  extractor.SetIndex({0,0});
  extractor.SetSize({10,10,10});
  ASSERT_ANY_THROW(output = extractor.Execute(input));

  extractor.SetIndex({0,0,0});
  extractor.SetSize({10,10});
  ASSERT_ANY_THROW(output = extractor.Execute(input));

  extractor.SetIndex({0,0,0});
  extractor.SetSize({10,0,0});
  ASSERT_ANY_THROW(output = extractor.Execute(input));

  extractor.SetSize({0,10,0});
  ASSERT_ANY_THROW(output = extractor.Execute(input));

}


#if SITK_MAX_DIMENSION >= 4
TEST(BasicFilters, ExtractImageFilter_4D)
{
  namespace sitk = itk::simple;

  sitk::Image input( {10, 11, 12, 13}, sitk::sitkUInt8);
  input.SetOrigin( {1.0, 2.0, 3.0, 4.0});
  sitk::Image output;

  sitk::ExtractImageFilter extractor;

  extractor.SetIndex({0,0,0,0});
  extractor.SetSize({10,11,12,13});
  ASSERT_NO_THROW(output = extractor.Execute(input));
  EXPECT_EQ(sitk::Hash(input), sitk::Hash(output));
  EXPECT_EQ(input.GetSize(), output.GetSize());
  EXPECT_VECTOR_NEAR(input.GetSize(), output.GetSize(), 1e-20);
  EXPECT_VECTOR_NEAR(input.GetOrigin(), output.GetOrigin(), 1e-20);

  extractor.SetIndex({0,0,0,0});
  extractor.SetSize({0,11,12,13});
  ASSERT_NO_THROW(output = extractor.Execute(input));
  EXPECT_VECTOR_NEAR(v3(11,12,13), output.GetSize(), 1e-20);
  EXPECT_VECTOR_NEAR(v3(2,3,4), output.GetOrigin(), 1e-20);

  extractor.SetIndex({0,0,0,0});
  extractor.SetSize({0,11,12,0});
  ASSERT_NO_THROW(output = extractor.Execute(input));
  EXPECT_VECTOR_NEAR(v2(11,12), output.GetSize(), 1e-20);
  EXPECT_VECTOR_NEAR(v2(2,3), output.GetOrigin(), 1e-20);

  extractor.SetIndex({0,0,0,0});
  extractor.SetSize({10,0,0,13});
  ASSERT_NO_THROW(output = extractor.Execute(input));
  EXPECT_VECTOR_NEAR(v2(10,13), output.GetSize(), 1e-20);
  EXPECT_VECTOR_NEAR(v2(1,4), output.GetOrigin(), 1e-20);


  extractor.SetIndex({0,0,0});
  extractor.SetSize({10,11,12,13});
  ASSERT_ANY_THROW(output = extractor.Execute(input));

  extractor.SetIndex({0,0,0,0});
  extractor.SetSize({10,11,12});
  ASSERT_ANY_THROW(output = extractor.Execute(input));

  extractor.SetIndex({0,0,0,0});
  extractor.SetSize({0, 0, 0, 13});
  ASSERT_ANY_THROW(output = extractor.Execute(input));

  extractor.SetIndex({0,0,0,0});
  extractor.SetSize({0, 0, 12, 0});
  ASSERT_ANY_THROW(output = extractor.Execute(input));

  extractor.SetIndex({0,0,0,0});
  extractor.SetSize({0, 11, 0, 0});
  ASSERT_ANY_THROW(output = extractor.Execute(input));

  extractor.SetIndex({0,0,0,0});
  extractor.SetSize({10, 0, 0, 0});
  ASSERT_ANY_THROW(output = extractor.Execute(input));

}
#endif

#if SITK_MAX_DIMENSION >= 5
TEST(BasicFilters, ExtractImageFilter_5D)
{
  namespace sitk = itk::simple;

  sitk::Image input( {10, 11, 12, 13, 14}, sitk::sitkUInt8);
  input.SetOrigin( {1.0, 2.0, 3.0, 4.0, 5.0});
  sitk::Image output;

  sitk::ExtractImageFilter extractor;

  extractor.SetIndex({0,0,0,0,0});
  extractor.SetSize({10,11,12,13,14});
  ASSERT_NO_THROW(output = extractor.Execute(input));
  EXPECT_EQ(sitk::Hash(input), sitk::Hash(output));
  EXPECT_EQ(input.GetSize(), output.GetSize());
  EXPECT_VECTOR_NEAR(input.GetSize(), output.GetSize(), 1e-20);
  EXPECT_VECTOR_NEAR(input.GetOrigin(), output.GetOrigin(), 1e-20);

  extractor.SetIndex({0,0,0,0,0});
  extractor.SetSize({0,11,12,13,14});
  ASSERT_NO_THROW(output = extractor.Execute(input));
  EXPECT_VECTOR_NEAR(v4(11,12,13,14), output.GetSize(), 1e-20);
  EXPECT_VECTOR_NEAR(v4(2,3,4,5), output.GetOrigin(), 1e-20);

  extractor.SetIndex({0,0,0,0,0});
  extractor.SetSize({0,11,12,0,14});
  ASSERT_NO_THROW(output = extractor.Execute(input));
  EXPECT_VECTOR_NEAR(v3(11,12,14), output.GetSize(), 1e-20);
  EXPECT_VECTOR_NEAR(v3(2,3,5), output.GetOrigin(), 1e-20);

  extractor.SetIndex({0,0,0,0,0});
  extractor.SetSize({10,0,0,13,14});
  ASSERT_NO_THROW(output = extractor.Execute(input));
  EXPECT_VECTOR_NEAR(v3(10,13,14), output.GetSize(), 1e-20);
  EXPECT_VECTOR_NEAR(v3(1,4,5), output.GetOrigin(), 1e-20);

  extractor.SetIndex({0,0,0,0,0});
  extractor.SetSize({0,0,12,0,14});
  ASSERT_NO_THROW(output = extractor.Execute(input));
  EXPECT_VECTOR_NEAR(v2(12,14), output.GetSize(), 1e-20);
  EXPECT_VECTOR_NEAR(v2(3,5), output.GetOrigin(), 1e-20);

  extractor.SetIndex({0,0,0,0,0});
  extractor.SetSize({10,0,0,13,0});
  ASSERT_NO_THROW(output = extractor.Execute(input));
  EXPECT_VECTOR_NEAR(v2(10,13), output.GetSize(), 1e-20);
  EXPECT_VECTOR_NEAR(v2(1,4), output.GetOrigin(), 1e-20);

  extractor.SetIndex({0,0,0,0});
  extractor.SetSize({10,11,12,13,14});
  ASSERT_ANY_THROW(output = extractor.Execute(input));

  extractor.SetIndex({0,0,0,0,0});
  extractor.SetSize({10,11,12,13});
  ASSERT_ANY_THROW(output = extractor.Execute(input));

  extractor.SetIndex({0,0,0,0,0});
  extractor.SetSize({0, 0, 0, 0, 14});
  ASSERT_ANY_THROW(output = extractor.Execute(input));

  extractor.SetIndex({0,0,0,0,0});
  extractor.SetSize({0, 0, 12, 0, 0});
  ASSERT_ANY_THROW(output = extractor.Execute(input));

  extractor.SetIndex({0,0,0,0,0});
  extractor.SetSize({0, 11, 0, 0,0});
  ASSERT_ANY_THROW(output = extractor.Execute(input));

  extractor.SetIndex({0,0,0,0,0});
  extractor.SetSize({10, 0, 0, 0,0});
  ASSERT_ANY_THROW(output = extractor.Execute(input));

}
#endif


TEST(BasicFilters, PasteImageFilter_2D)
{
  constexpr uint16_t value = 17;

  namespace sitk = itk::simple;
  sitk::Image img = sitk::Image({32,32}, sitk::sitkUInt16);
  sitk::Image simg = sitk::Image({5,5}, sitk::sitkUInt16);
  simg.SetPixelAsUInt16({1,2}, value);

  sitk::Image output;

  sitk::PasteImageFilter paster;

  paster.SetDestinationIndex({11,13});
  paster.SetSourceSize(simg.GetSize());
  output = paster.Execute(img, simg);
  EXPECT_EQ(value, output.GetPixelAsUInt16({12, 15}));
  EXPECT_EQ(0, output.GetPixelAsUInt16({1, 2}));

}

TEST(BasicFilters, PasteImageFilter_Constant)
{
  constexpr int32_t c = 4321;

  namespace sitk = itk::simple;
  sitk::Image img = sitk::Image({32,32}, sitk::sitkInt32);

  sitk::PasteImageFilter paster;

  paster.SetDestinationIndex({11,13});
  paster.SetSourceSize( {5,7});
  sitk::Image  output = paster.Execute(img, c);
  EXPECT_EQ(0, output.GetPixelAsInt32({10, 13}));
  EXPECT_EQ(0, output.GetPixelAsInt32({11, 12}));

  EXPECT_EQ(c, output.GetPixelAsInt32({11, 13}));
  EXPECT_EQ(c, output.GetPixelAsInt32({15, 13}));
  EXPECT_EQ(c, output.GetPixelAsInt32({11, 19}));

  EXPECT_EQ(c, output.GetPixelAsInt32({15, 19}));

}


TEST(BasicFilters, PasteImageFilter_3D_2D)
{
  constexpr uint16_t value = 17;

  namespace sitk = itk::simple;
  sitk::Image img = sitk::Image({32,32,32}, sitk::sitkUInt16);
  sitk::Image simg = sitk::Image({5,5}, sitk::sitkUInt16);
  simg.SetPixelAsUInt16({1,2}, value);

  sitk::Image output;

  sitk::PasteImageFilter paster;

  paster.SetDestinationIndex({11,13, 15});
  paster.SetSourceSize(simg.GetSize());
  output = paster.Execute(img, simg);
  EXPECT_EQ(value, output.GetPixelAsUInt16({12, 15, 15}));
  EXPECT_EQ(0, output.GetPixelAsUInt16({1, 2, 15}));

  paster.SetDestinationIndex({11,13,15});
  paster.SetDestinationSkipAxes({true, false, false});
  paster.SetSourceSize(simg.GetSize());
  output = paster.Execute(img, simg);
  EXPECT_EQ(0, output.GetPixelAsUInt16({12, 15, 15}));
  EXPECT_EQ(value, output.GetPixelAsUInt16({11, 14, 17}));

  paster.SetDestinationIndex({11,13,15});
  paster.SetDestinationSkipAxes({false, true, false});
  paster.SetSourceSize(simg.GetSize());
  output = paster.Execute(img, simg);
  EXPECT_EQ(0, output.GetPixelAsUInt16({12, 15, 15}));
  EXPECT_EQ(value, output.GetPixelAsUInt16({12, 13, 17}));

}

TEST(BasicFilters, N4BiasFieldCorrectionImageFilter_GetLogBiasField)
{
  namespace sitk = itk::simple;
  sitk::Image img(100,100, sitk::sitkFloat32);

  sitk::N4BiasFieldCorrectionImageFilter n4;

  // test before execution
  EXPECT_ANY_THROW(n4.GetLogBiasFieldAsImage(img));

  n4.Execute(img);

  n4.GetLogBiasFieldAsImage(img);

  n4.GetLogBiasFieldAsImage(sitk::Image(15,15, sitk::sitkUInt8));
  sitk::Image reference(200, 200, sitk::sitkLabelUInt8);
  reference.SetOrigin( { 1.1, 2.2 } );
  reference.SetSpacing( { 0.5, 0.4 } );
  sitk::Image logBiasField = n4.GetLogBiasFieldAsImage(reference);


  EXPECT_EQ( reference.GetSize(), logBiasField.GetSize() );
  EXPECT_VECTOR_DOUBLE_NEAR( reference.GetOrigin(), logBiasField.GetOrigin(), 1e-8 );
  EXPECT_VECTOR_DOUBLE_NEAR( reference.GetSpacing(), logBiasField.GetSpacing(), 1e-8 );
  EXPECT_VECTOR_DOUBLE_NEAR( reference.GetDirection(), logBiasField.GetDirection(), 1e-8 );

}
