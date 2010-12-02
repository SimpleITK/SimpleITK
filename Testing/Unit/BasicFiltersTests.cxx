#include <SimpleITK.h>
#include <SimpleITKTestHarness.h>
#include <ImageCompare.h>

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
