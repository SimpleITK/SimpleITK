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
#ifndef __itkMathematicalMorphologyImageFilter_txx
#define __itkMathematicalMorphologyImageFilter_txx

#include "itkMathematicalMorphologyImageFilter.h"

namespace itk
{
template< class TInputImage, class TOutputImage >
MathematicalMorphologyImageFilter< TInputImage, TOutputImage >
::MathematicalMorphologyImageFilter()
{
  this->m_Operation = BinaryErode;
}

template< class TInputImage, class TOutputImage >
void
MathematicalMorphologyImageFilter< TInputImage, TOutputImage >
::GenerateData()
{
  switch( this->m_Operation )
    {
    case BinaryErode:
      {
      typename BinaryErodeFilterType::Pointer filter = BinaryErodeFilterType::New();
      filter->SetInput( this->GetInput() );
      filter->GraftOutput( this->GetOutput() );
      filter->Update();
      this->GraftOutput( filter->GetOutput() );
      }
    case BinaryDilate:
      {
      typename BinaryDilateFilterType::Pointer filter = BinaryDilateFilterType::New();
      filter->SetInput( this->GetInput() );
      filter->GraftOutput( this->GetOutput() );
      filter->Update();
      this->GraftOutput( filter->GetOutput() );
      }
    case GrayscaleErode:
      {
      typename GrayscaleErodeFilterType::Pointer filter = GrayscaleErodeFilterType::New();
      filter->SetInput( this->GetInput() );
      filter->GraftOutput( this->GetOutput() );
      filter->Update();
      this->GraftOutput( filter->GetOutput() );
      }
    case GrayscaleDilate:
      {
      typename GrayscaleDilateFilterType::Pointer filter = GrayscaleDilateFilterType::New();
      filter->SetInput( this->GetInput() );
      filter->GraftOutput( this->GetOutput() );
      filter->Update();
      this->GraftOutput( filter->GetOutput() );
      }
    default:
      itkExceptionMacro("Unknown Operation" << this->m_Operation );
    }
}

/**
 * Standard "PrintSelf" method
 */
template< class TInputImage, class TOutput >
void
MathematicalMorphologyImageFilter< TInputImage, TOutput >
::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);
  os << indent << "Radius " << std::endl;
}
} // end namespace itk

#endif
