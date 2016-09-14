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

  // this is a little specialization just to get the
  // InternalInitialization method's PixelIDTpImageType lookup to get
  // a valid void type, so it'll dispatch to the a specialized
  // method. All this is just to instantiate something that will never
  // be actually used.
  template <unsigned int VImageDimension>
  struct PixelIDToImageType< typelist::NullType , VImageDimension >
  {
    typedef void ImageType;
  };

  // This method is explicitly instantiated, and in-turn implicitly
  // instantates the PipleImage for all used image types. This method
  // just dispatces to nother method, to aid in instantiating only the
  // images requested.
  template <int VPixelIDValue, unsigned int VImageDimension>
  void Image::InternalInitialization( typename PixelIDToImageType<typename typelist::TypeAt<InstantiatedPixelIDTypeList,
                                                                                            VPixelIDValue>::Result,
                                                                  VImageDimension>::ImageType *i )
  {
    this->ConditionalInternalInitialization<VPixelIDValue>( i );
  }

  template<int VPixelIDValue, typename TImageType>
  typename DisableIf<nsstd::is_same<TImageType, void>::value>::Type
  Image::ConditionalInternalInitialization( TImageType *image )
  {
    // no need to check if null
    delete this->m_PimpleImage;
    this->m_PimpleImage = NULL;

    this->m_PimpleImage = new PimpleImage<TImageType>( image );
  }


  template<class TImageType>
  typename EnableIf<IsBasic<TImageType>::Value>::Type
  Image::AllocateInternal ( unsigned int Width, unsigned int Height, unsigned int Depth, unsigned int dim4, unsigned int numberOfComponents )
  {
    if ( numberOfComponents != 1  && numberOfComponents != 0 )
      {
      sitkExceptionMacro( "Specified number of components as " << numberOfComponents
                          << " but did not specify pixelID as a vector type!" );
      }

    typename TImageType::IndexType  index;
    typename TImageType::SizeType   size;
    typename TImageType::RegionType region;

    index.Fill ( 0 );
    size.Fill(1);
    size[0] = Width;
    size[1] = Height;

    if ( TImageType::ImageDimension > 2 )
      {
      assert( Depth != 0 );
      size[2] = Depth;
      }

    if ( TImageType::ImageDimension > 3 )
      {
      assert(  dim4 != 0 );
      size[3] =  dim4;
      }

    region.SetSize ( size );
    region.SetIndex ( index );

    typename TImageType::Pointer image = TImageType::New();
    image->SetRegions ( region );
    image->Allocate();
    image->FillBuffer ( itk::NumericTraits<typename TImageType::PixelType>::Zero );

    delete this->m_PimpleImage;
    this->m_PimpleImage = NULL;
    m_PimpleImage =  new PimpleImage<TImageType>( image );
  }

  template<class TImageType>
  typename EnableIf<IsVector<TImageType>::Value>::Type
  Image::AllocateInternal ( unsigned int Width, unsigned int Height, unsigned int Depth, unsigned int dim4, unsigned int numberOfComponents )
  {
    if ( numberOfComponents == 0 )
      {
      numberOfComponents = TImageType::ImageDimension;
      }

    typename TImageType::IndexType  index;
    typename TImageType::SizeType   size;
    typename TImageType::RegionType region;
    typename TImageType::PixelType  zero;

    index.Fill ( 0 );
    size.Fill(1);
    size[0] = Width;
    size[1] = Height;

    if ( TImageType::ImageDimension > 2 )
      {
      assert( Depth != 0 );
      size[2] = Depth;
      }

    if ( TImageType::ImageDimension > 3 )
      {
      assert(  dim4 != 0 );
      size[3] =  dim4;
      }

    region.SetSize ( size );
    region.SetIndex ( index );

    zero.SetSize( numberOfComponents );
    zero.Fill ( itk::NumericTraits<typename TImageType::PixelType::ValueType>::Zero );

    typename TImageType::Pointer image = TImageType::New();
    image->SetRegions ( region );
    image->SetVectorLength( numberOfComponents );
    image->Allocate();
    image->FillBuffer ( zero );

    delete this->m_PimpleImage;
    this->m_PimpleImage = NULL;

    m_PimpleImage = new PimpleImage<TImageType>( image );
  }

  template<class TImageType>
  typename EnableIf<IsLabel<TImageType>::Value>::Type
  Image::AllocateInternal ( unsigned int Width, unsigned int Height, unsigned int Depth, unsigned int dim4, unsigned int numberOfComponents )
  {
    if ( numberOfComponents != 1 && numberOfComponents != 0 )
      {
      sitkExceptionMacro( "Specified number of components as " << numberOfComponents
                          << " but did not specify pixelID as a vector type!" );
      }

    typename TImageType::IndexType  index;
    typename TImageType::SizeType   size;
    typename TImageType::RegionType region;

    index.Fill ( 0 );
    size.Fill(1);
    size[0] = Width;
    size[1] = Height;

    if ( TImageType::ImageDimension > 2 )
      {
      assert( Depth != 0 );
      size[2] = Depth;
      }

    if ( TImageType::ImageDimension > 3 )
      {
      assert(  dim4 != 0 );
      size[3] =  dim4;
      }

    region.SetSize ( size );
    region.SetIndex ( index );

    typename TImageType::Pointer image = TImageType::New();
    image->SetRegions ( region );
    image->Allocate();
    image->SetBackgroundValue( 0 );

    delete this->m_PimpleImage;
    this->m_PimpleImage = NULL;

    m_PimpleImage = new PimpleImage<TImageType>( image );
  }

  }
}

#endif // sitkImage_h
