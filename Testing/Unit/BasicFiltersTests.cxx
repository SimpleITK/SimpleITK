#include <SimpleITKTestHarness.h>

#include <sitkImage.h>
#include <sitkImageFileReader.h>
#include <sitkImageFileWriter.h>
#include <sitkHashImageFilter.h>
#include <sitkRecursiveGaussianImageFilter.h>
#include <sitkCastImageFilter.h>
#include <sitkPixelIDValues.h>


#include "itkRecursiveGaussianImageFilter.h"


TEST(BasicFilters,RecursiveGaussian_ENUMCHECK) {

  typedef itk::RecursiveGaussianImageFilter< itk::Image<float,3> > ITKRecursiveGausianType;
  EXPECT_EQ( (int)ITKRecursiveGausianType::ZeroOrder, (int)itk::simple::RecursiveGaussianImageFilter::ZeroOrder );
  EXPECT_EQ( (int)ITKRecursiveGausianType::FirstOrder, (int)itk::simple::RecursiveGaussianImageFilter::FirstOrder );
  EXPECT_EQ( (int)ITKRecursiveGausianType::SecondOrder, (int)itk::simple::RecursiveGaussianImageFilter::SecondOrder );
}

TEST(BasicFilters,Cast) {
  itk::simple::HashImageFilter hasher;
  itk::simple::ImageFileReader reader;

  reader.SetFileName ( dataFinder.GetFile ( "Input/RA-Float.nrrd" ) );
  itk::simple::Image image = reader.Execute();
  ASSERT_TRUE ( image.GetImageBase() != NULL );
  hasher.SetHashFunction ( itk::simple::HashImageFilter::MD5 );
  EXPECT_EQ ( "3ccccde44efaa3d688a86e94335c1f16", hasher.Execute ( image ) );

  EXPECT_EQ ( image.GetPixelIDValue(), itk::simple::sitkFloat32 );
  EXPECT_EQ ( image.GetPixelIDTypeAsString(), "32-bit float" );

  typedef std::map<std::string,itk::simple::PixelIDValueType> MapType;
  MapType mapping;
  mapping["2f27e9260baeba84fb83dd35de23fa2d"] = (itk::simple::PixelIDValueType)itk::simple::sitkUInt8;
  mapping["2f27e9260baeba84fb83dd35de23fa2d"] = (itk::simple::PixelIDValueType)itk::simple::sitkInt8;
  mapping["a963bd6a755b853103a2d195e01a50d3"] = (itk::simple::PixelIDValueType)itk::simple::sitkUInt16;
  mapping["a963bd6a755b853103a2d195e01a50d3"] = (itk::simple::PixelIDValueType)itk::simple::sitkInt16;
  mapping["6ceea0011178a955b5be2d545d107199"] = (itk::simple::PixelIDValueType)itk::simple::sitkUInt32;
  mapping["6ceea0011178a955b5be2d545d107199"] = (itk::simple::PixelIDValueType)itk::simple::sitkInt32;
  mapping["efa4c3b27349b97b02a64f3d2b5ca9ed"] = (itk::simple::PixelIDValueType)itk::simple::sitkUInt64;
  mapping["sitkInt64"] = (itk::simple::PixelIDValueType)itk::simple::sitkInt64;
  mapping["3ccccde44efaa3d688a86e94335c1f16"] = (itk::simple::PixelIDValueType)itk::simple::sitkFloat32;
  mapping["ac0228acc17038fd1f1ed28eb2841c73"] = (itk::simple::PixelIDValueType)itk::simple::sitkFloat64;
  mapping["226dabda8fc07f20e2b9e44ca1c83955"] = (itk::simple::PixelIDValueType)itk::simple::sitkComplexFloat32;
  mapping["e92cbb187a92610068d7de0cb23364db"] = (itk::simple::PixelIDValueType)itk::simple::sitkComplexFloat64;
  mapping["2f27e9260baeba84fb83dd35de23fa2d"] = (itk::simple::PixelIDValueType)itk::simple::sitkVectorUInt8;
  mapping["2f27e9260baeba84fb83dd35de23fa2d"] = (itk::simple::PixelIDValueType)itk::simple::sitkVectorInt8;
  mapping["a963bd6a755b853103a2d195e01a50d3"] = (itk::simple::PixelIDValueType)itk::simple::sitkVectorUInt16;
  mapping["a963bd6a755b853103a2d195e01a50d3"] = (itk::simple::PixelIDValueType)itk::simple::sitkVectorInt16;
  mapping["sitkVectorUInt32"] = (itk::simple::PixelIDValueType)itk::simple::sitkVectorUInt32;
  mapping["sitkVectorInt32"] = (itk::simple::PixelIDValueType)itk::simple::sitkVectorInt32;
  mapping["sitkVectorUInt64"] = (itk::simple::PixelIDValueType)itk::simple::sitkVectorUInt64;
  mapping["sitkVectorInt64"] = (itk::simple::PixelIDValueType)itk::simple::sitkVectorInt64;
  mapping["3ccccde44efaa3d688a86e94335c1f16"] = (itk::simple::PixelIDValueType)itk::simple::sitkVectorFloat32;
  mapping["ac0228acc17038fd1f1ed28eb2841c73"] = (itk::simple::PixelIDValueType)itk::simple::sitkVectorFloat64;
  mapping["sitkLabelUInt8"] = (itk::simple::PixelIDValueType)itk::simple::sitkLabelUInt8;
  mapping["sitkLabelUInt16"] = (itk::simple::PixelIDValueType)itk::simple::sitkLabelUInt16;
  mapping["sitkLabelUInt32"] = (itk::simple::PixelIDValueType)itk::simple::sitkLabelUInt32;
  mapping["sitkLabelUInt64"] = (itk::simple::PixelIDValueType)itk::simple::sitkLabelUInt64;

  bool failed = false;

  // Loop over the map, load each file, and compare the hash value
  for ( MapType::iterator it = mapping.begin(); it != mapping.end(); ++it )
    {
    itk::simple::PixelIDValueType pixelID = it->second;
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
  EXPECT_NE ( "", hasher.ToString() );
  EXPECT_EQ ( itk::simple::HashImageFilter::SHA1, hasher.SetHashFunction ( itk::simple::HashImageFilter::SHA1 ).GetHashFunction() );
  EXPECT_EQ ( itk::simple::HashImageFilter::MD5, hasher.SetHashFunction ( itk::simple::HashImageFilter::MD5 ).GetHashFunction() );
}
