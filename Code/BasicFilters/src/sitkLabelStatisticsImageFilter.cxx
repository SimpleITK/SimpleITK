#include "sitkLabelStatisticsImageFilter.h"

#include "itkLabelStatisticsImageFilter.h"

// Needed to to calculate histogram properties
#include "sitkStatisticsImageFilter.h"


namespace itk {
namespace simple {

//----------------------------------------------------------------------------

// Functional interface
  LabelStatisticsImageFilter::LabelStatisticsMap LabelStatistics ( const Image& image, const Image& labels )
  {
    LabelStatisticsImageFilter filter;
    filter.Execute ( image, labels );
    return filter.GetLabelStatisticsMap();
  }

//
// Default constructor that initializes parameters
//
LabelStatisticsImageFilter::LabelStatisticsImageFilter ()
  {
  this->m_LabelMeasurementMap.clear();
  this->m_DualMemberFactory.reset( new detail::DualMemberFunctionFactory<MemberFunctionType>( this ) );

  this->m_DualMemberFactory->RegisterMemberFunctions< PixelIDTypeList, MapPixelIDTypeList, 3 > ();
  this->m_DualMemberFactory->RegisterMemberFunctions< PixelIDTypeList, MapPixelIDTypeList, 2 > ();
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

Image LabelStatisticsImageFilter::Execute ( const Image& image1 , const Image & labels )
  {
    PixelIDValueType type = image1.GetPixelIDValue();
    unsigned int dimension = image1.GetDimension();

    PixelIDValueType labeltype = labels.GetPixelIDValue();
    unsigned int labeldimension = labels.GetDimension();

    if ( dimension != labeldimension )
      {
      sitkExceptionMacro( "Labelmap and image MUST have same dimensions!" );
      }

    return this->m_DualMemberFactory->GetMemberFunction( type, labeltype, dimension )( image1, labels );
  }

//----------------------------------------------------------------------------

//
// ExecuteInternal
//
template <class TImageType, class TLabelImageType>
Image LabelStatisticsImageFilter::DualExecuteInternal ( const Image& inImage1, const Image& inLabels )
  {
  typename TImageType::ConstPointer image1 =
    dynamic_cast <const TImageType* > ( inImage1.GetITKBase() );

  if ( image1.IsNull() )
    {
    sitkExceptionMacro( "Unexpected template dispatch error!" );
    }

  typename TLabelImageType::ConstPointer labelImage =
    dynamic_cast <const TLabelImageType* > ( inLabels.GetITKBase() );
  if ( labelImage.IsNull() )
    {
    sitkExceptionMacro( "Unexpected template dispatch error!" );
    }

  //Need to find range of valid pixel values for histogram calulations
  typedef itk::LabelStatisticsImageFilter<TImageType,TLabelImageType> FilterType;

  typename FilterType::Pointer filter = FilterType::New();
  filter->SetInput( image1 );
  filter->SetLabelInput( labelImage );
  filter->UseHistogramsOn(); //Needed to get Median value

  typedef typename TImageType::PixelType PixelType;
  if( std::tr1::is_same< PixelType, uint8_t >::value ||
      std::tr1::is_same< PixelType, int8_t >::value )
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
    }

  //NOTE:  Input is passed through to output and is likely to get ignored!
  return Image( filter->GetOutput() );
  }
} // end namespace simple
} // end namespace itk
