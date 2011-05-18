#ifndef __sitkInterpolate_h
#define __sitkInterpolate_h

#include "sitkMacro.h"
#include "sitkDetail.h"
#include "sitkImage.h"
#include "itkObject.h"
#include "sitkMemberFunctionFactory.h"

namespace itk
{
namespace simple
{
  class Registration;
  class ResampleImageFilter;
  class Interpolate
  {
  public:
    Interpolate(){};
    virtual ~Interpolate(){};
    virtual ::itk::Object::Pointer GetInterpolator ( const Image &image ) = 0;
  protected:
    friend class Registration;
    friend class ResampleImageFilter;
    virtual Interpolate* Clone() = 0;
  };
}
}

#endif
