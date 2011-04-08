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
    Transform();
    virtual ~Transform();
    virtual ::itk::TransformBase::Pointer GetTransform ( int dimension );
    virtual Transform& SetParameters ( const std::vector<double>& parameters );
    virtual std::vector<double> GetParameters();
    virtual std::vector<double> GetOptimizerScales ( int dimension );
  protected:
    std::vector<double> m_Parameters;
    friend class Registration;
    friend class ResampleImageFilter;
    virtual Transform* Clone();
  };
}
}

#endif
