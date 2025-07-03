/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

/**
 * A SimpleITK example demonstrating how to convert and resize DICOM files
 * to common image types.
 */

#include <SimpleITK.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

namespace sitk = itk::simple;
namespace fs = std::filesystem;

bool
ConvertImage(const std::string & inputFile, const std::string & outputFile, unsigned int newWidth = 0)
{
  try
  {
    sitk::ImageFileReader reader;
    // Only read DICOM images
    reader.SetImageIO("GDCMImageIO");
    reader.SetFileName(inputFile);
    auto image = reader.Execute();
    auto imageSize = image.GetSize();
    // If 3D image with single slice, treat as 2D
    if (imageSize.size() == 3 && imageSize[2] == 1)
    {
      sitk::ExtractImageFilter extractFilter;
      extractFilter.SetIndex({ 0, 0, 0 });
      imageSize[2] = 0;
      extractFilter.SetSize(imageSize);
      image = extractFilter.Execute(image);
    }
    // Resample if new width is specified
    if (newWidth > 0)
    {
      auto         originalSize = image.GetSize();
      auto         originalSpacing = image.GetSpacing();
      double       newSpacing = ((originalSize[0] - 1) * originalSpacing[0]) / (newWidth - 1);
      unsigned int newHeight = static_cast<unsigned int>(((originalSize[1] - 1) * originalSpacing[1]) / newSpacing);
      image = sitk::Resample(image,
                             { newWidth, newHeight },
                             sitk::Transform(),
                             sitk::sitkLinear,
                             image.GetOrigin(),
                             { newSpacing, newSpacing },
                             image.GetDirection(),
                             0,
                             image.GetPixelID());
    }
    // If a single channel image, rescale to [0,255] and cast to UInt8.
    if (image.GetNumberOfComponentsPerPixel() == 1)
    {
      image = sitk::RescaleIntensity(image, 0, 255);
      image = sitk::Cast(image, sitk::sitkUInt8);
    }
    sitk::WriteImage(image, outputFile);
    return true;
  }
  catch (...)
  {
    return false;
  }
}

void
WalkDir(const fs::path & dir, std::vector<std::string> & files)
{
  for (const auto & entry : fs::recursive_directory_iterator(dir))
  {
    if (fs::is_regular_file(entry))
    {
      files.push_back(entry.path().string());
    }
  }
}

int
main(int argc, char * argv[])
{
  if (argc < 3)
  {
    std::cout
      << "Usage: DicomConvert <root_of_data_directory> <output_file_extension> [--w width] [--od output_directory]\n";
    return 1;
  }
  std::string rootDir = argv[1];
  std::string outputExt = argv[2];
  int         width = 0;
  std::string outDir;
  for (int i = 3; i < argc; ++i)
  {
    if (std::string(argv[i]) == "--w" && i + 1 < argc)
    {
      width = std::stoi(argv[++i]);
    }
    else if (std::string(argv[i]) == "--od" && i + 1 < argc)
    {
      outDir = argv[++i];
    }
  }
  std::vector<std::string> inputFiles;
  WalkDir(rootDir, inputFiles);
  std::vector<std::string> fileNames;
  if (!outDir.empty())
  {
    for (size_t i = 0; i < inputFiles.size(); ++i)
    {
      fileNames.push_back((fs::path(outDir) / std::to_string(i)).u8string());
    }
  }
  else
  {
    fileNames = inputFiles;
  }
  std::vector<std::string> outputFiles;
  for (const auto & f : fileNames)
  {
    outputFiles.push_back(f + "." + outputExt);
  }
  std::vector<bool> res;
  for (size_t i = 0; i < inputFiles.size(); ++i)
  {
    res.push_back(ConvertImage(inputFiles[i], outputFiles[i], width));
  }
  std::vector<std::string> filteredInput, filteredOutput;
  for (size_t i = 0; i < res.size(); ++i)
  {
    if (res[i])
    {
      filteredInput.push_back(inputFiles[i]);
      filteredOutput.push_back(outputFiles[i]);
    }
  }
  std::string csvDir = !outDir.empty() ? outDir : fs::current_path().string();

  std::ofstream writer(fs::path(csvDir) / "file_names.csv");
  writer << "input file name,output file name\n";
  for (size_t i = 0; i < filteredInput.size(); ++i)
  {
    writer << filteredInput[i] << "," << filteredOutput[i] << std::endl;
  }
  return 0;
}
