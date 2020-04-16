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
#ifndef itkHashImageFilter_hxx
#define itkHashImageFilter_hxx

#include "itkHashImageFilter.h"

#include "Ancillary/hl_sha1.h"
#include "itksys/MD5.h"

namespace itk {

//
// Constructor
//
template<class TImageType>
HashImageFilter<TImageType>::HashImageFilter()
{
  this->m_HashFunction = MD5;

  // create data object
  this->ProcessObject::SetNthOutput( 1, this->MakeOutput(1).GetPointer() );

  // NOTE: Turning this on causes a crash due to a bug is InPlaceImageFilter
  this->InPlaceOff();
}

//
// MakeOutput
//
template<class TImageType>
typename HashImageFilter<TImageType>::DataObjectPointer
HashImageFilter<TImageType>::MakeOutput(DataObjectPointerArraySizeType idx)
{
  if ( idx == 1 )
    {
    return static_cast< DataObject * >( HashObjectType::New().GetPointer() );
    }
  return Superclass::MakeOutput(idx);
}

//
// AfterThreadedGenerateData
//
template<class TImageType>
void
HashImageFilter<TImageType>::AfterThreadedGenerateData()
{
  // NOTE: We have choose our super class to be the
  // CastImageFilter. The filter is derived from the
  // InPlaceFilter. The CastImageFilter will copy its input, in the
  // best fashion based on the InPlace setting. We want the
  // behavior. This methods is called after the caster has done it's
  // work.

  Superclass::AfterThreadedGenerateData();

  using ImageType = TImageType;
  using PixelType = typename ImageType::PixelType;
  using ValueType = typename NumericTraits<PixelType>::ValueType;
  using Swapper = itk::ByteSwapper<ValueType>;

  struct MD5Holder
  {
    MD5Holder() : md5(itksysMD5_New()) {}
    ~MD5Holder() {itksysMD5_Delete(md5);}
    itksysMD5 *md5;
  };
  MD5Holder holder;

  itksysMD5 *md5 = holder.md5;
  itksysMD5_Initialize( md5 );

  ::SHA1 sha1;
  ::HL_SHA1_CTX sha1Context;
  sha1.SHA1Reset ( &sha1Context );

  typename ImageType::ConstPointer input = this->GetInput();


  // make a good guess about the number of components in each pixel
  size_t numberOfComponent =   sizeof(PixelType) / sizeof(ValueType );

  if ( strcmp(input->GetNameOfClass(), "VectorImage") == 0 )
    {
    // spacial case for VectorImages
    numberOfComponent = ImageType::AccessorFunctorType::GetVectorLength(input);
    }
  else if ( sizeof(PixelType) % sizeof(ValueType) != 0 )
    {
    itkExceptionMacro("Unsupported data type for hashing!");
    }

  // we feel bad about accessing the data this way
  ValueType *buffer = static_cast<ValueType*>( (void *)input->GetBufferPointer() );

  typename ImageType::RegionType largestRegion = input->GetBufferedRegion();
  const size_t numberOfValues = largestRegion.GetNumberOfPixels()*numberOfComponent;

  // Possibly byte swap so we always calculate on little endian data
  Swapper::SwapRangeFromSystemToLittleEndian ( buffer, numberOfValues );

  // Update the hash
  switch ( this->m_HashFunction )
    {
    case SHA1:
      sha1.SHA1Input ( &sha1Context, (unsigned char*)buffer, numberOfValues*sizeof(ValueType) );
      break;
    case MD5:
      itksysMD5_Append( md5, (unsigned char*)buffer, static_cast<int>( numberOfValues*sizeof(ValueType) ) );
      break;
    }

  // Calculate and return the hash value
  switch ( this->m_HashFunction )
    {
    case SHA1:
    {
    const int HashSize = SHA1HashSize;
     hl_uint8 Digest[1024];
    sha1.SHA1Result ( &sha1Context, Digest );

    // Convert binary to hex string representation

    std::ostringstream os;
    for(int i=0; i<HashSize; ++i)
      {
      // set the width to 2, fill with 0, and convert to hex
      os.width(2);
      os.fill('0');
      os << std::hex << static_cast<unsigned int>(Digest[i]);
      }

    this->GetHashOutput()->Set( os.str() );

    break;
    }
    case MD5:
    {
    const size_t DigestSize = 32u;
    char Digest[DigestSize];

    // directly to HEX
    itksysMD5_FinalizeHex( md5, Digest );

    this->GetHashOutput()->Set( std::string(Digest, DigestSize) );
    break;
    }
    }

}


//
// EnlargeOutputRequestedRegion
//
template<class TImageType>
void
HashImageFilter<TImageType>::EnlargeOutputRequestedRegion(DataObject *data)
{
  Superclass::EnlargeOutputRequestedRegion(data);

  // set the output region to the largest and let the pipeline
  // propagate the requested region to the input
  data->SetRequestedRegionToLargestPossibleRegion();
}


//
// PrintSelf
//
template<class TImageType>
void
HashImageFilter<TImageType>::PrintSelf(std::ostream & os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);

  os << indent << "HashFunction: " << m_HashFunction << std::endl;
}


} // end namespace itk

#endif // itkHashImageFilter_hxx
