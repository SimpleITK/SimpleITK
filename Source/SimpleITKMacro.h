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
#include <simplePixelTypeLists.h>


namespace itk {
  namespace simple {

// this is the list of types which we will try to instantiate
  typedef BasicPixelTypeList InstantiatedPixelTypeList;

    // Define macros to aid in the typeless layer
    typedef itk::ImageBase<3> SimpleImageBase;


  // predicate used with typelist::ForEach to initialize arrays for
  // run-time dispatching
  template < typename TObject>
  struct PFuncArrayInitializer
  {
    PFuncArrayInitializer( typename TObject::MemberFunctionType *a ) : createFunctions( a ) {}

    template <class TPixelType>
    void operator()( TPixelType t )
    {
      typedef TPixelType                 PixelType;
      typedef itk::Image< PixelType, 3 > ImageType;

      // this maps the pixel type to an array index
      int index = typelist::IndexOf< InstantiatedPixelTypeList, PixelType >::Result;

      if ( index > 0 &&  index < typelist::Length< InstantiatedPixelTypeList >::Result )
        {
        createFunctions[index] =   &TObject::template executeInternal<PixelType>;
        }
    }
  private:
    typename TObject::MemberFunctionType *createFunctions;
  };

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
//extern template class itk::Image<uint8_t,3>;
//extern template class itk::Image<uint16_t,3>;
//extern template class itk::Image<uint32_t,3>;
//extern template class itk::Image<float,3>;

#endif
