#ifndef __simpleCastImageFilter_h
#define __simpleCastImageFilter_h

#include <SimpleITKMacro.h>
#include <simpleImage.h>

namespace itk {
  namespace simple {

    class CastImageFilter {
    public:
      CastImageFilter();

      // Print ourselves out
      std::string toString();

      CastImageFilter& setOutputDataType ( ImageDataType );
      ImageDataType getOutputDataType();

      Image::Pointer execute ( Image::Pointer );
    private:
      ImageDataType mImageDataType;
      template <class TInput> Image::Pointer executeInternalOne ( Image::Pointer image );
      template <class TInput, class TOutput> Image::Pointer executeInternalTwo ( Image::Pointer image );
    };


  }
}
#endif
