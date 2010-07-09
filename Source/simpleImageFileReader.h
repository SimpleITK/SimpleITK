#ifndef __simpleImageFileReader_h
#define __simpleImageFileReader_h

#include <SimpleITKMacro.h>
#include <simpleImage.h>

namespace itk {
  namespace simple {

    class ImageFileReader {
    public:
      typedef ImageFileReader Self;
      Self& setFilename ( std::string fn );
      std::string getFilename();
      Image::Pointer execute();
    private:
      template <class T> Image::Pointer executeInternal ( ImageDataType datatype );
      std::string mFilename;
    };

  }
}



#endif
