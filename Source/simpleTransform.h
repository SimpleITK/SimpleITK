#ifndef __simpleTransform_h
#define __simpleTransform_h

#include <SimpleITKMacro.h>
#include <simpleImage.h>
#include <itkTransform.h>
#include <itkTransformBase.h>

namespace itk {
  namespace simple {
    typedef itk::Transform<double,3,3> TransformType;

    class Transform {
    public:
      typedef Transform Self;

      Transform();
      
      // Print ourselves out
      std::string toString();

      TransformType::Pointer getITKTransform();
      Self& setITKTransform ( TransformType::Pointer );
    private:
      TransformType::Pointer m_Transform;
    };
  }
}
#endif
