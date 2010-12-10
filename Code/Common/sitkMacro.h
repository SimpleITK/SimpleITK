#ifndef __sitkMacro_h
#define __sitkMacro_h


// Ideally, take the types from the C99 standard.  However,
// VS 8 does not have stdint.h, but they are defined anyway.
#ifndef _MSC_VER
	#include <stdint.h>
#endif

#include <itkImageBase.h>

#include "sitkPixelIDTypeLists.h"
#include "sitkPixelIDValues.h"

namespace itk {
namespace simple {

// Define common base image type
typedef itk::ImageBase<3> SimpleImageBase;


}
}


#endif
