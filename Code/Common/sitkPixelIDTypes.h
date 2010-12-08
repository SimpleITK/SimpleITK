#ifndef _sitkPixelIDTypes_h
#define _sitkPixelIDTypes_h


#include <itkImage.h>
#include <itkVectorImage.h>
#include <itkLabelMap.h>
#include <itkLabelObject.h>

namespace itk
{
namespace simple
{

template <typename TPixelType>
struct BasicPixelID
{};

template <typename TPixelType>
struct VectorPixelID
{};


template <typename TPixelType>
struct LabelPixelID
{};

template <typename TPixelIDType, unsigned int VImageDimension> struct PixelIDToImageType;

template <typename TPixelType, unsigned int VImageDimension>
struct PixelIDToImageType< BasicPixelID<TPixelType> , VImageDimension >
{
  typedef itk::Image< TPixelType, VImageDimension > ImageType;
};


template <typename TVectorPixelType, unsigned int VImageDimension>
struct PixelIDToImageType< VectorPixelID< TVectorPixelType >, VImageDimension >
{
  typedef itk::VectorImage< TVectorPixelType, VImageDimension > ImageType;
};


template <typename TLabelType, unsigned int VImageDimension>
struct PixelIDToImageType< LabelPixelID< TLabelType >, VImageDimension >
{
  typedef itk::LabelMap< itk::LabelMap< itk::LabelObject< TLabelType, VImageDimension > > > ImageType;
};


template <typename TImageType> struct ImageTypeToPixelID;

template <typename TPixelType, unsigned int VImageDimension>
struct ImageTypeToPixelID< itk::Image< TPixelType, VImageDimension> >
{
  typedef BasicPixelID<TPixelType >PixelIDType;
};


template <typename TPixelType, unsigned int VImageDimension>
struct ImageTypeToPixelID< itk::VectorImage< TPixelType, VImageDimension> >
{
  typedef VectorPixelID< TPixelType > PixelIDType;
};


template <typename TLabelType, unsigned int VImageDimension>
struct ImageTypeToPixelID< itk::LabelMap< itk::LabelMap< itk::LabelObject< TLabelType, VImageDimension > > > >
{
  typedef  LabelPixelID< TLabelType > PixelIDType;
};




}
}
#endif // _sitkPixelIDTypes_h
