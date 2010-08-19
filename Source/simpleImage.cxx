#include "simpleImage.h"

#include "itkCastImageFilter.h"

namespace itk {
  namespace simple {
    
    //Image::Image ( SimpleImageBase::Pointer image, ImageDataType datatype ) {
    //  mImage = image;
    //  mDataType = datatype;
    //}

#define simpleImageConstructorCast(inImagePointer, InPxType, OutPxType) { \
    typedef itk::Image<InPxType,3> InType; \
    typedef itk::Image<OutPxType,3> OutType; \
    typedef itk::CastImageFilter<InType, OutType> FilterType; \
    typename FilterType::Pointer filter = FilterType::New(); \
    filter->SetInput(inImagePointer); \
    filter->Update(); \
    mImage = filter->GetOutput(); \
    }
    
    template<class TDataType>
    Image::Image ( typename itk::Image<TDataType,3>::Pointer image, ImageDataType datatype ) {
      
      mDataType = datatype;
      
      // convert to the desired data type
      switch (datatype) {
        sitkImageDataTypeSwitch(DataType, (simpleImageConstructorCast(image, TDataType, DataType)) );
      }
    }

    SimpleImageBase::Pointer Image::getITKImage() { return mImage; }

    ImageDataType Image::getImageDataType() { return mDataType; }

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
