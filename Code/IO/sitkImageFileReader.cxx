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
      // Figure out what type of image we have
      typedef itk::Image<signed short,3> ImageType;
      typedef itk::ImageFileReader<ImageType> Reader;
      Reader::Pointer reader = Reader::New();
      reader->SetFileName ( this->m_Filename.c_str() );
      reader->UpdateOutputInformation();


      unsigned int dim = reader->GetImageIO()->GetNumberOfDimensions();
      std::cout << "Reading image " << m_Filename << " with " << dim << " dimensions" << std::endl;
      if ( dim == 2 ) {
        return ExecuteInteralDimension<2> ( reader->GetImageIO() );
      } else if ( dim == 3 ) {
        return ExecuteInteralDimension<3> ( reader->GetImageIO() );
      } else {
        std::cerr << "Can not read images of dimension " << dim << std::endl;
      }
      return NULL;
    }

    template<unsigned int dim>
    Image::Pointer ImageFileReader::ExecuteInteralDimension ( itk::ImageIOBase *io ) {
      Image::Pointer image = NULL;
      switch ( io->GetComponentType() ) {
      case itk::ImageIOBase::UCHAR:
        return ExecuteInternal<uint8_t,dim> ( );
      case itk::ImageIOBase::SHORT:
        return ExecuteInternal<int16_t,dim> ( );
      case itk::ImageIOBase::INT:
        return ExecuteInternal<int32_t,dim> ( );
      default:
      case itk::ImageIOBase::FLOAT:
        // If we don't know any better, return floats
        return ExecuteInternal<float,dim> ( );
      }
    }

    template <class T, unsigned int dimensions>
    Image::Pointer ImageFileReader::ExecuteInternal( void ) {
      Image::Pointer image = NULL;
      typedef itk::Image<T,dimensions> ImageType;
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
