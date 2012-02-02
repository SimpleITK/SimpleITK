#ifndef __sitkImageFilter_h
#define __sitkImageFilter_h

#include "sitkMacro.h"
#include "sitkImage.h"
#include "sitkMemberFunctionFactory.h"
#include "sitkBasicFilters.h"

namespace itk {
  namespace simple {

  /** \class ImageFilter
   * \brief The base interface for SimpleITK filters that take one input image
   *
   * All SimpleITK filters which take one input image should inherit from this
   * class
   */
  class SITKBasicFilters_EXPORT ImageFilter :protected NonCopyable
  {
    public:
      typedef ImageFilter Self;

      //
      // Type List Setup
      //

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

      virtual Image Execute ( const Image & ) = 0;

      /** return user readable name fo the filter */
      virtual std::string GetName() const = 0;

    private:

    };


  }
}
#endif
