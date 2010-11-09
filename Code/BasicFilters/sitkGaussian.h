#ifndef __sitkGaussian_h
#define __sitkGaussian_h

#include "sitkMacro.h"
#include "sitkDetail.h"
#include "sitkImage.h"


namespace itk {
  namespace simple {

    class Gaussian {
    public:
      typedef Gaussian Self;

      // function pointer type
      typedef Image::Pointer (Self::*MemberFunctionType)( Image::Pointer );

      // list of pixel types supported only basic since rgb and
      // vectors are not supported by this filter
      typedef BasicPixelTypeList PixelTypeList;


      Gaussian();

      // Sigma is always measured in physical units
      Self& SetSigma ( double sigma );
      double GetSigma();

      // Print ourselves out
      std::string ToString();

      Image::Pointer Execute ( Image::Pointer );

      double m_Sigma;

    private:

      template <class T> Image::Pointer ExecuteInternal ( Image::Pointer image );

      // friend to get access to executeInternal member 
      friend class detail::PFuncArrayInitializer<Self>;


      detail::MemberFunctionFactory<Self> m_MemberFactory;
    };


  }
}
#endif
