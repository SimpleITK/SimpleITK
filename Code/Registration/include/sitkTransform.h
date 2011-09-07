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

enum TransformEnum { Identity,
                     Translation,
                     Scale,
                     ScaleLogarithmic,
                     QuaternionRigid,
                     Versor,
                     Affine };

  class Transform
  {
  public:

    /** Questionable default constructable
     */
    Transform( void );
    Transform( unsigned int dimensions, TransformEnum type);
    virtual ~Transform( void );

    //
    Transform &operator=( const Transform & );
    Transform( const Transform & );


    itk::TransformBase* GetITKBase( void );
    const itk::TransformBase* GetITKBase( void ) const;

    unsigned int GetDimension( void ) const;

    /** Set/Get Parameter
     */
    void SetParameters ( const std::vector<double>& parameters );
    std::vector<double> GetParameters( void ) const ;

    std::string ToString( void ) const;


  protected:

  private:

    template< unsigned int VDimension>
    void InternalIntitialization(  TransformEnum type );

    PimpleTransformBase *m_PimpleTransform;


  };
}
}

#endif
