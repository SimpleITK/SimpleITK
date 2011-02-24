#include "sitkMattesMutualInformationMetric.h"

namespace itk
{
namespace simple
{
  void MattesMutualInformationMetric::Register2DFunctions() {
    m_DualMemberFactory->RegisterMemberFunctions<BasicPixelIDTypeList, BasicPixelIDTypeList, 2, GetMetricMemberFunctionAddressor<MemberFunctionType> > ();
  }
}
}
