#ifndef __sitkDualImageFilter_h
#define __sitkDualImageFilter_h

#include "sitkImageFilter.h"

namespace itk {
  namespace simple {

  class DualImageFilter :
      protected NonCopyable
  {
    public:

      /**
       * Default Constructor that takes no arguments and initializes
       * default parameters
       */
      DualImageFilter() {};


      // Print ourselves out
      virtual std::string ToString() const = 0;

      virtual Image::Pointer Execute ( Image::Pointer, Image::Pointer ) = 0;

      virtual ~DualImageFilter() {}

    private:

      //
    };

  }
}
#endif
