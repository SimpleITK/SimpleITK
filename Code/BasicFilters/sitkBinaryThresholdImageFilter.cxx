#include "sitkBinaryThresholdImageFilter.h"

#include <itkBinaryThresholdImageFilter.h>

namespace itk {
namespace simple {

//----------------------------------------------------------------------------

//
// Default constructor that initializes parameters
//
BinaryThresholdImageFilter::BinaryThresholdImageFilter ()
  {
  this->m_LowerThreshold = 0.0;
  this->m_UpperThreshold = 255.0;

  this->m_MemberFactory.reset( new detail::MemberFunctionFactory<MemberFunctionType>( this ) );

  this->m_MemberFactory->RegisterMemberFunctions< PixelTypeList, 3 > ();
  this->m_MemberFactory->RegisterMemberFunctions< PixelTypeList, 2 > ();
  }

//
// ToString
//
std::string BinaryThresholdImageFilter::ToString() const
  {
  std::ostringstream out;
  out << "itk::simple::BinaryThresholdImageFilter\n"
      << "\tLowerThreshold: " << this->m_LowerThreshold << "\n"
      << "\tUpperThreshold: " << this->m_UpperThreshold << "\n";
  return out.str();
  }


//
// Execute
//
Image::Pointer BinaryThresholdImageFilter::Execute ( Image::Pointer image )
  {

    ImageDataType type = image->GetDataType();
    unsigned int dimension = image->GetDimension();

    return this->m_MemberFactory->GetMemberFunction( type, dimension )( image );
  }

//----------------------------------------------------------------------------

//
// ExecuteInternal
//
template <class TImageType>
Image::Pointer BinaryThresholdImageFilter::ExecuteInternal ( Image::Pointer inImage )
  {
  typedef TImageType InputImageType;
  typedef itk::Image<float,InputImageType::ImageDimension> OutputImageType;
  typename InputImageType::Pointer image =
    dynamic_cast <InputImageType*> ( inImage->GetImageBase().GetPointer() );

  if ( image.IsNull() ) {
    // Take some action
    return NULL;
  }

  typedef itk::BinaryThresholdImageFilter<InputImageType, OutputImageType> FilterType;
  typename FilterType::Pointer filter = FilterType::New();

  filter->SetInput ( image );

  sitkTransferMemberVariableToFilterMacro( LowerThreshold );
  sitkTransferMemberVariableToFilterMacro( UpperThreshold );

  filter->Update();

  Image::Pointer out = new Image( filter->GetOutput() );
  filter->GetOutput()->DisconnectPipeline();
  return out;
  }

} // end namespace simple
} // end namespace itk
