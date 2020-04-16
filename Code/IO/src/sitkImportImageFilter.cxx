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
#ifdef _MFC_VER
#pragma warning(disable:4996)
#endif

#include "sitkImportImageFilter.h"
#include "sitkExceptionObject.h"

#include <itkImage.h>
#include <itkVectorImage.h>

#include <iterator>

namespace itk {
namespace simple {

// private namespace
namespace
{
const unsigned int UnusedDimension = 2;
}


Image ImportAsInt8(
    int8_t * buffer,
    const std::vector< unsigned int > &size,
    const std::vector< double > &spacing,
    const std::vector< double > &origin,
    const std::vector< double > &direction,
    unsigned int numberOfComponents
) {
    ImportImageFilter import;
    import.SetSize( size );
    import.SetSpacing( spacing );
    import.SetOrigin( origin );
    import.SetDirection( direction );
    import.SetBufferAsInt8( buffer, numberOfComponents );
    return import.Execute();
}

Image ImportAsUInt8(
    uint8_t * buffer,
    const std::vector< unsigned int > &size,
    const std::vector< double > &spacing,
    const std::vector< double > &origin,
    const std::vector< double > &direction,
    unsigned int numberOfComponents
) {
    ImportImageFilter import;
    import.SetSize( size );
    import.SetSpacing( spacing );
    import.SetOrigin( origin );
    import.SetDirection( direction );
    import.SetBufferAsUInt8( buffer, numberOfComponents );
    return import.Execute();
}

Image ImportAsInt16(
    int16_t * buffer,
    const std::vector< unsigned int > &size,
    const std::vector< double > &spacing,
    const std::vector< double > &origin,
    const std::vector< double > &direction,
    unsigned int numberOfComponents
) {
    ImportImageFilter import;
    import.SetSize( size );
    import.SetSpacing( spacing );
    import.SetOrigin( origin );
    import.SetDirection( direction );
    import.SetBufferAsInt16( buffer, numberOfComponents );
    return import.Execute();
}

Image ImportAsUInt16(
    uint16_t * buffer,
    const std::vector< unsigned int > &size,
    const std::vector< double > &spacing,
    const std::vector< double > &origin,
    const std::vector< double > &direction,
    unsigned int numberOfComponents
) {
    ImportImageFilter import;
    import.SetSize( size );
    import.SetSpacing( spacing );
    import.SetOrigin( origin );
    import.SetDirection( direction );
    import.SetBufferAsUInt16( buffer, numberOfComponents );
    return import.Execute();
}

Image ImportAsInt32(
    int32_t * buffer,
    const std::vector< unsigned int > &size,
    const std::vector< double > &spacing,
    const std::vector< double > &origin,
    const std::vector< double > &direction,
    unsigned int numberOfComponents
) {
    ImportImageFilter import;
    import.SetSize( size );
    import.SetSpacing( spacing );
    import.SetOrigin( origin );
    import.SetDirection( direction );
    import.SetBufferAsInt32( buffer, numberOfComponents );
    return import.Execute();
}

Image ImportAsUInt32(
    uint32_t * buffer,
    const std::vector< unsigned int > &size,
    const std::vector< double > &spacing,
    const std::vector< double > &origin,
    const std::vector< double > &direction,
    unsigned int numberOfComponents
) {
    ImportImageFilter import;
    import.SetSize( size );
    import.SetSpacing( spacing );
    import.SetOrigin( origin );
    import.SetDirection( direction );
    import.SetBufferAsUInt32( buffer, numberOfComponents );
    return import.Execute();
}

Image ImportAsInt64(
    int64_t * buffer,
    const std::vector< unsigned int > &size,
    const std::vector< double > &spacing,
    const std::vector< double > &origin,
    const std::vector< double > &direction,
    unsigned int numberOfComponents
) {
    ImportImageFilter import;
    import.SetSize( size );
    import.SetSpacing( spacing );
    import.SetOrigin( origin );
    import.SetDirection( direction );
    import.SetBufferAsInt64( buffer, numberOfComponents );
    return import.Execute();
}

Image ImportAsUInt64(
    uint64_t * buffer,
    const std::vector< unsigned int > &size,
    const std::vector< double > &spacing,
    const std::vector< double > &origin,
    const std::vector< double > &direction,
    unsigned int numberOfComponents
) {
    ImportImageFilter import;
    import.SetSize( size );
    import.SetSpacing( spacing );
    import.SetOrigin( origin );
    import.SetDirection( direction );
    import.SetBufferAsUInt64( buffer, numberOfComponents );
    return import.Execute();
}

Image ImportAsFloat(
    float * buffer,
    const std::vector< unsigned int > &size,
    const std::vector< double > &spacing,
    const std::vector< double > &origin,
    const std::vector< double > &direction,
    unsigned int numberOfComponents
) {
    ImportImageFilter import;
    import.SetSize( size );
    import.SetSpacing( spacing );
    import.SetOrigin( origin );
    import.SetDirection( direction );
    import.SetBufferAsFloat( buffer, numberOfComponents );
    return import.Execute();
}

Image ImportAsDouble(
    double * buffer,
    const std::vector< unsigned int > &size,
    const std::vector< double > &spacing,
    const std::vector< double > &origin,
    const std::vector< double > &direction,
    unsigned int numberOfComponents
) {
    ImportImageFilter import;
    import.SetSize( size );
    import.SetSpacing( spacing );
    import.SetOrigin( origin );
    import.SetDirection( direction );
    import.SetBufferAsDouble( buffer, numberOfComponents );
    return import.Execute();
}

ImportImageFilter::~ImportImageFilter() = default;

ImportImageFilter::ImportImageFilter()
{
  m_NumberOfComponentsPerPixel = 0;
  m_PixelIDValue = sitkUnknown;
  m_Origin = std::vector<double>( 3, 0.0 );
  m_Spacing = std::vector<double>( 3, 1.0 );
  this->m_Buffer = NULL;

  // list of pixel types supported
  using PixelIDTypeList = NonLabelPixelIDTypeList;

  this->m_MemberFactory.reset( new detail::MemberFunctionFactory<MemberFunctionType>( this ) );

  this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 4 > ();
  this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 3 > ();
  this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 2 > ();

}

ImportImageFilter::Self& ImportImageFilter::SetSpacing( const std::vector< double > &spacing )
{
  this->m_Spacing = spacing;
  return *this;
}

const std::vector< double > &ImportImageFilter::GetSpacing( ) const
{
  return this->m_Spacing;
}

ImportImageFilter::Self& ImportImageFilter::SetOrigin( const std::vector< double > &origin )
{
  this->m_Origin = origin;
  return *this;
}

const std::vector< double > &ImportImageFilter::GetOrigin( ) const
{
  return this->m_Origin;
}

ImportImageFilter::Self& ImportImageFilter::SetSize( const std::vector< unsigned int > &size )
{
  this->m_Size = size;
  return *this;
}

const std::vector< unsigned int > &ImportImageFilter::GetSize( ) const
{
  return this->m_Size;
}

ImportImageFilter::Self& ImportImageFilter::SetDirection( const std::vector< double > &direction )
{
  this->m_Direction = direction;
  return *this;
}

const std::vector< double > &ImportImageFilter::GetDirection( ) const
{
  return this->m_Direction;
}

ImportImageFilter::Self& ImportImageFilter::SetBufferAsInt8( int8_t * buffer, unsigned int numberOfComponents )
{
  this->m_Buffer = buffer;
  this->m_NumberOfComponentsPerPixel = numberOfComponents;
  if ( this->m_NumberOfComponentsPerPixel == 1 )
    {
    this->m_PixelIDValue = ImageTypeToPixelIDValue< itk::Image<int8_t, UnusedDimension> >::Result;
    }
  else
    {
    this->m_PixelIDValue = ImageTypeToPixelIDValue< itk::VectorImage<int8_t, UnusedDimension> >::Result;
    }
  return *this;
}
ImportImageFilter::Self& ImportImageFilter::SetBufferAsUInt8( uint8_t * buffer, unsigned int numberOfComponents )
{
  this->m_Buffer = buffer;
  this->m_NumberOfComponentsPerPixel = numberOfComponents;
  if ( this->m_NumberOfComponentsPerPixel == 1 )
    {
    this->m_PixelIDValue = ImageTypeToPixelIDValue< itk::Image<uint8_t, UnusedDimension> >::Result;
    }
  else
    {
    this->m_PixelIDValue = ImageTypeToPixelIDValue< itk::VectorImage<uint8_t, UnusedDimension> >::Result;
    }
  return *this;
}
ImportImageFilter::Self& ImportImageFilter::SetBufferAsInt16( int16_t * buffer, unsigned int numberOfComponents )
{
  this->m_Buffer = buffer;
  this->m_NumberOfComponentsPerPixel = numberOfComponents;
  if ( this->m_NumberOfComponentsPerPixel == 1 )
    {
    this->m_PixelIDValue = ImageTypeToPixelIDValue< itk::Image<int16_t, UnusedDimension> >::Result;
    }
  else
    {
    this->m_PixelIDValue = ImageTypeToPixelIDValue< itk::VectorImage<int16_t, UnusedDimension> >::Result;
    }
  return *this;
}
ImportImageFilter::Self& ImportImageFilter::SetBufferAsUInt16( uint16_t * buffer, unsigned int numberOfComponents )
{
  this->m_Buffer = buffer;
  this->m_NumberOfComponentsPerPixel = numberOfComponents;
  if ( this->m_NumberOfComponentsPerPixel == 1 )
    {
    this->m_PixelIDValue = ImageTypeToPixelIDValue< itk::Image<uint16_t, UnusedDimension> >::Result;
    }
  else
    {
    this->m_PixelIDValue = ImageTypeToPixelIDValue< itk::VectorImage<uint16_t, UnusedDimension> >::Result;
    }
  return *this;
}
ImportImageFilter::Self& ImportImageFilter::SetBufferAsInt32( int32_t * buffer, unsigned int numberOfComponents )
{
  this->m_Buffer = buffer;
  this->m_NumberOfComponentsPerPixel = numberOfComponents;
  if ( this->m_NumberOfComponentsPerPixel == 1 )
    {
    this->m_PixelIDValue = ImageTypeToPixelIDValue< itk::Image<int32_t, UnusedDimension> >::Result;
    }
  else
    {
    this->m_PixelIDValue = ImageTypeToPixelIDValue< itk::VectorImage<int32_t, UnusedDimension> >::Result;
    }
  return *this;
}
ImportImageFilter::Self& ImportImageFilter::SetBufferAsUInt32( uint32_t * buffer, unsigned int numberOfComponents )
{
  this->m_Buffer = buffer;
  this->m_NumberOfComponentsPerPixel = numberOfComponents;
  if ( this->m_NumberOfComponentsPerPixel == 1 )
    {
    this->m_PixelIDValue = ImageTypeToPixelIDValue< itk::Image<uint32_t, UnusedDimension> >::Result;
    }
  else
    {
    this->m_PixelIDValue = ImageTypeToPixelIDValue< itk::VectorImage<uint32_t, UnusedDimension> >::Result;
    }
  return *this;
}
ImportImageFilter::Self& ImportImageFilter::SetBufferAsInt64( int64_t * buffer, unsigned int numberOfComponents )
{
  this->m_Buffer = buffer;
  this->m_NumberOfComponentsPerPixel = numberOfComponents;
  if ( this->m_NumberOfComponentsPerPixel == 1 )
    {
    this->m_PixelIDValue = ImageTypeToPixelIDValue< itk::Image<int64_t, UnusedDimension> >::Result;
    }
  else
    {
    this->m_PixelIDValue = ImageTypeToPixelIDValue< itk::VectorImage<int64_t, UnusedDimension> >::Result;
    }
  return *this;
}
ImportImageFilter::Self& ImportImageFilter::SetBufferAsUInt64( uint64_t * buffer, unsigned int numberOfComponents )
{
  this->m_Buffer = buffer;
  this->m_NumberOfComponentsPerPixel = numberOfComponents;
  if ( this->m_NumberOfComponentsPerPixel == 1 )
    {
    this->m_PixelIDValue = ImageTypeToPixelIDValue< itk::Image<uint64_t, UnusedDimension> >::Result;
    }
  else
    {
    this->m_PixelIDValue = ImageTypeToPixelIDValue< itk::VectorImage<uint64_t, UnusedDimension> >::Result;
    }
  return *this;
}

ImportImageFilter::Self& ImportImageFilter::SetBufferAsFloat( float * buffer, unsigned int numberOfComponents )
{
  this->m_Buffer = buffer;
  this->m_NumberOfComponentsPerPixel = numberOfComponents;
  if ( this->m_NumberOfComponentsPerPixel == 1 )
    {
    this->m_PixelIDValue = ImageTypeToPixelIDValue< itk::Image<float, UnusedDimension> >::Result;
    }
  else
    {
    this->m_PixelIDValue = ImageTypeToPixelIDValue< itk::VectorImage<float, UnusedDimension> >::Result;
    }
  return *this;
}
ImportImageFilter::Self& ImportImageFilter::SetBufferAsDouble( double * buffer, unsigned int numberOfComponents )
{
  this->m_Buffer = buffer;
  this->m_NumberOfComponentsPerPixel = numberOfComponents;
  if ( this->m_NumberOfComponentsPerPixel == 1 )
    {
    this->m_PixelIDValue = ImageTypeToPixelIDValue< itk::Image<double, UnusedDimension> >::Result;
    }
  else
    {
    this->m_PixelIDValue = ImageTypeToPixelIDValue< itk::VectorImage<double, UnusedDimension> >::Result;
    }
  return *this;
}


#define PRINT_IVAR_MACRO( VAR ) "\t" << #VAR << ": " << VAR << std::endl

std::string ImportImageFilter::ToString() const
{
  std::ostringstream out;

  out << "itk::simple::ImportImageFilter\n"
      << PRINT_IVAR_MACRO( m_NumberOfComponentsPerPixel )
      << PRINT_IVAR_MACRO( m_PixelIDValue )
      << PRINT_IVAR_MACRO( m_Origin )
      << PRINT_IVAR_MACRO( m_Spacing )
      << PRINT_IVAR_MACRO( m_Size )
      << PRINT_IVAR_MACRO( m_Direction )
      << PRINT_IVAR_MACRO( m_Buffer );
  return out.str();
}

Image ImportImageFilter::Execute ()
{
  unsigned int imageDimension = this->m_Size.size();

  // perform sanity check on some parameters
  if (  this->m_NumberOfComponentsPerPixel == 0 || this->m_PixelIDValue == sitkUnknown )
    {
    sitkExceptionMacro( << "PixelType or NumberOfComponentsPerPixel are invalid!" );
    }


  if ( imageDimension != 3 && imageDimension != 2 )
    {
    sitkExceptionMacro(<< "The length of size is invalid! "
                       << "Only image of dimension 2 or 3 are supported." );
    }

  if ( !this->m_MemberFactory->HasMemberFunction( this->m_PixelIDValue, imageDimension ) )
    {
    sitkExceptionMacro( << "PixelType is not supported!" << std::endl
                        << "Pixel Type: "
                        << GetPixelIDValueAsString( this->m_PixelIDValue ) << std::endl
                        << "Refusing to load! " << std::endl );
    }

  return this->m_MemberFactory->GetMemberFunction( this->m_PixelIDValue, imageDimension )();
}


template <class TImageType>
Image ImportImageFilter::ExecuteInternal( )
{

  using ImageType = TImageType;
  const unsigned int Dimension = ImageType::ImageDimension;

  // if the InstantiatedToken is correctly implemented this should
  // not occur
  assert( ImageTypeToPixelIDValue<ImageType>::Result != (int)sitkUnknown );

  typename ImageType::Pointer image = ImageType::New();


  //
  //  Origin
  //
  typename ImageType::PointType origin = sitkSTLVectorToITK< typename ImageType::PointType >( this->m_Origin );
  image->SetOrigin( origin );

  //
  //  Spacing
  //
  typename ImageType::SpacingType spacing = sitkSTLVectorToITK< typename ImageType::SpacingType >( this->m_Spacing );
  image->SetSpacing( spacing );

  //
  //  Size and Region
  //
  typename ImageType::RegionType region;
  typename ImageType::SizeType size = sitkSTLVectorToITK< typename ImageType::SizeType >( this->m_Size );
  region.SetSize(size);
  // set the size and region to the ITK image.
  image->SetRegions( region );

  //
  // Direction, if m_Direction is not set, use ITK's default which is
  // an identity.
  //
  if (!this->m_Direction.empty() )
    {
    image->SetDirection(  sitkSTLToITKDirection<typename ImageType::DirectionType>( this->m_Direction ) );
    }


  size_t numberOfElements = m_NumberOfComponentsPerPixel;
  for(unsigned int si = 0; si < Dimension; si++ )
    {
    numberOfElements *= size[si];
    }

  const bool TheContainerWillTakeCareOfDeletingTheMemoryBuffer = false;

  // Set the image's pixel container to import the pointer provided.
  image->GetPixelContainer()->SetImportPointer(static_cast<typename ImageType::InternalPixelType*>(m_Buffer), numberOfElements,
                                               TheContainerWillTakeCareOfDeletingTheMemoryBuffer);


  //
  // Meta-programmed method to set the number of components if a
  // vector image
  //
  this->SetNumberOfComponentsOnImage( image.GetPointer() );

  // This line must be the last line in the function to prevent a deep
  // copy caused by a implicit sitk::MakeUnique
  return Image( image );
}

template <class TFilterType>
typename std::enable_if<IsVector<TFilterType>::Value>::type
ImportImageFilter::SetNumberOfComponentsOnImage ( TFilterType*image )
{
  image->SetNumberOfComponentsPerPixel( m_NumberOfComponentsPerPixel );
}

}
}
