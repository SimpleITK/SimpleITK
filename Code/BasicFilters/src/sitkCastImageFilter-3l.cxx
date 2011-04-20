#include "sitkCastImageFilter.h"
#include "sitkCastImageFilter.txx"


namespace itk
{
namespace simple
{


void CastImageFilter::RegisterMemberFactory3l()
{
  // basic to Label
  m_DualMemberFactory->RegisterMemberFunctions<BasicPixelIDTypeList, LabelPixelIDTypeList, 3, ToLabelAddressor<MemberFunctionType> > ();
}

} // end namespace simple
} // end namespace itk
