#include "sitkCastImageFilter.h"
#include "sitkCastImageFilter.txx"


namespace itk
{
namespace simple
{


void CastImageFilter::RegisterMemberFactory2l()
{
  // basic to Label
  m_DualMemberFactory->RegisterMemberFunctions<IntegerPixelIDTypeList, LabelPixelIDTypeList, 2, ToLabelAddressor<MemberFunctionType> > ();

 // Label to basic
  m_DualMemberFactory->RegisterMemberFunctions<LabelPixelIDTypeList, IntegerPixelIDTypeList, 2, LabelToAddressor<MemberFunctionType> > ();
}

} // end namespace simple
} // end namespace itk
