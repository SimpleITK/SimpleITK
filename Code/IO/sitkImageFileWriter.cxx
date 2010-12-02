#include "sitkImageFileWriter.h"
#include <itkImageIOBase.h>
#include <itkImageFileWriter.h>
#include <itkImageRegionIterator.h>

namespace itk {
namespace simple {

ImageFileWriter::ImageFileWriter()
  {
  this->m_MemberFactory.reset( new detail::MemberFunctionFactory<MemberFunctionType>( this ) );

  this->m_MemberFactory->RegisterMemberFunctions< PixelTypeList, 3 > ();
  this->m_MemberFactory->RegisterMemberFunctions< PixelTypeList, 2 > ();
  }

ImageFileWriter& ImageFileWriter::SetFilename ( std::string fn )
  {
  this->m_Filename = fn;
  return *this;
  }

std::string ImageFileWriter::GetFilename()
  {
  return this->m_Filename;
  }

ImageFileWriter& ImageFileWriter::Execute ( Image::Pointer image )
  {
    ImageDataType type = image->GetDataType();
    unsigned int dimension = image->GetDimension();

    return this->m_MemberFactory->GetMemberFunction( type, dimension )( image );
    return *this;
  }

//-----------------------------------------------------------------------------
template <class InputImageType>
ImageFileWriter& ImageFileWriter::ExecuteInternal( Image::Pointer inImage )
  {
    // typedef itk::Image<T,3> InputImageType;
  typename InputImageType::Pointer image =
    dynamic_cast <InputImageType*> ( inImage->GetImageBase().GetPointer() );

  // handle 2D images differently
  if (inImage->GetDimension() == 2)
    {

    // see if we're dealing with a jpg or png
    size_t pos = m_Filename.rfind(".");
    std::string suffix = m_Filename.substr(pos+1,m_Filename.size()-pos+1);

    if (std::strcmp(suffix.c_str(), "jpg") == 0 ||
        std::strcmp(suffix.c_str(), "JPG") == 0 ||
        std::strcmp(suffix.c_str(), "jpeg") == 0 ||
        std::strcmp(suffix.c_str(), "JPEG") == 0 ||
        std::strcmp(suffix.c_str(), "png") == 0 ||
        std::strcmp(suffix.c_str(), "PNG") == 0)
      {
      // set up the output 2D Region
      typedef itk::Image<unsigned char,2> OutputImageType;
      typename OutputImageType::SizeType size;
      size[0] = inImage->GetWidth();
      size[1] = inImage->GetHeight();
      typename OutputImageType::IndexType start;
      start[0] = 0;
      start[1] = 0;
      typename OutputImageType::RegionType outputRegion;
      outputRegion.SetSize(size);
      outputRegion.SetIndex(start);

      // set up the output 2D image
      typename OutputImageType::Pointer outputImage = OutputImageType::New();
      outputImage->SetRegions(outputRegion);
      typename OutputImageType::SpacingType spacing;
      spacing[0] = image->GetSpacing()[0];
      spacing[1] = image->GetSpacing()[1];
      outputImage->SetSpacing(spacing);
      typename OutputImageType::PointType origin;
      origin[0] = image->GetOrigin()[0];
      origin[1] = image->GetOrigin()[1];
      outputImage->SetOrigin(origin);
      outputImage->Allocate();

      // set up the iterators
      typedef itk::ImageRegionConstIterator< InputImageType > InputIteratorType;
      typedef itk::ImageRegionIterator< OutputImageType > OutputIteratorType;
      InputIteratorType inputIt( image, image->GetLargestPossibleRegion() );
      OutputIteratorType outputIt( outputImage, outputRegion );

      // do the conversin
      inputIt.GoToBegin();
      outputIt.GoToBegin();
      while( !inputIt.IsAtEnd() )
        {
        outputIt.Set( static_cast<unsigned char>(inputIt.Get()) );
        ++inputIt;
        ++outputIt;
        }

      // write out the 2D image
      typedef itk::ImageFileWriter<OutputImageType> Writer;
      typename Writer::Pointer writer = Writer::New();
      writer->UseCompressionOn();
      writer->SetFileName ( this->m_Filename.c_str() );
      writer->SetInput ( outputImage );
      writer->Update();
      }
    else
      {
      // set up the output 2D Region
      // typedef itk::Image<T,2> OutputImageType;
        typedef InputImageType OutputImageType;
      typename OutputImageType::SizeType size;
      size[0] = inImage->GetWidth();
      size[1] = inImage->GetHeight();
      typename OutputImageType::IndexType start;
      start[0] = 0;
      start[1] = 0;
      typename OutputImageType::RegionType outputRegion;
      outputRegion.SetSize(size);
      outputRegion.SetIndex(start);

      // set up the output 2D image
      typename OutputImageType::Pointer outputImage = OutputImageType::New();
      outputImage->SetRegions(outputRegion);
      typename OutputImageType::SpacingType spacing;
      spacing[0] = image->GetSpacing()[0];
      spacing[1] = image->GetSpacing()[1];
      outputImage->SetSpacing(spacing);
      typename OutputImageType::PointType origin;
      origin[0] = image->GetOrigin()[0];
      origin[1] = image->GetOrigin()[1];
      outputImage->SetOrigin(origin);
      outputImage->Allocate();

      // set up the iterators
      typedef itk::ImageRegionConstIterator< InputImageType > InputIteratorType;
      typedef itk::ImageRegionIterator< OutputImageType > OutputIteratorType;
      InputIteratorType inputIt( image, image->GetLargestPossibleRegion() );
      OutputIteratorType outputIt( outputImage, outputRegion );

      // do the conversin
      inputIt.GoToBegin();
      outputIt.GoToBegin();
      while( !inputIt.IsAtEnd() )
        {
        outputIt.Set( inputIt.Get() );
        ++inputIt;
        ++outputIt;
        }

      // write out the 2D image
      typedef itk::ImageFileWriter<OutputImageType> Writer;
      typename Writer::Pointer writer = Writer::New();
      writer->UseCompressionOn();
      writer->SetFileName ( this->m_Filename.c_str() );
      writer->SetInput ( outputImage );
      writer->Update();
      }
    }
  else
    {
    typedef itk::ImageFileWriter<InputImageType> Writer;
    typename Writer::Pointer writer = Writer::New();
      writer->UseCompressionOn();
    writer->SetFileName ( this->m_Filename.c_str() );
    writer->SetInput ( image );
    writer->Update();
    }
  return *this;
  }

} // end namespace simple
} // end namespace itk
