#ifndef sitkInternalUtilities_h
#define sitkInternalUtilities_h

#include "Ancillary/type_list2.h"

namespace itk::simple
{

/** SimpleElastix and SimpleTransformix is compiled with float pixel type only. This
 * saves compile time and reduces binary size. Images are automatically casted to and
 * from float before and after registration.
 */
using FloatPixelIDTypeList = typelist2::typelist<BasicPixelID<float>>;

} // namespace itk::simple

#endif
