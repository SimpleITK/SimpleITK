#ifndef __simpleImageFileWriter_h
#define __simpleImageFileWriter_h

#include <SimpleITKMacro.h>
#include <simpleImage.h>

namespace itk {
  namespace simple {

    class ImageFileWriter {
    public:
      typedef ImageFileWriter Self;

      // function pointer type
      typedef Self& (Self::*MemberFunctionType)( ImageBase::Pointer );

      ImageFileWriter( void );

      Self& setFilename ( std::string fn );
      std::string getFilename();
      Self& execute ( ImageBase::Pointer );

      template <class T> Self& executeInternal ( ImageBase::Pointer );
    private:
      std::string mFilename;

      // list of pixel types supported
      typedef AllPixelTypeList PixelTypeList;

      // array of pointers to member functions
      MemberFunctionType  m_CreateFunctions[ typelist::Length< InstantiatedPixelTypeList >::Result ];
    };

  }
}



#endif
