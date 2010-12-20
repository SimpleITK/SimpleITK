#ifndef __sitkSize_h
#define __sitkSize_h

// sitk includes
#include "sitkMacro.h"
#include "sitkIndex.h"

// itk includes
#include "itkSize.h"

namespace itk
{
namespace simple
{

class Size : public Index
{
public:
  // Cast operator for itk::Size<2>
  operator itk::Size<2>();

  // Cast operator for itk::Size<3>
  operator itk::Size<3>();

};

} // end namespace simple
} // end namespace itk


#endif
