#ifndef __sitkImageFileWriter_h
#define __sitkImageFileWriter_h

#include "sitkMacro.h"
#include "sitkMemberFunctionFactory.h"
#include "sitkImage.h"

namespace itk {
  namespace simple {

    class ImageFileWriter {
    public:
      typedef ImageFileWriter Self;

      // function pointer type
      typedef Self& (Self::*MemberFunctionType)( Image::Pointer );

      // list of pixel types supported
      typedef BasicPixelTypeList PixelTypeList;

      ImageFileWriter( void );

      Self& SetFilename ( std::string fn );
      std::string GetFilename();
      Self& Execute ( Image::Pointer );

    private:

      template <class T> Self& ExecuteInternal ( Image::Pointer );

      std::string m_Filename;

      // friend to get access to executeInternal member 
      friend struct detail::MemberFunctionAddressor<Self, MemberFunctionType>;

      std::auto_ptr<detail::MemberFunctionFactory<Self> > m_MemberFactory;

    };

  }
}



#endif
