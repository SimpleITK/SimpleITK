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
#ifndef sitkProcessObjectDeleter_h
#define sitkProcessObjectDeleter_h

#include "sitkCommon.h"

namespace itk
{

class LightObject;

namespace simple
{

/**
 * \brief Enable automatic reference removal of itk::LightObject pointers to be used with STL smart pointers.
 *
 * This class is used to remove a reference to ITK LightObjects when they are no longer needed.
 * It is typically used with std::unique_ptr or std::shared_ptr to manage the lifetime
 * of ITK objects in SimpleITK.
 */
struct SITKCommon_EXPORT ProcessObjectDeleter
{
  void
  operator()(itk::LightObject * ptr) const;
};

} // namespace simple
} // namespace itk

#endif
