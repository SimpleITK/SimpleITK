

#include <simpleImage.h>
#include <simpleGaussian.h>
#include <simpleImageFileReader.h>
#include <simpleImageFileWriter.h>


int main ( int argc, char* argv[] ) {

  if ( argc < 4 ) {
    std::cerr << "Usage: " << argv[0] << " <input> <sigma> <output>\n";
    return 1;
  }

  itk::simple::Image::Pointer image;

  itk::simple::ImageFileReader reader;
  reader.setFilename ( std::string ( argv[1] ) );
  image = reader.execute();
  
  std::cout << image->toString() << "\n";

  itk::simple::Gaussian gaussian;
  gaussian.setSigma ( atof ( argv[2] ) );
  image = gaussian.execute ( image );

  std::cout << image->toString() << "\n";

  itk::simple::ImageFileWriter writer;
  writer.setFilename ( std::string ( argv[3] ) );
  writer.execute ( image );

  return 0;
}
