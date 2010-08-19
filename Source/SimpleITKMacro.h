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
    //typedef itk::Image<float,3> SimpleImageBase;

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

#define sitkImageDataTypeCase(typeN, type, name, call ) \
    case typeN: { typedef type name; call; }; break

#define sitkImageDataTypeSwitch( name, call ) \
    sitkImageDataTypeCase ( sitkUInt8, uint8_t, name, call ); \
    sitkImageDataTypeCase ( sitkInt16, int16_t, name, call ); \
    sitkImageDataTypeCase ( sitkInt32, int32_t, name, call ); \
    sitkImageDataTypeCase ( sitkFloat32, float, name, call );

/**
 * Takes another macro as the argument which itself takes a type as its
 * single argument and repeates the call for all defined types
 */
#define sitkRepeatForEachType( innerMacro ) \
    innerMacro( uint8_t ); \
    innerMacro( int16_t ); \
    innerMacro( int32_t ); \
    innerMacro( float );


  }
}    

// Tell the compiler that we are going to explicitly instantiate these templates.
extern template class itk::Image<uint8_t,3>;
extern template class itk::Image<uint16_t,3>;
extern template class itk::Image<uint32_t,3>;
extern template class itk::Image<float,3>;

#endif
