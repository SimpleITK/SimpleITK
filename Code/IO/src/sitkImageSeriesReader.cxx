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
#pragma warning(disable:4996)
#endif

#include "sitkImageSeriesReader.h"

#include <itkImageIOBase.h>
#include <itkImageSeriesReader.h>

#include "itkGDCMSeriesFileNames.h"
#include "sitkMetaDataDictionaryCustomCast.hxx"

namespace itk {
  namespace simple {

  Image ReadImage ( const std::vector<std::string> &filenames,
                    PixelIDValueEnum outputPixelType,
                    const std::string &imageIO )
    {
    ImageSeriesReader reader;
    reader.SetFileNames(filenames);
    reader.SetOutputPixelType(outputPixelType);
    reader.SetImageIO(imageIO);
    return reader.Execute();
    }


  std::vector<std::string> ImageSeriesReader::GetGDCMSeriesFileNames( const std::string &directory,
                                                                      const std::string &seriesID,
                                                                      bool useSeriesDetails,
                                                                      bool recursive,
                                                                      bool loadSequences )
    {
    GDCMSeriesFileNames::Pointer gdcmSeries = GDCMSeriesFileNames::New();

    // SetRecursive must be called before SetInputDirectory
    gdcmSeries->SetRecursive( recursive );
    gdcmSeries->SetInputDirectory( directory );
    gdcmSeries->SetUseSeriesDetails( useSeriesDetails );
    gdcmSeries->SetLoadSequences( loadSequences );
    //Skip private tags. Loading DICOM files is faster when private tags are not needed.
    gdcmSeries->SetLoadPrivateTags( false );

    gdcmSeries->Update();

    return gdcmSeries->GetFileNames(seriesID);
    }

  std::vector<std::string> ImageSeriesReader::GetGDCMSeriesIDs( const std::string &directory )
    {
    GDCMSeriesFileNames::Pointer gdcmSeries = GDCMSeriesFileNames::New();

    gdcmSeries->SetInputDirectory( directory );
    return gdcmSeries->GetSeriesUIDs();
    }

  ImageSeriesReader::ImageSeriesReader()
    :
    m_Filter(nullptr),
    m_MetaDataDictionaryArrayUpdate(false)
    {

    // list of pixel types supported
    using PixelIDTypeList = NonLabelPixelIDTypeList;

    this->m_MemberFactory.reset( new detail::MemberFunctionFactory<MemberFunctionType>( this ) );

    this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 2, SITK_MAX_DIMENSION > ();
    }

  ImageSeriesReader::~ImageSeriesReader()
  {
  if (this->m_Filter != nullptr)
    {
      m_Filter->UnRegister();
    }
  }

  std::string ImageSeriesReader::ToString() const {

      std::ostringstream out;
      out << "itk::simple::ImageSeriesReader";
      out << std::endl;

      out << "  FileNames:" << std::endl;
      std::vector<std::string>::const_iterator iter  = m_FileNames.begin();
      while( iter != m_FileNames.end() )
        {
        out << "    \"" << *iter << "\"" << std::endl;
        ++iter;
        }

      out << ImageReaderBase::ToString();
      return out.str();
    }

  ImageSeriesReader& ImageSeriesReader::SetFileNames ( const std::vector<std::string> &filenames )
    {
    this->m_FileNames = filenames;
    return *this;
    }

  const std::vector<std::string> &ImageSeriesReader::GetFileNames() const
    {
    return this->m_FileNames;
    }

  Image ImageSeriesReader::Execute ()
    {
    if( this->m_FileNames.empty() )
      {
      sitkExceptionMacro( "File names information is empty. Cannot read series." );
      }


    PixelIDValueType type =  this->GetOutputPixelType();
    unsigned int dimension = 0;


    itk::ImageIOBase::Pointer imageio = this->GetImageIOBase( this->m_FileNames.front() );
    if (type == sitkUnknown)
      {
      this->GetPixelIDFromImageIO( imageio, type, dimension );
      }
    else
      {
      PixelIDValueType unused;
      this->GetPixelIDFromImageIO( imageio, unused, dimension );
      }

    // increment for series
    ++dimension;

    if (dimension == 4)
      {
      unsigned int size = this->GetDimensionFromImageIO( imageio, 2);
      if (size == 1)
        {
        --dimension;
        }
      }

    if ( dimension < 2 || dimension > SITK_MAX_DIMENSION )
      {
      sitkExceptionMacro( "The file in the series have unsupported " << dimension - 1 << " dimensions." );
      }

    if ( !this->m_MemberFactory->HasMemberFunction( type, dimension ) )
      {
      sitkExceptionMacro( << "PixelType is not supported!" << std::endl
                          << "Pixel Type: "
                          << GetPixelIDValueAsString( type ) << std::endl
                          << "Refusing to load! " << std::endl );
      }

    return this->m_MemberFactory->GetMemberFunction( type, dimension )(imageio);
    }


  template <class TImageType> Image
  ImageSeriesReader::ExecuteInternal( itk::ImageIOBase* imageio )
    {

    using ImageType = TImageType;
    using Reader = itk::ImageSeriesReader<ImageType>;

    // if the IsInstantiated is correctly implemented this should
    // not occur
    assert( ImageTypeToPixelIDValue<ImageType>::Result != (int)sitkUnknown );
    assert( imageio != nullptr );
    typename Reader::Pointer reader = Reader::New();
    reader->SetImageIO( imageio );
    reader->SetFileNames( this->m_FileNames );
    // save some computation by not updating this unneeded data-structure
    reader->SetMetaDataDictionaryArrayUpdate(m_MetaDataDictionaryArrayUpdate);

    // release the old filter ( and output data )
    if ( this->m_Filter != nullptr)
      {
      this->m_pfGetMetaDataKeys = nullptr;
      this->m_pfHasMetaDataKey = nullptr;
      this->m_pfGetMetaData =  nullptr;
      this->m_Filter->UnRegister();
      this->m_Filter = nullptr;
      }


    this->PreUpdate( reader.GetPointer() );

    if (m_MetaDataDictionaryArrayUpdate)
      {
      this->m_Filter = reader;
      this->m_Filter->Register();
      this->m_pfGetMetaDataKeys = std::bind(&GetMetaDataKeysCustomCast<Reader>::CustomCast, reader.GetPointer(), std::placeholders::_1 );
      this->m_pfHasMetaDataKey = std::bind(&HasMetaDataKeyCustomCast<Reader>::CustomCast, reader.GetPointer(), std::placeholders::_1, std::placeholders::_2 );
      this->m_pfGetMetaData = std::bind(&GetMetaDataCustomCast<Reader>::CustomCast, reader.GetPointer(), std::placeholders::_1, std::placeholders::_2 );
      }

    reader->Update();

    return Image( reader->GetOutput() );
    }

  }
}
