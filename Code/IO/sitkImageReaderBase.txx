#ifndef __sitkImageReaderBase_txx
#define __sitkImageReaderBase_txx


#include "sitkNonCopyable.h"

#include <stdint.h>
#include <itkImage.h>
#include <itkImageIOBase.h>
#include <itkImageIOFactory.h>

namespace itk {
namespace simple {


template <typename TDerived>
Image
ImageReaderBase<TDerived>
::ImageIODispatch( const std::string &fileName )
{

  itk::ImageIOBase::Pointer iobase =
    itk::ImageIOFactory::CreateImageIO( fileName.c_str(), itk::ImageIOFactory::ReadMode);

  if ( iobase.IsNull() )
    {
    sitkExceptionMacro( "Unable to determine ImageIO reader for \"" << fileName << "\"" );
    }

  // Read the image information
  iobase->SetFileName( fileName );
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
        return this->ExecuteInternalReadScalar<2>( componentType );
        break;
      case 3:
        return this->ExecuteInternalReadScalar<3>( componentType );
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
        return this->ExecuteInternalReadVector<2>( componentType );
        break;
      case 3:
        return this->ExecuteInternalReadVector<3>( componentType );
        break;
      }
    }
  else
    {
    sitkExceptionMacro(  "Unknown PixelType: "  << (int) componentType );
    }

  sitkExceptionMacro( "Unable to load image \"" << fileName << "\"" );

}

template <typename TDerived>
template < unsigned int VImageDimension >
Image
ImageReaderBase<TDerived>
::ExecuteInternalReadScalar( itk::ImageIOBase::IOComponentType componentType )
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
      sitkExceptionMacro( "Logic error!" );
    }
}

template <typename TDerived>
template < unsigned int VImageDimension >
Image
ImageReaderBase<TDerived>
::ExecuteInternalReadVector( itk::ImageIOBase::IOComponentType componentType )
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
      sitkExceptionMacro( "Logic error!" );
    }
}


}
}


#endif // __sitkImageReaderBase_txx
