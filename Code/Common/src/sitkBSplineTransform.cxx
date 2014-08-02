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
#include "sitkBSplineTransform.h"
#include "sitkPimpleTransform.hxx"

#include "itkBSplineTransform.h"

namespace itk
{
namespace simple
{
namespace
{
// convert an itk::Array of images to a stl vector of sitk images
template<typename TImageArrayType>
std::vector<Image> sitkImageArrayConvert(const TImageArrayType &a)
{
  std::vector<Image> ret(a.Size());

  for( unsigned int i = 0; i < a.Size(); ++i )
    {
    ret[i] = Image(a[i]);
    }
  return ret;
}
}


// construct identity
BSplineTransform::BSplineTransform(unsigned int dimensions)
  : Transform( CreateBSplinePimpleTransform(dimensions) )
{
  Self::InternalInitialization(Self::GetITKBase());
}

BSplineTransform::BSplineTransform( const BSplineTransform &arg )
  : Transform(arg)
{
  Self::InternalInitialization(Self::GetITKBase());
}


BSplineTransform &BSplineTransform::operator=( const BSplineTransform &arg )
{
  Superclass::operator=(arg);
  return *this;
}


BSplineTransform::Self &BSplineTransform::SetTransformDomainDirection(const std::vector<double> &params)
{
  this->MakeUniqueForWrite();
  this->m_pfSetTransformDomainDirection(params);
  return *this;
}


std::vector<double> BSplineTransform::GetTransformDomainDirection() const
{
  return this->m_pfGetTransformDomainDirection();
}


BSplineTransform::Self &BSplineTransform::SetTransformDomainMeshSize(const std::vector<unsigned int>&params)
{
  this->MakeUniqueForWrite();
  this->m_pfSetTransformDomainMeshSize(params);
  return *this;
}


std::vector<unsigned int> BSplineTransform::GetTransformDomainMeshSize() const
{
  return this->m_pfGetTransformDomainMeshSize();
}


BSplineTransform::Self &BSplineTransform::SetTransformDomainOrigin(const std::vector<double>&params)
{
  this->MakeUniqueForWrite();
  this->m_pfSetTransformDomainOrigin(params);
  return *this;
}


std::vector<double> BSplineTransform::GetTransformDomainOrigin() const
{
  return this->m_pfGetTransformDomainOrigin();
}


BSplineTransform::Self &BSplineTransform::SetTransformDomainPhysicalDimensions(const std::vector<double> &params)
{
  this->MakeUniqueForWrite();
  this->m_pfSetTransformDomainPhysicalDimensions(params);
  return *this;
}


std::vector<double> BSplineTransform::GetTransformDomainPhysicalDimensions() const
{
  return this->m_pfGetTransformDomainPhysicalDimensions();
}


std::vector<Image> BSplineTransform::GetCoefficientImages () const
{
  return this->m_pfGetCoefficientImages();
}


void BSplineTransform::SetPimpleTransform( PimpleTransformBase *pimpleTransform )
{
  Superclass::SetPimpleTransform(pimpleTransform);
  Self::InternalInitialization(this->GetITKBase());
}

void BSplineTransform::InternalInitialization(itk::TransformBase *transform)
{
  MyVisitor visitor;
  visitor.transform = transform;
  visitor.that = this;

  const unsigned int order = 3;

  typedef typelist::MakeTypeList<itk::BSplineTransform<double, 3, order>,
    itk::BSplineTransform<double, 2, order> >::Type TransformTypeList;

  typelist::Visit<TransformTypeList> callInternalInitialization;


  callInternalInitialization(visitor);

}


template<class TransformType>
void BSplineTransform::InternalInitialization(TransformType *t)
{
  { // TransformDomainDirection
  typename TransformType::DirectionType (*pfSTLToITKDirection)(const std::vector<double> &) = &sitkSTLToITKDirection<typename TransformType::DirectionType>;
  this->m_pfSetTransformDomainDirection = nsstd::bind(&TransformType::SetTransformDomainDirection,t,nsstd::bind(pfSTLToITKDirection,nsstd::placeholders::_1));

  std::vector<double> (*pfITKDirectionToSTL)( const typename TransformType::DirectionType &) = &sitkITKDirectionToSTL<typename TransformType::DirectionType>;
  this->m_pfGetTransformDomainDirection = nsstd::bind(pfITKDirectionToSTL,nsstd::bind(&TransformType::GetTransformDomainDirection,t));
  }


#define SITK_SET_MPF(NAME,ITK_TYPENAME, COMPONENT)                      \
  {                                                                     \
  typedef ITK_TYPENAME itkType;                                         \
  itkType (*pfSTLToITK)(const std::vector<COMPONENT> &) = &sitkSTLVectorToITK<itkType, COMPONENT>; \
  this->m_pfSet##NAME = nsstd::bind(&TransformType::Set##NAME,t,nsstd::bind(pfSTLToITK,nsstd::placeholders::_1)); \
                                                                        \
  std::vector<COMPONENT> (*pfITKToSTL)( const itkType &) = &sitkITKVectorToSTL<COMPONENT,itkType>; \
  this->m_pfGet##NAME = nsstd::bind(pfITKToSTL,nsstd::bind(&TransformType::Get##NAME,t)); \
  }



   // TransformDomainMeshSize
  SITK_SET_MPF( TransformDomainMeshSize, typename TransformType::MeshSizeType, unsigned int );
  // TransformDomainOrigin
  SITK_SET_MPF( TransformDomainOrigin, typename TransformType::OriginType, double );
  // TransformDomainPhysicalDimensions
  SITK_SET_MPF( TransformDomainPhysicalDimensions, typename TransformType::PhysicalDimensionsType, double );


  std::vector<Image> (*pfImageArrayConvert)(const typename TransformType::CoefficientImageArray &) = &sitkImageArrayConvert<typename TransformType::CoefficientImageArray>;
  this->m_pfGetCoefficientImages = nsstd::bind(pfImageArrayConvert, nsstd::bind(&TransformType::GetCoefficientImages,t) );
}

PimpleTransformBase *BSplineTransform::CreateBSplinePimpleTransform(unsigned int dimension)
{
  PimpleTransformBase* temp = NULL;
  const unsigned int order = 3;
  switch (dimension)
    {
    case 2:
      temp = new PimpleTransform<itk::BSplineTransform<double,2,order> >();
      break;
    case 3:
      temp = new PimpleTransform<itk::BSplineTransform<double,3,order> >();
      break;
    default:
      sitkExceptionMacro("Invalid dimension for transform");
    }
  return temp;
}

}
}
