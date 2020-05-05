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
#ifdef _MSC_VER
#pragma warning(disable:4996)
#endif

#include "sitkImageFileReader.h"

#include <itkImageFileReader.h>
#include <itkExtractImageFilter.h>

#include "sitkMetaDataDictionaryCustomCast.hxx"

namespace itk {
  namespace simple {

  constexpr unsigned int SITK_IO_INPUT_MAX_DIMENSION = 5 > SITK_MAX_DIMENSION ? 5 : SITK_MAX_DIMENSION;
  namespace {

      // Simple ITK must use a zero based index
      template< class TImageType>
      static void FixNonZeroIndex( TImageType * img )
      {
        assert( img != nullptr );

        typename TImageType::RegionType r = img->GetLargestPossibleRegion();
        typename TImageType::IndexType idx = r.GetIndex();

        for( unsigned int i = 0; i < TImageType::ImageDimension; ++i )
          {

          if ( idx[i] != 0 )
            {
            // if any of the indcies are non-zero, then just fix it
            typename TImageType::PointType o;
            img->TransformIndexToPhysicalPoint( idx, o );
            img->SetOrigin( o );

            idx.Fill( 0 );
            r.SetIndex( idx );

            // Need to set the buffered region to match largest
            img->SetRegions( r );

            return;
            }
          }
      }
  }

  Image ReadImage ( const std::string &filename,
                    PixelIDValueEnum outputPixelType,
                    const std::string &imageIO )
    {
      ImageFileReader reader;
      reader.SetFileName(filename);
      reader.SetOutputPixelType(outputPixelType);
      reader.SetImageIO(imageIO);
      return reader.Execute();
    }


  ImageFileReader::~ImageFileReader()
  = default;

  ImageFileReader::ImageFileReader() :
    m_PixelType(sitkUnknown),
    m_Dimension(0),
    m_NumberOfComponents(0)
  {
    // list of pixel types supported
    using PixelIDTypeList = NonLabelPixelIDTypeList;

    this->m_MemberFactory.reset( new detail::MemberFunctionFactory<MemberFunctionType>( this ) );

    this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 2, SITK_MAX_DIMENSION > ();
  }

    std::string ImageFileReader::ToString() const {

      std::ostringstream out;
      out << "itk::simple::ImageFileReader";
      out << std::endl;
      out << "  FileName: \"";
      this->ToStringHelper(out, this->m_FileName) << "\"" << std::endl;
      out << "  ExtractSize: " << this->m_ExtractSize << std::endl;
      out << "  ExtractIndex: " << this->m_ExtractIndex << std::endl;

      out << "  Image Information:" << std::endl
          << "    PixelType: ";
      this->ToStringHelper(out, this->m_PixelType) << std::endl;
      out << "    Dimension: " << this->m_Dimension << std::endl;
      out << "    NumberOfComponents: " << this->m_NumberOfComponents << std::endl;
      out << "    Direction: " << this->m_Direction << std::endl;
      out << "    Origin: " << this->m_Origin << std::endl;
      out << "    Spacing: " << this->m_Spacing << std::endl;
      out << "    Size: " << this->m_Size << std::endl;

      out << ImageReaderBase::ToString();
      return out.str();
    }

    ImageFileReader& ImageFileReader::SetFileName ( const std::string &fn ) {
      this->m_FileName = fn;
      return *this;
    }

    std::string ImageFileReader::GetFileName() const {
      return this->m_FileName;
    }


    void
    ImageFileReader
    ::UpdateImageInformationFromImageIO(const itk::ImageIOBase* iobase)
    {
      PixelIDValueType pixelType;
      this->GetPixelIDFromImageIO(iobase, pixelType, m_Dimension);

      std::vector<double> direction(m_Dimension*m_Dimension);

      std::vector<double> origin(m_Dimension);
      std::vector<double> spacing(m_Dimension);
      std::vector<uint64_t> size(m_Dimension);
      for( unsigned int i = 0; i < m_Dimension; ++i)
        {
        origin[i] = iobase->GetOrigin(i);
        spacing[i] = iobase->GetSpacing(i);
        size[i] = iobase->GetDimensions(i);
        for( unsigned int col = 0; col < m_Dimension; ++col)
          {
          direction[i*m_Dimension+col] = iobase->GetDirection(col)[i];
          }
        }

      // release functions bound to old meta data dictionary
      if (m_MetaDataDictionary.get())
        {
        this->m_pfGetMetaDataKeys = nullptr;
        this->m_pfHasMetaDataKey = nullptr;
        this->m_pfGetMetaData =  nullptr;
        }

      this->m_MetaDataDictionary.reset(new MetaDataDictionary(iobase->GetMetaDataDictionary()));

      m_PixelType = static_cast<PixelIDValueEnum>(pixelType);

      // Use the number of components as reported by the itk::Image
      m_NumberOfComponents = iobase->GetNumberOfComponents();

      using std::swap;
      swap(direction, m_Direction);
      swap(origin, m_Origin);
      swap(spacing, m_Spacing);
      swap(size, m_Size);

      this->m_pfGetMetaDataKeys = std::bind(&MetaDataDictionary::GetKeys, this->m_MetaDataDictionary.get());
      this->m_pfHasMetaDataKey = std::bind(&MetaDataDictionary::HasKey, this->m_MetaDataDictionary.get(), std::placeholders::_1);
      this->m_pfGetMetaData = std::bind(&GetMetaDataDictionaryCustomCast::CustomCast, this->m_MetaDataDictionary.get(), std::placeholders::_1);
    }

    PixelIDValueEnum
    ImageFileReader
    ::GetPixelID( ) const
    {
      return this->m_PixelType;
    }

    PixelIDValueType
    ImageFileReader
    ::GetPixelIDValue( ) const
    {
      return this->m_PixelType;
    }

    unsigned int
    ImageFileReader
    ::GetDimension( ) const
    {
      return this->m_Dimension;
    }

    unsigned int
    ImageFileReader
    ::GetNumberOfComponents( ) const
    {
      return this->m_NumberOfComponents;
    }

    const std::vector<double> &
    ImageFileReader
    ::GetOrigin( ) const
    {
      return this->m_Origin;
    }

    const std::vector<double> &
    ImageFileReader
    ::GetSpacing( ) const
    {
      return this->m_Spacing;
    }

    const std::vector<double> &
    ImageFileReader
    ::GetDirection() const
    {
      return this->m_Direction;
    }

    const std::vector<uint64_t> &
    ImageFileReader
    ::GetSize( ) const
    {
      return this->m_Size;
    }

    void
    ImageFileReader
    ::ReadImageInformation( )
    {
      itk::ImageIOBase::Pointer imageio = this->GetImageIOBase( this->m_FileName );
      this->UpdateImageInformationFromImageIO(imageio);
      sitkDebugMacro("ImageIO: " << imageio);
    }


    std::vector<std::string>
    ImageFileReader
    ::GetMetaDataKeys( ) const
    {
      return this->m_pfGetMetaDataKeys();
    }

    bool
    ImageFileReader
    ::HasMetaDataKey( const std::string &key ) const
    {
      return this->m_pfHasMetaDataKey(key);
    }

    std::string
    ImageFileReader
    ::GetMetaData( const std::string &key ) const
    {
      return this->m_pfGetMetaData(key);
    }

  ImageFileReader &ImageFileReader::SetExtractSize( const std::vector<unsigned int> &size)
  {
    this->m_ExtractSize = size;
    return *this;
  }

  const std::vector<unsigned int> &ImageFileReader::GetExtractSize( ) const
  {
    return this->m_ExtractSize;
  }

  ImageFileReader &ImageFileReader::SetExtractIndex( const std::vector<int> &index )
  {
    this->m_ExtractIndex = index;
    return *this;
  }


  const std::vector<int> &ImageFileReader::GetExtractIndex( ) const
  {
    return this->m_ExtractIndex;
  }

    Image ImageFileReader::Execute ()
    {

      PixelIDValueType type = this->GetOutputPixelType();


      itk::ImageIOBase::Pointer imageio = this->GetImageIOBase( this->m_FileName );
      this->UpdateImageInformationFromImageIO(imageio);

      sitkDebugMacro( "ImageIO: " << imageio->GetNameOfClass() );


      unsigned int dimension = this->GetDimension();

      if ( dimension < 2 || dimension > SITK_IO_INPUT_MAX_DIMENSION )
        {
        sitkExceptionMacro( "The file has unsupported image dimension of " << dimension << ".\n"
                            << "The maximum supported IO dimension is " << SITK_IO_INPUT_MAX_DIMENSION << "." );
        }

      if (!m_ExtractSize.empty())
        {
        dimension = 0;
        for(unsigned int i = 0; i < m_ExtractSize.size(); ++i )
          {
          if (m_ExtractSize[i] != 0)
            {
            ++dimension;
            }
          }
        if ( dimension < 2 || dimension > SITK_MAX_DIMENSION )
          {
          sitkExceptionMacro( "The extraction region has unsupported output dimension of " << dimension << "."
                              << "The maximum supported output Image dimension is " << SITK_MAX_DIMENSION << "." );
          }
        }



      if (type == sitkUnknown)
        {
        type = this->GetPixelIDValue();
        }


      if ( !this->m_MemberFactory->HasMemberFunction( type, dimension ) )
        {
        sitkExceptionMacro( << "PixelType is not supported!" << std::endl
                            << "Pixel Type: "
                            << GetPixelIDValueAsString( type ) << std::endl
                            << "Refusing to load! " << std::endl );
        }

      return this->m_MemberFactory->GetMemberFunction( type, dimension )(imageio.GetPointer());
    }

  template <class TImageType>
  Image
  ImageFileReader::ExecuteInternal( itk::ImageIOBase *imageio )
  {

    using ImageType = TImageType;
    using Reader = itk::ImageFileReader<ImageType>;

    using InternalImageType = typename ImageType::template Rebind<typename ImageType::PixelType, SITK_IO_INPUT_MAX_DIMENSION>::Type;
    using InternalReader = itk::ImageFileReader<InternalImageType>;

    // if the InstantiatedToken is correctly implemented this should
    // not occur
    assert( ImageTypeToPixelIDValue<ImageType>::Result != (int)sitkUnknown );
    assert( imageio != nullptr );


    if ( m_ExtractSize.empty() || m_ExtractSize.size() == ImageType::ImageDimension)
      {

      typename Reader::Pointer reader = Reader::New();
      reader->SetImageIO( imageio );
      reader->SetFileName( this->m_FileName.c_str() );

      if ( m_ExtractSize.empty() )
        {

        this->PreUpdate( reader.GetPointer() );
        reader->Update();
        return Image( reader->GetOutput() );
        }


      return this->ExecuteExtract<ImageType>(reader->GetOutput());

      }
    else
      {
      // Perform Reading->Extractor pipeline to adjust dimensions and
      // do streamed ImageIO
      typename InternalReader::Pointer reader = InternalReader::New();
      reader->SetImageIO( imageio );
      reader->SetFileName( this->m_FileName.c_str() );

      return this->ExecuteExtract<ImageType>(reader->GetOutput());
      }
  }

  template <class TImageType, class TInternalImageType>
  Image
  ImageFileReader::ExecuteExtract( TInternalImageType * itkImage )
  {
    using InternalImageType = TInternalImageType;
    using ImageType = TImageType;

    using ExtractType = itk::ExtractImageFilter<InternalImageType, ImageType>;
    typename ExtractType::Pointer extractor = ExtractType::New();

    extractor->InPlaceOn();
    extractor->SetDirectionCollapseToSubmatrix();

    extractor->SetInput(itkImage);

    itkImage->UpdateOutputInformation();

    const typename InternalImageType::RegionType largestRegion = itkImage->GetLargestPossibleRegion();
    typename InternalImageType::RegionType region = largestRegion;

    for (unsigned int i = 0; i < TInternalImageType::ImageDimension; ++i)
      {
      if ( i < m_ExtractSize.size() )
        {
        region.SetSize(i, m_ExtractSize[i]);
        }
      else if ( i >= ImageType::ImageDimension )
        {
        region.SetSize(i, 0u);
        }
      if ( i < m_ExtractIndex.size() )
        {
        region.SetIndex(i,m_ExtractIndex[i]);
        }
      }

    extractor->SetExtractionRegion(region);

    typename TInternalImageType::IndexType upperIndex = region.GetUpperIndex();
    for (unsigned int i = 0; i < TInternalImageType::ImageDimension; ++i)
      {
      if (region.GetSize(i) == 0)
        {
        upperIndex[i] = region.GetIndex(i);
        }
      }

    // check region is in largest possible
    if ( !largestRegion.IsInside( region.GetIndex() ) ||
         !largestRegion.IsInside( upperIndex ) )
      {
      sitkExceptionMacro( "The requested extraction region: "
                          << region
                          << " is not contained with in file's region: "
                          << itkImage->GetLargestPossibleRegion() );
      }

    assert(itkImage->GetSource() != nullptr);
    this->PreUpdate( itkImage->GetSource().GetPointer() );

    extractor->Update();

    ImageType *itkOutImage = extractor->GetOutput();
    // copy meta-data dictionary
    itkOutImage->SetMetaDataDictionary( itkImage->GetMetaDataDictionary() );
    FixNonZeroIndex( itkOutImage );
    return Image( itkOutImage );
  }

  }
}
