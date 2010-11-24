#ifndef __sitkRecursiveGaussianImageFilter_h
#define __sitkRecursiveGaussianImageFilter_h

#include "sitkImageFilter.h"

#include <itkRecursiveGaussianImageFilter.h>

namespace itk {
  namespace simple {

    class RecursiveGaussianImageFilter : ImageFilter {
    public:
      typedef RecursiveGaussianImageFilter Self;

      //
      // Type List Setup
      //

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
      Self& SetSigma ( double sigma );
      double GetSigma() const;

      /**
       * Get/Set NormalizeAcrossScale
       */
      Self& SetNormalizeAcrossScale( bool normalizeAcrossScale );
      bool GetNormalizeAcrossScale() const;

      /**
       * Get/Set Order
       */
      Self& SetOrder( OrderEnumType order );
      OrderEnumType GetOrder() const;

      // Print ourselves out
      std::string ToString() const;

      Image::Pointer Execute ( Image::Pointer );

    private:

      /** Sigma of the gaussian kernel. */
      double m_Sigma;

      /** Normalize the image across scale space */
      bool m_NormalizeAcrossScale;

      OrderEnumType m_Order;

      // function pointer type
      typedef Image::Pointer (Self::*MemberFunctionType)( Image::Pointer );

      template <class TImageType> Image::Pointer ExecuteInternal ( Image::Pointer image );

      // friend to get access to executeInternal member
      friend struct detail::MemberFunctionAddressor<MemberFunctionType>;


      std::auto_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;
    };


  }
}
#endif
