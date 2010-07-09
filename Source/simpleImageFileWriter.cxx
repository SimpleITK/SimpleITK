#include "simpleImageFileWriter.h"
#include <itkImageIOBase.h>
#include <itkImageFileWriter.h>

namespace itk {
  namespace simple {
    
    ImageFileWriter& ImageFileWriter::setFilename ( std::string fn ) {
      this->mFilename = fn;
      return *this;
    }

    std::string ImageFileWriter::getFilename() {
      return this->mFilename;
    }

    ImageFileWriter& ImageFileWriter::execute ( Image::Pointer image ) {
      switch ( image->getImageDataType() ) {
        sitkImageDataTypeSwitch ( return this->executeInternal<DataType>(image) );
      }
      return *this;
    }

    template <class T>
    ImageFileWriter& ImageFileWriter::executeInternal( Image::Pointer inImage ) {
      typedef itk::Image<T,3> InputImageType;
      typename InputImageType::Pointer image = dynamic_cast <InputImageType*> ( inImage->getITKImage().GetPointer() );
      
      typedef itk::ImageFileWriter<InputImageType> Writer;
      typename Writer::Pointer writer = Writer::New();
      writer->SetFileName ( this->mFilename.c_str() );
      writer->SetInput ( image );
      writer->Update();
      return *this;
    }
  }
}
      
    

