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

      // todo check if filename does not exits for robust error handling

      itk::ImageIOBase::Pointer iobase =
        itk::ImageIOFactory::CreateImageIO(this->m_Filename.c_str(),
                                           itk::ImageIOFactory::ReadMode);

      if ( iobase.IsNull() )
        {
        sitkExceptionMacro( "Unable to determine ImageIO reader for \"" << this->m_Filename << "\"" );
        }

      // Read the image information
      iobase->SetFileName( this->m_Filename );
      iobase->ReadImageInformation();

      // get output information about input image
      unsigned int dimension = iobase->GetNumberOfDimensions();
      itk::ImageIOBase::IOComponentType componentType = iobase->GetComponentType();
      itk::ImageIOBase::IOPixelType pixelType = iobase->GetPixelType();
      unsigned int numberOfComponents = iobase->GetNumberOfComponents();

      if (numberOfComponents == 1 &&
          ( pixelType == itk::ImageIOBase::SCALAR || pixelType == itk::ImageIOBase::COMPLEX ) )
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
      // we try to load anything else into a VectorImage
      else if  (pixelType == itk::ImageIOBase::RGB ||
                pixelType == itk::ImageIOBase::RGBA ||
                pixelType == itk::ImageIOBase::VECTOR ||
                pixelType == itk::ImageIOBase::COVARIANTVECTOR ||
                pixelType == itk::ImageIOBase::FIXEDARRAY ||
                pixelType == itk::ImageIOBase::POINT ||
                pixelType == itk::ImageIOBase::OFFSET )
        {
        switch (dimension)
          {
          case 2:
            image = this->ExecuteInternalReadVector<2>( componentType );
            break;
          case 3:
            image = this->ExecuteInternalReadVector<3>( componentType );
            break;
          }
        }
      else
        {
        sitkExceptionMacro(  "Unknown PixelType: "  << (int) componentType );
        }


      if ( image.IsNull() )
        {
        sitkExceptionMacro( "Unable to load image \"" << this->m_Filename << "\"" );
        }

      return image;
    }


  template < unsigned int VImageDimension >
  Image::Pointer ImageFileReader::ExecuteInternalReadScalar( itk::ImageIOBase::IOComponentType componentType )
  {
    switch(componentType)
      {
    case itk::ImageIOBase::CHAR:
      return this->ExecuteInternal< itk::Image<int8_t, VImageDimension> >( );
      break;
    case itk::ImageIOBase::UCHAR:
      return this->ExecuteInternal< itk::Image<uint8_t, VImageDimension> >( );
      break;
    case itk::ImageIOBase::SHORT:
      return this->ExecuteInternal< itk::Image<int16_t, VImageDimension> >( );
      break;
    case itk::ImageIOBase::USHORT:
      return this->ExecuteInternal< itk::Image<uint16_t, VImageDimension> >( );
      break;
    case itk::ImageIOBase::INT:
      return this->ExecuteInternal< itk::Image<int32_t, VImageDimension> >( );
      break;
    case itk::ImageIOBase::UINT:
      return this->ExecuteInternal< itk::Image<uint32_t, VImageDimension> >( );
      break;
    case itk::ImageIOBase::LONG:
      return this->ExecuteInternal< itk::Image<long, VImageDimension> >( );
      break;
    case itk::ImageIOBase::ULONG:
      return this->ExecuteInternal< itk::Image<unsigned long, VImageDimension> >( );
      break;
    case itk::ImageIOBase::FLOAT:
      return this->ExecuteInternal< itk::Image<float, VImageDimension> >( );
      break;
    case itk::ImageIOBase::DOUBLE:
      return this->ExecuteInternal< itk::Image<double, VImageDimension> >( );
      break;
    case itk::ImageIOBase::UNKNOWNCOMPONENTTYPE:
    default:
      assert( false ); // should never get here unless we forgot a type
      return NULL;
    }
  }


  template < unsigned int VImageDimension >
  Image::Pointer ImageFileReader::ExecuteInternalReadVector( itk::ImageIOBase::IOComponentType componentType )
  {
    switch(componentType)
      {
    case itk::ImageIOBase::CHAR:
      return this->ExecuteInternal< itk::VectorImage<signed char, VImageDimension> >( );
      break;
    case itk::ImageIOBase::UCHAR:
      return this->ExecuteInternal< itk::VectorImage<unsigned char, VImageDimension> >( );
      break;
    case itk::ImageIOBase::SHORT:
      return this->ExecuteInternal< itk::VectorImage<int16_t, VImageDimension> >( );
      break;
    case itk::ImageIOBase::USHORT:
      return this->ExecuteInternal< itk::VectorImage<uint16_t, VImageDimension> >( );
      break;
    case itk::ImageIOBase::INT:
      return this->ExecuteInternal< itk::VectorImage<int32_t, VImageDimension> >( );
      break;
    case itk::ImageIOBase::UINT:
      return this->ExecuteInternal< itk::VectorImage<uint32_t, VImageDimension> >( );
      break;
    case itk::ImageIOBase::LONG:
      return this->ExecuteInternal< itk::VectorImage<long, VImageDimension> >( );
      break;
    case itk::ImageIOBase::ULONG:
      return this->ExecuteInternal< itk::VectorImage<unsigned long, VImageDimension> >( );
      break;
    case itk::ImageIOBase::FLOAT:
      return this->ExecuteInternal< itk::VectorImage<float, VImageDimension> >( );
      break;
    case itk::ImageIOBase::DOUBLE:
      return this->ExecuteInternal< itk::VectorImage<double, VImageDimension> >( );
      break;
    case itk::ImageIOBase::UNKNOWNCOMPONENTTYPE:
    default:
      assert( false ); // should never get here unless we forgot a type
      return NULL;
    }
  }


  template <class TImageType>
  typename EnableIf<IsInstantiated<typename ImageTypeToPixelID<TImageType>::PixelIDType>::Value, Image::Pointer >::Type
  ImageFileReader::ExecuteInternal( void )
  {

    typedef TImageType                      ImageType;
    typedef itk::ImageFileReader<ImageType> Reader;

    // if the InstantiatedToken is correctly implemented this should
    // not occour
    assert( ImageTypeToPixelIDValue<ImageType>::Result != (int)sitkUnknown );

    typename Reader::Pointer reader = Reader::New();
    reader->SetFileName( this->m_Filename.c_str() );
    reader->Update();
    typename Image::Pointer image = new Image( reader->GetOutput() );
    return image;
  }

  template <class TImageType>
  typename DisableIf<IsInstantiated<typename ImageTypeToPixelID<TImageType>::PixelIDType>::Value, Image::Pointer >::Type
  ImageFileReader::ExecuteInternal( void )
  {
    typedef TImageType                      ImageType;
    sitkExceptionMacro( << "PixelType is not supported!" << std::endl
                        << "Pixel Type: "
                        << GetPixelIDValueAsString( ImageTypeToPixelIDValue<ImageType>::Result ) << std::endl
                        << "Refusing to load! " << std::endl );
    return NULL;
  }

  }
}
