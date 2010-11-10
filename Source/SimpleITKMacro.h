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
    sitkImageDataTypeCase ( itk::simple::sitkUInt8, uint8_t, name, call ); \
    sitkImageDataTypeCase ( itk::simple::sitkInt16, int16_t, name, call ); \
    sitkImageDataTypeCase ( itk::simple::sitkInt32, int32_t, name, call ); \
    sitkImageDataTypeCase ( itk::simple::sitkFloat32, float, name, call );

    /**
     * Takes another macro as the argument which itself takes a type as its
     * single argument and repeates the call for all defined types
     */
#define sitkRepeatForEachType( innerMacro ) \
    innerMacro( uint8_t ); \
    innerMacro( int16_t ); \
    innerMacro( int32_t ); \
    innerMacro( float );
    
    /**
     * Loop through all the pixels in an image and perform code on
     * each one.  No change occurs in the image (Read-Only).
     */
#define sitkForEachPixelRGivenType( image, datatype, pixelVarName, call ) {\
    typedef itk::Image<datatype,3> ITKImageType; \
    typedef itk::ImageRegionIterator<ITKImageType> IteratorType; \
    ITKImageType* itkImage = dynamic_cast<ITKImageType*>(image->getITKImage().GetPointer()); \
    IteratorType it(itkImage, itkImage->GetLargestPossibleRegion()); \
    for (it = it.Begin(); !it.IsAtEnd(); ++it) { \
      datatype pixelVarName = it.Get(); \
      call \
    }\
    }

#define sitkForEachPixelR( image, pixelVarName, call ) {\
    switch(image->getImageDataType()) { \
      sitkImageDataTypeSwitch(DataType, (sitkForEachPixelRGivenType(image,DataType,pixelVarName,call))) \
    } \
    }
    
    
    /**
     * Loop through all the pixels in an image and perform code on
     * each one.  Changes to the pixels do effect the image (Read-Write).
     */
#define sitkForEachPixelRWGivenType( image, datatype, pixelVarName, call ) {\
    typedef itk::Image<datatype,3> ITKImageType; \
    typedef itk::ImageRegionIterator<ITKImageType> IteratorType; \
    ITKImageType* itkImage = dynamic_cast<ITKImageType*>(image->getITKImage().GetPointer()); \
    IteratorType it(itkImage, itkImage->GetLargestPossibleRegion()); \
    for (it = it.Begin(); !it.IsAtEnd(); ++it) { \
      datatype pixelVarName = it.Get(); \
      call \
      it.Set(pixelVarName); \
    }\
    }

#define sitkForEachPixelRW( image, pixelVarName, call ) {\
    switch(image->getImageDataType()) { \
      sitkImageDataTypeSwitch(DataType, (sitkForEachPixelRWGivenType(image,DataType,pixelVarName,call))) \
    } \
    }
    
    /**
     * Loop through all the pixels in an image and perform code on
     * each one.  Changes to the pixels do effect the image (Write-Only).
     */
#define sitkForEachPixelWGivenType( image, datatype, pixelVarName, call ) {\
    typedef itk::Image<datatype,3> ITKImageType; \
    typedef itk::ImageRegionIterator<ITKImageType> IteratorType; \
    ITKImageType* itkImage = dynamic_cast<ITKImageType*>(image->getITKImage().GetPointer()); \
    IteratorType it(itkImage, itkImage->GetLargestPossibleRegion()); \
    for (it = it.Begin(); !it.IsAtEnd(); ++it) { \
      datatype pixelVarName; \
      call \
      it.Set(pixelVarName); \
    }\
    }

#define sitkForEachPixelW( image, pixelVarName, call ) {\
    switch(image->getImageDataType()) { \
      sitkImageDataTypeSwitch(DataType, (sitkForEachPixelWGivenType(image,DataType,pixelVarName,call))) \
    } \
    }

  }
}

#endif
