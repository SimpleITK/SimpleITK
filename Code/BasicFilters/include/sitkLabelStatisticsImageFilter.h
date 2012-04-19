/*=========================================================================
*
*  Copyright Insight Software Consortium
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*         http://www.apache.org/licenses/LICENSE-2.0.txt
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*=========================================================================*/
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
    class SITKBasicFilters0_EXPORT LabelStatisticsImageFilter : public DualImageFilter {
    public:
      typedef LabelStatisticsImageFilter       Self;

      /**
       * Default Constructor that takes no arguments and initializes
       * default parameters
       */
      LabelStatisticsImageFilter();

      ///Label type used is int because it is wrapped naturally by swig.
      typedef unsigned int                                         LabelIdentifierType;

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
      double GetMedian  ( const LabelIdentifierType labelCode ) const;
      double GetSigma   ( const LabelIdentifierType labelCode ) const;
      double GetVariance( const LabelIdentifierType labelCode ) const;
      double GetSum     ( const LabelIdentifierType labelCode ) const;
      double GetCount   ( const LabelIdentifierType labelCode ) const;

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

    SITKBasicFilters0_EXPORT LabelStatisticsImageFilter::LabelStatisticsMap LabelStatistics ( const Image&, const Image& );
  }
}
#endif
