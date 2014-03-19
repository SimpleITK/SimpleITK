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
#include "sitkLabelStatisticsImageFilter.h"

#include "itkLabelStatisticsImageFilter.h"

// Needed to to calculate histogram properties
#include "sitkStatisticsImageFilter.h"


namespace itk {
namespace simple {

//----------------------------------------------------------------------------

// Functional interface
  LabelStatisticsImageFilter::LabelStatisticsMap LabelStatistics ( const Image& image1, const Image& labelImage, bool useHistograms )
  {
    LabelStatisticsImageFilter filter;
    filter.Execute ( image1, labelImage, useHistograms );
    return filter.GetLabelStatisticsMap();
  }

//
// Default constructor that initializes parameters
//
LabelStatisticsImageFilter::LabelStatisticsImageFilter ()
  {
  this->m_DualMemberFactory.reset( new detail::DualMemberFunctionFactory<MemberFunctionType>( this ) );

  this->RegisterMemberFactory2();
  this->RegisterMemberFactory3();

  this->m_UseHistograms = true;
  }

LabelStatisticsImageFilter::LabelListingType LabelStatisticsImageFilter::GetValidLabels () const
  {
  LabelListingType validLabels(0);
  validLabels.reserve(this->m_LabelMeasurementMap.size());
  for( LabelStatisticsMap::const_iterator labelMeasurementMapIt=this->m_LabelMeasurementMap.begin();
    labelMeasurementMapIt != this->m_LabelMeasurementMap.end();
    ++labelMeasurementMapIt)
    {
    validLabels.push_back(labelMeasurementMapIt->first);
    }
  return validLabels;
  }

double LabelStatisticsImageFilter::QueryValue(const LabelIdentifierType currID, const std::string currMeasurement) const
  {
  const LabelStatisticsMap::const_iterator labelMeasurementMapIt( this->m_LabelMeasurementMap.find(currID) );
  if( labelMeasurementMapIt != this->m_LabelMeasurementMap.end() )
    {
    const MeasurementMap::const_iterator measurmentContainerIt(  labelMeasurementMapIt->second.find(currMeasurement) );
    if( measurmentContainerIt != labelMeasurementMapIt->second.end() )
      {
      return measurmentContainerIt->second;
      }
    }
    return itk::NumericTraits< double >::quiet_NaN();
  }

//
// ToString
//
std::string LabelStatisticsImageFilter::ToString() const
  {
  std::ostringstream out;
  out << "itk::simple::LabelStatisticsImageFilter\n";
  for( LabelStatisticsMap::const_iterator labelMeasurementMapIt=this->m_LabelMeasurementMap.begin();
    labelMeasurementMapIt != this->m_LabelMeasurementMap.end();
    ++labelMeasurementMapIt)
    {
    for ( MeasurementMap::const_iterator measurmentContainerIt = labelMeasurementMapIt->second.begin();
      measurmentContainerIt != labelMeasurementMapIt->second.end();
      ++measurmentContainerIt)
      {
      out <<
        "\t Label("<<
        labelMeasurementMapIt->first <<
        ")[" <<
        measurmentContainerIt->first <<
        "] = "  <<
        measurmentContainerIt->second <<
        "\n";
      }

    std::map<LabelIdentifierType, std::vector<int> >::const_iterator bbIt;
    bbIt = this->m_BoundingBoxMeasurementMap.find(labelMeasurementMapIt->first);
    if (bbIt != this->m_BoundingBoxMeasurementMap.end())
      {
      out << "\t Label("<<
        labelMeasurementMapIt->first <<
        ")[BoundingBox] = "  <<
        bbIt->second <<
      "\n";
      }
    }
  return out.str();
  }


double LabelStatisticsImageFilter::GetMinimum ( const LabelIdentifierType labelCode ) const
  {
  if( ! this->HasLabel(labelCode) )
    {
    sitkExceptionMacro( "Invalid label code requested " << labelCode );
    }
  return this->QueryValue(labelCode, "Minimum" );
  }
double LabelStatisticsImageFilter::GetMaximum ( const LabelIdentifierType labelCode ) const
  {
  if( ! this->HasLabel(labelCode) )
    {
    sitkExceptionMacro( "Invalid label code requested " << labelCode );
    }
  return this->QueryValue(labelCode, "Maximum" );
  }
double LabelStatisticsImageFilter::GetMean    ( const LabelIdentifierType labelCode ) const
  {
  if( ! this->HasLabel(labelCode) )
    {
    sitkExceptionMacro( "Invalid label code requested " << labelCode );
    }
  return this->QueryValue(labelCode, "Mean" );
  }
double LabelStatisticsImageFilter::GetMedian    ( const LabelIdentifierType labelCode ) const
  {
  if( ! this->HasLabel(labelCode) )
    {
    sitkExceptionMacro( "Invalid label code requested " << labelCode );
    }
  return this->QueryValue(labelCode, "approxMedian" );
  }
double LabelStatisticsImageFilter::GetSigma( const LabelIdentifierType labelCode ) const
  {
  if( ! this->HasLabel(labelCode) )
    {
    sitkExceptionMacro( "Invalid label code requested " << labelCode );
    }
  return this->QueryValue(labelCode, "Sigma" );
  }
double LabelStatisticsImageFilter::GetVariance( const LabelIdentifierType labelCode ) const
  {
  if( ! this->HasLabel(labelCode) )
    {
    sitkExceptionMacro( "Invalid label code requested " << labelCode );
    }
  return this->QueryValue(labelCode, "Variance" );
  }
double LabelStatisticsImageFilter::GetSum( const LabelIdentifierType labelCode ) const
  {
  if( ! this->HasLabel(labelCode) )
    {
    sitkExceptionMacro( "Invalid label code requested " << labelCode );
    }
  return this->QueryValue(labelCode, "Sum" );
  }
double LabelStatisticsImageFilter::GetCount( const LabelIdentifierType labelCode ) const
  {
  if( ! this->HasLabel(labelCode) )
    {
    sitkExceptionMacro( "Invalid label code requested " << labelCode );
    }
  return this->QueryValue(labelCode, "Count" );
  }
std::vector<int> LabelStatisticsImageFilter::GetBoundingBox( const LabelIdentifierType labelCode ) const
  {
  std::map<LabelIdentifierType, std::vector<int> >::const_iterator bbIt;
  bbIt = m_BoundingBoxMeasurementMap.find(labelCode);
  if( ! this->HasLabel(labelCode) || bbIt == m_BoundingBoxMeasurementMap.end() )
    {
    sitkExceptionMacro( "Invalid label code requested " << labelCode );
    }
  return bbIt->second;
  }


LabelStatisticsImageFilter::LabelStatisticsMap LabelStatisticsImageFilter::GetLabelStatisticsMap( ) const
  {
  return this->m_LabelMeasurementMap;
  }

bool   LabelStatisticsImageFilter::HasLabel   ( const LabelIdentifierType labelCode ) const
  {
  return ( this->m_LabelMeasurementMap.find(labelCode) != this->m_LabelMeasurementMap.end() ) ;
  }

itk::simple::MeasurementMap LabelStatisticsImageFilter::GetMeasurementMap( const LabelIdentifierType labelCode ) const
  {
  if( ! this->HasLabel(labelCode) )
    {
    sitkExceptionMacro( "Invalid label code requested " << labelCode );
    }
  return (this->m_LabelMeasurementMap.find(labelCode)->second);
  }



//
// Execute
//

Image LabelStatisticsImageFilter::Execute ( const Image& image1, const Image& labelImage, bool useHistograms )
  {
    this->SetUseHistograms(useHistograms);
    return this->Execute( image1, labelImage );
  }

Image LabelStatisticsImageFilter::Execute ( const Image& image1 , const Image & labels )
  {
    PixelIDValueEnum type = image1.GetPixelID();
    unsigned int dimension = image1.GetDimension();

    PixelIDValueEnum labeltype = labels.GetPixelID();
    unsigned int labeldimension = labels.GetDimension();

    if ( dimension != labeldimension )
      {
      sitkExceptionMacro( "Labelmap and image MUST have same dimensions!" );
      }

    return this->m_DualMemberFactory->GetMemberFunction( type, labeltype, dimension )( image1, labels );
  }
} // end namespace simple
} // end namespace itk
