#ifndef __simpleAffineRegistration_h
#define __simpleAffineRegistration_h

#include <SimpleITKMacro.h>
#include <simpleImage.h>
#include <simpleTransform.h>

namespace itk {
  namespace simple {

    class AffineRegistration {
    public:
      typedef AffineRegistration Self;
   
      AffineRegistration();

      // Print ourselves out
      std::string toString();

      AffineRegistration& setNumberOfIterations ( unsigned int i );
      unsigned int getNumberOfIterations();
      
       Transform execute ( Image::Pointer fixed, Image::Pointer moving );
    private:
      unsigned int m_NumberOfIterations;
      template <class TFixed> Transform executeInternalOne ( Image::Pointer fixed, Image::Pointer moving );
      template <class TFixed, class TMoving> Transform executeInternalTwo ( Image::Pointer fixed, Image::Pointer moving );
    };
  }
}
#endif
