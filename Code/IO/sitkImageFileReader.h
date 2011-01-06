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

      // methods which utlize the EnableIf idiom to conditionally
      // instatiate ad execute the implementation
      template <class TImageType>
      typename EnableIf<IsInstantiated<typename ImageTypeToPixelID<TImageType>::PixelIDType>::Value, Image::Pointer >::Type
      ExecuteInternal ( );
      template <class TImageType>
      typename DisableIf<IsInstantiated<typename ImageTypeToPixelID<TImageType>::PixelIDType>::Value, Image::Pointer >::Type
      ExecuteInternal ( );

    private:

      std::string m_Filename;
    };

  }
}

#endif
