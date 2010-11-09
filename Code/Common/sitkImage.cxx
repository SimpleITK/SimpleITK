#include "sitkImage.h"

namespace itk
{
namespace simple
{

SimpleImageBase::Pointer Image::GetITKImage( void )
{
  return m_Image;
}

ImageDataType Image::GetImageDataType( void )
{
  return this->m_PimpleImage->GetImageDataType();
}

std::string Image::ToString( void )
{
  std::ostringstream out;
  this->m_Image->Print ( out );
  return out.str();
}

uint64_t Image::GetWidth( void )
{
  SimpleImageBase::RegionType region;
  region = this->m_Image->GetLargestPossibleRegion();
  return region.GetSize()[0];
}

uint64_t Image::GetHeight( void )
{
  SimpleImageBase::RegionType region;
  region = this->m_Image->GetLargestPossibleRegion();
  return region.GetSize()[1];
}

uint64_t Image::GetDepth( void )
{
  SimpleImageBase::RegionType region;
  region = this->m_Image->GetLargestPossibleRegion();
  return region.GetSize()[2];
}
}
}
