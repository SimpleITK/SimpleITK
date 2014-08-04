/*=========================================================================
*
*  Copyright Insight Software Consortium
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

#include "sitkTransformCompare.h"
#include "SimpleITK.h"

namespace sitk = itk::simple;

int main(int argc, char *argv[])
{

  if (argc < 3)
    {
    std::cerr << "Usage: " << argv[0] << "transform baselineDisplacement [tolerance]" << std::endl;

    std::cerr << std::endl;
    std::cerr << "This program is used to compare an input transformation file to a baseline displacement field file." << std::endl;
    return EXIT_FAILURE;
    }

  try
    {
    std::string transformFileName = argv[1];
    std::string baselineFileName = argv[2];
    double tolerance = 0.0;
    if (argc > 3)
      tolerance = atof(argv[3]);

    std::cout << "Reading test transform: \"" << transformFileName << "\"..." << std::endl;
    sitk::Transform transform = sitk::ReadTransform(transformFileName);

    std::cout << "Reading baseline displacement: \"" << baselineFileName << "\"..." << std::endl;
    sitk::Image baseline = sitk::ReadImage(baselineFileName);

    TransformCompare compare;
    compare.SetTolerance(tolerance);
    if (compare.Compare(transform, baseline))
      {
      return EXIT_SUCCESS;
      }
    }
  catch (std::exception &e)
    {
    std::cerr << "Exception: " << e.what() << std::endl;
    }
  catch (...)
    {
    std::cerr << "Unknown Exception!" << std::endl;
    }
  return EXIT_FAILURE;
}
