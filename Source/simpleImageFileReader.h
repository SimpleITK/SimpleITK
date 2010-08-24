#ifndef __simpleImageFileReader_h
#define __simpleImageFileReader_h

#include <SimpleITKMacro.h>
#include <simpleImage.h>

namespace itk {
  namespace simple {

    class ImageFileReader {
    public:
      typedef ImageFileReader Self;

      typedef Image::Pointer (Self::*MemberFunctionType)( Image::Pointer );

      Self& setFilename ( std::string fn );
      std::string getFilename();
      Image::Pointer execute();

      template <class T> Image::Pointer executeInternal ( void );

    private:

      std::string mFilename;
    };

  }
}



#endif
