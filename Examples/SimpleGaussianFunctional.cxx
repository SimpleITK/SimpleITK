
// This one header will include all SimpleITK filters and external
// objects.
#include <SimpleITK.h>

// create convenient namespace alias
namespace sitk = itk::simple;


int main ( int argc, char* argv[] ) {

  if ( argc < 4 ) {
    std::cerr << "Usage: " << argv[0] << " <input> <sigma> <output>\n";
    return 1;
  }


  sitk::Image image = sitk::ReadImage ( std::string ( argv[1] ) );

  sitk::PixelIDValueType inputPixelID = image.GetPixelIDValue();

  image = sitk::SmoothingRecursiveGaussian ( image, atof ( argv[2] ) );

  image = sitk::Cast( image, inputPixelID );

  sitk::WriteImage ( image, std::string ( argv[3] ) );

  return 0;
}
