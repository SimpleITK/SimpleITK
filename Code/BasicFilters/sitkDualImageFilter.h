#ifndef __sitkDualImageFilter_h
#define __sitkDualImageFilter_h

#include "sitkImageFilter.h"

namespace itk {
  namespace simple {

    class DualImageFilter : public ImageFilter {
    public:

      /**
       * Default Constructor that takes no arguments and initializes
       * default parameters
       */
      DualImageFilter() {};

      virtual Image::Pointer Execute ( Image::Pointer, Image::Pointer ) = 0;

    private:

      // Make the Execute method of the base class to be final.
      Image::Pointer Execute ( Image::Pointer )
        {
        Image::Pointer image;
        return image;
        }

    };

  }
}
#endif
