#include "sitkStatisticsImageFilter.h"

#include "itkStatisticsImageFilter.h"

namespace itk {
namespace simple {

//----------------------------------------------------------------------------

// Functional interface
  itk::simple::MeasurementMap Statistics ( const Image& image )
  {
    StatisticsImageFilter filter;
    filter.Execute ( image );
    return filter.GetMeasurementMap( );
  }

//
// Default constructor that initializes parameters
//
StatisticsImageFilter::StatisticsImageFilter ()
  {
  this->m_MeasurementMap.clear();
  this->m_MemberFactory.reset( new detail::MemberFunctionFactory<MemberFunctionType>( this ) );

  this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 3 > ();
  this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 2 > ();
  }

double StatisticsImageFilter::QueryValue( const std::string currMeasurement) const
  {
    const MeasurementMap::const_iterator measurmentContainerIt(  this->m_MeasurementMap.find(currMeasurement) );
    if( measurmentContainerIt != this->m_MeasurementMap.end() )
      {
      return measurmentContainerIt->second;
      }
    return itk::NumericTraits< double >::quiet_NaN();
  }
//
// ToString
//
std::string StatisticsImageFilter::ToString() const
  {
  std::ostringstream out;
  out << "itk::simple::StatisticsImageFilter\n";
  for ( MeasurementMap::const_iterator measurmentContainerIt = this->m_MeasurementMap.begin();
    measurmentContainerIt != this->m_MeasurementMap.end();
    ++measurmentContainerIt)
    {
    out <<
      "\t[" <<
      measurmentContainerIt->first <<
      "] = "  <<
      measurmentContainerIt->second <<
      "\n";
    }
  return out.str();
  }


double StatisticsImageFilter::GetMinimum ( ) const
  {
  return this->QueryValue( "Minimum" );
  }
double StatisticsImageFilter::GetMaximum ( ) const
  {
  return this->QueryValue( "Maximum" );
  }
double StatisticsImageFilter::GetMean    ( ) const
  {
  return this->QueryValue( "Mean" );
  }
double StatisticsImageFilter::GetVariance( ) const
  {
  return this->QueryValue( "Variance" );
  }

itk::simple::MeasurementMap StatisticsImageFilter::GetMeasurementMap( ) const
  {
  return this->m_MeasurementMap;
  }

//
// Execute
//

Image StatisticsImageFilter::Execute ( const Image& image1 )
  {
    PixelIDValueType type = image1.GetPixelIDValue();
    unsigned int dimension = image1.GetDimension();

    return this->m_MemberFactory->GetMemberFunction( type, dimension )( image1 );
  }

//----------------------------------------------------------------------------

//
// ExecuteInternal
//
template <class TImageType>
Image StatisticsImageFilter::ExecuteInternal ( const Image& inImage1 )
  {
  typedef TImageType     InputImageType;
  typedef InputImageType OutputImageType;

  typename InputImageType::ConstPointer image1 =
    dynamic_cast <const InputImageType* > ( inImage1.GetImageBase() );

  if ( image1.IsNull() )
    {
    sitkExceptionMacro( "Unexpected template dispatch error!" );
    }

  typedef itk::StatisticsImageFilter<InputImageType> FilterType;

  typename FilterType::Pointer filter = FilterType::New();
  filter->SetInput( image1 );
  filter->Update();

  m_MeasurementMap["Minimum"] =filter->GetMinimum();
  m_MeasurementMap["Maximum"] =filter->GetMaximum();
  m_MeasurementMap["Mean"]    =filter->GetMean();
  m_MeasurementMap["Variance"]=filter->GetVariance();

  return Image( filter->GetOutput() );
  }

} // end namespace simple
} // end namespace itk
