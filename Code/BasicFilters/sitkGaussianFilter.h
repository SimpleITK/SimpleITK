#ifndef __sitkGaussianFilter_h
#define __sitkGaussianFilter_h

#include "sitkMacro.h"
#include "sitkDetail.h"
#include "sitkImage.h"


namespace itk {
  namespace simple {

    class GaussianFilter {
    public:
      typedef GaussianFilter Self;

      // function pointer type
      typedef Image::Pointer (Self::*MemberFunctionType)( Image::Pointer );

      // list of pixel types supported only basic since rgb and
      // vectors are not supported by this filter
      typedef BasicPixelTypeList PixelTypeList;

      GaussianFilter();

      // Sigma is always measured in physical units
      Self& SetSigma ( double sigma );
      double GetSigma();

      // Print ourselves out
      std::string ToString();

      Image::Pointer Execute ( Image::Pointer );

    private:

      double m_Sigma;

      template <class TImageType> Image::Pointer ExecuteInternal ( Image::Pointer image );

      // friend to get access to executeInternal member
      friend class detail::MemberFunctionAddressor<Self, MemberFunctionType>;


      std::auto_ptr<detail::MemberFunctionFactory<Self> > m_MemberFactory;
    };


  }
}
#endif
