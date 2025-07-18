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

#include <memory>

#include "itkImage.h"
#include "itkVectorImage.h"
#include "itkLabelMap.h"
#include "itkLabelObject.h"
#include "itkNumericTraits.h"
#include "itkNumericTraitsVariableLengthVectorPixel.h"
#include "itkVectorIndexSelectionCastImageFilter.h"
#include "itkComposeImageFilter.h"

#include "sitkLandmarkBasedTransformInitializerFilter.h"
#include "itkLandmarkBasedTransformInitializer.h"

// Additional include files
#include "sitkTransform.h"
#include "sitkBSplineTransform.h"
// Done with additional include files

namespace itk::simple
{

//-----------------------------------------------------------------------------

//
// Default constructor that initializes parameters
//
LandmarkBasedTransformInitializerFilter::LandmarkBasedTransformInitializerFilter() = default;

const detail::MemberFunctionFactory<LandmarkBasedTransformInitializerFilter::MemberFunctionType> &
LandmarkBasedTransformInitializerFilter::GetMemberFunctionFactory()
{
  static detail::MemberFunctionFactory<MemberFunctionType> static_factory = [] {
    detail::MemberFunctionFactory<MemberFunctionType> factory;
    factory.RegisterMemberFunctions<PixelIDTypeList, 3>();
    factory.RegisterMemberFunctions<PixelIDTypeList, 2>();
    return factory;
  }();

  return static_factory;
}


//
// Destructor
//
LandmarkBasedTransformInitializerFilter::~LandmarkBasedTransformInitializerFilter() = default;


//
// ToString
//
std::string
LandmarkBasedTransformInitializerFilter::ToString() const
{
  std::ostringstream out;
  out << "itk::simple::LandmarkBasedTransformInitializerFilter\n";
  out << "  FixedLandmarks: ";
  this->ToStringHelper(out, this->m_FixedLandmarks);
  out << std::endl;
  out << "  MovingLandmarks: ";
  this->ToStringHelper(out, this->m_MovingLandmarks);
  out << std::endl;
  out << "  LandmarkWeight: ";
  this->ToStringHelper(out, this->m_LandmarkWeight);
  out << std::endl;
  // out << "  ReferenceImage: ";
  // this->ToStringHelper(out, this->m_ReferenceImage);
  out << std::endl;
  out << "  BSplineNumberOfControlPoints: ";
  this->ToStringHelper(out, this->m_BSplineNumberOfControlPoints);
  out << std::endl;

  out << ProcessObject::ToString();
  return out.str();
}

//
// Execute
//
Transform
LandmarkBasedTransformInitializerFilter::Execute(const Transform & transform)
{
  const unsigned int dimension = transform.GetDimension();

  // The dimension of the reference image which the user explicitly
  // set (GetSize()!=[0...0]), and the dimension of the transform do not match
  if (this->m_ReferenceImage.GetSize() != std::vector<unsigned int>(this->m_ReferenceImage.GetDimension(), 0u) &&
      dimension != this->m_ReferenceImage.GetDimension())
  {
    sitkExceptionMacro(
      "ReferenceImage for LandmarkBasedTransformInitializerFilter does not match dimension of the transform!");
  }

  return GetMemberFunctionFactory().GetMemberFunction(sitkFloat32, dimension, this)(&transform);
}


//-----------------------------------------------------------------------------

//
// Custom Casts
//
namespace
{}

//-----------------------------------------------------------------------------

//
// ExecuteInternal
//
template <class TImageType>
Transform
LandmarkBasedTransformInitializerFilter::ExecuteInternal(const Transform * inTransform)
{

  // Define the input and output image types
  using InputImageType = itk::ImageBase<TImageType::ImageDimension>;
  const unsigned int Dimension = InputImageType::ImageDimension;


  using FilterType = itk::
    LandmarkBasedTransformInitializer<itk::Transform<double, Dimension, Dimension>, InputImageType, InputImageType>;
  // Set up the ITK filter
  typename FilterType::Pointer filter = FilterType::New();

  // This initializers modifies the input, we copy the transform to
  // prevent this change
  Transform copyTransform(*inTransform);
  copyTransform.SetFixedParameters(copyTransform.GetFixedParameters());


  const typename FilterType::TransformType * itkTx =
    dynamic_cast<const typename FilterType::TransformType *>(copyTransform.GetITKBase());

  if (!itkTx)
  {
    sitkExceptionMacro("Unexpected error converting transform! Possible miss matching dimensions!");
  }
  else
  {
    filter->SetTransform(const_cast<typename FilterType::TransformType *>(itkTx));
  }


  using PointContainer = typename FilterType::LandmarkPointContainer;
  PointContainer fixedITKPoints;
  fixedITKPoints = sitkSTLVectorToITKPointVector<PointContainer, double>(m_FixedLandmarks);
  filter->SetFixedLandmarks(fixedITKPoints);

  PointContainer movingITKPoints;
  movingITKPoints = sitkSTLVectorToITKPointVector<PointContainer, double>(m_MovingLandmarks);
  filter->SetMovingLandmarks(movingITKPoints);

  filter->SetLandmarkWeight(this->m_LandmarkWeight);

  using TransformCategoryEnum = typename FilterType::TransformType::TransformCategoryEnum;
  // BSpline specific setup
  if (itkTx->GetTransformCategory() == TransformCategoryEnum::BSpline)
  {
    if (this->m_ReferenceImage.GetSize() == std::vector<unsigned int>(this->m_ReferenceImage.GetDimension(), 0u))
    {
      sitkExceptionMacro("Image not set for BSplineTransform initializer.");
    }
    {
      BSplineTransform bsTx(*inTransform);
      if (bsTx.GetOrder() != 3)
      {
        sitkExceptionMacro("BSplineTransform is only supported  with an order of 3.")
      }
    }
    // Get the pointer to the ITK image contained in image1
    typename InputImageType::ConstPointer referenceImage = this->CastImageToITK<InputImageType>(this->m_ReferenceImage);
    filter->SetReferenceImage(referenceImage.GetPointer());
    filter->SetBSplineNumberOfControlPoints(this->m_BSplineNumberOfControlPoints);
  }

  sitkDebugMacro(<< "Executing ITK filter:" << std::endl << *filter);


  filter->InitializeTransform();

  return copyTransform;
}

//-----------------------------------------------------------------------------


//
// Function to run the Execute method of this filter
//
Transform
LandmarkBasedTransformInitializer(const Transform &           transform,
                                  const std::vector<double> & fixedLandmarks,
                                  const std::vector<double> & movingLandmarks,
                                  const std::vector<double> & landmarkWeight,
                                  const Image &               referenceImage,
                                  unsigned int                numberOfControlPoints)
{
  LandmarkBasedTransformInitializerFilter filter;
  filter.SetFixedLandmarks(fixedLandmarks);
  filter.SetMovingLandmarks(movingLandmarks);
  filter.SetLandmarkWeight(landmarkWeight);
  filter.SetReferenceImage(referenceImage);
  filter.SetBSplineNumberOfControlPoints(numberOfControlPoints);
  return filter.Execute(transform);
}


} // namespace itk::simple
