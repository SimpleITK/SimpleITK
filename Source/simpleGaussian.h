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
      typedef Image::Pointer (Self::*MemberFunctionType)( Image::Pointer );

      // list of pixel types supported only basic since rgb and
      // vectors are not supported by this filter
      typedef BasicPixelTypeList PixelTypeList;


      Gaussian();

      // Sigma is always measured in physical units
      Self& setSigma ( double sigma );
      double getSigma();

      // Print ourselves out
      std::string toString();

      Image::Pointer execute ( Image::Pointer );

      double mSigma;

    private:

      template <class T> Image::Pointer executeInternal ( Image::Pointer image );

      // friend to get access to executeInternal member 
      friend class PFuncArrayInitializer<Self>;

      // array of pointers to member functions
      MemberFunctionType  m_PFunction[ typelist::Length< InstantiatedPixelTypeList >::Result ];
    };


  }
}
#endif
