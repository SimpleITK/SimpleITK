#ifndef __simpleImageHash_h
#define __simpleImageHash_h

#include <SimpleITKMacro.h>
#include <simpleImage.h>

namespace itk {
  namespace simple {

    class ImageHash {
    public:
      typedef ImageHash Self;
   
      ImageHash();

      enum HashFunction { SHA1, MD5 };
      Self& setHashFunction ( HashFunction hashFunction );
      HashFunction getHashFunction ();

      // Print ourselves out
      std::string toString();

      std::string execute ( Image::Pointer );
    private:
      HashFunction mHashFunction;
      template <class T> std::string executeInternal ( Image::Pointer image );
    };


  }
}
#endif
