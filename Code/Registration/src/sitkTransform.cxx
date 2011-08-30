#include "sitkTransform.h"

namespace itk
{
namespace simple
{

  Transform::Transform() {};
  Transform::~Transform() {};
  ::itk::TransformBase::Pointer Transform::GetTransform ( int dimension ) { return NULL; };
  Transform& Transform::SetParameters ( const std::vector<double>& parameters )
  {
    m_Parameters.resize ( parameters.size() );
    m_Parameters = parameters;
    return *this;
  }
  std::vector<double> Transform::GetParameters()
  {
    return m_Parameters;
  }
  std::vector<double> Transform::GetOptimizerScales ( int dimension )
  {
    return std::vector<double>();
  }

  Transform* Transform::Clone()
  {
    return new Transform ( *this );
  }
}
}


