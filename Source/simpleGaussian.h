#ifndef __simpleGaussian_h
#define __simpleGaussian_h

#include <SimpleITKMacro.h>
#include <simpleImage.h>

namespace itk {
  namespace simple {

    class Gaussian {
    public:
      typedef Gaussian Self;

      // function pointer type
      typedef ImageBase::Pointer (Self::*MemberFunctionType)( ImageBase::Pointer );

      Gaussian();

      // Sigma is always measured in physical units
      Self& setSigma ( double sigma );
      double getSigma();

      // Print ourselves out
      std::string toString();

      ImageBase::Pointer execute ( ImageBase::Pointer );

      double mSigma;

    private:

      template <class T> ImageBase::Pointer executeInternal ( ImageBase::Pointer image );

      // list of pixel types supported only basic since rgb and
      // vectors are not supported by this filter
      typedef BasicPixelTypeList PixelTypeList;

      // friend to get access to executeInternal member 
      friend class PFuncArrayInitializer<Self>;

      // array of pointers to member functions
      MemberFunctionType  m_PFunction[ typelist::Length< InstantiatedPixelTypeList >::Result ];
    };


  }
}
#endif
