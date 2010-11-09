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

// Define common base image type
typedef itk::ImageBase<3> SimpleImageBase;

typedef unsigned int ImageDataType;

}
}

// Tell the compiler that we are going to explicitly instantiate these templates.
//extern template class itk::Image<uint8_t,3>;
//extern template class itk::Image<uint16_t,3>;
//extern template class itk::Image<uint32_t,3>;
//extern template class itk::Image<float,3>;

#endif
