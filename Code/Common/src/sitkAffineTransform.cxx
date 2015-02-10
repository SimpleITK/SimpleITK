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
#include "sitkAffineTransform.h"
#include "sitkTransformHelper.hxx"

#include "itkAffineTransform.h"

namespace itk
{
namespace simple
{

// construct identity
AffineTransform::AffineTransform(unsigned int dimensions)
  : Transform(dimensions, sitkAffine)
{
  Self::InternalInitialization(Self::GetITKBase());
}

AffineTransform::AffineTransform( const AffineTransform &arg )
  : Transform(arg)
{
  Self::InternalInitialization(Self::GetITKBase());
}

AffineTransform::AffineTransform( const Transform &arg )
  : Transform(arg)
{
  Self::InternalInitialization(Self::GetITKBase());
}

AffineTransform::AffineTransform( const std::vector< double> &matrix,
                                  const std::vector< double> &translation,
                                  const std::vector< double> &fixedCenter )
  : Transform(translation.size(), sitkAffine)
{
  Self::InternalInitialization(Self::GetITKBase());

  this->SetMatrix(matrix);
  this->SetTranslation(translation);
  this->SetCenter(fixedCenter);
}

AffineTransform &AffineTransform::operator=( const AffineTransform &arg )
{
  Superclass::operator=(arg);
  return *this;
}

/** parameter */
AffineTransform::Self &AffineTransform::SetTranslation(const std::vector<double> &params)
{
  this->MakeUnique();
  this->m_pfSetTranslation(params);
  return *this;
}

std::vector<double> AffineTransform::GetTranslation( ) const
{
  return this->m_pfGetTranslation();
}


AffineTransform::Self &AffineTransform::SetMatrix(const std::vector<double> &params)
{
  this->MakeUnique();
  this->m_pfSetMatrix(params);
  return *this;
}

std::vector<double> AffineTransform::GetMatrix( ) const
{
  return this->m_pfGetMatrix();
}


/** fixed parameter */
AffineTransform::Self &AffineTransform::SetCenter(const std::vector<double> &params)
{
  this->MakeUnique();
  this->m_pfSetCenter(params);
  return *this;
}

std::vector<double> AffineTransform::GetCenter( ) const
{
  return this->m_pfGetCenter();
}

AffineTransform::Self &AffineTransform::Scale(const std::vector<double> &factor, bool pre)
{
  this->MakeUnique();
  this->m_pfScale1(factor, pre);
  return *this;
}

AffineTransform::Self &AffineTransform::Scale(double factor, bool pre)
{
  this->MakeUnique();
  this->m_pfScale2(factor, pre);
  return *this;
}

AffineTransform::Self &AffineTransform::Shear(int axis1, int axis2, double coef, bool pre)
{
  this->MakeUnique();
  this->m_pfShear(axis1, axis2, coef, pre);
  return *this;
}

AffineTransform::Self &AffineTransform::Translate(const std::vector<double> &offset, bool pre)
{
  this->MakeUnique();
  this->m_pfTranslate(offset, pre);
  return *this;
}

AffineTransform::Self &AffineTransform::Rotate(int axis1, int axis2, double angle, bool pre)
{
  this->MakeUnique();
  this->m_pfRotate(axis1, axis2, angle, pre);
  return *this;
}

void AffineTransform::SetPimpleTransform( PimpleTransformBase *pimpleTransform )
{
  Superclass::SetPimpleTransform(pimpleTransform);
  Self::InternalInitialization(this->GetITKBase());
}

void AffineTransform::InternalInitialization(itk::TransformBase *transform)
{
  MyVisitor visitor;
  visitor.transform = transform;
  visitor.that = this;

  typedef typelist::MakeTypeList<itk::AffineTransform<double, 3>,
                                 itk::AffineTransform<double, 2> >::Type TransformTypeList;

  typelist::Visit<TransformTypeList> callInternalInitialization;

  // explicitly remove all function pointer with reference to prior transform
  this->m_pfSetCenter = SITK_NULLPTR;
  this->m_pfGetCenter = SITK_NULLPTR;
  this->m_pfSetTranslation = SITK_NULLPTR;
  this->m_pfGetTranslation = SITK_NULLPTR;
  this->m_pfSetMatrix = SITK_NULLPTR;
  this->m_pfGetMatrix = SITK_NULLPTR;
  this->m_pfScale1 = SITK_NULLPTR;
  this->m_pfScale2 = SITK_NULLPTR;
  this->m_pfShear = SITK_NULLPTR;
  this->m_pfTranslate = SITK_NULLPTR;
  this->m_pfRotate = SITK_NULLPTR;

  callInternalInitialization(visitor);

  if ( this->m_pfSetCenter == SITK_NULLPTR )
    {
    sitkExceptionMacro("Transform is not of type " << this->GetName() << "!" );
    }
}


template<class TransformType>
void AffineTransform::InternalInitialization(TransformType *t)
{
  SITK_TRANSFORM_SET_MPF(Center, typename TransformType::InputPointType, double);
  SITK_TRANSFORM_SET_MPF(Translation, typename TransformType::OutputVectorType, double);

  typename TransformType::MatrixType (*pfSTLToITKDirection)(const std::vector<double> &) = &sitkSTLToITKDirection<typename TransformType::MatrixType>;
  this->m_pfSetMatrix = nsstd::bind(&TransformType::SetMatrix, t, nsstd::bind(pfSTLToITKDirection, nsstd::placeholders::_1));

  SITK_TRANSFORM_SET_MPF_GetMatrix();

  typename TransformType::OutputVectorType (*pfSTLVectorToITK)(const std::vector<double> &) = &sitkSTLVectorToITK<typename TransformType::OutputVectorType, double>;
  void 	(TransformType::*pfScale1) (const typename TransformType::OutputVectorType &, bool) = &TransformType::Scale;
  this->m_pfScale1 = nsstd::bind(pfScale1,t,nsstd::bind(pfSTLVectorToITK,nsstd::placeholders::_1),nsstd::placeholders::_2);

  void 	(TransformType::*pfScale2) (const double &, bool) = &TransformType::Scale;
  this->m_pfScale2 = nsstd::bind(pfScale2,t,nsstd::placeholders::_1,nsstd::placeholders::_2);
  this->m_pfShear = nsstd::bind(&TransformType::Shear,t,nsstd::placeholders::_1,nsstd::placeholders::_2,nsstd::placeholders::_3,nsstd::placeholders::_4);
  this->m_pfTranslate = nsstd::bind(&TransformType::Translate,t,nsstd::bind(pfSTLVectorToITK,nsstd::placeholders::_1),nsstd::placeholders::_2);
  this->m_pfRotate = nsstd::bind(&TransformType::Rotate,t,nsstd::placeholders::_1,nsstd::placeholders::_2,nsstd::placeholders::_3,nsstd::placeholders::_4);
}

}
}
