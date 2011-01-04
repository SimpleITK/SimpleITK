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

  // Typedefs
  typedef Size               Self;
  typedef size_t             SizeValueType;

  //
  // Constructors
  //
  Size();
  Size( SizeValueType x, SizeValueType y );
  Size( SizeValueType x, SizeValueType y, SizeValueType z );
  explicit Size( const itk::Size<2> &idx );
  explicit Size( const itk::Size<3> &idx );

  // Cast operator for itk::Size<2>
  operator itk::Size<2>();

  // Cast operator for itk::Size<3>
  operator itk::Size<3>();

};

} // end namespace simple
} // end namespace itk


#endif
