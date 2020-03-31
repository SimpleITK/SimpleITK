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
#ifndef sitkImageConvert_h
#define sitkImageConvert_h

#include "sitkImage.h"

namespace itk
{

template< typename T, unsigned int NVectorDimension > class Vector;
template< typename T, unsigned int NVectorDimension > class CovariantVector;

namespace simple
{


/** \brief A utility method to help convert between itk image types efficiently.
 *
 */
template< typename TPixelType, unsigned int ImageDimension >
SITKCommon_HIDDEN
typename itk::Image< itk::Vector< TPixelType, ImageDimension >, ImageDimension>::Pointer
GetImageFromVectorImage( itk::VectorImage< TPixelType, ImageDimension > *img, bool transferOwnership = false );


template< class TPixelType, unsigned int NImageDimension, unsigned int NLength >
SITKCommon_HIDDEN
typename itk::VectorImage< TPixelType, NImageDimension >::Pointer
GetVectorImageFromImage( itk::Image< itk::Vector< TPixelType, NLength >, NImageDimension> *img, bool transferOwnership = false );

template< class TPixelType, unsigned int NImageDimension, unsigned int NLength >
SITKCommon_HIDDEN
typename itk::VectorImage< TPixelType, NImageDimension >::Pointer
GetVectorImageFromImage( itk::Image< itk::CovariantVector< TPixelType, NLength >, NImageDimension> *img, bool transferOwnership = false );


}
}

#endif // sitkImageConvert_h
