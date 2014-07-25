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
#include "sitkEuler2DTransform.h"

#include "itkEuler2DTransform.h"

namespace itk
{
namespace simple
{

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


Euler2DTransform &Euler2DTransform::operator=( const Euler2DTransform &arg )
{
  Superclass::operator=(arg);
  return *this;
}


/** fixed parameter */
Euler2DTransform::Self &Euler2DTransform::SetCenter(const std::vector<double> &params)
{
  this->MakeUniqueForWrite();
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
  this->MakeUniqueForWrite();
  this->m_pfSetAngle(angle);
  return *this;
}

Euler2DTransform::Self &Euler2DTransform::SetTranslation(const std::vector<double> &params)
{
  this->MakeUniqueForWrite();
  this->m_pfSetTranslation(params);
  return *this;
}

std::vector<double> Euler2DTransform::GetTranslation( ) const
{
  return this->m_pfGetTranslation();
}

void Euler2DTransform::SetPimpleTransform( PimpleTransformBase *pimpleTransform )
{
  Superclass::SetPimpleTransform(pimpleTransform);
  Self::InternalInitialization(this->GetITKBase());
}

void Euler2DTransform::InternalInitialization(itk::TransformBase *transform)
{

  typedef itk::Euler2DTransform<double> TransformType;
  TransformType *t = dynamic_cast<TransformType*>(transform);

  if (t)
    {
    this->InternalInitialization(t);
    return;
    }

  this->m_pfSetCenter = ITK_NULLPTR;
  this->m_pfGetCenter = ITK_NULLPTR;
  this->m_pfSetTranslation = ITK_NULLPTR;
  this->m_pfGetTranslation = ITK_NULLPTR;
  this->m_pfSetAngle = ITK_NULLPTR;
  this->m_pfGetAngle = ITK_NULLPTR;

}


template<class TransformType>
void Euler2DTransform::InternalInitialization(TransformType *t)
{
  typename TransformType::InputPointType (*pfSTLVectorToITKPoint)(const std::vector<double> &) = &sitkSTLVectorToITK<typename TransformType::InputPointType, double>;
  this->m_pfSetCenter = nsstd::bind(&TransformType::SetCenter,t,nsstd::bind(pfSTLVectorToITKPoint,nsstd::placeholders::_1));

  std::vector<double> (*pfITKPointToSTL)( const typename TransformType::InputPointType &) = &sitkITKVectorToSTL<double,typename TransformType::InputPointType>;
  this->m_pfGetCenter = nsstd::bind(pfITKPointToSTL,nsstd::bind(&TransformType::GetCenter,t));

  typename TransformType::OutputVectorType (*pfSTLVectorToITK)(const std::vector<double> &) = &sitkSTLVectorToITK<typename TransformType::OutputVectorType, double>;
  this->m_pfSetTranslation = nsstd::bind(&TransformType::SetTranslation,t,nsstd::bind(pfSTLVectorToITK,nsstd::placeholders::_1));

  std::vector<double> (*pfITKVectorToSTL)( const typename TransformType::OutputVectorType &) = &sitkITKVectorToSTL<double,typename TransformType::OutputVectorType>;
  this->m_pfGetTranslation = nsstd::bind(pfITKVectorToSTL,nsstd::bind(&TransformType::GetTranslation,t));

  this->m_pfSetAngle = nsstd::bind(&TransformType::SetAngle,t,nsstd::placeholders::_1);
  this->m_pfGetAngle = nsstd::bind(&TransformType::GetAngle,t);
}

}
}
