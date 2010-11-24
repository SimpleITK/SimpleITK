#ifndef __sitkAddImageFilter_h
#define __sitkAddImageFilter_h

#include "sitkDualImageFilter.h"



namespace itk {
  namespace simple {

    class AddImageFilter : public DualImageFilter {
    public:
      typedef AddImageFilter Self;

      /**
       * Default Constructor that takes no arguments and initializes
       * default parameters
       */
      AddImageFilter();

      // Print ourselves out
      std::string ToString() const;

      Image::Pointer Execute ( Image::Pointer, Image::Pointer );

    private:

      sitkDualImageMemberFunctionDispatcher;

    };


  }
}
#endif
