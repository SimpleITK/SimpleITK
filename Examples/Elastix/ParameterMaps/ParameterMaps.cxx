#include "SimpleITK.h"
#include <iostream>
#include <string>

namespace sitk = itk::simple;

int
main(int argc, char * argv[])
{
  if (argc < 3)
  {
    std::cerr << "Usage: " << argv[0] << " <fixedImage> <movingImage> [outputPrefix]" << std::endl;
    return 1;
  }

  // Read input images
  sitk::Image fixedImage = sitk::ReadImage(argv[1]);
  sitk::Image movingImage = sitk::ReadImage(argv[2]);

  std::cout << "SimpleITK Elastix Parameter Maps Example" << std::endl;
  std::cout << std::string(60, '=') << std::endl;

  // START_DEFAULT_PARAMETER_MAP
  //  Get a default parameter map for a common registration type
  sitk::ElastixImageFilter::ParameterMapType parameterMap = sitk::GetDefaultParameterMap("translation");

  // Print parameter map to see its contents
  sitk::PrintParameterMap(parameterMap);
  // END_DEFAULT_PARAMETER_MAP

  // START_MODIFY_PARAMETER_MAP
  //  Modify parameter map entries (values are vectors of strings)
  parameterMap["Transform"] = sitk::ElastixImageFilter::ParameterValueVectorType(1, "AffineTransform");
  parameterMap["MaximumNumberOfIterations"] = sitk::ElastixImageFilter::ParameterValueVectorType(1, "512");
  parameterMap["NumberOfSpatialSamples"] = sitk::ElastixImageFilter::ParameterValueVectorType(1, "8192");
  // END_MODIFY_PARAMETER_MAP

  // START_MULTI_STAGE_REGISTRATION
  //  Multi-stage registration: translation -> affine -> bspline
  sitk::ElastixImageFilter elastixImageFilter;
  elastixImageFilter.SetFixedImage(fixedImage);
  elastixImageFilter.SetMovingImage(movingImage);

  elastixImageFilter.SetParameterMap(sitk::GetDefaultParameterMap("translation"));
  elastixImageFilter.AddParameterMap(sitk::GetDefaultParameterMap("affine"));

  sitk::ElastixImageFilter::ParameterMapType bsplineMap = sitk::GetDefaultParameterMap("bspline");
  bsplineMap["FinalGridSpacingInPhysicalUnits"] = sitk::ElastixImageFilter::ParameterValueVectorType(1, "8.0");
  elastixImageFilter.AddParameterMap(bsplineMap);

  elastixImageFilter.LogToConsoleOff();
  sitk::Image resultImage = elastixImageFilter.Execute();

  // Retrieve transform parameter maps from the result
  sitk::ElastixImageFilter::ParameterMapVectorType transformParameterMaps =
    elastixImageFilter.GetTransformParameterMaps();
  // END_MULTI_STAGE_REGISTRATION

  // START_READ_WRITE_PARAMETER_MAP
  //  Write a parameter map to a file
  sitk::WriteParameterFile(parameterMap, "parameters.txt");

  // Read a parameter map from a file
  sitk::ElastixImageFilter::ParameterMapType readMap = sitk::ReadParameterFile("parameters.txt");
  // END_READ_WRITE_PARAMETER_MAP

  // Write results if output prefix provided
  if (argc > 3)
  {
    std::string outputPrefix = argv[3];
    for (size_t i = 0; i < transformParameterMaps.size(); ++i)
    {
      std::string filename = outputPrefix + "_TransformParameters_" + std::to_string(i) + ".txt";
      sitk::WriteParameterFile(transformParameterMaps[i], filename);
    }
    sitk::WriteImage(resultImage, outputPrefix + ".nii");
  }

  return 0;
}
