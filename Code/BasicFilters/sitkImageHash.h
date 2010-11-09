#ifndef __sitkImageHash_h
#define __sitkImageHash_h

#include "sitkMacro.h"
#include "sitkDetail.h"
#include "sitkImage.h"

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
      Self& SetHashFunction ( HashFunction hashFunction );
      HashFunction GetHashFunction ();

      // Print ourselves out
      std::string ToString();

      std::string Execute ( Image::Pointer );


    private:
      HashFunction m_HashFunction;

      template <class T> std::string ExecuteInternal ( Image::Pointer image );

      // friend to get access to executeInternal member
      friend class detail::PFuncArrayInitializer<Self>;

      detail::MemberFunctionFactory<Self> m_MemberFactory;
    };


  }
}
#endif
