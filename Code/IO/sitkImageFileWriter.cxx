#include "sitkImageFileWriter.h"
#include <itkImageIOBase.h>
#include <itkImageFileWriter.h>
#include <itkImageRegionIterator.h>

namespace itk {
namespace simple {

ImageFileWriter::ImageFileWriter()
  {
  this->m_MemberFactory.reset( new detail::MemberFunctionFactory<MemberFunctionType>( this ) );

  this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 3 > ();
  this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 2 > ();
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
    PixelIDValueType type = image->GetPixelIDValue();
    unsigned int dimension = image->GetDimension();

    return this->m_MemberFactory->GetMemberFunction( type, dimension )( image );
    return *this;
  }

//-----------------------------------------------------------------------------
template <class InputImageType>
ImageFileWriter& ImageFileWriter::ExecuteInternal( Image::Pointer inImage )
  {
    typename InputImageType::Pointer image =
      dynamic_cast <InputImageType*> ( inImage->GetImageBase().GetPointer() );

    typedef itk::ImageFileWriter<InputImageType> Writer;
    typename Writer::Pointer writer = Writer::New();
    writer->SetFileName ( this->m_Filename.c_str() );
    writer->SetInput ( image );
    writer->Update();

    return *this;
  }

} // end namespace simple
} // end namespace itk
