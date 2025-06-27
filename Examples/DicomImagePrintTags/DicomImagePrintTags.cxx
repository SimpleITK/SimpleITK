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
 * A SimpleITK example demonstrating how to print a DICOM image's tags.
 */

#include <SimpleITK.h>
#include <iostream>
#include <vector>

namespace sitk = itk::simple;

/**
 * A SimpleITK script that prints a DICOM image's tags.
 */
int
main(int argc, char * argv[])
{
  if (argc < 2)
  {
    std::cout << "Usage: DicomImagePrintTags <input_file>" << std::endl;
    return 1;
  }

  sitk::ImageFileReader reader;

  reader.SetFileName(argv[1]);
  reader.LoadPrivateTagsOn();

  reader.ReadImageInformation();

  std::vector<std::string> keys = reader.GetMetaDataKeys();
  for (const auto & k : keys)
  {
    std::cout << "(" << k << ") = = \"" << reader.GetMetaData(k) << "\"" << std::endl;
  }

  std::vector<uint64_t> size = reader.GetSize();
  std::cout << "Image Size: [" << size[0];
  for (size_t i = 1; i < size.size(); ++i)
  {
    std::cout << ", " << size[i];
  }
  std::cout << "]" << std::endl;

  std::cout << "Image PixelType: " << sitk::GetPixelIDValueAsString(reader.GetPixelID()) << std::endl;

  return 0;
}
