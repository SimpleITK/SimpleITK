#include "sitkGaussianFilter.h"
#include <itkRecursiveGaussianImageFilter.h>

namespace itk {
  namespace simple {

    GaussianFilter::GaussianFilter () {
      this->m_Sigma = 1.0;

      this->m_MemberFactory.reset( new detail::MemberFunctionFactory<Self>( this ) );

      this->m_MemberFactory->RegisterMemberFunctions< PixelTypeList, 3 > ();
      this->m_MemberFactory->RegisterMemberFunctions< PixelTypeList, 2 > ();
    }

    std::string GaussianFilter::ToString() {
      std::ostringstream out;
      out << "itk::simple::GaussianFilter\n"
          << "\tsigma: " << this->m_Sigma << "\n";
      return out.str();
    }

    GaussianFilter& GaussianFilter::SetSigma ( double sigma ) {
      this->m_Sigma = sigma;
      return *this;
    }

    double GaussianFilter::GetSigma() {
      return this->m_Sigma;
    }

    Image::Pointer GaussianFilter::Execute ( Image::Pointer image )  {

      ImageDataType type = image->GetDataType();
      unsigned int dimension = image->GetDimension();

      return this->m_MemberFactory->GetMemberFunction( type, dimension )( image );
    }

    template <class TImageType>
    Image::Pointer GaussianFilter::ExecuteInternal ( Image::Pointer inImage ) {
      typedef TImageType InputImageType;
      typedef itk::Image<float,InputImageType::ImageDimension> OutputImageType;
      typename InputImageType::Pointer image =
        dynamic_cast <InputImageType*> ( inImage->GetImageBase().GetPointer() );

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
      filter->GetOutput()->DisconnectPipeline();
      return out;
    }
  }
}
