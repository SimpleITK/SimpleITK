#include "simpleImage.h"

#include <itkImage.h>
#include <itkCastImageFilter.h>

namespace itk {
  namespace simple {
    
    Image::Image ( SimpleImageBase::Pointer image, ImageDataType datatype ) {
      mImage = image;
      mDataType = datatype;
    }
    
    ////////////////////////////////
    // Type specific constructors //
    ////////////////////////////////
#define simpleImageConstructorCast(inImagePointer, InPxType, OutPxType) { \
    typedef itk::Image<InPxType,3> InType; \
    typedef itk::Image<OutPxType,3> OutType; \
    typedef itk::CastImageFilter<InType, OutType> FilterType; \
    FilterType::Pointer filter = FilterType::New(); \
    filter->SetInput(inImagePointer); \
    filter->Update(); \
    mImage = filter->GetOutput(); \
    }
    
    //
    // int (DEBUG)
    //
    Image::Image ( itk::Image<int,3>::Pointer image, ImageDataType datatype ) {
      
      mDataType = sitkFloat32;
      
      // convert to the desired data type
      switch (datatype) {
        sitkImageDataTypeSwitch(DataType, (simpleImageConstructorCast(image, int, DataType)) );
      }
    }
    
    
    //////////////////////
    // Standard Methods //
    //////////////////////
    
    //
    // getITKImage
    //
    SimpleImageBase::Pointer Image::getITKImage() { return mImage; }
    
    //
    // getImageDataType
    //
    ImageDataType Image::getImageDataType() { return mDataType; }
    
    //
    // toString
    //
    std::string Image::toString() {
      std::ostringstream out;
      this->mImage->Print ( out );
      return out.str();
    }
    
    //
    // getWidth
    //
    unsigned long Image::getWidth() {
      SimpleImageBase::RegionType region;
      region = this->mImage->GetLargestPossibleRegion();
      return region.GetSize()[0];
    }
    
    //
    // getHeight
    //
    unsigned long Image::getHeight() {
      SimpleImageBase::RegionType region;
      region = this->mImage->GetLargestPossibleRegion();
      return region.GetSize()[1];
    }
    
    //
    // getDepth
    //
    unsigned long Image::getDepth() {
      SimpleImageBase::RegionType region;
      region = this->mImage->GetLargestPossibleRegion();
      return region.GetSize()[2];
    }
    
    
    ///////////////////////////////////
    // Type Specific Pixel Accessors //
    ///////////////////////////////////
    
#define simpleImagePixelRetrieval(DataType, outType, x, y, z) {\
    typedef itk::Image<DataType,3> ITKImageType; \
    ITKImageType* itkImage = dynamic_cast<ITKImageType*>(mImage.GetPointer()); \
    ITKImageType::IndexType idx; \
    idx[0] = x; idx[1] = y; idx[2] = z; \
    ITKImageType::PixelType px = itkImage->GetPixel(idx); \
    *out = (outType)px; \
    }
    
    //
    // float
    //
    /*
    template <class TPixelType>
    TPixelType Image::getPixel(int x, int y, int z) {
      TPixelType out;
      switch (mDataType) {
        sitkImageDataTypeSwitch(DataType, (simpleImagePixelRetrieval(DataType, TPixelType, x, y, z)))
      }
      return out;
    }
    */
    void Image::getPixel(int x, int y, int z, float* out) {
      switch (mDataType) {
        sitkImageDataTypeSwitch(DataType, (simpleImagePixelRetrieval(DataType, float, x, y, z)))
      }
    }
    
  }
}












