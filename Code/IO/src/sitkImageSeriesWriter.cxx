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

// suppress warning about using sprintf
#ifdef _MSC_VER
  #define _CRT_SECURE_NO_WARNINGS
#endif

#include "sitkImageSeriesWriter.h"
#include "sitkImageIOUtilities.h"

#include <itkImageIOBase.h>
#include <itkImageSeriesWriter.h>

#include <cctype>

namespace itk {
  namespace simple {

  void WriteImage ( const Image& inImage, const std::vector<std::string> &filenames, bool useCompression, int compressionLevel )
  {
    ImageSeriesWriter writer;
    writer.Execute( inImage, filenames, useCompression, compressionLevel );
  }

  ImageSeriesWriter::~ImageSeriesWriter()
  = default;

  ImageSeriesWriter::ImageSeriesWriter()
  {

    this->m_UseCompression = false;
    this->m_CompressionLevel = -1;

    // list of pixel types supported
    using PixelIDTypeList = NonLabelPixelIDTypeList;

    this->m_MemberFactory.reset( new detail::MemberFunctionFactory<MemberFunctionType>( this ) );

    this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 3 > ();
    //this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 2 > ();
  }

  std::string ImageSeriesWriter::ToString() const
  {

    std::ostringstream out;
    out << "itk::simple::ImageSeriesWriter";
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

    out << "  FileNames:" << std::endl;
    std::vector<std::string>::const_iterator iter  = m_FileNames.begin();
    while( iter != m_FileNames.end() )
      {
      out << "    \"" << *iter << "\"" << std::endl;
      ++iter;
      }

    out << "  ImageIOName: ";
    this->ToStringHelper(out, this->m_ImageIOName) << std::endl;

    out << "  Registered ImageIO:" << std::endl;
    ioutils::PrintRegisteredImageIOs(out);

    return out.str();
  }


  std::vector<std::string>
  ImageSeriesWriter::GetRegisteredImageIOs() const
  {
    return ioutils::GetRegisteredImageIOs();
  }

  ImageSeriesWriter::Self&
  ImageSeriesWriter
  ::SetImageIO(const std::string &imageio)
  {
    this->m_ImageIOName = imageio;
    return *this;
  }


  std::string
  ImageSeriesWriter
  ::GetImageIO() const
  {
    return this->m_ImageIOName;
  }

  itk::SmartPointer<ImageIOBase>
  ImageSeriesWriter
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

    return iobase;
  }


  ImageSeriesWriter::Self&
  ImageSeriesWriter::SetUseCompression( bool UseCompression )
  {
    this->m_UseCompression = UseCompression;
    return *this;
  }

  bool ImageSeriesWriter::GetUseCompression( ) const
  {
    return this->m_UseCompression;
  }

  ImageSeriesWriter::Self &
  ImageSeriesWriter::SetCompressionLevel(int CompressionLevel)
  {
    this->m_CompressionLevel = CompressionLevel;
    return *this;
  }

  int
  ImageSeriesWriter::GetCompressionLevel() const
  {
    return m_CompressionLevel;
  }

  ImageSeriesWriter::Self &
  ImageSeriesWriter::SetCompressor(const std::string &Compressor)
  {
    this->m_Compressor = Compressor;
    return *this;
  }

  std::string
  ImageSeriesWriter::GetCompressor()
  {
    return m_Compressor;
  }


  ImageSeriesWriter& ImageSeriesWriter::SetFileNames ( const std::vector<std::string> &filenames )
  {
    this->m_FileNames = filenames;
    return *this;
  }

  const std::vector<std::string> &ImageSeriesWriter::GetFileNames() const
  {
    return this->m_FileNames;
  }


  ImageSeriesWriter& ImageSeriesWriter::Execute ( const Image& image, const std::vector<std::string> &inFileNames, bool useCompression, int compressionLevel )
  {
    this->SetFileNames( inFileNames );
    this->SetUseCompression( useCompression );
    this->SetCompressionLevel( compressionLevel );
    return this->Execute( image );
  }

  ImageSeriesWriter &ImageSeriesWriter::Execute ( const Image &image )
  {

    // check that the number of file names match the slice size
    PixelIDValueType type = image.GetPixelIDValue();
    unsigned int dimension = image.GetDimension();

    return this->m_MemberFactory->GetMemberFunction( type, dimension )( image );
  }

  template <class TImageType>
  ImageSeriesWriter &
  ImageSeriesWriter::ExecuteInternal( const Image& inImage )
  {
    // Define the input and output image types
    using InputImageType = TImageType;

    // Verify input file name are provided
    if( this->m_FileNames.empty() )
      {
      sitkExceptionMacro("The parameter \"FileNames\" is empty!");
      }

    // Verify the input file name are not DICOM
    for(unsigned int i = 0; i < this->m_FileNames.size(); ++i)
      {
      const std::string & fn = this->m_FileNames[i];
      std::string ext = fn.substr(fn.find_last_of(".")+1);
      std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

      if (ext == "dcm" || ext == "dicom")
        {
        sitkExceptionMacro(<<this->GetName()<<" does not support writing a DICOM series!")
        }
      }


    typename InputImageType::ConstPointer image = this->CastImageToITK<InputImageType>( inImage );

    using Writer = itk::ImageSeriesWriter<InputImageType,
                                   typename InputImageType::template Rebind<typename InputImageType::PixelType, InputImageType::ImageDimension-1>::Type>;

    typename Writer::Pointer writer = Writer::New();
    writer->SetUseCompression( this->m_UseCompression );
    writer->SetFileNames( this->m_FileNames );
    writer->SetInput( image );

    itk::ImageIOBase::Pointer imageio = this->GetImageIOBase( this->m_FileNames[0] );

    if (!this->m_Compressor.empty())
    {
      imageio->SetCompressor(this->m_Compressor);
    }

    if (this->m_CompressionLevel != -1)
    {
     imageio->SetCompressionLevel(this->m_CompressionLevel);
    }

    sitkDebugMacro( "ImageIO: " << imageio->GetNameOfClass() );

    writer->SetImageIO( imageio );

    this->PreUpdate( writer.GetPointer() );

    writer->Update();

    return *this;
  }

  }
}
