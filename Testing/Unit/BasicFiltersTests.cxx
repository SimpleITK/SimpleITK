#include <SimpleITKTestHarness.h>

#include <sitkImage.h>
#include <sitkImageFileReader.h>
#include <sitkImageFileWriter.h>
#include <sitkImageHashFilter.h>
#include <sitkRecursiveGaussianImageFilter.h>
#include <sitkCastImageFilter.h>
#include <sitkPixelIDValues.h>

TEST(BasicFilters,RecursiveGaussian) {
  itk::simple::ImageHashFilter hasher;
  itk::simple::ImageFileReader reader;
  itk::simple::RecursiveGaussianImageFilter filter;
  itk::simple::Image::Pointer image;

  reader.SetFilename ( dataFinder.GetFile ( "Input/RA-Float.nrrd" ) );
  image = reader.Execute();
  ASSERT_TRUE ( image->GetImageBase().IsNotNull() );
  image = filter.Execute ( image );
  IMAGECOMPAREWITHTOLERANCE ( image, "default", 0.1 );
}


TEST(BasicFilters,Cast) {
  itk::simple::ImageHashFilter hasher;
  itk::simple::ImageFileReader reader;
  itk::simple::RecursiveGaussianImageFilter filter;
  itk::simple::Image::Pointer image;

  reader.SetFilename ( dataFinder.GetFile ( "Input/RA-Float.nrrd" ) );
  image = reader.Execute();
  ASSERT_TRUE ( image->GetImageBase().IsNotNull() );
  hasher.SetHashFunction ( itk::simple::ImageHashFilter::MD5 );
  EXPECT_EQ ( "3ccccde44efaa3d688a86e94335c1f16", hasher.Execute ( image ) );

  EXPECT_EQ ( image->GetPixelIDValue(), itk::simple::sitkFloat32 );
  EXPECT_EQ ( image->GetPixelIDTypeAsString(), "32-bit float" );

  typedef std::map<std::string,itk::simple::PixelIDValueType> MapType;
  MapType mapping;
  mapping["2f27e9260baeba84fb83dd35de23fa2d"] = (itk::simple::PixelIDValueType)itk::simple::sitkUInt8;
  mapping["sitkInt8"] = (itk::simple::PixelIDValueType)itk::simple::sitkInt8;
  mapping["a963bd6a755b853103a2d195e01a50d3"] = (itk::simple::PixelIDValueType)itk::simple::sitkUInt16;
  mapping["a963bd6a755b853103a2d195e01a50d3"] = (itk::simple::PixelIDValueType)itk::simple::sitkInt16;
  mapping["6ceea0011178a955b5be2d545d107199"] = (itk::simple::PixelIDValueType)itk::simple::sitkUInt32;
  mapping["6ceea0011178a955b5be2d545d107199"] = (itk::simple::PixelIDValueType)itk::simple::sitkInt32;
  mapping["efa4c3b27349b97b02a64f3d2b5ca9ed"] = (itk::simple::PixelIDValueType)itk::simple::sitkUInt64;
  mapping["sitkInt64"] = (itk::simple::PixelIDValueType)itk::simple::sitkInt64;
  mapping["3ccccde44efaa3d688a86e94335c1f16"] = (itk::simple::PixelIDValueType)itk::simple::sitkFloat32;
  mapping["ac0228acc17038fd1f1ed28eb2841c73"] = (itk::simple::PixelIDValueType)itk::simple::sitkFloat64;
  mapping["sitkComplexFloat32"] = (itk::simple::PixelIDValueType)itk::simple::sitkComplexFloat32;
  mapping["sitkComplexFloat64"] = (itk::simple::PixelIDValueType)itk::simple::sitkComplexFloat64;
  mapping["sitkVectorUInt8"] = (itk::simple::PixelIDValueType)itk::simple::sitkVectorUInt8;
  mapping["sitkVectorInt8"] = (itk::simple::PixelIDValueType)itk::simple::sitkVectorInt8;
  mapping["sitkVectorUInt16"] = (itk::simple::PixelIDValueType)itk::simple::sitkVectorUInt16;
  mapping["sitkVectorInt16"] = (itk::simple::PixelIDValueType)itk::simple::sitkVectorInt16;
  mapping["sitkVectorUInt32"] = (itk::simple::PixelIDValueType)itk::simple::sitkVectorUInt32;
  mapping["sitkVectorInt32"] = (itk::simple::PixelIDValueType)itk::simple::sitkVectorInt32;
  mapping["sitkVectorUInt64"] = (itk::simple::PixelIDValueType)itk::simple::sitkVectorUInt64;
  mapping["sitkVectorInt64"] = (itk::simple::PixelIDValueType)itk::simple::sitkVectorInt64;
  mapping["sitkVectorFloat32"] = (itk::simple::PixelIDValueType)itk::simple::sitkVectorFloat32;
  mapping["sitkVectorFloat64"] = (itk::simple::PixelIDValueType)itk::simple::sitkVectorFloat64;
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
    itk::simple::Image::Pointer test;

    if ( pixelID == itk::simple::sitkUnknown )
      {
      failed = true;
      std::cerr << "Enum type: " << pixelID << " (" << hash << ") is unknown" << std::endl;
      continue;
      }
    
    std::cout << "Trying to cast pixelID: " << pixelID << " (" << hash << ") to " << itk::simple::GetPixelIDValueAsString ( pixelID ) << std::endl;
    try
      {
      itk::simple::CastImageFilter caster;
      std::cout << "Doing the cast" << std::endl;
      test = caster.SetOutputPixelType ( pixelID ).Execute ( image );
      std::cout << "Done with the cast" << std::endl;
      }
    catch ( ::itk::simple::GenericException &e )
      {
      failed = true;
      std::cerr << "Failed to cast" << std::endl;
      }
    catch ( ... )
      {
      failed = true;
      std::cerr << "Failed to cast (generic exception)" << std::endl;
      }
    if ( test.IsNotNull() )
      {
      try
        {
        hasher.SetHashFunction ( itk::simple::ImageHashFilter::MD5 );
        EXPECT_EQ ( hash, hasher.Execute ( test ) ) << "Cast to " << itk::simple::GetPixelIDValueAsString ( pixelID );
        }
      catch ( ... )
        {
        std::cerr << "Could not hash the image" << std::endl;
        failed = true;
        }
      }
  }
  EXPECT_FALSE ( failed ) << "Cast failed, or could not take the hash of the imoge";

}

TEST(BasicFilters,ImageHashFilter) {
  itk::simple::ImageHashFilter hasher;
  EXPECT_NE ( "", hasher.ToString() );
  EXPECT_EQ ( itk::simple::ImageHashFilter::SHA1, hasher.SetHashFunction ( itk::simple::ImageHashFilter::SHA1 ).GetHashFunction() );
  EXPECT_EQ ( itk::simple::ImageHashFilter::MD5, hasher.SetHashFunction ( itk::simple::ImageHashFilter::MD5 ).GetHashFunction() );
}
