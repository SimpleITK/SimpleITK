#include "hl_md5.h"
#include "hl_sha1.h"
#include "simpleImageHash.h"
#include "itkByteSwapper.h"
#include "itkImageRegionConstIterator.h"

namespace itk {
  namespace simple {
    ImageHash::ImageHash () {
      // initialize array to all zeros
      std::fill_n( m_PFunction, size_t(typelist::Length< InstantiatedPixelTypeList >::Result), MemberFunctionType(0) );

      // initialize function array with pointer
      typelist::ForEach<PixelTypeList> arrayInitializer;
      arrayInitializer( PFuncArrayInitializer<Self>( this->m_PFunction ) );

      this->mHashFunction = SHA1;
    }

    std::string ImageHash::toString() {
      std::ostringstream out;
      out << "itk::simple::ImageHash\n";
      out << "HashFunction: ";
      switch ( this->mHashFunction )
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

    ImageHash::HashFunction ImageHash::getHashFunction() { return this->mHashFunction; }
    ImageHash& ImageHash::setHashFunction ( ImageHash::HashFunction hashFunction ) { this->mHashFunction = hashFunction; return *this; }

    std::string ImageHash::execute ( Image::Pointer image ) {

      int fnIndex = image->getImageDataType();
      assert( fnIndex > 0 && fnIndex < typelist::Length< InstantiatedPixelTypeList >::Result );
      if ( m_PFunction[ fnIndex ] )
        {
        return ((*this).*(m_PFunction[ fnIndex ]))(image);
        }
      else
        {
        // error
        std::cerr << "pixel type is not supported!" << std::endl;
        exit(1);
        }
      return std::string();
    }

    template <class T>
    std::string ImageHash::executeInternal ( Image::Pointer inImage ) {
      typedef itk::ByteSwapper<T> Swapper;
      typedef itk::Image<T,3> InputImageType;
      typename InputImageType::Pointer image = dynamic_cast <InputImageType*> ( inImage->getITKImage().GetPointer() );

      if ( image.IsNull() ) {
        // Take some action
        return NULL;
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

      unsigned long VoxelsPerSlice = inImage->getWidth() * inImage->getHeight();
      T* buffer = new T[VoxelsPerSlice];
      // Compute the hash value one slice at a time
      for ( unsigned long depth = 0; depth < inImage->getDepth(); depth++ ) {
        for ( unsigned long i = 0; i < VoxelsPerSlice; i++ ) {
          buffer[i] = iterator.Value();
          ++iterator;
        }
        // Possibly byte swap
        Swapper::SwapRangeFromSystemToLittleEndian ( buffer, VoxelsPerSlice );

        // Update the hash
        switch ( this->mHashFunction )
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
      switch ( this->mHashFunction )
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
