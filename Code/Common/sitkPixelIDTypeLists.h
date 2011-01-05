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


/** This list of pixel types is intended to be used with itk::Image classes. */
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

/** This list of pixel types is intended to be used with itk::Image classes. */
typedef BasicPixelIDTypeList ScalarPixelIDTypeList;

/** This list of pixel types is intended to be used with itk::Image classes. */
typedef typelist::MakeTypeList<BasicPixelID<signed char>,
                               BasicPixelID<unsigned char>,
                               BasicPixelID<short>,
                               BasicPixelID<unsigned short>,
                               BasicPixelID<int>,
                               BasicPixelID<unsigned int>,
                               BasicPixelID<long>,
                               BasicPixelID<unsigned long> >::Type IntegerPixelIDTypeList;


/** This list of pixel types is intended to be used with itk::Image classes. */
typedef typelist::MakeTypeList<BasicPixelID<float>,
                               BasicPixelID<double> >::Type RealPixelIDTypeList;

/** This list of pixel types is intended to be used with ?? classes. */
typedef typelist::MakeTypeList< BasicPixelID<std::complex< float > >,
                                BasicPixelID<std::complex< double > > >::Type ComplexPixelIDTypeList;

/** This list of pixel types is intended to be used with VectorImage classes. */
typedef typelist::MakeTypeList<VectorPixelID<signed char>,
                               VectorPixelID<unsigned char>,
                               VectorPixelID<short>,
                               VectorPixelID<unsigned short>,
                               VectorPixelID<float>,
                               VectorPixelID<double> >::Type VectorPixelIDTypeList;


/** This list of pixel types is intended to be used with VectorImage classes. */
typedef typelist::MakeTypeList<VectorPixelID<float>,
                               VectorPixelID<double> >::Type RealVectorPixelIDTypeList;


/** This list of pixel types is intended to be used with LabelMaps */
typedef typelist::MakeTypeList<LabelPixelID<unsigned char>,
                               LabelPixelID<unsigned short>,
                               LabelPixelID<unsigned int>,
                               LabelPixelID<unsigned long> >::Type LabelPixelIDTypeList;

typedef typelist::Append<
  typelist::Append< BasicPixelIDTypeList, ComplexPixelIDTypeList >::Type,
  VectorPixelIDTypeList
  >::Type AllPixelIDTypeList;


// this is the list of types which we will try to instantiate

#ifdef SITK_EXPRESS_INSTANTIATEDPIXELS

typedef typelist::MakeTypeList< BasicPixelID<short>, BasicPixelID<float>, BasicPixelID<double> >::Type InstantiatedPixelIDTypeList;

#else

typedef AllPixelIDTypeList InstantiatedPixelIDTypeList;

#endif


}
}
#endif // _sitkPixelIDTypeLists_h
