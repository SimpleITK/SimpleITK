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
#include "sitkShow.h"
#include "sitkMacro.h"
#include "sitkImageViewer.h"

namespace itk
{
  namespace simple
  {

  void Show( const Image &image, const std::string& title, const bool debugOn)
    {

    ImageViewer viewer;

    viewer.SetTitle(title);

    if (debugOn)
      {
      ImageViewer::SetGlobalDefaultDebugOn();
      }
    else
      {
      ImageViewer::SetGlobalDefaultDebugOff();
      }

      viewer.Execute(image);
    }

  } // namespace simple
}
