#ifndef __sitkImageFileReader_h
#define __sitkImageFileReader_h

#include "sitkMacro.h"
#include "sitkImage.h"

#include "sitkPixelIDTokens.h"

#include "itkImageIOBase.h"

namespace itk {
  namespace simple {

    /** \class ImageFileReader
     * \brief Read a 2D or 3D image and return a smart pointer to a SimpleITK
     * image
     *
     * This reader handles scalar and vector images and returns an image with
     * the same type as the file on disk.
     */
    class ImageFileReader {
    public:
      typedef ImageFileReader Self;

      Self& SetFileName ( std::string fn );
      std::string GetFileName();
      Image* Execute();
      typedef Image* (Self::*MemberFunctionType)( Image* );

    protected:

      template < unsigned int VImageDimension >
      Image* ExecuteInternalReadScalar( itk::ImageIOBase::IOComponentType componentType );

      template < unsigned int VImageDimension >
      Image* ExecuteInternalReadVector( itk::ImageIOBase::IOComponentType componentType );

      // methods which utlize the EnableIf idiom to conditionally
      // instatiate ad execute the implementation
      template <class TImageType>
      typename EnableIf<IsInstantiated<TImageType>::Value, Image* >::Type
      ExecuteInternal ( );
      template <class TImageType>
      typename DisableIf<IsInstantiated<TImageType>::Value, Image* >::Type
      ExecuteInternal ( );

    private:

      std::string m_FileName;
    };
    Image* ReadImage ( std::string filename );
  }
}

#endif
