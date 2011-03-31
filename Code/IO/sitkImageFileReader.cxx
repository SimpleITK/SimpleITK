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

    ImageFileReader& ImageFileReader::SetFileName ( std::string fn ) {
      this->m_FileName = fn;
      return *this;
    }

    std::string ImageFileReader::GetFileName() {
      return this->m_FileName;
    }

    Image ImageFileReader::Execute () {

      return ImageIODispatch( this->m_FileName );
    }

  template <class TImageType>
  typename EnableIf<IsInstantiated<TImageType>::Value, Image >::Type
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

  template <class TImageType>
  typename DisableIf<IsInstantiated<TImageType>::Value, Image >::Type
  ImageFileReader::ExecuteInternal( void )
  {
    typedef TImageType                      ImageType;
    sitkExceptionMacro( << "PixelType is not supported!" << std::endl
                        << "Pixel Type: "
                        << GetPixelIDValueAsString( ImageTypeToPixelIDValue<ImageType>::Result ) << std::endl
                        << "Refusing to load! " << std::endl );
  }

  }
}
