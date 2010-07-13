#ifndef __SimpleITKMacro_h
#define __SimpleITKMacro_h


// Ideally, take the types from the C99 standard.  However,
// VS 8 does not have stdint.h, but they are defined anyway.
#ifndef _MSC_VER
	#include <stdint.h>
#endif

#include <itkImageBase.h>
#include <itkImage.h>
#include <itkLightObject.h>
#include <itkSmartPointer.h>


namespace itk {
  namespace simple {

    // Define macros to aid in the typeless layer
    typedef itk::ImageBase<3> SimpleImageBase;

    // To add a new type you must:
    // 1. Add an entry to ImageDataType
    // 2. Add to the sitkDataTypeSwitch
    // 3. Add the new type to ImageFileReader/ImageFileWriter

    enum ImageDataType {
      sitkUInt8,    // Unsigned 8 bit integer
      sitkInt16,   // Signed 16 bit integer
      sitkInt32,   // Signed 32 bit integer
      sitkFloat32,  // 32 bit float
    };


#define sitkImageDataTypeCase(typeN, type, call ) \
    case typeN: { typedef type DataType; call; }; break

#define sitkImageDataTypeSwitch( call ) \
    sitkImageDataTypeCase ( sitkUInt8, uint8_t, call ); \
    sitkImageDataTypeCase ( sitkInt16, int16_t, call ); \
    sitkImageDataTypeCase ( sitkInt32, int32_t, call ); \
    sitkImageDataTypeCase ( sitkFloat32, float, call );




  }
}    

// Tell the compiler that we are going to explicitly instantiate these templates.
extern template class itk::Image<uint8_t,3>;
extern template class itk::Image<uint16_t,3>;
extern template class itk::Image<uint32_t,3>;
extern template class itk::Image<float,3>;

#endif
