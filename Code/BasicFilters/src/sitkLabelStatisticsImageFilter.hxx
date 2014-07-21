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
#ifndef __sitkLabelStatisticsImageFilter_hxx
#define __sitkLabelStatisticsImageFilter_hxx
#include "sitkLabelStatisticsImageFilter.h"

#include "itkLabelStatisticsImageFilter.h"

// Needed to to calculate histogram properties
#include "sitkStatisticsImageFilter.h"


namespace itk {
namespace simple {


//----------------------------------------------------------------------------

//
// ExecuteInternal
//
template <class TImageType, class TLabelImageType>
Image LabelStatisticsImageFilter::DualExecuteInternal ( const Image& inImage1, const Image& inLabels )
  {
    typedef TImageType                                InputImageType;
    typedef TLabelImageType                           LabelImageType;

    typename InputImageType::ConstPointer image1 = this->CastImageToITK<InputImageType>( inImage1 );

    typename LabelImageType::ConstPointer labelImage = this->CastImageToITK<LabelImageType>( inLabels );

  //Need to find range of valid pixel values for histogram calulations
  typedef itk::LabelStatisticsImageFilter<TImageType,TLabelImageType> FilterType;

  typename FilterType::Pointer filter = FilterType::New();
  filter->SetInput( image1 );
  filter->SetLabelInput( labelImage );
  filter->SetUseHistograms(m_UseHistograms);

  if( m_UseHistograms)
    {
    typedef typename TImageType::PixelType PixelType;
    if( nsstd::is_same< PixelType, uint8_t >::value ||
        nsstd::is_same< PixelType, int8_t >::value )
      {
      //NOTE:  This is a heuristic that works exact median only for
      //(unsigned) char images.
      filter->SetHistogramParameters(256,std::numeric_limits<PixelType>::min()-0.5,std::numeric_limits<PixelType>::max()+0.5 );
      }
    else
      {
      itk::simple::StatisticsImageFilter stats;
      stats.Execute( inImage1 );

      filter->SetHistogramParameters(256,stats.GetMinimum(), stats.GetMaximum() );
      }
    }
  else
    {
    filter->UseHistogramsOff();
    }

  this->PreUpdate( filter.GetPointer() );

  this->m_BoundingBoxMeasurementMap.clear();
  this->m_LabelMeasurementMap.clear();

  filter->Update();


  typedef typename FilterType::ValidLabelValuesContainerType ValidLabelValuesType;

  for(typename ValidLabelValuesType::const_iterator vIt= filter->GetValidLabelValues().begin();
      vIt != filter->GetValidLabelValues().end();
      ++vIt)
    {

    assert ( filter->HasLabel(*vIt) );

    this->m_LabelMeasurementMap[*vIt]["Minimum"]  = filter->GetMinimum(*vIt);
    this->m_LabelMeasurementMap[*vIt]["Maximum"]  = filter->GetMaximum(*vIt);
    this->m_LabelMeasurementMap[*vIt]["Mean"]     = filter->GetMean(*vIt);
    this->m_LabelMeasurementMap[*vIt]["approxMedian"]   = filter->GetMedian(*vIt);
    this->m_LabelMeasurementMap[*vIt]["Sigma"]    = filter->GetSigma(*vIt);
    this->m_LabelMeasurementMap[*vIt]["Variance"] = filter->GetVariance(*vIt);
    this->m_LabelMeasurementMap[*vIt]["Sum"]      = filter->GetSum(*vIt);
    this->m_LabelMeasurementMap[*vIt]["Count"]    = filter->GetCount(*vIt);

    typename FilterType::BoundingBoxType bb = filter->GetBoundingBox(*vIt);
    this->m_BoundingBoxMeasurementMap.insert( std::make_pair(*vIt,std::vector<int>(bb.begin(),bb.end())));
    }

  //NOTE:  Input is passed through to output and is likely to get ignored!
  return Image( filter->GetOutput() );
  }
} // end namespace simple
} // end namespace itk

#endif //__sitkLabelStatisticsImageFilter_hxx
