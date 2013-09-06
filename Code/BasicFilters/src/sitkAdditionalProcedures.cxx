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

#include "sitkAdditionalProcedures.h"
#include "sitkResampleImageFilter.h"

namespace itk {
namespace simple {

//
// Function to run the Execute method of this filter after custom
// setting the parameters.
//

SITKBasicFilters_EXPORT Image Resample ( const Image& image1,
                                         Transform transform,
                                         InterpolatorEnum interpolator,
                                         double defaultPixelValue,
                                         PixelIDValueEnum outputPixelType )
{
  ResampleImageFilter filter;
  filter.SetReferenceImage( image1 );
  filter.SetTransform( transform );
  filter.SetInterpolator( interpolator );
  filter.SetDefaultPixelValue( defaultPixelValue );
  filter.SetOutputPixelType(outputPixelType);
  return filter.Execute ( image1);
}

Image Resample ( const Image& image1,
                 const Image& referenceImage,
                 Transform transform,
                 InterpolatorEnum interpolator,
                 double defaultPixelValue,
                 PixelIDValueEnum outputPixelType )
{
  ResampleImageFilter filter;
  filter.SetReferenceImage( referenceImage );
  filter.SetTransform( transform );
  filter.SetInterpolator( interpolator );
  filter.SetDefaultPixelValue( defaultPixelValue );
  filter.SetOutputPixelType(outputPixelType);
  return filter.Execute ( image1);
}


SITKBasicFilters_EXPORT Image Resample ( const Image& image1,
                                         std::vector<uint32_t> size,
                                         Transform transform,
                                         InterpolatorEnum interpolator,
                                         std::vector<double> outputOrigin,
                                         std::vector<double> outputSpacing,
                                         std::vector<double> outputDirection,
                                         double defaultPixelValue,
                                         PixelIDValueEnum outputPixelType )
{
  ResampleImageFilter filter;
  return filter.Execute ( image1, size, transform, interpolator, outputOrigin, outputSpacing, outputDirection, defaultPixelValue, outputPixelType );
}

}
}
