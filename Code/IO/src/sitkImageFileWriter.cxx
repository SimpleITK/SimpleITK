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

#include "sitkImageFileWriter.h"

#include <itkImageIOBase.h>
#include <itkImageFileWriter.h>
#include <itkImageRegionIterator.h>
#include <itkGDCMImageIO.h>

namespace itk {
namespace simple {

void WriteImage ( const Image& image, const std::string &inFileName, bool inUseCompression )
  {
    ImageFileWriter writer;
    writer.Execute ( image, inFileName, inUseCompression );
  }


ImageFileWriter::ImageFileWriter()
  {
  this->m_UseCompression = false;
  this->m_KeepOriginalImageUID = false;

  this->m_MemberFactory.reset( new detail::MemberFunctionFactory<MemberFunctionType>( this ) );

  this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 4 > ();
  this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 3 > ();
  this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 2 > ();

  }


std::string ImageFileWriter::ToString() const
  {
  std::ostringstream out;
  out << "itk::simple::ImageFileWriter";
  out << std::endl;

  out << "  UseCompression: ";
  this->ToStringHelper(out, this->m_UseCompression);
  out << std::endl;

  out << "  KeepOriginalImageUID: ";
  this->ToStringHelper(out, this->m_KeepOriginalImageUID);
  out << std::endl;

  out << "  FileName: \"";
  this->ToStringHelper(out, this->m_FileName);
  out << "\"" << std::endl;

  out << ProcessObject::ToString();
  return out.str();
  }

  ImageFileWriter::Self&
  ImageFileWriter::SetUseCompression( bool UseCompression )
  {
    this->m_UseCompression = UseCompression;
    return *this;
  }

  bool ImageFileWriter::GetUseCompression( void ) const
  {
    return this->m_UseCompression;
  }

  ImageFileWriter::Self&
  ImageFileWriter::SetKeepOriginalImageUID( bool KeepOriginalImageUID )
  {
    this->m_KeepOriginalImageUID = KeepOriginalImageUID;
    return *this;
  }

  bool ImageFileWriter::GetKeepOriginalImageUID( void ) const
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

  ImageFileWriter& ImageFileWriter::Execute ( const Image& image, const std::string &inFileName, bool inUseCompression )
  {
    this->SetFileName( inFileName );
    this->SetUseCompression( inUseCompression );
    return this->Execute( image );
  }

ImageFileWriter& ImageFileWriter::Execute ( const Image& image )
  {
    PixelIDValueType type = image.GetPixelIDValue();
    unsigned int dimension = image.GetDimension();

    return this->m_MemberFactory->GetMemberFunction( type, dimension )( image );
  }

itk::SmartPointer<ImageIOBase>
ImageFileWriter
::GetImageIOBase(const std::string &fileName)
{
  itk::ImageIOBase::Pointer iobase =
    itk::ImageIOFactory::CreateImageIO( fileName.c_str(), itk::ImageIOFactory::WriteMode);


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

    typedef itk::ImageFileWriter<InputImageType> Writer;
    typename Writer::Pointer writer = Writer::New();
    writer->SetUseCompression( this->m_UseCompression );
    writer->SetFileName ( this->m_FileName.c_str() );
    writer->SetInput ( image );
    writer->SetImageIO( GetImageIOBase( this->m_FileName ).GetPointer() );

    this->PreUpdate( writer.GetPointer() );

    writer->Update();

    return *this;
  }

} // end namespace simple
} // end namespace itk
