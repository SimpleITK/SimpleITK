#ifndef _sitkPixelTypeLists_h
#define _sitkPixelTypeLists_h

#include "Ancillary/TypeList.h"

#include <itkImage.h>
#include <itkVectorImage.h>
#include <itkLabelMap.h>
#include <itkLabelObject.h>


#include <complex>

namespace itk
{
namespace simple
{

template <typename TPixelType>
struct VectorPixel
{};


template <typename TPixelType>
struct LabelPixel
{};



template <typename TPixelIDType, unsigned int VImageDimension> struct PixelIDtoImageType;

template <typename TPixelIDType, unsigned int VImageDimension>
struct PixelIDtoImageType
{
  typedef itk::Image< TPixelIDType, VImageDimension > ImageType;
};


template <typename TVectorPixelType, unsigned int VImageDimension>
struct PixelIDtoImageType< VectorPixel< TVectorPixelType >, VImageDimension >
{
  typedef itk::VectorImage< TVectorPixelType, VImageDimension > ImageType;
};


template <typename TLabelType, unsigned int VImageDimension>
struct PixelIDtoImageType< LabelPixel< TLabelType >, VImageDimension >
{
  typedef itk::LabelMap< itk::LabelMap< itk::LabelObject< TLabelType, VImageDimension > > > ImageType;
};


template <typename TImageType> struct ImageTypeToPixelID;

template <typename TPixelType, unsigned int VImageDimension>
struct ImageTypeToPixelID< itk::Image< TPixelType, VImageDimension> >
{
  typedef TPixelType PixelIDType;
};


template <typename TPixelType, unsigned int VImageDimension>
struct ImageTypeToPixelID< itk::VectorImage< TPixelType, VImageDimension> >
{
  typedef VectorPixel< TPixelType > PixelIDType;
};


template <typename TLabelType, unsigned int VImageDimension>
struct ImageTypeToPixelID< itk::LabelMap< itk::LabelMap< itk::LabelObject< TLabelType, VImageDimension > > > >
{
  typedef  LabelPixel< TLabelType > PixelIDType;
};




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

typedef typelist::MakeTypeList<char,
                               unsigned char,
                               short,
                               unsigned short,
                               int,
                               unsigned int,
                               long,
                               unsigned long>::Type IntegerPixelTypeList;


typedef typelist::MakeTypeList<float,
                               double >::Type RealPixelTypeList;

typedef typelist::MakeTypeList< std::complex< float >,
                                std::complex< double > >::Type ComplexPixelTypeList;

typedef typelist::MakeTypeList<VectorPixel<signed char>,
                               VectorPixel<char>,
                               VectorPixel<unsigned char>,
                               VectorPixel<short>,
                               VectorPixel<unsigned short>,
                               VectorPixel<float>,
                               VectorPixel<double> >::Type VectorPixelTypeList;


typedef typelist::MakeTypeList<VectorPixel<float>,
                               VectorPixel<double> >::Type RealVectorPixelTypeList;


typedef typelist::MakeTypeList<LabelPixel<unsigned char>,
                               LabelPixel<unsigned short>,
                               LabelPixel<unsigned int>,
                               LabelPixel<unsigned long> >::Type LabelPixelTypeList;

typedef typelist::Append<
  typelist::Append< BasicPixelTypeList, ComplexPixelTypeList >::Type,
  VectorPixelTypeList
  >::Type AllPixelTypeList;

}
}
#endif // _sitkPixelTypeLists_h
