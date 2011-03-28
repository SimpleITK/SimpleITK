#ifndef __sitkExtractImageFilter_h
#define __sitkExtractImageFilter_h

#include "sitkImageFilter.h"

#include <itkExtractImageFilter.h>

#include <memory>

namespace itk {
  namespace simple {

    /** \class ExtractImageFilter
     * \brief Extract a slice from an image
     */
    class ExtractImageFilter : public ImageFilter {
    public:
      typedef ExtractImageFilter Self;

      // Type List Setup
      typedef NonLabelPixelIDTypeList PixelIDTypeList;

      /**
       * Default Constructor that takes no arguments and initializes
       * default parameters
       */
      ExtractImageFilter();

      Self& SetSlice ( size_t s ) { this->m_Slice = s; return *this; }
      size_t GetSlice() { return this->m_Slice; }

      Self& SetDimension ( size_t s ) { this->m_Dimension = s; return *this; }
      size_t GetDimension() { return this->m_Dimension; }

      /** Name of this class */
      std::string GetName() const { return std::string ( "Extract"); }

      // Print ourselves out
      std::string ToString() const;

      Image* Execute ( Image* );
      Image* Execute ( Image*, size_t s, size_t d );

    private:

      /** Slice to extract */
      size_t m_Slice;

      /** Dimesion along which to extract the slice */
      size_t m_Dimension;

      // Macro that instantiate the member function dispatching
      typedef Image* (Self::*MemberFunctionType)( Image* );
      template <class TImageType> Image* ExecuteInternal ( Image* image );
      friend struct detail::MemberFunctionAddressor<MemberFunctionType>;
      std::auto_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;
    };
    Image* Extract ( Image*, size_t s, size_t d );
  }
}
#endif
