
#include <SimpleITK.h>

int main ( int argc, char* argv[] ) {

  if ( argc < 4 ) {
    std::cerr << "Usage: " << argv[0] << " <input> <sigma> <output>\n";
    return 1;
  }

  itk::simple::Image::Pointer image;

  image = itk::simple::ReadImage ( std::string ( argv[1] ) );
  image = itk::simple::RecursiveGaussian ( image, 
                                         atof ( argv[2] ),
                                         false,
                                         itk::simple::RecursiveGaussianImageFilter::ZeroOrder,
                                         0 );
  itk::simple::WriteImage ( image, std::string ( argv[3] ) );

  return 0;
}
