#ifndef __sitkImageFileReader_h
#define __sitkImageFileReader_h

#include "sitkMacro.h"
#include "sitkImage.h"

#include "sitkPixelIDTokens.h"

#include "itkImageIOBase.h"

namespace itk {
  namespace simple {


    class ImageFileReader {
    public:
      typedef ImageFileReader Self;

      Self& SetFilename ( std::string fn );
      std::string GetFilename();
      Image::Pointer Execute();
      typedef Image::Pointer (Self::*MemberFunctionType)( Image::Pointer );

    protected:

      template < unsigned int VImageDimension >
      Image::Pointer ExecuteInternalReadScalar( itk::ImageIOBase::IOComponentType componentType );

      template < unsigned int VImageDimension >
      Image::Pointer ExecuteInternalReadVector( itk::ImageIOBase::IOComponentType componentType );

      template <class TImageType> Image::Pointer ExecuteInternal ( )
        { return this->ConditionalExecuteInternal<TImageType>( ); }

      // methods which utlize the pixel id token type to conditionally
      // instatiate ad execute the implementation
      template <class TImageType>
      Image::Pointer
      ConditionalExecuteInternal ( typename EnableIf<IsInstantiated<typename ImageTypeToPixelID<TImageType>::PixelIDType>::Value >::Type*b = 0);
      template <class TImageType>
      Image::Pointer
      ConditionalExecuteInternal ( typename EnableIf<!IsInstantiated<typename ImageTypeToPixelID<TImageType>::PixelIDType>::Value >::Type*b = 0 );

    private:

      std::string m_Filename;
    };

  }
}

#endif
