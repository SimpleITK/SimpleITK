
#include "sitkImageFileWriter.h"

#include <itkImageIOBase.h>
#include <itkImageFileWriter.h>
#include <itkImageRegionIterator.h>

namespace itk {
namespace simple {
  void WriteImage ( Image* image, std::string filename ) { ImageFileWriter writer; writer.SetFileName ( filename ).Execute ( image ); }

ImageFileWriter::ImageFileWriter()
  {
  this->m_MemberFactory.reset( new detail::MemberFunctionFactory<MemberFunctionType>( this ) );

  this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 3 > ();
  this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 2 > ();
  }

ImageFileWriter& ImageFileWriter::SetFileName ( std::string fn )
  {
  this->m_FileName = fn;
  return *this;
  }

std::string ImageFileWriter::GetFileName()
  {
  return this->m_FileName;
  }

ImageFileWriter& ImageFileWriter::Execute ( Image* image )
  {
    PixelIDValueType type = image->GetPixelIDValue();
    unsigned int dimension = image->GetDimension();

    return this->m_MemberFactory->GetMemberFunction( type, dimension )( image );
    return *this;
  }

//-----------------------------------------------------------------------------
template <class InputImageType>
ImageFileWriter& ImageFileWriter::ExecuteInternal( Image* inImage )
  {
    typename InputImageType::Pointer image =
      dynamic_cast <InputImageType*> ( inImage->GetImageBase() );

    typedef itk::ImageFileWriter<InputImageType> Writer;
    typename Writer::Pointer writer = Writer::New();
    writer->UseCompressionOn();
    writer->SetFileName ( this->m_FileName.c_str() );
    writer->SetInput ( image );
    writer->Update();

    return *this;
  }

} // end namespace simple
} // end namespace itk
