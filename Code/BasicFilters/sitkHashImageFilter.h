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
      typedef std::string (Self::*MemberFunctionType)( Image* );

      // this filter works with all itk::Image and itk::VectorImage types.
      typedef typelist::Append<
        typelist::Append< BasicPixelIDTypeList, ComplexPixelIDTypeList>::Type,
        VectorPixelIDTypeList >::Type PixelIDTypeList;

      HashImageFilter();

      enum HashFunction { SHA1, MD5 };
      Self& SetHashFunction ( HashFunction hashFunction );
      HashFunction GetHashFunction ();

      /** Name of this class */
      std::string GetName() const { return std::string ( "Hash"); }

      // Print ourselves out
      std::string ToString() const;

      std::string Execute ( Image* );


    private:
      HashFunction m_HashFunction;

      template <class TImageType> std::string ExecuteInternal ( Image* image );

      // friend to get access to executeInternal member
      friend struct detail::MemberFunctionAddressor<MemberFunctionType>;

      std::auto_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;
    };

    std::string Hash ( Image* image, HashImageFilter::HashFunction function = HashImageFilter::SHA1 );
  }
}
#endif
