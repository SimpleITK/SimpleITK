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
#include "sitkVersorTransform.h"
#include "sitkTransformHelper.hxx"

#include "itkVersorTransform.h"

namespace itk
{
namespace simple
{

VersorTransform::~VersorTransform() = default;

// construct identity
VersorTransform::VersorTransform()
  : Transform(3, sitkVersor)
{
  Self::InternalInitialization(Self::GetITKBase());
}

VersorTransform::VersorTransform( const VersorTransform &arg )
  : Transform(arg)
{
  Self::InternalInitialization(Self::GetITKBase());
}

VersorTransform::VersorTransform( const Transform &arg )
  : Transform(arg)
{
  Self::InternalInitialization(Self::GetITKBase());
}

VersorTransform::VersorTransform( const std::vector< double > &versor,
                                  const std::vector< double> &fixedCenter )
  : Transform(3, sitkVersor)
{
  Self::InternalInitialization(Self::GetITKBase());

  this->SetCenter(fixedCenter);
  this->SetRotation(versor);
}

VersorTransform::VersorTransform( const std::vector< double > &axis,
                                  double angle,
                                  const std::vector< double> &fixedCenter )
  : Transform(3, sitkVersor)
{
  Self::InternalInitialization(Self::GetITKBase());

  this->SetCenter(fixedCenter);
  this->SetRotation(axis, angle);
}

VersorTransform &VersorTransform::operator=( const VersorTransform &arg )
{
  Superclass::operator=(arg);
  return *this;
}


/** fixed parameter */
VersorTransform::Self &VersorTransform::SetCenter(const std::vector<double> &params)
{
  this->MakeUnique();
  this->m_pfSetCenter(params);
  return *this;
}

std::vector<double> VersorTransform::GetCenter( ) const
{
  return this->m_pfGetCenter();
}


VersorTransform::Self &VersorTransform::SetRotation(const std::vector<double> &versor)
{
  this->MakeUnique();
  this->m_pfSetRotation1(versor);
  return *this;
}

VersorTransform::Self &VersorTransform::SetRotation(const std::vector<double> &axis,  double angle)
{
  this->MakeUnique();
  this->m_pfSetRotation2(axis, angle);
  return *this;
}

std::vector<double>  VersorTransform::GetVersor() const
{
  return this->m_pfGetVersor();
}

std::vector<double> VersorTransform::GetMatrix( ) const
{
  return this->m_pfGetMatrix();
}

VersorTransform::Self &VersorTransform::SetMatrix(const std::vector<double> &params, double tolerance)
{
  this->MakeUnique();
  this->m_pfSetMatrix(params,tolerance);
  return *this;
}

void VersorTransform::SetPimpleTransform( PimpleTransformBase *pimpleTransform )
{
  Superclass::SetPimpleTransform(pimpleTransform);
  Self::InternalInitialization(this->GetITKBase());
}

void VersorTransform::InternalInitialization(itk::TransformBase *transform)
{

  using TransformType = itk::VersorTransform<double>;
  TransformType *t = dynamic_cast<TransformType*>(transform);

  // explicitly remove all function pointer with reference to prior transform
  this->m_pfSetCenter = nullptr;
  this->m_pfGetCenter = nullptr;
  this->m_pfSetRotation1 = nullptr;
  this->m_pfSetRotation2 = nullptr;
  this->m_pfGetVersor = nullptr;
  this->m_pfGetMatrix = nullptr;
  this->m_pfSetMatrix = nullptr;

  if (t && (typeid(*t) == typeid(TransformType)))
    {
    this->InternalInitialization(t);
    return;
    }
  else
    {
    sitkExceptionMacro("Transform is not of type " << this->GetName() << "!" );
    }
}


template<class TransformType>
void VersorTransform::InternalInitialization(TransformType *t)
{
  SITK_TRANSFORM_SET_MPF(Center, typename TransformType::InputPointType, double);
  SITK_TRANSFORM_SET_MPF_GetMatrix();
  SITK_TRANSFORM_SET_MPF_SetMatrix();

  this->m_pfSetRotation1 = [t](const std::vector<double> &v) {
    t->SetRotation(sitkSTLVectorToITKVersor<double>(v));
  };

  this->m_pfSetRotation2 = [t](const std::vector<double> &v, double d) {
    t->SetRotation(sitkSTLVectorToITK<typename TransformType::AxisType>(v),d);
  };

  this->m_pfGetVersor = [t] () {
    return sitkITKVersorToSTL<double>(t->GetVersor());
  };
}

}
}
