#ifndef __sitkStatisticsImageFilter_h
#define __sitkStatisticsImageFilter_h

#include "sitkImageFilter.h"


namespace itk {
  namespace simple {

    /** \class StatisticsImageFilter
     * \brief Compute min, max, variance, and mean of an image
     */
    class StatisticsImageFilter : public ImageFilter {
    public:
      typedef StatisticsImageFilter Self;

      /**
       * Default Constructor that takes no arguments and initializes
       * default parameters
       */
      StatisticsImageFilter();

      typedef BasicPixelIDTypeList PixelIDTypeList;

      /** Name of this class */
      std::string GetName() const { return std::string ( "Statistics"); }

      // Print ourselves out
      std::string ToString() const;

      Image Execute ( const Image & );
      double GetMinimum() { return this->m_Minimum; }
      double GetMaximum() { return this->m_Maximum; }
      double GetMean() { return this->m_Mean; }
      double GetVariance() { return this->m_Variance; }
    private:

      typedef Image (Self::*MemberFunctionType)( const Image& );
      template <class TImageType> Image ExecuteInternal ( const Image& image );
      friend struct detail::MemberFunctionAddressor<MemberFunctionType>;
      std::auto_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;

      double m_Minimum;
      double m_Maximum;
      double m_Mean;
      double m_Variance;

    };


  }
}
#endif
