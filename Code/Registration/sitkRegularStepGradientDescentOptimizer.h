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

  class RegularStepGradientDescentOptimizer
  {
  public:
    RegularStepGradientDescentOptimizer() {};
    // Could potentially set some parameters here
    ::itk::Optimizer::Pointer GetOptimizer()
    {
      ::itk::RegularStepGradientDescentOptimizer::Pointer optimizer = ::itk::RegularStepGradientDescentOptimizer::New();
      optimizer->SetNumberOfIterations ( 2000 );
      optimizer->SetMinimumStepLength ( .0005 );
      optimizer->SetMaximumStepLength ( 10.0 );
      optimizer->SetMinimize(true);
      return optimizer.GetPointer();
    }
  protected:
  };
}
}

#endif
