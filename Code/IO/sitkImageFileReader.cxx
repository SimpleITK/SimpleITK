#ifdef _MFC_VER
#pragma warning(disable:4996)
#endif

#include "sitkImageFileReader.h"
#include <itkImageIOBase.h>
#include <itkImageFileReader.h>


namespace itk {
  namespace simple {
    
    ImageFileReader& ImageFileReader::SetFilename ( std::string fn ) {
      this->m_Filename = fn;
      return *this;
    }

    std::string ImageFileReader::GetFilename() {
      return this->m_Filename;
    }

    Image::Pointer ImageFileReader::Execute () {
      Image::Pointer image = NULL;
      // Figure out what type of image we have
      typedef itk::Image<signed short,3> ImageType;
      typedef itk::ImageFileReader<ImageType> Reader;
      Reader::Pointer reader = Reader::New();
      reader->SetFileName ( this->m_Filename.c_str() );
      reader->UpdateOutputInformation();

      switch ( reader->GetImageIO()->GetComponentType() ) {
      case itk::ImageIOBase::FLOAT:
        image = ExecuteInternal<float> ( );
        break;
      case itk::ImageIOBase::UCHAR:
        image = ExecuteInternal<uint8_t> ( );
        break;
      default:
      case itk::ImageIOBase::SHORT:
        
        image = ExecuteInternal<int16_t> ( );
        break;
      case itk::ImageIOBase::INT:
        image = ExecuteInternal<int32_t> ( );
        break;
      }
    return image;
    }

  template <class T>
  Image::Pointer ImageFileReader::ExecuteInternal( void ) {
    Image::Pointer image = NULL;
    typedef itk::Image<T,3> ImageType;
    typedef itk::ImageFileReader<ImageType> Reader;
    typename Reader::Pointer reader = Reader::New();
    reader->SetFileName( this->m_Filename.c_str() );
    reader->Update();
    image = new Image( reader->GetOutput() );
    reader->GetOutput()->DisconnectPipeline();
    return image;
  }
      

      

    

  }
}
