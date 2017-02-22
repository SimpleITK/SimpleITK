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
#ifndef sitkPixelIDTypeLists_h
#define sitkPixelIDTypeLists_h

#include <stdint.h>

#include "sitkConfigure.h"
#include "sitkPixelIDTypes.h"

#include "Ancillary/TypeList.h"

#include <complex>

namespace itk
{
namespace simple
{


/** List of all pixel ids for the itk::Image class.
 *
 * \todo adress vnl issues with long long types
 *
 * \sa BasicPixelID
 */
typedef typelist::MakeTypeList<BasicPixelID<int8_t>,
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
                               BasicPixelID<double> >::Type BasicPixelIDTypeList;

/** List of all single valued images of the itk::Image class.
 *
 * \sa BasicPixelID
 */
typedef BasicPixelIDTypeList ScalarPixelIDTypeList;


/** List of pixel ids which are integer types for the itk::Image class.
 *
 * \sa BasicPixelID
 */
typedef typelist::MakeTypeList<BasicPixelID<int8_t>,
                               BasicPixelID<uint8_t>,
                               BasicPixelID<int16_t>,
                               BasicPixelID<uint16_t>,
                               BasicPixelID<int32_t>,
                               BasicPixelID<uint32_t>
#ifdef SITK_INT64_PIXELIDS
                               , BasicPixelID<int64_t>,
                               BasicPixelID<uint64_t>
#endif
                               >::Type IntegerPixelIDTypeList;

/** List of pixel ids which are unsigned integer types for the itk::Image class.
 *
 * \sa BasicPixelID
 */
typedef typelist::MakeTypeList<BasicPixelID<uint8_t>,
                               BasicPixelID<uint16_t>,
                               BasicPixelID<uint32_t>
#ifdef SITK_INT64_PIXELIDS
                               , BasicPixelID<uint64_t>
#endif
                               >::Type UnsignedIntegerPixelIDTypeList;


/** List of pixel ids which are real types for the itk::Image class.
 *
 * \sa BasicPixelID
 */
typedef typelist::MakeTypeList<BasicPixelID<float>,
                               BasicPixelID<double> >::Type RealPixelIDTypeList;

/** List of pixel ids which are std::complex types for the itk::Image class.
 *
 * \sa BasicPixelID
 */
typedef typelist::MakeTypeList< BasicPixelID<std::complex< float > >,
                                BasicPixelID<std::complex< double > > >::Type ComplexPixelIDTypeList;

/** List of pixel ids which are signed
 *
 * \sa BasicPixelID
 */
typedef typelist::MakeTypeList<BasicPixelID<int8_t>,
                               BasicPixelID<int16_t>,
                               BasicPixelID<int32_t>,
#ifdef SITK_INT64_PIXELIDS
                               BasicPixelID<int64_t>,
#endif
                               BasicPixelID<float>,
                               BasicPixelID<double> >::Type SignedPixelIDTypeList;



/** List of pixel ids which are vectors for itk::VectorImage class.
 *
 * \sa VectorPixelID
 */
typedef typelist::MakeTypeList<VectorPixelID<int8_t>,
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
                               VectorPixelID<double> >::Type VectorPixelIDTypeList;


/** List of pixel ids which are real vectors for itk::VectorImage class.
 *
 * \sa VectorPixelID
 */
typedef typelist::MakeTypeList<VectorPixelID<float>,
                               VectorPixelID<double> >::Type RealVectorPixelIDTypeList;

/** List of pixel ids which are signed of vectors
 *
 * \sa BasicPixelID
 */
typedef typelist::MakeTypeList< VectorPixelID<int8_t>,
                                VectorPixelID<int16_t>,
                                VectorPixelID<int32_t>,
                                VectorPixelID<float>,
                                VectorPixelID<double> >::Type SignedVectorPixelIDTypeList;


/** List of pixel ids which are for itk::LabelMap Image class.
 *
 * \sa LabelPixelID
 */
typedef typelist::MakeTypeList<LabelPixelID<uint8_t>,
                               LabelPixelID<uint16_t>,
                               LabelPixelID<uint32_t>
#ifdef SITK_INT64_PIXELIDS
                               ,LabelPixelID<uint64_t>
#endif
                               >::Type LabelPixelIDTypeList;

typedef UnsignedIntegerPixelIDTypeList IntegerLabelPixelIDTypeList;

/** List of all pixel ids available, but itk::LabelMap this include image of itk::Image,
 * itk::VectorImage
 *
 *
 * \sa BasicPixelID
 * \sa VectorPixelID
 * \sa LabelPixelID
 */
typedef typelist::Append<
  typelist::Append< BasicPixelIDTypeList, ComplexPixelIDTypeList >::Type,
  VectorPixelIDTypeList
  >::Type NonLabelPixelIDTypeList;


/** List of all pixel ids available, this include image of itk::Image,
 * itk::VectorImage, and itk::LabelMap types.
 *
 * \todo This needs to be extended to include LabelMap pixel ids.
 *
 * \sa BasicPixelID
 * \sa VectorPixelID
 * \sa LabelPixelID
 */
typedef typelist::Append<
  typelist::Append< BasicPixelIDTypeList, ComplexPixelIDTypeList >::Type,
  typelist::Append< VectorPixelIDTypeList, LabelPixelIDTypeList >::Type
  >::Type AllPixelIDTypeList;


/** List of pixel ids which are instantiated for use in SimpleITK
 *
 *  this include image of itk::Image,itk::VectorImage, and
 *  itk::LabelMap types.
 *
 * \sa BasicPixelID
 * \sa VectorPixelID
 * \sa LabelPixelID
 */
typedef AllPixelIDTypeList InstantiatedPixelIDTypeList;

}
}
#endif // _sitkPixelIDTypeLists_h
