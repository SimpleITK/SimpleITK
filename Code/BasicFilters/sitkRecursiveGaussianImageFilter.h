#ifndef __sitkRecursiveGaussianImageFilter_h
#define __sitkRecursiveGaussianImageFilter_h

#include "sitkImageFilter.h"

#include <itkRecursiveGaussianImageFilter.h>

namespace itk {
  namespace simple {

    /** \class RecursiveGaussianImageFilter
     * \brief This filter recursively applies a gaussian kernel to the image
     */
    class RecursiveGaussianImageFilter : public ImageFilter {
    public:
      typedef RecursiveGaussianImageFilter Self;

      //
      // Type List Setup
      //
      typedef BasicPixelIDTypeList PixelIDTypeList;

      //
      // Filter Setup
      //

      /**
       * Default Constructor that takes no arguments and initializes
       * default parameters
       */
      RecursiveGaussianImageFilter();

      /** Enum type that indicates if the filter applies the equivalent operation
          of convolving with a gaussian, first derivative of a gaussian or the
          second derivative of a gaussian.  */
      typedef  enum { ZeroOrder, FirstOrder, SecondOrder } OrderEnumType;

      /**
       * Get/Set Sigma
       *
       * Note: Sigma is always measured in physical units
       */
      Self& SetSigma ( double t ) { this->m_Sigma = t; return *this; }
      double GetSigma() { return this->m_Sigma; }

      /**
       * Get/Set NormalizeAcrossScale
       */
      Self& SetNormalizeAcrossScale ( bool t ) { this->m_NormalizeAcrossScale = t; return *this; }
      bool GetNormalizeAcrossScale() { return this->m_NormalizeAcrossScale; }

      /**
       * Get/Set Order
       */
      Self& SetOrder ( OrderEnumType t ) { this->m_Order = t; return *this; }
      OrderEnumType GetOrder() { return this->m_Order; }

      /**
       * Get/Set Direction
       */
      Self& SetDirection ( unsigned int t ) { this->m_Direction = t; return *this; }
      unsigned int GetDirection() { return this->m_Direction; }


      // Print ourselves out
      std::string ToString() const;

      Image::Pointer Execute ( Image::Pointer );

    private:

      /** Sigma of the gaussian kernel. */
      double m_Sigma;

      /** Normalize the image across scale space */
      bool m_NormalizeAcrossScale;

      /** Direction the filter should be applied in */
      unsigned int m_Direction;

      OrderEnumType m_Order;

      // Macro that instantiate the member function dispatching
      typedef Image::Pointer (Self::*MemberFunctionType)( Image::Pointer );
      template <class TImageType> Image::Pointer ExecuteInternal ( Image::Pointer image );
      friend struct detail::MemberFunctionAddressor<MemberFunctionType>;
      std::auto_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;

    };

    Image::Pointer RecursiveGaussian ( Image::Pointer image,
      double Sigma = 1.0,
      bool NormalizeAcrossScale = false,
      RecursiveGaussianImageFilter::OrderEnumType order = RecursiveGaussianImageFilter::ZeroOrder,
      unsigned int Direction = 0 );
  }
}
#endif
