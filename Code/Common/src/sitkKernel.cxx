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

#include "sitkKernel.h"

#define sitkKernelToStringCaseMacro(n) case sitk##n: return ( os << #n )

namespace itk
{
namespace simple
{

std::ostream& operator<<(std::ostream& os, const KernelEnum k)
{
  switch (k)
    {
    sitkKernelToStringCaseMacro(Annulus);
    sitkKernelToStringCaseMacro(Ball);
    sitkKernelToStringCaseMacro(Box);
    sitkKernelToStringCaseMacro(Cross);
    sitkKernelToStringCaseMacro(Polygon3);
    sitkKernelToStringCaseMacro(Polygon4);
    sitkKernelToStringCaseMacro(Polygon5);
    sitkKernelToStringCaseMacro(Polygon6);
    sitkKernelToStringCaseMacro(Polygon7);
    sitkKernelToStringCaseMacro(Polygon8);
    sitkKernelToStringCaseMacro(Polygon9);
    }
  return os;
}

} // end namespace simple
} // end namespace itk
