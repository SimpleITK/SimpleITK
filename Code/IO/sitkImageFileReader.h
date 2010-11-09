#ifndef __sitkImageFileReader_h
#define __sitkImageFileReader_h

#include "sitkMacro.h"
#include "sitkImage.h"

namespace itk {
  namespace simple {

    class ImageFileReader {
    public:
      typedef ImageFileReader Self;

      typedef Image::Pointer (Self::*MemberFunctionType)( Image::Pointer );

      Self& SetFilename ( std::string fn );
      std::string GetFilename();
      Image::Pointer Execute();

    protected:

      template <class T> Image::Pointer ExecuteInternal ( void );

    private:

      std::string m_Filename;
    };

  }
}



#endif
