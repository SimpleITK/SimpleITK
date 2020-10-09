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

#ifndef sitkImageIOUtilities_h
#define sitkImageIOUtilities_h

#include <string>
#include <vector>
#include <ostream>

namespace itk {


// Forward declaration for pointer
class ImageIOBase;


template<class T>
class SmartPointer;

namespace simple {
namespace ioutils {

/* Internal method which prints all registered ImageIO names and the
 * file extensions they report as supporting.
 */
SITKIO_HIDDEN void PrintRegisteredImageIOs(std::ostream & out);

/* Internal method which creates a string list of the names of the
* ImageIOs registered.
 */
SITKIO_HIDDEN std::vector<std::string> GetRegisteredImageIOs();


SITKIO_HIDDEN itk::SmartPointer<ImageIOBase> CreateImageIOByName(const std::string & ioname);

}
}
}

#endif
