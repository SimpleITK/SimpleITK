#include "simpleImage.h"

namespace itk {
  namespace simple {

  Image::Image( SimpleImageBase::Pointer image ) :mImage(image) {}
  
  SimpleImageBase::Pointer Image::getITKImage() { return mImage; }


    std::string Image::toString() {
      std::ostringstream out;
      this->mImage->Print ( out );
      return out.str();
    }

    unsigned long Image::getWidth() {
      SimpleImageBase::RegionType region;
      region = this->mImage->GetLargestPossibleRegion();
      return region.GetSize()[0];
    }
    unsigned long Image::getHeight() {
      SimpleImageBase::RegionType region;
      region = this->mImage->GetLargestPossibleRegion();
      return region.GetSize()[1];
    }
    unsigned long Image::getDepth() {
      SimpleImageBase::RegionType region;
      region = this->mImage->GetLargestPossibleRegion();
      return region.GetSize()[2];
    }
  }
}
