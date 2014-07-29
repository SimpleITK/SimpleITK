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
#include "sitkSimilarity2DTransform.h"

#include "itkSimilarity2DTransform.h"

namespace itk
{
namespace simple
{

// construct identity
Similarity2DTransform::Similarity2DTransform()
  : Transform(2,sitkSimilarity)
{
  Self::InternalInitialization(Self::GetITKBase());
}

Similarity2DTransform::Similarity2DTransform(const std::vector<double> &fixedCenter,
                                   double angle,
                                   const std::vector<double> &translation)
  : Transform(2,sitkSimilarity)

{
  Self::InternalInitialization(Self::GetITKBase());

  this->SetCenter(fixedCenter);
  this->SetAngle(angle);
  this->SetTranslation(translation);
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
  this->MakeUniqueForWrite();
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
  this->MakeUniqueForWrite();
  this->m_pfSetAngle(angle);
  return *this;
}

Similarity2DTransform::Self &Similarity2DTransform::SetTranslation(const std::vector<double> &params)
{
  this->MakeUniqueForWrite();
  this->m_pfSetTranslation(params);
  return *this;
}

std::vector<double> Similarity2DTransform::GetTranslation( ) const
{
  return this->m_pfGetTranslation();
}

Similarity2DTransform::Self &Similarity2DTransform::SetScale(double scale)
{
  this->MakeUniqueForWrite();
  this->m_pfSetScale(scale);
  return *this;
}

double Similarity2DTransform::GetScale() const
{
  return this->m_pfGetScale();
}

void Similarity2DTransform::SetPimpleTransform( PimpleTransformBase *pimpleTransform )
{
  Superclass::SetPimpleTransform(pimpleTransform);
  Self::InternalInitialization(this->GetITKBase());
}

void Similarity2DTransform::InternalInitialization(itk::TransformBase *transform)
{

  typedef itk::Similarity2DTransform<double> TransformType;
  TransformType *t = dynamic_cast<TransformType*>(transform);

  // explicitly remove all function pointer with reference to prior transform
  this->m_pfSetCenter = SITK_NULLPTR;
  this->m_pfGetCenter = SITK_NULLPTR;
  this->m_pfSetTranslation = SITK_NULLPTR;
  this->m_pfGetTranslation = SITK_NULLPTR;
  this->m_pfSetAngle = SITK_NULLPTR;
  this->m_pfGetAngle = SITK_NULLPTR;
  this->m_pfSetScale = SITK_NULLPTR;
  this->m_pfGetScale = SITK_NULLPTR;

  if (t)
    {
    this->InternalInitialization(t);
    return;
    }


}


template<class TransformType>
void Similarity2DTransform::InternalInitialization(TransformType *t)
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

  this->m_pfSetScale = nsstd::bind(&TransformType::SetScale,t,nsstd::placeholders::_1);
  this->m_pfGetScale = nsstd::bind(&TransformType::GetScale,t);
}

}
}
