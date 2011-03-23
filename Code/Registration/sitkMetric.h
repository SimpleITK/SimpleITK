#ifndef __sitkMetric_h
#define __sitkMetric_h

#include "sitkMacro.h"

#include "sitkDetail.h"
#include "sitkImage.h"
#include "sitkPixelIDTokens.h"
#include "sitkPixelContainer.h"
#include "itkImageToImageMetric.h"
#include "sitkMemberFunctionFactory.h"

namespace itk
{
namespace simple
{
  class Registration;
  class Metric
  {
  public:
    Metric() {};
    virtual ~Metric() {};
    virtual ::itk::SingleValuedCostFunction::Pointer GetMetric ( Image* image ) { return NULL; };
  protected:
    friend class Registration;
    virtual Metric* Clone() { return new Metric ( *this ); }
  };
}
}

#endif
