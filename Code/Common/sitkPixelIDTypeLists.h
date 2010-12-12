#ifndef _sitkPixelIDTypeLists_h
#define _sitkPixelIDTypeLists_h

#include "Ancillary/TypeList.h"

#include "sitkPixelIDTypes.h"

#include <complex>

namespace itk
{
namespace simple
{


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

typedef BasicPixelIDTypeList ScalarPixelIDTypeList;

typedef typelist::MakeTypeList<BasicPixelID<signed char>,
                               BasicPixelID<unsigned char>,
                               BasicPixelID<short>,
                               BasicPixelID<unsigned short>,
                               BasicPixelID<int>,
                               BasicPixelID<unsigned int>,
                               BasicPixelID<long>,
                               BasicPixelID<unsigned long> >::Type IntegerPixelIDTypeList;


typedef typelist::MakeTypeList<BasicPixelID<float>,
                               BasicPixelID<double> >::Type RealPixelIDTypeList;

typedef typelist::MakeTypeList< BasicPixelID<std::complex< float > >,
                                BasicPixelID<std::complex< double > > >::Type ComplexPixelIDTypeList;

typedef typelist::MakeTypeList<VectorPixelID<signed char>,
                               VectorPixelID<unsigned char>,
                               VectorPixelID<short>,
                               VectorPixelID<unsigned short>,
                               VectorPixelID<float>,
                               VectorPixelID<double> >::Type VectorPixelIDTypeList;


typedef typelist::MakeTypeList<VectorPixelID<float>,
                               VectorPixelID<double> >::Type RealVectorPixelIDTypeList;


typedef typelist::MakeTypeList<LabelPixelID<unsigned char>,
                               LabelPixelID<unsigned short>,
                               LabelPixelID<unsigned int>,
                               LabelPixelID<unsigned long> >::Type LabelPixelIDTypeList;

typedef typelist::Append<
  typelist::Append< BasicPixelIDTypeList, ComplexPixelIDTypeList >::Type,
  VectorPixelIDTypeList
  >::Type AllPixelIDTypeList;


// this is the list of types which we will try to instantiate
typedef AllPixelIDTypeList InstantiatedPixelIDTypeList;


}
}
#endif // _sitkPixelIDTypeLists_h
