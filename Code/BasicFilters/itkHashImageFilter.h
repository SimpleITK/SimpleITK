#ifndef __itkHashImageFilter_h
#define __itkHashImageFilter_h


#include "itkSimpleDataObjectDecorator.h"
#include "itkImageLinearConstIteratorWithIndex.h"
#include "itkCastImageFilter.h"
#include "itkByteSwapper.h"


#include "hl_md5.h"
#include "hl_sha1.h"

namespace itk {

/** \class Generates a hash string from an image.
*
* \note This class utlizes low level buffer pointer access, to work
* with itk::Image and itk::VectorImage. It is modeled after the access
* an ImageFileWriter provides to an ImageIO.
*
* \todo complete documentation
* \todo move implementation to txx file
*/
template < class TImageType >
class ITK_EXPORT HashImageFilter:
    public CastImageFilter< TImageType, TImageType >
{
public:
  /** Standard Self typedef */
  typedef HashImageFilter                           Self;
  typedef CastImageFilter< TImageType, TImageType > Superclass;
  typedef SmartPointer< Self >                      Pointer;
  typedef SmartPointer< const Self >                ConstPointer;

  typedef typename TImageType::RegionType RegionType;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Runtime information support. */
  itkTypeMacro(HashImageFilter, CastImageFilter);

  /** Smart Pointer type to a DataObject. */
  typedef typename DataObject::Pointer DataObjectPointer;

  /** Type of DataObjects used for scalar outputs */
  typedef SimpleDataObjectDecorator< std::string >  HashObjectType;

  /** Get the computed Hash values */
  std::string GetHash() const
  { return this->GetHashOutput()->Get(); }
  HashObjectType* GetHashOutput()
  { return static_cast< HashObjectType *>( this->ProcessObject::GetOutput(1) ); }
  const HashObjectType* GetHashOutput() const
  { return static_cast<const HashObjectType *>( this->ProcessObject::GetOutput(1) ); }

  enum  HashFunction { SHA1, MD5 };

  /** Set/Get hashing function as enumerated type */
  itkSetMacro( HashFunction, HashFunction );
  itkGetMacro( HashFunction, HashFunction );


  /** Make a DataObject of the correct type to be used as the specified
   * output. */
  virtual DataObjectPointer MakeOutput(unsigned int idx)
  {
    if ( idx == 1 )
      {
      return static_cast< DataObject * >( HashObjectType::New().GetPointer() );
      }
    return Superclass::MakeOutput(idx);
  }

protected:

  HashImageFilter()
    {
    this->m_HashFunction = MD5;

    // create data object
    this->ProcessObject::SetNthOutput( 1, this->MakeOutput(1).GetPointer() );
    }

  ~HashImageFilter(){}

  virtual void PrintSelf(std::ostream & os, Indent indent) const
  {
    Superclass::PrintSelf(os, indent);

    os << indent << "HashFunction: " << m_HashFunction << std::endl;
  }

  /** Do final mean and variance computation from data accumulated in threads.
   */
  void AfterThreadedGenerateData()
  {
    Superclass::AfterThreadedGenerateData();

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


    // estimate 
    size_t numberOfComponent =   sizeof(PixelType) / sizeof(ValueType );

    if ( strcmp(input->GetNameOfClass(), "VectorImage") == 0 )
      {
      numberOfComponent = ImageType::AccessorFunctorType::GetVectorLength(input);
      }
    else if ( sizeof(PixelType) % sizeof(ValueType) != 0 )
      {
      itkExceptionMacro("Unsupported data type for hashing!");
      }

    ValueType *buffer = static_cast<ValueType*>( (void *)input->GetBufferPointer() );

    typename ImageType::RegionType largestRegion = input->GetBufferedRegion();
    const size_t numberOfValues = largestRegion.GetNumberOfPixels()*numberOfComponent;


    // Possibly byte swap so we always calculate on little endian data
    Swapper::SwapRangeFromSystemToLittleEndian ( buffer, numberOfValues);

    // Update the hash
    switch ( this->m_HashFunction )
      {
      case SHA1:
        sha1.SHA1Input ( &sha1Context, (unsigned char*)buffer, numberOfValues*sizeof(ValueType) );
        break;
      case MD5:
        md5.MD5Update ( &md5Context, (unsigned char*)buffer, numberOfValues*sizeof(ValueType) );
        break;
      }

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

    this->GetHashOutput()->Set( os.str() );
  }


  // Override since the filter produces all of its output
  void EnlargeOutputRequestedRegion(DataObject *data)
  {
  Superclass::EnlargeOutputRequestedRegion(data);
  data->SetRequestedRegionToLargestPossibleRegion();
  }

private:
  HashImageFilter(const Self &); //purposely not implemented
  void operator=(const Self &);        //purposely not implemented


  HashFunction m_HashFunction;

};


} // end namespace itk

#endif // __itkHashImageFilter_h
