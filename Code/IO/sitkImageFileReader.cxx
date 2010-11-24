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

      // todo check if filename does not exits for robust error handling

      itk::ImageIOBase::Pointer iobase =
        itk::ImageIOFactory::CreateImageIO(this->m_Filename.c_str(),
                                           itk::ImageIOFactory::ReadMode);

      if ( iobase.IsNull() )
        {
        std::cerr << "unable to create ImageIO for \"" << this->m_Filename << "\"" << std::endl;
        return image;
        }
      // Read the image information
      iobase->SetFileName( this->m_Filename );
      iobase->ReadImageInformation();

      // get output information about input image
      unsigned int dimension = iobase->GetNumberOfDimensions();
      itk::ImageIOBase::IOComponentType componentType = iobase->GetComponentType();
      itk::ImageIOBase::IOPixelType pixelType = iobase->GetPixelType();
      unsigned int numberOfComponents = iobase->GetNumberOfComponents();

      if (numberOfComponents == 1 && pixelType == itk::ImageIOBase::SCALAR)
        {
        switch (dimension)
          {
          case 2:
            image = this->ExecuteInternalReadScalar<2>( componentType );
            break;
          case 3:
            image = this->ExecuteInternalReadScalar<3>( componentType );
            break;
          }
        }
      else if  (pixelType == itk::ImageIOBase::RGB)
        {
        std::cerr << "RGB pixels not supported" << std::endl;
        }
      else if  (pixelType == itk::ImageIOBase::RGBA)
        {
        std::cerr << "RGBA pixels not supported" << std::endl;
        }
      else if  (pixelType == itk::ImageIOBase::VECTOR)
        {
        std::cerr << "Vector pixel type with " << numberOfComponents << " number of components not supported" << std::endl;
        }
      else
        {
        std::cerr << "Unknown PixelType: "  << (int) componentType << std::endl;
        }


      if ( image.IsNull() )
        {
        std::cerr << "Unable to load image!" << std::endl;
        }

    return image;
    }


  template < unsigned int ImageDimension >
  Image::Pointer ImageFileReader::ExecuteInternalReadScalar( itk::ImageIOBase::IOComponentType componentType )
  {
    switch(componentType)
      {
    case itk::ImageIOBase::CHAR:
      return this->ExecuteInternal< itk::Image<int8_t, ImageDimension> >( );
      break;
    case itk::ImageIOBase::UCHAR:
      return this->ExecuteInternal< itk::Image<uint8_t, ImageDimension> >( );
      break;
    case itk::ImageIOBase::SHORT:
      return this->ExecuteInternal< itk::Image<int16_t, ImageDimension> >( );
      break;
    case itk::ImageIOBase::USHORT:
      return this->ExecuteInternal< itk::Image<uint16_t, ImageDimension> >( );
      break;
    case itk::ImageIOBase::INT:
      return this->ExecuteInternal< itk::Image<int32_t, ImageDimension> >( );
      break;
    case itk::ImageIOBase::UINT:
      return this->ExecuteInternal< itk::Image<uint32_t, ImageDimension> >( );
      break;
    case itk::ImageIOBase::LONG:
      return this->ExecuteInternal< itk::Image<long, ImageDimension> >( );
      break;
    case itk::ImageIOBase::ULONG:
      return this->ExecuteInternal< itk::Image<unsigned long, ImageDimension> >( );
      break;
    case itk::ImageIOBase::FLOAT:
      return this->ExecuteInternal< itk::Image<float, ImageDimension> >( );
      break;
    case itk::ImageIOBase::DOUBLE:
      return this->ExecuteInternal< itk::Image<double, ImageDimension> >( );
      break;
    case itk::ImageIOBase::UNKNOWNCOMPONENTTYPE:
    default:
      // todo error handling
      std::cerr << "Unknow pixel component type" << std::endl;
      return NULL;
    }
  }


  template <class TImageType>
  Image::Pointer ImageFileReader::ExecuteInternal( void ) {

    typedef TImageType                      ImageType;
    typedef itk::ImageFileReader<ImageType> Reader;

    // do not create an image if it's not in the instatied pixel list
    if ( !typelist::HasType< InstantiatedPixelTypeList, typename TImageType::PixelType>::Result )
      {
      std::cerr << "PixelType is not supported!" << std::endl;
      return NULL;
      }

    typename Reader::Pointer reader = Reader::New();
    reader->SetFileName( this->m_Filename.c_str() );
    reader->Update();
    typename Image::Pointer image = new Image( reader->GetOutput() );
    return image;
  }

  }
}
