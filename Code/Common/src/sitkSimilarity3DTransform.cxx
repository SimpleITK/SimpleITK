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
#include "sitkSimilarity3DTransform.h"
#include "sitkTransformHelper.hxx"

#include "itkSimilarity3DTransform.h"

namespace itk
{
namespace simple
{

namespace
{

template< typename T, typename TType>
itk::Versor<T> sitkSTLVectorToITKVersor( const std::vector< TType > & in )
{
  typedef itk::Versor<T> itkVectorType;
  if ( in.size() != 4 )
    {
    sitkExceptionMacro(<<"Unable to convert vector to ITK Versor type\n"
                      << "Expected vector of length " <<  4
                       << " but got " << in.size() << " elements." );
    }
  itkVectorType out;
  out.Set(in[0],in[1],in[2],in[3]);
  return out;
}


template< typename TType, typename T>
std::vector<TType> sitkITKVersorToSTL( const itk::Versor<T> & in )
{
  std::vector<TType> out(4);
  out[0] = in.GetX();
  out[1] = in.GetY();
  out[2] = in.GetZ();
  out[3] = in.GetW();
  return out;
}


}

// construct identity
Similarity3DTransform::Similarity3DTransform()
  : Transform(3, sitkSimilarity)
{
  Self::InternalInitialization(Self::GetITKBase());
}

Similarity3DTransform::Similarity3DTransform( const Similarity3DTransform &arg )
  : Transform(arg)
{
  Self::InternalInitialization(Self::GetITKBase());
}


Similarity3DTransform::Similarity3DTransform( const Transform &arg )
  : Transform(arg)
{
  Self::InternalInitialization(Self::GetITKBase());
}

Similarity3DTransform::Similarity3DTransform( double scaleFactor, const std::vector< double > &versor,
                                              const std::vector< double > &translation,
                                              const std::vector< double > &fixedCenter )
  : Transform(3, sitkSimilarity)
{
  Self::InternalInitialization(Self::GetITKBase());

  this->SetScale(scaleFactor);
  this->SetCenter(fixedCenter);
  this->SetRotation(versor);
  this->SetTranslation(translation);
}

Similarity3DTransform::Similarity3DTransform( double scaleFactor, const std::vector< double > &axis,
                                              double angle,
                                              const std::vector< double > &translation,
                                              const std::vector< double > &fixedCenter )
  : Transform(3, sitkSimilarity)
{
  Self::InternalInitialization(Self::GetITKBase());

  this->SetScale(scaleFactor);
  this->SetCenter(fixedCenter);
  this->SetRotation(axis, angle);
  this->SetTranslation(translation);
}

Similarity3DTransform &Similarity3DTransform::operator=( const Similarity3DTransform &arg )
{
  Superclass::operator=(arg);
  return *this;
}


/** fixed parameter */
Similarity3DTransform::Self &Similarity3DTransform::SetCenter(const std::vector<double> &params)
{
  this->MakeUnique();
  this->m_pfSetCenter(params);
  return *this;
}

std::vector<double> Similarity3DTransform::GetCenter( ) const
{
  return this->m_pfGetCenter();
}


Similarity3DTransform::Self &Similarity3DTransform::SetRotation(const std::vector<double> &versor)
{
  this->MakeUnique();
  this->m_pfSetRotation1(versor);
  return *this;
}

Similarity3DTransform::Self &Similarity3DTransform::SetRotation(const std::vector<double> &axis,  double angle)
{
  this->MakeUnique();
  this->m_pfSetRotation2(axis, angle);
  return *this;
}

std::vector<double>  Similarity3DTransform::GetVersor() const
{
  return this->m_pfGetVersor();
}

Similarity3DTransform::Self &Similarity3DTransform::SetTranslation(const std::vector<double> &params)
{
  this->MakeUnique();
  this->m_pfSetTranslation(params);
  return *this;
}

std::vector<double> Similarity3DTransform::GetTranslation( ) const
{
  return this->m_pfGetTranslation();
}

Similarity3DTransform::Self &Similarity3DTransform::SetScale(double scale)
{
  this->MakeUnique();
  this->m_pfSetScale(scale);
  return *this;
}

double Similarity3DTransform::GetScale() const
{
  return this->m_pfGetScale();
}

Similarity3DTransform::Self &Similarity3DTransform::Translate(const std::vector<double> &offset)
{
  this->MakeUnique();
  this->m_pfTranslate(offset);
  return *this;
}

std::vector<double> Similarity3DTransform::GetMatrix( ) const
{
  return this->m_pfGetMatrix();
}

Similarity3DTransform::Self &Similarity3DTransform::SetMatrix(const std::vector<double> &params, double tolerance)
{
  this->MakeUnique();
  this->m_pfSetMatrix(params,tolerance);
  return *this;
}

void Similarity3DTransform::SetPimpleTransform( PimpleTransformBase *pimpleTransform )
{
  Superclass::SetPimpleTransform(pimpleTransform);
  Self::InternalInitialization(this->GetITKBase());
}

void Similarity3DTransform::InternalInitialization(itk::TransformBase *transform)
{

  typedef itk::Similarity3DTransform<double> TransformType;
  TransformType *t = dynamic_cast<TransformType*>(transform);

  // explicitly remove all function pointer with reference to prior transform
  this->m_pfSetCenter = SITK_NULLPTR;
  this->m_pfGetCenter = SITK_NULLPTR;
  this->m_pfSetTranslation = SITK_NULLPTR;
  this->m_pfGetTranslation = SITK_NULLPTR;
  this->m_pfSetRotation1 = SITK_NULLPTR;
  this->m_pfSetRotation2 = SITK_NULLPTR;
  this->m_pfGetVersor = SITK_NULLPTR;
  this->m_pfSetScale = SITK_NULLPTR;
  this->m_pfGetScale = SITK_NULLPTR;
  this->m_pfTranslate = SITK_NULLPTR;
  this->m_pfGetMatrix = SITK_NULLPTR;
  this->m_pfSetMatrix = SITK_NULLPTR;

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
void Similarity3DTransform::InternalInitialization(TransformType *t)
{
  SITK_TRANSFORM_SET_MPF(Center, typename TransformType::InputPointType, double);
  SITK_TRANSFORM_SET_MPF(Translation, typename TransformType::OutputVectorType, double);
  SITK_TRANSFORM_SET_MPF_GetMatrix();
  SITK_TRANSFORM_SET_MPF_SetMatrix();

  void  (TransformType::*pfSetRotation1) (const typename TransformType::VersorType &) = &TransformType::SetRotation;
  this->m_pfSetRotation1 = nsstd::bind(pfSetRotation1,t,nsstd::bind(&sitkSTLVectorToITKVersor<double, double>,nsstd::placeholders::_1));

  typename TransformType::OutputVectorType (*pfSTLVectorToITK)(const std::vector<double> &) = &sitkSTLVectorToITK<typename TransformType::OutputVectorType, double>;
  void  (TransformType::*pfSetRotation2) (const typename TransformType::AxisType &, double) = &TransformType::SetRotation;
  this->m_pfSetRotation2 = nsstd::bind(pfSetRotation2,t,nsstd::bind(pfSTLVectorToITK,nsstd::placeholders::_1),nsstd::placeholders::_2);

  this->m_pfGetVersor  = nsstd::bind(&sitkITKVersorToSTL<double, double>,nsstd::bind(&TransformType::GetVersor,t));

  this->m_pfSetScale = nsstd::bind(&TransformType::SetScale,t,nsstd::placeholders::_1);
  this->m_pfGetScale = nsstd::bind(&TransformType::GetScale,t);

  // pre argument has no effect
  this->m_pfTranslate = nsstd::bind(&TransformType::Translate,t,nsstd::bind(pfSTLVectorToITK,nsstd::placeholders::_1), false);

}

}
}
