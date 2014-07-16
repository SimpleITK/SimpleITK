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
#include "sitkImageFilter.h"

#include "itkProcessObject.h"

#include <iostream>



namespace itk {
namespace simple {
//----------------------------------------------------------------------------

//
// Default constructor that initializes parameters
//
template< unsigned int N >
ImageFilter< N >::ImageFilter ()
{
}

//
// Default destructor
//
template< unsigned int N >
ImageFilter< N >::~ImageFilter ()
{
}

template class ImageFilter<0>;
template class ImageFilter<1>;
template class ImageFilter<2>;
template class ImageFilter<3>;
template class ImageFilter<4>;
template class ImageFilter<5>;

} // end namespace simple
} // end namespace itk
