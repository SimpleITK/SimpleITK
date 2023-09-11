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
#include <itkBSplineInterpolateImageFunction.h>
#include <itkBSplineResampleImageFunction.h>
#include <itkGaussianInterpolateImageFunction.h>
#include <itkLabelImageGaussianInterpolateImageFunction.h>
#ifdef SITK_GENERIC_LABEL_INTERPOLATOR
#include <itkLabelImageGenericInterpolateImageFunction.h>
#endif
#include <itkLinearInterpolateImageFunction.h>
#include <itkNearestNeighborInterpolateImageFunction.h>
#include <itkWindowedSincInterpolateImageFunction.h>

namespace itk
{

namespace simple
{
namespace {
template <typename TInterpolatorType>
typename TInterpolatorType::Pointer
ConditionalCreateInterpolator(const TrueType &) {
  return TInterpolatorType::New();
}

template <typename TInterpolatorType>
TInterpolatorType *ConditionalCreateInterpolator(const FalseType &) {
  return nullptr;
}

template <typename TPixelType, unsigned int N>
typename itk::InterpolateImageFunction<itk::VectorImage<TPixelType, N>,
                                       double>::Pointer
CreateInterpolator(const itk::VectorImage<TPixelType, N> * image,
                   InterpolatorEnum itype) {
  Unused(image);
  using TImageType = itk::VectorImage<TPixelType, N>;
  using RType =
      typename itk::InterpolateImageFunction<TImageType, double>::Pointer;

  switch (itype) {
  case sitkNearestNeighbor: {
    using InterpolatorType =
        itk::NearestNeighborInterpolateImageFunction<TImageType, double>;
    return RType(InterpolatorType::New());
  }
  case sitkLinear: {
    using InterpolatorType =
        itk::LinearInterpolateImageFunction<TImageType, double>;
    return RType(InterpolatorType::New());
  }
  default:
    return nullptr;
  }
}


template <typename TPixelType, unsigned int N>
typename itk::InterpolateImageFunction<itk::Image<std::complex<TPixelType>, N>,
                                       double>::Pointer
CreateInterpolator(const itk::Image<std::complex<TPixelType>, N> * image,
                   InterpolatorEnum itype) {
  Unused(image);
  using TImageType = itk::Image<std::complex<TPixelType>, N>;
  using RType =
      typename itk::InterpolateImageFunction<TImageType, double>::Pointer;

  switch (itype) {
  case sitkNearestNeighbor: {
    using InterpolatorType =
        itk::NearestNeighborInterpolateImageFunction<TImageType, double>;
    return RType(InterpolatorType::New());
  }
  case sitkLinear: {
    using InterpolatorType =
        itk::LinearInterpolateImageFunction<TImageType, double>;
    return RType(InterpolatorType::New());
  }
  default:
    return nullptr;
  }
}

template <typename TImageType>
typename itk::InterpolateImageFunction<TImageType, double>::Pointer
CreateInterpolator(const TImageType *image, InterpolatorEnum itype) {
  using RType =
      typename itk::InterpolateImageFunction<TImageType, double>::Pointer;
  using BoundaryCondition =
      typename itk::ZeroFluxNeumannBoundaryCondition<TImageType, TImageType>;

  using SpacingType = typename TImageType::SpacingType;

  static const unsigned int WindowingRadius = 5;

  const SpacingType &spacing = image->GetSpacing();

  switch (itype) {
  case sitkNearestNeighbor: {
    using InterpolatorType =
        itk::NearestNeighborInterpolateImageFunction<TImageType, double>;
    return RType(InterpolatorType::New());
  }
  case sitkLinear: {
    using InterpolatorType =
        itk::LinearInterpolateImageFunction<TImageType, double>;
    return RType(InterpolatorType::New());
  }
  case sitkBSpline1: {
      using InterpolatorType = itk::BSplineInterpolateImageFunction<TImageType, double>;
      auto interp = ConditionalCreateInterpolator<InterpolatorType>( typename IsBasic<TImageType>::Type() );
      interp->SetSplineOrder(1);
      return interp;
  }
    case sitkBSpline2: {
      using InterpolatorType = itk::BSplineInterpolateImageFunction<TImageType, double>;
      auto interp = ConditionalCreateInterpolator<InterpolatorType>( typename IsBasic<TImageType>::Type() );
      interp->SetSplineOrder(2);
      return interp;
    }
    case sitkBSpline3: {
      using InterpolatorType = itk::BSplineInterpolateImageFunction<TImageType, double>;
      auto interp = ConditionalCreateInterpolator<InterpolatorType>( typename IsBasic<TImageType>::Type() );
      interp->SetSplineOrder(3);
      return interp;
    }
    case sitkBSpline4: {
      using InterpolatorType = itk::BSplineInterpolateImageFunction<TImageType, double>;
      auto interp = ConditionalCreateInterpolator<InterpolatorType>( typename IsBasic<TImageType>::Type() );
      interp->SetSplineOrder(4);
      return interp;
    }
    case sitkBSpline5: {
      using InterpolatorType = itk::BSplineInterpolateImageFunction<TImageType, double>;
      auto interp = ConditionalCreateInterpolator<InterpolatorType>( typename IsBasic<TImageType>::Type() );
      interp->SetSplineOrder(5);
      return interp;
    }
  case sitkGaussian: {
    using InterpolatorType = itk::GaussianInterpolateImageFunction<TImageType, double>;

    typename InterpolatorType::ArrayType sigma;

    for( unsigned int i = 0; i < TImageType::ImageDimension; ++i )
      {
      sigma[i] = 0.8*spacing[i];
      }
    typename InterpolatorType::Pointer p = ConditionalCreateInterpolator<InterpolatorType>( typename IsBasic<TImageType>::Type() );
    if (p == nullptr) {
      return p;
    }
    p->SetSigma(sigma);
    p->SetAlpha(4.0);
    return RType(p);
  }
  case sitkLabelGaussian: {
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
  case sitkLabelLinear: {
#ifdef SITK_GENERIC_LABEL_INTERPOLATOR
    using InterpolatorType = itk::LabelImageGenericInterpolateImageFunction<TImageType, itk::LinearInterpolateImageFunction, double>;

    typename InterpolatorType::Pointer p = InterpolatorType::New();
    return RType(p);
#else
      sitkExceptionMacro( "sitkLabelLinear is not supported in this build. Compile ITK with Module_GenericLabelInterpolator=ON." );
#endif
  }
  case sitkHammingWindowedSinc: {

    using WindowFunction =
        typename itk::Function::HammingWindowFunction<WindowingRadius, double,
                                                      double>;
    using InterpolatorType = itk::WindowedSincInterpolateImageFunction<
        TImageType, WindowingRadius, WindowFunction, BoundaryCondition>;
    return RType(ConditionalCreateInterpolator<InterpolatorType>(
        typename IsBasic<TImageType>::Type()));
  }
  case sitkCosineWindowedSinc: {
    using WindowFunction =
        typename itk::Function::CosineWindowFunction<WindowingRadius, double,
                                                     double>;
    using InterpolatorType = itk::WindowedSincInterpolateImageFunction<
        TImageType, WindowingRadius, WindowFunction, BoundaryCondition>;
    return RType(ConditionalCreateInterpolator<InterpolatorType>(
        typename IsBasic<TImageType>::Type()));
  }
  case sitkWelchWindowedSinc: {
    using WindowFunction =
        typename itk::Function::WelchWindowFunction<WindowingRadius, double,
                                                    double>;
    using InterpolatorType = itk::WindowedSincInterpolateImageFunction<
        TImageType, WindowingRadius, WindowFunction, BoundaryCondition>;
    return RType(ConditionalCreateInterpolator<InterpolatorType>(
        typename IsBasic<TImageType>::Type()));
  }
  case sitkLanczosWindowedSinc: {
    using WindowFunction =
        typename itk::Function::LanczosWindowFunction<WindowingRadius, double,
                                                      double>;
    using InterpolatorType = itk::WindowedSincInterpolateImageFunction<
        TImageType, WindowingRadius, WindowFunction, BoundaryCondition>;
    return RType(ConditionalCreateInterpolator<InterpolatorType>(
        typename IsBasic<TImageType>::Type()));
  }
  case sitkBlackmanWindowedSinc: {
    using WindowFunction =
        typename itk::Function::BlackmanWindowFunction<WindowingRadius, double,
                                                       double>;
    using InterpolatorType = itk::WindowedSincInterpolateImageFunction<
        TImageType, WindowingRadius, WindowFunction, BoundaryCondition>;
    return RType(ConditionalCreateInterpolator<InterpolatorType>(
        typename IsBasic<TImageType>::Type()));
  }
  case sitkBSplineResamplerOrder1: {
    using InterpolatorType =
        typename itk::BSplineResampleImageFunction<TImageType, double>;
    typename InterpolatorType::Pointer p =
        ConditionalCreateInterpolator<InterpolatorType>(
            typename IsBasic<TImageType>::Type());
    p->SetSplineOrder(1);
    return RType(p);
  }
  case sitkBSplineResamplerOrder2: {
    using InterpolatorType =
        typename itk::BSplineResampleImageFunction<TImageType, double>;
    typename InterpolatorType::Pointer p =
        ConditionalCreateInterpolator<InterpolatorType>(
            typename IsBasic<TImageType>::Type());
    p->SetSplineOrder(2);
    return RType(p);
  }
  case sitkBSplineResamplerOrder3:
    // sitkBSplineResampler
    {
      using InterpolatorType =
          typename itk::BSplineResampleImageFunction<TImageType, double>;
      typename InterpolatorType::Pointer p =
          ConditionalCreateInterpolator<InterpolatorType>(
              typename IsBasic<TImageType>::Type());
      p->SetSplineOrder(3);
      return RType(p);
    }
  case sitkBSplineResamplerOrder4: {
    using InterpolatorType =
        typename itk::BSplineResampleImageFunction<TImageType, double>;
    typename InterpolatorType::Pointer p =
        ConditionalCreateInterpolator<InterpolatorType>(
            typename IsBasic<TImageType>::Type());
    p->SetSplineOrder(4);
    return RType(p);
  }
  case sitkBSplineResamplerOrder5: {
    using InterpolatorType =
        typename itk::BSplineResampleImageFunction<TImageType, double>;
    typename InterpolatorType::Pointer p =
        ConditionalCreateInterpolator<InterpolatorType>(
            typename IsBasic<TImageType>::Type());
    p->SetSplineOrder(5);
    return RType(p);
  }
  default:
    return nullptr;
  }
  return nullptr;
}

}
} // end namespace simple
} // end namespace itk


#endif // sitkCreateInterpolator_hxx
