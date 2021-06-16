/*=========================================================================
*
*  Copyright NumFOCUS
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
#include "itkLBFGS2Optimizerv4.h"
#include "itkOnePlusOneEvolutionaryOptimizerv4.h"
#include "itkNormalVariateGenerator.h"
#include "itkExhaustiveOptimizerv4.h"
#include "itkAmoebaOptimizerv4.h"
#include "itkPowellOptimizerv4.h"

#include <time.h>


namespace {

template <typename T>
void UpdateWithBestValueExhaustive(itk::ExhaustiveOptimizerv4<T> *exhaustiveOptimizer,
                                   double *outValue,
                                   itk::TransformBase *outTransform)
{
  *outValue = exhaustiveOptimizer->GetMinimumMetricValue();
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

struct CurrentIterationCustomCast
{
  static unsigned int CustomCast(const itk::ObjectToObjectOptimizerBaseTemplate<double> *opt)
    {
      return static_cast<unsigned int>(std::min<itk::SizeValueType>(opt->GetCurrentIteration(), std::numeric_limits<unsigned int>::max()));
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
    using InternalComputationValueType = double;

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

      this->m_pfGetMetricValue = std::bind(&_OptimizerType::GetCurrentMetricValue,optimizer.GetPointer());
      this->m_pfGetOptimizerIteration = std::bind(&CurrentIterationCustomCast::CustomCast,optimizer.GetPointer());
      this->m_pfGetOptimizerPosition = std::bind(&PositionOptimizerCustomCast::CustomCast,optimizer.GetPointer());
      this->m_pfGetOptimizerLearningRate = std::bind(&_OptimizerType::GetLearningRate,optimizer.GetPointer());
      this->m_pfGetOptimizerConvergenceValue = std::bind(&_OptimizerType::GetConvergenceValue,optimizer.GetPointer());
      auto x = optimizer.GetPointer();
      this->m_pfGetOptimizerScales = [x]() {
        return PositionOptimizerCustomCast::Helper(x->GetScales());
      };
      this->m_pfOptimizerStopRegistration = std::bind(&_OptimizerType::StopOptimization, optimizer.GetPointer());

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

      this->m_pfGetMetricValue = std::bind(&_OptimizerType::GetCurrentMetricValue,optimizer.GetPointer());
      this->m_pfGetOptimizerIteration = std::bind(&CurrentIterationCustomCast::CustomCast,optimizer.GetPointer());
      this->m_pfGetOptimizerPosition = std::bind(&PositionOptimizerCustomCast::CustomCast,optimizer.GetPointer());
      this->m_pfGetOptimizerLearningRate = std::bind(&_OptimizerType::GetLearningRate,optimizer.GetPointer());
      this->m_pfGetOptimizerConvergenceValue = std::bind(&_OptimizerType::GetConvergenceValue,optimizer.GetPointer());
      auto x = optimizer.GetPointer();
      this->m_pfGetOptimizerScales = [x]() {
        return PositionOptimizerCustomCast::Helper(x->GetScales());
      };
      this->m_pfOptimizerStopRegistration = std::bind(&_OptimizerType::StopOptimization, optimizer.GetPointer());

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

      this->m_pfGetMetricValue = std::bind(&_OptimizerType::GetCurrentMetricValue,optimizer.GetPointer());
      this->m_pfGetOptimizerIteration = std::bind(&CurrentIterationCustomCast::CustomCast,optimizer.GetPointer());
      this->m_pfGetOptimizerPosition = std::bind(&PositionOptimizerCustomCast::CustomCast,optimizer.GetPointer());
      this->m_pfGetOptimizerLearningRate = std::bind(&_OptimizerType::GetLearningRate,optimizer.GetPointer());
      this->m_pfGetOptimizerConvergenceValue = std::bind(&_OptimizerType::GetConvergenceValue,optimizer.GetPointer());
      auto x = optimizer.GetPointer();
      this->m_pfGetOptimizerScales = [x]() {
        return PositionOptimizerCustomCast::Helper(x->GetScales());
      };
      this->m_pfOptimizerStopRegistration = std::bind(&_OptimizerType::StopOptimization, optimizer.GetPointer());


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

      this->m_pfGetMetricValue = std::bind(&_OptimizerType::GetValue,optimizer);
      this->m_pfGetOptimizerIteration = std::bind(&CurrentIterationCustomCast::CustomCast,optimizer.GetPointer());
      this->m_pfGetOptimizerPosition = std::bind(&PositionOptimizerCustomCast::CustomCast,optimizer.GetPointer());
      this->m_pfGetOptimizerLearningRate = std::bind(&_OptimizerType::GetLearningRate,optimizer.GetPointer());
      this->m_pfGetOptimizerConvergenceValue = std::bind(&_OptimizerType::GetConvergenceValue,optimizer.GetPointer());
      auto x = optimizer.GetPointer();
      this->m_pfGetOptimizerScales = [x]() {
        return PositionOptimizerCustomCast::Helper(x->GetScales());
      };
      this->m_pfOptimizerStopRegistration = std::bind(&_OptimizerType::StopOptimization, optimizer.GetPointer());


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
      lowerBound.Fill( this->m_OptimizerLowerBound );
      upperBound.Fill( this->m_OptimizerUpperBound );

      optimizer->SetBoundSelection( boundSelection );
      optimizer->SetLowerBound( lowerBound  );
      optimizer->SetUpperBound( upperBound  );
      optimizer->SetTrace( m_OptimizerTrace );
      optimizer->Register();

      this->m_pfGetMetricValue = std::bind(&_OptimizerType::GetValue,optimizer.GetPointer());
      this->m_pfGetOptimizerIteration = std::bind(&CurrentIterationCustomCast::CustomCast,optimizer.GetPointer());
      this->m_pfGetOptimizerPosition = std::bind(&PositionOptimizerCustomCast::CustomCast,optimizer.GetPointer());
      auto x = optimizer.GetPointer();
      this->m_pfGetOptimizerScales = [x]() {
        return PositionOptimizerCustomCast::Helper(x->GetScales());
      };
      this->m_pfOptimizerStopRegistration = nullptr;


      return optimizer.GetPointer();
      }
    else if ( m_OptimizerType == LBFGS2 )
      {
      typedef itk::LBFGS2Optimizerv4 _OptimizerType;
      _OptimizerType::Pointer      optimizer =  _OptimizerType::New();

      optimizer->SetSolutionAccuracy( this->m_OptimizerSolutionAccuracy );
      optimizer->SetNumberOfIterations( this->m_OptimizerNumberOfIterations );
      optimizer->SetHessianApproximationAccuracy( this->m_OptimizerHessianApproximationAccuracy );
      optimizer->SetDeltaConvergenceDistance( this->m_OptimizerDeltaConvergenceDistance );
      optimizer->SetDeltaConvergenceTolerance( this->m_OptimizerDeltaConvergenceTolerance );
      optimizer->SetMaximumLineSearchEvaluations( this->m_OptimizerLineSearchMaximumEvaluations );
      optimizer->SetMinimumLineSearchStep( this->m_OptimizerLineSearchMinimumStep );
      optimizer->SetMaximumLineSearchStep( this->m_OptimizerLineSearchMaximumStep );
      optimizer->SetLineSearchAccuracy( this->m_OptimizerLineSearchAccuracy );
      optimizer->Register();

      this->m_pfGetMetricValue = std::bind(&_OptimizerType::GetValue,optimizer.GetPointer());
      this->m_pfGetOptimizerIteration = std::bind(&CurrentIterationCustomCast::CustomCast,optimizer.GetPointer());
      this->m_pfGetOptimizerPosition = std::bind(&PositionOptimizerCustomCast::CustomCast,optimizer.GetPointer());
      auto x = optimizer.GetPointer();
      this->m_pfGetOptimizerScales = [x]() {
        return PositionOptimizerCustomCast::Helper(x->GetScales());
      };
      this->m_pfOptimizerStopRegistration = nullptr;


      return optimizer.GetPointer();
      }
    else if ( m_OptimizerType == Exhaustive )
      {
      typedef itk::ExhaustiveOptimizerv4<double> _OptimizerType;
      _OptimizerType::Pointer      optimizer     = _OptimizerType::New();

      optimizer->SetStepLength( this->m_OptimizerStepLength );
      optimizer->SetNumberOfSteps( sitkSTLVectorToITKArray<_OptimizerType::StepsType::ValueType>(this->m_OptimizerNumberOfSteps));

      this->m_pfGetMetricValue = std::bind(&_OptimizerType::GetCurrentValue,optimizer);
      this->m_pfGetOptimizerIteration = std::bind(&CurrentIterationCustomCast::CustomCast,optimizer.GetPointer());
      this->m_pfGetOptimizerPosition = std::bind(&PositionOptimizerCustomCast::CustomCast,optimizer);
      auto x = optimizer.GetPointer();
      this->m_pfGetOptimizerScales = [x]() {
        return PositionOptimizerCustomCast::Helper(x->GetScales());
      };


      this->m_pfUpdateWithBestValue = std::bind(&UpdateWithBestValueExhaustive<double>,
                                                  optimizer,
                                                  &(this->m_MetricValue),
                                                  std::placeholders::_1);

      this->m_pfOptimizerStopRegistration = std::bind(&_OptimizerType::StopWalking, optimizer.GetPointer());

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


      this->m_pfGetMetricValue = std::bind(&_OptimizerType::GetValue,optimizer);
      this->m_pfGetOptimizerIteration = std::bind(&CurrentIterationCustomCast::CustomCast,optimizer.GetPointer());
      this->m_pfGetOptimizerPosition = std::bind(&PositionOptimizerCustomCast::CustomCast,optimizer);
      auto x = optimizer.GetPointer();
      this->m_pfGetOptimizerScales = [x]() {
        return PositionOptimizerCustomCast::Helper(x->GetScales());
      };
      this->m_pfOptimizerStopRegistration = nullptr;


      optimizer->Register();
      return optimizer.GetPointer();
      }
    else if ( m_OptimizerType == Powell )
      {
      typedef itk::PowellOptimizerv4<double> _OptimizerType;
      _OptimizerType::Pointer optimizer = _OptimizerType::New();

      optimizer->SetMaximumIteration( this->m_OptimizerNumberOfIterations );
      optimizer->SetMaximumLineIteration( this->m_OptimizerMaximumLineIterations );
      optimizer->SetStepLength(this->m_OptimizerStepLength );
      optimizer->SetStepTolerance( this->m_OptimizerStepTolerance );
      optimizer->SetValueTolerance( this->m_OptimizerValueTolerance );

      this->m_pfGetMetricValue = std::bind(&_OptimizerType::GetValue,optimizer.GetPointer());
      this->m_pfGetOptimizerIteration = std::bind(&CurrentIterationCustomCast::CustomCast,optimizer.GetPointer());
      this->m_pfGetOptimizerPosition = std::bind(&PositionOptimizerCustomCast::CustomCast,optimizer.GetPointer());
      auto x = optimizer.GetPointer();
      this->m_pfGetOptimizerScales = [x]() {
        return PositionOptimizerCustomCast::Helper(x->GetScales());
      };
      this->m_pfOptimizerStopRegistration = std::bind(&_OptimizerType::StopOptimization, optimizer.GetPointer());


      optimizer->Register();
      return optimizer.GetPointer();
      }
    else if ( m_OptimizerType == OnePlusOneEvolutionary )
      {
       typedef itk::OnePlusOneEvolutionaryOptimizerv4<double> _OptimizerType;
      _OptimizerType::Pointer optimizer = _OptimizerType::New();
      optimizer->SetMaximumIteration( this->m_OptimizerNumberOfIterations );
      optimizer->SetEpsilon( this->m_OptimizerEpsilon );
      optimizer->Initialize( this->m_OptimizerInitialRadius,
                             this->m_OptimizerGrowthFactor,
                             this->m_OptimizerShrinkFactor);

      using GeneratorType = itk::Statistics::NormalVariateGenerator;
      GeneratorType::Pointer generator = GeneratorType::New();
      if ( this->m_OptimizerSeed == sitkWallClock )
        {
        // use time() and clock() to generate a unlikely-to-repeat
        // seed.
        uint64_t seed =  time(ITK_NULLPTR);
        seed ^= (uint64_t)clock();
        generator->Initialize( static_cast<unsigned int>(seed) );
        }
      else
        {
        generator->Initialize(this->m_OptimizerSeed);
        }
      optimizer->SetNormalVariateGenerator( generator );

      this->m_pfGetMetricValue = std::bind(&_OptimizerType::GetValue,optimizer.GetPointer());
      this->m_pfGetOptimizerIteration = std::bind(&CurrentIterationCustomCast::CustomCast,optimizer.GetPointer());
      this->m_pfGetOptimizerPosition = std::bind(&PositionOptimizerCustomCast::CustomCast,optimizer.GetPointer());
      this->m_pfGetOptimizerConvergenceValue = std::bind(&_OptimizerType::GetFrobeniusNorm,optimizer.GetPointer());
      auto x = optimizer.GetPointer();
      this->m_pfGetOptimizerScales = [x]() {
        return PositionOptimizerCustomCast::Helper(x->GetScales());
      };
      this->m_pfOptimizerStopRegistration = std::bind(&_OptimizerType::StopOptimization, optimizer.GetPointer());

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
