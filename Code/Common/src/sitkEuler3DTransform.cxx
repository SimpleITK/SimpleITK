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
#include "sitkEuler3DTransform.h"
#include "sitkTransformHelper.hxx"

#include "itkEuler3DTransform.h"

namespace itk
{
namespace simple
{

// construct identity
Euler3DTransform::Euler3DTransform()
  : Transform(3,sitkEuler)
{
  Self::InternalInitialization(Self::GetITKBase());
}

Euler3DTransform::Euler3DTransform(const std::vector<double> &fixedCenter,
                                   double angleX, double angleY, double angleZ,
                                   const std::vector<double> &translation)
  : Transform(3,sitkEuler)

{
  Self::InternalInitialization(Self::GetITKBase());

  this->SetCenter(fixedCenter);
  this->SetRotation(angleX, angleY, angleZ);
  this->SetTranslation(translation);
}

Euler3DTransform::Euler3DTransform( const Euler3DTransform &arg )
  : Transform(arg)
{
  Self::InternalInitialization(Self::GetITKBase());
}

Euler3DTransform::Euler3DTransform( const Transform &arg )
  : Transform(arg)
{
  Self::InternalInitialization(Self::GetITKBase());
}


Euler3DTransform &Euler3DTransform::operator=( const Euler3DTransform &arg )
{
  Superclass::operator=(arg);
  return *this;
}


/** fixed parameter */
Euler3DTransform::Self &Euler3DTransform::SetCenter(const std::vector<double> &params)
{
  this->MakeUnique();
  this->m_pfSetCenter(params);
  return *this;
}

std::vector<double> Euler3DTransform::GetCenter( ) const
{
  return this->m_pfGetCenter();
}

double Euler3DTransform::GetAngleX () const
{
  return this->m_pfGetAngleX();
}

double Euler3DTransform::GetAngleY () const
{
  return this->m_pfGetAngleY();
}

double Euler3DTransform::GetAngleZ () const
{
  return this->m_pfGetAngleZ();
}

/** parameter */
Euler3DTransform::Self &Euler3DTransform::SetRotation (double angleX, double angleY, double angleZ)
{
  this->MakeUnique();
  this->m_pfSetRotation(angleX,angleY,angleZ);
  return *this;
}

Euler3DTransform::Self &Euler3DTransform::SetTranslation(const std::vector<double> &params)
{
  this->MakeUnique();
  this->m_pfSetTranslation(params);
  return *this;
}

std::vector<double> Euler3DTransform::GetTranslation( ) const
{
  return this->m_pfGetTranslation();
}


Euler3DTransform::Self &Euler3DTransform::SetComputeZYX (bool _arg)
{
  this->MakeUnique();
  this->m_pfSetComputeZYX(_arg);
  return *this;
}

bool Euler3DTransform::GetComputeZYX () const
{
  return this->m_pfGetComputeZYX();
}

std::vector<double> Euler3DTransform::GetMatrix( ) const
{
  return this->m_pfGetMatrix();
}

Euler3DTransform::Self &Euler3DTransform::SetMatrix(const std::vector<double> &params, double tolerance)
{
  this->MakeUnique();
  this->m_pfSetMatrix(params,tolerance);
  return *this;
}

void Euler3DTransform::SetPimpleTransform( PimpleTransformBase *pimpleTransform )
{
  Superclass::SetPimpleTransform(pimpleTransform);
  Self::InternalInitialization(this->GetITKBase());
}

void Euler3DTransform::InternalInitialization(itk::TransformBase *transform)
{

  typedef itk::Euler3DTransform<double> TransformType;
  TransformType *t = dynamic_cast<TransformType*>(transform);

  // explicitly remove all function pointer with reference to prior transform
  this->m_pfSetCenter = SITK_NULLPTR;
  this->m_pfGetCenter = SITK_NULLPTR;
  this->m_pfSetTranslation = SITK_NULLPTR;
  this->m_pfGetTranslation = SITK_NULLPTR;
  this->m_pfSetRotation = SITK_NULLPTR;
  this->m_pfGetAngleX = SITK_NULLPTR;
  this->m_pfGetAngleY = SITK_NULLPTR;
  this->m_pfGetAngleZ = SITK_NULLPTR;
  this->m_pfSetComputeZYX = SITK_NULLPTR;
  this->m_pfGetComputeZYX = SITK_NULLPTR;
  this->m_pfGetMatrix = SITK_NULLPTR;
  this->m_pfSetMatrix = SITK_NULLPTR;

  if (t && (typeid(*t)==typeid(TransformType)))
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
void Euler3DTransform::InternalInitialization(TransformType *t)
{
  SITK_TRANSFORM_SET_MPF(Center, typename TransformType::InputPointType, double);
  SITK_TRANSFORM_SET_MPF(Translation, typename TransformType::OutputVectorType, double);
  SITK_TRANSFORM_SET_MPF_GetMatrix();
  SITK_TRANSFORM_SET_MPF_SetMatrix();

  this->m_pfSetRotation = nsstd::bind(&TransformType::SetRotation,t,nsstd::placeholders::_1,nsstd::placeholders::_2,nsstd::placeholders::_3);
  this->m_pfGetAngleX = nsstd::bind(&TransformType::GetAngleX,t);
  this->m_pfGetAngleY = nsstd::bind(&TransformType::GetAngleY,t);
  this->m_pfGetAngleZ = nsstd::bind(&TransformType::GetAngleZ,t);
  this->m_pfSetComputeZYX = nsstd::bind(&TransformType::SetComputeZYX,t,nsstd::placeholders::_1);
  this->m_pfGetComputeZYX = nsstd::bind(&TransformType::GetComputeZYX,t);

}

}
}
