#include "simpleGaussian.h"
#include <itkRecursiveGaussianImageFilter.h>

namespace itk {
  namespace simple {

    Gaussian::Gaussian () {
      this->mSigma = 1.0;
    }

    std::string Gaussian::toString() {
      std::ostringstream out;
      out << "itk::simple::Gaussian\n"
          << "\tsigma: " << this->mSigma << "\n";
      return out.str();
    }

    Gaussian& Gaussian::setSigma ( double sigma ) {
      this->mSigma = sigma;
      return *this;
    }

    double Gaussian::getSigma() {
      return this->mSigma;
    }

    Image::Pointer Gaussian::execute ( Image::Pointer image ) {
      // Would likely want to check to see if the image is null
      switch ( image->getImageDataType() ) {
        sitkImageDataTypeSwitch ( return this->executeInternal<DataType>(image) );
      }
      return NULL;
    }

    template <class T> 
    Image::Pointer Gaussian::executeInternal ( Image::Pointer inImage ) {
      typedef itk::Image<T,3> InputImageType;
      typedef itk::Image<float,3> OutputImageType;
      typename InputImageType::Pointer image = dynamic_cast <InputImageType*> ( inImage->getITKImage().GetPointer() );
      
      if ( image.IsNull() ) {
        // Take some action
        return NULL;
      }
      
      typedef itk::RecursiveGaussianImageFilter<InputImageType, OutputImageType> GaussianFilterType;
      typename GaussianFilterType::Pointer filter = GaussianFilterType::New();
      
      filter->SetInput ( image );
      filter->SetSigma ( this->mSigma );
      filter->Update();
      
      Image::Pointer out = new Image ( filter->GetOutput(), sitkFloat32 );
      out->getITKImage()->DisconnectPipeline();
      return out;
    }
  }
}
