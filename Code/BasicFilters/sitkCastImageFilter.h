#ifndef __sitkCastImageFilter_h
#define __sitkCastImageFilter_h

#include "sitkImageFilter.h"

#include "sitkPixelIDTokens.h"

namespace itk {
  namespace simple {

    class CastImageFilter : ImageFilter {
    public:
      typedef CastImageFilter      Self;
      typedef BasicPixelIDTypeList PixelIDTypeList;

      Self& SetOutputPixelType( PixelIDValueType pixelID ) { this->m_OutputPixelType = pixelID; return *this; }
      PixelIDValueType GetOutputPixelType( void ) const { return this->m_OutputPixelType; }

      /**
       * Default Constructor that takes no arguments and initializes
       * default parameters
       */
      CastImageFilter();

      // Print ourselves out
      std::string ToString() const;

      Image::Pointer Execute ( Image::Pointer );

    private:

      PixelIDValueType m_OutputPixelType;

      // method to add instantiated token to function for conditional
      // instantiation of section image type
      template <typename TImageType, typename TOutputImageType>
      Image::Pointer ExecuteInternal ( typename TImageType::ConstPointer inImage )
        {
          return this->ConditionalExecuteInternal<TImageType, TOutputImageType>( inImage, ImageTypeToToken<TOutputImageType>::Token() );
        }

      // methods which utilizes the pixel id token type to
      // conditionally instatiate and execute the implementation
      template<typename TImageType, typename TOutputImageType>
      Image::Pointer ConditionalExecuteInternal(  typename TImageType::ConstPointer inImage, InstantiatedToken<true> );
      template<typename TImageType, typename TOutputImageType>
      Image::Pointer ConditionalExecuteInternal(  typename TImageType::ConstPointer inImage, InstantiatedToken<false> );


      typedef Image::Pointer (Self::*MemberFunctionType)( Image::Pointer );

      template <typename TImageType>
      Image::Pointer ExecuteInternal (  Image::Pointer image );

      friend struct detail::MemberFunctionAddressor<MemberFunctionType>;
      std::auto_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;

    };


  }
}
#endif
