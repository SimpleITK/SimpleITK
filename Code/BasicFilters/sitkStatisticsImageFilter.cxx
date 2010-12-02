#include "sitkStatisticsImageFilter.h"
#include "itkStatisticsImageFilter.h"

namespace itk {
namespace simple {

//----------------------------------------------------------------------------

//
// Default constructor that initializes parameters
//
StatisticsImageFilter::StatisticsImageFilter ()
  {
    m_Minimum = -1.0;
    m_Maximum = -1.0;
    m_Mean = -1.0;
    m_Variance = -1.0;

  this->m_MemberFactory.reset( new detail::MemberFunctionFactory<MemberFunctionType>( this ) );

  this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 3 > ();
  this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 2 > ();
  }

//
// ToString
//
std::string StatisticsImageFilter::ToString() const
  {
  std::ostringstream out;
  out << "itk::simple::StatisticsImageFilter\n";
  out << "\tMinimum: " << this->m_Minimum << "\n";
  out << "\tMaximum: " << this->m_Maximum << "\n";
  out << "\tMean: " << this->m_Mean << "\n";
  out << "\tVariance: " << this->m_Variance << "\n";
  return out.str();
  }
//
// Execute
//

Image::Pointer StatisticsImageFilter::Execute ( Image::Pointer image1 )
  {
    ImageDataType type = image1->GetDataType();
    unsigned int dimension = image1->GetDimension();

    return this->m_MemberFactory->GetMemberFunction( type, dimension )( image1 );
  }

//----------------------------------------------------------------------------

//
// ExecuteInternal
//
template <class TImageType>
Image::Pointer StatisticsImageFilter::ExecuteInternal ( Image::Pointer inImage1 )
  {
  typedef TImageType     InputImageType;
  typedef InputImageType OutputImageType;

  typename InputImageType::Pointer image1 =
    dynamic_cast <InputImageType*> ( inImage1->GetImageBase().GetPointer() );

  if ( image1.IsNull() ) {
    // Take some action
    return NULL;
  }

  typedef itk::StatisticsImageFilter<InputImageType> FilterType;

  typename FilterType::Pointer filter = FilterType::New();
  filter->SetInput( image1 );
  filter->Update();
  Image::Pointer out = new Image( filter->GetOutput() );

  return out;
  }

} // end namespace simple
} // end namespace itk
