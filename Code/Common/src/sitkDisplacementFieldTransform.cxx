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
#include "sitkDisplacementFieldTransform.h"
#include "sitkPimpleTransform.hxx"
#include "sitkImageConvert.h"

#include "itkDisplacementFieldTransform.h"
#include "itkBSplineSmoothingOnUpdateDisplacementFieldTransform.h"
#include "itkGaussianSmoothingOnUpdateDisplacementFieldTransform.h"
#include "itkVectorImage.h"
#include "itkImage.h"

namespace itk
{
namespace simple
{

namespace
{

template<unsigned int NDimension>
typename itk::Image<itk::Vector<double,NDimension>,NDimension>::Pointer
 GetITKImageFormSITKVectorImage(Image &inImage)
{
  typedef itk::VectorImage<double,NDimension> VectorImageType;

  if (inImage.GetDimension() != NDimension)
    {
    sitkExceptionMacro("Expected input displacement field image to be of dimension "
                       << NDimension << " not " << inImage.GetDimension() << "!" );
    }

  if (inImage.GetPixelID() != sitkVectorFloat64)
    {
    sitkExceptionMacro("Expected input displacement field image for be of pixel type: " << sitkVectorFloat64);
    }

  typename VectorImageType::Pointer image = dynamic_cast < VectorImageType* > ( inImage.GetITKBase() );

  if ( image.IsNull() )
    {
    sitkExceptionMacro( "Unexpected casting error!")
    }

  // make inImage Unique

  typedef typename itk::Image<itk::Vector<double,NDimension>,NDimension> ImageVectorType;
  typename ImageVectorType::Pointer out = GetImageFromVectorImage(image.GetPointer(), true );

  // make in Image unique so no other object reference, then take ownership.
  inImage = Image();

  return out;
}

template< typename TDisplacementFieldTransform >
void InternalSetDisplacementField( TDisplacementFieldTransform *itkDisplacementTx, Image & inImage )
{
  typedef typename TDisplacementFieldTransform::DisplacementFieldType ITKDisplacementFieldType;
  typename ITKDisplacementFieldType::Pointer itkDisplacement = GetITKImageFormSITKVectorImage<TDisplacementFieldTransform::Dimension>(inImage);
  itkDisplacementTx->SetDisplacementField(itkDisplacement);
}

}

// construct identity
DisplacementFieldTransform::DisplacementFieldTransform(unsigned int dimensions)
  : Transform( CreateDisplacementFieldPimpleTransform(dimensions) )
{
  Self::InternalInitialization(Self::GetITKBase());
}


DisplacementFieldTransform::DisplacementFieldTransform( Image &img)
  : Transform( img )
{
  Self::InternalInitialization(Self::GetITKBase());
}

DisplacementFieldTransform::DisplacementFieldTransform( const DisplacementFieldTransform &arg )
  : Transform(arg)
{
  Self::InternalInitialization(Self::GetITKBase());
}


DisplacementFieldTransform &DisplacementFieldTransform::operator=( const DisplacementFieldTransform &arg )
{
  Superclass::operator=(arg);
  return *this;
}


DisplacementFieldTransform::Self &DisplacementFieldTransform::SetDisplacementField(Image &img)
{
  this->m_pfSetDisplacementField(img);
  return *this;
}

Image DisplacementFieldTransform::GetDisplacementField() const
{
  return this->m_pfGetDisplacementField();
}


DisplacementFieldTransform::Self &DisplacementFieldTransform::SetInverseDisplacementField(Image &img)
{
  this->m_pfSetInverseDisplacementField(img);
  return *this;
}


Image DisplacementFieldTransform::GetInverseDisplacementField() const
{
  return this->m_pfGetInverseDisplacementField();
}

DisplacementFieldTransform::Self &DisplacementFieldTransform::SetInterpolator(InterpolatorEnum interp)
{
  this->m_pfSetInterpolator(interp);
  return *this;
}

InterpolatorEnum DisplacementFieldTransform::GetInterpolator() const
{
  return this->m_pfGetInterpolator();
}

DisplacementFieldTransform::Self &DisplacementFieldTransform::SetSmoothingOff()
{
  return *this;
}

DisplacementFieldTransform::Self &DisplacementFieldTransform::SetSmoothingGaussianOnUpdate( double varianceForUpdateField, double varianceForTotalField )
{
  return *this;
}

DisplacementFieldTransform::Self &
DisplacementFieldTransform::SetSmoothingBSplineOnUpdate( std::vector<unsigned int> numberOfControlPointsForUpdateField,
                                                           std::vector<unsigned int> meshSizeForTotalField,
                                                           bool enforceStationaryBoundary,
                                                           unsigned int order )
{
  return *this;
}


void DisplacementFieldTransform::SetPimpleTransform( PimpleTransformBase *pimpleTransform )
{
  Superclass::SetPimpleTransform(pimpleTransform);
  Self::InternalInitialization(this->GetITKBase());
}

void DisplacementFieldTransform::InternalInitialization(itk::TransformBase *transform)
{
  MyVisitor visitor;
  visitor.transform = transform;
  visitor.that = this;

  typedef typelist::MakeTypeList<
    itk::DisplacementFieldTransform<double, 3>,
    itk::DisplacementFieldTransform<double, 2>,
    itk::BSplineSmoothingOnUpdateDisplacementFieldTransform<double, 3>,
    itk::BSplineSmoothingOnUpdateDisplacementFieldTransform<double, 2>,
    itk::GaussianSmoothingOnUpdateDisplacementFieldTransform<double, 3>,
    itk::GaussianSmoothingOnUpdateDisplacementFieldTransform<double, 2> >::Type TransformTypeList;

  typelist::Visit<TransformTypeList> callInternalInitialization;

  // explicitly remove all function pointer with reference to prior transform
  m_pfSetDisplacementField = SITK_NULLPTR;
  m_pfGetDisplacementField = SITK_NULLPTR;
  m_pfSetInverseDisplacementField = SITK_NULLPTR;
  m_pfGetInverseDisplacementField = SITK_NULLPTR;
  m_pfSetInterpolator = SITK_NULLPTR;
  m_pfGetInterpolator = SITK_NULLPTR;

  callInternalInitialization(visitor);

}


template<class TransformType>
void DisplacementFieldTransform::InternalInitialization(TransformType *t)
{
  this->m_pfSetDisplacementField = nsstd::bind(&InternalSetDisplacementField<TransformType>, t, nsstd::placeholders::_1);
  this->m_pfGetDisplacementField = nsstd::bind(&DisplacementFieldTransform::InternalGetDisplacementField<TransformType>, t);

  this->m_pfGetInverseDisplacementField = nsstd::bind(&DisplacementFieldTransform::InternalGetInverseDisplacementField<TransformType>, t);

}

PimpleTransformBase *DisplacementFieldTransform::CreateDisplacementFieldPimpleTransform(unsigned int dimension)
{
  switch (dimension)
    {
      case 2:
        return new PimpleTransform<itk::DisplacementFieldTransform<double,2> >();
      case 3:
        return new PimpleTransform<itk::DisplacementFieldTransform<double,3> >();
    default:
      sitkExceptionMacro("Invalid dimension for transform");
    }
}


template< typename TDisplacementFieldTransform >
Image DisplacementFieldTransform::InternalGetDisplacementField( const TDisplacementFieldTransform *itkDisplacementTx )
{
  typedef typename TDisplacementFieldTransform::DisplacementFieldType DisplacementFieldType;
  DisplacementFieldType *itkDisplacement = const_cast<DisplacementFieldType*>(itkDisplacementTx->GetDisplacementField());
  if (itkDisplacement != NULL)
    {
    return Image(GetVectorImageFromImage(itkDisplacement));
    }
  return Image(std::vector<unsigned int>(TDisplacementFieldTransform::Dimension,0), sitkVectorFloat64);
}

template< typename TDisplacementFieldTransform >
Image DisplacementFieldTransform::InternalGetInverseDisplacementField( const TDisplacementFieldTransform *itkDisplacementTx )
{
  typedef typename TDisplacementFieldTransform::DisplacementFieldType DisplacementFieldType;
  DisplacementFieldType *itkDisplacement = const_cast<DisplacementFieldType*>(itkDisplacementTx->GetInverseDisplacementField());
  if (itkDisplacement != NULL)
    {
    return Image(GetVectorImageFromImage(itkDisplacement));
    }
  return Image(std::vector<unsigned int>(TDisplacementFieldTransform::Dimension,0), sitkVectorFloat64);
}



}
}
