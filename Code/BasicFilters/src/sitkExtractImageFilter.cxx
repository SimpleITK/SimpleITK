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

#include "itkImage.h"
#include "itkVectorImage.h"
#include "itkLabelMap.h"
#include "itkLabelObject.h"
#include "itkNumericTraits.h"
#include "itkNumericTraitsVariableLengthVectorPixel.h"
#include "itkVectorIndexSelectionCastImageFilter.h"
#include "itkComposeImageFilter.h"

#include "sitkExtractImageFilter.h"
#include "itkExtractImageFilter.h"



namespace itk {
namespace simple {

//-----------------------------------------------------------------------------

//
// Default constructor that initializes parameters
//
ExtractImageFilter::ExtractImageFilter ()
{
  this->m_MemberFactory.reset( new detail::MemberFunctionFactory<MemberFunctionType>( this ) );

  this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 2, SITK_MAX_DIMENSION > ();
}

//
// Destructor
//
ExtractImageFilter::~ExtractImageFilter() = default;

//
// ToString
//
std::string ExtractImageFilter::ToString() const
{
  std::ostringstream out;
  out << "itk::simple::ExtractImageFilter\n";
  out << "  Size: ";
  this->ToStringHelper(out, this->m_Size);
  out << std::endl;
  out << "  Index: ";
  this->ToStringHelper(out, this->m_Index);
  out << std::endl;
  out << "  DirectionCollapseToStrategy: ";
  this->ToStringHelper(out, this->m_DirectionCollapseToStrategy);
  out << std::endl;

  out << ProcessObject::ToString();
  return out.str();
}

//
// Execute
//
Image ExtractImageFilter::Execute ( const Image& image1 )
{
  const PixelIDValueEnum type = image1.GetPixelID();
  const unsigned int dimension = image1.GetDimension();

  return this->m_MemberFactory->GetMemberFunction( type, dimension )( image1 );
}
Image ExtractImageFilter::Execute ( Image&& image1 )
{
  Image &temp = image1;
  auto autoResetInPlace = make_scope_exit([this, &temp]{this->m_InPlace=false; Image moved(std::move(temp));});
  if (temp.IsUnique())
    {
    m_InPlace = true;
    }
  return this->Execute( image1 );
}

//-----------------------------------------------------------------------------

//
// Custom Casts
//
namespace {

}

//-----------------------------------------------------------------------------

sitkClangDiagnosticPush();
sitkClangWarningIgnore("-Wunused-local-typedef");

//
// ExecuteInternal
//
template <class TImageType>
Image ExtractImageFilter::ExecuteInternal ( const Image& inImage1 )
{
  // Define the input and output image types
  using InputImageType = TImageType;


  // Get the pointer to the ITK image contained in image1
  typename InputImageType::ConstPointer image1 = this->CastImageToITK<InputImageType>( inImage1 );

  unsigned int outputDimension = 0;
  if (!m_Size.empty())
    {
    for(unsigned int i = 0; i < m_Size.size() && i < TImageType::ImageDimension; ++i )
      {
      if (m_Size[i] != 0)
        {
        ++outputDimension;
        }
      }
    if ( outputDimension < 2 || outputDimension > SITK_MAX_DIMENSION )
      {
      sitkExceptionMacro( "The extraction size has unsupported output dimension of " << outputDimension << "." );
      }
    }

  return this->ExecuteInternal<TImageType>( image1, outputDimension, std::integral_constant<unsigned int, TImageType::ImageDimension>() );
}


template <class TImageType, unsigned int OutputDimension>
Image ExtractImageFilter::ExecuteInternal ( const TImageType *image1, unsigned int extractDimension, std::integral_constant<unsigned int, OutputDimension> )
{
  if ( extractDimension != OutputDimension )
    {
    return this->ExecuteInternal<TImageType>(image1, extractDimension, std::integral_constant<unsigned int, OutputDimension-1>());
    }

  using InputImageType = TImageType;
  using OutputImageType = typename InputImageType::template Rebind<typename InputImageType::PixelType, OutputDimension>::Type;
  using FilterType = itk::ExtractImageFilter<InputImageType, OutputImageType >;

  // Set up the ITK filter
  typename FilterType::Pointer filter = FilterType::New();

  filter->SetInput( 0, image1 );

  typename InputImageType::RegionType itkRegion( sitkSTLVectorToITK<typename InputImageType::IndexType>( m_Index ), sitkSTLVectorToITK<typename InputImageType::SizeType>( m_Size) );
  filter->SetExtractionRegion( itkRegion );
  filter->SetDirectionCollapseToStrategy ( typename FilterType::DirectionCollapseStrategyEnum ( int( this->m_DirectionCollapseToStrategy ) ) );
  filter->SetInPlace( m_InPlace );

  this->PreUpdate( filter.GetPointer() );

  // Run the ITK filter and return the output as a SimpleITK image
  filter->Update();

  typename FilterType::OutputImageType::Pointer itkOutImage{ filter->GetOutput()};
  filter = nullptr;
  this->FixNonZeroIndex( itkOutImage.GetPointer() );
  return Image{ this->CastITKToImage( itkOutImage.GetPointer() ) };

}


template <class TImageType>
Image ExtractImageFilter::ExecuteInternal ( const TImageType *, unsigned int extractDimension,  std::integral_constant<unsigned int, 1> )
{
  sitkExceptionMacro("The extraction size: " << m_Size << " has dimension of " << extractDimension << ". At least two dimensions in size must be non-zero.");
}

sitkClangDiagnosticPop();

//-----------------------------------------------------------------------------


//
// Function to run the Execute method of this filter
//
Image Extract ( const Image& image1, std::vector<unsigned int> size, std::vector<int> index, ExtractImageFilter::DirectionCollapseToStrategyType directionCollapseToStrategy )
{
  ExtractImageFilter filter;
  filter.SetSize( size );  filter.SetIndex( index );  filter.SetDirectionCollapseToStrategy( directionCollapseToStrategy );
  return filter.Execute ( image1 );
}
//
// Function to run the Execute method of this filter
//
Image Extract ( Image&& image1, std::vector<unsigned int> size, std::vector<int> index, ExtractImageFilter::DirectionCollapseToStrategyType directionCollapseToStrategy )
{
  ExtractImageFilter filter;
  filter.SetSize( std::move(size) );  filter.SetIndex( std::move(index) );  filter.SetDirectionCollapseToStrategy( directionCollapseToStrategy );
  return filter.Execute ( std::move(image1) );
}

} // end namespace simple
} // end namespace itk
