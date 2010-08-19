#ifndef __simpleAddImage_h
#define __simpleAddImage_h

#include <SimpleITKMacro.h>
#include <simpleImage.h>

namespace itk {
namespace simple {
  
/** \class AddImage
 * \brief Filter to add two images together
 * 
 * Parameters:
 * <none>
 *
 * Inputs:
 *  - image1 -> First image to add
 *  - imate2 -> Second image to add
 */
class AddImage 
{
public:
  typedef AddImage Self;

  AddImage();
  
  // Print ourselves out
  std::string toString();
  
  Image::Pointer execute ( Image::Pointer, Image::Pointer );
private:
  template <class TInPixel1, class TInPixel2>  Image::Pointer executeInternal ( Image::Pointer inImage1, Image::Pointer inImage2 );
};


}
}
#endif
