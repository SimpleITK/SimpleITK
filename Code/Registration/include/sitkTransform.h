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

class PimpleTransformBase;

  class Transform
  {
  public:

    /** Questionable default constructable
     */
    Transform();
    virtual ~Transform( void );

    // TODO determine best copy syntax
    virtual Transform * Clone( void ) { return NULL; }
    const Transform &operator=( const Transform & ) { return *this; };
    Transform( const Transform & ) {};


    itk::TransformBase* GetITKBase( void );
    const itk::TransformBase* GetITKBase( void ) const;

    /** Set/Get Parameter
     */
    void SetParameters ( const std::vector<double>& parameters );
    virtual std::vector<double> GetParameters( void ) const ;

    std::string ToString( void ) const;


  protected:

    PimpleTransformBase *m_PimpleTransform;


  };
}
}

#endif
