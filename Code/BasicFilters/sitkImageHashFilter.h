#ifndef __sitkImageHashFilter_h
#define __sitkImageHashFilter_h

#include "sitkMacro.h"
#include "sitkMemberFunctionFactory.h"
#include "sitkImage.h"

namespace itk {
  namespace simple {

    /** \class ImageHashFilter
     * \brief Compute the sha1 or md5 hash of an image
     */
    class ImageHashFilter {
    public:
      typedef ImageHashFilter Self;

      // function pointer type
      typedef std::string (Self::*MemberFunctionType)( Image::Pointer );

      // this filter works with all itk::Image and itk::VectorImage types.
      typedef typelist::Append<
        typelist::Append< BasicPixelIDTypeList, ComplexPixelIDTypeList>::Type,
        VectorPixelIDTypeList >::Type PixelIDTypeList;

      ImageHashFilter();

      enum HashFunction { SHA1, MD5 };
      Self& SetHashFunction ( HashFunction hashFunction );
      HashFunction GetHashFunction ();

      // Print ourselves out
      std::string ToString() const;

      std::string Execute ( Image::Pointer );


    private:
      HashFunction m_HashFunction;

      template <class TImageType> std::string ExecuteInternal ( Image::Pointer image );

      // friend to get access to executeInternal member
      friend struct detail::MemberFunctionAddressor<MemberFunctionType>;

      std::auto_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;
    };
  }
}
#endif
