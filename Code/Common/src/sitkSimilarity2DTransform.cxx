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
#include "sitkSimilarity2DTransform.h"
#include "sitkTransformHelper.hxx"

#include "itkSimilarity2DTransform.h"

namespace itk
{
namespace simple
{

Similarity2DTransform::~Similarity2DTransform() = default;

// construct identity
Similarity2DTransform::Similarity2DTransform()
  : Transform(2,sitkSimilarity)
{
  Self::InternalInitialization(Self::GetITKBase());
}

Similarity2DTransform::Similarity2DTransform( double scaleFactor,
                                              double angle,
                                              const std::vector<double> &translation,
                                              const std::vector<double> &fixedCenter )
  : Transform(2,sitkSimilarity)

{
  Self::InternalInitialization(Self::GetITKBase());

  this->SetCenter(fixedCenter);
  this->SetAngle(angle);
  this->SetTranslation(translation);
  this->SetScale(scaleFactor);
}

Similarity2DTransform::Similarity2DTransform( const Transform &arg )
  : Transform(arg)
{
  Self::InternalInitialization(Self::GetITKBase());
}


Similarity2DTransform::Similarity2DTransform( const Similarity2DTransform &arg )
  : Transform(arg)
{
  Self::InternalInitialization(Self::GetITKBase());
}


Similarity2DTransform &Similarity2DTransform::operator=( const Similarity2DTransform &arg )
{
  Superclass::operator=(arg);
  return *this;
}


/** fixed parameter */
Similarity2DTransform::Self &Similarity2DTransform::SetCenter(const std::vector<double> &params)
{
  this->MakeUnique();
  this->m_pfSetCenter(params);
  return *this;
}

std::vector<double> Similarity2DTransform::GetCenter( ) const
{
  return this->m_pfGetCenter();
}

double Similarity2DTransform::GetAngle() const
{
  return this->m_pfGetAngle();
}

/** parameter */
Similarity2DTransform::Self &Similarity2DTransform::SetAngle(double angle)
{
  this->MakeUnique();
  this->m_pfSetAngle(angle);
  return *this;
}

Similarity2DTransform::Self &Similarity2DTransform::SetTranslation(const std::vector<double> &params)
{
  this->MakeUnique();
  this->m_pfSetTranslation(params);
  return *this;
}

std::vector<double> Similarity2DTransform::GetTranslation( ) const
{
  return this->m_pfGetTranslation();
}

Similarity2DTransform::Self &Similarity2DTransform::SetScale(double scale)
{
  this->MakeUnique();
  this->m_pfSetScale(scale);
  return *this;
}

double Similarity2DTransform::GetScale() const
{
  return this->m_pfGetScale();
}

std::vector<double> Similarity2DTransform::GetMatrix( ) const
{
  return this->m_pfGetMatrix();
}

Similarity2DTransform::Self &Similarity2DTransform::SetMatrix(const std::vector<double> &params, double tolerance)
{
  this->MakeUnique();
  this->m_pfSetMatrix(params,tolerance);
  return *this;
}

void Similarity2DTransform::SetPimpleTransform( PimpleTransformBase *pimpleTransform )
{
  Superclass::SetPimpleTransform(pimpleTransform);
  Self::InternalInitialization(this->GetITKBase());
}

void Similarity2DTransform::InternalInitialization(itk::TransformBase *transform)
{

  using TransformType = itk::Similarity2DTransform<double>;
  TransformType *t = dynamic_cast<TransformType*>(transform);

  // explicitly remove all function pointer with reference to prior transform
  this->m_pfSetCenter = nullptr;
  this->m_pfGetCenter = nullptr;
  this->m_pfSetTranslation = nullptr;
  this->m_pfGetTranslation = nullptr;
  this->m_pfSetAngle = nullptr;
  this->m_pfGetAngle = nullptr;
  this->m_pfSetScale = nullptr;
  this->m_pfGetScale = nullptr;
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
void Similarity2DTransform::InternalInitialization(TransformType *t)
{
  SITK_TRANSFORM_SET_MPF(Center, typename TransformType::InputPointType, double);
  SITK_TRANSFORM_SET_MPF(Translation, typename TransformType::OutputVectorType, double);
  SITK_TRANSFORM_SET_MPF_GetMatrix();
  SITK_TRANSFORM_SET_MPF_SetMatrix();

  this->m_pfSetAngle = std::bind(&TransformType::SetAngle,t,std::placeholders::_1);
  this->m_pfGetAngle = std::bind(&TransformType::GetAngle,t);

  this->m_pfSetScale = std::bind(&TransformType::SetScale,t,std::placeholders::_1);
  this->m_pfGetScale = std::bind(&TransformType::GetScale,t);
}

}
}
