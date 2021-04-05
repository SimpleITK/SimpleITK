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
#include "sitkComposeScaleSkewVersor3DTransform.h"
#include "sitkTransformHelper.hxx"

#include "itkComposeScaleSkewVersor3DTransform.h"

namespace itk
{
namespace simple
{

ComposeScaleSkewVersor3DTransform::~ComposeScaleSkewVersor3DTransform() = default;

// construct identity
ComposeScaleSkewVersor3DTransform::ComposeScaleSkewVersor3DTransform()
  : Transform(3, sitkComposeScaleSkewVersor)
{
  Self::InternalInitialization(Self::GetITKBase());
}

ComposeScaleSkewVersor3DTransform::ComposeScaleSkewVersor3DTransform( const ComposeScaleSkewVersor3DTransform &arg )
  : Transform(arg)
{
  Self::InternalInitialization(Self::GetITKBase());
}

ComposeScaleSkewVersor3DTransform::ComposeScaleSkewVersor3DTransform( const Transform & arg )
  : Transform(arg)
{
  Self::InternalInitialization(Self::GetITKBase());
}

ComposeScaleSkewVersor3DTransform::ComposeScaleSkewVersor3DTransform( const std::vector< double > &scale,
                                                        const std::vector< double> &skew,
                                                        const std::vector< double > &versor,
                                                        const std::vector< double > &translation,
                                                        const std::vector< double> &fixedCenter )
  : Transform(3, sitkComposeScaleSkewVersor)
{
  Self::InternalInitialization(Self::GetITKBase());

  this->SetScale(scale);
  this->SetSkew(skew);
  this->SetCenter(fixedCenter);
  this->SetRotation(versor);
  this->SetTranslation(translation);
}

ComposeScaleSkewVersor3DTransform::ComposeScaleSkewVersor3DTransform( const std::vector< double > &scale,
                                                        const std::vector< double> &skew,
                                                        const std::vector< double > &axis, double angle,
                                                        const std::vector< double > &translation,
                                                        const std::vector< double> &fixedCenter )
  : Transform(3, sitkComposeScaleSkewVersor)
{
  Self::InternalInitialization(Self::GetITKBase());

  this->SetScale(scale);
  this->SetSkew(skew);
  this->SetCenter(fixedCenter);
  this->SetRotation(axis, angle);
  this->SetTranslation(translation);
}


ComposeScaleSkewVersor3DTransform &ComposeScaleSkewVersor3DTransform::operator=( const ComposeScaleSkewVersor3DTransform &arg )
{
  Superclass::operator=(arg);
  return *this;
}


/** fixed parameter */
ComposeScaleSkewVersor3DTransform::Self &ComposeScaleSkewVersor3DTransform::SetCenter(const std::vector<double> &params)
{
  this->MakeUnique();
  this->m_pfSetCenter(params);
  return *this;
}

std::vector<double> ComposeScaleSkewVersor3DTransform::GetCenter( ) const
{
  return this->m_pfGetCenter();
}


ComposeScaleSkewVersor3DTransform::Self &ComposeScaleSkewVersor3DTransform::SetRotation(const std::vector<double> &versor)
{
  this->MakeUnique();
  this->m_pfSetRotation1(versor);
  return *this;
}

ComposeScaleSkewVersor3DTransform::Self &ComposeScaleSkewVersor3DTransform::SetRotation(const std::vector<double> &axis,  double angle)
{
  this->MakeUnique();
  this->m_pfSetRotation2(axis, angle);
  return *this;
}

std::vector<double>  ComposeScaleSkewVersor3DTransform::GetVersor() const
{
  return this->m_pfGetVersor();
}

ComposeScaleSkewVersor3DTransform::Self &ComposeScaleSkewVersor3DTransform::SetTranslation(const std::vector<double> &params)
{
  this->MakeUnique();
  this->m_pfSetTranslation(params);
  return *this;
}

std::vector<double> ComposeScaleSkewVersor3DTransform::GetTranslation( ) const
{
  return this->m_pfGetTranslation();
}

ComposeScaleSkewVersor3DTransform::Self &ComposeScaleSkewVersor3DTransform::Translate(const std::vector<double> &offset)
{
  this->MakeUnique();
  this->m_pfTranslate(offset);
  return *this;
}

ComposeScaleSkewVersor3DTransform::Self &ComposeScaleSkewVersor3DTransform::SetScale(const std::vector<double> &params)
{
  this->MakeUnique();
  this->m_pfSetScale(params);
  return *this;
}

std::vector<double> ComposeScaleSkewVersor3DTransform::GetScale( ) const
{
  return this->m_pfGetScale();
}

ComposeScaleSkewVersor3DTransform::Self &ComposeScaleSkewVersor3DTransform::SetSkew(const std::vector<double> &params)
{
  this->MakeUnique();
  this->m_pfSetSkew(params);
  return *this;
}

std::vector<double> ComposeScaleSkewVersor3DTransform::GetSkew( ) const
{
  return this->m_pfGetSkew();
}

std::vector<double> ComposeScaleSkewVersor3DTransform::GetMatrix( ) const
{
  return this->m_pfGetMatrix();
}

void ComposeScaleSkewVersor3DTransform::SetPimpleTransform( PimpleTransformBase *pimpleTransform )
{
  Superclass::SetPimpleTransform(pimpleTransform);
  Self::InternalInitialization(this->GetITKBase());
}

void ComposeScaleSkewVersor3DTransform::InternalInitialization(itk::TransformBase *transform)
{

  using TransformType = itk::ComposeScaleSkewVersor3DTransform<double>;
  TransformType *t = dynamic_cast<TransformType*>(transform);

  // explicitly remove all function pointer with reference to prior transform
  this->m_pfSetCenter = nullptr;
  this->m_pfGetCenter = nullptr;
  this->m_pfSetTranslation = nullptr;
  this->m_pfGetTranslation = nullptr;
  this->m_pfSetRotation1 = nullptr;
  this->m_pfSetRotation2 = nullptr;
  this->m_pfGetVersor = nullptr;
  this->m_pfTranslate = nullptr;
  this->m_pfGetMatrix = nullptr;

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
void ComposeScaleSkewVersor3DTransform::InternalInitialization(TransformType *t)
{

  SITK_TRANSFORM_SET_MPF(Center, typename TransformType::InputPointType, double);
  SITK_TRANSFORM_SET_MPF(Translation, typename TransformType::OutputVectorType, double);
  SITK_TRANSFORM_SET_MPF(Scale, typename TransformType::ScaleVectorType, double);
  SITK_TRANSFORM_SET_MPF(Skew, typename TransformType::SkewVectorType, double);
  SITK_TRANSFORM_SET_MPF_GetMatrix();

  this->m_pfSetRotation1 = [t](const std::vector<double> &v) {
    t->SetRotation(sitkSTLVectorToITKVersor<double>(v));
  };

  this->m_pfSetRotation2 = [t](const std::vector<double> &v, double d) {
    t->SetRotation(sitkSTLVectorToITK<typename TransformType::AxisType>(v),d);
  };

  this->m_pfGetVersor = [t] () {
    return sitkITKVersorToSTL<double>(t->GetVersor());
  };

  // pre argument has no effect
  this->m_pfTranslate = [t] (const std::vector<double> &v) {
    t->Translate( sitkSTLVectorToITK<typename TransformType::OutputVectorType>(v), false );
  };
}

}
}
