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
  class Interpolate
  {
  public:
    Interpolate(){};
    virtual ~Interpolate(){};
    virtual ::itk::Object::Pointer GetInterpolator ( Image* image ) { return NULL; };
  protected:
    friend class Registration;
    virtual Interpolate* Clone() { return new Interpolate ( *this ); }
  };
}
}

#endif
