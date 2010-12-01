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
  std::ostringstream out;
  // todo bring me back
  // this->m_PimpleImage->Print ( out );
  out << "ToString is not currently implemented because the itk::Image class obscured.\n...there be dragons here..." << std::endl;
  out << this->GetImageBase();
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
