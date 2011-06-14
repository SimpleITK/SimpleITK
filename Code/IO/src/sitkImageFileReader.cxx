#ifdef _MFC_VER
#pragma warning(disable:4996)
#endif

#include "sitkImageFileReader.h"

#include <itkImageFileReader.h>


namespace itk {
  namespace simple {

    Image ReadImage ( std::string filename ) {
      ImageFileReader reader; return reader.SetFileName ( filename ).Execute();
    }

    ImageFileReader::ImageFileReader() {

      // list of pixel types supported
      typedef NonLabelPixelIDTypeList PixelIDTypeList;

      this->m_MemberFactory.reset( new detail::MemberFunctionFactory<MemberFunctionType>( this ) );

      this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 3 > ();
      this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 2 > ();
    }

    ImageFileReader& ImageFileReader::SetFileName ( std::string fn ) {
      this->m_FileName = fn;
      return *this;
    }

    std::string ImageFileReader::GetFileName() {
      return this->m_FileName;
    }

    Image ImageFileReader::Execute () {

      PixelIDValueType type = sitkUnknown;
      unsigned int dimension = 0;

      this->GetPixelIDFromImageIO( this->m_FileName, type, dimension );

      if ( dimension != 2 && dimension != 3 )
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

      return this->m_MemberFactory->GetMemberFunction( type, dimension )();
    }

  template <class TImageType>
  Image
  ImageFileReader::ExecuteInternal( void )
  {

    typedef TImageType                      ImageType;
    typedef itk::ImageFileReader<ImageType> Reader;

    // if the InstantiatedToken is correctly implemented this should
    // not occour
    assert( ImageTypeToPixelIDValue<ImageType>::Result != (int)sitkUnknown );

    typename Reader::Pointer reader = Reader::New();
    reader->SetFileName( this->m_FileName.c_str() );
    reader->Update();

    return Image( reader->GetOutput() );
  }

  }
}
