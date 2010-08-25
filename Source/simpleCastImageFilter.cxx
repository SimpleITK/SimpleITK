#include "simpleCastImageFilter.h"
#include <itkCastImageFilter.h>

namespace itk {
  namespace simple {

    CastImageFilter::CastImageFilter () {
      this->mImageDataType = sitkInt16;
    }

    std::string CastImageFilter::toString() {
      return "";
    }

    CastImageFilter& CastImageFilter::setOutputDataType ( ImageDataType dt ) {
      this->mImageDataType = dt;
      return *this;
    }

    ImageDataType CastImageFilter::getOutputDataType() {
      return this->mImageDataType;
    }

    Image::Pointer CastImageFilter::execute ( Image::Pointer image ) {
      // Would likely want to check to see if the image is null
      switch ( image->getImageDataType() ) {
        sitkImageDataTypeSwitch ( return this->executeInternalOne<DataType>(image) );
      }
      return NULL;
    }

    template <class TInput> 
    Image::Pointer CastImageFilter::executeInternalOne ( Image::Pointer image ) {
      switch ( this->mImageDataType ) {
        sitkImageDataTypeSwitch ( return (this->executeInternalTwo<TInput,DataType>(image)); );
      }
      return NULL;
    }

    template <class TInput,class TOutput> 
    Image::Pointer CastImageFilter::executeInternalTwo ( Image::Pointer inImage ) {
      typedef itk::Image<TInput,3> InputImageType;
      typedef itk::Image<TOutput,3> OutputImageType;
      typename InputImageType::Pointer image = dynamic_cast <InputImageType*> ( inImage->getITKImage().GetPointer() );
      
      if ( image.IsNull() ) {
        // Take some action
        return NULL;
      }
      
      typedef itk::CastImageFilter<InputImageType, OutputImageType> CastImageFilterFilterType;
      typename CastImageFilterFilterType::Pointer filter = CastImageFilterFilterType::New();
      
      filter->SetInput ( image );
      filter->Update();
      
      Image::Pointer out = new Image ( filter->GetOutput(), this->mImageDataType );
      out->getITKImage()->DisconnectPipeline();
      return out;
    }
  }
}
