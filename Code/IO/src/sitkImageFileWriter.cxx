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

namespace itk {
namespace simple {

void WriteImage ( const Image& image, const std::string &inFileName, bool useCompression, int compressionLevel )
{
  ImageFileWriter writer;
  writer.Execute ( image, inFileName, useCompression, compressionLevel );
}


ImageFileWriter::~ImageFileWriter() = default;

ImageFileWriter::ImageFileWriter()
{
  this->m_UseCompression = false;
  this->m_KeepOriginalImageUID = false;
  this->m_CompressionLevel = -1;

  this->m_MemberFactory.reset( new detail::MemberFunctionFactory<MemberFunctionType>( this ) );

  this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 1, SITK_MAX_DIMENSION > ();

}


std::string ImageFileWriter::ToString() const
{
  std::ostringstream out;
  out << "itk::simple::ImageFileWriter";
  out << std::endl;

  out << "  UseCompression: ";
  this->ToStringHelper(out, this->m_UseCompression);
  out << std::endl;

  out << "  CompressionLevel: ";
  this->ToStringHelper( out, this->m_CompressionLevel);
  out << std::endl;

  out << "  Compressor: ";
  this->ToStringHelper( out, this->m_Compressor);
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

ImageFileWriter::Self&
ImageFileWriter::SetUseCompression( bool UseCompression )
{
  this->m_UseCompression = UseCompression;
  return *this;
}

bool ImageFileWriter::GetUseCompression( ) const
{
  return this->m_UseCompression;
}

ImageFileWriter::Self &
ImageFileWriter::SetCompressionLevel(int CompressionLevel)
{
  this->m_CompressionLevel = CompressionLevel;
  return *this;
}

int
ImageFileWriter::GetCompressionLevel() const
{
  return m_CompressionLevel;
}

ImageFileWriter::Self &
ImageFileWriter::SetCompressor(const std::string &Compressor)
{
  this->m_Compressor = Compressor;
  return *this;
}

std::string
ImageFileWriter::GetCompressor()
{
  return m_Compressor;
}


ImageFileWriter::Self&
ImageFileWriter::SetKeepOriginalImageUID( bool KeepOriginalImageUID )
{
  this->m_KeepOriginalImageUID = KeepOriginalImageUID;
  return *this;
}

bool ImageFileWriter::GetKeepOriginalImageUID( ) const
{
  return this->m_KeepOriginalImageUID;
}

ImageFileWriter& ImageFileWriter::SetFileName ( const std::string &fn )
{
  this->m_FileName = fn;
  return *this;
}

std::string ImageFileWriter::GetFileName() const
{
  return this->m_FileName;
}

ImageFileWriter& ImageFileWriter::Execute ( const Image& image, const std::string &inFileName, bool useCompression, int compressionLevel )
{
  this->SetFileName( inFileName );
  this->SetUseCompression( useCompression );
  this->SetCompressionLevel( compressionLevel );
  return this->Execute( image );
}

ImageFileWriter& ImageFileWriter::Execute ( const Image& image )
{
  PixelIDValueType type = image.GetPixelIDValue();
  unsigned int dimension = image.GetDimension();

  return this->m_MemberFactory->GetMemberFunction( type, dimension )( image );
}


ImageFileWriter::Self&
ImageFileWriter
::SetImageIO(const std::string &imageio)
{
  this->m_ImageIOName = imageio;
  return *this;
}


std::string
ImageFileWriter
::GetImageIO() const
{
  return this->m_ImageIOName;
}


itk::SmartPointer<ImageIOBase>
ImageFileWriter
::GetImageIOBase(const std::string &fileName)
{
  itk::ImageIOBase::Pointer iobase;
  if (this->m_ImageIOName.empty())
    {
    iobase = itk::ImageIOFactory::CreateImageIO( fileName.c_str(), itk::ImageIOFactory::FileModeEnum::WriteMode);
    }
  else
    {
    iobase = ioutils::CreateImageIOByName(m_ImageIOName);
    }

  if ( iobase.IsNull() )
    {
    sitkExceptionMacro( "Unable to determine ImageIO writer for \"" << fileName << "\"" );
    }

  // Try additional parameters
  GDCMImageIO *ioGDCMImage = dynamic_cast<GDCMImageIO*>(iobase.GetPointer());
  if (ioGDCMImage)
    {
    ioGDCMImage->SetKeepOriginalUID(this->m_KeepOriginalImageUID);
    }
  return iobase;
}

//-----------------------------------------------------------------------------
template <class InputImageType>
ImageFileWriter& ImageFileWriter::ExecuteInternal( const Image& inImage )
{
  typename InputImageType::ConstPointer image =
    dynamic_cast <const InputImageType*> ( inImage.GetITKBase() );

  using Writer = itk::ImageFileWriter<InputImageType>;
  typename Writer::Pointer writer = Writer::New();
  writer->SetUseCompression( this->m_UseCompression );
  writer->SetCompressionLevel( this->m_CompressionLevel );
  writer->SetFileName ( this->m_FileName.c_str() );
  writer->SetInput ( image );

  itk::ImageIOBase::Pointer imageio = this->GetImageIOBase( this->m_FileName );

  if (!this->m_Compressor.empty())
  {
  imageio->SetCompressor(this->m_Compressor);
  }

  sitkDebugMacro( "ImageIO: " << imageio->GetNameOfClass() );

  writer->SetImageIO( imageio );

  this->PreUpdate( writer.GetPointer() );

  writer->Update();

  return *this;
}

} // end namespace simple
} // end namespace itk
