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

#include "sitkImageFilter.h"
#include "sitkDualMemberFunctionFactory.h"
#include "sitkMeasurementMap.h"

namespace itk {
  namespace simple {

    /** \class LabelStatisticsImageFilter
     * \brief Given an intensity image and a label map, compute min,
     * max, variance and mean of the pixels associated with each label
     * or segment.
     *
     * LabelStatisticsImageFilter computes the minimum, maximum, sum,
     * mean, median, variance and sigma of regions of an intensity image, where
     * the regions are defined via a label map (a second input).  The
     * label image should be integral type. The filter needs all of its
     * input image.
     *
     * \sa itk::simple::LabelStatistics for the procedural interface
     */
    class SITKBasicFilters_EXPORT  LabelStatisticsImageFilter
      : public ImageFilter<2> {
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
      std::string GetName() const { return std::string ("LabelStatisticsImageFilter" ); }

      // Print ourselves out
      std::string ToString() const;

      /** \brief Compute histogram with statistics
       *
       * Enable the computation of the approximate median value, at
       * the cost of additional computation.
       */
      bool GetUseHistograms() const {return this->m_UseHistograms;}
      void SetUseHistograms(bool v) {this->m_UseHistograms=v;}
      void UseHistogramsOn() {this->SetUseHistograms(true);}
      void UseHistogramsOff() {this->SetUseHistograms(false);}

      Image Execute ( const Image & image1, const Image & labelImage );

      Image Execute ( const Image & image1, const Image & labelImage, bool useHistograms );

      double GetMinimum ( const LabelIdentifierType labelCode ) const;
      double GetMaximum ( const LabelIdentifierType labelCode ) const;
      double GetMean    ( const LabelIdentifierType labelCode ) const;
      double GetMedian  ( const LabelIdentifierType labelCode ) const;
      double GetSigma   ( const LabelIdentifierType labelCode ) const;
      double GetVariance( const LabelIdentifierType labelCode ) const;
      double GetSum     ( const LabelIdentifierType labelCode ) const;
      double GetCount   ( const LabelIdentifierType labelCode ) const;

      /**
       * \brief Get the bounding box of a label.
       *
       * Defined by the closed interval of indexes, with a
       * lower index followed by the upper for each dimension.
       * i.e. [0,255,0,255]. The bounding box always has a positive
       * size.
       */
      std::vector<int> GetBoundingBox( const LabelIdentifierType labelCode ) const;

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

      /**
       * These methods are used to instantiate and register member functions
       * with the factory. Each function is split into a separate file to
       * make the compilation units smaller, and take less time to compile.
       * @{
       */
      void RegisterMemberFactory2();
      void RegisterMemberFactory3();
      /** @} */

      typedef Image (Self::*MemberFunctionType)( const Image&, const Image& );
      template <class TImageType, class TLabelImageType> Image DualExecuteInternal ( const Image& image, const Image& labels );

      friend struct detail::DualExecuteInternalAddressor<MemberFunctionType>;
      std::auto_ptr<detail::DualMemberFunctionFactory<MemberFunctionType> > m_DualMemberFactory;

      bool m_UseHistograms;

      LabelStatisticsMap  m_LabelMeasurementMap;

      std::map<LabelIdentifierType, std::vector<int> > m_BoundingBoxMeasurementMap;

      //A helper to get values out of the m_LabelMeasurementMap;
      double QueryValue(const LabelIdentifierType, const std::string) const;
    };

  SITKBasicFilters_EXPORT LabelStatisticsImageFilter::LabelStatisticsMap LabelStatistics ( const Image& image1, const Image& labelImage, bool useHistograms = true );
  }
}
#endif
