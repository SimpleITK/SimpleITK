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

#include "sitkAdditionalProcedures.h"
#include "sitkResampleImageFilter.h"
#include "sitkPatchBasedDenoisingImageFilter.h"
#include "sitkDiscreteGaussianImageFilter.h"
#include "sitkSmoothingRecursiveGaussianImageFilter.h"

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
                                         PixelIDValueEnum outputPixelType,
                                         bool useNearestNeighborExtrapolator)
{
  ResampleImageFilter filter;
  filter.SetReferenceImage( image1 );
  filter.SetTransform( transform );
  filter.SetInterpolator( interpolator );
  filter.SetDefaultPixelValue( defaultPixelValue );
  filter.SetOutputPixelType(outputPixelType);
  filter.SetUseNearestNeighborExtrapolator(useNearestNeighborExtrapolator);
  return filter.Execute ( image1);
}

Image Resample ( const Image& image1,
                 const Image& referenceImage,
                 Transform transform,
                 InterpolatorEnum interpolator,
                 double defaultPixelValue,
                 PixelIDValueEnum outputPixelType,
                 bool useNearestNeighborExtrapolator)
{
  ResampleImageFilter filter;
  filter.SetReferenceImage( referenceImage );
  filter.SetTransform( transform );
  filter.SetInterpolator( interpolator );
  filter.SetDefaultPixelValue( defaultPixelValue );
  filter.SetOutputPixelType(outputPixelType);
  filter.SetUseNearestNeighborExtrapolator(useNearestNeighborExtrapolator);
  return filter.Execute ( image1);
}


SITKBasicFilters_EXPORT Image Resample ( const Image& image1,
                                         const std::vector<uint32_t> &size,
                                         Transform transform,
                                         InterpolatorEnum interpolator,
                                         const std::vector<double> &outputOrigin,
                                         const std::vector<double> &outputSpacing,
                                         const std::vector<double> &outputDirection,
                                         double defaultPixelValue,
                                         PixelIDValueEnum outputPixelType,
                                         bool useNearestNeighborExtrapolator)
{
  ResampleImageFilter filter;
  filter.SetSize(size);
  filter.SetTransform(transform);
  filter.SetInterpolator(interpolator);
  filter.SetOutputOrigin(outputOrigin);
  filter.SetOutputSpacing(outputSpacing);
  filter.SetOutputDirection(outputDirection);
  filter.SetDefaultPixelValue(defaultPixelValue);
  filter.SetOutputPixelType(outputPixelType);
  filter.SetUseNearestNeighborExtrapolator(useNearestNeighborExtrapolator);
  return filter.Execute ( image1 );
}

SITKBasicFilters_EXPORT Image PatchBasedDenoising (const Image& image1,
                                                   double kernelBandwidthSigma,
                                                   uint32_t patchRadius,
                                                   uint32_t numberOfIterations,
                                                   uint32_t numberOfSamplePatches,
                                                   double sampleVariance )
{
  PatchBasedDenoisingImageFilter filter;

  const PatchBasedDenoisingImageFilter::NoiseModelType noiseModel = itk::simple::PatchBasedDenoisingImageFilter::NOMODEL;
  const double noiseSigma = 0.0;
  const double noiseModelFidelityWeight = 0.0;
  //const bool alwaysTreatComponentsAsEuclidean = false;


  filter.KernelBandwidthEstimationOff();

  filter.SetKernelBandwidthSigma(kernelBandwidthSigma);
  filter.SetPatchRadius(patchRadius);
  filter.SetNumberOfIterations(numberOfIterations);
  filter.SetNumberOfSamplePatches(numberOfSamplePatches);
  filter.SetSampleVariance(sampleVariance);
  filter.SetNoiseModel(noiseModel);
  filter.SetNoiseSigma(noiseSigma);
  filter.SetNoiseModelFidelityWeight(noiseModelFidelityWeight);
  //filter.SetAlwaysTreatComponentsAsEuclidean(alwaysTreatComponentsAsEuclidean);
  return filter.Execute ( image1 );
}


SITKBasicFilters_EXPORT Image PatchBasedDenoising (const Image& image1,
                                                   PatchBasedDenoisingImageFilter::NoiseModelType noiseModel,
                                                   double kernelBandwidthSigma,
                                                   uint32_t patchRadius,
                                                   uint32_t numberOfIterations,
                                                   uint32_t numberOfSamplePatches,
                                                   double sampleVariance,
                                                   double noiseSigma,
                                                   double noiseModelFidelityWeight )
{
  PatchBasedDenoisingImageFilter filter;

  //const bool alwaysTreatComponentsAsEuclidean = false;

  filter.KernelBandwidthEstimationOff();

  filter.SetKernelBandwidthSigma(kernelBandwidthSigma);
  filter.SetPatchRadius(patchRadius);
  filter.SetNumberOfIterations(numberOfIterations);
  filter.SetNumberOfSamplePatches(numberOfSamplePatches);
  filter.SetSampleVariance(sampleVariance);
  filter.SetNoiseModel(noiseModel);
  filter.SetNoiseSigma(noiseSigma);
  filter.SetNoiseModelFidelityWeight(noiseModelFidelityWeight);
  //filter.SetAlwaysTreatComponentsAsEuclidean(alwaysTreatComponentsAsEuclidean);

  return filter.Execute ( image1 );
}


//
// Function to run the Execute method of this filter
//
Image DiscreteGaussian ( const Image& image1, double variance, unsigned int maximumKernelWidth, double maximumError, bool useImageSpacing )
{
  DiscreteGaussianImageFilter filter;
  filter.SetVariance(variance);
  filter.SetMaximumKernelWidth(maximumKernelWidth);
  filter.SetMaximumError(maximumError);
  filter.SetUseImageSpacing(useImageSpacing);
  return filter.Execute ( image1 );
}

//
// Function to run the Execute method of this filter
//
Image SmoothingRecursiveGaussian ( const Image& image1,
                                   double sigma,
                                   bool normalizeAcrossScale )
{
  SmoothingRecursiveGaussianImageFilter filter;
  filter.SetSigma(sigma);
  filter.SetNormalizeAcrossScale(normalizeAcrossScale);
  return filter.Execute(image1);
}


}
}
