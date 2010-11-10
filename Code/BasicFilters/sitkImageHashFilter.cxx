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
    }

    std::string ImageHashFilter::ToString() {
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

      int fnIndex = image->GetImageDataType();

      // todo fix this ugly syntax
      return ((*this).*(m_MemberFactory.GetMemberFunction( fnIndex )))(image);
    }

    template <class T>
    std::string ImageHashFilter::ExecuteInternal ( Image::Pointer inImage ) {
      typedef itk::ByteSwapper<T> Swapper;
      typedef itk::Image<T,3> InputImageType;
      typename InputImageType::Pointer image =
        dynamic_cast <InputImageType*> ( inImage->GetITKImage().GetPointer() );

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

      unsigned long VoxelsPerSlice = inImage->GetWidth() * inImage->GetHeight();
      T* buffer = new T[VoxelsPerSlice];
      // Compute the hash value one slice at a time
      for ( unsigned long depth = 0; depth < inImage->GetDepth(); depth++ ) {
        for ( unsigned long i = 0; i < VoxelsPerSlice; i++ ) {
          buffer[i] = iterator.Value();
          ++iterator;
        }
        // Possibly byte swap
        Swapper::SwapRangeFromSystemToLittleEndian ( buffer, VoxelsPerSlice );

        // Update the hash
        switch ( this->m_HashFunction )
          {
          case SHA1:
            sha1.SHA1Input ( &sha1Context, (unsigned char*)buffer, VoxelsPerSlice );
            break;
          case MD5:
            md5.MD5Update ( &md5Context, (unsigned char*)buffer, VoxelsPerSlice );
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
