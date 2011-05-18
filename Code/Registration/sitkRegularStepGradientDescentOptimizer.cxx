#include "sitkRegularStepGradientDescentOptimizer.h"

namespace itk
{
namespace simple
{

  SOptimizer* RegularStepGradientDescentOptimizer::Clone()
  {
    return new RegularStepGradientDescentOptimizer();
  }
  RegularStepGradientDescentOptimizer::RegularStepGradientDescentOptimizer()
  {
  }
  RegularStepGradientDescentOptimizer::~RegularStepGradientDescentOptimizer()
  {
  }
  ::itk::Optimizer::Pointer RegularStepGradientDescentOptimizer::GetOptimizer()
  {
    ::itk::RegularStepGradientDescentOptimizer::Pointer optimizer = ::itk::RegularStepGradientDescentOptimizer::New();
    optimizer->SetNumberOfIterations ( 2000 );
    optimizer->SetMinimumStepLength ( .00005 );
    optimizer->SetMaximumStepLength ( 0.1 );
    optimizer->SetMinimize(false);
    return optimizer.GetPointer();
  }


}
}


