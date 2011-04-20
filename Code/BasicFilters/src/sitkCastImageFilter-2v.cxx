#include "sitkCastImageFilter.h"
#include "sitkCastImageFilter.txx"


namespace itk
{
namespace simple
{


void CastImageFilter::RegisterMemberFactory2v()
{

  // cast between vector images
  m_DualMemberFactory->RegisterMemberFunctions<VectorPixelIDTypeList, VectorPixelIDTypeList, 2, CastAddressor<MemberFunctionType> > ();

  // basic to vector
  m_DualMemberFactory->RegisterMemberFunctions<BasicPixelIDTypeList, VectorPixelIDTypeList, 2, ToVectorAddressor<MemberFunctionType> > ();

}

} // end namespace simple
} // end namespace itk
