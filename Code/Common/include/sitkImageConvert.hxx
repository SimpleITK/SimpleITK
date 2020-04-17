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
#ifndef sitkImageConvert_hxx
#define sitkImageConvert_hxx

#include "sitkImageConvert.h"
#include "itkHolderCommand.h"

namespace itk
{

namespace simple
{


/** \brief A utility method to help convert between itk image types efficiently.
 *
 */
template< typename TPixelType, unsigned int ImageDimension >
SITKCommon_HIDDEN
typename itk::Image< itk::Vector< TPixelType, ImageDimension >, ImageDimension>::Pointer
GetImageFromVectorImage( itk::VectorImage< TPixelType, ImageDimension > *img, bool transferOwnership )
{
  using ImageType = itk::Image< itk::Vector< TPixelType, ImageDimension >, ImageDimension>;
  using VectorImageType = itk::VectorImage< TPixelType, ImageDimension >;

  // check number of element compatibility
  if ( img->GetNumberOfComponentsPerPixel() != VectorImageType::ImageDimension )
    {
    sitkExceptionMacro("Expected number of elements in vector image to be the same as the dimension!");
    }

  size_t numberOfElements = img->GetBufferedRegion().GetNumberOfPixels();
  typename ImageType::PixelType* buffer = reinterpret_cast<typename ImageType::PixelType*>( img->GetPixelContainer()->GetBufferPointer() );


  typename ImageType::Pointer out = ImageType::New();

  if (img->GetPixelContainer()->GetContainerManageMemory() && transferOwnership )
    {
    out->GetPixelContainer()->SetImportPointer(buffer, numberOfElements, true );
    img->GetPixelContainer()->ContainerManageMemoryOff();
    }
  else
    {
    auto holder = itk::HolderCommand<typename VectorImageType::PixelContainer::Pointer>::New();
    holder->Set( img->GetPixelContainer() );

    // Set the image's pixel container to import the pointer provided.
    out->GetPixelContainer()->SetImportPointer(buffer, numberOfElements, false );
    out->AddObserver( itk::DeleteEvent(), holder);
    }

  out->CopyInformation( img );
  out->SetRegions( img->GetBufferedRegion() );

  return out;

}


template< class TPixelType, unsigned int NImageDimension, unsigned int NLength >
SITKCommon_HIDDEN
typename itk::VectorImage< TPixelType, NImageDimension >::Pointer
GetVectorImageFromImage( itk::Image< itk::Vector< TPixelType, NLength >, NImageDimension> *img, bool transferOwnership )
{
  using VectorImageType = itk::VectorImage< TPixelType, NImageDimension >;
  using ImageType = itk::Image< itk::Vector< TPixelType, NLength >, NImageDimension>;

  size_t numberOfElements = img->GetBufferedRegion().GetNumberOfPixels();
  typename VectorImageType::InternalPixelType* buffer = reinterpret_cast<typename VectorImageType::InternalPixelType*>( img->GetPixelContainer()->GetBufferPointer() );

  // Unlike an image of Vectors a VectorImage's container is a
  // container of TPixelType, whos size is the image's number of
  // pixels * number of pixels per component
  numberOfElements *= NLength;


  typename VectorImageType::Pointer out = VectorImageType::New();

  if (img->GetPixelContainer()->GetContainerManageMemory() && transferOwnership)
    {
    out->GetPixelContainer()->SetImportPointer(buffer, numberOfElements, true );
    img->GetPixelContainer()->ContainerManageMemoryOff();
    }
  else
    {
    auto holder = itk::HolderCommand<typename ImageType::PixelContainer::Pointer>::New();
    holder->Set( typename ImageType::PixelContainer::Pointer(img->GetPixelContainer()) );

    // Set the image's pixel container to import the pointer provided.
    out->GetPixelContainer()->SetImportPointer(buffer, numberOfElements, false );
    out->AddObserver( itk::DeleteEvent(), holder);

    }


  out->CopyInformation( img );
  out->SetRegions( img->GetBufferedRegion() );

  assert(out->GetNumberOfComponentsPerPixel() == NLength);

  return out;
}


template< class TPixelType, unsigned int NImageDimension, unsigned int NLength >
SITKCommon_HIDDEN
typename itk::VectorImage< TPixelType, NImageDimension >::Pointer
GetVectorImageFromImage( itk::Image< itk::CovariantVector< TPixelType, NLength>, NImageDimension> *img, bool transferOwnership )
{
  using VectorImageType = itk::VectorImage< TPixelType, NImageDimension >;
  using ImageType = itk::Image< itk::CovariantVector< TPixelType, NLength >, NImageDimension>;

  size_t numberOfElements = img->GetBufferedRegion().GetNumberOfPixels();
  typename VectorImageType::InternalPixelType* buffer = reinterpret_cast<typename VectorImageType::InternalPixelType*>( img->GetPixelContainer()->GetBufferPointer() );

  // Unlike an image of Vectors a VectorImage's container is a
  // container of TPixelType, whos size is the image's number of
  // pixels * number of pixels per component
  numberOfElements *= NLength;


  typename VectorImageType::Pointer out = VectorImageType::New();

  if (img->GetPixelContainer()->GetContainerManageMemory() && transferOwnership)
    {
    out->GetPixelContainer()->SetImportPointer(buffer, numberOfElements, true );
    img->GetPixelContainer()->ContainerManageMemoryOff();
    }
  else
    {
    auto holder = itk::HolderCommand<typename ImageType::PixelContainer::Pointer>::New();
    holder->Set( typename ImageType::PixelContainer::Pointer(img->GetPixelContainer()) );

    // Set the image's pixel container to import the pointer provided.
    out->GetPixelContainer()->SetImportPointer(buffer, numberOfElements, false );
    out->AddObserver( itk::DeleteEvent(), holder);

    }


  out->CopyInformation( img );
  out->SetRegions( img->GetBufferedRegion() );

  assert(out->GetNumberOfComponentsPerPixel() == NLength);

  return out;
}


}
}

#endif // sitkImageConvert_hxx
