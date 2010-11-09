#include "sitkImageFileWriter.h"
#include <itkImageIOBase.h>
#include <itkImageFileWriter.h>

namespace itk {
  namespace simple {

  ImageFileWriter::ImageFileWriter()
  {
  }

    ImageFileWriter& ImageFileWriter::SetFilename ( std::string fn ) {
      this->m_Filename = fn;
      return *this;
    }

    std::string ImageFileWriter::GetFilename() {
      return this->m_Filename;
    }

    ImageFileWriter& ImageFileWriter::Execute ( Image::Pointer image ) {
      int fnIndex = image->GetImageDataType();

      // todo fix this ugly syntax
      ((*this).*(m_MemberFactory.GetMemberFunction( fnIndex )))(image);
      return *this;
    }

    template <class T>
    ImageFileWriter& ImageFileWriter::ExecuteInternal( Image::Pointer inImage ) {
      typedef itk::Image<T,3> InputImageType;
      typename InputImageType::Pointer image = 
        dynamic_cast <InputImageType*> ( inImage->GetITKImage().GetPointer() );

      typedef itk::ImageFileWriter<InputImageType> Writer;
      typename Writer::Pointer writer = Writer::New();
      writer->SetFileName ( this->m_Filename.c_str() );
      writer->SetInput ( image );
      writer->Update();
      return *this;
    }
  }
}
