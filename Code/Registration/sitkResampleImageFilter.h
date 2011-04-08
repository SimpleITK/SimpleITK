#ifndef __sitkResampleImageFilter_h
#define __sitkResampleImageFilter_h

#include "sitkImage.h"
#include "sitkImageFilter.h"
#include "sitkInterpolate.h"
#include "sitkTransform.h"

namespace itk {
  namespace simple {

    /** \class ResampleImageFilter
     */
    class ResampleImageFilter : public ImageFilter
    {
    public:
      typedef ResampleImageFilter Self;

      /** Default Constructor that takes no arguments and initializes
       * default parameters */
      ResampleImageFilter();

      /** Define the pixels types supported by this filter */
      typedef BasicPixelIDTypeList  PixelIDTypeList;

      /** Name of this class */
      std::string GetName() const { return std::string ( "Resample"); }

      /** Print ourselves out */
      std::string ToString() const;

      /** Execute the filter on the input image */
      Image Execute ( const Image & );

      /** Execute the filter on the input image with the given parameters */
      // Image Execute ( const Image &, Transform );

      virtual Self& SetTransform ( Transform *transform );
      virtual Self& SetInterpolate ( Interpolate &interpolate );

      /** Resample parameters */
      Self& SetResampleParametersFromImage ( const Image& );
      Self& SetResampleOrigin ( std::vector<double> origin );
      Self& SetResampleSpacing ( std::vector<double> spacing );
      Self& SetResampleSize ( std::vector<uint32_t> size );
      Self& SetResampleDirection ( std::vector<std::vector<double> > direction );

    private:
      std::auto_ptr<Transform> m_Transform;
      std::auto_ptr<Interpolate> m_Interpolate;
      std::vector<double> m_Origin;
      std::vector<double> m_Spacing;
      std::vector<uint32_t> m_Size;
      std::vector<std::vector<double> > m_Direction;

      typedef Image (Self::*MemberFunctionType)( const Image & );
      template <class TImageType> Image ExecuteInternal ( const Image& image );

      /** Setup for member function dispatching */
      friend struct detail::MemberFunctionAddressor<MemberFunctionType>;
      std::auto_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;
    };

    /**
     * itk::simple::ResampleImageFilter Functional Interface
     *
     * This function directly calls the execute method of ResampleImageFilter
     * in order to support a fully functional API
     */
    Image Resample ( const Image& );
  }
}
#endif
