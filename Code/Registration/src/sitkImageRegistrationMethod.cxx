#include "sitkImageRegistrationMethod.h"

#include "sitkCreateInterpolator.hxx"
#include "itkImage.h"
#include "itkImageRegistrationMethod.h"


#include "itkMeanSquaresImageToImageMetric.h"

template< typename TValue, typename TType>
itk::Array<TValue> sitkSTLVectorToITKArray( const std::vector< TType > & in )
{
  itk::Array<TValue> out(in.size());
  for( unsigned int i = 0; i < in.size(); ++i )
    {
    out[i] = in[i];
    }
  return out;
}

namespace itk
{
namespace simple
{

  ImageRegistrationMethod::ImageRegistrationMethod()
    : m_ActiveOptimizer(NULL)
  {
    m_MemberFactory.reset( new  detail::MemberFunctionFactory<MemberFunctionType>( this ) );

    m_MemberFactory->RegisterMemberFunctions< BasicPixelIDTypeList, 3 > ();
    m_MemberFactory->RegisterMemberFunctions< BasicPixelIDTypeList, 2 > ();

    m_Interpolator = sitkLinear;
    m_OptimizerMinimize = true;
  }


  ImageRegistrationMethod::~ImageRegistrationMethod()
  {
  }

  std::string  ImageRegistrationMethod::ToString() const
  {
    std::ostringstream out;
    out << "itk::simple" << this->GetName() << std::endl;

    out << "  Interpolator: ";
    this->ToStringHelper(out, this->m_Interpolator);
    out << std::endl;

    out << "  Transform: ";
    this->ToStringHelper(out, this->m_Transform.ToString());
    out << std::endl;

    out << "  FixedImageRegionSize: ";
    this->ToStringHelper(out, this->m_FixedImageRegionSize);
    out << std::endl;

     out << "  FixedImageRegionIndex: ";
    this->ToStringHelper(out, this->m_FixedImageRegionIndex);
    out << std::endl;

    return out.str();
  }


  ImageRegistrationMethod::Self&
  ImageRegistrationMethod::SetMetricAsMeanSquares( uint64_t numberOfSpatialSamples )
  {
    m_MetricType = MeanSquares;
    m_MetricNumberOfSpatialSamples = numberOfSpatialSamples;
    this->m_OptimizerMinimize = true;
    return *this;
  }


  template <class TImageType>
  itk::ImageToImageMetric<TImageType,TImageType>*
  ImageRegistrationMethod::CreateMetric( )
  {
    typedef TImageType     FixedImageType;
    typedef TImageType     MovingImageType;


    switch (m_MetricType)
      {
      case MeanSquares:
      {
        typedef itk::MeanSquaresImageToImageMetric< FixedImageType, MovingImageType >    _MetricType;
        typename _MetricType::Pointer         metric        = _MetricType::New();
        metric->UseAllPixelsOn();
        if ( this->m_MetricNumberOfSpatialSamples )
          {
          metric->SetNumberOfSpatialSamples( this->m_MetricNumberOfSpatialSamples );
          }

        metric->Register();
        return metric.GetPointer();
      }
      default:
        sitkExceptionMacro("LogicError: Unexpected case!");
      }

 }

  ImageRegistrationMethod::Self&
  ImageRegistrationMethod::SetOptimizerAsRegularStepGradientDescent( double maxStep,
                                                                     double minStep,
                                                                     unsigned int numberOfIteratons,
                                                                     double relaxationFactor )
  {
    m_OptimizerType = RegularStepGradientDescent;
    m_OptimizerMaximumStepLength = maxStep;
    m_OptimizerMinimumStepLength = minStep;
    m_OptimizerNumberOfIterations = numberOfIteratons;
    m_OptimizerRelaxationFactor = relaxationFactor;
    return *this;
  }


  ImageRegistrationMethod::Self&
  ImageRegistrationMethod::SetOptimizerScales( const std::vector<double> &scales)
  {
    this->m_OptimizerScales = scales;
    return *this;
  }

  ImageRegistrationMethod::Self&
  ImageRegistrationMethod::SetFixedImageRegion( const std::vector<unsigned int> &size,
                                                    const std::vector<unsigned int> &index)
  {
    this->m_FixedImageRegionSize = size;
    this->m_FixedImageRegionIndex = index;
    return *this;
  }


  const std::string &ImageRegistrationMethod::GetOptimizerStopConditionDescription() const
  {
    return this->m_StopConditionDescription;
  }

  unsigned int ImageRegistrationMethod::GetOptimizerIteration() const
  {
    if (bool(this->m_pfGetOptimizerIteration))
      {
      return this->m_pfGetOptimizerIteration();
      }
    return this->m_Iteration;
  }


  std::vector<double> ImageRegistrationMethod::GetOptimizerPosition() const
  {
    if(bool(this->m_pfGetOptimizerPosition))
      {
      return this->m_pfGetOptimizerPosition();
      }
    return std::vector<double>();
  }

  double ImageRegistrationMethod::GetMetricValue() const
  {
    if(bool(this->m_pfGetMetricValue))
      {
      return this->m_pfGetMetricValue();
      }
    return m_MetricValue;
  }


  Transform ImageRegistrationMethod::Execute ( const Image &fixed, const Image & moving )
  {
    const PixelIDValueType fixedType = fixed.GetPixelIDValue();
    const unsigned int fixedDim = fixed.GetDimension();
    if ( fixed.GetPixelIDValue() != moving.GetPixelIDValue() )
      {
      sitkExceptionMacro ( << "Fixed and moving images must be the same datatype! Got "
                           << fixed.GetPixelIDValue() << " and " << moving.GetPixelIDValue() );
      }

    if ( fixed.GetDimension() != moving.GetDimension() )
      {
      sitkExceptionMacro ( << "Fixed and moving images must be the same dimensionality! Got "
                           << fixed.GetDimension() << " and " << moving.GetDimension() );
      }

    if (this->m_MemberFactory->HasMemberFunction( fixedType, fixedDim ) )
      {
      return this->m_MemberFactory->GetMemberFunction( fixedType, fixedDim )( fixed, moving );
      }

    sitkExceptionMacro( << "Filter does not support fixed image type: " << itk::simple::GetPixelIDValueAsString (fixedType) );

  }

    template<class TImageType>
    Transform ImageRegistrationMethod::ExecuteInternal ( const Image &inFixed, const Image &inMoving )
    {
      typedef TImageType     FixedImageType;
      typedef TImageType     MovingImageType;


      typedef itk::ImageRegistrationMethod<FixedImageType, MovingImageType>  RegistrationType;
      typename RegistrationType::Pointer   registration  = RegistrationType::New();

      // Get the pointer to the ITK image contained in image1
      typename FixedImageType::ConstPointer fixed = this->CastImageToITK<FixedImageType>( inFixed );
      typename MovingImageType::ConstPointer moving = this->CastImageToITK<MovingImageType>( inMoving );

      registration->SetFixedImage( fixed );
      registration->SetMovingImage( moving );

      typedef itk::InterpolateImageFunction< MovingImageType, double > InterpolatorType;
      typename InterpolatorType::Pointer   interpolator  = CreateInterpolator(moving.GetPointer(), m_Interpolator);
      registration->SetInterpolator( interpolator );

      typename itk::ImageToImageMetric<FixedImageType, MovingImageType>::Pointer metric = this->CreateMetric<FixedImageType>();
      registration->SetMetric( metric );
      metric->UnRegister();

      typename itk::SingleValuedNonLinearOptimizer::Pointer optimizer = this->CreateOptimizer();
      optimizer->UnRegister();

      registration->SetOptimizer( optimizer );

      typename RegistrationType::TransformType *itkTx;
      if ( !(itkTx = dynamic_cast<typename RegistrationType::TransformType *>(this->m_Transform.GetITKBase())) )
        {
        sitkExceptionMacro( "Unexpected error converting transform! Possible miss matching dimensions!" );
        }

      registration->SetTransform( itkTx );

      registration->SetInitialTransformParameters(itkTx->GetParameters());

      if (m_FixedImageRegionSize.size() && m_FixedImageRegionIndex.size())
        {
        typedef typename FixedImageType::RegionType RegionType;
        RegionType r( sitkSTLVectorToITK<typename RegionType::IndexType>(m_FixedImageRegionIndex),
                      sitkSTLVectorToITK<typename RegionType::SizeType>(m_FixedImageRegionSize) );
        registration->SetFixedImageRegion( r );
        }

      this->m_ActiveOptimizer = optimizer;
      this->PreUpdate( registration.GetPointer() );

      if (this->GetDebug())
        {
        std::cout << optimizer;
        std::cout << metric;
        }

      registration->Update();

      // update measurements
      this->m_StopConditionDescription = registration->GetOptimizer()->GetStopConditionDescription();

      m_MetricValue = this->GetMetricValue();
      m_Iteration = this->GetOptimizerIteration();
      m_pfGetOptimizerIteration = NULL;
      m_pfGetOptimizerPosition = NULL;
      m_pfGetMetricValue = NULL;


      return this->m_Transform;
    }


void ImageRegistrationMethod::PreUpdate( itk::ProcessObject *p )
{
  Superclass::PreUpdate(p);
}


void ImageRegistrationMethod::PreUpdateAddObserver( itk::ProcessObject *p, const itk::EventObject &e, itk::Command *c)
{
  assert(this->m_ActiveOptimizer);
  // todo switch to generator function
  itk::IterationEvent iterationEvent;
  if (e.CheckEvent(&iterationEvent))
    {
    this->m_ActiveOptimizer->AddObserver(e,c);
    return;
    }
  Superclass::PreUpdateAddObserver(p,e,c);
}

void ImageRegistrationMethod::OnActiveProcessDelete( ) throw()
{
  Superclass::OnActiveProcessDelete( );
  this->m_ActiveOptimizer = NULL;
}


}
}
