#ifndef __sitkImageRegistrationMethod_h
#define __sitkImageRegistrationMethod_h

#include "sitkRegistration.h"

#include "sitkDetail.h"
#include "sitkImage.h"
#include "sitkPixelIDTokens.h"
#include "sitkMemberFunctionFactory.h"
#include "sitkProcessObject.h"

#include "sitkInterpolator.h"
#include "sitkTransform.h"

#ifndef SWIGPYTHON
#define LAMBDA lambda
#else
#define LAMBDA _lambda
#endif



namespace itk
{

#ifndef SWIG
template< typename TInternalComputationValueType> class ObjectToObjectOptimizerBaseTemplate;
template<typename TFixedImage,
         typename TMovingImage,
         typename TVirtualImage,
         typename TInternalComputationValueType,
         typename TMetricTraits >
class ImageToImageMetricv4;

template<typename TFixedImageType,
         typename TMovingImageType,
         typename TVirtualImageType,
         typename TCoordRep>
class DefaultImageToImageMetricTraitsv4;


class Command;
class EventObject;
#endif



namespace simple
{

  class SITKRegistration_EXPORT ImageRegistrationMethod
    : public ProcessObject
  {
  public:

    typedef ImageRegistrationMethod Self;
    typedef ProcessObject Superclass;

    ImageRegistrationMethod();
    virtual ~ImageRegistrationMethod();

    std::string GetName() const { return std::string("ImageRegistrationMethod"); }
    std::string ToString() const;


    InterpolatorEnum GetInterpolator()
      { return this->m_Interpolator; }
    Self& SetInterpolator ( InterpolatorEnum Interpolator )
      { this->m_Interpolator = Interpolator; return *this; }

    Self& SetTransform ( const Transform &Transform )
      { this->m_Transform = Transform; return *this; }
    Transform GetTransform()
      { return this->m_Transform; }

    Self& SetMetricAsCorrelation( );
    Self& SetMetricAsDemons( );
    Self& SetMetricAsJointHistogramMutualInformation( );
    Self& SetMetricAsMeanSquares( );
    Self& SetMetricAsMattesMutualInformation( );


    Self& SetOptimizerAsRegularStepGradientDescent( double learningRate,
                                                    double minStep,
                                                    unsigned int numberOfIterations,
                                                    double relaxationFactor=0.5);
    Self& SetOptimizerAsGradientDescent( double learningRate,
                                         unsigned int numberOfIterations );
    Self& SetOptimizerScales( const std::vector<double> &scales);


    Self& SetFixedImageRegion( const std::vector<unsigned int> &size, const std::vector<unsigned int> &index);

    Transform Execute ( const Image &fixed, const Image & moving );

     /**
      * Active measurements which can be obtained during call backs.
      *
      * This is a measurement. Its value is updated in the Execute
      * methods, so the value will only be valid after an execution.
      */
    unsigned int GetOptimizerIteration() const;
    std::vector<double> GetOptimizerPosition() const;
    double GetMetricValue() const;

    /** Measurement updated at the end of execution.
      */
    const std::string &GetOptimizerStopConditionDescription() const;

  protected:

    template<class TImage>
    Transform ExecuteInternal ( const Image &fixed, const Image &moving );

    itk::ObjectToObjectOptimizerBaseTemplate<double> *CreateOptimizer( );

    template <class TImageType>
      itk::ImageToImageMetricv4<TImageType,
      TImageType,
      TImageType,
      double,
      DefaultImageToImageMetricTraitsv4< TImageType, TImageType, TImageType, double >
      >* CreateMetric( );

    virtual void PreUpdate( itk::ProcessObject *p );
    virtual void OnActiveProcessDelete( ) throw();
    virtual unsigned long AddITKObserver(const itk::EventObject &, itk::Command *);
    virtual void RemoveITKObserver( EventCommand &e );

  private:

    nsstd::function<unsigned int()> m_pfGetOptimizerIteration;
    nsstd::function<std::vector<double>()> m_pfGetOptimizerPosition;
    nsstd::function<double()> m_pfGetMetricValue;

    typedef Transform (ImageRegistrationMethod::*MemberFunctionType)( const Image &fixed, const Image &moving );
    friend struct detail::MemberFunctionAddressor<MemberFunctionType>;
    std::auto_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;

    InterpolatorEnum  m_Interpolator;
    Transform  m_Transform;

    // optimizer
    enum OptimizerType { RegularStepGradientDescent,
                         GradientDescent
    };
    OptimizerType m_OptimizerType;
    double m_OptimizerLearningRate;
    double m_OptimizerMinimumStepLength;
    unsigned int m_OptimizerNumberOfIterations;
    double m_OptimizerRelaxationFactor;
    std::vector<double> m_OptimizerScales;

    // metric
    enum MetricType { Correlation,
                      Demons,
                      JointHistogramMutualInformation,
                      MeanSquares,
                      MattesMutualInformation
    };
    MetricType m_MetricType;

    std::vector<unsigned int> m_FixedImageRegionSize;
    std::vector<unsigned int> m_FixedImageRegionIndex;


    std::string m_StopConditionDescription;
    double m_MetricValue;
    unsigned int m_Iteration;

    itk::ObjectToObjectOptimizerBaseTemplate<double> *m_ActiveOptimizer;
  };

}
}

#endif // __sitkImageRegistrationMethod_h
