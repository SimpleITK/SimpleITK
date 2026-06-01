// This one header will include all SimpleITK filters and external
// objects.
#include <SimpleITK.h>
#include <iostream>
#include <stdlib.h>

namespace sitk = itk::simple;

int
main(int argc, char * argv[])
{

  if (argc < 3)
  {
    std::cerr << "Usage: " << argv[0] << " <inputImage> <parameterFile> <outputImage>\n";
    return 1;
  }

  // Instantiate transformix
  sitk::TransformixImageFilter transformixImageFilter;
  transformixImageFilter.LogToConsoleOn();

  // Read input
  sitk::ImageFileReader reader;
  reader.SetFileName(std::string(argv[1]));
  transformixImageFilter.SetMovingImage(reader.Execute());
  transformixImageFilter.SetTransformParameterMap(sitk::ReadParameterFile(argv[2]));

  // Run warp
  transformixImageFilter.Execute();

  // Write result image
  sitk::ImageFileWriter writer;
  writer.SetFileName(std::string(argv[3]));
  writer.Execute(transformixImageFilter.GetResultImage());

  return 0;
}
