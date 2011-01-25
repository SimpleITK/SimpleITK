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

      Self& SetFileName ( std::string fn );
      std::string GetFileName();
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
      typename EnableIf<IsInstantiated<TImageType>::Value, Image::Pointer >::Type
      ExecuteInternal ( );
      template <class TImageType>
      typename DisableIf<IsInstantiated<TImageType>::Value, Image::Pointer >::Type
      ExecuteInternal ( );

    private:

      std::string m_FileName;
    };

    Image::Pointer ReadImage ( std::string filename );

  }
}

#endif
