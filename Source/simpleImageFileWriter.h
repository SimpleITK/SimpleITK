#ifndef __simpleImageFileWriter_h
#define __simpleImageFileWriter_h

#include <SimpleITKMacro.h>
#include <simpleImage.h>

namespace itk {
  namespace simple {

    class ImageFileWriter {
    public:
      typedef ImageFileWriter Self;
      Self& setFilename ( std::string fn );
      std::string getFilename();
      Self& execute ( Image::Pointer );
    private:
      template <class T> Self& executeInternal ( Image::Pointer );
      std::string mFilename;
    };

  }
}



#endif
