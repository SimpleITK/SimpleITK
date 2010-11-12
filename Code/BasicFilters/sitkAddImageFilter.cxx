#include "sitkAddImageFilter.h"
#include "itkAddImageFilter.h"

namespace itk {
namespace simple {

//----------------------------------------------------------------------------

//
// Default constructor that initializes parameters
//
AddImageFilter::AddImageFilter ()
  {

  this->m_MemberFactory.reset( new detail::MemberFunctionFactory<Self>( this ) );

  this->m_MemberFactory->RegisterMemberFunctions< PixelTypeList, 3 > ();
  this->m_MemberFactory->RegisterMemberFunctions< PixelTypeList, 2 > ();
  }

//
// ToString
//
std::string AddImageFilter::ToString()
  {
  std::ostringstream out;
  out << "itk::simple::AddImageFilter\n";
  return out.str();
  }
//
// Execute
//
Image::Pointer AddImageFilter::Execute ( Image::Pointer image1,  Image::Pointer image2)
  {

    ImageDataType type = image1->GetDataType();
    unsigned int dimension = image1->GetDimension();

    // todo need better error handling and potential type conversion
    if ( type != image2->GetDataType() ||
         dimension != image2->GetDimension() )
      {
      std::cerr << "Both image for add filter don't match type or dimension!" << std::endl;
      throw;
      }

    return this->m_MemberFactory->GetMemberFunction( type, dimension )( image1, image2 );
  }

//----------------------------------------------------------------------------

//
// ExecuteInternal
//
template <class TImageType>
Image::Pointer AddImageFilter::ExecuteInternal ( Image::Pointer inImage1,  Image::Pointer inImage2 )
  {
  typedef TImageType     InputImageType;
  typedef InputImageType OutputImageType;

  typename InputImageType::Pointer image1 =
    dynamic_cast <InputImageType*> ( inImage1->GetImageBase().GetPointer() );

  typename InputImageType::Pointer image2 =
  dynamic_cast <InputImageType*> ( inImage2->GetImageBase().GetPointer() );

  if ( image1.IsNull() || image2.IsNull() ) {
    // Take some action
    return NULL;
  }

  typedef itk::AddImageFilter<InputImageType, InputImageType, OutputImageType> FilterType;

  typename FilterType::Pointer filter = FilterType::New();
  filter->SetInput1( image1 );
  filter->SetInput2( image2 );
  filter->InPlaceOn();

  Image::Pointer out = new Image( filter->GetOutput() );

  return out;
  }

} // end namespace simple
} // end namespace itk
