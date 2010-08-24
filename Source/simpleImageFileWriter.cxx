#include "simpleImageFileWriter.h"
#include <itkImageIOBase.h>
#include <itkImageFileWriter.h>

namespace itk {
  namespace simple {

  ImageFileWriter::ImageFileWriter()
  {
      // initialize array to all zeros
      std::fill_n( m_PFunction, size_t(typelist::Length< InstantiatedPixelTypeList >::Result), MemberFunctionType(0) );

      // initialize function array with pointer
      typelist::ForEach<PixelTypeList> arrayInitializer;
      arrayInitializer( PFuncArrayInitializer<Self>( this->m_PFunction ) );
  }

    ImageFileWriter& ImageFileWriter::setFilename ( std::string fn ) {
      this->mFilename = fn;
      return *this;
    }

    std::string ImageFileWriter::getFilename() {
      return this->mFilename;
    }

    ImageFileWriter& ImageFileWriter::execute ( Image::Pointer image ) {
      int fnIndex = image->getImageDataType();
      assert( fnIndex > 0 && fnIndex < typelist::Length< InstantiatedPixelTypeList >::Result );
      if ( m_PFunction[ fnIndex ] )
        {
        ((*this).*(m_PFunction[ fnIndex ]))(image);
        }
      else
        {
        // error
        std::cerr << "pixel type is not supported!" << std::endl;
        exit(1);
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
