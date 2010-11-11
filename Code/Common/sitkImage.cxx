#include "sitkImage.h"

namespace itk
{
namespace simple
{

itk::DataObject::Pointer Image::GetImageBase( void )
{
  assert( m_PimpleImage.get() );
  return m_PimpleImage->GetDataBase();
}

itk::DataObject::ConstPointer Image::GetImageBase( void ) const
{
  assert( m_PimpleImage.get() );
  return m_PimpleImage->GetDataBase().GetPointer();
}

ImageDataType Image::GetImageDataType( void )
{
  return this->m_PimpleImage->GetImageDataType();
}

std::string Image::ToString( void )
{
  std::ostringstream out;
  // todo bring me back
  //this->m_Image->Print ( out );
  return out.str();
}

uint64_t Image::GetWidth( void )
{
  return this->m_PimpleImage->GetWidth();
}

uint64_t Image::GetHeight( void )
{
  return this->m_PimpleImage->GetHeight();
}

uint64_t Image::GetDepth( void )
{
  return this->m_PimpleImage->GetDepth();
}
}
}
