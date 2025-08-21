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
#ifdef _MSC_VER
#  pragma warning(disable : 4996)
#endif

#include "sitkImageSeriesReader.h"

#include <itkImageIOBase.h>
#include <itkImageSeriesReader.h>

#include <memory>

#include "itkGDCMSeriesFileNames.h"
#include "sitkMetaDataDictionaryCustomCast.hxx"

namespace itk::simple
{

const detail::MemberFunctionFactory<ImageSeriesReader::MemberFunctionType> &
ImageSeriesReader::GetMemberFunctionFactory()
{
  static const auto static_factory = []() SITK_CONSTEVAL {
    detail::MemberFunctionFactory<MemberFunctionType> factory;

    using PixelIDTypeList = NonLabelPixelIDTypeList;
    factory.RegisterMemberFunctions<PixelIDTypeList, 2, SITK_MAX_DIMENSION>();
    return factory;
  }();
  return static_factory;
}

Image
ReadImage(const std::vector<PathType> & filenames, PixelIDValueEnum outputPixelType, const std::string & imageIO)
{
  ImageSeriesReader reader;
  reader.SetFileNames(filenames);
  reader.SetOutputPixelType(outputPixelType);
  reader.SetImageIO(imageIO);
  return reader.Execute();
}


std::vector<PathType>
ImageSeriesReader::GetGDCMSeriesFileNames(const PathType &    directory,
                                          const std::string & seriesID,
                                          bool                useSeriesDetails,
                                          bool                recursive,
                                          bool                loadSequences)
{
  GDCMSeriesFileNames::Pointer gdcmSeries = GDCMSeriesFileNames::New();

  // SetRecursive must be called before SetInputDirectory
  gdcmSeries->SetRecursive(recursive);
  gdcmSeries->SetInputDirectory(directory);
  gdcmSeries->SetUseSeriesDetails(useSeriesDetails);
  gdcmSeries->SetLoadSequences(loadSequences);
  // Skip private tags. Loading DICOM files is faster when private tags are not needed.
  gdcmSeries->SetLoadPrivateTags(false);

  gdcmSeries->Update();

  auto filenames = gdcmSeries->GetFileNames(seriesID);
  return std::vector<PathType>(filenames.begin(), filenames.end());
}

std::vector<std::string>
ImageSeriesReader::GetGDCMSeriesIDs(const PathType & directory, bool useSeriesDetails)
{
  GDCMSeriesFileNames::Pointer gdcmSeries = GDCMSeriesFileNames::New();

  gdcmSeries->SetInputDirectory(directory);
  gdcmSeries->SetUseSeriesDetails(useSeriesDetails);
  return gdcmSeries->GetSeriesUIDs();
}

double
ImageSeriesReader::GetSpacingWarningRelThreshold() const
{
  return m_SpacingWarningRelThreshold;
}

void
ImageSeriesReader::SetSpacingWarningRelThreshold(double spacingWarningRelThreshold)
{
  m_SpacingWarningRelThreshold = spacingWarningRelThreshold;
}

void
ImageSeriesReader::SetForceOrthogonalDirection(bool forceOrthogonalDirection)
{
  this->m_ForceOrthogonalDirection = forceOrthogonalDirection;
}

bool
ImageSeriesReader::GetForceOrthogonalDirection() const
{
  return this->m_ForceOrthogonalDirection;
}

void
ImageSeriesReader::ForceOrthogonalDirectionOn()
{
  this->SetForceOrthogonalDirection(true);
}

void
ImageSeriesReader::ForceOrthogonalDirectionOff()
{
  this->SetForceOrthogonalDirection(false);
}

void
ImageSeriesReader::SetReverseOrder(bool reverseOrder)
{
  this->m_ReverseOrder = reverseOrder;
}

bool
ImageSeriesReader::GetReverseOrder() const
{
  return this->m_ReverseOrder;
}

void
ImageSeriesReader::ReverseOrderOn()
{
  this->SetReverseOrder(true);
}

void
ImageSeriesReader::ReverseOrderOff()
{
  this->SetReverseOrder(false);
}

ImageSeriesReader::ImageSeriesReader() = default;

ImageSeriesReader::~ImageSeriesReader() = default;

std::string
ImageSeriesReader::ToString() const
{

  std::ostringstream out;
  out << "itk::simple::ImageSeriesReader";
  out << std::endl;

  out << "  FileNames:" << std::endl;
  for (auto name : m_FileNames)
  {
    out << "    \"" << name << "\"" << std::endl;
  }

  out << "  SpacingWarningRelThreshold: " << m_SpacingWarningRelThreshold << std::endl;
  out << "  MetaDataDictionaryArrayUpdate: ";
  this->ToStringHelper(out, m_MetaDataDictionaryArrayUpdate) << std::endl;
  out << "  ForceOrthogonalDirection: ";
  this->ToStringHelper(out, m_ForceOrthogonalDirection) << std::endl;
  out << "  ReverseOrder: ";
  this->ToStringHelper(out, m_ReverseOrder) << std::endl;


  out << ImageReaderBase::ToString();
  return out.str();
}

void
ImageSeriesReader::SetFileNames(const std::vector<PathType> & filenames)
{
  this->m_FileNames = filenames;
}

const std::vector<PathType> &
ImageSeriesReader::GetFileNames() const
{
  return this->m_FileNames;
}

Image
ImageSeriesReader::Execute()
{
  if (this->m_FileNames.empty())
  {
    sitkExceptionMacro("File names information is empty. Cannot read series.");
  }


  PixelIDValueType type = this->GetOutputPixelType();
  unsigned int     dimension = 0;


  itk::ImageIOBase::Pointer imageio = this->GetImageIOBase(this->m_FileNames.front());
  if (type == sitkUnknown)
  {
    this->GetPixelIDFromImageIO(imageio, type, dimension);
  }
  else
  {
    PixelIDValueType unused;
    this->GetPixelIDFromImageIO(imageio, unused, dimension);
  }

  // increment for series
  ++dimension;

  if (dimension == 4)
  {
    unsigned int size = this->GetDimensionFromImageIO(imageio, 2);
    if (size == 1)
    {
      --dimension;
    }
  }

  if (dimension < 2 || dimension > SITK_MAX_DIMENSION)
  {
    sitkExceptionMacro("The file in the series have unsupported " << dimension - 1 << " dimensions.");
  }

  if (!GetMemberFunctionFactory().HasMemberFunction(type, dimension))
  {
    sitkExceptionMacro(<< "PixelType is not supported!" << std::endl
                       << "Pixel Type: " << GetPixelIDValueAsString(type) << std::endl
                       << "Refusing to load! " << std::endl);
  }

  return GetMemberFunctionFactory().GetMemberFunction(type, dimension, this)(imageio);
}


template <class TImageType>
Image
ImageSeriesReader::ExecuteInternal(itk::ImageIOBase * imageio)
{

  using ImageType = TImageType;
  using Reader = itk::ImageSeriesReader<ImageType>;

  // if the IsInstantiated is correctly implemented this should
  // not occur
  assert(ImageTypeToPixelIDValue<ImageType>::Result != (int)sitkUnknown);
  assert(imageio != nullptr);
  typename Reader::Pointer reader = Reader::New();
  reader->SetImageIO(imageio);
  reader->SetFileNames(std::vector<std::string>(this->m_FileNames.begin(), this->m_FileNames.end()));
  reader->SetSpacingWarningRelThreshold(m_SpacingWarningRelThreshold);
  reader->SetForceOrthogonalDirection(m_ForceOrthogonalDirection);
  reader->SetReverseOrder(m_ReverseOrder);
  // save some computation by not updating this unneeded data-structure
  reader->SetMetaDataDictionaryArrayUpdate(m_MetaDataDictionaryArrayUpdate);

  // release the old filter ( and output data )
  this->m_pfGetMetaDataKeys = nullptr;
  this->m_pfHasMetaDataKey = nullptr;
  this->m_pfGetMetaData = nullptr;
  this->m_Filter = nullptr;


  this->PreUpdate(reader.GetPointer());

  if (m_MetaDataDictionaryArrayUpdate)
  {
    this->m_Filter.reset(reader);
    this->m_Filter->Register();
    this->m_pfGetMetaDataKeys = [capture0 = reader.GetPointer()](auto && PH1) {
      return GetMetaDataKeysCustomCast<Reader>::CustomCast(capture0, std::forward<decltype(PH1)>(PH1));
    };
    this->m_pfHasMetaDataKey = [capture0 = reader.GetPointer()](auto && PH1, auto && PH2) {
      return HasMetaDataKeyCustomCast<Reader>::CustomCast(
        capture0, std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2));
    };
    this->m_pfGetMetaData = [capture0 = reader.GetPointer()](auto && PH1, auto && PH2) {
      return GetMetaDataCustomCast<Reader>::CustomCast(
        capture0, std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2));
    };
  }

  reader->Update();

  return Image(reader->GetOutput());
}

} // namespace itk::simple
