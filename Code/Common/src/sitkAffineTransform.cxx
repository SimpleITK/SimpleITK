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
#include "sitkAffineTransform.h"
#include "sitkTransformHelper.hxx"

#include "itkAffineTransform.h"

namespace itk
{
namespace simple
{

AffineTransform::~AffineTransform() = default;

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
  this->m_pfSetCenter = nullptr;
  this->m_pfGetCenter = nullptr;
  this->m_pfSetTranslation = nullptr;
  this->m_pfGetTranslation = nullptr;
  this->m_pfSetMatrix = nullptr;
  this->m_pfGetMatrix = nullptr;
  this->m_pfScale1 = nullptr;
  this->m_pfScale2 = nullptr;
  this->m_pfShear = nullptr;
  this->m_pfTranslate = nullptr;
  this->m_pfRotate = nullptr;

  callInternalInitialization(visitor);

  if ( this->m_pfSetCenter == nullptr )
    {
    sitkExceptionMacro("Transform is not of type " << this->GetName() << "!" );
    }
}


template<class TransformType>
void AffineTransform::InternalInitialization(TransformType *t)
{
  SITK_TRANSFORM_SET_MPF(Center, typename TransformType::InputPointType, double);
  SITK_TRANSFORM_SET_MPF(Translation, typename TransformType::OutputVectorType, double);

  this->m_pfSetMatrix = [t](const std::vector<double> &arg)
    {
      t->SetMatrix(sitkSTLToITKDirection<typename TransformType::MatrixType>(arg));
    };


  SITK_TRANSFORM_SET_MPF_GetMatrix();

  this->m_pfScale1 = [t](const std::vector<double> v, bool b)
    {
      t->Scale(sitkSTLVectorToITK<typename TransformType::OutputVectorType>(v), b);
    };

  this->m_pfScale2 = [t](double v, bool b) { t->Scale(v, b); };

  this->m_pfShear = std::bind(&TransformType::Shear,t,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
  this->m_pfTranslate = [t] (const std::vector<double> &v, bool b) {
    t->Translate(sitkSTLVectorToITK<typename TransformType::OutputVectorType>(v),b);
  };
  this->m_pfRotate = std::bind(&TransformType::Rotate,t,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
}

}
}
