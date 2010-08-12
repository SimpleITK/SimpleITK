#ifndef __simpleImageFileReader_h
#define __simpleImageFileReader_h

#include <SimpleITKMacro.h>
#include <simpleImage.h>

namespace itk {
  namespace simple {

    class ImageFileReader {
    public:
      typedef ImageFileReader Self;

      typedef ImageBase::Pointer (Self::*MemberFunctionType)( ImageBase::Pointer );

      Self& setFilename ( std::string fn );
      std::string getFilename();
      ImageBase::Pointer execute();

      template <class T> ImageBase::Pointer executeInternal ( ImageDataType datatype );

    private:

      std::string mFilename;
    };

  }
}



#endif
