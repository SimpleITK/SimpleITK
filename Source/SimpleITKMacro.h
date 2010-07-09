#ifndef __SimpleITKMacro_h
#define __SimpleITKMacro_h

#include <stdint.h>
#include <itkImageBase.h>
#include <itkImage.h>
#include <itkLightObject.h>
#include <itkSmartPointer.h>

// Define macros to aid in the typeless layer
typedef itk::ImageBase<3> SimpleImageBase;

namespace itk {
  namespace simple {

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

#endif
