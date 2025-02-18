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
#ifndef sitkPimpleImageBase_hxx
#define sitkPimpleImageBase_hxx

#include "sitkPimpleImageBase.h"
#include "sitkMemberFunctionFactory.h"
#include "sitkConditional.h"
#include "sitkCreateInterpolator.hxx"
#include "sitkImageConvert.hxx"

#include "itkImage.h"
#include "itkVectorImage.h"
#include "itkLabelMap.h"
#include "itkImageDuplicator.h"
#include "itkConvertLabelMapFilter.h"


#include <type_traits>

namespace itk::simple
{

///
/// Private name space for a concrete implementation of pimple image
/// for a specific image types with dimensions and pixel types
///
namespace
{

template <typename T>
struct ValuePixelType;

template <typename T, unsigned int D>
struct ValuePixelType<itk::VectorImage<T, D>>
{
  using ValueType = typename itk::VectorImage<T, D>::PixelType::ValueType;
};

template <typename T, unsigned int D>
struct ValuePixelType<itk::Image<T, D>>
{
  using ValueType = typename itk::Image<T, D>::PixelType;
};

template <typename T>
struct ValuePixelType<itk::LabelMap<T>>
{
  using ValueType = typename itk::LabelMap<T>::PixelType;
};

template <class TImageType>
class PimpleImage : public PimpleImageBase
{
public:
  using Self = PimpleImage;
  using ImageType = TImageType;
  using ImagePointer = typename ImageType::Pointer;
  using IndexType = typename ImageType::IndexType;
  using PixelType = typename ImageType::PixelType;
  using ValuePixelType = typename ValuePixelType<ImageType>::ValueType;

  PimpleImage(ImageType * image)
    : m_Image(image)
  {
    static_assert(ImageType::ImageDimension <= SITK_MAX_DIMENSION && ImageType::ImageDimension >= 2,
                  "Image Dimension out of range");
    static_assert(ImageTypeToPixelIDValue<ImageType>::Result != (int)sitkUnknown, "invalid pixel type");

    if (image == nullptr)
    {
      sitkExceptionMacro(<< "Unable to initialize an image with nullptr");
    }

    if (image->GetLargestPossibleRegion() != image->GetBufferedRegion())
    {
      sitkExceptionMacro(<< "The image has a LargestPossibleRegion of " << image->GetLargestPossibleRegion()
                         << " while the buffered region is " << image->GetBufferedRegion() << std::endl
                         << "SimpleITK does not support streaming or unbuffered regions!");
    }

    if constexpr (!IsLabel<ImageType>::Value)
    {
      auto container = image->GetPixelContainer();
      if (container->GetReferenceCount() != 1)
      {
        sitkExceptionMacro(<< "The image pixel container is shared by other resources and presents aliasing issue.");
      }
    }

    const IndexType & idx = image->GetBufferedRegion().GetIndex();
    for (unsigned int i = 0; i < ImageType::ImageDimension; ++i)
    {
      if (idx[i] != 0)
      {
        sitkExceptionMacro(<< "The image has a staring index of " << idx
                           << "SimpleITK only supports images with a zero starting index!");
      }
    }
  }

  std::unique_ptr<PimpleImageBase>
  ShallowCopy() const override
  {
    return std::make_unique<Self>(this->m_Image.GetPointer());
  }

  std::unique_ptr<PimpleImageBase>
  DeepCopy() const override
  {
    if constexpr (IsLabel<TImageType>::Value)
    {
      using FilterType = itk::ConvertLabelMapFilter<TImageType, TImageType>;
      typename FilterType::Pointer filter = FilterType::New();
      filter->SetInput(this->m_Image);
      filter->UpdateLargestPossibleRegion();
      ImagePointer output = filter->GetOutput();

      return std::make_unique<Self>(output.GetPointer());
    }
    else
    {
      using ImageDuplicatorType = itk::ImageDuplicator<ImageType>;
      typename ImageDuplicatorType::Pointer dup = ImageDuplicatorType::New();

      dup->SetInputImage(this->m_Image);
      dup->Update();
      ImagePointer output = dup->GetOutput();

      return std::make_unique<Self>(output.GetPointer());
    }
  }

  std::unique_ptr<PimpleImageBase>
  ProxyCopy() override
  {
    if constexpr (IsLabel<TImageType>::Value)
    {
      sitkExceptionMacro("ProxyCopy for inplace operations is not supported for label pixel types.");
    }
    else
    {

      auto oldBuffer = this->m_Image->GetPixelContainer();

      auto itkImage = TImageType::New();
      itkImage->CopyInformation(this->m_Image);
      itkImage->SetBufferedRegion(this->m_Image->GetBufferedRegion());
      itkImage->SetLargestPossibleRegion(this->m_Image->GetLargestPossibleRegion());
      {
        auto buffer = TImageType::PixelContainer::New();
        buffer->SetImportPointer(oldBuffer->GetImportPointer(), oldBuffer->Capacity(), false);
        itkImage->SetPixelContainer(buffer);
      }
      return std::make_unique<Self>(itkImage.GetPointer());
    }
  }


  itk::DataObject *
  GetDataBase() override
  {
    return this->m_Image.GetPointer();
  }
  const itk::DataObject *
  GetDataBase() const override
  {
    return this->m_Image.GetPointer();
  }

  PixelIDValueEnum
  GetPixelID() const noexcept override
  {
    // The constructor ensures that we have a valid image
    // this maps the Image's pixel type to the array index
    return static_cast<PixelIDValueEnum>(ImageTypeToPixelIDValue<ImageType>::Result);
  }

  unsigned int
  GetDimension() const override
  {
    return ImageType::ImageDimension;
  }


  unsigned int
  GetNumberOfComponentsPerPixel() const override
  {
    if constexpr (IsVector<TImageType>::Value)
    {
      return this->m_Image->GetNumberOfComponentsPerPixel();
    }
    return 1;
  }

  // Get Origin
  std::vector<double>
  GetOrigin() const override
  {
    return sitkITKVectorToSTL<double>(this->m_Image->GetOrigin());
  }

  // Set Origin
  void
  SetOrigin(const std::vector<double> & orgn) override
  {
    this->m_Image->SetOrigin(sitkSTLVectorToITK<typename ImageType::PointType>(orgn));
  }

  // Get Spacing
  std::vector<double>
  GetSpacing() const override
  {
    return sitkITKVectorToSTL<double>(this->m_Image->GetSpacing());
  }

  // Set Spacing
  void
  SetSpacing(const std::vector<double> & spc) override
  {
    this->m_Image->SetSpacing(sitkSTLVectorToITK<typename ImageType::SpacingType>(spc));
  }


  // Get Direction
  std::vector<double>
  GetDirection() const override
  {
    return sitkITKDirectionToSTL(this->m_Image->GetDirection());
  }

  // Set Direction
  void
  SetDirection(const std::vector<double> & in) override
  {
    this->m_Image->SetDirection(sitkSTLToITKDirection<typename ImageType::DirectionType>(in));
  }


  // Physical Point to Index
  std::vector<int64_t>
  TransformPhysicalPointToIndex(const std::vector<double> & pt) const override
  {
    if (pt.size() != ImageType::ImageDimension)
    {
      sitkExceptionMacro("vector dimension mismatch");
    }


    typename ImageType::IndexType index =
      this->m_Image->TransformPhysicalPointToIndex(sitkSTLVectorToITK<typename ImageType::PointType>(pt));

    return sitkITKVectorToSTL<int64_t>(index);
  }

  // Index to Physical Point
  std::vector<double>
  TransformIndexToPhysicalPoint(const std::vector<int64_t> & idx) const override
  {

    if (idx.size() != ImageType::ImageDimension)
    {
      sitkExceptionMacro("vector dimension mismatch");
    }

    typename ImageType::IndexType index;
    for (unsigned int i = 0; i < ImageType::ImageDimension; ++i)
    {
      index[i] = idx[i];
    }


    typename ImageType::PointType point = this->m_Image->template TransformIndexToPhysicalPoint<double>(index);
    return sitkITKVectorToSTL<double>(point);
  }

  //  Physical Point To Continuous Index
  std::vector<double>
  TransformPhysicalPointToContinuousIndex(const std::vector<double> & pt) const override
  {
    if (pt.size() != ImageType::ImageDimension)
    {
      sitkExceptionMacro("vector dimension mismatch");
    }

    auto index = this->m_Image->template TransformPhysicalPointToContinuousIndex<double>(
      sitkSTLVectorToITK<typename ImageType::PointType>(pt));

    return sitkITKVectorToSTL<double>(index);
  }

  // Continuous Index to Physical Point
  std::vector<double>
  TransformContinuousIndexToPhysicalPoint(const std::vector<double> & idx) const override
  {
    if (idx.size() != ImageType::ImageDimension)
    {
      sitkExceptionMacro("vector dimension mismatch");
    }


    typename itk::ContinuousIndex<double, ImageType::ImageDimension> index;
    for (unsigned int i = 0; i < ImageType::ImageDimension; ++i)
    {
      index[i] = idx[i];
    }

    typename ImageType::PointType point =
      this->m_Image->template TransformContinuousIndexToPhysicalPoint<double>(index);

    return sitkITKVectorToSTL<double>(point);
  }

  std::vector<double>
  EvaluateAtContinuousIndex(const std::vector<double> & index, [[maybe_unused]] InterpolatorEnum interp) const override
  {
    if constexpr (IsLabel<ImageType>::Value)
    {
      sitkExceptionMacro("Interpolation is not supported for label pixel types.")
    }
    else
    {
      auto cidx = sitkSTLVectorToITK<itk::ContinuousIndex<double, ImageType::ImageDimension>>(index);
      if (!this->m_Image->GetLargestPossibleRegion().IsInside(cidx))
      {
        sitkExceptionMacro("index out of bounds");
      }

      auto itkInterpolator = CreateInterpolator(this->m_Image.GetPointer(), interp);
      if (itkInterpolator == nullptr)
      {
        sitkExceptionMacro("Interpolator type \"" << interp << "\" does not support "
                                                  << GetPixelIDValueAsString(this->GetPixelID()))
      }
      itkInterpolator->SetInputImage(this->m_Image.GetPointer());
      auto result = itkInterpolator->EvaluateAtContinuousIndex(cidx);
      if constexpr (IsVector<ImageType>::Value)
      {
        return std::vector<double>{ result.GetDataPointer(), result.GetDataPointer() + result.Size() };
      }
      else if constexpr (typelist2::has_type<ComplexPixelIDTypeList,
                                             typename ImageTypeToPixelID<ImageType>::PixelIDType>::value)
      {
        return { { double(result.real()), double(result.imag()) } };
      }
      else
      {
        return std::vector<double>(1, double(result));
      }
    }
  }

  unsigned int
  GetSize(unsigned int dimension) const override
  {
    if (dimension > ImageType::ImageDimension - 1)
    {
      return 0;
    }

    typename ImageType::RegionType largestRegion = this->m_Image->GetLargestPossibleRegion();
    return largestRegion.GetSize(dimension);
  }

  std::vector<unsigned int>
  GetSize() const override
  {
    typename ImageType::RegionType largestRegion = this->m_Image->GetLargestPossibleRegion();
    std::vector<unsigned int>      size(ImageType::ImageDimension);

    return sitkITKVectorToSTL<unsigned int>(largestRegion.GetSize());
  }


  bool
  IsCongruentImageGeometry(const PimpleImageBase * otherImage,
                           double                  coordinateTolerance,
                           double                  directionTolerance) const override
  {
    auto other = dynamic_cast<const itk::ImageBase<ImageType::ImageDimension> *>(otherImage->GetDataBase());
    if (other == nullptr)
    {
      return false;
    }

    return this->m_Image->IsCongruentImageGeometry(other, coordinateTolerance, directionTolerance);
  }

  bool
  IsSameImageGeometryAs(const PimpleImageBase * otherImage,
                        double                  coordinateTolerance,
                        double                  directionTolerance) const override
  {
    auto other = dynamic_cast<const itk::ImageBase<ImageType::ImageDimension> *>(otherImage->GetDataBase());
    if (other == nullptr)
    {
      return false;
    }

    return this->m_Image->IsSameImageGeometryAs(other, coordinateTolerance, directionTolerance);
  }


  uint64_t
  GetNumberOfPixels() const override
  {
    return this->m_Image->GetLargestPossibleRegion().GetNumberOfPixels();
  }

  std::string
  ToString() const override
  {
    std::ostringstream out;
    this->m_Image->Print(out);
    return out.str();
  }

  int
  GetReferenceCountOfImage() const override
  {
    return this->m_Image->GetReferenceCount();
  }

  int8_t
  GetPixelAsInt8(const std::vector<uint32_t> & idx) const override
  {
    return this->InternalGetPixelAs<int8_t>(idx);
  }
  uint8_t
  GetPixelAsUInt8(const std::vector<uint32_t> & idx) const override
  {
    return this->InternalGetPixelAs<uint8_t>(idx);
  }
  int16_t
  GetPixelAsInt16(const std::vector<uint32_t> & idx) const override
  {
    return this->InternalGetPixelAs<int16_t>(idx);
  }
  uint16_t
  GetPixelAsUInt16(const std::vector<uint32_t> & idx) const override
  {
    return this->InternalGetPixelAs<uint16_t>(idx);
  }
  int32_t
  GetPixelAsInt32(const std::vector<uint32_t> & idx) const override
  {
    return this->InternalGetPixelAs<int32_t>(idx);
  }
  uint32_t
  GetPixelAsUInt32(const std::vector<uint32_t> & idx) const override
  {
    return this->InternalGetPixelAs<uint32_t>(idx);
  }
  int64_t
  GetPixelAsInt64(const std::vector<uint32_t> & idx) const override
  {
    return this->InternalGetPixelAs<int64_t>(idx);
  }
  uint64_t
  GetPixelAsUInt64(const std::vector<uint32_t> & idx) const override
  {
    return this->InternalGetPixelAs<uint64_t>(idx);
  }
  float
  GetPixelAsFloat(const std::vector<uint32_t> & idx) const override
  {
    return this->InternalGetPixelAs<float>(idx);
  }
  double
  GetPixelAsDouble(const std::vector<uint32_t> & idx) const override
  {
    return this->InternalGetPixelAs<double>(idx);
  }
  std::vector<int8_t>
  GetPixelAsVectorInt8(const std::vector<uint32_t> & idx) const override
  {
    return this->InternalGetPixelAs<std::vector<int8_t>>(idx);
  }
  std::vector<uint8_t>
  GetPixelAsVectorUInt8(const std::vector<uint32_t> & idx) const override
  {
    return this->InternalGetPixelAs<std::vector<uint8_t>>(idx);
  }
  std::vector<int16_t>
  GetPixelAsVectorInt16(const std::vector<uint32_t> & idx) const override
  {
    return this->InternalGetPixelAs<std::vector<int16_t>>(idx);
  }
  std::vector<uint16_t>
  GetPixelAsVectorUInt16(const std::vector<uint32_t> & idx) const override
  {
    return this->InternalGetPixelAs<std::vector<uint16_t>>(idx);
  }
  std::vector<int32_t>
  GetPixelAsVectorInt32(const std::vector<uint32_t> & idx) const override
  {
    return this->InternalGetPixelAs<std::vector<int32_t>>(idx);
  }
  std::vector<uint32_t>
  GetPixelAsVectorUInt32(const std::vector<uint32_t> & idx) const override
  {
    return this->InternalGetPixelAs<std::vector<uint32_t>>(idx);
  }
  std::vector<int64_t>
  GetPixelAsVectorInt64(const std::vector<uint32_t> & idx) const override
  {
    return this->InternalGetPixelAs<std::vector<int64_t>>(idx);
  }
  std::vector<uint64_t>
  GetPixelAsVectorUInt64(const std::vector<uint32_t> & idx) const override
  {
    return this->InternalGetPixelAs<std::vector<uint64_t>>(idx);
  }
  std::vector<float>
  GetPixelAsVectorFloat32(const std::vector<uint32_t> & idx) const override
  {
    return this->InternalGetPixelAs<std::vector<float>>(idx);
  }
  std::vector<double>
  GetPixelAsVectorFloat64(const std::vector<uint32_t> & idx) const override
  {
    return this->InternalGetPixelAs<std::vector<double>>(idx);
  }
  std::complex<float>
  GetPixelAsComplexFloat32(const std::vector<uint32_t> & idx) const override
  {
    return this->InternalGetPixelAs<std::complex<float>>(idx);
  }
  std::complex<double>
  GetPixelAsComplexFloat64(const std::vector<uint32_t> & idx) const override
  {
    return this->InternalGetPixelAs<std::complex<double>>(idx);
  }

  int8_t *
  GetBufferAsInt8() override
  {
    return this->InternalGetBufferAs<int8_t>();
  }
  uint8_t *
  GetBufferAsUInt8() override
  {
    return this->InternalGetBufferAs<uint8_t>();
  }
  int16_t *
  GetBufferAsInt16() override
  {
    return this->InternalGetBufferAs<int16_t>();
  }
  uint16_t *
  GetBufferAsUInt16() override
  {
    return this->InternalGetBufferAs<uint16_t>();
  }
  int32_t *
  GetBufferAsInt32() override
  {
    return this->InternalGetBufferAs<int32_t>();
  }
  uint32_t *
  GetBufferAsUInt32() override
  {
    return this->InternalGetBufferAs<uint32_t>();
  }
  int64_t *
  GetBufferAsInt64() override
  {
    return this->InternalGetBufferAs<int64_t>();
  }
  uint64_t *
  GetBufferAsUInt64() override
  {
    return this->InternalGetBufferAs<uint64_t>();
  }
  float *
  GetBufferAsFloat() override
  {
    return this->InternalGetBufferAs<float>();
  }
  double *
  GetBufferAsDouble() override
  {
    return this->InternalGetBufferAs<double>();
  }
  void *
  GetBufferAsVoid() override
  {
    return this->InternalGetBufferAs<ValuePixelType>();
  }

  const int8_t *
  GetBufferAsInt8() const override
  {
    return this->InternalGetBufferAs<int8_t>();
  }
  const uint8_t *
  GetBufferAsUInt8() const override
  {
    return this->InternalGetBufferAs<uint8_t>();
  }
  const int16_t *
  GetBufferAsInt16() const override
  {
    return this->InternalGetBufferAs<int16_t>();
  }
  const uint16_t *
  GetBufferAsUInt16() const override
  {
    return this->InternalGetBufferAs<uint16_t>();
  }
  const int32_t *
  GetBufferAsInt32() const override
  {
    return this->InternalGetBufferAs<int32_t>();
  }
  const uint32_t *
  GetBufferAsUInt32() const override
  {
    return this->InternalGetBufferAs<uint32_t>();
  }
  const int64_t *
  GetBufferAsInt64() const override
  {
    return this->InternalGetBufferAs<int64_t>();
  }
  const uint64_t *
  GetBufferAsUInt64() const override
  {
    return this->InternalGetBufferAs<uint64_t>();
  }
  const float *
  GetBufferAsFloat() const override
  {
    return this->InternalGetBufferAs<float>();
  }
  const double *
  GetBufferAsDouble() const override
  {
    return this->InternalGetBufferAs<double>();
  }
  const void *
  GetBufferAsVoid() const override
  {
    return this->InternalGetBufferAs<ValuePixelType>();
  }


  void
  SetPixelAsInt8(const std::vector<uint32_t> & idx, int8_t v) override
  {
    InternalSetPixelAs<int8_t>(idx, v);
  }
  void
  SetPixelAsUInt8(const std::vector<uint32_t> & idx, uint8_t v) override
  {
    InternalSetPixelAs<uint8_t>(idx, v);
  }
  void
  SetPixelAsInt16(const std::vector<uint32_t> & idx, int16_t v) override
  {
    InternalSetPixelAs<int16_t>(idx, v);
  }
  void
  SetPixelAsUInt16(const std::vector<uint32_t> & idx, uint16_t v) override
  {
    InternalSetPixelAs<uint16_t>(idx, v);
  }
  void
  SetPixelAsInt32(const std::vector<uint32_t> & idx, int32_t v) override
  {
    InternalSetPixelAs<int32_t>(idx, v);
  }
  void
  SetPixelAsUInt32(const std::vector<uint32_t> & idx, uint32_t v) override
  {
    InternalSetPixelAs<uint32_t>(idx, v);
  }
  void
  SetPixelAsInt64(const std::vector<uint32_t> & idx, int64_t v) override
  {
    InternalSetPixelAs<int64_t>(idx, v);
  }
  void
  SetPixelAsUInt64(const std::vector<uint32_t> & idx, uint64_t v) override
  {
    InternalSetPixelAs<uint64_t>(idx, v);
  }
  void
  SetPixelAsFloat(const std::vector<uint32_t> & idx, float v) override
  {
    InternalSetPixelAs<float>(idx, v);
  }
  void
  SetPixelAsDouble(const std::vector<uint32_t> & idx, double v) override
  {
    InternalSetPixelAs<double>(idx, v);
  }
  void
  SetPixelAsVectorInt8(const std::vector<uint32_t> & idx, const std::vector<int8_t> & v) override
  {
    InternalSetPixelAs<std::vector<int8_t>>(idx, v);
  }
  void
  SetPixelAsVectorUInt8(const std::vector<uint32_t> & idx, const std::vector<uint8_t> & v) override
  {
    InternalSetPixelAs<std::vector<uint8_t>>(idx, v);
  }
  void
  SetPixelAsVectorInt16(const std::vector<uint32_t> & idx, const std::vector<int16_t> & v) override
  {
    InternalSetPixelAs<std::vector<int16_t>>(idx, v);
  }
  void
  SetPixelAsVectorUInt16(const std::vector<uint32_t> & idx, const std::vector<uint16_t> & v) override
  {
    InternalSetPixelAs<std::vector<uint16_t>>(idx, v);
  }
  void
  SetPixelAsVectorInt32(const std::vector<uint32_t> & idx, const std::vector<int32_t> & v) override
  {
    InternalSetPixelAs<std::vector<int32_t>>(idx, v);
  }
  void
  SetPixelAsVectorUInt32(const std::vector<uint32_t> & idx, const std::vector<uint32_t> & v) override
  {
    InternalSetPixelAs<std::vector<uint32_t>>(idx, v);
  }
  void
  SetPixelAsVectorInt64(const std::vector<uint32_t> & idx, const std::vector<int64_t> & v) override
  {
    InternalSetPixelAs<std::vector<int64_t>>(idx, v);
  }
  void
  SetPixelAsVectorUInt64(const std::vector<uint32_t> & idx, const std::vector<uint64_t> & v) override
  {
    InternalSetPixelAs<std::vector<uint64_t>>(idx, v);
  }
  void
  SetPixelAsVectorFloat32(const std::vector<uint32_t> & idx, const std::vector<float> & v) override
  {
    InternalSetPixelAs<std::vector<float>>(idx, v);
  }
  void
  SetPixelAsVectorFloat64(const std::vector<uint32_t> & idx, const std::vector<double> & v) override
  {
    InternalSetPixelAs<std::vector<double>>(idx, v);
  }
  void
  SetPixelAsComplexFloat32(const std::vector<uint32_t> & idx, const std::complex<float> v) override
  {
    InternalSetPixelAs<std::complex<float>>(idx, v);
  }
  void
  SetPixelAsComplexFloat64(const std::vector<uint32_t> & idx, const std::complex<double> v) override
  {
    InternalSetPixelAs<std::complex<double>>(idx, v);
  }

protected:
  IndexType
  GetIndex(const std::vector<uint32_t> & idx) const
  {
    auto itkIdx = sitkSTLVectorToITK<IndexType>(idx);
    if (!m_Image->GetLargestPossibleRegion().IsInside(itkIdx))
    {
      sitkExceptionMacro("index out of bounds");
    }

    return itkIdx;
  };

  template <typename TReturn>
  TReturn
  InternalGetPixelAs(const std::vector<uint32_t> & idx) const
  {

    if constexpr (IsLabel<ImageType>::Value && std::is_same<ValuePixelType, TReturn>::value)
    {
      return this->m_Image->GetPixel(GetIndex(idx));
    }
    else if constexpr (IsBasic<ImageType>::Value && std::is_same<ValuePixelType, TReturn>::value)
    {
      return this->m_Image->GetPixel(GetIndex(idx));
    }
    else if constexpr (IsVector<ImageType>::Value && std::is_same<std::vector<ValuePixelType>, TReturn>::value)
    {
      const typename ImageType::PixelType px = this->m_Image->GetPixel(GetIndex(idx));
      return std::vector<typename ImageType::InternalPixelType>(&px[0], &px[px.GetSize()]);
    }
    else
    {
      sitkExceptionMacro(<< "The image is of type: " << GetPixelIDValueAsString(this->GetPixelID())
                         << " but the GetPixel access method does not match the type!");
    }
  }


  template <typename TReturn>
  TReturn *
  InternalGetBufferAs() const
  {

    if constexpr (IsLabel<ImageType>::Value)
    {
      sitkExceptionMacro("This method is not supported for LabelMaps.")
    }
    else if constexpr (IsBasic<ImageType>::Value && std::is_same<ValuePixelType, TReturn>::value)
    {
      return this->m_Image->GetPixelContainer()->GetBufferPointer();
    }
    else if constexpr (IsBasic<ImageType>::Value && std::is_same<ValuePixelType, std::complex<TReturn>>::value)
    {
      return reinterpret_cast<TReturn *>(this->m_Image->GetPixelContainer()->GetBufferPointer());
    }
    else if constexpr (IsVector<ImageType>::Value && std::is_same<ValuePixelType, TReturn>::value)
    {
      return this->m_Image->GetPixelContainer()->GetBufferPointer();
    }
    else
    {
      sitkExceptionMacro(<< "The image is of type: " << GetPixelIDValueAsString(this->GetPixelID())
                         << " but the GetBuffer access method does not match the type!");
    }
  }

  template <typename TPixelType>
  void
  InternalSetPixelAs(const std::vector<uint32_t> & idx, [[maybe_unused]] const TPixelType v) const
  {


    if constexpr (IsLabel<ImageType>::Value && std::is_same<ValuePixelType, TPixelType>::value)
    {
      return this->m_Image->SetPixel(GetIndex(idx), v);
    }
    else if constexpr (IsBasic<ImageType>::Value && std::is_same<ValuePixelType, TPixelType>::value)
    {
      return this->m_Image->SetPixel(GetIndex(idx), v);
    }
    else if constexpr (IsVector<ImageType>::Value && std::is_same<std::vector<ValuePixelType>, TPixelType>::value)
    {
      typename ImageType::PixelType px = this->m_Image->GetPixel(GetIndex(idx));

      if (px.GetSize() != v.size())
      {
        sitkExceptionMacro(<< "Unable to convert vector to ITK pixel type\n"
                           << "Expected vector of length " << px.GetSize() << " but only got " << v.size()
                           << " elements.");
      }

      std::copy(v.begin(), v.end(), &px[0]);
    }
    else
    {
      sitkExceptionMacro(<< "The image is of type: " << GetPixelIDValueAsString(this->GetPixelID())
                         << " does not match the type of SetPixel method called.");
    }
  }


private:
  ImagePointer m_Image;
};

} // namespace

} // namespace itk::simple

#endif // sitkPimpleImageBase_hxx
