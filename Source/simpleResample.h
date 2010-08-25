#ifndef __simpleResample_h
#define __simpleResample_h

#include <SimpleITKMacro.h>
#include <simpleImage.h>
#include <simpleTransform.h>

namespace itk {
  namespace simple {
    enum InterpolationType {
      LinearInterpolation,
      SincInterpolation,
      NearestNeighborInterpolation,
      BSplineInterpolation
    };

    class Resample {
    public:
      Resample();
      
      Resample& setTransform ( Transform t );
      Transform getTransform();

      Resample& setInterpolationType ( InterpolationType );
      InterpolationType getInterpolationType();

      // Methods to set the output spacing, etc...
      Resample& setOutputCoordinateSystemFromImage ( Image::Pointer );

      Image::Pointer execute ( Image::Pointer );

    private:
      InterpolationType m_InterpolationType;
      Transform m_Transform;
      Image::Pointer m_OutputSpaceImage;
      template <class T> Image::Pointer executeInternal ( Image::Pointer image );
    };
  }
}


#endif
