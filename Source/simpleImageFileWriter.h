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
      typedef Self& (Self::*MemberFunctionType)( Image::Pointer );

      ImageFileWriter( void );

      Self& setFilename ( std::string fn );
      std::string getFilename();
      Self& execute ( Image::Pointer );

    private:

      template <class T> Self& executeInternal ( Image::Pointer );

      std::string mFilename;

      // list of pixel types supported
      typedef AllPixelTypeList PixelTypeList;

      // friend to get access to executeInternal member 
      friend class PFuncArrayInitializer<Self>;

      // array of pointers to member functions
      MemberFunctionType  m_PFunction[ typelist::Length< InstantiatedPixelTypeList >::Result ];
    };

  }
}



#endif
