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
#ifndef sitkCreateInterpolator_hxx
#define sitkCreateInterpolator_hxx


#include "sitkInterpolator.h"
#include <itkNearestNeighborInterpolateImageFunction.h>
#include <itkLinearInterpolateImageFunction.h>
#include <itkBSplineInterpolateImageFunction.h>
#include <itkGaussianInterpolateImageFunction.h>
#include <itkLabelImageGaussianInterpolateImageFunction.h>
#include <itkWindowedSincInterpolateImageFunction.h>
#include <itkBSplineResampleImageFunction.h>

namespace itk
{

namespace simple
{

template<typename TInterpolatorType>
typename TInterpolatorType::Pointer
ConditionalCreateInterpolator( const TrueType & )
{
  return TInterpolatorType::New();
}

template<typename TInterpolatorType>
TInterpolatorType*
ConditionalCreateInterpolator( const FalseType & )
{
  return nullptr;
}

template< typename TImageType >
typename itk::InterpolateImageFunction< TImageType, double >::Pointer
CreateInterpolator( const TImageType *image, InterpolatorEnum itype )
{
  using RType = typename itk::InterpolateImageFunction< TImageType, double >::Pointer;
  using BoundaryCondition = typename itk::ZeroFluxNeumannBoundaryCondition<TImageType,TImageType>;
  //using BoundaryCondition = typename itk::ConstantBoundaryCondition<TImageType>;

  using SpacingType = typename TImageType::SpacingType;

  static const unsigned int WindowingRadius = 5;

  const SpacingType &spacing = image->GetSpacing();

  switch( itype )
    {
    case sitkNearestNeighbor:
    {
      using InterpolatorType = itk::NearestNeighborInterpolateImageFunction<TImageType, double>;
      return RType( InterpolatorType::New() );
    }
    case sitkLinear:
    {
      using InterpolatorType = itk::LinearInterpolateImageFunction<TImageType, double>;
      return RType( InterpolatorType::New() );
    }
    case sitkBSpline:
    {
      using InterpolatorType = itk::BSplineInterpolateImageFunction<TImageType, double>;
      return RType( ConditionalCreateInterpolator<InterpolatorType>( typename IsBasic<TImageType>::Type() ) );
    }
    case sitkGaussian:
    {
    using InterpolatorType = itk::GaussianInterpolateImageFunction<TImageType, double>;

    typename InterpolatorType::ArrayType sigma;

    for( unsigned int i = 0; i < TImageType::ImageDimension; ++i )
      {
      sigma[i] = 0.8*spacing[i];
      }
    typename InterpolatorType::Pointer p = InterpolatorType::New();
    p->SetSigma(sigma);
    p->SetAlpha(4.0);
    return RType(p);
    }
    case sitkLabelGaussian:
    {
    using InterpolatorType = itk::LabelImageGaussianInterpolateImageFunction<TImageType, double>;

    typename InterpolatorType::ArrayType sigma;

    for( unsigned int i = 0; i < TImageType::ImageDimension; ++i )
      {
      sigma[i] = spacing[i];
      }
    typename InterpolatorType::Pointer p = InterpolatorType::New();
    p->SetSigma(sigma);
    p->SetAlpha(1.0);
    return RType(p);
    }
    case sitkHammingWindowedSinc:
    {

      using WindowFunction = typename itk::Function::HammingWindowFunction<WindowingRadius, double, double >;
      using InterpolatorType = itk::WindowedSincInterpolateImageFunction<TImageType, WindowingRadius, WindowFunction, BoundaryCondition>;
      return RType( ConditionalCreateInterpolator<InterpolatorType>( typename IsBasic<TImageType>::Type() ) );
    }
    case sitkCosineWindowedSinc:
    {
      using WindowFunction = typename itk::Function::CosineWindowFunction<WindowingRadius, double, double >;
      using InterpolatorType = itk::WindowedSincInterpolateImageFunction<TImageType, WindowingRadius, WindowFunction, BoundaryCondition>;
      return RType( ConditionalCreateInterpolator<InterpolatorType>( typename IsBasic<TImageType>::Type() ) );
    }
    case sitkWelchWindowedSinc:
    {
      using WindowFunction = typename itk::Function::WelchWindowFunction<WindowingRadius, double, double >;
      using InterpolatorType = itk::WindowedSincInterpolateImageFunction<TImageType, WindowingRadius, WindowFunction, BoundaryCondition>;
      return RType( ConditionalCreateInterpolator<InterpolatorType>( typename IsBasic<TImageType>::Type() ) );
    }
    case sitkLanczosWindowedSinc:
    {
      using WindowFunction = typename itk::Function::LanczosWindowFunction<WindowingRadius, double, double >;
      using InterpolatorType = itk::WindowedSincInterpolateImageFunction<TImageType, WindowingRadius, WindowFunction, BoundaryCondition>;
      return RType( ConditionalCreateInterpolator<InterpolatorType>( typename IsBasic<TImageType>::Type() ) );
    }
    case sitkBlackmanWindowedSinc:
    {
      using WindowFunction = typename itk::Function::BlackmanWindowFunction<WindowingRadius, double, double >;
      using InterpolatorType = itk::WindowedSincInterpolateImageFunction<TImageType, WindowingRadius, WindowFunction, BoundaryCondition>;
      return RType( ConditionalCreateInterpolator<InterpolatorType>( typename IsBasic<TImageType>::Type() ) );
    }
    case sitkBSplineResamplerOrder1:
    {
    using InterpolatorType = typename itk::BSplineResampleImageFunction<TImageType, double>;
    typename InterpolatorType::Pointer p = ConditionalCreateInterpolator<InterpolatorType>( typename IsBasic<TImageType>::Type() );
    p->SetSplineOrder(1);
    return RType( p );
    }
    case sitkBSplineResamplerOrder2:
    {
    using InterpolatorType = typename itk::BSplineResampleImageFunction<TImageType, double>;
    typename InterpolatorType::Pointer p = ConditionalCreateInterpolator<InterpolatorType>( typename IsBasic<TImageType>::Type() );
    p->SetSplineOrder(2);
    return RType( p );
    }
    case  sitkBSplineResamplerOrder3:
      // sitkBSplineResampler
    {
    using InterpolatorType = typename itk::BSplineResampleImageFunction<TImageType, double>;
    typename InterpolatorType::Pointer p = ConditionalCreateInterpolator<InterpolatorType>( typename IsBasic<TImageType>::Type() );
    p->SetSplineOrder(3);
    return RType( p );
    }
    case sitkBSplineResamplerOrder4:
    {
    using InterpolatorType = typename itk::BSplineResampleImageFunction<TImageType, double>;
    typename InterpolatorType::Pointer p = ConditionalCreateInterpolator<InterpolatorType>( typename IsBasic<TImageType>::Type() );
    p->SetSplineOrder(4);
    return RType( p );
    }
    case sitkBSplineResamplerOrder5 :
    {
    using InterpolatorType = typename itk::BSplineResampleImageFunction<TImageType, double>;
    typename InterpolatorType::Pointer p = ConditionalCreateInterpolator<InterpolatorType>( typename IsBasic<TImageType>::Type() );
    p->SetSplineOrder(5);
    return RType( p );
    }
    default:
      return nullptr;
    }

}


} // end namespace simple
} // end namespace itk


#endif // sitkCreateInterpolator_hxx
