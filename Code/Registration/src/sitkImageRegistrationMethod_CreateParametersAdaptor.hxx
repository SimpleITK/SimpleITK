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
#ifndef sitkImageRegistrationMethod_CreateParametersAdaptor_hxx
#define sitkImageRegistrationMethod_CreateParametersAdaptor_hxx

#include "sitkImageRegistrationMethod.h"

#include "itkShrinkImageFilter.h"

#include "itkDisplacementFieldTransform.h"
#include "itkDisplacementFieldTransformParametersAdaptor.h"

#include "itkBSplineTransform.h"
#include "itkBSplineTransformParametersAdaptor.h"

namespace itk
{
namespace simple
{

template<typename TTransformBase,
         typename TFixedImageType,
         typename TTransformType>
typename TransformParametersAdaptorBase<TTransformBase>::Pointer
CreateTransformParametersAdaptorBSpline(TTransformType *bsplineTransform,
                                        const FixedArray<unsigned int, TTransformBase::InputSpaceDimension> &shrinkFactors,
                                        const TFixedImageType* fixedImage,
                                        unsigned int scaleFactor  )
{

  if ( scaleFactor < 1 )
    {
    return SITK_NULLPTR;
    }

  typedef TTransformType BSplineTransformType;
  typedef TFixedImageType FixedImageType;
  const unsigned int Dimension = FixedImageType::ImageDimension;



  typedef  itk::ShrinkImageFilter< FixedImageType, FixedImageType> ShrinkFilterType;

  typename ShrinkFilterType::Pointer shrinkFilter = ShrinkFilterType::New();
  shrinkFilter->SetShrinkFactors( shrinkFactors );
  shrinkFilter->SetInput( fixedImage );
  shrinkFilter->UpdateOutputInformation();

  TFixedImageType * shrinkOutput = shrinkFilter->GetOutput();

  typename BSplineTransformType::MeshSizeType meshSize = bsplineTransform->GetTransformDomainMeshSize();

  typename BSplineTransformType::MeshSizeType requiredMeshSize;
  for( unsigned int d = 0; d < Dimension; d++ )
    {
    requiredMeshSize[d] = meshSize[d] * scaleFactor;

    }

  typename BSplineTransformType::PhysicalDimensionsType fixedPhysicalDimensions;
  for( unsigned int i=0; i< Dimension; i++ )
    {
    fixedPhysicalDimensions[i] = fixedImage->GetSpacing()[i] *
      static_cast<double>(
      fixedImage->GetLargestPossibleRegion().GetSize()[i] - 1 );
    }


  typedef itk::BSplineTransformParametersAdaptor<BSplineTransformType> BSplineAdaptorType;
  typename BSplineAdaptorType::Pointer bsplineAdaptor = BSplineAdaptorType::New();
  bsplineAdaptor->SetTransform( bsplineTransform );
  bsplineAdaptor->SetRequiredTransformDomainMeshSize( requiredMeshSize );
  bsplineAdaptor->SetRequiredTransformDomainOrigin( shrinkOutput->GetOrigin() );
  bsplineAdaptor->SetRequiredTransformDomainDirection( shrinkOutput->GetDirection() );
  bsplineAdaptor->SetRequiredTransformDomainPhysicalDimensions( fixedPhysicalDimensions );

  return bsplineAdaptor.GetPointer();
}




template<typename TTransformBase, typename TFixedImageType>
typename TransformParametersAdaptorBase<TTransformBase>::Pointer
CreateTransformParametersAdaptorDisplacementField(TTransformBase *transform,
                                                  const FixedArray<unsigned int, TTransformBase::InputSpaceDimension> &shrinkFactors,
                                                  const TFixedImageType* fixedImage,
                                                  unsigned int level  )
{
  Unused(level);
  Unused(fixedImage);

  typedef TFixedImageType FixedImageType;
  const unsigned int Dimension = FixedImageType::ImageDimension;
  typedef itk::DisplacementFieldTransform<double, Dimension> DisplacementFieldTransformType;
  typedef typename DisplacementFieldTransformType::DisplacementFieldType DisplacementFieldType;

  DisplacementFieldTransformType *displacementFieldTransform = dynamic_cast<DisplacementFieldTransformType*>(transform);
  if (!displacementFieldTransform)
    {
    return SITK_NULLPTR;
    }

  const DisplacementFieldType * displacementField = displacementFieldTransform->GetDisplacementField();

  // We use the shrink image filter to calculate the fixed parameters of the virtual
  // domain at each level.  To speed up calculation and avoid unnecessary memory
  // usage, we could calculate these fixed parameters directly.

  typedef itk::ShrinkImageFilter<DisplacementFieldType, DisplacementFieldType> ShrinkFilterType;
  typename ShrinkFilterType::Pointer shrinkFilter = ShrinkFilterType::New();
  shrinkFilter->SetShrinkFactors( shrinkFactors );
  shrinkFilter->SetInput( displacementField );
  shrinkFilter->UpdateOutputInformation();
  typename DisplacementFieldType::Pointer shrinkOutput = shrinkFilter->GetOutput();

  typedef DisplacementFieldTransformParametersAdaptor<DisplacementFieldTransformType> DisplacementFieldTransformAdaptorType;
  typename DisplacementFieldTransformAdaptorType::Pointer fieldTransformAdaptor = DisplacementFieldTransformAdaptorType::New();
  fieldTransformAdaptor->SetRequiredSpacing( shrinkOutput->GetSpacing() );
  fieldTransformAdaptor->SetRequiredSize( shrinkOutput->GetLargestPossibleRegion().GetSize() );
  fieldTransformAdaptor->SetRequiredDirection( shrinkOutput->GetDirection() );
  fieldTransformAdaptor->SetRequiredOrigin( shrinkOutput->GetOrigin() );

  return fieldTransformAdaptor.GetPointer();
}

template<typename TTransformAdaptorPointer, typename TRegistrationMethod >
std::vector< TTransformAdaptorPointer >
ImageRegistrationMethod::CreateTransformParametersAdaptor(TRegistrationMethod* method)
{
  typedef std::vector< TTransformAdaptorPointer >      TransformParametersAdaptorsContainerType;
  typedef typename TRegistrationMethod::FixedImageType FixedImageType;

  typedef typename TRegistrationMethod::InitialTransformType TransformType;

  typedef typename TRegistrationMethod::TransformParametersAdaptorPointer TransformParametersAdaptorTypePointer;


  TransformType *transform = const_cast<TransformType *>(method->GetInitialTransform());

  TransformParametersAdaptorsContainerType adaptors;

  const unsigned int numberOfLevels = method->GetNumberOfLevels();
  const FixedImageType *fixedImage = method->GetFixedImage();

  typedef itk::DisplacementFieldTransform<double, FixedImageType::ImageDimension> DisplacementFieldTransformType;
  DisplacementFieldTransformType *displacementField = dynamic_cast<DisplacementFieldTransformType *>(transform);

  typedef itk::BSplineTransform<double, FixedImageType::ImageDimension, 3> BSplineTransformO3Type;
  BSplineTransformO3Type *bsplineO3 = dynamic_cast<BSplineTransformO3Type *>(transform);

  typedef itk::BSplineTransform<double, FixedImageType::ImageDimension, 2> BSplineTransformO2Type;
  BSplineTransformO2Type *bsplineO2 = dynamic_cast<BSplineTransformO2Type *>(transform);

  for( unsigned int level = 0; level < numberOfLevels; ++level )
    {
    const typename TRegistrationMethod::ShrinkFactorsPerDimensionContainerType &shrinkFactors = method->GetShrinkFactorsPerDimension(level);

    unsigned int bsplineScaleFactor = 0;
    if ( m_TransformBSplineScaleFactors.size() > level )
      {
      bsplineScaleFactor = m_TransformBSplineScaleFactors[level];
      }

    TransformParametersAdaptorTypePointer adaptor = SITK_NULLPTR;
    if (displacementField != SITK_NULLPTR)
      {
      adaptor = CreateTransformParametersAdaptorDisplacementField<TransformType>( displacementField,
                                                                                  shrinkFactors,
                                                                                  fixedImage,
                                                                                  level );
      }
    else if (bsplineO3 != SITK_NULLPTR)
      {
      adaptor = CreateTransformParametersAdaptorBSpline<TransformType>( bsplineO3,
                                                                        shrinkFactors,
                                                                        fixedImage,
                                                                        bsplineScaleFactor );
      }
    else if (bsplineO2 != SITK_NULLPTR)
      {
      adaptor = CreateTransformParametersAdaptorBSpline<TransformType>( bsplineO2,
                                                                        shrinkFactors,
                                                                        fixedImage,
                                                                        bsplineScaleFactor );
      }


    adaptors.push_back( adaptor.GetPointer() );
    }
  return adaptors;
}





}
}
#endif // sitkImageRegistrationMethod_CreateParametersAdaptor_hxx
