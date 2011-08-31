#ifndef __sitkTransform_h
#define __sitkTransform_h

#include "sitkMacro.h"
#include <vector>

namespace itk
{

// Forward decalaration for pointer
class TransformBase;

namespace simple
{
  class Registration;
  class ResampleImageFilter;
  class Transform
  {
  public:

    /** Questionable default constructable
     */
    Transform();
    virtual ~Transform( void );

    // TODO determine best copy syntax
    virtual Transform * Clone( void ) { return NULL; }

     itk::TransformBase* GetITKBase ( void );

    /** Set/Get Parameter
     */
    void SetParameters ( const std::vector<double>& parameters );
    virtual std::vector<double> GetParameters( void ) const ;

    std::string ToString( void ) const;

  };
}
}

#endif
