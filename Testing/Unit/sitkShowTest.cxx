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

#include <cstdlib>
#include <SimpleITKTestHarness.h>
#include <SimpleITK.h>


namespace sitk = itk::simple;

DataFinder dataFinder;

int main (int argc, char *argv[])
{

  sitk::Image img;
  sitk::ImageViewer viewer;

  sitk::ImageViewer::SetGlobalDefaultDebug(true);

  std::cout << "Starting sitkShowTest\n";

  if (argc > 1)
    {
    for (int i=1; i<argc; i++)
      {
      std::string title;
      try
        {
        std::cout << "Reading " << argv[i] << std::endl;
        img = sitk::ReadImage( argv[i] );
        std::cout << "Showing " << argv[i] << std::endl;
        title = "Show Test " + std::to_string(i);
        viewer.SetTitle(title);
        viewer.Execute(img);
        }
      catch (std::exception &e)
        {
        std::cout << "Exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
        }
      catch (...)
        {
        std::cout << "Default exception\n";
        return EXIT_FAILURE;
        }
      }
    }

  else
    {
    try
      {
      std::cout << "Read 1\n";
      img = sitk::ReadImage( dataFinder.GetFile ( "Input/RA-Float.nrrd" ) );
      std::cout << "Show 1\n";
      sitk::Show(img, "Show Test 1", true);
      }
    catch (std::exception &e)
      {
      std::cout << "Exception: " << e.what() << std::endl;
      return EXIT_FAILURE;
      }
    catch (...)
      {
      std::cout << "Default exception\n";
      return EXIT_FAILURE;
      }


    try
      {
      std::cout << "Read 2\n";
      img = sitk::ReadImage( dataFinder.GetFile ( "Input/VM1111Shrink-RGB.png" ) );
      std::cout << "Show 2\n";
      sitk::Show(img, "Show Test 2", true);
      }
    catch (std::exception &e)
      {
      std::cout << "Exception: " << e.what() << std::endl;
      return EXIT_FAILURE;
      }
    catch (...)
      {
      std::cout << "Default exception\n";
      return EXIT_FAILURE;
      }

    try
      {
      std::cout << "Read 3\n";
      img = sitk::ReadImage( dataFinder.GetFile ( "Input/cthead1-Float.mha" ) );
      std::cout << "Show 3\n";
      sitk::Show(img, "Show Test 3", true);
      }
    catch (std::exception &e)
      {
      std::cout << "Exception: " << e.what() << std::endl;
      return EXIT_FAILURE;
      }
    catch (...)
      {
      std::cout << "Default exception\n";
      return EXIT_FAILURE;
      }
    }

  return EXIT_SUCCESS;
}
