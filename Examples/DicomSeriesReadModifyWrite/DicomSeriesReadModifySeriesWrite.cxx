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
 * A SimpleITK example demonstrating how to read a DICOM series,
 * modify it, and then write a new DICOM series.
 */

#include <SimpleITK.h>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

namespace sitk = itk::simple;

int
main(int argc, char * argv[])
{
  if (argc < 3)
  {
    std::cout << "Usage: " << argv[0] << " <input_directory_with_DICOM_series> <output_directory>" << std::endl;
    return 1;
  }

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
  seriesReader.MetaDataDictionaryArrayUpdateOn();
  seriesReader.LoadPrivateTagsOn();
  sitk::Image image3D = seriesReader.Execute();

  // Modify the image (blurring)
  sitk::Image filteredImage = sitk::DiscreteGaussian(image3D);

  // Write the 3D image as a series
  // IMPORTANT: There are many DICOM tags that need to be updated when you modify
  //            an original image. This is a delicate operation and requires
  //            knowledge of the DICOM standard. This example only modifies some.
  //            For a more complete list of tags that need to be modified see:
  //                http://gdcm.sourceforge.net/wiki/index.php/Writing_DICOM

  sitk::ImageFileWriter writer;
  // Use the study/series/frame of reference information given in the meta-data
  // dictionary and not the automatically generated information from the file IO
  writer.KeepOriginalImageUIDOn();

  // Copy relevant tags from the original meta-data dictionary (private tags are
  // also accessible).
  std::vector<std::string> tagsToCopy = {
    "0010|0010", // Patient Name
    "0010|0020", // Patient ID
    "0010|0030", // Patient Birth Date
    "0020|000d", // Study Instance UID, for machine consumption
    "0020|0010", // Study ID, for human consumption
    "0008|0020", // Study Date
    "0008|0030", // Study Time
    "0008|0050", // Accession Number
    "0008|0060"  // Modality
  };

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
  // NOTE: Always represent DICOM tags using lower case hexadecimals.
  std::vector<double>                              direction = filteredImage.GetDirection();
  std::vector<std::pair<std::string, std::string>> seriesTagValues;

  // Copy existing tags
  for (const auto & tag : tagsToCopy)
  {
    if (seriesReader.HasMetaDataKey(0, tag))
    {
      seriesTagValues.push_back({ tag, seriesReader.GetMetaData(0, tag) });
    }
  }

  // Add modification tags
  seriesTagValues.insert(
    seriesTagValues.end(),
    {
      { "0008|0031", modificationTime },     // Series Time
      { "0008|0021", modificationDate },     // Series Date
      { "0008|0008", "DERIVED\\SECONDARY" }, // Image Type
      { "0020|000e",
        "1.2.826.0.1.3680043.2.1125." + modificationDate + ".1" + modificationTime }, // Series Instance UID
    });

  // Image Orientation (Patient)
  std::ostringstream orientationStream;
  orientationStream << direction[0] << "\\" << direction[3] << "\\" << direction[6] << "\\" << direction[1] << "\\"
                    << direction[4] << "\\" << direction[7];
  seriesTagValues.push_back({ "0020|0037", orientationStream.str() });

  // Series Description
  std::string seriesDescription;
  if (seriesReader.HasMetaDataKey(0, "0008|103e"))
  {
    seriesDescription = seriesReader.GetMetaData(0, "0008|103e");
  }
  seriesDescription += " Processed-SimpleITK";
  seriesTagValues.push_back({ "0008|103e", seriesDescription });

  sitk::ExtractImageFilter  extractFilter;
  std::vector<unsigned int> size = filteredImage.GetSize();
  size[2] = 1; // Extract single slice
  extractFilter.SetSize(size);
  for (int i = 0; i < (int)filteredImage.GetDepth(); ++i)
  {
    extractFilter.SetIndex({ 0, 0, i });
    auto imageSlice = extractFilter.Execute(filteredImage);

    // Tags shared by the series.
    for (const auto & tagValue : seriesTagValues)
    {
      imageSlice.SetMetaData(tagValue.first, tagValue.second);
    }

    // Slice specific tags.
    auto    sliceNow = std::chrono::system_clock::now();
    auto    sliceTime_t = std::chrono::system_clock::to_time_t(sliceNow);
    std::tm sliceTm = *std::localtime(&sliceTime_t);

    std::ostringstream instanceDateStream, instanceTimeStream;
    instanceDateStream << std::put_time(&sliceTm, "%Y%m%d");
    instanceTimeStream << std::put_time(&sliceTm, "%H%M%S");

    // Instance Creation Date
    imageSlice.SetMetaData("0008|0012", instanceDateStream.str());
    // Instance Creation Time
    imageSlice.SetMetaData("0008|0013", instanceTimeStream.str());

    // Image Position (Patient)
    std::vector<double> position = filteredImage.TransformIndexToPhysicalPoint({ 0, 0, i });
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

    // Write to the output directory and add the extension dcm, to force writing
    // in DICOM format.
    std::string outPath = std::string(argv[2]) + "/" + std::to_string(i) + ".dcm";
    writer.SetFileName(outPath);
    writer.Execute(imageSlice);
  }

  return 0;
}
