#ifndef __sitkCastImageFilter_h
#define __sitkCastImageFilter_h

#include "sitkImageFilter.h"

namespace itk {
  namespace simple {

    class CastImageFilter : ImageFilter {
    public:
      typedef CastImageFilter Self;
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

      template<typename TImageType, typename TOutputImageType>
      Image::Pointer ExecuteInternal(  typename TImageType::ConstPointer inImage );

      // Macro that instantiate the member function dispatching
      typedef Image::Pointer (Self::*MemberFunctionType)( Image::Pointer );
      template <class TImageType> Image::Pointer ExecuteInternal ( Image::Pointer image );
      friend struct detail::MemberFunctionAddressor<MemberFunctionType>;
      std::auto_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;
    };


  }
}
#endif
