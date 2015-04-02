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
#include "sitkTransformHelper.hxx"

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


template<typename TBSplineTransform>
unsigned int sitkGetOrder(void)
{
  return TBSplineTransform::SplineOrder;
}

}


// construct identity
BSplineTransform::BSplineTransform(unsigned int dimensions, unsigned int order)
  : Transform( CreateBSplinePimpleTransform(dimensions, order) )
{
  Self::InternalInitialization(Self::GetITKBase());
}

BSplineTransform::BSplineTransform( const BSplineTransform &arg )
  : Transform(arg)
{
  Self::InternalInitialization(Self::GetITKBase());
}


BSplineTransform::BSplineTransform( const Transform &arg )
  : Transform( arg )
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
  this->MakeUnique();
  this->m_pfSetTransformDomainDirection(params);
  return *this;
}


std::vector<double> BSplineTransform::GetTransformDomainDirection() const
{
  return this->m_pfGetTransformDomainDirection();
}


BSplineTransform::Self &BSplineTransform::SetTransformDomainMeshSize(const std::vector<unsigned int>&params)
{
  this->MakeUnique();
  this->m_pfSetTransformDomainMeshSize(params);
  return *this;
}


std::vector<unsigned int> BSplineTransform::GetTransformDomainMeshSize() const
{
  return this->m_pfGetTransformDomainMeshSize();
}


BSplineTransform::Self &BSplineTransform::SetTransformDomainOrigin(const std::vector<double>&params)
{
  this->MakeUnique();
  this->m_pfSetTransformDomainOrigin(params);
  return *this;
}


std::vector<double> BSplineTransform::GetTransformDomainOrigin() const
{
  return this->m_pfGetTransformDomainOrigin();
}


BSplineTransform::Self &BSplineTransform::SetTransformDomainPhysicalDimensions(const std::vector<double> &params)
{
  this->MakeUnique();
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

unsigned int BSplineTransform::GetOrder() const
{
  return this->m_pfGetOrder();
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

  typedef typelist::MakeTypeList<
  itk::BSplineTransform<double, 3, 0>,
    itk::BSplineTransform<double, 2, 0>,
  itk::BSplineTransform<double, 3, 1>,
    itk::BSplineTransform<double, 2, 1>,
  itk::BSplineTransform<double, 3, 2>,
    itk::BSplineTransform<double, 2, 2>,
  itk::BSplineTransform<double, 3, 3>,
    itk::BSplineTransform<double, 2, 3> >::Type TransformTypeList;

  typelist::Visit<TransformTypeList> callInternalInitialization;

  // explicitly remove all function pointer with reference to prior transform
  this->m_pfGetTransformDomainDirection = SITK_NULLPTR;
  this->m_pfSetTransformDomainDirection = SITK_NULLPTR;
  this->m_pfGetTransformDomainMeshSize = SITK_NULLPTR;
  this->m_pfSetTransformDomainMeshSize = SITK_NULLPTR;
  this->m_pfGetTransformDomainOrigin = SITK_NULLPTR;
  this->m_pfSetTransformDomainOrigin = SITK_NULLPTR;
  this->m_pfGetTransformDomainPhysicalDimensions = SITK_NULLPTR;
  this->m_pfSetTransformDomainPhysicalDimensions = SITK_NULLPTR;
  this->m_pfGetCoefficientImages = SITK_NULLPTR;
  this->m_pfGetOrder = SITK_NULLPTR;

  callInternalInitialization(visitor);

  if ( this->m_pfGetOrder == SITK_NULLPTR )
    {
    sitkExceptionMacro("Transform is not of type " << this->GetName() << "!" );
    }
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

   // TransformDomainMeshSize
  SITK_TRANSFORM_SET_MPF( TransformDomainMeshSize, typename TransformType::MeshSizeType, unsigned int );
  // TransformDomainOrigin
  SITK_TRANSFORM_SET_MPF( TransformDomainOrigin, typename TransformType::OriginType, double );
  // TransformDomainPhysicalDimensions
  SITK_TRANSFORM_SET_MPF( TransformDomainPhysicalDimensions, typename TransformType::PhysicalDimensionsType, double );


  std::vector<Image> (*pfImageArrayConvert)(const typename TransformType::CoefficientImageArray &) = &sitkImageArrayConvert<typename TransformType::CoefficientImageArray>;
  this->m_pfGetCoefficientImages = nsstd::bind(pfImageArrayConvert, nsstd::bind(&TransformType::GetCoefficientImages,t) );

  this->m_pfGetOrder =  &sitkGetOrder<TransformType>;
}

PimpleTransformBase *BSplineTransform::CreateBSplinePimpleTransform(unsigned int dimension, unsigned int order)
{
  switch (dimension)
    {
    case 2:
      return Self::CreateBSplinePimpleTransform<2>(order);
    case 3:
      return Self::CreateBSplinePimpleTransform<3>(order);
    default:
      sitkExceptionMacro("Invalid dimension for transform");
    }
}

template <unsigned int ND>
PimpleTransformBase *BSplineTransform::CreateBSplinePimpleTransform(unsigned int order)
{
  switch(order)
    {
    case 0:
      return new PimpleTransform<itk::BSplineTransform<double,ND,0> >();
    case 1:
      return new PimpleTransform<itk::BSplineTransform<double,ND,1> >();
    case 2:
      return new PimpleTransform<itk::BSplineTransform<double,ND,2> >();
    case 3:
      return new PimpleTransform<itk::BSplineTransform<double,ND,3> >();
    default:
      sitkExceptionMacro("Spline order " << static_cast<int>(order) << " is not supported!");
    }
}

}
}
