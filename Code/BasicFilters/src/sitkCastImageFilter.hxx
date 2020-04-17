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
#ifndef sitkCastImageFilter_hxx
#define sitkCastImageFilter_hxx

// include itk first to suppress std::copy conversion warning
#include <itkCastImageFilter.h>

#include "sitkCastImageFilter.h"

#include <itkComposeImageFilter.h>
#include <itkLabelImageToLabelMapFilter.h>
#include <itkLabelMapToLabelImageFilter.h>

namespace itk
{
namespace simple
{

//----------------------------------------------------------------------------
// Execute Internal Methods
//----------------------------------------------------------------------------

template<typename TImageType, typename TOutputImageType>
Image
CastImageFilter::ExecuteInternalCast( const Image& inImage )
{
  using InputImageType = TImageType;
  using OutputImageType = TOutputImageType;

  typename InputImageType::ConstPointer image = this->CastImageToITK<InputImageType>( inImage );

  using FilterType = itk::CastImageFilter<InputImageType, OutputImageType>;
  typename FilterType::Pointer filter = FilterType::New();

  filter->SetInput ( image );

  this->PreUpdate( filter.GetPointer() );

  filter->Update();

  return Image( filter->GetOutput() );
}


template<typename TImageType, typename TOutputImageType>
Image CastImageFilter::ExecuteInternalToVector( const Image& inImage )
{

  using InputImageType = TImageType;
  using OutputImageType = TOutputImageType;

  typename InputImageType::ConstPointer image = this->CastImageToITK<InputImageType>( inImage );

  using FilterType = itk::ComposeImageFilter<InputImageType>;
  typename FilterType::Pointer filter = FilterType::New();
  filter->SetInput ( image );

  this->PreUpdate( filter.GetPointer() );

  using CastFilterType = itk::CastImageFilter< typename FilterType::OutputImageType, OutputImageType >;
  typename CastFilterType::Pointer caster = CastFilterType::New();
  caster->SetInput( filter->GetOutput() );
  caster->InPlaceOn();

  sitkDebugMacro( << "Executing ITK filters:" << std::endl
                  << filter
                  << caster );

  caster->Update();

  return Image( caster->GetOutput() );
}


template<typename TImageType, typename TOutputImageType>
Image CastImageFilter::ExecuteInternalToLabel( const Image& inImage )
{
  using InputImageType = TImageType;
  using OutputImageType = TOutputImageType;


  typename InputImageType::ConstPointer image = this->CastImageToITK<InputImageType>( inImage );

  using FilterType = itk::LabelImageToLabelMapFilter<InputImageType, OutputImageType>;
  typename FilterType::Pointer filter = FilterType::New();
  filter->SetInput ( image );

  this->PreUpdate( filter.GetPointer() );

  filter->Update();

  return Image( filter->GetOutput() );
}


template<typename TImageType, typename TOutputImageType>
Image CastImageFilter::ExecuteInternalLabelToImage( const Image& inImage )
{
  using InputImageType = TImageType;
  using OutputImageType = TOutputImageType;

  typename InputImageType::ConstPointer image = this->CastImageToITK<InputImageType>( inImage );


  using FilterType = itk::LabelMapToLabelImageFilter<InputImageType, OutputImageType>;
  typename FilterType::Pointer filter = FilterType::New();
  filter->SetInput ( image );

  this->PreUpdate( filter.GetPointer() );

  filter->Update();

  return Image( filter->GetOutput() );
}

} // end namespace simple
} // end namespace itk

#endif // sitkCastImageFilter_hxx
