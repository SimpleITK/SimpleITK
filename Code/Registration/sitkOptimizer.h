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
  class Optimizer
  {
  public:
    Optimizer() {};
    virtual ~Optimizer() {};
    virtual ::itk::Optimizer::Pointer GetOptimizer() { return NULL; }
  protected:
    friend class Registration;
    virtual Optimizer* Clone() { return new Optimizer ( *this ); }
  };
}
}

#endif
