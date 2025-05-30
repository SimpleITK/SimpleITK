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

#include "sitkDisplacementFieldTransform.h"
#include "sitkPimpleTransform.hxx"
#include "sitkImageConvert.hxx"

#include "itkDisplacementFieldTransform.h"
#include "itkBSplineSmoothingOnUpdateDisplacementFieldTransform.h"
#include "itkGaussianSmoothingOnUpdateDisplacementFieldTransform.h"
#include "itkVectorImage.h"
#include "itkImage.h"
#include "itkVectorNearestNeighborInterpolateImageFunction.h"

namespace itk::simple
{

namespace
{

template <unsigned int NDimension>
typename itk::Image<itk::Vector<double, NDimension>, NDimension>::Pointer
GetITKImageFromSITKVectorImage(Image & inImage)
{
  using VectorImageType = itk::VectorImage<double, NDimension>;

  if (inImage.GetDimension() != NDimension)
  {
    sitkExceptionMacro("Expected input displacement field image to be of dimension " << NDimension << " not "
                                                                                     << inImage.GetDimension() << "!");
  }

  if (inImage.GetPixelID() != sitkVectorFloat64)
  {
    sitkExceptionMacro("Expected input displacement field image must be of pixel type: " << sitkVectorFloat64);
  }

  typename VectorImageType::Pointer image = dynamic_cast<VectorImageType *>(inImage.GetITKBase());

  if (image.IsNull())
  {
    sitkExceptionMacro("Unexpected casting error!")
  }

  // TODO: the input image needs to be made unique before we take the buffer

  using ImageVectorType = typename itk::Image<itk::Vector<double, NDimension>, NDimension>;
  typename ImageVectorType::Pointer out = GetImageFromVectorImage(image.GetPointer(), true);

  // With the above the itk::Image has taken ownership, so the input
  // image is set to a new empty image.
  inImage = Image();

  return out;
}

template <typename TDisplacementFieldTransform>
void
InternalSetDisplacementField(TDisplacementFieldTransform * itkDisplacementTx, Image & inImage)
{
  using ITKDisplacementFieldType = typename TDisplacementFieldTransform::DisplacementFieldType;
  typename ITKDisplacementFieldType::Pointer itkDisplacement =
    GetITKImageFromSITKVectorImage<TDisplacementFieldTransform::Dimension>(inImage);
  itkDisplacementTx->SetDisplacementField(itkDisplacement);
}


template <typename TDisplacementFieldTransform>
void
InternalSetInverseDisplacementField(TDisplacementFieldTransform * itkDisplacementTx, Image & inImage)
{
  using ITKDisplacementFieldType = typename TDisplacementFieldTransform::DisplacementFieldType;
  typename ITKDisplacementFieldType::Pointer itkDisplacement =
    GetITKImageFromSITKVectorImage<TDisplacementFieldTransform::Dimension>(inImage);
  itkDisplacementTx->SetInverseDisplacementField(itkDisplacement);
}


template <typename TDisplacementFieldTransform>
void
InternalSetInterpolator(TDisplacementFieldTransform * itkDisplacementTx, InterpolatorEnum interp)
{
  using ITKInterpoaltorType = typename TDisplacementFieldTransform::InterpolatorType;
  using ImageType = typename TDisplacementFieldTransform::DisplacementFieldType;
  using ScalarType = typename TDisplacementFieldTransform::ScalarType;
  typename ITKInterpoaltorType::Pointer itkInterp;
  switch (interp)
  {
    case sitkNearestNeighbor:
    {
      using InterpolatorType = itk::VectorNearestNeighborInterpolateImageFunction<ImageType, ScalarType>;
      itkInterp = InterpolatorType::New();
      break;
    }
    case sitkLinear:
    {
      using InterpolatorType = itk::VectorLinearInterpolateImageFunction<ImageType, ScalarType>;
      itkInterp = InterpolatorType::New();
      break;
    }
    default:
      sitkExceptionMacro("Interpolator type " << interp << " is not supported!");
  }
  itkDisplacementTx->SetInterpolator(itkInterp);
  itkDisplacementTx->SetInverseInterpolator(itkInterp);
}


} // namespace

DisplacementFieldTransform::~DisplacementFieldTransform() = default;

// construct identity
DisplacementFieldTransform::DisplacementFieldTransform(unsigned int dimensions)
  : Transform(CreateDisplacementFieldPimpleTransform(dimensions))
{
  Self::InternalInitialization(Self::GetITKBase());
}


DisplacementFieldTransform::DisplacementFieldTransform(Image & img)
  : Transform(CreateDisplacementFieldPimpleTransform(img.GetDimension()))
{
  Self::InternalInitialization(Self::GetITKBase());
  Self::SetDisplacementField(img);
}

DisplacementFieldTransform::DisplacementFieldTransform(const DisplacementFieldTransform & arg)
  : Transform(arg)
{
  Self::InternalInitialization(Self::GetITKBase());
}


DisplacementFieldTransform::DisplacementFieldTransform(const Transform & arg)
  : Transform(arg)
{
  Self::InternalInitialization(Self::GetITKBase());
}


DisplacementFieldTransform &
DisplacementFieldTransform::operator=(const DisplacementFieldTransform & arg)
{
  Superclass::operator=(arg);
  return *this;
}


void
DisplacementFieldTransform::SetDisplacementField(Image & img)
{
  this->MakeUnique();
  this->m_pfSetDisplacementField(img);
}

Image
DisplacementFieldTransform::GetDisplacementField() const
{
  return this->m_pfGetDisplacementField();
}


void
DisplacementFieldTransform::SetInverseDisplacementField(Image & img)
{
  this->MakeUnique();
  this->m_pfSetInverseDisplacementField(img);
}


Image
DisplacementFieldTransform::GetInverseDisplacementField() const
{
  return this->m_pfGetInverseDisplacementField();
}

void
DisplacementFieldTransform::SetInterpolator(InterpolatorEnum interp)
{
  this->MakeUnique();
  this->m_pfSetInterpolator(interp);
}

// InterpolatorEnum DisplacementFieldTransform::GetInterpolator() const
// {
//   return this->m_pfGetInterpolator();
// }

void
DisplacementFieldTransform::SetSmoothingOff()
{
  this->MakeUnique();
  this->m_pfSetSmoothingOff();
}

void
DisplacementFieldTransform::SetSmoothingGaussianOnUpdate(double varianceForUpdateField, double varianceForTotalField)
{
  this->MakeUnique();
  this->m_pfSetSmoothingGaussianOnUpdate(varianceForUpdateField, varianceForTotalField);
}

void
DisplacementFieldTransform::SetSmoothingBSplineOnUpdate(
  const std::vector<unsigned int> & numberOfControlPointsForUpdateField,
  const std::vector<unsigned int> & numberOfControlPointsForTotalField,
  bool                              enforceStationaryBoundary,
  unsigned int                      order)
{
  this->MakeUnique();
  this->m_pfSetSmoothingBSplineOnUpdate(
    numberOfControlPointsForUpdateField, numberOfControlPointsForTotalField, enforceStationaryBoundary, order);
}


void
DisplacementFieldTransform::SetPimpleTransform(std::unique_ptr<PimpleTransformBase> && pimpleTransform)
{
  Superclass::SetPimpleTransform(std::move(pimpleTransform));
  Self::InternalInitialization(this->GetITKBase());
}

void
DisplacementFieldTransform::InternalInitialization(itk::TransformBase * transform)
{
  MyVisitor visitor;
  visitor.transform = transform;
  visitor.that = this;

  using TransformTypeList = typelist2::typelist<itk::DisplacementFieldTransform<double, 3>,
                                                itk::DisplacementFieldTransform<double, 2>,
                                                itk::BSplineSmoothingOnUpdateDisplacementFieldTransform<double, 3>,
                                                itk::BSplineSmoothingOnUpdateDisplacementFieldTransform<double, 2>,
                                                itk::GaussianSmoothingOnUpdateDisplacementFieldTransform<double, 3>,
                                                itk::GaussianSmoothingOnUpdateDisplacementFieldTransform<double, 2>>;

  typelist2::visit<TransformTypeList> callInternalInitialization;

  // explicitly remove all function pointer with reference to prior transform
  m_pfSetDisplacementField = nullptr;
  m_pfGetDisplacementField = nullptr;
  m_pfSetInverseDisplacementField = nullptr;
  m_pfGetInverseDisplacementField = nullptr;
  m_pfSetInterpolator = nullptr;
  m_pfGetInterpolator = nullptr;
  m_pfSetSmoothingOff = nullptr;
  m_pfSetSmoothingGaussianOnUpdate = nullptr;
  m_pfSetSmoothingBSplineOnUpdate = nullptr;

  callInternalInitialization(visitor);

  if (this->m_pfSetDisplacementField == nullptr)
  {
    sitkExceptionMacro("Transform is not of type " << this->GetName() << "!");
  }
}


template <class TransformType>
void
DisplacementFieldTransform::InternalInitialization(TransformType * t)
{
  this->m_pfSetDisplacementField = [t](auto && PH1) {
    return InternalSetDisplacementField<TransformType>(t, std::forward<decltype(PH1)>(PH1));
  };
  this->m_pfGetDisplacementField = [t] {
    return DisplacementFieldTransform::InternalGetDisplacementField<TransformType>(t);
  };

  this->m_pfSetInverseDisplacementField = [t](auto && PH1) {
    return InternalSetInverseDisplacementField<TransformType>(t, std::forward<decltype(PH1)>(PH1));
  };
  this->m_pfGetInverseDisplacementField = [t] {
    return DisplacementFieldTransform::InternalGetInverseDisplacementField<TransformType>(t);
  };

  this->m_pfSetInterpolator = [t](auto && PH1) {
    return InternalSetInterpolator<TransformType>(t, std::forward<decltype(PH1)>(PH1));
  };

  m_pfSetSmoothingOff = [this, t] { this->InternalSetSmoothingOff(t); };
  m_pfSetSmoothingGaussianOnUpdate = [this, t](auto && PH1, auto && PH2) {
    this->InternalSetSmoothingGaussianOnUpdate(t, std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2));
  };
  m_pfSetSmoothingBSplineOnUpdate = [this, t](auto && PH1, auto && PH2, auto && PH3, auto && PH4) {
    this->InternalSetSmoothingBSplineOnUpdate(t,
                                              std::forward<decltype(PH1)>(PH1),
                                              std::forward<decltype(PH2)>(PH2),
                                              std::forward<decltype(PH3)>(PH3),
                                              std::forward<decltype(PH4)>(PH4));
  };
}

PimpleTransformBase *
DisplacementFieldTransform::CreateDisplacementFieldPimpleTransform(unsigned int dimension)
{
  switch (dimension)
  {
    case 2:
      return new PimpleTransform<itk::DisplacementFieldTransform<double, 2>>();
    case 3:
      return new PimpleTransform<itk::DisplacementFieldTransform<double, 3>>();
    default:
      sitkExceptionMacro("Invalid dimension for transform");
  }
}


template <typename TDisplacementFieldTransform>
Image
DisplacementFieldTransform::InternalGetDisplacementField(const TDisplacementFieldTransform * itkDisplacementTx)
{
  // The returned image references the buffer for the displacement
  // field, but it does not have the correct reference count.
  using DisplacementFieldType = typename TDisplacementFieldTransform::DisplacementFieldType;
  DisplacementFieldType * itkDisplacement =
    const_cast<DisplacementFieldType *>(itkDisplacementTx->GetDisplacementField());
  if (itkDisplacement != nullptr)
  {
    return Image(GetVectorImageFromImage(itkDisplacement));
  }
  return Image(std::vector<unsigned int>(TDisplacementFieldTransform::Dimension, 0), sitkVectorFloat64);
}

template <typename TDisplacementFieldTransform>
Image
DisplacementFieldTransform::InternalGetInverseDisplacementField(const TDisplacementFieldTransform * itkDisplacementTx)
{
  using DisplacementFieldType = typename TDisplacementFieldTransform::DisplacementFieldType;
  DisplacementFieldType * itkDisplacement =
    const_cast<DisplacementFieldType *>(itkDisplacementTx->GetInverseDisplacementField());
  if (itkDisplacement != nullptr)
  {
    return Image(GetVectorImageFromImage(itkDisplacement));
  }
  return Image(std::vector<unsigned int>(TDisplacementFieldTransform::Dimension, 0), sitkVectorFloat64);
}

template <typename TDisplacementFieldTransform>
void
DisplacementFieldTransform::InternalSetSmoothingOff(TDisplacementFieldTransform * itkDisplacement)
{
  // To set smoothing off we make sure that the displacement type is
  // not of a derived type.
  const unsigned int Dimension = TDisplacementFieldTransform::Dimension;

  using ScalarType = typename TDisplacementFieldTransform::ScalarType;
  using NewTransformType = itk::DisplacementFieldTransform<ScalarType, Dimension>;

  // already off don't need to create a new transform
  if (!std::is_same<TDisplacementFieldTransform, NewTransformType>::value)
  {
    typename NewTransformType::Pointer itkNewDisplacement = NewTransformType::New();

    itkNewDisplacement->SetDisplacementField(itkDisplacement->GetModifiableDisplacementField());
    itkNewDisplacement->SetInverseDisplacementField(itkDisplacement->GetModifiableInverseDisplacementField());
    itkNewDisplacement->SetInterpolator(itkDisplacement->GetModifiableInterpolator());
    itkNewDisplacement->SetInverseInterpolator(itkDisplacement->GetModifiableInverseInterpolator());

    this->SetPimpleTransform(std::make_unique<PimpleTransform<NewTransformType>>(itkNewDisplacement));
  }
}

template <typename TDisplacementFieldTransform>
void
DisplacementFieldTransform::InternalSetSmoothingGaussianOnUpdate(TDisplacementFieldTransform * itkDisplacement,
                                                                 double                        varianceForUpdateField,
                                                                 double                        varianceForTotalField)
{
  // To set the smoothing to the Gaussian, we change the type of
  // displacement field transform if need, copying the fields.
  const unsigned int Dimension = TDisplacementFieldTransform::Dimension;
  using ScalarType = typename TDisplacementFieldTransform::ScalarType;
  using NewTransformType = itk::GaussianSmoothingOnUpdateDisplacementFieldTransform<ScalarType, Dimension>;

  typename NewTransformType::Pointer itkNewDisplacement;

  // change the type of the current displace field for the correct update
  if (!std::is_same<TDisplacementFieldTransform, NewTransformType>::value)
  {
    itkNewDisplacement = NewTransformType::New();

    itkNewDisplacement->SetDisplacementField(itkDisplacement->GetModifiableDisplacementField());
    itkNewDisplacement->SetInverseDisplacementField(itkDisplacement->GetModifiableInverseDisplacementField());
    itkNewDisplacement->SetInterpolator(itkDisplacement->GetModifiableInterpolator());
    itkNewDisplacement->SetInverseInterpolator(itkDisplacement->GetModifiableInverseInterpolator());

    this->SetPimpleTransform(std::make_unique<PimpleTransform<NewTransformType>>(itkNewDisplacement));
  }
  else
  {
    itkNewDisplacement = dynamic_cast<NewTransformType *>(itkDisplacement);
  }

  itkNewDisplacement->SetGaussianSmoothingVarianceForTheUpdateField(varianceForUpdateField);
  itkNewDisplacement->SetGaussianSmoothingVarianceForTheTotalField(varianceForTotalField);
}


template <typename TDisplacementFieldTransform>
void
DisplacementFieldTransform::InternalSetSmoothingBSplineOnUpdate(
  TDisplacementFieldTransform *     itkDisplacement,
  const std::vector<unsigned int> & numberOfControlPointsForUpdateField,
  const std::vector<unsigned int> & numberOfControlPointsForTotalField,
  bool                              enforceStationaryBoundary,
  unsigned int                      order)
{

  // To set the smoothing to the Gaussian, we change the type of
  // displacement field transform if need, copying the fields.
  const unsigned int Dimension = TDisplacementFieldTransform::Dimension;
  using ScalarType = typename TDisplacementFieldTransform::ScalarType;
  using NewTransformType = itk::BSplineSmoothingOnUpdateDisplacementFieldTransform<ScalarType, Dimension>;

  typename NewTransformType::Pointer itkNewDisplacement;

  // change the type of the current displace field for the correct update
  if (!std::is_same<TDisplacementFieldTransform, NewTransformType>::value)
  {
    itkNewDisplacement = NewTransformType::New();

    itkNewDisplacement->SetDisplacementField(itkDisplacement->GetModifiableDisplacementField());
    itkNewDisplacement->SetInverseDisplacementField(itkDisplacement->GetModifiableInverseDisplacementField());
    itkNewDisplacement->SetInterpolator(itkDisplacement->GetModifiableInterpolator());
    itkNewDisplacement->SetInverseInterpolator(itkDisplacement->GetModifiableInverseInterpolator());

    this->SetPimpleTransform(std::make_unique<PimpleTransform<NewTransformType>>(itkNewDisplacement));
  }
  else
  {
    itkNewDisplacement = dynamic_cast<NewTransformType *>(itkDisplacement);
  }
  using ArrayType = typename NewTransformType::ArrayType;
  itkNewDisplacement->SetNumberOfControlPointsForTheUpdateField(
    sitkSTLVectorToITK<ArrayType>(numberOfControlPointsForUpdateField));
  itkNewDisplacement->SetNumberOfControlPointsForTheTotalField(
    sitkSTLVectorToITK<ArrayType>(numberOfControlPointsForTotalField));
  itkNewDisplacement->SetEnforceStationaryBoundary(enforceStationaryBoundary);
  itkNewDisplacement->SetSplineOrder(order);
}


} // namespace itk::simple
