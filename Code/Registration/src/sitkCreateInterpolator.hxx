/*=========================================================================
*
*  Copyright Insight Software Consortium
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
  return NULL;
}

template< typename TImageType >
typename itk::InterpolateImageFunction< TImageType, double >::Pointer
CreateInterpolator( const TImageType *image, InterpolatorEnum itype )
{
  typedef typename itk::InterpolateImageFunction< TImageType, double >::Pointer RType;
  typedef typename itk::ZeroFluxNeumannBoundaryCondition<TImageType,TImageType> BoundaryCondition;
  //typedef typename itk::ConstantBoundaryCondition<TImageType> BoundaryCondition;

  typedef typename TImageType::SpacingType SpacingType;

  static const unsigned int WindowingRadius = 5;

  const SpacingType &spacing = image->GetSpacing();

  switch( itype )
    {
    case sitkNearestNeighbor:
    {
      typedef itk::NearestNeighborInterpolateImageFunction<TImageType, double> InterpolatorType;
      return RType( InterpolatorType::New() );
    }
    case sitkLinear:
    {
      typedef itk::LinearInterpolateImageFunction<TImageType, double> InterpolatorType;
      return RType( InterpolatorType::New() );
    }
    case sitkBSpline:
    {
      typedef itk::BSplineInterpolateImageFunction<TImageType, double> InterpolatorType;
      return RType( ConditionalCreateInterpolator<InterpolatorType>( typename IsBasic<TImageType>::Type() ) );
    }
    case sitkGaussian:
    {
    typedef itk::GaussianInterpolateImageFunction<TImageType, double> InterpolatorType;

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
    typedef itk::LabelImageGaussianInterpolateImageFunction<TImageType, double> InterpolatorType;

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

      typedef typename itk::Function::HammingWindowFunction<WindowingRadius, double, double > WindowFunction;
      typedef itk::WindowedSincInterpolateImageFunction<TImageType, WindowingRadius, WindowFunction, BoundaryCondition> InterpolatorType;
      return RType( ConditionalCreateInterpolator<InterpolatorType>( typename IsBasic<TImageType>::Type() ) );
    }
    case sitkCosineWindowedSinc:
    {
      typedef typename itk::Function::CosineWindowFunction<WindowingRadius, double, double > WindowFunction;
      typedef itk::WindowedSincInterpolateImageFunction<TImageType, WindowingRadius, WindowFunction, BoundaryCondition> InterpolatorType;
      return RType( ConditionalCreateInterpolator<InterpolatorType>( typename IsBasic<TImageType>::Type() ) );
    }
    case sitkWelchWindowedSinc:
    {
      typedef typename itk::Function::WelchWindowFunction<WindowingRadius, double, double > WindowFunction;
      typedef itk::WindowedSincInterpolateImageFunction<TImageType, WindowingRadius, WindowFunction, BoundaryCondition> InterpolatorType;
      return RType( ConditionalCreateInterpolator<InterpolatorType>( typename IsBasic<TImageType>::Type() ) );
    }
    case sitkLanczosWindowedSinc:
    {
      typedef typename itk::Function::LanczosWindowFunction<WindowingRadius, double, double > WindowFunction;
      typedef itk::WindowedSincInterpolateImageFunction<TImageType, WindowingRadius, WindowFunction, BoundaryCondition> InterpolatorType;
      return RType( ConditionalCreateInterpolator<InterpolatorType>( typename IsBasic<TImageType>::Type() ) );
    }
    case sitkBlackmanWindowedSinc:
    {
      typedef typename itk::Function::BlackmanWindowFunction<WindowingRadius, double, double > WindowFunction;
      typedef itk::WindowedSincInterpolateImageFunction<TImageType, WindowingRadius, WindowFunction, BoundaryCondition> InterpolatorType;
      return RType( ConditionalCreateInterpolator<InterpolatorType>( typename IsBasic<TImageType>::Type() ) );
    }
    default:
      return NULL;
    }

}


} // end namespace simple
} // end namespace itk


#endif // sitkCreateInterpolator_hxx
