#include "sitkTransform.h"
#include "itkTransformBase.h"

namespace itk
{
namespace simple
{

  Transform::Transform()
  {
  }

  Transform::~Transform()
  {
  }

  itk::TransformBase* Transform::GetITKBase ( void )
  {
    return NULL;
  }

  void Transform::SetParameters ( const std::vector<double>& parameters )
  {
  }
  std::vector<double> Transform::GetParameters( void ) const
  {
    return std::vector<double>();
  }


  std::string Transform::ToString( void ) const
  {
    return std::string();
  }
}
}


