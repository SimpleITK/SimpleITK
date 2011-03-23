#ifndef __sitkHashImageFilter_h
#define __sitkHashImageFilter_h

#include "sitkMacro.h"
#include "sitkMemberFunctionFactory.h"
#include "sitkImage.h"

namespace itk {
  namespace simple {

    /** \class HashImageFilter
     * \brief Compute the sha1 or md5 hash of an image
     */
    class HashImageFilter {
    public:
      typedef HashImageFilter Self;

      // function pointer type
      typedef std::string (Self::*MemberFunctionType)( const Image& );

      // this filter works with all itk::Image and itk::VectorImage types.
      typedef typelist::Append<
        typelist::Append< BasicPixelIDTypeList, ComplexPixelIDTypeList>::Type,
        VectorPixelIDTypeList >::Type PixelIDTypeList;

      HashImageFilter();

      enum HashFunction { SHA1, MD5 };
      Self& SetHashFunction ( HashFunction hashFunction );
      HashFunction GetHashFunction ();

      // Print ourselves out
      std::string ToString() const;

      std::string Execute ( const Image& );


    private:
      HashFunction m_HashFunction;

      template <class TImageType> std::string ExecuteInternal ( const Image& image );

      // friend to get access to executeInternal member
      friend struct detail::MemberFunctionAddressor<MemberFunctionType>;

      std::auto_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;
    };

    std::string Hash ( const Image& image, HashImageFilter::HashFunction function = HashImageFilter::SHA1 );
  }
}
#endif
