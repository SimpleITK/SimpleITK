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

#include <SimpleITKTestHarness.h>
#include <SimpleITK.h>


namespace sitk = itk::simple;

DataFinder dataFinder;

int main (int argc, char *argv[])
{

  sitk::Image img;

  if (argc > 1)
    {
    for (int i=1; i<argc; i++)
      {
      img = sitk::ReadImage( argv[i] );
      sitk::Show(img);
      }
    }
  else
    {

    img = sitk::ReadImage( dataFinder.GetFile ( "Input/RA-Float.nrrd" ) );
    sitk::Show(img);

    img = sitk::ReadImage( dataFinder.GetFile ( "Input/VM1111Shrink-RGB.png" ) );
    sitk::Show(img);

    img = sitk::ReadImage( dataFinder.GetFile ( "Input/cthead1-Float.mha" ) );
    sitk::Show(img);
    }
}
