#include "sitkImageFilter.h"

namespace itk {
namespace simple {

//----------------------------------------------------------------------------

//
// Default constructor that initializes parameters
//
template< unsigned int N >
ImageFilter< N >::ImageFilter ()
  {
  }

//
// Default destructor
//
template< unsigned int N >
ImageFilter< N >::~ImageFilter ()
  {
  }

template class ImageFilter<0>;
template class ImageFilter<1>;
template class ImageFilter<2>;
template class ImageFilter<3>;
template class ImageFilter<4>;
template class ImageFilter<5>;

} // end namespace simple
} // end namespace itk
