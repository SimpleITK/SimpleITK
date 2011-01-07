#ifndef __itkHashImageFilter_h
#define __itkHashImageFilter_h


#include "itkSimpleDataObjectDecorator.h"
#include "itkImageSliceConstIteratorWithIndex.h"
#include "itkImageToImageFilter.h"


#include "hl_md5.h"
#include "hl_sha1.h"

namespace itk {

template < class TInputImage >
class ITK_EXPORT HashImageFilter:
    public ImageToImageFilter< TInputImage, TInputImage >
{
public:
  /** Standard Self typedef */
  typedef HashImageFilter                                Self;
  typedef ImageToImageFilter< TInputImage, TInputImage > Superclass;
  typedef SmartPointer< Self >                           Pointer;
  typedef SmartPointer< const Self >                     ConstPointer;


  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Runtime information support. */
  itkTypeMacro(HashImageFilter, ImageToImageFilter);

  /** Smart Pointer type to a DataObject. */
  typedef typename DataObject::Pointer DataObjectPointer;

  /** Type of DataObjects used for scalar outputs */
  typedef SimpleDataObjectDecorator< uint32_t >  HashObjectType;

  /** Return the computed Hash. */
  uint32_t GetHash() const
  { return this->GetMinimumOutput()->Get(); }
  HashObjectType* GetHashOutput()
  { return static_cast< HashObjectType *>( this->ProcessObject::GetOutput(1) ); }

  /** Make a DataObject of the correct type to be used as the specified
   * output. */
  virtual DataObjectPointer MakeOutput(unsigned int idx);

protected:

  HashImageFilter()
    {
    this->ProcessObject::SetNthOutput( 1, this->MakeOutput(1).GetPointer() );
    this->GetHashOutput()->Set( 0 );
    }

  ~HashImageFilter(){}

  void PrintSelf(std::ostream & os, Indent indent) const
  {
    Superclass::PrintSelf(os, indent);
  }

  DataObjectPointer MakeOutput(unsigned int idx)
  {
    if ( idx == 1 )
      {
      return static_cast< DataObject * >( HashObjectType::New().GetPointer() );
      }
    return Superclass::MakeOutput(idx);
  }

  /** Pass the input through unmodified. Do this by Grafting in the
   *  AllocateOutputs method.
   */
  void AllocateOutputs()
  {
    // hack because output #1 needs to be an image but ours is an hash

    // Pass the input through as the output
    InputImagePointer image =
      const_cast< TInputImage * >( this->GetInput() );

    this->GraftOutput(image);

    // Nothing that needs to be allocated for the remaining outputs
  }

  enum HashFunction { SHA1, MD5 };
  HashFunction m_HashFunction;

  /** Do final mean and variance computation from data accumulated in threads.
   */
  void AfterThreadedGenerateData()
  {
    typedef TImageType                                   ImageType;
    typedef typename ImageType::PixelType                PixelType;
    typedef typename NumericTraits<PixelType>::ValueType ValueType;
    typedef itk::ByteSwapper<ValueType>                  Swapper;

    ::MD5 md5;
    ::HL_MD5_CTX md5Context;
    md5.MD5Init ( &md5Context );
    ::SHA1 sha1;
    ::HL_SHA1_CTX sha1Context;
    sha1.SHA1Reset ( &sha1Context );

    typename ImageType::ConstPointer input = this->GetInput();


    typedef itk::ImageSliceConstIteratorWithIndex<ImageType> IteratorType;
    IteratorType iterator = IteratorType ( input, input->GetLargestPossibleRegion() );
    iterator.SetFirstDirection(0);
    iterator.SetSecondDirection(1);
    iterator.GoToBegin();

    typename ImageType::RegionType largestRegion = input->GetLargestPossibleRegion();

    size_t VoxelsPerSlice = largestRegion.GetSize(0);
    if ( ImageType::ImageDimension > 1 )
      {
      VoxelsPerSlice *= largestRegion.GetSize(1);
      }

    PixelType* buffer = new PixelType[VoxelsPerSlice];

    // Compute the hash value one slice at a time
    size_t NumberOfSlices = 1;
    for ( unsigned int i = 2; i < TImageType::ImageDimension; ++i )
      {
      NumberOfSlices = largestRegion.GetSize(i);
      }


    while( !it.IsAtEnd() )
      {
      size_t i = 0;
      while( !it.IsAtEndOfSlice() )
        {
        while( !it.IsAtEndOfLine() )
          {
          buffer[i++] = it.Get();
          ++it;
          }
        it.NextLine();
        }
      it.NextSlice();

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
    int HashSize = SHA1HashSize;
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
    for(int i=0; i<HashSize; ++i)
      {
      // set the width to 2, fill with 0, and convert to hex
      os.width(2);
      os.fill('0');
      os << std::hex << static_cast<unsigned int>(Digest[i]);
      }
    return os.str();
  }

  /** Multi-thread version GenerateData. */
  void  ThreadedGenerateData(const RegionType &
                             outputRegionForThread,
                             int threadId) {}

  // Override since the filter produces all of its output
  void EnlargeOutputRequestedRegion(DataObject *data)
  {
  Superclass::EnlargeOutputRequestedRegion(data);
  data->SetRequestedRegionToLargestPossibleRegion();
  }

private:
  HashImageFilter(const Self &); //purposely not implemented
  void operator=(const Self &);        //purposely not implemented

  uint32_t m_Hash;
};


} // end namespace itk

#endif // __itkHashImageFilter_h
