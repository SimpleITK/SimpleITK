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
#include "sitkScaleSkewVersor3DTransform.h"
#include "sitkTransformHelper.hxx"

#include "itkScaleSkewVersor3DTransform.h"

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
ScaleSkewVersor3DTransform::ScaleSkewVersor3DTransform()
  : Transform(3, sitkScaleSkewVersor)
{
  Self::InternalInitialization(Self::GetITKBase());
}

ScaleSkewVersor3DTransform::ScaleSkewVersor3DTransform( const ScaleSkewVersor3DTransform &arg )
  : Transform(arg)
{
  Self::InternalInitialization(Self::GetITKBase());
}

ScaleSkewVersor3DTransform::ScaleSkewVersor3DTransform( const Transform & arg )
  : Transform(arg)
{
  Self::InternalInitialization(Self::GetITKBase());
}

ScaleSkewVersor3DTransform &ScaleSkewVersor3DTransform::operator=( const ScaleSkewVersor3DTransform &arg )
{
  Superclass::operator=(arg);
  return *this;
}


/** fixed parameter */
ScaleSkewVersor3DTransform::Self &ScaleSkewVersor3DTransform::SetCenter(const std::vector<double> &params)
{
  this->MakeUniqueForWrite();
  this->m_pfSetCenter(params);
  return *this;
}

std::vector<double> ScaleSkewVersor3DTransform::GetCenter( ) const
{
  return this->m_pfGetCenter();
}


ScaleSkewVersor3DTransform::Self &ScaleSkewVersor3DTransform::SetRotation(const std::vector<double> &versor)
{
  this->MakeUniqueForWrite();
  this->m_pfSetRotation1(versor);
  return *this;
}

ScaleSkewVersor3DTransform::Self &ScaleSkewVersor3DTransform::SetRotation(const std::vector<double> &axis,  double angle)
{
  this->MakeUniqueForWrite();
  this->m_pfSetRotation2(axis, angle);
  return *this;
}

std::vector<double>  ScaleSkewVersor3DTransform::GetVersor() const
{
  return this->m_pfGetVersor();
}

ScaleSkewVersor3DTransform::Self &ScaleSkewVersor3DTransform::SetTranslation(const std::vector<double> &params)
{
  this->MakeUniqueForWrite();
  this->m_pfSetTranslation(params);
  return *this;
}

std::vector<double> ScaleSkewVersor3DTransform::GetTranslation( ) const
{
  return this->m_pfGetTranslation();
}

ScaleSkewVersor3DTransform::Self &ScaleSkewVersor3DTransform::Translate(const std::vector<double> &offset)
{
  this->MakeUniqueForWrite();
  this->m_pfTranslate(offset);
  return *this;
}

ScaleSkewVersor3DTransform::Self &ScaleSkewVersor3DTransform::SetScale(const std::vector<double> &params)
{
  this->MakeUniqueForWrite();
  this->m_pfSetScale(params);
  return *this;
}

std::vector<double> ScaleSkewVersor3DTransform::GetScale( ) const
{
  return this->m_pfGetScale();
}

ScaleSkewVersor3DTransform::Self &ScaleSkewVersor3DTransform::SetSkew(const std::vector<double> &params)
{
  this->MakeUniqueForWrite();
  this->m_pfSetSkew(params);
  return *this;
}

std::vector<double> ScaleSkewVersor3DTransform::GetSkew( ) const
{
  return this->m_pfGetSkew();
}

void ScaleSkewVersor3DTransform::SetPimpleTransform( PimpleTransformBase *pimpleTransform )
{
  Superclass::SetPimpleTransform(pimpleTransform);
  Self::InternalInitialization(this->GetITKBase());
}

void ScaleSkewVersor3DTransform::InternalInitialization(itk::TransformBase *transform)
{

  typedef itk::ScaleSkewVersor3DTransform<double> TransformType;
  TransformType *t = dynamic_cast<TransformType*>(transform);

  // explicitly remove all function pointer with reference to prior transform
  this->m_pfSetCenter = SITK_NULLPTR;
  this->m_pfGetCenter = SITK_NULLPTR;
  this->m_pfSetTranslation = SITK_NULLPTR;
  this->m_pfGetTranslation = SITK_NULLPTR;
  this->m_pfSetRotation1 = SITK_NULLPTR;
  this->m_pfSetRotation2 = SITK_NULLPTR;
  this->m_pfGetVersor = SITK_NULLPTR;
  this->m_pfTranslate = SITK_NULLPTR;

  if (t)
    {
    this->InternalInitialization(t);
    return;
    }
}


template<class TransformType>
void ScaleSkewVersor3DTransform::InternalInitialization(TransformType *t)
{

  SITK_TRANSFORM_SET_MPF(Center, typename TransformType::InputPointType, double);
  SITK_TRANSFORM_SET_MPF(Translation, typename TransformType::OutputVectorType, double);
  SITK_TRANSFORM_SET_MPF(Scale, typename TransformType::ScaleVectorType, double);
  SITK_TRANSFORM_SET_MPF(Skew, typename TransformType::SkewVectorType, double);

  void 	(TransformType::*pfSetRotation1) (const typename TransformType::VersorType &) = &TransformType::SetRotation;
  this->m_pfSetRotation1 = nsstd::bind(pfSetRotation1,t,nsstd::bind(&sitkSTLVectorToITKVersor<double, double>,nsstd::placeholders::_1));

  typename TransformType::OutputVectorType (*pfSTLVectorToITK)(const std::vector<double> &) = &sitkSTLVectorToITK<typename TransformType::OutputVectorType, double>;
  void 	(TransformType::*pfSetRotation2) (const typename TransformType::AxisType &, double) = &TransformType::SetRotation;
  this->m_pfSetRotation2 = nsstd::bind(pfSetRotation2,t,nsstd::bind(pfSTLVectorToITK,nsstd::placeholders::_1),nsstd::placeholders::_2);

  this->m_pfGetVersor  = nsstd::bind(&sitkITKVersorToSTL<double, double>,nsstd::bind(&TransformType::GetVersor,t));


  // pre argument has no effect
  this->m_pfTranslate = nsstd::bind(&TransformType::Translate,t,nsstd::bind(pfSTLVectorToITK,nsstd::placeholders::_1), false);
}

}
}
