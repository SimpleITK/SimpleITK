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
#include "sitkVersorTransform.h"
#include "sitkTransformHelper.hxx"

#include "itkVersorTransform.h"

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

  typedef itk::VersorTransform<double> TransformType;
  TransformType *t = dynamic_cast<TransformType*>(transform);

  // explicitly remove all function pointer with reference to prior transform
  this->m_pfSetCenter = SITK_NULLPTR;
  this->m_pfGetCenter = SITK_NULLPTR;
  this->m_pfSetRotation1 = SITK_NULLPTR;
  this->m_pfSetRotation2 = SITK_NULLPTR;
  this->m_pfGetVersor = SITK_NULLPTR;
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
void VersorTransform::InternalInitialization(TransformType *t)
{
  SITK_TRANSFORM_SET_MPF(Center, typename TransformType::InputPointType, double);
  SITK_TRANSFORM_SET_MPF_GetMatrix();
  SITK_TRANSFORM_SET_MPF_SetMatrix();

  typename TransformType::OutputVectorType (*pfSTLVectorToITK)(const std::vector<double> &) = &sitkSTLVectorToITK<typename TransformType::OutputVectorType, double>;

  void 	(TransformType::*pfSetRotation1) (const typename TransformType::VersorType &) = &TransformType::SetRotation;
  this->m_pfSetRotation1 = nsstd::bind(pfSetRotation1,t,nsstd::bind(&sitkSTLVectorToITKVersor<double, double>,nsstd::placeholders::_1));

  void 	(TransformType::*pfSetRotation2) (const typename TransformType::AxisType &, double) = &TransformType::SetRotation;
  this->m_pfSetRotation2 = nsstd::bind(pfSetRotation2,t,nsstd::bind(pfSTLVectorToITK,nsstd::placeholders::_1),nsstd::placeholders::_2);

  this->m_pfGetVersor  = nsstd::bind(&sitkITKVersorToSTL<double, double>,nsstd::bind(&TransformType::GetVersor,t));

}

}
}
