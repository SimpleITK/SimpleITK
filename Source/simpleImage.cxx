#include "simpleImage.h"

namespace itk
{
namespace simple
{

SimpleImageBase::Pointer Image::getITKImage( void )
{
  return m_Image;
}

ImageDataType Image::getImageDataType( void )
{
  return this->m_PimpleImage->getImageDataType();
}

std::string Image::toString( void )
{
  std::ostringstream out;
  this->m_Image->Print ( out );
  return out.str();
}

uint64_t Image::getWidth( void )
{
  SimpleImageBase::RegionType region;
  region = this->m_Image->GetLargestPossibleRegion();
  return region.GetSize()[0];
}

uint64_t Image::getHeight( void )
{
  SimpleImageBase::RegionType region;
  region = this->m_Image->GetLargestPossibleRegion();
  return region.GetSize()[1];
}

uint64_t Image::getDepth( void )
{
  SimpleImageBase::RegionType region;
  region = this->m_Image->GetLargestPossibleRegion();
  return region.GetSize()[2];
}
}
}
