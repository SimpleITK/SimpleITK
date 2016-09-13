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
#ifndef sitkKernel_h
#define sitkKernel_h

#include "sitkCommon.h"
#include <ostream>

namespace itk
{
namespace simple
{

enum KernelEnum {
  sitkAnnulus,
  sitkBall,
  sitkBox,
  sitkCross,
  sitkPolygon3,
  sitkPolygon4,
  sitkPolygon5,
  sitkPolygon6,
  sitkPolygon7,
  sitkPolygon8,
  sitkPolygon9
};

#ifndef SWIG
SITKCommon_EXPORT std::ostream& operator<<(std::ostream& os, const KernelEnum k);
#endif

} // end namespace simple
} // end namespace itk


#endif // sitkKernel_h
