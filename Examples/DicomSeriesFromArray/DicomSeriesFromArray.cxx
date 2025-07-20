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
 * A SimpleITK example demonstrating how to write a DICOM series.
 */

#include <SimpleITK.h>
#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <chrono>
#include <iomanip>
#include <sstream>

namespace sitk = itk::simple;

sitk::ImageFileWriter writer;

/**
 * Write slices to output directory
 */
void
WriteSlices(const std::vector<std::pair<std::string, std::string>> & seriesTag,
            const sitk::Image &                                      inImage,
            const std::string &                                      outDir,
            uint64_t                                                 i)
{
  sitk::Image imageSlice = inImage.Slice(0, i, 2);

  // Tags shared by the series.
  for (const auto & tagValue : seriesTag)
  {
    imageSlice.SetMetaData(tagValue.first, tagValue.second);
  }

  // Slice specific tags.
  auto    now = std::chrono::system_clock::now();
  auto    time_t = std::chrono::system_clock::to_time_t(now);
  std::tm tm = *std::localtime(&time_t);

  std::ostringstream dateStream, timeStream;
  dateStream << std::put_time(&tm, "%Y%m%d");
  timeStream << std::put_time(&tm, "%H%M%S");

  // Instance Creation Date
  imageSlice.SetMetaData("0008|0012", dateStream.str());
  // Instance Creation Time
  imageSlice.SetMetaData("0008|0013", timeStream.str());

  // Setting the type to CT so that the slice location is preserved and
  // the thickness is carried over.
  imageSlice.SetMetaData("0008|0060", "CT");

  // (0020, 0032) image position patient determines the 3D spacing between slices.
  // Image Position (Patient)
  std::vector<double> position = inImage.TransformIndexToPhysicalPoint({ 0, 0, i });
  std::ostringstream  posStream;
  for (size_t j = 0; j < position.size(); ++j)
  {
    if (j > 0)
      posStream << "\\";
    posStream << position[j];
  }
  imageSlice.SetMetaData("0020|0032", posStream.str());

  // Instance Number
  imageSlice.SetMetaData("0020|0013", std::to_string(i));

  // Write to the output directory and add the extension dcm, to force
  // writing in DICOM format.
  std::string outPath = std::string(outDir) + "/" + std::to_string(i) + ".dcm";
  writer.SetFileName(outPath);
  writer.Execute(imageSlice);
}

int
main(int argc, char * argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: DicomSeriesFromArray <output_directory>" << std::endl;
    return 1;
  }

  // Set pixel type sitkInt16 or sitkFloat64
  sitk::PixelIDValueEnum pixelType = sitk::sitkInt16;

  // Create image from random data array based on the pixel type
  std::vector<unsigned int> imageSize = { 512, 512, 256 };
  size_t                    totalPixels = imageSize[0] * imageSize[1] * imageSize[2];

  std::random_device rd;
  std::mt19937       gen(rd());
  sitk::Image        newImg;

  if (pixelType == sitk::sitkInt16)
  {
    std::uniform_int_distribution<short> dis(-1000, 1000);
    std::vector<short>                   randomData(totalPixels);
    for (size_t i = 0; i < totalPixels; ++i)
    {
      randomData[i] = dis(gen);
    }
    newImg = sitk::ImportAsInt16(randomData.data(), imageSize);
  }
  else if (pixelType == sitk::sitkFloat64)
  {
    std::uniform_real_distribution<> dis(-1000.0, 1000.0);
    std::vector<double>              randomData(totalPixels);
    for (size_t i = 0; i < totalPixels; ++i)
    {
      randomData[i] = dis(gen);
    }
    newImg = sitk::ImportAsFloat64(randomData.data(), imageSize);
  }
  else
  {
    std::cerr << "Unsupported pixel type" << std::endl;
    return 1;
  }

  newImg.SetSpacing({ 2.5, 3.5, 4.5 });

  // Write the 3D image as a series
  // IMPORTANT: There are many DICOM tags that need to be updated when you modify
  //            an original image. This is a delicate operation and requires
  //            knowledge of the DICOM standard. This example only modifies some.
  //            For a more complete list of tags that need to be modified see:
  //                  http://gdcm.sourceforge.net/wiki/index.php/Writing_DICOM
  //            If it is critical for your work to generate valid DICOM files,
  //            It is recommended to use David Clunie's Dicom3tools to validate
  //            the files:
  //                  http://www.dclunie.com/dicom3tools.html

  // Use the study/series/frame of reference information given in the meta-data
  // dictionary and not the automatically generated information from the file IO
  writer.KeepOriginalImageUIDOn();

  auto    now = std::chrono::system_clock::now();
  auto    time_t = std::chrono::system_clock::to_time_t(now);
  std::tm tm = *std::localtime(&time_t);

  std::ostringstream modificationTimeStream, modificationDateStream;
  modificationDateStream << std::put_time(&tm, "%Y%m%d");
  modificationTimeStream << std::put_time(&tm, "%H%M%S");
  std::string modificationTime = modificationTimeStream.str();
  std::string modificationDate = modificationDateStream.str();

  // Copy some of the tags and add the relevant tags indicating the change.
  // For the series instance UID (0020|000e), each of the components is a number,
  // cannot start with zero, and separated by a '.' We create a unique series ID
  // using the date and time.
  std::vector<double>                              direction = newImg.GetDirection();
  std::vector<std::pair<std::string, std::string>> seriesTagValues = {
    { "0008|0031", modificationTime },                                                           // Series Time
    { "0008|0021", modificationDate },                                                           // Series Date
    { "0008|0008", "DERIVED\\SECONDARY" },                                                       // Image Type
    { "0020|000e", "1.2.826.0.1.3680043.2.1125." + modificationDate + ".1" + modificationTime }, // Series Instance UID
    { "0008|103e", "Created-SimpleITK" }                                                         // Series Description
  };

  // Image Orientation (Patient)
  std::ostringstream orientationStream;
  orientationStream << direction[0] << "\\" << direction[3] << "\\" << direction[6] << "\\" << direction[1] << "\\"
                    << direction[4] << "\\" << direction[7];
  seriesTagValues.push_back({ "0020|0037", orientationStream.str() });

  if (pixelType == sitk::sitkFloat64)
  {
    // If we want to write floating point values, we need to use the rescale
    // slope, "0028|1053", to select the number of digits we want to keep.
    double rescaleSlope = 0.001; // keep three digits after the decimal point
    seriesTagValues.insert(seriesTagValues.end(),
                           {
                             { "0028|1053", std::to_string(rescaleSlope) }, // rescale slope
                             { "0028|1052", "0" },                          // rescale intercept
                             { "0028|0100", "16" },                         // bits allocated
                             { "0028|0101", "16" },                         // bits stored
                             { "0028|0102", "15" },                         // high bit
                             { "0028|0103", "1" }                           // pixel representation
                           });
  }

  // Write slices to output directory
  for (uint64_t i = 0; i < newImg.GetDepth(); ++i)
  {
    WriteSlices(seriesTagValues, newImg, argv[1], i);
  }

  // Re-read the series
  // Read the original series. First obtain the series file names using the
  // image series reader.
  std::string              dataDirectory = argv[1];
  std::vector<std::string> seriesIDs = sitk::ImageSeriesReader::GetGDCMSeriesIDs(dataDirectory);
  if (seriesIDs.empty())
  {
    std::cout << "ERROR: given directory \"" << dataDirectory << "\" does not contain a DICOM series." << std::endl;
    return 1;
  }

  std::vector<std::string> seriesFileNames =
    sitk::ImageSeriesReader::GetGDCMSeriesFileNames(dataDirectory, seriesIDs[0]);

  sitk::ImageSeriesReader seriesReader;
  seriesReader.SetFileNames(seriesFileNames);

  // Configure the reader to load all of the DICOM tags (public+private):
  // By default tags are not loaded (saves time).
  // By default if tags are loaded, the private tags are not loaded.
  // We explicitly configure the reader to load tags, including the
  // private ones.
  seriesReader.LoadPrivateTagsOn();
  sitk::Image image3D = seriesReader.Execute();

  std::vector<double> readSpacing = image3D.GetSpacing();
  std::vector<double> originalSpacing = newImg.GetSpacing();
  std::cout << "[" << readSpacing[0] << ", " << readSpacing[1] << ", " << readSpacing[2] << "] vs ["
            << originalSpacing[0] << ", " << originalSpacing[1] << ", " << originalSpacing[2] << "]" << std::endl;

  return 0;
}
