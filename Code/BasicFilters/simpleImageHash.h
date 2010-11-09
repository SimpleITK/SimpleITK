#ifndef __simpleImageHash_h
#define __simpleImageHash_h

#include "SimpleITKMacro.h"
#include "simpleITKDetail.h"
#include "simpleImage.h"

namespace itk {
  namespace simple {

    class ImageHash {
    public:
      typedef ImageHash Self;
   
      // function pointer type
      typedef std::string (Self::*MemberFunctionType)( Image::Pointer );

      // list of pixel types supported (not  sure what this would
      // actually work with)
      typedef BasicPixelTypeList PixelTypeList;



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

      // friend to get access to executeInternal member
      friend class detail::PFuncArrayInitializer<Self>;

      detail::MemberFunctionFactory<Self> m_MemberFactory;
    };


  }
}
#endif
