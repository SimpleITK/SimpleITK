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
#ifndef sitkPixelIDTypeLists_h
#define sitkPixelIDTypeLists_h

#include <stdint.h>

#include "sitkConfigure.h"
#include "sitkPixelIDTypes.h"

#include "Ancillary/type_list2.h"

#include <complex>

namespace itk::simple
{


/** List of all pixel ids for the itk::Image class.
 *
 * \todo address vnl issues with long long types
 *
 * \sa BasicPixelID
 */
using BasicPixelIDTypeList = typelist2::typelist<BasicPixelID<int8_t>,
                                                 BasicPixelID<uint8_t>,
                                                 BasicPixelID<int16_t>,
                                                 BasicPixelID<uint16_t>,
                                                 BasicPixelID<int32_t>,
                                                 BasicPixelID<uint32_t>,
#ifdef SITK_INT64_PIXELIDS
                                                 BasicPixelID<int64_t>,
                                                 BasicPixelID<uint64_t>,
#endif
                                                 BasicPixelID<float>,
                                                 BasicPixelID<double>>;

/** List of all single valued images of the itk::Image class.
 *
 * \sa BasicPixelID
 */
using ScalarPixelIDTypeList = BasicPixelIDTypeList;


/** List of pixel ids which are integer types for the itk::Image class.
 *
 * \sa BasicPixelID
 */
using IntegerPixelIDTypeList = typelist2::typelist<BasicPixelID<int8_t>,
                                                   BasicPixelID<uint8_t>,
                                                   BasicPixelID<int16_t>,
                                                   BasicPixelID<uint16_t>,
                                                   BasicPixelID<int32_t>,
                                                   BasicPixelID<uint32_t>
#ifdef SITK_INT64_PIXELIDS
                                                   ,
                                                   BasicPixelID<int64_t>,
                                                   BasicPixelID<uint64_t>
#endif
                                                   >;

/** List of pixel ids which are unsigned integer types for the itk::Image class.
 *
 * \sa BasicPixelID
 */
using UnsignedIntegerPixelIDTypeList = typelist2::typelist<BasicPixelID<uint8_t>,
                                                           BasicPixelID<uint16_t>,
                                                           BasicPixelID<uint32_t>
#ifdef SITK_INT64_PIXELIDS
                                                           ,
                                                           BasicPixelID<uint64_t>
#endif
                                                           >;

/** The conventional type used for a mask image as a list */
using MaskedPixelIDTypeList = typelist2::typelist<BasicPixelID<uint8_t>>;


/** List of pixel ids which are real types for the itk::Image class.
 *
 * \sa BasicPixelID
 */
using RealPixelIDTypeList = typelist2::typelist<BasicPixelID<float>, BasicPixelID<double>>;

/** List of pixel ids which are std::complex types for the itk::Image class.
 *
 * \sa BasicPixelID
 */
using ComplexPixelIDTypeList =
  typelist2::typelist<BasicPixelID<std::complex<float>>, BasicPixelID<std::complex<double>>>;

/** List of pixel ids which are signed
 *
 * \sa BasicPixelID
 */
using SignedPixelIDTypeList = typelist2::typelist<BasicPixelID<int8_t>,
                                                  BasicPixelID<int16_t>,
                                                  BasicPixelID<int32_t>,
#ifdef SITK_INT64_PIXELIDS
                                                  BasicPixelID<int64_t>,
#endif
                                                  BasicPixelID<float>,
                                                  BasicPixelID<double>>;


/** List of pixel ids which are vectors for itk::VectorImage class.
 *
 * \sa VectorPixelID
 */
using VectorPixelIDTypeList = typelist2::typelist<VectorPixelID<int8_t>,
                                                  VectorPixelID<uint8_t>,
                                                  VectorPixelID<int16_t>,
                                                  VectorPixelID<uint16_t>,
                                                  VectorPixelID<int32_t>,
                                                  VectorPixelID<uint32_t>,
#ifdef SITK_INT64_PIXELIDS
                                                  VectorPixelID<int64_t>,
                                                  VectorPixelID<uint64_t>,
#endif
                                                  VectorPixelID<float>,
                                                  VectorPixelID<double>>;


/** List of pixel ids which are real vectors for itk::VectorImage class.
 *
 * \sa VectorPixelID
 */
using RealVectorPixelIDTypeList = typelist2::typelist<VectorPixelID<float>, VectorPixelID<double>>;

/** List of pixel ids which are signed of vectors
 *
 * \sa BasicPixelID
 */
using SignedVectorPixelIDTypeList = typelist2::typelist<VectorPixelID<int8_t>,
                                                        VectorPixelID<int16_t>,
                                                        VectorPixelID<int32_t>,
                                                        VectorPixelID<float>,
                                                        VectorPixelID<double>>;


/** List of pixel ids which are for itk::LabelMap Image class.
 *
 * \sa LabelPixelID
 */
using LabelPixelIDTypeList = typelist2::typelist<LabelPixelID<uint8_t>,
                                                 LabelPixelID<uint16_t>,
                                                 LabelPixelID<uint32_t>
#ifdef SITK_INT64_PIXELIDS
                                                 ,
                                                 LabelPixelID<uint64_t>
#endif
                                                 >;

using IntegerLabelPixelIDTypeList = UnsignedIntegerPixelIDTypeList;

/** List of all pixel ids available, but itk::LabelMap this include image of itk::Image,
 * itk::VectorImage
 *
 *
 * \sa BasicPixelID
 * \sa VectorPixelID
 * \sa LabelPixelID
 */
using NonLabelPixelIDTypeList =
  typelist2::append<BasicPixelIDTypeList, ComplexPixelIDTypeList, VectorPixelIDTypeList>::type;


/** List of all pixel ids available, this include image of itk::Image,
 * itk::VectorImage, and itk::LabelMap types.
 *
 * \todo This needs to be extended to include LabelMap pixel ids.
 *
 * \sa BasicPixelID
 * \sa VectorPixelID
 * \sa LabelPixelID
 */
using AllPixelIDTypeList =
  typelist2::append<BasicPixelIDTypeList, ComplexPixelIDTypeList, VectorPixelIDTypeList, LabelPixelIDTypeList>::type;


/** List of pixel ids which are instantiated for use in SimpleITK
 *
 *  this include image of itk::Image,itk::VectorImage, and
 *  itk::LabelMap types.
 *
 * \sa BasicPixelID
 * \sa VectorPixelID
 * \sa LabelPixelID
 */
using InstantiatedPixelIDTypeList = AllPixelIDTypeList;

} // namespace itk::simple
#endif // _sitkPixelIDTypeLists_h
