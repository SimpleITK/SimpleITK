#ifndef __itkHashImageFilter_h
#define __itkHashImageFilter_h


#include "itkSimpleDataObjectDecorator.h"
#include "itkImageLinearConstIteratorWithIndex.h"
#include "itkCastImageFilter.h"
#include "itkByteSwapper.h"


#include "hl_md5.h"
#include "hl_sha1.h"

namespace itk {

/** \breif Generates a hash string from an image.
*
* \note This class utlizes low level buffer pointer access, to work
* with itk::Image and itk::VectorImage. It is modeled after the access
* an ImageFileWriter provides to an ImageIO.
*
* \todo complete documentation
* \todo Update in-place on to default after fixing bug in InPlaceImageFilter
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
  virtual DataObjectPointer MakeOutput(unsigned int idx);

protected:

  HashImageFilter();

  // virtual ~HashImageFilter(); // implementation not needed

  virtual void PrintSelf(std::ostream & os, Indent indent) const;

  // See superclass for doxygen documentation
  //
  // This method is to do work after the superclass potential threaded
  // copy.
  void AfterThreadedGenerateData();

  // See superclass for doxygen documentation
  //
  // Override since the filter produces all of its output
  void EnlargeOutputRequestedRegion(DataObject *data);

private:
  HashImageFilter(const Self &); //purposely not implemented
  void operator=(const Self &);  //purposely not implemented


  HashFunction m_HashFunction;
};


} // end namespace itk


#include "itkHashImageFilter.txx"

#endif // __itkHashImageFilter_h
