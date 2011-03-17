#ifndef __sitkCastImageFilter_txx
#define __sitkCastImageFilter_txx

#include "sitkCastImageFilter.h"

#include <itkCastImageFilter.h>
#include <itkImageToVectorImageFilter.h>
#include <itkLabelImageToLabelMapFilter.h>

namespace itk
{
namespace simple
{

//----------------------------------------------------------------------------
// Execute Internal Methods
//----------------------------------------------------------------------------

template<typename TImageType, typename TOutputImageType>
Image*
CastImageFilter::ExecuteInternalCast( Image* inImage )
{
  typedef TImageType       InputImageType;
  typedef TOutputImageType OutputImageType;

  typename InputImageType::ConstPointer image =
    dynamic_cast <InputImageType*> ( inImage->GetImageBase() );

  if ( image.IsNull() )
    {
    sitkExceptionMacro( << "Could not cast input image to proper type" );
    }

  typedef itk::CastImageFilter<InputImageType, OutputImageType> FilterType;
  typename FilterType::Pointer filter = FilterType::New();

  filter->SetInput ( image );
  filter->Update();

  Image* out = new Image( filter->GetOutput() );

  return out;
}


template<typename TImageType, typename TOutputImageType>
Image* CastImageFilter::ExecuteInternalToVector( Image* inImage )
{

  typedef TImageType       InputImageType;
  typedef TOutputImageType OutputImageType;

  typename InputImageType::ConstPointer image =
    dynamic_cast <InputImageType*> ( inImage->GetImageBase() );

  if ( image.IsNull() )
    {
    sitkExceptionMacro( << "Could not cast input image to proper type" );
    }

  typedef itk::ImageToVectorImageFilter<InputImageType> FilterType;
  typename FilterType::Pointer filter = FilterType::New();
  filter->SetInput ( image );

  typedef itk::CastImageFilter< typename FilterType::OutputImageType, OutputImageType > CastFilterType;
  typename CastFilterType::Pointer caster = CastFilterType::New();
  caster->SetInput( filter->GetOutput() );
  caster->InPlaceOn();
  caster->Update();

  Image* out = new Image( caster->GetOutput() );

  return out;
}


template<typename TImageType, typename TOutputImageType>
Image* CastImageFilter::ExecuteInternalToLabel( Image* inImage )
{
  typedef TImageType                                InputImageType;
  typedef TOutputImageType                          OutputImageType;
  typedef typename OutputImageType::LabelObjectType LabelObjectType;
  typedef typename LabelObjectType::LabelType       LabelType;

  typedef itk::Image<LabelType, InputImageType::ImageDimension> LabelImageType;

  typename InputImageType::ConstPointer image =
    dynamic_cast <InputImageType*> ( inImage->GetImageBase() );

  if ( image.IsNull() )
    {
    sitkExceptionMacro( << "Could not cast input image to proper type" );
    }

  typedef itk::LabelImageToLabelMapFilter<InputImageType, OutputImageType> FilterType;
  typename FilterType::Pointer filter = FilterType::New();
  filter->SetInput ( image );
  filter->Update();

  Image* out = new Image( filter->GetOutput() );

  return out;
}

Image* Cast ( Image* image, PixelIDValueType pixelID ) {
  CastImageFilter filter;
  return filter.SetOutputPixelType ( pixelID ).Execute ( image );
}


} // end namespace simple
} // end namespace itk

#endif //__sitkCastImageFilter_txx
