#include "simpleImage.h"

namespace itk {
  namespace simple {
    
    Image::Image ( SimpleImageBase::Pointer image, ImageDataType datatype ) {
      mImage = image;
      mDataType = datatype;
    }

    SimpleImageBase::Pointer Image::getITKImage() { return mImage; }

    ImageDataType Image::getImageDataType() { return mDataType; }

    std::string Image::toString() {
      std::ostringstream out;
      this->mImage->Print ( out );
      return out.str();
    }

  }
}
