#include "sitkRecursiveGaussianImageFilter.h"

namespace itk {
namespace simple {

//----------------------------------------------------------------------------

//
// Default constructor that initializes parameters
//
RecursiveGaussianImageFilter::RecursiveGaussianImageFilter ()
  {
  this->m_Sigma = 1.0;
  this->m_Order = ZeroOrder;
  this->m_NormalizeAcrossScale = false;

  this->m_MemberFactory.reset( new detail::MemberFunctionFactory<MemberFunctionType>( this ) );

  this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 3 > ();
  this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 2 > ();
  }

//
// ToString
//
std::string RecursiveGaussianImageFilter::ToString() const
  {
  std::ostringstream out;
  out << "itk::simple::RecursiveGaussianImageFilter\n"
      << "\tSigma: " << this->m_Sigma << "\n"
      << "\tOrder: " << this->m_Order << "\n"
      << "\tNormalizeAcrossScale: " << this->m_NormalizeAcrossScale << "\n";
  return out.str();
  }


//
// Execute
//
Image::Pointer RecursiveGaussianImageFilter::Execute ( Image::Pointer image )
  {

    PixelIDValueType type = image->GetPixelIDValue();
    unsigned int dimension = image->GetDimension();

    return this->m_MemberFactory->GetMemberFunction( type, dimension )( image );
  }

//----------------------------------------------------------------------------

//
// ExecuteInternal
//
template <class TImageType>
Image::Pointer RecursiveGaussianImageFilter::ExecuteInternal ( Image::Pointer inImage )
  {
  typedef TImageType InputImageType;
  typedef itk::Image<float,InputImageType::ImageDimension> OutputImageType;
  typename InputImageType::Pointer image =
    dynamic_cast <InputImageType*> ( inImage->GetImageBase().GetPointer() );

  if ( image.IsNull() )
    {
    itkGenericExceptionMacro( "Unexpected template dispatch error!" );
    }

  typedef itk::RecursiveGaussianImageFilter<InputImageType, OutputImageType> FilterType;
  typename FilterType::Pointer filter = FilterType::New();

  filter->SetInput ( image );

  filter->SetSigma ( this->m_Sigma );
  filter->SetNormalizeAcrossScale ( this->m_NormalizeAcrossScale );

  // cast the order parameter to the type from the itk filter
  typename FilterType::OrderEnumType internalOrder =
    static_cast<typename FilterType::OrderEnumType>(this->m_Order);
  filter->SetOrder ( internalOrder );

  filter->Update();

  Image::Pointer out = new Image( filter->GetOutput() );
  filter->GetOutput()->DisconnectPipeline();
  return out;
  }

} // end namespace simple
} // end namespace itk
