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
#ifndef sitkImageConvert_h
#define sitkImageConvert_h


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


template< class TPixelType, unsigned int NImageDimension, unsigned int NLength >
SITKCommon_HIDDEN
typename itk::VectorImage< TPixelType, NImageDimension >::Pointer
GetVectorImageFromImage( itk::Image< itk::Vector< TPixelType, NLength >, NImageDimension> *img, bool transferOwnership = false )
{
  typedef itk::VectorImage< TPixelType, NImageDimension > VectorImageType;

  size_t numberOfElements = img->GetBufferedRegion().GetNumberOfPixels();
  typename VectorImageType::InternalPixelType* buffer = reinterpret_cast<typename VectorImageType::InternalPixelType*>( img->GetPixelContainer()->GetBufferPointer() );

  // Unlike an image of Vectors a VectorImage's container is a
  // container of TPixelType, whos size is the image's number of
  // pixels * number of pixels per component
  numberOfElements *= NImageDimension;


  if (!img->GetPixelContainer()->GetContainerManageMemory())
    {
    transferOwnership=false;
    }


  typename VectorImageType::Pointer out = VectorImageType::New();

  // Set the image's pixel container to import the pointer provided.
  out->GetPixelContainer()->SetImportPointer(buffer, numberOfElements, transferOwnership );
  img->GetPixelContainer()->SetContainerManageMemory(!transferOwnership);
  out->CopyInformation( img );
  out->SetRegions( img->GetBufferedRegion() );

  return out;
}


template< class TPixelType, unsigned int NImageDimension >
SITKCommon_HIDDEN
typename itk::VectorImage< TPixelType, NImageDimension >::Pointer
GetVectorImageFromImage( itk::Image< itk::Vector< TPixelType, NImageDimension >, NImageDimension> *img, bool transferOwnership = false )
{
  return GetVectorImageFromImage<TPixelType,NImageDimension,NImageDimension>(img, transferOwnership);
}

}
}

#endif // sitkImageConvert_h
