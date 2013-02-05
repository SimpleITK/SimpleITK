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
#ifndef __sitkAdditionalProcedures_h
#define __sitkAdditionalProcedures_h


#include "sitkBasicFilters.h"
#include "sitkImage.h"
#include "sitkTransform.h"
#include "sitkInterpolator.h"

namespace itk {
namespace simple {

/**
 * \brief itk::simple::ResampleImageFilter Procedural Interface
 *
 * This function directly calls the execute method of ResampleImageFilter
 * in order to support a procedual API
 *
 * \sa itk::simple::ResampleImageFilter for the object oriented interface
 */
SITKBasicFilters_EXPORT Image Resample ( const Image& image1, const Image& referenceImage, Transform transform = itk::simple::Transform(), InterpolatorEnum interpolator = itk::simple::sitkLinear, double defaultPixelValue = 0.0 );

}
}
#endif
