#ifndef __sitkExtractImageFilter_h
#define __sitkExtractImageFilter_h

#include "sitkImageFilter.h"

#include <itkExtractImageFilter.h>

namespace itk {
  namespace simple {

    class ExtractImageFilter : public ImageFilter {
    public:
      typedef ExtractImageFilter Self;

      // Type List Setup
      typedef AllPixelIDTypeList PixelIDTypeList;

      /**
       * Default Constructor that takes no arguments and initializes
       * default parameters
       */
      ExtractImageFilter();

      Self& SetSlice ( size_t s ) { this->m_Slice = s; return *this; }
      size_t GetSlice() { return this->m_Slice; };

      // Print ourselves out
      std::string ToString() const;

      Image::Pointer Execute ( Image::Pointer );
      Image::Pointer Execute ( Image::Pointer, size_t s );

    private:

      /** Slice to extract */
      size_t m_Slice;

      // Macro that instantiate the member function dispatching
      typedef Image::Pointer (Self::*MemberFunctionType)( Image::Pointer );
      template <class TImageType> Image::Pointer ExecuteInternal ( Image::Pointer image );
      friend struct detail::MemberFunctionAddressor<MemberFunctionType>;
      std::auto_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;
    };
  }
}
#endif
