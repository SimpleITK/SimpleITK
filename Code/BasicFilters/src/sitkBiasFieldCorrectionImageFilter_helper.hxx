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
#ifndef sitkBiasFieldCorrectionImageFilter_helper_hxx
#define sitkBiasFieldCorrectionImageFilter_helper_hxx

#include "itkBSplineControlPointImageFilter.h"

namespace itk
{
namespace simple
{

template<typename TBiasFieldType>
Image BSplineLatticeToImage(const TBiasFieldType *bsplineLattice, const Image &referenceImage, unsigned int splineOrder = 3)
{
  constexpr unsigned int Dimension = TBiasFieldType::ImageDimension;

  using BaseImageType = typename itk::ImageBase<Dimension>;
  using ScalarImageType = itk::Image<itk::Vector<float, 1>, Dimension>;

  using BSplinerType = itk::BSplineControlPointImageFilter<TBiasFieldType, ScalarImageType>;
  typename BSplinerType::Pointer bspliner = BSplinerType::New();
  bspliner->SetInput(bsplineLattice);
  bspliner->SetSplineOrder(splineOrder);
  bspliner->SetSize(sitkSTLVectorToITK<typename BaseImageType::SizeType>(referenceImage.GetSize()));
  bspliner->SetOrigin(sitkSTLVectorToITK<typename BaseImageType::PointType>(referenceImage.GetOrigin()));
  bspliner->SetSpacing(sitkSTLVectorToITK<typename BaseImageType::SpacingType>(referenceImage.GetSpacing()));
  bspliner->SetDirection(sitkSTLToITKDirection<typename BaseImageType::DirectionType>(referenceImage.GetDirection()));

  // This update is require to prevent erroneous output, from full
  // pipeline execution.
  bspliner->Update();

  auto caster = itk::UnaryGeneratorImageFilter<ScalarImageType, itk::Image<float,Dimension> >::New();
  caster->SetFunctor([](const typename ScalarImageType::PixelType &p){return p[0];});
  caster->SetInput(bspliner->GetOutput());
  caster->Update();

  return Image(caster->GetOutput());
}
}
}
#endif // sitkBiasFieldCorrectionImageFilter_helper_hxx
