#include "sitkCastImageFilter.h"
#include "sitkCastImageFilter.txx"


namespace itk
{
namespace simple
{


void CastImageFilter::RegisterMemberFactory3v()
{

  // cast between vector images
  m_DualMemberFactory->RegisterMemberFunctions<VectorPixelIDTypeList, VectorPixelIDTypeList, 3, CastAddressor<MemberFunctionType> > ();

  // basic to vector
  m_DualMemberFactory->RegisterMemberFunctions<BasicPixelIDTypeList, VectorPixelIDTypeList, 3, ToVectorAddressor<MemberFunctionType> > ();
}

} // end namespace simple
} // end namespace itk
