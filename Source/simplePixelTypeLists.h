#ifndef _cltPixelTypeLists_h
#define _cltPixelTypeLists_h

#include "Ancillary/TypeList.h"
#include "itkRGBPixel.h"
#include "itkRGBAPixel.h"

namespace itk
{
namespace simple
{
typedef typelist::MakeTypeList<signed char,
                               unsigned char,
                               short,
                               unsigned short,
                               int,
                               unsigned int,
                               long,
                               unsigned long,
                               float,
                               double>::Type BasicPixelTypeList;

typedef BasicPixelTypeList ScalarPixelTypeList;

typedef typelist::MakeTypeList<unsigned char,
                               unsigned short,
                               unsigned int,
                               unsigned long>::Type LabelPixelTypeList;



typedef typelist::MakeTypeList< itk::RGBPixel<signed char>,
                                itk::RGBPixel<unsigned char>,
                                itk::RGBPixel<short>,
                                itk::RGBPixel<unsigned short>,
                                itk::RGBPixel<float>,
                                itk::RGBPixel<double>
                                >::Type RGBPixelTypeList;



typedef typelist::MakeTypeList< itk::RGBPixel<signed char>,
                                itk::RGBPixel<unsigned char>,
                                itk::RGBPixel<short>,
                                itk::RGBPixel<unsigned short>,
                                itk::RGBPixel<int>,
                                itk::RGBPixel<unsigned int>,
                                itk::RGBPixel<long>,
                                itk::RGBPixel<unsigned long>,
                                itk::RGBPixel<float>,
                                itk::RGBPixel<double>
                                >::Type AllRGBPixelTypeList;



typedef typelist::MakeTypeList< itk::RGBAPixel<signed char>,
                                itk::RGBAPixel<unsigned char>,
                                itk::RGBAPixel<short>,
                                itk::RGBAPixel<unsigned short>,
                                itk::RGBAPixel<float>,
                                itk::RGBAPixel<double>
                                >::Type RGBAPixelTypeList;


typedef typelist::MakeTypeList< itk::RGBAPixel<signed char>,
                                itk::RGBAPixel<unsigned char>,
                                itk::RGBAPixel<short>,
                                itk::RGBAPixel<unsigned short>,
                                itk::RGBAPixel<int>,
                                itk::RGBAPixel<unsigned int>,
                                itk::RGBAPixel<long>,
                                itk::RGBAPixel<unsigned long>,
                                itk::RGBAPixel<float>,
                                itk::RGBAPixel<double>
                                >::Type AllRGBAPixelTypeList;

typedef typelist::Append<
  RGBPixelTypeList,
  RGBAPixelTypeList
  >::Type ColorPixelTypeList;


typedef typelist::Append<
  AllRGBPixelTypeList,
  AllRGBAPixelTypeList
  >::Type AllColorPixelTypeList;



typedef typelist::MakeTypeList< itk::Vector<signed char,2>,
                                itk::Vector<unsigned char,2>,
                                itk::Vector<short,2>,
                                itk::Vector<unsigned short,2>,
                                itk::Vector<float,2>,
                                itk::Vector<double,2>
                                >::Type Vector2PixelTypeList;


typedef typelist::MakeTypeList< itk::Vector<signed char,2>,
                                itk::Vector<unsigned char,2>,
                                itk::Vector<short,2>,
                                itk::Vector<unsigned short,2>,
                                itk::Vector<int,2>,
                                itk::Vector<unsigned int,2>,
                                itk::Vector<long,2>,
                                itk::Vector<unsigned long,2>,
                                itk::Vector<float,2>,
                                itk::Vector<double,2>
                                >::Type AllVector2PixelTypeList;

typedef typelist::MakeTypeList<  itk::Vector<unsigned char,3>,
                                itk::Vector<short,3>,
                                itk::Vector<unsigned short,3>,
                                itk::Vector<float,3>,
                                itk::Vector<double,3>
                                 >::Type Vector3PixelTypeList;

typedef typelist::MakeTypeList<  itk::Vector<unsigned char,3>,
                                itk::Vector<short,3>,
                                itk::Vector<unsigned short,3>,
                                itk::Vector<int,3>,
                                itk::Vector<unsigned int,3>,
                                itk::Vector<long,3>,
                                itk::Vector<unsigned long,3>,
                                itk::Vector<float,3>,
                                itk::Vector<double,3>
                                 >::Type AllVector3PixelTypeList;

typedef typelist::MakeTypeList< itk::Vector<unsigned char,4>,
                                itk::Vector<short,4>,
                                itk::Vector<unsigned short,4>,
                                itk::Vector<float,4>,
                                itk::Vector<double,4>
                                >::Type Vector4PixelTypeList;

typedef typelist::MakeTypeList< itk::Vector<unsigned char,4>,
                                itk::Vector<short,4>,
                                itk::Vector<unsigned short,4>,
                                itk::Vector<int,4>,
                                itk::Vector<unsigned int,4>,
                                itk::Vector<long,4>,
                                itk::Vector<unsigned long,4>,
                                itk::Vector<float,4>,
                                itk::Vector<double,4>
                                >::Type AllVector4PixelTypeList;

typedef typelist::Append<
  typelist::Append< Vector2PixelTypeList, Vector3PixelTypeList>::Type,
  Vector4PixelTypeList
  >::Type VectorPixelTypeList;


typedef typelist::Append<
  typelist::Append< AllVector2PixelTypeList, AllVector3PixelTypeList>::Type,
  AllVector4PixelTypeList
  >::Type AllVectorPixelTypeList;

typedef typelist::Append<
  typelist::Append< BasicPixelTypeList, RGBPixelTypeList>::Type,
  typelist::Append< RGBAPixelTypeList, VectorPixelTypeList>::Type
  >::Type AllPixelTypeList;

typedef typelist::MakeTypeList< unsigned char,
                                short,
                                unsigned short
                                int,
                                unsigned int,
                                float,
                                double,
                                itk::RGBPixel<unsigned char>,
                                itk::RGBAPixel<unsigned char>,
                                itk::Vector<unsigned char,3>,
                                itk::Vector<unsigned char,4>,
                                itk::Vector<double,2>,
                                itk::Vector<double,3>,
                                itk::Vector<double,4>
                                >::Type CommonPixelTypeList;

}
}
#endif // _cltPixelTypeLists_h
