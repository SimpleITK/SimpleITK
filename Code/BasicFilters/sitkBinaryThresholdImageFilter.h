#ifndef __sitkBinaryThresholdImageFilter_h
#define __sitkBinaryThresholdImageFilter_h

#include "sitkImageFilter.h"



namespace itk {
  namespace simple {

    class BinaryThresholdImageFilter : public ImageFilter {
    public:
      typedef BinaryThresholdImageFilter Self;

      /**
       * Default Constructor that takes no arguments and initializes
       * default parameters
       */
      BinaryThresholdImageFilter();

      sitkSetGetMacro( double, LowerThreshold );
      sitkSetGetMacro( double, UpperThreshold );

      // Print ourselves out
      std::string ToString() const;

      Image::Pointer Execute ( Image::Pointer );

    private:

      sitkSingleImageMemberFunctionDispatcher;

      double    m_LowerThreshold;
      double    m_UpperThreshold;
    };


  }
}
#endif
