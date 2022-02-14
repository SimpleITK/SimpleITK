// This one header will include all SimpleITK filters and external
// objects.
#include <SimpleITK.h>
#include <iostream>
#include <stdlib.h>

namespace sitk = itk::simple;

int main ( int argc, char* argv[] ) {

  if ( argc < 4 ) {
    std::cerr << "Usage: " << argv[0] << " <fixedImage> <movingImage> <parameterFile> <outputImage>\n";
    return 1;
  }

  // Instantiate SimpleElastix
  sitk::ElastixImageFilter elastixImageFilter;

  // Read input
  sitk::ImageFileReader reader;
  reader.SetFileName( std::string( argv[1] ) );
  elastixImageFilter.SetFixedImage( reader.Execute() );
  reader.SetFileName( std::string( argv[2] ) );
  elastixImageFilter.SetMovingImage( reader.Execute() );
  elastixImageFilter.SetParameterMap( sitk::ReadParameterFile( std::string( argv[3] ) ) );
  elastixImageFilter.LogToConsoleOn();

  // Run registration
  elastixImageFilter.Execute();

  // Write result image
  sitk::ImageFileWriter writer;
  writer.SetFileName( std::string( argv[4] ) );
  writer.Execute( elastixImageFilter.GetResultImage() );

  return 0;
}
