
#include <SimpleITK.h>
#include <sitkBinaryThresholdImageFilter.h>

int main ( int argc, char* argv[] ) {

  if ( argc < 5 ) {
    std::cerr << "Usage: " << argv[0] << " <input> <lowerthreshold> <upperthreshold> <output>\n";
    return 1;
  }

  itk::simple::Image::Pointer image;

  itk::simple::ImageFileReader reader;
  reader.SetFilename ( std::string ( argv[1] ) );
  image = reader.Execute();

  std::cout << image->ToString() << "\n";

  itk::simple::BinaryThresholdImageFilter thresholder;
  thresholder.SetLowerThreshold ( atof ( argv[2] ) );
  thresholder.SetUpperThreshold ( atof ( argv[3] ) );
  image = thresholder.Execute ( image );

  std::cout << image->ToString() << "\n";

  itk::simple::ImageFileWriter writer;
  writer.SetFilename ( std::string ( argv[4] ) );
  writer.Execute ( image );

  return 0;
}
