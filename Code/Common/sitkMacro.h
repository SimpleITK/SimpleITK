#ifndef __sitkMacro_h
#define __sitkMacro_h


// Ideally, take the types from the C99 standard.  However,
// VS 8 does not have stdint.h, but they are defined anyway.
#ifndef _MSC_VER
	#include <stdint.h>
#endif

#include <itkImageBase.h>
#include <itkImage.h>
#include <itkLightObject.h>
#include <itkSmartPointer.h>

#include "sitkPixelTypeLists.h"

namespace itk {
namespace simple {

// this is the list of types which we will try to instantiate
typedef BasicPixelTypeList InstantiatedPixelTypeList;

// Define common base image type
typedef itk::ImageBase<3> SimpleImageBase;

typedef unsigned int ImageDataType;

}
}

#endif
