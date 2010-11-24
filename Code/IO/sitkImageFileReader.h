#ifndef __sitkImageFileReader_h
#define __sitkImageFileReader_h

#include "sitkMacro.h"
#include "sitkImage.h"
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

      template<unsigned int dim> Image::Pointer ExecuteInteralDimension ( itk::ImageIOBase *io );
      template <class T, unsigned int dimension> Image::Pointer ExecuteInternal ( void );

    private:

      std::string m_Filename;
    };

  }
}



#endif
