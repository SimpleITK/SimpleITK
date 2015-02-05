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
#include "sitkScaleTransform.h"
#include "sitkTransformHelper.hxx"
#include "itkScaleTransform.h"

namespace itk
{
namespace simple
{

ScaleTransform::ScaleTransform(unsigned int dimensions,
                                           const std::vector<double> &scale)
  : Transform(dimensions, sitkScale)

{
  Self::InternalInitialization(Self::GetITKBase());

  this->SetScale(scale);
}


ScaleTransform::ScaleTransform( const Transform &arg )
  : Transform(arg)
{
  Self::InternalInitialization(Self::GetITKBase());
}


ScaleTransform::ScaleTransform( const ScaleTransform &arg )
  : Transform(arg)
{
  Self::InternalInitialization(Self::GetITKBase());
}


ScaleTransform &ScaleTransform::operator=( const ScaleTransform &arg )
{
  Superclass::operator=(arg);
  return *this;
}


/** fixed parameter */
ScaleTransform::Self &ScaleTransform::SetCenter(const std::vector<double> &params)
{
  this->MakeUnique();
  this->m_pfSetCenter(params);
  return *this;
}

std::vector<double> ScaleTransform::GetCenter( ) const
{
  return this->m_pfGetCenter();
}

ScaleTransform::Self &ScaleTransform::SetScale(const std::vector<double> &params)
{
  this->MakeUnique();
  this->m_pfSetScale(params);
  return *this;
}

std::vector<double> ScaleTransform::GetScale( ) const
{
  return this->m_pfGetScale();
}

std::vector<double> ScaleTransform::GetMatrix( ) const
{
  return this->m_pfGetMatrix();
}

void ScaleTransform::SetPimpleTransform( PimpleTransformBase *pimpleTransform )
{
  Superclass::SetPimpleTransform(pimpleTransform);
  Self::InternalInitialization(this->GetITKBase());
}

void ScaleTransform::InternalInitialization(itk::TransformBase *transform)
{

  MyVisitor visitor;
  visitor.transform = transform;
  visitor.that = this;

  typedef typelist::MakeTypeList<itk::ScaleTransform<double, 3>,
                                 itk::ScaleTransform<double, 2> >::Type TransformTypeList;

  typelist::Visit<TransformTypeList> callInternalInitialization;

  this->m_pfSetCenter = SITK_NULLPTR;
  this->m_pfGetCenter = SITK_NULLPTR;
  this->m_pfSetScale = SITK_NULLPTR;
  this->m_pfGetScale = SITK_NULLPTR;
  this->m_pfGetMatrix = SITK_NULLPTR;

  callInternalInitialization(visitor);

  if ( this->m_pfSetCenter == SITK_NULLPTR )
    {
    sitkExceptionMacro("Transform is not of type " << this->GetName() << "!" );
    }
}


template<class TransformType>
void ScaleTransform::InternalInitialization(TransformType *t)
{
  SITK_TRANSFORM_SET_MPF(Center, typename TransformType::InputPointType, double);
  SITK_TRANSFORM_SET_MPF(Scale, typename TransformType::ScaleType, double);
  SITK_TRANSFORM_SET_MPF_GetMatrix();

}

}
}
