#ifndef __sitkLabelStatisticsImageFilter_h
#define __sitkLabelStatisticsImageFilter_h

#include "sitkDualImageFilter.h"
#include "sitkDualMemberFunctionFactory.h"
#include "sitkMeasurementMap.h"

namespace itk {
  namespace simple {

    /** \class LabelStatisticsImageFilter
     * \brief Compute min, max, variance, and mean of an image
     */
    class LabelStatisticsImageFilter : public DualImageFilter {
    public:
      typedef LabelStatisticsImageFilter       Self;

      /**
       * Default Constructor that takes no arguments and initializes
       * default parameters
       */
      LabelStatisticsImageFilter();

      ///Label type used is int because it is wrapped naturally by swig.
      typedef size_t                                         LabelIdentifierType;

      ///List of labels is an std::vector because it seems to be most widely supported for wrapping.
      typedef std::vector<LabelIdentifierType> LabelListingType;

      ///The type used to catalog all named values
      typedef std::map<LabelIdentifierType, MeasurementMap> LabelStatisticsMap;

      typedef BasicPixelIDTypeList   PixelIDTypeList;
      typedef IntegerPixelIDTypeList MapPixelIDTypeList;

      /** Name of this class */
      std::string GetName() const { return std::string ( "LabelStatistics" ); }

      // Print ourselves out
      std::string ToString() const;

      Image Execute ( const Image & , const Image & );

      double GetMinimum ( const LabelIdentifierType labelCode ) const;
      double GetMaximum ( const LabelIdentifierType labelCode ) const;
      double GetMean    ( const LabelIdentifierType labelCode ) const;
      double GetVariance( const LabelIdentifierType labelCode ) const;

      //Return the MeasuremetMap for the given labelCode
      MeasurementMap GetMeasurementMap ( const LabelIdentifierType labelCode ) const;

      bool   HasLabel   ( const LabelIdentifierType labelCode ) const;

      /** A convenience function to return a dense list of valid labels found in the label image */
      LabelListingType GetValidLabels () const;

      /**
       * Return the entire statistics map
       */
      LabelStatisticsMap GetLabelStatisticsMap( ) const;
    private:

      typedef Image (Self::*MemberFunctionType)( const Image&, const Image& );
      template <class TImageType, class TLabelImageType> Image DualExecuteInternal ( const Image& image, const Image& labels );

      friend struct detail::DualExecuteInternalAddressor<MemberFunctionType>;
      std::auto_ptr<detail::DualMemberFunctionFactory<MemberFunctionType> > m_DualMemberFactory;

      LabelStatisticsMap  m_LabelMeasurementMap;

      //A helper to get values out of the m_LabelMeasurementMap;
      double QueryValue(const LabelIdentifierType, const std::string) const;
    };

    LabelStatisticsImageFilter::LabelStatisticsMap LabelStatistics ( const Image&, const Image& );
  }
}
#endif
