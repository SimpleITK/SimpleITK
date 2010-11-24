
#include <SimpleITK.h>

int main ( int argc, char* argv[] ) {

  if ( argc < 4 ) {
    std::cerr << "Usage: " << argv[0] << " <input1> <input2> <output>\n";
    return 1;
  }

  itk::simple::Image::Pointer image1;
  itk::simple::Image::Pointer image2;
  itk::simple::Image::Pointer image3;

  itk::simple::ImageFileReader reader1;
  reader1.SetFilename ( std::string ( argv[1] ) );
  image1 = reader1.Execute();

  itk::simple::ImageFileReader reader2;
  reader2.SetFilename ( std::string ( argv[2] ) );
  image2 = reader1.Execute();

  std::cout << image1->ToString() << "\n";
  std::cout << image2->ToString() << "\n";

  itk::simple::AddImageFilter adder;
  image3 = adder.Execute ( image1, image2 );

  std::cout << image3->ToString() << "\n";

  itk::simple::ImageFileWriter writer;
  writer.SetFilename ( std::string ( argv[3] ) );
  writer.Execute ( image3 );

  return 0;
}
