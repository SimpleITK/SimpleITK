#ifndef __sitkRegularStepGradientDescentOptimizer_h
#define __sitkRegularStepGradientDescentOptimizer_h

#include "sitkMacro.h"
#include "sitkDetail.h"
#include "sitkImage.h"
#include "sitkOptimizer.h"
#include "itkRegularStepGradientDescentOptimizer.h"
#include "sitkMemberFunctionFactory.h"

namespace itk
{
namespace simple
{

  class RegularStepGradientDescentOptimizer : public SOptimizer
  {
  public:
    RegularStepGradientDescentOptimizer();
    virtual ~RegularStepGradientDescentOptimizer();
    virtual ::itk::Optimizer::Pointer GetOptimizer();
  protected:
    SOptimizer* Clone();
  };
}
}

#endif
