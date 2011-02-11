#ifndef __sitkDualImageFilter_h
#define __sitkDualImageFilter_h

#include "sitkImageFilter.h"

namespace itk {
  namespace simple {

  /** \class DualImageFilter
   * \brief The base interface for SimpleITK filters that take two input images
   *
   * All SimpleITK filters which take two input images should inherit from this
   * class
   */
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

      virtual Image* Execute ( Image*, Image* ) = 0;

      virtual ~DualImageFilter() {}

    private:

      //
    };

  }
}
#endif
