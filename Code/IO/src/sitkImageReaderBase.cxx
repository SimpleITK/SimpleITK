/*=========================================================================
*
*  Copyright NumFOCUS
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*         http://www.apache.org/licenses/LICENSE-2.0.txt
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*=========================================================================*/

#include "sitkImageReaderBase.h"
#include "sitkMacro.h"
#include "sitkExceptionObject.h"
#include "sitkImageIOUtilities.h"

#include <itksys/SystemTools.hxx>

// Include the Transform IO here, so that the IO factory registration
// will occur.
#include <itkTransformFileReader.h>
#include <itkTransformFileWriter.h>

#include <string>

#include <itkImage.h>
#include <itkImageIOBase.h>
#include <itkImageIOFactory.h>
#include <itkGDCMImageIO.h>


namespace itk {
namespace simple {

ImageReaderBase
::~ImageReaderBase() = default;

ImageReaderBase
::ImageReaderBase()
  : m_OutputPixelType(sitkUnknown),
    m_LoadPrivateTags(false),
    m_ImageIOName("")
{
}

std::string
ImageReaderBase
::ToString() const
{
  std::ostringstream out;
  out << "  OutputPixelType: ";
  this->ToStringHelper(out, this->m_OutputPixelType) << std::endl;
  out << "  LoadPrivateTags: ";
  this->ToStringHelper(out, this->m_LoadPrivateTags) << std::endl;
  out << "  ImageIOName: ";
  this->ToStringHelper(out, this->m_ImageIOName) << std::endl;
  out << "  Registered ImageIO:" << std::endl;
  ioutils::PrintRegisteredImageIOs(out);
  out << ProcessObject::ToString();
  return out.str();
}


std::vector<std::string>
ImageReaderBase
::GetRegisteredImageIOs() const
{
  return ioutils::GetRegisteredImageIOs();
}

itk::SmartPointer<ImageIOBase>
ImageReaderBase
::GetImageIOBase(const std::string &fileName)
{
  itk::ImageIOBase::Pointer iobase;
  if (this->m_ImageIOName.empty())
    {
    iobase = itk::ImageIOFactory::CreateImageIO( fileName.c_str(), itk::ImageIOFactory::FileModeEnum::ReadMode);
    }
  else
    {
    iobase = ioutils::CreateImageIOByName(m_ImageIOName);
    }


  if ( iobase.IsNull() )
     {
     if ( !itksys::SystemTools::FileExists( fileName.c_str() ) )
       {
       sitkExceptionMacro( "The file \"" << fileName << "\" does not exist." );
       }

     if ( !bool(std::ifstream( fileName.c_str() )) )
       {
       sitkExceptionMacro( "Unable to open \"" << fileName << "\" for reading." );
       }

     sitkExceptionMacro( "Unable to determine ImageIO reader for \"" << fileName << "\"" );
    }

  // Try additional parameters
  GDCMImageIO *ioGDCMImage = dynamic_cast<GDCMImageIO*>(iobase.GetPointer());
  if (ioGDCMImage)
    {
    ioGDCMImage->SetLoadPrivateTags(this->m_LoadPrivateTags);
    }

  // Read the image information
  iobase->SetFileName( fileName );
  iobase->ReadImageInformation();


  return iobase;
}

ImageReaderBase::Self&
ImageReaderBase
::SetOutputPixelType( PixelIDValueEnum pixelID )
{
  this->m_OutputPixelType = pixelID;
  return *this;
}

PixelIDValueEnum
ImageReaderBase
::GetOutputPixelType( ) const
{
  return this->m_OutputPixelType;
}


ImageReaderBase::Self&
ImageReaderBase
::SetLoadPrivateTags(bool loadPrivateTags)
{
  this->m_LoadPrivateTags = loadPrivateTags;
  return *this;
}

bool
ImageReaderBase
::GetLoadPrivateTags() const
{
  return this->m_LoadPrivateTags;
}

void
ImageReaderBase
::LoadPrivateTagsOn()
{
  this->SetLoadPrivateTags(true);
}

void
ImageReaderBase
::LoadPrivateTagsOff()
{
  this->SetLoadPrivateTags(false);
}

ImageReaderBase::Self&
ImageReaderBase
::SetImageIO(const std::string &imageio)
{
  this->m_ImageIOName = imageio;
  return *this;
}


std::string
ImageReaderBase
::GetImageIO() const
{
  return this->m_ImageIOName;
}

std::string
ImageReaderBase
::GetImageIOFromFileName( const std::string &fileName )
{
  itk::ImageIOBase::Pointer iobase;
  try
    {
    iobase = itk::ImageIOFactory::CreateImageIO( fileName.c_str(), itk::ImageIOFactory::FileModeEnum::ReadMode);
    }
  catch(...)
    {
    // ignore exceptions
    }


  if ( iobase.IsNull() )
    {
    return std::string();
    }

  return iobase->GetNameOfClass();
}

void
ImageReaderBase
::GetPixelIDFromImageIO( const std::string &fileName,
                         PixelIDValueType &outPixelType,
                         unsigned int & outDimensions )
{
  itk::ImageIOBase::Pointer iobase = this->GetImageIOBase(fileName);


  this->GetPixelIDFromImageIO(iobase, outPixelType, outDimensions);
}

void
ImageReaderBase
::GetPixelIDFromImageIO( const ImageIOBase *iobase,
                         PixelIDValueType &outPixelType,
                         unsigned int & outDimensions )
{

  // get output information about input image
  unsigned int dimension = iobase->GetNumberOfDimensions();
  itk::ImageIOBase::IOComponentType componentType = iobase->GetComponentType();
  itk::ImageIOBase::IOPixelType pixelType = iobase->GetPixelType();
  unsigned int numberOfComponents = iobase->GetNumberOfComponents();

  outDimensions = dimension;


  if (numberOfComponents == 1 &&
      ( pixelType == itk::ImageIOBase::SCALAR || pixelType == itk::ImageIOBase::COMPLEX ) )
    {
    outPixelType = this->ExecuteInternalReadScalar( static_cast<int>(componentType) );
    return;
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
    outPixelType = this->ExecuteInternalReadVector( static_cast<int>(componentType) );
    return;
    }
  else if ( pixelType == itk::ImageIOBase::COMPLEX )
    {
    outPixelType = this->ExecuteInternalReadComplex( static_cast<int>(componentType) );
    return;
    }
  else
    {
    sitkExceptionMacro(  "Unknown PixelType: "
                         << itk::ImageIOBase::GetComponentTypeAsString(componentType)
                         << "(" <<(int) componentType << ")" );
    }

  sitkExceptionMacro( "Unable to load image." );
}

unsigned int
ImageReaderBase
::GetDimensionFromImageIO( const itk::ImageIOBase* iobase, unsigned int i)
{
  return iobase->GetDimensions(i);
}


unsigned int
ImageReaderBase
::GetDimensionFromImageIO(const std::string &filename, unsigned int i)
{
  itk::ImageIOBase::Pointer iobase = this->GetImageIOBase(filename);

  return this->GetDimensionFromImageIO(iobase.GetPointer(), i);
}


PixelIDValueType
ImageReaderBase
::ExecuteInternalReadScalar( int componentType )
{
  const unsigned int UnusedDimension = 2;

  switch(static_cast<ImageIOBase::IOComponentType>(componentType))
    {
    case itk::ImageIOBase::CHAR:
      return ImageTypeToPixelIDValue< itk::Image<int8_t, UnusedDimension> >::Result;
      break;
    case itk::ImageIOBase::UCHAR:
      return ImageTypeToPixelIDValue< itk::Image<uint8_t, UnusedDimension> >::Result;
      break;
    case itk::ImageIOBase::SHORT:
      return ImageTypeToPixelIDValue< itk::Image<int16_t, UnusedDimension> >::Result;
      break;
    case itk::ImageIOBase::USHORT:
      return ImageTypeToPixelIDValue< itk::Image<uint16_t, UnusedDimension> >::Result;
      break;
    case itk::ImageIOBase::INT:
      return ImageTypeToPixelIDValue< itk::Image<int32_t, UnusedDimension> >::Result;
      break;
    case itk::ImageIOBase::UINT:
      return ImageTypeToPixelIDValue< itk::Image<uint32_t, UnusedDimension> >::Result;
      break;
    case itk::ImageIOBase::LONG:
      if (sizeof(long) == 4 )
        return ImageTypeToPixelIDValue< itk::Image<int32_t, UnusedDimension> >::Result;
      else
        return ImageTypeToPixelIDValue< itk::Image<int64_t, UnusedDimension> >::Result;
      break;
    case itk::ImageIOBase::ULONG:
      if (sizeof(unsigned long) == 4 )
        return ImageTypeToPixelIDValue< itk::Image<uint32_t, UnusedDimension> >::Result;
      else
        return ImageTypeToPixelIDValue< itk::Image<uint64_t, UnusedDimension> >::Result;
      break;
    case itk::ImageIOBase::LONGLONG:
      return ImageTypeToPixelIDValue< itk::Image<int64_t, UnusedDimension> >::Result;
      break;
    case itk::ImageIOBase::ULONGLONG:
      return ImageTypeToPixelIDValue< itk::Image<uint64_t, UnusedDimension> >::Result;
      break;
    case itk::ImageIOBase::FLOAT:
      return ImageTypeToPixelIDValue< itk::Image<float, UnusedDimension> >::Result;
      break;
    case itk::ImageIOBase::DOUBLE:
      return ImageTypeToPixelIDValue< itk::Image<double, UnusedDimension> >::Result;
      break;
    case itk::ImageIOBase::UNKNOWNCOMPONENTTYPE:
    default:
      assert( false ); // should never get here unless we forgot a type
      sitkExceptionMacro( "Logic error!" );
    }
}


PixelIDValueType
ImageReaderBase
::ExecuteInternalReadComplex( int componentType )
{
  const unsigned int UnusedDimension = 2;

  switch(static_cast<ImageIOBase::IOComponentType>(componentType))
    {
    case itk::ImageIOBase::FLOAT:
      return ImageTypeToPixelIDValue< itk::Image<std::complex<float>, UnusedDimension> >::Result;
      break;
    case itk::ImageIOBase::DOUBLE:
      return ImageTypeToPixelIDValue< itk::Image<std::complex<double>, UnusedDimension> >::Result;
      break;
    case itk::ImageIOBase::UNKNOWNCOMPONENTTYPE:
    default:
      sitkExceptionMacro( "Only Complex image with float and double are supported!" );
    }
}

PixelIDValueType
ImageReaderBase
::ExecuteInternalReadVector( int componentType )
{
  const unsigned int UnusedDimension = 2;

  switch(static_cast<ImageIOBase::IOComponentType>(componentType))
    {
    case itk::ImageIOBase::CHAR:
      return ImageTypeToPixelIDValue< itk::VectorImage<int8_t, UnusedDimension> >::Result;
      break;
    case itk::ImageIOBase::UCHAR:
      return ImageTypeToPixelIDValue< itk::VectorImage<uint8_t , UnusedDimension> >::Result;
      break;
    case itk::ImageIOBase::SHORT:
      return ImageTypeToPixelIDValue< itk::VectorImage<int16_t, UnusedDimension> >::Result;
      break;
    case itk::ImageIOBase::USHORT:
      return ImageTypeToPixelIDValue< itk::VectorImage<uint16_t, UnusedDimension> >::Result;
      break;
    case itk::ImageIOBase::INT:
      return ImageTypeToPixelIDValue< itk::VectorImage<int32_t, UnusedDimension> >::Result;
      break;
    case itk::ImageIOBase::UINT:
      return ImageTypeToPixelIDValue< itk::VectorImage<uint32_t, UnusedDimension> >::Result;
      break;
    case itk::ImageIOBase::LONG:
      if (sizeof(long) == 4 )
        return ImageTypeToPixelIDValue< itk::VectorImage<int32_t, UnusedDimension> >::Result;
      else
        return ImageTypeToPixelIDValue< itk::VectorImage<int64_t, UnusedDimension> >::Result;
      break;
    case itk::ImageIOBase::ULONG:
      if (sizeof(unsigned long) == 4 )
        return ImageTypeToPixelIDValue< itk::VectorImage<uint32_t, UnusedDimension> >::Result;
      else
        return ImageTypeToPixelIDValue< itk::VectorImage<uint64_t, UnusedDimension> >::Result;
      break;
    case itk::ImageIOBase::LONGLONG:
      return ImageTypeToPixelIDValue< itk::VectorImage<int64_t, UnusedDimension> >::Result;
      break;
    case itk::ImageIOBase::ULONGLONG:
      return ImageTypeToPixelIDValue< itk::VectorImage<uint64_t, UnusedDimension> >::Result;
      break;
    case itk::ImageIOBase::FLOAT:
      return ImageTypeToPixelIDValue< itk::VectorImage<float, UnusedDimension> >::Result;
      break;
    case itk::ImageIOBase::DOUBLE:
      return ImageTypeToPixelIDValue< itk::VectorImage<double, UnusedDimension> >::Result;
      break;
    case itk::ImageIOBase::UNKNOWNCOMPONENTTYPE:
    default:
      assert( false ); // should never get here unless we forgot a type
      sitkExceptionMacro( "Logic error!" );
    }
}


}
}
