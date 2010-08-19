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

// Tell the compiler that we are going to explicitly instantiate these templates.
extern template class itk::Image<uint8_t,3>;
extern template class itk::Image<uint16_t,3>;
extern template class itk::Image<uint32_t,3>;
extern template class itk::Image<float,3>;

#endif
