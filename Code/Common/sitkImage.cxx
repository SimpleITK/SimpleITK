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

ImageDataType Image::GetDataType( void ) const
{
  return this->m_PimpleImage->GetDataType();
}

unsigned int Image::GetDimension( void ) const
{
  return this->m_PimpleImage->GetDimension();
}

std::string Image::ToString( void )
{
  return this->m_PimpleImage->ToString();
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
