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
#ifndef sitkImage_hxx
#define sitkImage_hxx

#include "sitkImage.h"

#include "itkImage.h"
#include "itkVectorImage.h"
#include "itkLabelMap.h"
#include "itkLabelObject.h"

#include "sitkExceptionObject.h"
#include "sitkPimpleImageBase.hxx"
#include "sitkPixelIDTypeLists.h"


namespace itk
{
  namespace simple
  {

  // This method is explicitly instantiated, and in-turn implicitly
  // instantiates the PimpleImage for all used image types. This method
  // just dispatches to another method, to aid in instantiating only the
  // images requested.
  template <int VPixelIDValue, unsigned int VImageDimension>
  void Image::InternalInitialization( typename PixelIDToImageType<typename typelist2::type_at<InstantiatedPixelIDTypeList,
                                                                                            VPixelIDValue>::type,
                                                                  VImageDimension>::ImageType *image )
  {
    using ImageType =
      typename PixelIDToImageType<typename typelist2::type_at<InstantiatedPixelIDTypeList, VPixelIDValue>::type,
                                  VImageDimension>::ImageType;

    // no need to check if null
    delete this->m_PimpleImage;
    this->m_PimpleImage = nullptr;

    this->m_PimpleImage = new PimpleImage<ImageType>(image);
  }

  template<class TImageType>
  typename std::enable_if<IsBasic<TImageType>::Value>::type
  Image::AllocateInternal ( const std::vector<unsigned int > &_size, unsigned int numberOfComponents )
  {
    if ( numberOfComponents != 1  && numberOfComponents != 0 )
      {
      sitkExceptionMacro( "Specified number of components as " << numberOfComponents
                          << " but did not specify pixelID as a vector type!" );
      }

    typename TImageType::IndexType index;
    index.Fill ( 0 );

    typename TImageType::SizeType size = sitkSTLVectorToITK<typename TImageType::SizeType>(_size);

    typename TImageType::RegionType region{index, size};

    typename TImageType::Pointer image = TImageType::New();
    image->SetRegions ( region );
    image->Allocate();
    image->FillBuffer ( itk::NumericTraits<typename TImageType::PixelType>::ZeroValue() );

    delete this->m_PimpleImage;
    this->m_PimpleImage = nullptr;
    m_PimpleImage =  new PimpleImage<TImageType>( image );
  }

  template<class TImageType>
  typename std::enable_if<IsVector<TImageType>::Value>::type
  Image::AllocateInternal ( const std::vector<unsigned int > &_size, unsigned int numberOfComponents )
  {
    if ( numberOfComponents == 0 )
      {
      numberOfComponents = TImageType::ImageDimension;
      }

    typename TImageType::IndexType  index;
    index.Fill ( 0 );

    typename TImageType::SizeType   size = sitkSTLVectorToITK<typename TImageType::SizeType>(_size);

    typename TImageType::RegionType region{index, size};
    typename TImageType::PixelType  zero;

    zero.SetSize( numberOfComponents );
    zero.Fill ( itk::NumericTraits<typename TImageType::PixelType::ValueType>::Zero );

    typename TImageType::Pointer image = TImageType::New();
    image->SetRegions ( region );
    image->SetVectorLength( numberOfComponents );
    image->Allocate();
    image->FillBuffer ( zero );

    delete this->m_PimpleImage;
    this->m_PimpleImage = nullptr;

    m_PimpleImage = new PimpleImage<TImageType>( image );
  }

  template<class TImageType>
  typename std::enable_if<IsLabel<TImageType>::Value>::type
  Image::AllocateInternal ( const std::vector<unsigned int > &_size, unsigned int numberOfComponents )
  {
    if ( numberOfComponents != 1 && numberOfComponents != 0 )
      {
      sitkExceptionMacro( "Specified number of components as " << numberOfComponents
                          << " but did not specify pixelID as a vector type!" );
      }

    typename TImageType::IndexType index;
    index.Fill ( 0 );

    typename TImageType::SizeType size = sitkSTLVectorToITK<typename TImageType::SizeType>(_size);

    typename TImageType::RegionType region{index, size};

    typename TImageType::Pointer image = TImageType::New();
    image->SetRegions ( region );
    image->Allocate();
    image->SetBackgroundValue( 0 );

    delete this->m_PimpleImage;
    this->m_PimpleImage = nullptr;

    m_PimpleImage = new PimpleImage<TImageType>( image );
  }

  }
}

#endif // sitkImage_h
