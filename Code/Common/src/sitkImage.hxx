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
#include "sitkImageConvert.hxx"



namespace itk
{
  namespace simple
  {


  template <typename TImageType>
  PimpleImageBase *
  Image::DispatchedInternalInitialization(itk::DataObject * image)
  {
    return new PimpleImage<TImageType>(dynamic_cast<TImageType *>(image));
  }


  template <class TImageType>
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
    m_PimpleImage.reset(  new PimpleImage<TImageType>( image ) );
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

    m_PimpleImage.reset( new PimpleImage<TImageType>( image ) );
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

    m_PimpleImage.reset( new PimpleImage<TImageType>( image ) );
  }

  template <typename TImageType>
  std::enable_if_t<IsVector<TImageType>::Value, Image>
  Image::ToVectorInternal(bool)
  {
    return *this;
  }

  template <typename TImageType>
  std::enable_if_t<IsBasic<TImageType>::Value, Image>
  Image::ToVectorInternal(bool inPlace)
  {
    static_assert(TImageType::ImageDimension > 2, "Image dimension must be greater than 2");

    typename TImageType::Pointer itkImage;

    if (inPlace)
    {
      this->MakeUnique();
      itkImage = dynamic_cast<TImageType *>(this->m_PimpleImage->GetDataBase());
    }
    else
    {
      auto copy = this->m_PimpleImage->DeepCopy();
      itkImage = dynamic_cast<TImageType *>(copy->GetDataBase());
    }

    if (itkImage.GetPointer() == nullptr)
    {
      sitkExceptionMacro(<< "Unexpected template dispatch error");
    }


    auto direction = itkImage->GetDirection();
    for (unsigned int i = 1; i < TImageType::ImageDimension; ++i)
    {
      if (direction[i][0] != 0.0 || direction[0][i] != 0.0)
      {
        sitkExceptionMacro(<< "Cannot convert image with non-identity direction in first dimension to a vector image");
      }
    }
    if (direction[0][0] != 1.0)
    {
      sitkExceptionMacro(<< "Cannot convert image with non-identity direction in first dimension to a vector image");
    }

    auto itkVectorImage = GetVectorImageFromScalarImage(itkImage.GetPointer());

    itkImage = nullptr;
    using VectorImageType = typename decltype(itkVectorImage)::ObjectType;

    if (inPlace)
    {
      // The pimpleImage does not allow construction when the Image's PixelContainer has more than one reference. So
      // The pre-existing image must be destroyed before the new one is created.
      this->m_PimpleImage.reset();
      this->m_PimpleImage = std::make_unique<PimpleImage<VectorImageType>>(itkVectorImage);
      return *this;
    }
    else
    {
      return Image(std::make_unique<PimpleImage<VectorImageType>>(itkVectorImage));
    }
  }


  template <typename TImageType>
  std::enable_if_t<IsBasic<TImageType>::Value, Image>
  Image::ToScalarInternal(bool)
  {
    return *this;
  }

  template <typename TImageType>
  std::enable_if_t<IsVector<TImageType>::Value, Image>
  Image::ToScalarInternal(bool inPlace)
  {

    typename TImageType::Pointer itkImage;

    if (inPlace)
    {
      this->MakeUnique();
      itkImage = dynamic_cast<TImageType *>(this->m_PimpleImage->GetDataBase());
    }
    else
    {
      auto copy = this->m_PimpleImage->DeepCopy();
      itkImage = dynamic_cast<TImageType *>(copy->GetDataBase());
    }

    if (itkImage.GetPointer() == nullptr)
    {
      sitkExceptionMacro(<< "Unexpected template dispatch error");
    }

    auto itkScalarImage = GetScalarImageFromVectorImage(itkImage.GetPointer());
    itkImage = nullptr;
    using ScalarImageType = typename decltype(itkScalarImage)::ObjectType;

    if (inPlace)
    {
      this->m_PimpleImage.reset();
      this->m_PimpleImage = std::make_unique<PimpleImage<ScalarImageType>>(itkScalarImage);
      return *this;
    }
    else
    {
      return Image(std::make_unique<PimpleImage<ScalarImageType>>(itkScalarImage));
    }
  }


  } // namespace simple
} // namespace itk

#endif // sitkImage_h
