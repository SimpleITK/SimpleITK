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
#ifndef __sitkImageConvert_h
#define __sitkImageConvert_h


namespace itk
{

template< typename T, unsigned int NVectorDimension > class Vector;

namespace simple
{


/** \brief A utility method to help convert between itk image types efficiently.
 *
 */
template< typename TPixelType, unsigned int ImageDimension >
SITKCommon_HIDDEN
typename itk::Image< itk::Vector< TPixelType, ImageDimension >, ImageDimension>::Pointer
GetImageFromVectorImage( itk::VectorImage< TPixelType, ImageDimension > *img, bool transferOwnership = false )
{
  typedef itk::Image< itk::Vector< TPixelType, ImageDimension >, ImageDimension> ImageType;
  typedef itk::VectorImage< TPixelType, ImageDimension > VectorImageType;

  // check number of element compatibility
  if ( img->GetNumberOfComponentsPerPixel() != VectorImageType::ImageDimension )
    {
    sitkExceptionMacro("Expected number of elements in vector image to be the same as the dimension!");
    }

  size_t numberOfElements = img->GetBufferedRegion().GetNumberOfPixels();
  typename ImageType::PixelType* buffer = reinterpret_cast<typename ImageType::PixelType*>( img->GetPixelContainer()->GetBufferPointer() );

  if (!img->GetPixelContainer()->GetContainerManageMemory())
    {
    transferOwnership=false;
    }

  typename ImageType::Pointer out = ImageType::New();

  out->CopyInformation( img );
  out->SetRegions( img->GetBufferedRegion() );

  // Set the image's pixel container to import the pointer provided.
  out->GetPixelContainer()->SetImportPointer(buffer, numberOfElements, transferOwnership );
  img->GetPixelContainer()->SetContainerManageMemory(!transferOwnership);

  return out;

}

}
}

#endif // __sitkImageConvert_h
