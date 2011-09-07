#include "sitkTransform.h"
#include "itkTransformBase.h"

#include "itkIdentityTransform.h"
#include "itkTranslationTransform.h"
#include "itkScaleTransform.h"
#include "itkScaleLogarithmicTransform.h"
#include "itkQuaternionRigidTransform.h"
#include "itkVersorTransform.h"
#include "itkAffineTransform.h"

namespace itk
{
namespace simple
{

class PimpleTransformBase
{
public:
  virtual ~PimpleTransformBase( void ) {};

  virtual TransformBase::Pointer GetTransformBase( void ) = 0;
  virtual TransformBase::ConstPointer GetTransformBase( void ) const = 0;

  virtual unsigned int GetInputDimension( void ) const = 0;
  virtual unsigned int GetOutputDimension( void ) const = 0;

  void SetFixedParameters( const std::vector< double > &inParams )
    {
      itk::TransformBase::ParametersType p( inParams.size() );

      // todo check expected number of Fixed parameters
      std::copy( inParams.begin(), inParams.end(), p.begin() );
      this->GetTransformBase()->SetFixedParameters( p );
    }
  std::vector< double >  GetFixedParameters( void ) const
    {
      const itk::TransformBase::ParametersType &p = this->GetTransformBase()->GetFixedParameters();
      return std::vector< double >( p.begin(), p.end() );
    }

  unsigned int GetNumberOfParameters( void ) const { return this->GetTransformBase()->GetNumberOfParameters(); }


  void SetParameters( const std::vector< double > &inParams )
    {
      itk::TransformBase::ParametersType p( inParams.size() );

      // todo check expected number of Parameters
      std::copy( inParams.begin(), inParams.end(), p.begin() );
      this->GetTransformBase()->SetParameters( p );
    }
  std::vector< double > GetParameters( void ) const
    {
      const itk::TransformBase::ParametersType &p = this->GetTransformBase()->GetParameters();
      return std::vector< double >( p.begin(), p.end() );
    }


protected:

};

template< typename TTransformType >
class PimpleTransform
  : public PimpleTransformBase
{
public:
  typedef TTransformType                   TransformType;
  typedef typename TransformType::Pointer  TransformPointer;

  static const unsigned int InputDimension = TTransformType::InputSpaceDimension;
  static const unsigned int OutputDimension = TTransformType::OutputSpaceDimension;

  PimpleTransform( )
    {
      this->m_Transform = TransformType::New();
    }

  virtual TransformBase::Pointer GetTransformBase( void ) { return this->m_Transform.GetPointer(); }
  virtual TransformBase::ConstPointer GetTransformBase( void ) const { return this->m_Transform.GetPointer(); }

  virtual unsigned int GetInputDimension( void ) const { return InputDimension; }
  virtual unsigned int GetOutputDimension( void ) const { return OutputDimension; }



private:

  TransformPointer m_Transform;
};

Transform::Transform( )
  : m_PimpleTransform( NULL )
  {
    m_PimpleTransform = new PimpleTransform<itk::IdentityTransform< double, 3 > >();
  }

  Transform::Transform( unsigned int dimensions, TransformEnum type)
    : m_PimpleTransform( NULL )
  {
    if ( dimensions == 2 )
      {
      this->InternalIntitialization<2 >(type);
      }
    else if ( dimensions == 3 )
      {
      this->InternalIntitialization<3>(type);
      }
    else
      {
      sitkExceptionMacro("Invalid dimension for transform");
      }
  }

  Transform::~Transform()
  {
    delete m_PimpleTransform;
    this->m_PimpleTransform = NULL;
  }


  template< unsigned int VDimension>
  void  Transform::InternalIntitialization(  TransformEnum type )
  {
    switch( type )
      {

      case Translation:
        m_PimpleTransform = new PimpleTransform<itk::TranslationTransform< double, VDimension > >();
        break;
      case Scale:
        m_PimpleTransform = new PimpleTransform<itk::ScaleTransform< double, VDimension > >();
        break;
      case ScaleLogarithmic:
        m_PimpleTransform = new PimpleTransform<itk::ScaleLogarithmicTransform< double, VDimension > >();
        break;
      case QuaternionRigid:
        // todo what todo about transform which require a specific dimension
        assert( VDimension == 3 );
        m_PimpleTransform = new PimpleTransform<itk::QuaternionRigidTransform< double > >();
        break;
      case Versor:
        // todo what todo about transform which require a specific dimension
        assert( VDimension == 3 );
        m_PimpleTransform = new PimpleTransform<itk::VersorTransform< double > >();
        break;
      case Affine:
        m_PimpleTransform = new PimpleTransform<itk::AffineTransform< double, VDimension > >();
        break;
      case Identity:
      default:
        m_PimpleTransform = new PimpleTransform<itk::IdentityTransform< double, VDimension > >();
      }
  }


  itk::TransformBase* Transform::GetITKBase ( void )
  {
    assert( m_PimpleTransform );
    return this->m_PimpleTransform->GetTransformBase();
  }

  const itk::TransformBase* Transform::GetITKBase ( void ) const
  {
    assert( m_PimpleTransform );
    return this->m_PimpleTransform->GetTransformBase();
  }

  unsigned int  Transform::GetDimension( void ) const
  {
    assert( m_PimpleTransform );
    return this->m_PimpleTransform->GetInputDimension();
  }

  void Transform::SetParameters ( const std::vector<double>& parameters )
  {
    assert( m_PimpleTransform );
    this->m_PimpleTransform->SetParameters( parameters );
  }
  std::vector<double> Transform::GetParameters( void ) const
  {
    assert( m_PimpleTransform );
    return this->m_PimpleTransform->GetParameters();
  }


  std::string Transform::ToString( void ) const
  {
    return std::string();
  }
}
}


