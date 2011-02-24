#ifndef __sitkMattesMutualInformationMetric_h
#define __sitkMattesMutualInformationMetric_h

#include "sitkMacro.h"

#include "sitkDetail.h"
#include "sitkImage.h"
#include "sitkPixelIDTokens.h"
#include "sitkPixelContainer.h"
#include "itkMattesMutualInformationImageToImageMetric.h"
#include "sitkDualMemberFunctionFactory.h"

#include <memory>

namespace itk
{
namespace simple
{

  class PimpleMetricBase
  {
  public:
    virtual ~PimpleMetricBase() {};
  };


  class MattesMutualInformationMetric
  {
  public:
    MattesMutualInformationMetric();
    ::itk::SingleValuedCostFunction::Pointer GetMetric ( Image* imageA, Image* imageB );

  protected:
    template<class TFixedImage, class TMovingImage>
    ::itk::SingleValuedCostFunction::Pointer GetMetricInternal ( Image* imageA, Image* imageB );
    void Register2DFunctions();
    void Register3DFunctions();

    template < class TMemberFunctionPointer >
    struct GetMetricMemberFunctionAddressor
    {
      typedef typename ::detail::FunctionTraits<TMemberFunctionPointer>::ClassType ObjectType;

      template< typename TFixedImage, typename TMovingImage >
      TMemberFunctionPointer operator() ( void ) const
      {
        return &ObjectType::template GetMetricInternal < TFixedImage, TMovingImage >;
      }
    };


    typedef ::itk::SingleValuedCostFunction::Pointer (MattesMutualInformationMetric::*MemberFunctionType)( Image* imageA, Image* imageB );
    friend struct GetMetricMemberFunctionAddressor<MemberFunctionType>;
    std::auto_ptr<detail::DualMemberFunctionFactory<MemberFunctionType> > m_DualMemberFactory;
  };
}
}

#endif
