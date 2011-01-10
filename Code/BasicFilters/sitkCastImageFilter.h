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

      // method utlized for instantiated pixel types utilizing
      // EnableIf SFINAE idom
      template<typename TImageType, typename TOutputImageType>
      typename EnableIf< IsInstantiated<TOutputImageType>::Value, Image::Pointer>::Type
      ExecuteInternal( const TImageType* inImage );

      // fall back methods which should never be called
      template<typename TImageType, typename TOutputImageType>
      Image::Pointer
      ExecuteInternal( ... );

      typedef Image::Pointer (Self::*MemberFunctionType)( Image::Pointer );

      template <typename TImageType>
      Image::Pointer ExecuteInternal (  Image::Pointer image );

      friend struct detail::MemberFunctionAddressor<MemberFunctionType>;
      std::auto_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;

    };


  }
}
#endif
