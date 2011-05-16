#ifndef __sitkStatisticsImageFilter_h
#define __sitkStatisticsImageFilter_h

#include "sitkImageFilter.h"
#include "sitkMeasurementMap.h"

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

      typedef BasicPixelIDTypeList   PixelIDTypeList;

      /** Name of this class */
      std::string GetName() const { return std::string ( "Statistics"); }

      // Print ourselves out
      std::string ToString() const;

      Image Execute ( const Image & );

      double GetMinimum ( ) const;
      double GetMaximum ( ) const;
      double GetMean    ( ) const;
      double GetVariance( ) const;

      //Return the MeasuremetMap for the given labelCode
      itk::simple::MeasurementMap GetMeasurementMap ( ) const;
    private:

      typedef Image (Self::*MemberFunctionType)( const Image& );
      template <class TImageType> Image ExecuteInternal ( const Image& image );

      friend struct detail::MemberFunctionAddressor<MemberFunctionType>;
      std::auto_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;

      MeasurementMap  m_MeasurementMap;

      //A helper to get values out of the m_LabelStatisticsMap;
      double QueryValue( const std::string) const;
    };

    itk::simple::MeasurementMap Statistics ( const Image& );
  }
}
#endif
