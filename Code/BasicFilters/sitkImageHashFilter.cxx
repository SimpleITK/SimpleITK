#include "hl_md5.h"
#include "hl_sha1.h"
#include "sitkImageHashFilter.h"

#include <itkByteSwapper.h>
#include <itkImageRegionConstIterator.h>

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

    ImageHashFilter::HashFunction ImageHashFilter::GetHashFunction() { return this->m_HashFunction; }
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
    std::string ImageHashFilter::ExecuteInternal ( Image::Pointer inImage ) {
      typedef TImageType InputImageType;
      typedef typename InputImageType::PixelType PixelType;
      typedef typename NumericTraits<PixelType>::ValueType ValueType;
      typedef itk::ByteSwapper<ValueType> Swapper;
      typename InputImageType::Pointer image =
        dynamic_cast <InputImageType*> ( inImage->GetImageBase().GetPointer() );

      if ( image.IsNull() ) {
        // Take some action
        return "ImageIsNull";
      }

      ::MD5 md5;
      ::HL_MD5_CTX md5Context;
      md5.MD5Init ( &md5Context );
      ::SHA1 sha1;
      ::HL_SHA1_CTX sha1Context;
      sha1.SHA1Reset ( &sha1Context );

      typedef itk::ImageRegionConstIterator<InputImageType> IteratorType;
      IteratorType iterator = IteratorType ( image, image->GetLargestPossibleRegion() );
      iterator.GoToBegin();

      size_t VoxelsPerSlice = inImage->GetWidth() * inImage->GetHeight();
      PixelType* buffer = new PixelType[VoxelsPerSlice];
      // Compute the hash value one slice at a time
      size_t NumberOfSlices;
      if ( TImageType::ImageDimension == 2 ) {
        NumberOfSlices = 1;
      } else {
        NumberOfSlices = inImage->GetDepth();
      }
      for ( size_t depth = 0; depth < NumberOfSlices; depth++ ) {
        for ( size_t i = 0; i < VoxelsPerSlice; i++ ) {
          buffer[i] = iterator.Value();
          ++iterator;
        }
        // Possibly byte swap so we always calculate on little endian data
        Swapper::SwapRangeFromSystemToLittleEndian ( buffer, VoxelsPerSlice );

        // Update the hash
        switch ( this->m_HashFunction )
          {
          case SHA1:
            sha1.SHA1Input ( &sha1Context, (unsigned char*)buffer, VoxelsPerSlice*sizeof(PixelType) );
            break;
          case MD5:
            md5.MD5Update ( &md5Context, (unsigned char*)buffer, VoxelsPerSlice*sizeof(PixelType) );
            break;
          }
      }

      delete[] buffer;
      // Calculate and return the hash value
      std::string hash;
      int HashSize;
      unsigned char Digest[1024];
      switch ( this->m_HashFunction )
        {
        case SHA1:
          {
            HashSize = SHA1HashSize;
            sha1.SHA1Result ( &sha1Context, Digest );
            break;
          }
        case MD5:
          {
            HashSize = 16;
            md5.MD5Final ( Digest, &md5Context );
            break;
          }
        }
      // Print to a string
      std::ostringstream os;
      for(int i=0; i<HashSize; ++i) {
        // set the width to 2, fill with 0, and convert to hex
        os.width(2);
        os.fill('0');
        os << std::hex << static_cast<unsigned int>(Digest[i]);
      }
      return os.str();
    }
  }
}
