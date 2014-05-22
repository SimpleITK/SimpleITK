#include "sitkImageRegistrationMethod.h"

#include "itkGradientDescentOptimizerv4.h"
#include "itkRegularStepGradientDescentOptimizerv4.h"


namespace {

struct PositionOptimizerCustomCast
{
  template <typename T>
  static std::vector<double> Helper(const T &value)
    { return std::vector<double>(value.begin(),value.end()); }

  static std::vector<double> CustomCast(const itk::ObjectToObjectOptimizerBaseTemplate<double> *opt)
    {
      return Helper(opt->GetCurrentPosition());
    }
};

}

namespace itk
{
namespace simple
{



  itk::ObjectToObjectOptimizerBaseTemplate<double>*
  ImageRegistrationMethod::CreateOptimizer( )
  {
    typedef double InternalComputationValueType;

    if ( m_OptimizerType == GradientDescent )
      {
      typedef itk::GradientDescentOptimizerv4Template<InternalComputationValueType> _OptimizerType;
      _OptimizerType::Pointer      optimizer     = _OptimizerType::New();
      optimizer->SetLearningRate( this->m_OptimizerLearningRate );
      optimizer->SetNumberOfIterations( this->m_OptimizerNumberOfIterations );
      optimizer->SetMinimumConvergenceValue( this->m_OptimizerConvergenceMinimumValue );
      optimizer->SetConvergenceWindowSize( this->m_OptimizerConvergenceWindowSize );

      this->m_pfGetMetricValue = nsstd::bind(&_OptimizerType::GetCurrentMetricValue,optimizer);
      this->m_pfGetOptimizerIteration = nsstd::bind(&_OptimizerType::GetCurrentIteration,optimizer);
      this->m_pfGetOptimizerPosition = nsstd::bind(&PositionOptimizerCustomCast::CustomCast,optimizer);

      optimizer->Register();
      return optimizer.GetPointer();
      }
    else if ( m_OptimizerType == RegularStepGradientDescent )
      {
      typedef itk::RegularStepGradientDescentOptimizerv4<InternalComputationValueType> _OptimizerType;
      _OptimizerType::Pointer      optimizer =  _OptimizerType::New();

      optimizer->SetLearningRate( this->m_OptimizerLearningRate );
      optimizer->SetMinimumStepLength( this->m_OptimizerMinimumStepLength );
      optimizer->SetNumberOfIterations( this->m_OptimizerNumberOfIterations  );
      optimizer->SetRelaxationFactor( this->m_OptimizerRelaxationFactor );
      optimizer->Register();

      this->m_pfGetMetricValue = nsstd::bind(&_OptimizerType::GetValue,optimizer);
      this->m_pfGetOptimizerIteration = nsstd::bind(&_OptimizerType::GetCurrentIteration,optimizer);
      this->m_pfGetOptimizerPosition = nsstd::bind(&PositionOptimizerCustomCast::CustomCast,optimizer);

      return optimizer.GetPointer();
      }
    else
      {
      sitkExceptionMacro("LogicError: Unexpected case!");
      }
  }

}
}
