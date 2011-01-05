#ifndef __sitkPixelIDTypeLists_h
#define __sitkPixelIDTypeLists_h

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
 * \sa BasicPixelID
 */
typedef typelist::MakeTypeList<BasicPixelID<signed char>,
                               BasicPixelID<unsigned char>,
                               BasicPixelID<short>,
                               BasicPixelID<unsigned short>,
                               BasicPixelID<int>,
                               BasicPixelID<unsigned int>,
                               BasicPixelID<long>,
                               BasicPixelID<unsigned long>,
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
typedef typelist::MakeTypeList<BasicPixelID<signed char>,
                               BasicPixelID<unsigned char>,
                               BasicPixelID<short>,
                               BasicPixelID<unsigned short>,
                               BasicPixelID<int>,
                               BasicPixelID<unsigned int>,
                               BasicPixelID<long>,
                               BasicPixelID<unsigned long> >::Type IntegerPixelIDTypeList;


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
typedef typelist::MakeTypeList<VectorPixelID<signed char>,
                               VectorPixelID<unsigned char>,
                               VectorPixelID<short>,
                               VectorPixelID<unsigned short>,
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
typedef typelist::MakeTypeList<LabelPixelID<unsigned char>,
                               LabelPixelID<unsigned short>,
                               LabelPixelID<unsigned int>,
                               LabelPixelID<unsigned long> >::Type LabelPixelIDTypeList;

/** List of all pixel ids available, this include image of itk::Image,
 * itk::VectorImage, and itk::LabelMap types.
 *
 * \todo This needs to be extended to include LabelMap pixel ids.
 *
 * \sa BasicPixelID
 * \sa VectorPixelID
 * \sa LablePixelID
 */
typedef typelist::Append<
  typelist::Append< BasicPixelIDTypeList, ComplexPixelIDTypeList >::Type,
  VectorPixelIDTypeList
  >::Type AllPixelIDTypeList;


#ifdef SITK_EXPRESS_INSTANTIATEDPIXELS

// this is a quick and dirty list to only be used for development purposes
typedef typelist::MakeTypeList< BasicPixelID<short>, BasicPixelID<float>, BasicPixelID<double> >::Type InstantiatedPixelIDTypeList;

#else

/** List of pixel ids which are instantiated for use in SimpleITK
 *
 *  this include image of itk::Image,itk::VectorImage, and
 *  itk::LabelMap types.
 *
 * \sa BasicPixelID
 * \sa VectorPixelID
 * \sa LablePixelID
 */
typedef AllPixelIDTypeList InstantiatedPixelIDTypeList;

#endif


}
}
#endif // _sitkPixelIDTypeLists_h
