#ifdef _MFC_VER
#pragma warning(disable:4996)
#endif

#include "sitkImportImageFilter.h"

#include <itkImage.h>
#include <itkVectorImage.h>

// private namespace
namespace
{
const unsigned int UnusedDimension = 2;
}

namespace itk {
namespace simple {

ImportImageFilter::ImportImageFilter()
{
  m_NumberOfComponentsPerPixel = 0;
  m_PixelIDValue = sitkUnknown;
  m_Origin = std::vector<double>( 3, 0.0 );
  m_Spacing = std::vector<double>( 3, 1.0 );
  this->m_Buffer = NULL;

  // list of pixel types supported
  typedef NonLabelPixelIDTypeList PixelIDTypeList;

  this->m_MemberFactory.reset( new detail::MemberFunctionFactory<MemberFunctionType>( this ) );

  this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 3 > ();
  this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 2 > ();
}

void ImportImageFilter::SetSpacing( const std::vector< double > &spacing )
{
  this->m_Spacing = spacing;
}

void ImportImageFilter::SetOrigin( const std::vector< double > &origin )
{
  this->m_Origin = origin;
}

void ImportImageFilter::SetSize( const std::vector< unsigned int > &size )
{
  this->m_Size = size;
}

void ImportImageFilter::SetBufferAsInt8( int8_t * buffer, unsigned int numberOfComponents )
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
}
void ImportImageFilter::SetBufferAsUInt8( uint8_t * buffer, unsigned int numberOfComponents )
{
  this->m_Buffer = buffer;
  this->m_NumberOfComponentsPerPixel = numberOfComponents;
  if ( this->m_NumberOfComponentsPerPixel == 1 )
    {
    this->m_PixelIDValue = ImageTypeToPixelIDValue< itk::Image<uint8_t, UnusedDimension> >::Result;
    }
  else
    {
    this->m_PixelIDValue = ImageTypeToPixelIDValue< itk::VectorImage<int8_t, UnusedDimension> >::Result;
    }
}
void ImportImageFilter::SetBufferAsInt16( int16_t * buffer, unsigned int numberOfComponents )
{
  this->m_Buffer = buffer;
  this->m_NumberOfComponentsPerPixel = numberOfComponents;
  if ( this->m_NumberOfComponentsPerPixel == 1 )
    {
    this->m_PixelIDValue = ImageTypeToPixelIDValue< itk::Image<int16_t, UnusedDimension> >::Result;
    }
  else
    {
    this->m_PixelIDValue = ImageTypeToPixelIDValue< itk::VectorImage<int8_t, UnusedDimension> >::Result;
    }
}
void ImportImageFilter::SetBufferAsUInt16( uint16_t * buffer, unsigned int numberOfComponents )
{
  this->m_Buffer = buffer;
  this->m_NumberOfComponentsPerPixel = numberOfComponents;
  if ( this->m_NumberOfComponentsPerPixel == 1 )
    {
    this->m_PixelIDValue = ImageTypeToPixelIDValue< itk::Image<uint16_t, UnusedDimension> >::Result;
    }
  else
    {
    this->m_PixelIDValue = ImageTypeToPixelIDValue< itk::VectorImage<int8_t, UnusedDimension> >::Result;
    }
}
void ImportImageFilter::SetBufferAsInt32( int32_t * buffer, unsigned int numberOfComponents )
{
  this->m_Buffer = buffer;
  this->m_NumberOfComponentsPerPixel = numberOfComponents;
  if ( this->m_NumberOfComponentsPerPixel == 1 )
    {
    this->m_PixelIDValue = ImageTypeToPixelIDValue< itk::Image<int32_t, UnusedDimension> >::Result;
    }
  else
    {
    this->m_PixelIDValue = ImageTypeToPixelIDValue< itk::VectorImage<int8_t, UnusedDimension> >::Result;
    }
}
void ImportImageFilter::SetBufferAsUInt32( uint32_t * buffer, unsigned int numberOfComponents )
{
  this->m_Buffer = buffer;
  if ( this->m_NumberOfComponentsPerPixel == 1 )
    {
    this->m_PixelIDValue = ImageTypeToPixelIDValue< itk::Image<uint32_t, UnusedDimension> >::Result;
    }
  else
    {
    this->m_PixelIDValue = ImageTypeToPixelIDValue< itk::VectorImage<int8_t, UnusedDimension> >::Result;
    }
}

void ImportImageFilter::SetBufferAsFloat( float * buffer, unsigned int numberOfComponents )
{
  this->m_Buffer = buffer;
  this->m_NumberOfComponentsPerPixel = numberOfComponents;
  if ( this->m_NumberOfComponentsPerPixel == 1 )
    {
    this->m_PixelIDValue = ImageTypeToPixelIDValue< itk::Image<float, UnusedDimension> >::Result;
    }
  else
    {
    this->m_PixelIDValue = ImageTypeToPixelIDValue< itk::VectorImage<int8_t, UnusedDimension> >::Result;
    }
}
void ImportImageFilter::SetBufferAsDouble( double * buffer, unsigned int numberOfComponents )
{
  this->m_Buffer = buffer;
  this->m_NumberOfComponentsPerPixel = numberOfComponents;
  if ( this->m_NumberOfComponentsPerPixel == 1 )
    {
    this->m_PixelIDValue = ImageTypeToPixelIDValue< itk::Image<double, UnusedDimension> >::Result;
    }
  else
    {
    this->m_PixelIDValue = ImageTypeToPixelIDValue< itk::VectorImage<int8_t, UnusedDimension> >::Result;
    }
}


#define PRINT_IVAR_MACRO( VAR ) "\t" << #VAR << ": " << VAR << std::endl

std::string ImportImageFilter::ToString() const
{
  std::ostringstream out;

  out << "itk::simple::ImportImageFilter\n"
      << PRINT_IVAR_MACRO( m_NumberOfComponentsPerPixel )
      << PRINT_IVAR_MACRO( m_PixelIDValue )
    //         << PRINT_IVAR_MACRO( m_Origin )
//          << PRINT_IVAR_MACRO( m_Spacing )
//          << PRINT_IVAR_MACRO( m_Size )
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

  typedef TImageType                            ImageType;
  typedef typename ImageType::InternalPixelType PixelType;
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
  image->SetRegions( region );


  size_t numberOfElements = m_NumberOfComponentsPerPixel;
  for(unsigned int si = 0; si < Dimension; si++ )
    {
    numberOfElements *= size[si];
    }

  // todo set direction

  const bool TheContainerWillTakeCareOfDeletingTheMemoryBuffer = false;

  // Set the image's pixel container to import the pointer provided.
  image->GetPixelContainer()->SetImportPointer(static_cast<typename ImageType::InternalPixelType*>(m_Buffer), numberOfElements,
                                               TheContainerWillTakeCareOfDeletingTheMemoryBuffer);


  //
  // Meta-programmed method to set the number of components if a
  // vector image
  //
  this->SetNumberOfComponentsOnImage( image.GetPointer() );

  return Image(image);
}

template <class TFilterType>
typename EnableIf<IsVector<TFilterType>::Value>::Type
ImportImageFilter::SetNumberOfComponentsOnImage ( TFilterType*image )
{
  image->SetNumberOfComponentsPerPixel( m_NumberOfComponentsPerPixel );
}

}
}
