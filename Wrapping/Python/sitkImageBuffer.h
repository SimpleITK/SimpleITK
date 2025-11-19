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

#ifndef sitkImageBuffer_h
#define sitkImageBuffer_h

#include "sitkImage.h"
#include <Python.h>

#ifdef __cplusplus
extern "C"
{
#endif

  /**
   * @brief Initialize the ImageBuffer type and add it to the Python module
   *
   * This function registers the ImageBuffer type with the Python module,
   * making it publicly available as _SimpleITK.ImageBuffer(image).
   * The ImageBuffer type implements the Python buffer protocol for efficient
   * zero-copy access to SimpleITK image data.
   *
   * @param module The Python module to register the type with
   * @return int 0 on success, -1 on failure
   */
  int
  InitImageBufferType(PyObject * module);

#ifdef __cplusplus
}

// C++ helper function to extract sitk::Image* from SWIG-wrapped PyObject
// This is defined in Python.i where SWIG macros are available
namespace itk::simple
{
class Image;
}
itk::simple::Image *
sitk_GetImagePointerFromPyObject(PyObject * pyImage);
#endif

#endif // sitkImageBuffer_h
