#ifndef __SimpleITKMacro_h
#define __SimpleITKMacro_h

// Ignore Visual Studio checked iterator warnings.
// See http://msdn.microsoft.com/en-us/library/aa985974.aspx
#ifdef _MSC_VER
  #define _SCL_SECURE_NO_WARNINGS
#endif

// Ideally, take the types from the C99 standard.
// However, because Visual Studio does not properly implement C99,
// handle this compiler specially.
#ifndef _MSC_VER
  #include <stdint.h>
#else
  #if (_MSC_VER <= 1500)
  // Types defined in stdint.h are not defined for < Visual Studio 10.0
  // See http://en.wikipedia.org/wiki/Stdint.h
  // They are however defined in itkIntTypes.h (in ::itk namespace)
  #include <itkIntTypes.h>
  typedef itk::int8_t   int8_t;
  typedef itk::uint8_t  uint8_t;
  typedef itk::int16_t  int16_t;
  typedef itk::uint16_t uint16_t;
  typedef itk::int32_t  int32_t;
  typedef itk::uint32_t uint32_t;
  #endif
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

#endif
