#include "sitkImageRegistrationMethod.h"

#include "itkRegularStepGradientDescentOptimizer.h"
#include "itkGradientDescentOptimizer.h"


namespace {

struct PositionOptimizerCustomCast
{
  template <typename T>
  static std::vector<double> Helper(const T &value)
    { return std::vector<double>(value.begin(),value.end()); }

  static std::vector<double> CustomCast(const itk::SingleValuedNonLinearOptimizer *opt)
    {
      return Helper(opt->GetCurrentPosition());
    }
};

}

namespace itk
{
namespace simple
{



  itk::SingleValuedNonLinearOptimizer*
  ImageRegistrationMethod::CreateOptimizer( )
  {

    itk::SingleValuedNonLinearOptimizer::ScalesType scales(m_OptimizerScales.size());
    std::copy( m_OptimizerScales.begin(), m_OptimizerScales.end(), scales.begin() );


    if ( m_OptimizerType == GradientDescent )
      {
      typedef itk::GradientDescentOptimizer _OptimizerType;
      _OptimizerType::Pointer      optimizer     = _OptimizerType::New();
      optimizer->SetLearningRate( this->m_OptimizerLearningRate );
      optimizer->SetNumberOfIterations( this->m_OptimizerNumberOfIterations  );
      optimizer->SetMinimize( this->m_OptimizerMinimize );
      if (scales.GetSize()) optimizer->SetScales(scales);

      this->m_pfGetMetricValue = std::tr1::bind(&_OptimizerType::GetValue,optimizer);
      this->m_pfGetOptimizerIteration = std::tr1::bind(&_OptimizerType::GetCurrentIteration,optimizer);
      this->m_pfGetOptimizerPosition = std::tr1::bind(&PositionOptimizerCustomCast::CustomCast,optimizer);

      optimizer->Register();
      return optimizer.GetPointer();
      }
    else if ( m_OptimizerType == RegularStepGradientDescent )
      {
      typedef itk::RegularStepGradientDescentBaseOptimizer _OptimizerType;
      _OptimizerType::Pointer      optimizer;
      optimizer = itk::RegularStepGradientDescentOptimizer::New();

      optimizer->SetMaximumStepLength( this->m_OptimizerMaximumStepLength );
      optimizer->SetMinimumStepLength( this->m_OptimizerMinimumStepLength );
      optimizer->SetNumberOfIterations( this->m_OptimizerNumberOfIterations  );
      optimizer->SetMinimize( this->m_OptimizerMinimize );
      optimizer->SetRelaxationFactor( this->m_OptimizerRelaxationFactor );
      if (scales.GetSize()) optimizer->SetScales(scales);
      optimizer->Register();

      this->m_pfGetMetricValue = std::tr1::bind(&_OptimizerType::GetValue,optimizer);
      this->m_pfGetOptimizerIteration = std::tr1::bind(&_OptimizerType::GetCurrentIteration,optimizer);
      this->m_pfGetOptimizerPosition = std::tr1::bind(&PositionOptimizerCustomCast::CustomCast,optimizer);

      return optimizer.GetPointer();
      }
    else
      {
      sitkExceptionMacro("LogicError: Unexpected case!");
      }
  }

}
}
