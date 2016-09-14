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

namespace itk
{
namespace simple
{




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

  DisplacementFieldType * displacementField = displacementFieldTransform->GetDisplacementField();

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
  const bool isDisplacementField = (dynamic_cast<DisplacementFieldTransformType *>(transform) != SITK_NULLPTR);

  for( unsigned int level = 0; level < numberOfLevels; ++level )
    {
    const typename TRegistrationMethod::ShrinkFactorsPerDimensionContainerType &shrinkFactors = method->GetShrinkFactorsPerDimension(level);
    TransformParametersAdaptorTypePointer adaptor = SITK_NULLPTR;
    if (isDisplacementField)
      {
      adaptor = CreateTransformParametersAdaptorDisplacementField( transform,
                                                                   shrinkFactors,
                                                                   fixedImage,
                                                                   level );
      }


    adaptors.push_back( adaptor.GetPointer() );
    }
  return adaptors;
}





}
}
#endif // sitkImageRegistrationMethod_CreateParametersAdaptor_hxx
