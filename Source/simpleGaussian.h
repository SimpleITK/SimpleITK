#ifndef __simpleGaussian_h
#define __simpleGaussian_h

#include <SimpleITKMacro.h>
#include <simpleImage.h>

namespace itk {
  namespace simple {

    class Gaussian {
    public:
      typedef Gaussian Self;
   
      Gaussian();

      // Sigma is always measured in physical units
      Self& setSigma ( double sigma );
      double getSigma();
      
      // Print ourselves out
      std::string toString();

      Image::Pointer execute ( Image::Pointer );
    private:
      double mSigma;
      template <class T> Image::Pointer executeInternal ( Image::Pointer image );
    };


  }
}
#endif
