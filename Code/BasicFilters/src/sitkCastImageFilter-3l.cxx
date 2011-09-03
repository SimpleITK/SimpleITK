#include "sitkCastImageFilter.h"
#include "sitkCastImageFilter.txx"


namespace itk
{
namespace simple
{


void CastImageFilter::RegisterMemberFactory3l()
{
  // basic to Label
  m_DualMemberFactory->RegisterMemberFunctions<IntegerPixelIDTypeList, LabelPixelIDTypeList, 3, ToLabelAddressor<MemberFunctionType> > ();

 // Label to basic
  m_DualMemberFactory->RegisterMemberFunctions<LabelPixelIDTypeList, IntegerPixelIDTypeList, 3, LabelToAddressor<MemberFunctionType> > ();

}

} // end namespace simple
} // end namespace itk
