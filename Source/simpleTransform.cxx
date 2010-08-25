#include "simpleTransform.h"

namespace itk {
  namespace simple {

    Transform::Transform() {
      m_Transform = NULL;
    }

    std::string Transform::toString() {
      std::ostringstream out;
      if ( m_Transform.IsNotNull() ) {
        m_Transform->Print ( out );
      } else {
        out << "m_Transform is NULL";
      }
      return out.str();
    }

    TransformType::Pointer Transform::getITKTransform() {
      return m_Transform;
    }

    Transform& Transform::setITKTransform ( TransformType::Pointer t ) {
      m_Transform = t;
      return *this;
    }
  }
}
