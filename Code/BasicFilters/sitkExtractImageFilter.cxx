#include "sitkExtractImageFilter.h"
#include "sitkMacro.h"

#include "itkVectorImage.h"

namespace itk {
namespace simple {

//----------------------------------------------------------------------------

//
// Default constructor that initializes parameters
//
ExtractImageFilter::ExtractImageFilter ()
  {
  this->m_Slice = 0;
  this->m_MemberFactory.reset( new detail::MemberFunctionFactory<MemberFunctionType>( this ) );
  this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 3 > ();
  }

//
// ToString
//
std::string ExtractImageFilter::ToString() const
  {
  std::ostringstream out;
  out << "itk::simple::ExtractImageFilter\n"
      << "\tSlice: " << this->m_Slice << "\n";
  return out.str();
  }


  Image* ExtractImageFilter::Execute ( Image* image, size_t s )
  {
  this->m_Slice = s;
  return Execute ( image );
  }

//
// Execute
//
Image* ExtractImageFilter::Execute ( Image* image )
  {

    PixelIDValueType type = image->GetPixelIDValue();
    unsigned int dimension = image->GetDimension();
    if ( dimension != 3 ) {
      sitkExceptionMacro ( << "ExtractImageFilter operates on 3 dimensional images only" );
    }
    return this->m_MemberFactory->GetMemberFunction( type, dimension )( image );
  }

//----------------------------------------------------------------------------

//
// ExecuteInternal
//
template <class TImageType>
Image* ExtractImageFilter::ExecuteInternal ( Image* inImage )
  {
  typename TImageType::Pointer image =
    dynamic_cast <TImageType*> ( inImage->GetImageBase().GetPointer() );

  if ( image.IsNull() )
    {
    sitkExceptionMacro( << "Could not cast input image to proper type" );
    }

  typedef itk::ExtractImageFilter<TImageType, TImageType> FilterType;
  typename FilterType::Pointer filter = FilterType::New();

  filter->SetInput ( image );

  typename TImageType::IndexType index;
  typename TImageType::SizeType size;
  index.Fill ( 0 );
  index[2] = this->m_Slice;
  size = image->GetLargestPossibleRegion().GetSize();
  size[2] = 1;
  typename TImageType::RegionType region ( index, size );
  
  filter->SetDirectionCollapseToSubmatrix();
  filter->SetExtractionRegion ( region );

  filter->Update();
  typename TImageType::Pointer filterOutput = filter->GetOutput();

  // Make the index 0,0,0
  index.Fill ( 0 );
  region.SetIndex ( index );
  filterOutput->SetRegions ( region );
  Image* out = new Image( filterOutput );
  
  filterOutput->DisconnectPipeline();
  return out;
  }

} // end namespace simple
} // end namespace itk
