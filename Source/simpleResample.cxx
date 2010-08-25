#include <simpleResample.h>
#include <itkResampleImageFilter.h>
#include <itkWindowedSincInterpolateImageFunction.h>
#include <itkLinearInterpolateImageFunction.h>
#include <itkNearestNeighborInterpolateImageFunction.h>
#include <itkZeroFluxNeumannBoundaryCondition.h>
#include <itkBSplineInterpolateImageFunction.h>

namespace itk {
  namespace simple {

    Resample::Resample() {
      this->m_InterpolationType = LinearInterpolation;
      this->m_OutputSpaceImage = NULL;
    }
      
    Resample& Resample::setTransform ( Transform t ) {
      this->m_Transform = t;
      return *this;
    }
    
    Transform Resample::getTransform() {
      return this->m_Transform;
    }

    Resample& Resample::setInterpolationType ( InterpolationType t ) {
      this->m_InterpolationType = t;
      return *this;
    }
    InterpolationType Resample::getInterpolationType() {
      return this->m_InterpolationType;
    }
    
    // Methods to set the output spacing, etc...
    Resample& Resample::setOutputCoordinateSystemFromImage ( Image::Pointer i ) {
      this->m_OutputSpaceImage = i;
      return *this;
    }

    Image::Pointer Resample::execute ( Image::Pointer image ) {
      switch ( image->getImageDataType() ) {
        sitkImageDataTypeSwitch ( return this->executeInternal<DataType>(image) );
      }
      return NULL;
    }
    
    template <class T> Image::Pointer Resample::executeInternal ( Image::Pointer image ) {
      TransformType *transform = m_Transform.getITKTransform();

      typedef itk::Image<T,3> ImageType;
      typedef itk::ResampleImageFilter<ImageType,ImageType> ResamplerType;
      typename ResamplerType::Pointer resampler = ResamplerType::New();
    
      const int VRadius = 4;
      typedef itk::ZeroFluxNeumannBoundaryCondition<ImageType> BCType;
      typedef itk::WindowedSincInterpolateImageFunction<ImageType,VRadius,itk::Function::HammingWindowFunction<VRadius>,BCType,double> SincType;
      typedef itk::LinearInterpolateImageFunction<ImageType,double> LinearType;
      typedef itk::NearestNeighborInterpolateImageFunction<ImageType,double> NearestType;
      typedef itk::BSplineInterpolateImageFunction<ImageType, double> BSplineType;

      switch ( this->m_InterpolationType ) {
      case SincInterpolation: {
        typename SincType::Pointer sinc = SincType::New();
        resampler->SetInterpolator ( sinc );
        break;
      }
      case BSplineInterpolation: {
        typename BSplineType::Pointer bspline = BSplineType::New();
        resampler->SetInterpolator ( bspline.GetPointer() );
        break;
      }
      case NearestNeighborInterpolation: {
        typename NearestType::Pointer nearest = NearestType::New();
        resampler->SetInterpolator ( nearest );
        break;
      }
      default:
      case LinearInterpolation: {
        typename LinearType::Pointer linear = LinearType::New();
        resampler->SetInterpolator ( linear.GetPointer() );
        break;
      }
      }

    resampler->SetTransform(transform);
    resampler->SetInput( dynamic_cast<ImageType*> (image->getITKImage().GetPointer() ) );
    resampler->SetOutputParametersFromImage( dynamic_cast<SimpleImageBase*> (this->m_OutputSpaceImage->getITKImage().GetPointer() ) );
    resampler->SetDefaultPixelValue(0);
    resampler->Update();
    Image::Pointer output = new Image ( resampler->GetOutput(), image->getImageDataType() );
    return output;
   }

  }
}
