#ifndef __sitkMacro_h
#define __sitkMacro_h


// Ideally, take the types from the C99 standard.  However,
// VS 8 does not have stdint.h, but they are defined anyway.
#ifndef _MSC_VER
	#include <stdint.h>
#endif

#include <itkImageBase.h>

#include "sitkPixelIDTypeLists.h"

namespace itk {
namespace simple {

// this is the list of types which we will try to instantiate
typedef AllPixelIDTypeList InstantiatedPixelIDTypeList;

// Define common base image type
typedef itk::ImageBase<3> SimpleImageBase;

typedef int ImageDataType;

}
}


#define sitkSingleImageMemberFunctionDispatcher \
typedef Image::Pointer (Self::*MemberFunctionType)( Image::Pointer ); \
template <class TImageType> Image::Pointer ExecuteInternal ( Image::Pointer image ); \
friend struct detail::MemberFunctionAddressor<MemberFunctionType>; \
std::auto_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;

#endif
