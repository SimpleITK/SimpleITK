
#include "sitkHashImageFilter.h"
#include "itkHashImageFilter.h"
#include "itkVectorImage.h"

#include <string>

namespace itk {
  namespace simple {
    HashImageFilter::HashImageFilter () {
      this->m_HashFunction = SHA1;

      this->m_MemberFactory.reset( new detail::MemberFunctionFactory<MemberFunctionType>( this ) );

      this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 3 > ();
      this->m_MemberFactory->RegisterMemberFunctions< PixelIDTypeList, 2 > ();
    }

    std::string HashImageFilter::ToString() const {
      std::ostringstream out;
      out << "itk::simple::HashImageFilter\n";
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

    HashImageFilter::HashFunction HashImageFilter::GetHashFunction()
    {
      return this->m_HashFunction;
    }

    HashImageFilter& HashImageFilter::SetHashFunction ( HashImageFilter::HashFunction hashFunction )
      {
      this->m_HashFunction = hashFunction;
      return *this;
      }

    std::string HashImageFilter::Execute ( Image* image ) {

      PixelIDValueType type = image->GetPixelIDValue();
      unsigned int dimension = image->GetDimension();

      return this->m_MemberFactory->GetMemberFunction( type, dimension )( image );
    }

    template <class TImageType>
    std::string HashImageFilter::ExecuteInternal ( Image* inImage )
    {
      typedef TImageType                                   InputImageType;

      typename InputImageType::ConstPointer image =
        dynamic_cast <InputImageType*> ( inImage->GetImageBase() );

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
    std::string Hash ( Image* image, HashImageFilter::HashFunction function ) {
      return HashImageFilter().SetHashFunction ( function ).Execute ( image );
    }
  }
}
