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
#ifndef sitkVectorScalarBroadcast_hxx
#define sitkVectorScalarBroadcast_hxx

#include "itkImage.h"
#include "itkVectorImage.h"

#include <type_traits>

namespace itk::simple
{

namespace
{

/** True for itk::VectorImage, false for all other image types. */
template <typename TImage>
struct IsVectorImage : std::false_type
{};

template <typename TComponent, unsigned int VImageDimension>
struct IsVectorImage<itk::VectorImage<TComponent, VImageDimension>> : std::true_type
{};

/** The scalar image type holding one component of a vector image. */
template <typename TVectorImage>
struct ComponentImage;

template <typename TComponent, unsigned int VImageDimension>
struct ComponentImage<itk::VectorImage<TComponent, VImageDimension>>
{
  using Type = itk::Image<TComponent, VImageDimension>;
};

} // namespace
} // namespace itk::simple

#endif
