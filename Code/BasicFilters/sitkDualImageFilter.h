#ifndef __sitkDualImageFilter_h
#define __sitkDualImageFilter_h

#include "sitkImageFilter.h"

#define sitkDualImageMemberFunctionDispatcher \
typedef Image::Pointer (Self::*MemberFunctionType)( Image::Pointer, Image::Pointer ); \
template <class TImageType> Image::Pointer ExecuteInternal ( Image::Pointer image1, Image::Pointer image2 ); \
friend struct detail::MemberFunctionAddressor<MemberFunctionType>; \
std::auto_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;


namespace itk {
  namespace simple {

    class DualImageFilter : public ImageFilter {
    public:
      typedef DualImageFilter Self;

      /**
       * Default Constructor that takes no arguments and initializes
       * default parameters
       */
      DualImageFilter();

      // Print ourselves out
      std::string ToString() const;

      Image::Pointer Execute ( Image::Pointer, Image::Pointer );

    private:

    };

  }
}
#endif
