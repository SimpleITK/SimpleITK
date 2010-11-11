#ifndef __sitkImageHashFilter_h
#define __sitkImageHashFilter_h

#include "sitkMacro.h"
#include "sitkDetail.h"
#include "sitkImage.h"

namespace itk {
  namespace simple {

    class ImageHashFilter {
    public:
      typedef ImageHashFilter Self;
   
      // function pointer type
      typedef std::string (Self::*MemberFunctionType)( Image::Pointer );

      // list of pixel types supported (not  sure what this would
      // actually work with)
      typedef BasicPixelTypeList PixelTypeList;



      ImageHashFilter();

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
      friend class detail::MemberFunctionAddressor<Self,MemberFunctionType>;

      std::auto_ptr<detail::MemberFunctionFactory<Self> > m_MemberFactory;
    };


  }
}
#endif
