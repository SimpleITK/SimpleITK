#include "sitkGaussian.h"
#include <itkRecursiveGaussianImageFilter.h>

namespace itk {
  namespace simple {

    Gaussian::Gaussian () {
      this->m_Sigma = 1.0;
    }

    std::string Gaussian::ToString() {
      std::ostringstream out;
      out << "itk::simple::Gaussian\n"
          << "\tsigma: " << this->m_Sigma << "\n";
      return out.str();
    }

    Gaussian& Gaussian::SetSigma ( double sigma ) {
      this->m_Sigma = sigma;
      return *this;
    }

    double Gaussian::GetSigma() {
      return this->m_Sigma;
    }

    Image::Pointer Gaussian::Execute ( Image::Pointer image )  {

      int fnIndex = image->GetImageDataType();

      // todo fix this ugly syntax
      return ((*this).*(m_MemberFactory.GetMemberFunction( fnIndex )))(image);
    }

    template <class T>
    Image::Pointer Gaussian::ExecuteInternal ( Image::Pointer inImage ) {
      typedef itk::Image<T,3> InputImageType;
      typedef itk::Image<float,3> OutputImageType;
      typename InputImageType::Pointer image =
        dynamic_cast <InputImageType*> ( inImage->GetITKImage().GetPointer() );

      if ( image.IsNull() ) {
        // Take some action
        return NULL;
      }

      typedef itk::RecursiveGaussianImageFilter<InputImageType, OutputImageType> GaussianFilterType;
      typename GaussianFilterType::Pointer filter = GaussianFilterType::New();

      filter->SetInput ( image );
      filter->SetSigma ( this->m_Sigma );
      filter->Update();

      Image::Pointer out = new Image( filter->GetOutput() );
      out->GetITKImage()->DisconnectPipeline();
      return out;
    }
  }
}
