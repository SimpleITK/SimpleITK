#include "sitkCastImageFilter.h"
#include "sitkCastImageFilter.txx"


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

  // cast between complex pixels and complex pixel
  m_DualMemberFactory->RegisterMemberFunctions<ComplexPixelIDTypeList, ComplexPixelIDTypeList, 2, CastAddressor<MemberFunctionType> > ();
  m_DualMemberFactory->RegisterMemberFunctions<ComplexPixelIDTypeList, ComplexPixelIDTypeList, 3, CastAddressor<MemberFunctionType> > ();

  // cast between basic pixels and complex number pixels
  m_DualMemberFactory->RegisterMemberFunctions<BasicPixelIDTypeList, ComplexPixelIDTypeList, 2, CastAddressor<MemberFunctionType> > ();
  m_DualMemberFactory->RegisterMemberFunctions<BasicPixelIDTypeList, ComplexPixelIDTypeList, 3, CastAddressor<MemberFunctionType> > ();

  // cast between basic images
  m_DualMemberFactory->RegisterMemberFunctions<BasicPixelIDTypeList, BasicPixelIDTypeList, 2, CastAddressor<MemberFunctionType> > ();
  m_DualMemberFactory->RegisterMemberFunctions<BasicPixelIDTypeList, BasicPixelIDTypeList, 3, CastAddressor<MemberFunctionType> > ();

  // cast between vector images
  m_DualMemberFactory->RegisterMemberFunctions<VectorPixelIDTypeList, VectorPixelIDTypeList, 2, CastAddressor<MemberFunctionType> > ();
  m_DualMemberFactory->RegisterMemberFunctions<VectorPixelIDTypeList, VectorPixelIDTypeList, 3, CastAddressor<MemberFunctionType> > ();

  // basic to vector
  m_DualMemberFactory->RegisterMemberFunctions<BasicPixelIDTypeList, VectorPixelIDTypeList, 2, ToVectorAddressor<MemberFunctionType> > ();
  m_DualMemberFactory->RegisterMemberFunctions<BasicPixelIDTypeList, VectorPixelIDTypeList, 3, ToVectorAddressor<MemberFunctionType> > ();

  // basic to Label
  m_DualMemberFactory->RegisterMemberFunctions<BasicPixelIDTypeList, LabelPixelIDTypeList, 2, ToLabelAddressor<MemberFunctionType> > ();
  m_DualMemberFactory->RegisterMemberFunctions<BasicPixelIDTypeList, LabelPixelIDTypeList, 3, ToLabelAddressor<MemberFunctionType> > ();
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


} // end namespace simple
} // end namespace itk
