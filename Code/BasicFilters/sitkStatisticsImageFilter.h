#ifndef __sitkStatisticsImageFilter_h
#define __sitkStatisticsImageFilter_h

#include "sitkImageFilter.h"



namespace itk {
  namespace simple {

    class StatisticsImageFilter : public ImageFilter {
    public:
      typedef StatisticsImageFilter Self;

      /**
       * Default Constructor that takes no arguments and initializes
       * default parameters
       */
      StatisticsImageFilter();

      typedef BasicPixelTypeList PixelTypeList;

      // Print ourselves out
      std::string ToString() const;

      Image::Pointer Execute ( Image::Pointer );
      double GetMinimum() { return this->m_Minimum; }
      double GetMaximum() { return this->m_Maximum; }
      double GetMean() { return this->m_Mean; }
      double GetVariance() { return this->m_Variance; }
    private:

      sitkSingleImageMemberFunctionDispatcher;
      double m_Minimum;
      double m_Maximum;
      double m_Mean;
      double m_Variance;
      
    };


  }
}
#endif
