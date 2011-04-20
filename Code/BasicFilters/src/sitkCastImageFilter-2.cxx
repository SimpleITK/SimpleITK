#include "sitkCastImageFilter.h"
#include "sitkCastImageFilter.txx"


namespace itk
{
namespace simple
{


void CastImageFilter::RegisterMemberFactory2()
{
  // cast between complex pixels and complex pixel
  m_DualMemberFactory->RegisterMemberFunctions<ComplexPixelIDTypeList, ComplexPixelIDTypeList, 2, CastAddressor<MemberFunctionType> > ();

  // cast between basic pixels and complex number pixels
  m_DualMemberFactory->RegisterMemberFunctions<BasicPixelIDTypeList, ComplexPixelIDTypeList, 2, CastAddressor<MemberFunctionType> > ();

  // cast between basic images
  m_DualMemberFactory->RegisterMemberFunctions<BasicPixelIDTypeList, BasicPixelIDTypeList, 2, CastAddressor<MemberFunctionType> > ();

}

} // end namespace simple
} // end namespace itk
