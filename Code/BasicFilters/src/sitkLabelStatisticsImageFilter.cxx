#include "sitkLabelStatisticsImageFilter.h"

#include "itkLabelStatisticsImageFilter.h"

//HACK until itkLabelStaticsImageFilter can return list of valid labels found
#include "itkMinimumMaximumImageFilter.h"

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
double LabelStatisticsImageFilter::GetVariance( const LabelIdentifierType labelCode ) const
  {
  if( ! this->HasLabel(labelCode) )
    {
    sitkExceptionMacro( "Invalid label code requested " << labelCode );
    }
  return this->QueryValue(labelCode, "Variance" );
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
    dynamic_cast <const TImageType* > ( inImage1.GetImageBase() );

  if ( image1.IsNull() )
    {
    sitkExceptionMacro( "Unexpected template dispatch error!" );
    }

  typename TLabelImageType::ConstPointer labelImage =
    dynamic_cast <const TLabelImageType* > ( inLabels.GetImageBase() );
  if ( labelImage.IsNull() )
    {
    sitkExceptionMacro( "Unexpected template dispatch error!" );
    }

  typedef itk::LabelStatisticsImageFilter<TImageType,TLabelImageType> FilterType;

  typename FilterType::Pointer filter = FilterType::New();
  filter->SetInput( image1 );
  filter->SetLabelInput( labelImage );
  filter->Update();


    {
    //HACK until itk::LabelStatisticsImageFilter is instumented to provide a list of valid labels found
    //     we must search by brute force through all the possiblities looking for valid values.
    typedef itk::MinimumMaximumImageFilter<TLabelImageType> MinMaxType;
    typename MinMaxType::Pointer rangeFinderFilter=MinMaxType::New();
    rangeFinderFilter->SetInput(labelImage);
    rangeFinderFilter->Update();

    for( typename TLabelImageType::PixelType rangeIt=rangeFinderFilter->GetMinimum();
      rangeIt <= rangeFinderFilter->GetMaximum();
      ++rangeIt)
      {
      if( filter->HasLabel( rangeIt ) )
        {
        this->m_LabelMeasurementMap[rangeIt]["Minimum"]  = filter->GetMinimum(rangeIt);
        this->m_LabelMeasurementMap[rangeIt]["Maximum"]  = filter->GetMaximum(rangeIt);
        this->m_LabelMeasurementMap[rangeIt]["Mean"]     = filter->GetMean(rangeIt);
        this->m_LabelMeasurementMap[rangeIt]["Variance"] = filter->GetVariance(rangeIt);
        }
      }
    }
  //NOTE:  Input is passed through to output and is likely to get ignored!
  return Image( filter->GetOutput() );
  }
} // end namespace simple
} // end namespace itk
