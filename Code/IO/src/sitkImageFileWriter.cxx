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

#include "sitkImageFileWriter.h"
#include "sitkImageIOUtilities.h"

#include <itkImageIOBase.h>
#include <itkImageFileWriter.h>
#include <itkImageRegionIterator.h>
#include <itkGDCMImageIO.h>

#include <memory>

namespace itk::simple
{

const detail::MemberFunctionFactory<ImageFileWriter::MemberFunctionType> &
ImageFileWriter::GetMemberFunctionFactory()
{
  static constexpr auto static_factory = []() SITK_CONSTEVAL {
    detail::MemberFunctionFactory<MemberFunctionType> factory;
    factory.RegisterMemberFunctions<PixelIDTypeList, 1, SITK_MAX_DIMENSION>();
    return factory;
  }();
  return static_factory;
}


void
WriteImage(const Image & image, const PathType & inFileName, bool useCompression, int compressionLevel)
{
  ImageFileWriter writer;
  writer.Execute(image, inFileName, useCompression, compressionLevel);
}


ImageFileWriter::~ImageFileWriter() = default;

ImageFileWriter::ImageFileWriter() = default;


std::string
ImageFileWriter::ToString() const
{
  std::ostringstream out;
  out << "itk::simple::ImageFileWriter";
  out << std::endl;

  out << "  UseCompression: ";
  this->ToStringHelper(out, this->m_UseCompression);
  out << std::endl;

  out << "  CompressionLevel: ";
  this->ToStringHelper(out, this->m_CompressionLevel);
  out << std::endl;

  out << "  Compressor: ";
  this->ToStringHelper(out, this->m_Compressor);
  out << std::endl;

  out << "  KeepOriginalImageUID: ";
  this->ToStringHelper(out, this->m_KeepOriginalImageUID);
  out << std::endl;

  out << "  FileName: \"";
  this->ToStringHelper(out, this->m_FileName);

  out << "  ImageIOName: ";
  this->ToStringHelper(out, this->m_ImageIOName) << std::endl;

  out << "  Registered ImageIO:" << std::endl;
  ioutils::PrintRegisteredImageIOs(out);
  out << "\"" << std::endl;

  out << ProcessObject::ToString();
  return out.str();
}

std::vector<std::string>
ImageFileWriter::GetRegisteredImageIOs() const
{
  return ioutils::GetRegisteredImageIOs();
}

void
ImageFileWriter::SetUseCompression(bool UseCompression)
{
  this->m_UseCompression = UseCompression;
}

bool
ImageFileWriter::GetUseCompression() const
{
  return this->m_UseCompression;
}

void
ImageFileWriter::SetCompressionLevel(int CompressionLevel)
{
  this->m_CompressionLevel = CompressionLevel;
}

int
ImageFileWriter::GetCompressionLevel() const
{
  return m_CompressionLevel;
}

void
ImageFileWriter::SetCompressor(const std::string & Compressor)
{
  this->m_Compressor = Compressor;
}

std::string
ImageFileWriter::GetCompressor()
{
  return m_Compressor;
}


void
ImageFileWriter::SetKeepOriginalImageUID(bool KeepOriginalImageUID)
{
  this->m_KeepOriginalImageUID = KeepOriginalImageUID;
}

bool
ImageFileWriter::GetKeepOriginalImageUID() const
{
  return this->m_KeepOriginalImageUID;
}

void
ImageFileWriter::SetFileName(const PathType & fn)
{
  this->m_FileName = fn;
}

PathType
ImageFileWriter::GetFileName() const
{
  return this->m_FileName;
}

void
ImageFileWriter::Execute(const Image & image, const PathType & inFileName, bool useCompression, int compressionLevel)
{
  this->SetFileName(inFileName);
  this->SetUseCompression(useCompression);
  this->SetCompressionLevel(compressionLevel);
  return this->Execute(image);
}

void
ImageFileWriter::Execute(const Image & image)
{
  const PixelIDValueType type = image.GetPixelIDValue();
  const unsigned int     dimension = image.GetDimension();

  return GetMemberFunctionFactory().GetMemberFunction(type, dimension, this)(image);
}


void
ImageFileWriter ::SetImageIO(const std::string & imageio)
{
  this->m_ImageIOName = imageio;
}


std::string
ImageFileWriter ::GetImageIO() const
{
  return this->m_ImageIOName;
}


itk::SmartPointer<ImageIOBase>
ImageFileWriter ::GetImageIOBase(const PathType & fileName)
{
  itk::ImageIOBase::Pointer iobase;
  if (this->m_ImageIOName.empty())
  {
    iobase = itk::ImageIOFactory::CreateImageIO(fileName.c_str(), itk::IOFileModeEnum::WriteMode);
  }
  else
  {
    iobase = ioutils::CreateImageIOByName(m_ImageIOName);
  }

  if (iobase.IsNull())
  {
    sitkExceptionMacro("Unable to determine ImageIO writer for \"" << fileName << "\"");
  }

  // Try additional parameters
  GDCMImageIO * ioGDCMImage = dynamic_cast<GDCMImageIO *>(iobase.GetPointer());
  if (ioGDCMImage)
  {
    ioGDCMImage->SetKeepOriginalUID(this->m_KeepOriginalImageUID);
  }
  return iobase;
}

//-----------------------------------------------------------------------------
template <class InputImageType>
void
ImageFileWriter::ExecuteInternal(const Image & inImage)
{
  typename InputImageType::ConstPointer image = dynamic_cast<const InputImageType *>(inImage.GetITKBase());

  using Writer = itk::ImageFileWriter<InputImageType>;
  typename Writer::Pointer writer = Writer::New();
  writer->SetUseCompression(this->m_UseCompression);
  writer->SetCompressionLevel(this->m_CompressionLevel);
  writer->SetFileName(this->m_FileName.c_str());
  writer->SetInput(image);

  itk::ImageIOBase::Pointer imageio = this->GetImageIOBase(this->m_FileName);

  if (!this->m_Compressor.empty())
  {
    imageio->SetCompressor(this->m_Compressor);
  }

  sitkDebugMacro("ImageIO: " << imageio->GetNameOfClass());

  writer->SetImageIO(imageio);

  this->PreUpdate(writer.GetPointer());

  writer->Update();
}

} // namespace itk::simple
