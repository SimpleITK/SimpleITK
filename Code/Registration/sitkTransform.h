#ifndef __sitkTransform_h
#define __sitkTransform_h

#include "sitkMacro.h"
#include "sitkDetail.h"
#include "itkTransform.h"

namespace itk
{
namespace simple
{
  class Registration;
  class ResampleImageFilter;
  class Transform
  {
  public:
    Transform() {};
    virtual ~Transform() {};
    virtual ::itk::TransformBase::Pointer GetTransform ( int dimension ) { Unused( dimension ); return NULL; };
    virtual std::vector<double> GetOptimizerScales ( int dimension ) { Unused( dimension ); return std::vector<double>(); };
  protected:
    friend class Registration;
    friend class ResampleImageFilter;
    virtual Transform* Clone() { std::cout << "Cloned generic Transform" << std::endl; return new Transform ( *this ); }
  };
}
}

#endif
