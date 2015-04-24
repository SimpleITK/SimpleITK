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
#include "sitkImageRegistrationMethod.h"

#include "itkConjugateGradientLineSearchOptimizerv4.h"
#include "itkGradientDescentOptimizerv4.h"
#include "itkRegularStepGradientDescentOptimizerv4.h"
#include "itkLBFGSBOptimizerv4.h"
#include "itkExhaustiveOptimizerv4.h"
#include "itkAmoebaOptimizerv4.h"


namespace {

template <typename T>
void UpdateWithBestValueExhaustive(itk::ExhaustiveOptimizerv4<T> *exhaustiveOptimizer,
                                   double &outValue,
                                   itk::TransformBase *outTransform)
{
  outValue = exhaustiveOptimizer->GetMinimumMetricValue();
  if (outTransform)
    {
    outTransform->SetParameters(exhaustiveOptimizer->GetMinimumMetricValuePosition());
    }
}

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

  template< typename TValue, typename TType>
  itk::Array<TValue> sitkSTLVectorToITKArray( const std::vector< TType > & in )
  {
    itk::Array<TValue> out(in.size());
    std::copy(in.begin(), in.end(), out.begin());
    return out;
  }

  itk::ObjectToObjectOptimizerBaseTemplate<double>*
  ImageRegistrationMethod::CreateOptimizer( unsigned int numberOfTransformParameters )
  {
    typedef double InternalComputationValueType;

    if ( m_OptimizerType == ConjugateGradientLineSearch )
      {
      typedef itk::ConjugateGradientLineSearchOptimizerv4Template<InternalComputationValueType> _OptimizerType;
      _OptimizerType::Pointer      optimizer     = _OptimizerType::New();
      optimizer->SetLearningRate( this->m_OptimizerLearningRate );
      optimizer->SetNumberOfIterations( this->m_OptimizerNumberOfIterations );
      optimizer->SetMinimumConvergenceValue( this->m_OptimizerConvergenceMinimumValue );
      optimizer->SetConvergenceWindowSize( this->m_OptimizerConvergenceWindowSize );
      optimizer->SetLowerLimit( this->m_OptimizerLineSearchLowerLimit);
      optimizer->SetUpperLimit( this->m_OptimizerLineSearchUpperLimit);
      optimizer->SetEpsilon( this->m_OptimizerLineSearchEpsilon);
      optimizer->SetMaximumLineSearchIterations( this->m_OptimizerLineSearchMaximumIterations);
      optimizer->SetDoEstimateLearningRateAtEachIteration( this->m_OptimizerEstimateLearningRate==EachIteration );
      optimizer->SetDoEstimateLearningRateOnce( this->m_OptimizerEstimateLearningRate==Once );
      optimizer->SetMaximumStepSizeInPhysicalUnits( this->m_OptimizerMaximumStepSizeInPhysicalUnits );

      this->m_pfGetMetricValue = nsstd::bind(&_OptimizerType::GetCurrentMetricValue,optimizer.GetPointer());
      this->m_pfGetOptimizerIteration = nsstd::bind(&_OptimizerType::GetCurrentIteration,optimizer.GetPointer());
      this->m_pfGetOptimizerPosition = nsstd::bind(&PositionOptimizerCustomCast::CustomCast,optimizer.GetPointer());
      this->m_pfGetOptimizerLearningRate = nsstd::bind(&_OptimizerType::GetLearningRate,optimizer.GetPointer());
      this->m_pfGetOptimizerConvergenceValue = nsstd::bind(&_OptimizerType::GetConvergenceValue,optimizer.GetPointer());
      this->m_pfGetOptimizerScales = nsstd::bind(&PositionOptimizerCustomCast::Helper<_OptimizerType::ScalesType>, nsstd::bind(&_OptimizerType::GetScales, optimizer.GetPointer()));

      optimizer->Register();
      return optimizer.GetPointer();
      }
    else if ( m_OptimizerType == GradientDescent )
      {
      typedef itk::GradientDescentOptimizerv4Template<InternalComputationValueType> _OptimizerType;
      _OptimizerType::Pointer      optimizer     = _OptimizerType::New();
      optimizer->SetLearningRate( this->m_OptimizerLearningRate );
      optimizer->SetNumberOfIterations( this->m_OptimizerNumberOfIterations );
      optimizer->SetMinimumConvergenceValue( this->m_OptimizerConvergenceMinimumValue );
      optimizer->SetConvergenceWindowSize( this->m_OptimizerConvergenceWindowSize );
      optimizer->SetDoEstimateLearningRateAtEachIteration( this->m_OptimizerEstimateLearningRate==EachIteration );
      optimizer->SetDoEstimateLearningRateOnce( this->m_OptimizerEstimateLearningRate==Once );
      optimizer->SetMaximumStepSizeInPhysicalUnits( this->m_OptimizerMaximumStepSizeInPhysicalUnits );

      this->m_pfGetMetricValue = nsstd::bind(&_OptimizerType::GetCurrentMetricValue,optimizer.GetPointer());
      this->m_pfGetOptimizerIteration = nsstd::bind(&_OptimizerType::GetCurrentIteration,optimizer.GetPointer());
      this->m_pfGetOptimizerPosition = nsstd::bind(&PositionOptimizerCustomCast::CustomCast,optimizer.GetPointer());
      this->m_pfGetOptimizerLearningRate = nsstd::bind(&_OptimizerType::GetLearningRate,optimizer.GetPointer());
      this->m_pfGetOptimizerConvergenceValue = nsstd::bind(&_OptimizerType::GetConvergenceValue,optimizer.GetPointer());
      this->m_pfGetOptimizerScales = nsstd::bind(&PositionOptimizerCustomCast::Helper<_OptimizerType::ScalesType>, nsstd::bind(&_OptimizerType::GetScales, optimizer.GetPointer()));

      optimizer->Register();
      return optimizer.GetPointer();
      }
    else if ( m_OptimizerType == GradientDescentLineSearch )
      {
      typedef itk::GradientDescentLineSearchOptimizerv4Template<InternalComputationValueType> _OptimizerType;
      _OptimizerType::Pointer      optimizer     = _OptimizerType::New();
      optimizer->SetLearningRate( this->m_OptimizerLearningRate );
      optimizer->SetNumberOfIterations( this->m_OptimizerNumberOfIterations );
      optimizer->SetMinimumConvergenceValue( this->m_OptimizerConvergenceMinimumValue );
      optimizer->SetConvergenceWindowSize( this->m_OptimizerConvergenceWindowSize );
      optimizer->SetLowerLimit( this->m_OptimizerLineSearchLowerLimit);
      optimizer->SetUpperLimit( this->m_OptimizerLineSearchUpperLimit);
      optimizer->SetEpsilon( this->m_OptimizerLineSearchEpsilon);
      optimizer->SetMaximumLineSearchIterations( this->m_OptimizerLineSearchMaximumIterations);
      optimizer->SetDoEstimateLearningRateAtEachIteration( this->m_OptimizerEstimateLearningRate==EachIteration );
      optimizer->SetDoEstimateLearningRateOnce( this->m_OptimizerEstimateLearningRate==Once );
      optimizer->SetMaximumStepSizeInPhysicalUnits( this->m_OptimizerMaximumStepSizeInPhysicalUnits );

      this->m_pfGetMetricValue = nsstd::bind(&_OptimizerType::GetCurrentMetricValue,optimizer.GetPointer());
      this->m_pfGetOptimizerIteration = nsstd::bind(&_OptimizerType::GetCurrentIteration,optimizer.GetPointer());
      this->m_pfGetOptimizerPosition = nsstd::bind(&PositionOptimizerCustomCast::CustomCast,optimizer.GetPointer());
      this->m_pfGetOptimizerLearningRate = nsstd::bind(&_OptimizerType::GetLearningRate,optimizer.GetPointer());
      this->m_pfGetOptimizerConvergenceValue = nsstd::bind(&_OptimizerType::GetConvergenceValue,optimizer.GetPointer());
      this->m_pfGetOptimizerScales = nsstd::bind(&PositionOptimizerCustomCast::Helper<_OptimizerType::ScalesType>, nsstd::bind(&_OptimizerType::GetScales, optimizer.GetPointer()));

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
      optimizer->SetGradientMagnitudeTolerance( this->m_OptimizerGradientMagnitudeTolerance );
      optimizer->SetDoEstimateLearningRateAtEachIteration( this->m_OptimizerEstimateLearningRate==EachIteration );
      optimizer->SetDoEstimateLearningRateOnce( this->m_OptimizerEstimateLearningRate==Once );
      optimizer->SetMaximumStepSizeInPhysicalUnits( this->m_OptimizerMaximumStepSizeInPhysicalUnits );
      optimizer->Register();

      this->m_pfGetMetricValue = nsstd::bind(&_OptimizerType::GetValue,optimizer);
      this->m_pfGetOptimizerIteration = nsstd::bind(&_OptimizerType::GetCurrentIteration,optimizer.GetPointer());
      this->m_pfGetOptimizerPosition = nsstd::bind(&PositionOptimizerCustomCast::CustomCast,optimizer.GetPointer());
      this->m_pfGetOptimizerLearningRate = nsstd::bind(&_OptimizerType::GetLearningRate,optimizer.GetPointer());
      this->m_pfGetOptimizerConvergenceValue = nsstd::bind(&_OptimizerType::GetConvergenceValue,optimizer.GetPointer());
      this->m_pfGetOptimizerScales = nsstd::bind(&PositionOptimizerCustomCast::Helper<_OptimizerType::ScalesType>, nsstd::bind(&_OptimizerType::GetScales, optimizer.GetPointer()));

      return optimizer.GetPointer();
      }
    else if ( m_OptimizerType == LBFGSB )
      {
      typedef itk::LBFGSBOptimizerv4 _OptimizerType;
      _OptimizerType::Pointer      optimizer =  _OptimizerType::New();

      optimizer->SetGradientConvergenceTolerance( this->m_OptimizerGradientConvergenceTolerance );
      optimizer->SetNumberOfIterations( this->m_OptimizerNumberOfIterations );
      optimizer->SetMaximumNumberOfCorrections( this->m_OptimizerMaximumNumberOfCorrections  );
      optimizer->SetMaximumNumberOfFunctionEvaluations( this->m_OptimizerMaximumNumberOfFunctionEvaluations );
      optimizer->SetCostFunctionConvergenceFactor( this->m_OptimizerCostFunctionConvergenceFactor );

      #define NOBOUND     0 // 00
      #define LOWERBOUND  1 // 01
      #define UPPERBOUND  2 // 10
      #define BOTHBOUND   3 // 11

      unsigned char flag = NOBOUND;
      const unsigned int sitkToITK[] = {0,1,3,2};
      if ( this->m_OptimizerLowerBound != std::numeric_limits<double>::min() )
        {
        flag |= LOWERBOUND;
        }
      if ( this->m_OptimizerUpperBound != std::numeric_limits<double>::max() )
        {
        flag |= UPPERBOUND;
        }

      _OptimizerType::BoundSelectionType boundSelection( numberOfTransformParameters );
      _OptimizerType::BoundValueType lowerBound( numberOfTransformParameters );
      _OptimizerType::BoundValueType upperBound( numberOfTransformParameters );

      boundSelection.Fill( sitkToITK[flag] );
      lowerBound.Fill( this->m_OptimizerUpperBound );
      upperBound.Fill( this->m_OptimizerUpperBound );

      optimizer->SetBoundSelection( boundSelection );
      optimizer->SetLowerBound( lowerBound  );
      optimizer->SetUpperBound( upperBound  );
      optimizer->SetTrace( m_OptimizerTrace );
      optimizer->Register();

      this->m_pfGetMetricValue = nsstd::bind(&_OptimizerType::GetValue,optimizer.GetPointer());
      this->m_pfGetOptimizerIteration = nsstd::bind(&_OptimizerType::GetCurrentIteration,optimizer.GetPointer());
      this->m_pfGetOptimizerPosition = nsstd::bind(&PositionOptimizerCustomCast::CustomCast,optimizer.GetPointer());

      return optimizer.GetPointer();
      }
    else if ( m_OptimizerType == Exhaustive )
      {
      typedef itk::ExhaustiveOptimizerv4<double> _OptimizerType;
      _OptimizerType::Pointer      optimizer     = _OptimizerType::New();

      optimizer->SetStepLength( this->m_OptimizerStepLength );
      optimizer->SetNumberOfSteps( sitkSTLVectorToITKArray<_OptimizerType::StepsType::ValueType>(this->m_OptimizerNumberOfSteps));

      this->m_pfGetMetricValue = nsstd::bind(&_OptimizerType::GetCurrentValue,optimizer);
      this->m_pfGetOptimizerIteration = nsstd::bind(&_OptimizerType::GetCurrentIteration,optimizer);
      this->m_pfGetOptimizerPosition = nsstd::bind(&PositionOptimizerCustomCast::CustomCast,optimizer);

      this->m_pfGetOptimizerScales = nsstd::bind(&PositionOptimizerCustomCast::Helper<_OptimizerType::ScalesType>, nsstd::bind(&_OptimizerType::GetScales, optimizer.GetPointer()));

      this->m_pfUpdateWithBestValue = nsstd::bind(&UpdateWithBestValueExhaustive<double>,
                                                  optimizer,
                                                  this->m_MetricValue,
                                                  nsstd::placeholders::_1);


      optimizer->Register();
      return optimizer.GetPointer();
      }
    else if( m_OptimizerType == Amoeba )
      {
      typedef itk::AmoebaOptimizerv4 _OptimizerType;
      _OptimizerType::Pointer      optimizer     = _OptimizerType::New();

      _OptimizerType::ParametersType simplexDelta( numberOfTransformParameters );
      simplexDelta.Fill( this->m_OptimizerSimplexDelta );
      optimizer->SetInitialSimplexDelta( simplexDelta );

      optimizer->SetNumberOfIterations( this->m_OptimizerNumberOfIterations  );
      optimizer->SetParametersConvergenceTolerance(this->m_OptimizerParametersConvergenceTolerance);
      optimizer->SetFunctionConvergenceTolerance(this->m_OptimizerFunctionConvergenceTolerance);
      optimizer->SetOptimizeWithRestarts(this->m_OptimizerWithRestarts);


      this->m_pfGetMetricValue = nsstd::bind(&_OptimizerType::GetValue,optimizer);
      this->m_pfGetOptimizerIteration = nsstd::bind(&_OptimizerType::GetCurrentIteration,optimizer);
      this->m_pfGetOptimizerPosition = nsstd::bind(&PositionOptimizerCustomCast::CustomCast,optimizer);

      optimizer->Register();
      return optimizer.GetPointer();
      }
    else
      {
      sitkExceptionMacro("LogicError: Unexpected case!");
      }
  }

}
}
