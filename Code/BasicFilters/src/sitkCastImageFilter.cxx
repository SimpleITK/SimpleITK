#include "sitkCastImageFilter.h"


namespace itk
{
namespace simple
{


//----------------------------------------------------------------------------

//
// Default constructor that initializes parameters
//
CastImageFilter::CastImageFilter ()
{
  this->m_OutputPixelType = sitkFloat32;

  m_DualMemberFactory.reset( new  detail::DualMemberFunctionFactory<MemberFunctionType>( this ) );

  this->RegisterMemberFactory2();
  this->RegisterMemberFactory2v();
  this->RegisterMemberFactory2l();
  this->RegisterMemberFactory3();
  this->RegisterMemberFactory3v();
  this->RegisterMemberFactory3l();

}

//
// ToString
//
std::string CastImageFilter::ToString() const
{
  std::ostringstream out;
  out << "itk::simple::CastImageFilter\n"
      << "\tOutputPixelType: " << this->m_OutputPixelType << " "
      << GetPixelIDValueAsString( this->m_OutputPixelType ) << "\n";
  return out.str();
}

//
// Set/Get Methods for output pixel type
//

CastImageFilter::Self& CastImageFilter::SetOutputPixelType( PixelIDValueType pixelID )
{
  this->m_OutputPixelType = pixelID;
  return *this;
}

PixelIDValueType CastImageFilter::GetOutputPixelType( void ) const
{
  return this->m_OutputPixelType;
}


//
// Execute
//
Image CastImageFilter::Execute ( const Image& image )
{

  const PixelIDValueType inputType = image.GetPixelIDValue();
  const PixelIDValueType outputType = this->m_OutputPixelType;
  const unsigned int dimension = image.GetDimension();

  if (this->m_DualMemberFactory->HasMemberFunction( inputType, outputType,  dimension ) )
    {
    return this->m_DualMemberFactory->GetMemberFunction( inputType, outputType, dimension )( image );
    }

  sitkExceptionMacro( << "Filter does not support casting from casting " << itk::simple::GetPixelIDValueAsString (inputType) << " to "
                      << itk::simple::GetPixelIDValueAsString (outputType) );

}


//----------------------------------------------------------------------------


Image Cast ( const Image& image, PixelIDValueType pixelID ) {
  CastImageFilter filter;
  return filter.SetOutputPixelType ( pixelID ).Execute ( image );
}


} // end namespace simple
} // end namespace itk
