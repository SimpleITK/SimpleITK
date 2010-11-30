#include <SimpleITK.h>
#include <SimpleITKTestHarness.h>
#include <ImageCompare.h>

TEST(BasicFilters,RecursiveGaussian) {
  itk::simple::ImageHashFilter hasher;
  itk::simple::ImageFileReader reader;
  itk::simple::RecursiveGaussianImageFilter filter;
  itk::simple::Image::Pointer image;

  reader.SetFilename ( dataFinder.GetFile ( "Input/HeadMRVolumeWithDirection.nhdr" ) );
  image = reader.Execute();
  ASSERT_TRUE ( image->GetImageBase().IsNotNull() );
  image = filter.Execute ( image );
  IMAGECOMPAREWITHTOLERANCE ( image, "HeadMRVolumeWithDirection", 0.1 );
}
