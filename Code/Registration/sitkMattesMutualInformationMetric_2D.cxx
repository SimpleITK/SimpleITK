#include "sitkMattesMutualInformationMetric.h"

namespace itk
{
namespace simple
{
  void MattesMutualInformationMetric::Register3DFunctions() {
    m_DualMemberFactory->RegisterMemberFunctions<BasicPixelIDTypeList, BasicPixelIDTypeList, 3, GetMetricMemberFunctionAddressor<MemberFunctionType> > ();
  }
}
}
