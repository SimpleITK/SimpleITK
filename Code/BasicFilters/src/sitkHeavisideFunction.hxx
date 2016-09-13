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
#ifndef sitkHeavisideFunction_h
#define sitkHeavisideFunction_h

#include "itkAtanRegularizedHeavisideStepFunction.h"
#include "itkSinRegularizedHeavisideStepFunction.h"
#include "itkHeavisideStepFunction.h"

namespace itk {
namespace simple {

  if (m_HeavisideStepFunction == AtanRegularizedHeaviside) {
    typedef itk::AtanRegularizedHeavisideStepFunction< typename InputImageType::PixelType, typename InputImageType::PixelType >  DomainFunctionType;
    typename DomainFunctionType::Pointer domainFunction = DomainFunctionType::New();
    domainFunction->SetLambda(m_Lambda);
    filter->GetDifferenceFunction(0)->SetDomainFunction( domainFunction );
  } else if ( m_HeavisideStepFunction == SinRegularizedHeaviside ) {
    typedef itk::AtanRegularizedHeavisideStepFunction< typename InputImageType::PixelType, typename InputImageType::PixelType >  DomainFunctionType;
    typename DomainFunctionType::Pointer domainFunction = DomainFunctionType::New();
    domainFunction->SetLambda(m_Lambda);
    filter->GetDifferenceFunction(0)->SetDomainFunction( domainFunction );
  } else {
    typedef itk::HeavisideStepFunction< typename InputImageType::PixelType, typename InputImageType::PixelType >  DomainFunctionType;
    typename DomainFunctionType::Pointer domainFunction = DomainFunctionType::New();
    filter->GetDifferenceFunction(0)->SetDomainFunction( domainFunction );
  }


} // end namespace simple
} // end namespace itk

#endif
