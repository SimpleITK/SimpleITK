#ifndef __sitkAffineTransform_h
#define __sitkAffineTransform_h

#include "sitkMacro.h"
#include "sitkDetail.h"
#include "sitkTransform.h"
#include "itkAffineTransform.h"

namespace itk
{
namespace simple
{
class AffineTransform : public Transform
  {
  public:
    AffineTransform();
    virtual ::itk::TransformBase::Pointer GetTransform ( int dimension );
    virtual std::vector<double> GetOptimizerScales ( int dimension );
  protected:
    virtual Transform* Clone() { std::cout << "Cloned an AffineTransform" << std::endl; return new AffineTransform ( *this ); }
  };
}
}

#endif
