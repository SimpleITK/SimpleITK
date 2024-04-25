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
#ifndef sitkKernel_h
#define sitkKernel_h

#include "sitkCommon.h"
#include <ostream>

namespace itk::simple
{

enum KernelEnum
{
  /** \brief Annulus, ring, shaped structuring element.
   */
  sitkAnnulus,
  /** \brief Ball (sphere in 3D, circle in 2D) shaped structuring element.
   */
  sitkBall,
  /** \brief Box shaped structuring element.
   */
  sitkBox,
  /** \brief Cross shaped structuring element.
   */
  sitkCross,
  /** \brief Separable approximation of ball structuring element for faster computation.
   */
  sitkPolygon3,
  /** \brief Separable approximation of ball structuring element for faster computation.
   */
  sitkPolygon4,
  /** \brief Separable approximation of ball structuring element for faster computation.
   */
  sitkPolygon5,
  /** \brief Separable approximation of ball structuring element for faster computation.
   */
  sitkPolygon6,
  /** \brief Separable approximation of ball structuring element for faster computation.
   */
  sitkPolygon7,
  /** \brief Separable approximation of ball structuring element for faster computation.
   */
  sitkPolygon8,
  /** \brief Separable approximation of ball structuring element for faster computation.
   */
  sitkPolygon9
};

#ifndef SWIG
SITKCommon_EXPORT std::ostream &
                  operator<<(std::ostream & os, const KernelEnum k);
#endif

} // namespace itk::simple


#endif // sitkKernel_h
