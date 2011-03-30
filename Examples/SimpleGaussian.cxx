
#include <SimpleITK.h>

int main ( int argc, char* argv[] ) {

  if ( argc < 4 ) {
    std::cerr << "Usage: " << argv[0] << " <input> <sigma> <output>\n";
    return 1;
  }

  itk::simple::ImageFileReader reader;
  reader.SetFileName ( std::string ( argv[1] ) );
  itk::simple::Image image = reader.Execute();

#if 0
  itk::simple::RecursiveGaussianImageFilter gaussian;
  gaussian.SetSigma ( atof ( argv[2] ) );
  itk::simple::Image blurredImage = gaussian.Execute ( image );

  itk::simple::ImageFileWriter writer;
  writer.SetFileName ( std::string ( argv[3] ) );
  writer.Execute ( blurredImage );
#endif
  return 0;
}
