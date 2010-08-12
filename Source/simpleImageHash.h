#ifndef __simpleImageHash_h
#define __simpleImageHash_h

#include <SimpleITKMacro.h>
#include <simpleImage.h>

namespace itk {
  namespace simple {

    class ImageHash {
    public:
      typedef ImageHash Self;
   
      // function pointer type
      typedef std::string (Self::*MemberFunctionType)( ImageBase::Pointer );

      ImageHash();

      enum HashFunction { SHA1, MD5 };
      Self& setHashFunction ( HashFunction hashFunction );
      HashFunction getHashFunction ();

      // Print ourselves out
      std::string toString();

      std::string execute ( ImageBase::Pointer );

      template <class T> std::string executeInternal ( ImageBase::Pointer image );

    private:
      HashFunction mHashFunction;



      // list of pixel types supported (not  sure what this would
      // actually work with)
      typedef BasicPixelTypeList PixelTypeList;

      // array of pointers to member functions
      MemberFunctionType  m_PFunction[ typelist::Length< InstantiatedPixelTypeList >::Result ];
    };


  }
}
#endif
