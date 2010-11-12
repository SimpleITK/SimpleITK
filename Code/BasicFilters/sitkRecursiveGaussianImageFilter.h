#ifndef __sitkRecursiveGaussianImageFilter_h
#define __sitkRecursiveGaussianImageFilter_h

#include "sitkMacro.h"
#include "sitkMemberFunctionFactory.h"
#include "sitkImage.h"


#include <itkRecursiveGaussianImageFilter.h>

namespace itk {
  namespace simple {

    class RecursiveGaussianImageFilter {
    public:
      typedef RecursiveGaussianImageFilter Self;

      //
      // Type List Setup
      //
      
      // function pointer type
      typedef Image::Pointer (Self::*MemberFunctionType)( Image::Pointer );

      // list of pixel types supported only basic since rgb and
      // vectors are not supported by this filter
      typedef BasicPixelTypeList PixelTypeList;


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
      double GetSigma();

      /**
       * Get/Set NormalizeAcrossScale
       */
      Self& SetNormalizeAcrossScale( bool normalizeAcrossScale );
      bool GetNormalizeAcrossScale();

      /**
       * Get/Set Order
       */
      Self& SetOrder( OrderEnumType order );
      OrderEnumType GetOrder();

      // Print ourselves out
      std::string ToString();

      Image::Pointer Execute ( Image::Pointer );

    private:

      /** Sigma of the gaussian kernel. */
      double m_Sigma;

      /** Normalize the image across scale space */
      bool m_NormalizeAcrossScale;

      OrderEnumType m_Order;

      template <class TImageType> Image::Pointer ExecuteInternal ( Image::Pointer image );

      // friend to get access to executeInternal member
      friend struct detail::MemberFunctionAddressor<Self, MemberFunctionType>;


      std::auto_ptr<detail::MemberFunctionFactory<Self> > m_MemberFactory;
    };


  }
}
#endif
