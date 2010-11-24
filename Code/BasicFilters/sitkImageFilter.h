#ifndef __sitkImageFilter_h
#define __sitkImageFilter_h

#include "sitkMacro.h"
#include "sitkMemberFunctionFactory.h"
#include "sitkImage.h"

namespace itk {
  namespace simple {

    class ImageFilter {
    public:
      typedef ImageFilter Self;

      //
      // Type List Setup
      //

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
      ImageFilter();

      /**
       * Default Destructor
       */
      virtual ~ImageFilter();

      // Print ourselves out
      virtual std::string ToString() const = 0;

      virtual Image::Pointer Execute ( Image::Pointer ) = 0;

    private:

    };


  }
}
#endif
