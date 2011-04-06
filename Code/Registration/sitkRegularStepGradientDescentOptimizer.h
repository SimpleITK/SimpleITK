#ifndef __sitkRegularStepGradientDescentOptimizer_h
#define __sitkRegularStepGradientDescentOptimizer_h

#include "sitkMacro.h"
#include "sitkDetail.h"
#include "sitkImage.h"
#include "itkRegularStepGradientDescentOptimizer.h"
#include "sitkMemberFunctionFactory.h"

namespace itk
{
namespace simple
{

class RegularStepGradientDescentOptimizer : public Optimizer
  {
  public:
    RegularStepGradientDescentOptimizer();
    virtual ::itk::Optimizer::Pointer GetOptimizer();
  protected:
    virtual Optimizer* Clone();
  };
}
}

#endif
