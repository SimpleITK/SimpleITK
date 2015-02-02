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
#include "sitkTranslationTransform.h"
#include "sitkTransformHelper.hxx"

#include "itkTranslationTransform.h"

namespace itk
{
namespace simple
{

TranslationTransform::TranslationTransform(unsigned int dimensions,
                                           const std::vector<double> &offset)
  : Transform(dimensions, sitkTranslation)

{
  Self::InternalInitialization(Self::GetITKBase());

  this->SetOffset(offset);
}


TranslationTransform::TranslationTransform( const TranslationTransform &arg )
  : Transform(arg)
{
  Self::InternalInitialization(Self::GetITKBase());
}


TranslationTransform::TranslationTransform( const Transform &arg )
  : Transform(arg)
{
  Self::InternalInitialization(Self::GetITKBase());
}


TranslationTransform &TranslationTransform::operator=( const TranslationTransform &arg )
{
  Superclass::operator=(arg);
  return *this;
}


/** fixed parameter */
TranslationTransform::Self &TranslationTransform::SetOffset(const std::vector<double> &params)
{
  this->MakeUnique();
  this->m_pfSetOffset(params);
  return *this;
}

std::vector<double> TranslationTransform::GetOffset( ) const
{
  return this->m_pfGetOffset();
}
void TranslationTransform::SetPimpleTransform( PimpleTransformBase *pimpleTransform )
{
  Superclass::SetPimpleTransform(pimpleTransform);
  Self::InternalInitialization(this->GetITKBase());
}

void TranslationTransform::InternalInitialization(itk::TransformBase *transform)
{

  MyVisitor visitor;
  visitor.transform = transform;
  visitor.that = this;

  typedef typelist::MakeTypeList<itk::TranslationTransform<double, 3>,
                                 itk::TranslationTransform<double, 2> >::Type TransformTypeList;

  typelist::Visit<TransformTypeList> callInternalInitialization;

  // explicitly remove all function pointer with reference to prior transform
  this->m_pfSetOffset = SITK_NULLPTR;
  this->m_pfGetOffset = SITK_NULLPTR;

  callInternalInitialization(visitor);

  if ( this->m_pfSetOffset == SITK_NULLPTR )
    {
    sitkExceptionMacro("Transform is not of type " << this->GetName() << "!" );
    }
}


template<class TransformType>
void TranslationTransform::InternalInitialization(TransformType *t)
{
  SITK_TRANSFORM_SET_MPF(Offset, typename TransformType::OutputVectorType, double);

}

}
}
