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
#ifndef __sitkStatisticsImageFilter_h
#define __sitkStatisticsImageFilter_h

#include "sitkImageFilter.h"
#include "sitkMeasurementMap.h"

namespace itk {
  namespace simple {

    /** \class StatisticsImageFilter
     * \brief Compute min, max, variance, and mean of an image
     *
     * \sa itk::simple::Statistics for the procedural interface
     */
    class SITKBasicFilters_EXPORT StatisticsImageFilter : public ImageFilter<1> {
    public:
      typedef StatisticsImageFilter Self;

      /**
       * Default Constructor that takes no arguments and initializes
       * default parameters
       */
      StatisticsImageFilter();

      typedef BasicPixelIDTypeList   PixelIDTypeList;

      /** Name of this class */
      std::string GetName() const { return std::string ("StatisticsImageFilter"); }

      // Print ourselves out
      std::string ToString() const;

      Image Execute ( const Image & );

      double GetMinimum ( ) const;
      double GetMaximum ( ) const;
      double GetMean    ( ) const;
      double GetSigma   ( ) const;
      double GetVariance( ) const;
      double GetSum     ( ) const;

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

    SITKBasicFilters_EXPORT itk::simple::MeasurementMap Statistics ( const Image& );
  }
}
#endif
