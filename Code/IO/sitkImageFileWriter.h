#ifndef __sitkImageFileWriter_h
#define __sitkImageFileWriter_h

#include "sitkMacro.h"
#include "sitkImage.h"
#include "sitkMemberFunctionFactory.h"

namespace itk {
  namespace simple {

    class ImageFileWriter {
    public:
      typedef ImageFileWriter Self;

      // function pointer type
      typedef Self& (Self::*MemberFunctionType)( Image::Pointer );

      // list of pixel types supported
      typedef NonLabelPixelIDTypeList PixelIDTypeList;

      ImageFileWriter( void );

      Self& SetFileName ( std::string fn );
      std::string GetFileName();
      Self& Execute ( Image::Pointer );

    private:

      template <class T> Self& ExecuteInternal ( Image::Pointer );

      std::string m_FileName;

      // friend to get access to executeInternal member
      friend struct detail::MemberFunctionAddressor<MemberFunctionType>;

      std::auto_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;

    };
    void WriteImage ( Image::Pointer image, std::string filename );
  }
}

#endif
