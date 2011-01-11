#ifndef __sitkPixelIDTypeLists_h
#define __sitkPixelIDTypeLists_h

#include "itkIntTypes.h"

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
//                               BasicPixelID<int64_t>,
//                               BasicPixelID<uint64_t>,
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
                               BasicPixelID<uint32_t>//,
//                               BasicPixelID<int64_t>,
//                               BasicPixelID<uint64_t>
                               >::Type IntegerPixelIDTypeList;


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


/** List of pixel ids which are vectors for itk::VectorImage class.
 *
 * \sa VectorPixelID
 */
typedef typelist::MakeTypeList<VectorPixelID<int8_t>,
                               VectorPixelID<uint8_t>,
                               VectorPixelID<int16_t>,
                               VectorPixelID<uint16_t>,
                               VectorPixelID<float>,
                               VectorPixelID<double> >::Type VectorPixelIDTypeList;


/** List of pixel ids which are real vectors for itk::VectorImage class.
 *
 * \sa VectorPixelID
 */
typedef typelist::MakeTypeList<VectorPixelID<float>,
                               VectorPixelID<double> >::Type RealVectorPixelIDTypeList;



/** List of pixel ids which are for itk::LabelMap Image class.
 *
 * \sa LabelPixelID
 */
typedef typelist::MakeTypeList<LabelPixelID<uint8_t>,
                               LabelPixelID<uint16_t>,
                               LabelPixelID<uint32_t>//,
//                               LabelPixelID<uint64_t>
                               >::Type LabelPixelIDTypeList;


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
  VectorPixelIDTypeList
  >::Type AllPixelIDTypeList;


#ifdef SITK_EXPRESS_INSTANTIATEDPIXELS


// this is a quick and dirty list to only be used for development purposes
typedef typelist::MakeTypeList< BasicPixelID<int16_t>, BasicPixelID<float>, BasicPixelID<double> >::Type InstantiatedPixelIDTypeList;

#else

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

#endif


}
}
#endif // _sitkPixelIDTypeLists_h
