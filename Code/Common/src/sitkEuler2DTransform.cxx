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
#include "sitkEuler2DTransform.h"
#include "sitkTransformHelper.hxx"

#include "itkEuler2DTransform.h"

namespace itk
{
namespace simple
{

Euler2DTransform::~Euler2DTransform() = default;

// construct identity
Euler2DTransform::Euler2DTransform()
  : Transform(2,sitkEuler)
{
  Self::InternalInitialization(Self::GetITKBase());
}

Euler2DTransform::Euler2DTransform(const std::vector<double> &fixedCenter,
                                   double angle,
                                   const std::vector<double> &translation)
  : Transform(2,sitkEuler)

{
  Self::InternalInitialization(Self::GetITKBase());

  this->SetCenter(fixedCenter);
  this->SetAngle(angle);
  this->SetTranslation(translation);
}


Euler2DTransform::Euler2DTransform( const Euler2DTransform &arg )
  : Transform(arg)
{
  Self::InternalInitialization(Self::GetITKBase());
}


Euler2DTransform::Euler2DTransform( const Transform &arg )
  : Transform(arg)
{
  Self::InternalInitialization(Self::GetITKBase());
}


Euler2DTransform &Euler2DTransform::operator=( const Euler2DTransform &arg )
{
  Superclass::operator=(arg);
  return *this;
}


/** fixed parameter */
Euler2DTransform::Self &Euler2DTransform::SetCenter(const std::vector<double> &params)
{
  this->MakeUnique();
  this->m_pfSetCenter(params);
  return *this;
}

std::vector<double> Euler2DTransform::GetCenter( ) const
{
  return this->m_pfGetCenter();
}

double Euler2DTransform::GetAngle() const
{
  return this->m_pfGetAngle();
}

/** parameter */
Euler2DTransform::Self &Euler2DTransform::SetAngle(double angle)
{
  this->MakeUnique();
  this->m_pfSetAngle(angle);
  return *this;
}

Euler2DTransform::Self &Euler2DTransform::SetTranslation(const std::vector<double> &params)
{
  this->MakeUnique();
  this->m_pfSetTranslation(params);
  return *this;
}

std::vector<double> Euler2DTransform::GetTranslation( ) const
{
  return this->m_pfGetTranslation();
}

std::vector<double> Euler2DTransform::GetMatrix( ) const
{
  return this->m_pfGetMatrix();
}

Euler2DTransform::Self &Euler2DTransform::SetMatrix(const std::vector<double> &params, double tolerance)
{
  this->MakeUnique();
  this->m_pfSetMatrix(params,tolerance);
  return *this;
}

void Euler2DTransform::SetPimpleTransform( PimpleTransformBase *pimpleTransform )
{
  Superclass::SetPimpleTransform(pimpleTransform);
  Self::InternalInitialization(this->GetITKBase());
}

void Euler2DTransform::InternalInitialization(itk::TransformBase *transform)
{

  using TransformType = itk::Euler2DTransform<double>;
  TransformType *t = dynamic_cast<TransformType*>(transform);

  this->m_pfSetCenter = nullptr;
  this->m_pfGetCenter = nullptr;
  this->m_pfSetTranslation = nullptr;
  this->m_pfGetTranslation = nullptr;
  this->m_pfSetAngle = nullptr;
  this->m_pfGetAngle = nullptr;
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
void Euler2DTransform::InternalInitialization(TransformType *t)
{
  SITK_TRANSFORM_SET_MPF(Center, typename TransformType::InputPointType, double);
  SITK_TRANSFORM_SET_MPF(Translation, typename TransformType::OutputVectorType, double);
  SITK_TRANSFORM_SET_MPF_GetMatrix();
  SITK_TRANSFORM_SET_MPF_SetMatrix();

  this->m_pfSetAngle = std::bind(&TransformType::SetAngle,t,std::placeholders::_1);
  this->m_pfGetAngle = std::bind(&TransformType::GetAngle,t);
}

}
}
