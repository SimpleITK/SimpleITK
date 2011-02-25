#ifndef __sitkAffineTransform_h
#define __sitkAffineTransform_h

#include "sitkMacro.h"
#include "sitkDetail.h"
#include "itkAffineTransform.h"

namespace itk
{
namespace simple
{

  class AffineTransform
  {
  public:
    AffineTransform();
    ::itk::TransformBase::Pointer GetTransform ( int dimension );
    std::vector<double> GetOptimizerScales ( int dimension );
  protected:
  };
}
}

#endif
