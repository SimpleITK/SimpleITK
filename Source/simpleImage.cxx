#include "simpleImage.h"

namespace itk {
  namespace simple {

  ImageBase::ImageBase( SimpleImageBase::Pointer image ) :mImage(image) {}
  
  SimpleImageBase::Pointer ImageBase::getITKImage() { return mImage; }


    std::string ImageBase::toString() {
      std::ostringstream out;
      this->mImage->Print ( out );
      return out.str();
    }

    unsigned long ImageBase::getWidth() {
      SimpleImageBase::RegionType region;
      region = this->mImage->GetLargestPossibleRegion();
      return region.GetSize()[0];
    }
    unsigned long ImageBase::getHeight() {
      SimpleImageBase::RegionType region;
      region = this->mImage->GetLargestPossibleRegion();
      return region.GetSize()[1];
    }
    unsigned long ImageBase::getDepth() {
      SimpleImageBase::RegionType region;
      region = this->mImage->GetLargestPossibleRegion();
      return region.GetSize()[2];
    }
  }
}
