#ifdef _MFC_VER
#pragma warning(disable:4996)
#endif

#include "sitkImageSeriesReader.h"

#include <itkImageIOBase.h>
#include <itkImageSeriesReader.h>


namespace itk {
  namespace simple {

    Image ReadImage ( const std::vector<std::string> &filenames ) {
      ImageSeriesReader reader;
      return reader.SetFileNames ( filenames ).Execute();
    }

    ImageSeriesReader::ImageSeriesReader() {

      // list of pixel types supported
      typedef NonLabelPixelIDTypeList PixelIDTypeList;

      this->m_MemberFactory.reset( new detail::MemberFunctionFactory<MemberFunctionType>( this ) );

      this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 3 > ();
      this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 2 > ();
    }

    ImageSeriesReader& ImageSeriesReader::SetFileNames ( const std::vector<std::string> &filenames ) {
      this->m_FileNames = filenames;
      return *this;
    }

    const std::vector<std::string> &ImageSeriesReader::GetFileNames() const {
      return this->m_FileNames;
    }

    Image ImageSeriesReader::Execute () {
      // todo check if filename does not exits for robust error handling
      assert( !this->m_FileNames.empty() );

      PixelIDValueType type = sitkUnknown;
      unsigned int dimension = 0;

      this->GetPixelIDFromImageIO( this->m_FileNames.front(), type, dimension );

      return this->m_MemberFactory->GetMemberFunction( type, dimension )();
      sitkExceptionMacro( << "PixelType is not supported!" << std::endl
                          << "Pixel Type: "
                          << GetPixelIDValueAsString( type ) << std::endl
                          << "Refusing to load! " << std::endl );
    }

  template <class TImageType>
  Image
  ImageSeriesReader::ExecuteInternal( void )
  {

    typedef TImageType                        ImageType;
    typedef itk::ImageSeriesReader<ImageType> Reader;

    // if the IsInstantiated is correctly implemented this should
    // not occour
    assert( ImageTypeToPixelIDValue<ImageType>::Result != (int)sitkUnknown );
    typename Reader::Pointer reader = Reader::New();
    reader->SetFileNames( this->m_FileNames );
    reader->Update();
    return Image( reader->GetOutput() );
  }

  }
}
