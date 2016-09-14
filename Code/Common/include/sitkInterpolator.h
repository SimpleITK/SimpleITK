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
#ifndef sitkInterpolator_h
#define sitkInterpolator_h

#include "sitkCommon.h"
#include <ostream>


namespace itk
{
namespace simple
{

enum InterpolatorEnum {
  /** \brief Nearest-neighbor interpolation
   * \sa itk::NearestNeighborInterpolateImageFunction
   */
  sitkNearestNeighbor = 1,

  /** \brief N-D linear interpolation
   * \sa itk::LinearInterpolateImageFunction
   */
  sitkLinear = 2,

  /** \brief B-Spline of order 3 interpolation
   * \sa itk::BSplineInterpolateImageFunction
   */
  sitkBSpline = 3,

  /** \brief Gaussian interpolation
   *
   * Sigma is set to 0.8 input pixels and alpha is 4.0
   *
   * \sa itk::GaussianInterpolateImageFunction
   */
  sitkGaussian = 4,

  /** \brief Smoothly interpolate multi-label images
   *
   * Sigma is set to 1.0 input pixels and alpha is 1.0
   *
   * \sa itk:LabelImageGaussianInterpolateImageFunction
   */
  sitkLabelGaussian = 5,

  /** \brief Windowed sinc interpolation
   *
   * \f[ w(x) = 0.54 + 0.46 cos(\frac{\pi x}{m} ) \f]
   *
   * \sa itk::WindowedSincInterpolateImageFunction
   * \sa itk::Function::HammingWindowFunction
   */
  sitkHammingWindowedSinc = 6,

  /** \brief Windowed sinc interpolation
   *
   * \f[ w(x) = cos(\frac{\pi x}{2 m} ) \f]
   *
   * \sa itk::WindowedSincInterpolateImageFunction
   * \sa itk::Function::CosineWindowFunction
   */
  sitkCosineWindowedSinc = 7,

  /** \brief Windowed sinc interpolation
   *
   * \f[ w(x) = 1 - ( \frac{x^2}{m^2} ) \f]
   *
   * \sa itk::WindowedSincInterpolateImageFunction
   * \sa itk::Function::WelchWindowFunction
   */
  sitkWelchWindowedSinc = 8,

  /** \brief Windowed sinc interpolation
   *
   * \f[ w(x) = \textrm{sinc} ( \frac{x}{m} ) \f]
   *
   * \sa itk::WindowedSincInterpolateImageFunction
   * \sa itk::Function::LanczosWindowFunction
   */
  sitkLanczosWindowedSinc = 9,

  /** \brief Windowed sinc interpolation
   *
   * \f[ w(x) = 0.42 + 0.5 cos(\frac{\pi x}{m}) + 0.08 cos(\frac{2 \pi x}{m}) \f]
   *
   * \sa itk::WindowedSincInterpolateImageFunction
   * \sa itk::Function::BlackmanWindowFunction
   */
  sitkBlackmanWindowedSinc = 10
};

#ifndef SWIG
/**
 * Convert Interpolator enum to a string for printing etc..
 */
SITKCommon_EXPORT std::ostream& operator<<(std::ostream& os, const InterpolatorEnum i);
#endif

} // end namespace simple
} // end namespace itk


#endif // sitkInterpolator_h
