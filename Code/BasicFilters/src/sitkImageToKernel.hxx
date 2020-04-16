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
#ifndef sitkImageToKernel_hxx
#define sitkImageToKernel_hxx

#include <memory>
#include <itkImageKernelOperator.h>
#include <itkConstantPadImageFilter.h>

namespace itk {
namespace simple {


/** \brief Convert an itk Image to an itk ImageKernalOperator
 *
 * This method will internally pad the image with the
 * ConstantPadImageFilter, and then convert to an ImageKernalOperator
 * via a deep copy.
 *
 */
template<typename TImageType>
std::unique_ptr< ImageKernelOperator< typename TImageType::PixelType, TImageType::ImageDimension > >
CreateOperatorFromImage( const TImageType * image )
{
using KernelImagePixelType = typename TImageType::PixelType;
using KernelType = ImageKernelOperator< KernelImagePixelType, TImageType::ImageDimension >;
using KernelPointerType = std::unique_ptr<KernelType>;

using KernelSizeType = typename KernelType::SizeType;

KernelPointerType kernelOperator( new KernelType() );

bool kernelNeedsPadding = false;

using PadImageFilter = itk::ConstantPadImageFilter<TImageType,TImageType>;
typename PadImageFilter::Pointer padFilter = PadImageFilter::New();
padFilter->SetConstant( NumericTraits< KernelImagePixelType >::ZeroValue() );
typename TImageType::SizeType padSize = image->GetLargestPossibleRegion().GetSize();
for( unsigned int i = 0; i < TImageType::ImageDimension; ++i )
  {
  // Pad by 1 if the size of the image in this dimension is even.
  padSize[i] = 1 - padSize[i]%2;

  if ( padSize[i] != 0 )
    {
    kernelNeedsPadding = true;
    }
  }
padFilter->SetPadLowerBound(padSize);
padFilter->SetInput( image );

if ( kernelNeedsPadding )
  {
  padFilter->UpdateLargestPossibleRegion();
  image = padFilter->GetOutput();
  }

kernelOperator->SetImageKernel( image );

KernelSizeType radius;
for ( unsigned int i = 0; i < TImageType::ImageDimension; ++i )
  {
  radius[i] = image->GetLargestPossibleRegion().GetSize()[i]/2;
  }

kernelOperator->CreateToRadius( radius );

return kernelOperator;
}

} // end namespace simple
} // end namespace itk

#endif
