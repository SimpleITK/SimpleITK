#ifndef __sitkMattesMutualInformationMetric_h
#define __sitkMattesMutualInformationMetric_h

#include "sitkMacro.h"

#include "sitkDetail.h"
#include "sitkImage.h"
#include "sitkPixelIDTokens.h"
#include "sitkMetric.h"
#include "itkMattesMutualInformationImageToImageMetric.h"
#include "sitkMemberFunctionFactory.h"

#include <memory>

namespace itk
{
namespace simple
{

class MattesMutualInformationMetric : public Metric
  {
  public:
    MattesMutualInformationMetric();
    virtual ::itk::SingleValuedCostFunction::Pointer GetMetric ( const Image &image );

  protected:
    template<class TImage>
    ::itk::SingleValuedCostFunction::Pointer GetMetricInternal ( const Image &image );

    template < class TMemberFunctionPointer >
    struct GetMetricMemberFunctionAddressor
    {
      typedef typename ::detail::FunctionTraits<TMemberFunctionPointer>::ClassType ObjectType;

      template< typename TImage >
      TMemberFunctionPointer operator() ( void ) const
      {
        return &ObjectType::template GetMetricInternal < TImage >;
      }
    };

    typedef ::itk::SingleValuedCostFunction::Pointer (MattesMutualInformationMetric::*MemberFunctionType)( const Image &image );
    friend struct GetMetricMemberFunctionAddressor<MemberFunctionType>;
    std::auto_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;
    virtual Metric* Clone() { return new MattesMutualInformationMetric ( *this ); }
  };
}
}

#endif
