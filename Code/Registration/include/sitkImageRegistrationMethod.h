/*=========================================================================
*
*  Copyright Insight Software Consortium
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*         http://www.apache.org/licenses/LICENSE-2.0.txt
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*=========================================================================*/
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

template<typename TMetric> class RegistrationParameterScalesEstimator;

template<unsigned int VDimension> class SpatialObject;

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

    /** \brief Set the initial transform and parameters to optimize.
     *
     * This transform is a applied before the MovingInitialTransform,
     * to map from the virtual image domain to the moving image
     * domain.
     *
     * If the inPlace flag is explicitly false, then the transform
     * will be the ITK registration will internally make a copy, and
     * the transform will not be accessible during
     * registration. Otherwise, the accessible InitialTransform value
     * will be the same object used during registration, and will have
     * a modified value upon completion.
     *
     * \sa itk::ImageRegistrationv4::SetInitialTransform
     * @{
     */
#if !defined(SWIG) || defined(JAVASWIG) || defined(CSHARPSWIG)
    // Only wrap this method if the wrapping language is strongly typed
    Self& SetInitialTransform ( const Transform &transform );
#endif
    Self& SetInitialTransform ( Transform &transform, bool inPlace=true );
    Transform GetInitialTransform()
      { return this->m_InitialTransform; }
    bool GetInitialTransformInPlace() const
    { return this->m_InitialTransformInPlace;}
    /** @} */

    /** \brief Set a fixed transform component towards moving domain.
     *
     * The InitialTransform is added to this transform to form the
     * composite transform which maps from the virtual domain to the
     * moving image's domain. The parameters of this transform are not
     * optimized.
     *
     * By default this transform is an identity, and not used.
     *
     * \sa itk::ImageRegistrationMethodv4::SetMovingInitialTransform
     * @{
     */
    Self& SetMovingInitialTransform( const Transform &transform )
    { this->m_MovingInitialTransform = transform; return *this; }
    Transform GetMovingInitialTransform( ) const
    { return this->m_MovingInitialTransform; }
    /**@}*/

    /** \brief Set transform mapping to the fixed domain.
     *
     * This transform is used to map from the virtual domain to the
     * fixed image domain.
     *
     * By default this transform is an identity, and not used.
     *
     * \sa itk::ImageRegistrationMethodv4::SetFixedInitialTransform
     * @{
     */
    Self& SetFixedInitialTransform( const Transform &transform )
    { this->m_FixedInitialTransform = transform; return *this; }
    Transform GetFixedInitialTransform( ) const
    { return this->m_FixedInitialTransform; }
    /**@}*/

    Self& SetMetricAsANTSNeighborhoodCorrelation( unsigned int radius );
    Self& SetMetricAsCorrelation( );
    Self& SetMetricAsDemons( double intensityDifferenceThreshold = 0.001 );
    Self& SetMetricAsJointHistogramMutualInformation( unsigned int numberOfHistogramBins = 20,
                                                      double varianceForJointPDFSmoothing = 1.5);
    Self& SetMetricAsMeanSquares( );
    Self& SetMetricAsMattesMutualInformation( unsigned int numberOfHistogramBins = 50 );


    enum EstimateLearningRateType { Never, Once, EachIteration };
    Self& SetOptimizerAsConjugateGradientLineSearch( double learningRate,
                                                     unsigned int numberOfIterations,
                                                     double convergenceMinimumValue = 1e-6,
                                                     unsigned int convergenceWindowSize = 10,
                                                     double lineSearchLowerLimit = 0,
                                                     double lineSearchUpperLimit = 5.0,
                                                     double lineSearchEpsilon = 0.01,
                                                     unsigned int lineSearchMaximumIterations = 20,
                                                     EstimateLearningRateType estimateLearningRate = Once,
                                                     double maximumStepSizeInPhysicalUnits = 0.0 );
    Self& SetOptimizerAsRegularStepGradientDescent( double learningRate,
                                                    double minStep,
                                                    unsigned int numberOfIterations,
                                                    double relaxationFactor=0.5,
                                                    double gradientMagnitudeTolerance = 1e-4,
                                                    EstimateLearningRateType estimateLearningRate = Never,
                                                    double maximumStepSizeInPhysicalUnits = 0.0);
    Self& SetOptimizerAsGradientDescent( double learningRate,
                                         unsigned int numberOfIterations,
                                         double convergenceMinimumValue = 1e-6,
                                         unsigned int convergenceWindowSize = 10,
                                         EstimateLearningRateType estimateLearningRate = Once,
                                         double maximumStepSizeInPhysicalUnits = 0.0);
    Self& SetOptimizerAsGradientDescentLineSearch( double learningRate,
                                                   unsigned int numberOfIterations,
                                                   double convergenceMinimumValue = 1e-6,
                                                   unsigned int convergenceWindowSize = 10,
                                                   double lineSearchLowerLimit = 0,
                                                   double lineSearchUpperLimit = 5.0,
                                                   double lineSearchEpsilon = 0.01,
                                                   unsigned int lineSearchMaximumIterations = 20,
                                                   EstimateLearningRateType estimateLearningRate = Once,
                                                   double maximumStepSizeInPhysicalUnits = 0.0 );


    Self& SetOptimizerAsLBFGSB(double gradientConvergenceTolerance = 1e-5,
                               unsigned int maximumNumberOfIterations = 500,
                               unsigned int maximumNumberOfCorrections = 5,
                               unsigned int maximumNumberOfFunctionEvaluations = 2000,
                               double costFunctionConvergenceFactor = 1e+7,
                               double lowerBound = std::numeric_limits<double>::min(),
                               double upperBound = std::numeric_limits<double>::max(),
                               bool trace = false );

    /** \brief Set the optimizer to sample the metric at regular steps.
     *
     * At each iteration the GetOptimizerIteration, can be used to
     * index into the sampling grid along with the
     * GetCurrentMetricValue.
     *
     * The resulting transform and value at the end of execution is
     * the best location.
     *
     * The OptimizerScales can be used to perform anisotropic sampling.
     *
     * \note This optimizer is not suited to using at multiple scales.
     */
    Self& SetOptimizerAsExhaustive( const std::vector<unsigned int> &numberOfSteps,
                                    double stepLength = 1.0 );

    Self& SetOptimizerAsAmoeba(double simplexDelta,
                               unsigned int numberOfIterations,
                               double parametersConvergenceTolerance=1e-8,
                               double functionConvergenceTolerance=1e-4,
                               bool withRestarts = false );

    /** \brief A per parameter weighting array for the optimizer.
     *
     * Allows setting of a per-local-parameter weighting array. If
     * unset, the weights are treated as identity. Weights are
     * multiplied by the gradient at the same time scaling is
     * applied. Weights are similar to the scales but not estimated,
     * and may be used, for example, to easily mask out a particular
     * parameter during optimization to hold it constant. Or they may
     * be used to apply another kind of prior knowledge.
     * @{
     */
    Self& SetOptimizerWeights(const std::vector<double> &weights);
    std::vector<double> GetOptimizerWeights( ) const;
    /**@}*/

    Self& SetOptimizerScales( const std::vector<double> &scales );
    Self& SetOptimizerScalesFromJacobian( unsigned int centralRegionRadius = 5 );
    Self& SetOptimizerScalesFromIndexShift( unsigned int centralRegionRadius = 5,
                                           double smallParameterVariation =  0.01 );

    Self& SetOptimizerScalesFromPhysicalShift( unsigned int centralRegionRadius = 5,
                                              double smallParameterVariation =  0.01 );


    Self& SetMetricFixedMask( const Image &binaryMask );

    Self& SetMetricMovingMask( const Image &binaryMask );

    Self &SetMetricSamplingPercentage(double percentage);
    Self &SetMetricSamplingPercentagePerLevel(const std::vector<double> &percentage);

    enum MetricSamplingStrategyType {
      NONE,
      REGULAR,
      RANDOM
    };

    Self &SetMetricSamplingStrategy( MetricSamplingStrategyType strategy);

    Self& SetMetricUseFixedImageGradientFilter(bool);
    Self& MetricUseFixedImageGradientFilterOn() {return this->SetMetricUseFixedImageGradientFilter(true);}
    Self& MetricUseFixedImageGradientFilterOff() {return this->SetMetricUseFixedImageGradientFilter(false);}

    Self& SetMetricUseMovingImageGradientFilter(bool);
    Self& MetricUseMovingImageGradientFilterOn() {return this->SetMetricUseMovingImageGradientFilter(true);}
    Self& MetricUseMovingImageGradientFilterOff() {return this->SetMetricUseMovingImageGradientFilter(false);}


    Self &SetShrinkFactorsPerLevel( const std::vector<unsigned int> &shrinkFactors );
    Self &SetSmoothingSigmasPerLevel( const std::vector<double> &smoothingSigmas );


    Self &SetSmoothingSigmasAreSpecifiedInPhysicalUnits(bool arg);
    Self &SmoothingSigmasAreSpecifiedInPhysicalUnitsOn() { this->SetSmoothingSigmasAreSpecifiedInPhysicalUnits(true); return *this;}
    Self &SmoothingSigmasAreSpecifiedInPhysicalUnitsOff()  { this->SetSmoothingSigmasAreSpecifiedInPhysicalUnits(false); return *this;}


    Transform Execute ( const Image &fixed, const Image & moving );


    /** \brief Get the value of the metric given the state of the method
     *
     * Passing a fixed and moving image, this method constructs and
     * configures a metric object to obtain the value. This will take
     * into consideration the current transforms, metric,
     * interpolator, and image masks. It does not take into
     * consideration the sampling strategy, smoothing sigmas, or the
     * shrink factors.
     */
    double MetricEvaluate( const Image &fixed, const Image & moving );


    /**
      * Active measurements which can be obtained during call backs.
      *
      * This is a measurement. Its value is updated in the Execute
      * methods, so the value will only be valid after an execution.
      */
    unsigned int GetOptimizerIteration() const;
    std::vector<double> GetOptimizerPosition() const;
    double GetOptimizerLearningRate() const;
    double GetOptimizerConvergenceValue() const;
    double GetMetricValue() const;


    unsigned int GetCurrentLevel() const;

    /** \brief Get the OptimizerScales
      *
      * If the scales are explicitly set then this method returns
      * those values. If an estimator is used then this is an active
      * measurement returning the scales estimated by the estimator
      * and is only available during execution.
      */
    std::vector<double> GetOptimizerScales() const;

    /** Measurement updated at the end of execution.
      */
    std::string GetOptimizerStopConditionDescription() const;

  protected:

    template<class TImage>
    Transform ExecuteInternal ( const Image &fixed, const Image &moving );

    template<class TImage>
    double EvaluateInternal ( const Image &fixed, const Image &moving );


    itk::ObjectToObjectOptimizerBaseTemplate<double> *CreateOptimizer( unsigned int numberOfTransformParameters );

    template<unsigned int VDimension>
      itk::SpatialObject<VDimension> *CreateSpatialObjectMask(const Image &mask);

    template <class TImageType>
      itk::ImageToImageMetricv4<TImageType,
      TImageType,
      TImageType,
      double,
      itk::DefaultImageToImageMetricTraitsv4< TImageType, TImageType, TImageType, double >
      >* CreateMetric( );

    template <class TImageType>
      void SetupMetric(
      itk::ImageToImageMetricv4<TImageType,
      TImageType,
      TImageType,
      double,
      itk::DefaultImageToImageMetricTraitsv4< TImageType, TImageType, TImageType, double >
      >*, const TImageType*, const TImageType* );

    template <typename TMetric>
      itk::RegistrationParameterScalesEstimator< TMetric >*CreateScalesEstimator();

    template <typename TTransformAdaptorPointer, typename TRegistrationMethod >
    std::vector< TTransformAdaptorPointer >
      CreateTransformParametersAdaptor(
        TRegistrationMethod* method);

    virtual void PreUpdate( itk::ProcessObject *p );
    virtual void OnActiveProcessDelete( ) throw();
    virtual unsigned long AddITKObserver(const itk::EventObject &, itk::Command *);
    virtual void RemoveITKObserver( EventCommand &e );

  private:

    nsstd::function<unsigned int()> m_pfGetOptimizerIteration;
    nsstd::function<std::vector<double>()> m_pfGetOptimizerPosition;
    nsstd::function<double()> m_pfGetOptimizerLearningRate;
    nsstd::function<double()> m_pfGetOptimizerConvergenceValue;
    nsstd::function<double()> m_pfGetMetricValue;
    nsstd::function<std::vector<double>()> m_pfGetOptimizerScales;
    nsstd::function<std::string()> m_pfGetOptimizerStopConditionDescription;


    nsstd::function<unsigned int()> m_pfGetCurrentLevel;

    nsstd::function<void (itk::TransformBase *outTransform)> m_pfUpdateWithBestValue;

    template < class TMemberFunctionPointer >
      struct EvaluateMemberFunctionAddressor
    {
      typedef typename ::detail::FunctionTraits<TMemberFunctionPointer>::ClassType ObjectType;

      template< typename TImageType >
      TMemberFunctionPointer operator() ( void ) const
        {
          return &ObjectType::template EvaluateInternal< TImageType >;
        }
    };

    typedef Transform (ImageRegistrationMethod::*MemberFunctionType)( const Image &fixed, const Image &moving );
    typedef double (ImageRegistrationMethod::*EvaluateMemberFunctionType)( const Image &fixed, const Image &moving );
    friend struct detail::MemberFunctionAddressor<MemberFunctionType>;
    std::auto_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;
    std::auto_ptr<detail::MemberFunctionFactory<EvaluateMemberFunctionType> > m_EvaluateMemberFactory;

    InterpolatorEnum  m_Interpolator;
    Transform  m_InitialTransform;
    bool m_InitialTransformInPlace;
    Transform m_MovingInitialTransform;
    Transform m_FixedInitialTransform;

    // optimizer
    enum OptimizerType { ConjugateGradientLineSearch,
                         RegularStepGradientDescent,
                         GradientDescent,
                         GradientDescentLineSearch,
                         LBFGSB,
                         Exhaustive,
                         Amoeba
    };
    OptimizerType m_OptimizerType;
    double m_OptimizerLearningRate;
    double m_OptimizerMinimumStepLength;
    unsigned int m_OptimizerNumberOfIterations;
    double m_OptimizerLineSearchLowerLimit;
    double m_OptimizerLineSearchUpperLimit;
    double m_OptimizerLineSearchEpsilon;
    unsigned int m_OptimizerLineSearchMaximumIterations;
    EstimateLearningRateType m_OptimizerEstimateLearningRate;
    double  m_OptimizerMaximumStepSizeInPhysicalUnits;
    double m_OptimizerRelaxationFactor;
    double m_OptimizerGradientMagnitudeTolerance;
    double m_OptimizerConvergenceMinimumValue;
    unsigned int m_OptimizerConvergenceWindowSize;
    double m_OptimizerGradientConvergenceTolerance;
    unsigned int m_OptimizerMaximumNumberOfCorrections;
    unsigned int m_OptimizerMaximumNumberOfFunctionEvaluations;
    double m_OptimizerCostFunctionConvergenceFactor;
    double m_OptimizerLowerBound;
    double m_OptimizerUpperBound;
    bool m_OptimizerTrace;
    std::vector<unsigned int> m_OptimizerNumberOfSteps;
    double m_OptimizerStepLength;
    double m_OptimizerSimplexDelta;
    double m_OptimizerParametersConvergenceTolerance;
    double m_OptimizerFunctionConvergenceTolerance;
    bool m_OptimizerWithRestarts;

    std::vector<double> m_OptimizerWeights;

    enum OptimizerScalesType {
      Manual,
      Jacobian,
      IndexShift,
      PhysicalShift
    };
    OptimizerScalesType m_OptimizerScalesType;
    std::vector<double> m_OptimizerScales;
    unsigned int m_OptimizerScalesCentralRegionRadius;
    double m_OptimizerScalesSmallParameterVariation;

    // metric
    enum MetricType { ANTSNeighborhoodCorrelation,
                      Correlation,
                      Demons,
                      JointHistogramMutualInformation,
                      MeanSquares,
                      MattesMutualInformation
    };
    MetricType m_MetricType;
    unsigned int m_MetricRadius;
    double m_MetricIntensityDifferenceThreshold;
    unsigned int m_MetricNumberOfHistogramBins;
    double m_MetricVarianceForJointPDFSmoothing;

    Image m_MetricFixedMaskImage;
    Image m_MetricMovingMaskImage;

    std::vector<double> m_MetricSamplingPercentage;
    MetricSamplingStrategyType m_MetricSamplingStrategy;

    bool m_MetricUseFixedImageGradientFilter;
    bool m_MetricUseMovingImageGradientFilter;

    std::vector<unsigned int> m_ShrinkFactorsPerLevel;
    std::vector<double> m_SmoothingSigmasPerLevel;
    bool m_SmoothingSigmasAreSpecifiedInPhysicalUnits;

    std::string m_StopConditionDescription;
    double m_MetricValue;
    unsigned int m_Iteration;

    itk::ObjectToObjectOptimizerBaseTemplate<double> *m_ActiveOptimizer;
  };

}
}

#endif // __sitkImageRegistrationMethod_h
