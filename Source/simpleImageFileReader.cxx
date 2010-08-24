#include "simpleImageFileReader.h"
#include <itkImageIOBase.h>
#include <itkImageFileReader.h>

namespace itk {
  namespace simple {
    
    ImageFileReader& ImageFileReader::setFilename ( std::string fn ) {
      this->mFilename = fn;
      return *this;
    }

    std::string ImageFileReader::getFilename() {
      return this->mFilename;
    }

    Image::Pointer ImageFileReader::execute () {
      Image::Pointer image = NULL;
      // Figure out what type of image we have
      typedef itk::Image<signed short,3> ImageType;
      typedef itk::ImageFileReader<ImageType> Reader;
      Reader::Pointer reader = Reader::New();
      reader->SetFileName ( this->mFilename.c_str() );
      reader->UpdateOutputInformation();

      switch ( reader->GetImageIO()->GetComponentType() ) {
      case itk::ImageIOBase::FLOAT:
        image = executeInternal<float> ( );
        break;
      case itk::ImageIOBase::UCHAR:
        image = executeInternal<uint8_t> ( );
        break;
      default:
      case itk::ImageIOBase::SHORT:
        image = executeInternal<int16_t> ( );
        break;
      case itk::ImageIOBase::INT:
        image = executeInternal<int32_t> ( );
        break;
      }
    return image;
    }

  template <class T>
  Image::Pointer ImageFileReader::executeInternal( void ) {
    Image::Pointer image = NULL;
    typedef itk::Image<T,3> ImageType;
    typedef itk::ImageFileReader<ImageType> Reader;
    typename Reader::Pointer reader = Reader::New();
    reader->SetFileName ( this->mFilename.c_str() );
    reader->Update();
    image = new ImageImplementation<ImageType> ( reader->GetOutput() );
    reader->GetOutput()->DisconnectPipeline();
    return image;
  }
      

      

    

  }
}
