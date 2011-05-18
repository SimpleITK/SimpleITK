#ifndef __sitkOptimizer_h
#define __sitkOptimizer_h

#include "sitkMacro.h"
#include "sitkDetail.h"
#include "sitkImage.h"
#include "itkOptimizer.h"
#include "sitkMemberFunctionFactory.h"

namespace itk
{
namespace simple
{
  class Registration;
  class SOptimizer
  {
  public:
    SOptimizer() {};
    virtual ~SOptimizer() {};
    virtual ::itk::Optimizer::Pointer GetOptimizer() { return NULL; }
  protected:
    friend class Registration;
    virtual SOptimizer* Clone() { return new SOptimizer ( *this ); }
  };
}
}

#endif
