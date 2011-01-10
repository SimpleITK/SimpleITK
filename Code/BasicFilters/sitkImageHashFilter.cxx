
#include "sitkImageHashFilter.h"
#include "itkHashImageFilter.h"

#include <string>

namespace itk {
  namespace simple {
    ImageHashFilter::ImageHashFilter () {
      this->m_HashFunction = SHA1;

      this->m_MemberFactory.reset( new detail::MemberFunctionFactory<MemberFunctionType>( this ) );

      this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 3 > ();
      this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 2 > ();
    }

    std::string ImageHashFilter::ToString() const {
      std::ostringstream out;
      out << "itk::simple::ImageHashFilter\n";
      out << "HashFunction: ";
      switch ( this->m_HashFunction )
        {
        case SHA1:
          out << "SHA1";
          break;
        case MD5:
          out << "MD5";
          break;
        }
      out << "\n";
      return out.str();
    }

    ImageHashFilter::HashFunction ImageHashFilter::GetHashFunction()
    {
      return this->m_HashFunction;
    }

    ImageHashFilter& ImageHashFilter::SetHashFunction ( ImageHashFilter::HashFunction hashFunction )
      {
      this->m_HashFunction = hashFunction;
      return *this;
      }

    std::string ImageHashFilter::Execute ( Image::Pointer image ) {

      PixelIDValueType type = image->GetPixelIDValue();
      unsigned int dimension = image->GetDimension();

      return this->m_MemberFactory->GetMemberFunction( type, dimension )( image );
    }

    template <class TImageType>
    std::string ImageHashFilter::ExecuteInternal ( Image::Pointer inImage )
    {
      typedef TImageType                                   InputImageType;

      typename InputImageType::ConstPointer image =
        dynamic_cast <InputImageType*> ( inImage->GetImageBase().GetPointer() );

      typedef itk::HashImageFilter<InputImageType> HashFilterType;
      typename HashFilterType::Pointer hasher = HashFilterType::New();
      hasher->SetInput( image );
      hasher->InPlaceOff(); // pointless copy of data needed

      switch ( this->GetHashFunction() )
        {
        case SHA1:
          hasher->SetHashFunction( HashFilterType::SHA1 );
          break;
        case MD5:
          hasher->SetHashFunction( HashFilterType::MD5 );
          break;
        }

      hasher->Update();

      std::string output = hasher->GetHash();

      return output;
    }
  }
}
