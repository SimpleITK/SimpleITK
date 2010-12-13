#include "sitkImage.h"

namespace itk
{
  namespace simple
  {

    template<class TImageType> void Image::AllocateInternal ( uint64_t Width, uint64_t Height, uint64_t Depth ) {
      typename TImageType::IndexType  index;
      typename TImageType::SizeType   size;
      typename TImageType::RegionType region;
      index.Fill ( 0 );
      size.Fill(1);
      size[0] = Width;
      size[1] = Height;
      if ( Depth != 0 ) {
        size[2] = Depth;
      }
      region.SetSize ( size );
      region.SetIndex ( index );
      typename TImageType::Pointer image = TImageType::New();
      image->SetRegions ( region );
      image->Allocate();
      image->FillBuffer ( 0.0 );
      m_PimpleImage.reset( new PimpleImage<TImageType>( image ) );
    }

    void Image::Allocate ( uint64_t Width, uint64_t Height, uint64_t Depth, PixelIDValueEnum ValueEnum ) {
      // Allocate an image
      this->m_AllocateMemberFactory.reset( new detail::MemberFunctionFactory<MemberFunctionType, detail::AllocateMemberFunctionAddressor<MemberFunctionType> > ( this ) );

      this->m_AllocateMemberFactory->RegisterMemberFunctions< PixelIDTypeList, 3 > ();
      this->m_AllocateMemberFactory->RegisterMemberFunctions< PixelIDTypeList, 2 > ();
      PixelIDValueType type = ValueEnum;
      if ( Depth == 0 ) {
        this->m_AllocateMemberFactory->GetMemberFunction( type, 2 )( Width, Height, Depth );
      } else {
        this->m_AllocateMemberFactory->GetMemberFunction( type, 3 )( Width, Height, Depth );
      }
    }

    Image::Image( uint64_t Width, uint64_t Height, PixelIDValueType ValueType ) {
      Allocate ( Width, Height, 0, (PixelIDValueEnum) ValueType );
    }
    Image::Image( uint64_t Width, uint64_t Height, uint64_t Depth, PixelIDValueEnum ValueEnum ) {
      Allocate ( Width, Height, Depth, ValueEnum );
    }

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

    PixelIDValueType Image::GetPixelIDValue( void ) const
    {
      return this->m_PimpleImage->GetPixelIDValue();
    }

    unsigned int Image::GetDimension( void ) const
    {
      return this->m_PimpleImage->GetDimension();
    }

    std::string Image::GetPixelIDTypeAsString( void ) const
    {
      return std::string( GetPixelIDValueAsString( this->GetPixelIDValue() ) );
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

    /*
    void Image::Show(const std::string name) const
    {
      // Try to find ImageJ, write out a file and open
#if defined(__WIN32__)
      // Windows
#elseif defined(__APPLE__)
      // Mac
      char *filename = malloc ( sizeof(char) * (100 + name.size()) );
      sprintf ( filename, "/tmp/%s-XXXXX.nrrd", name.c_str() );
      mktemp ( filename );
      ImageFileWriter().SetFilename ( filename ).Execute ( this );
      std::cout << "Show Filename: " << filename << std::endl;
#else
      // Linux
#endif
    }
    */

  }
}
