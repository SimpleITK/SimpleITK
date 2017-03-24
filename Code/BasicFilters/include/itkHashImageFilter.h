/*=========================================================================
*
*  Copyright Insight Software Consortium
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
#ifndef itkHashImageFilter_h
#define itkHashImageFilter_h


#include "itkSimpleDataObjectDecorator.h"
#include "itkImageLinearConstIteratorWithIndex.h"
#include "itkCastImageFilter.h"
#include "itkByteSwapper.h"


#include "Ancillary/hl_md5.h"
#include "Ancillary/hl_sha1.h"

namespace itk {

/** \class HashImageFilter
 * \brief Generates a hash string from an image.
 *
 * \note This class utlizes low level buffer pointer access, to work
 * with itk::Image and itk::VectorImage. It is modeled after the access
 * an ImageFileWriter provides to an ImageIO.
 *
 * \todo Update in-place on to default after fixing bug in InPlaceImageFilter
 */
template < class TImageType >
class HashImageFilter:
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
  typedef ProcessObject::DataObjectPointerArraySizeType DataObjectPointerArraySizeType;
  using Superclass::MakeOutput;
  virtual DataObjectPointer MakeOutput(DataObjectPointerArraySizeType idx) ITK_OVERRIDE;

protected:

  HashImageFilter();

  // virtual ~HashImageFilter(); // implementation not needed

  virtual void PrintSelf(std::ostream & os, Indent indent) const ITK_OVERRIDE;

  // See superclass for doxygen documentation
  //
  // This method is to do work after the superclass potential threaded
  // copy.
  void AfterThreadedGenerateData() ITK_OVERRIDE;

  // See superclass for doxygen documentation
  //
  // Override since the filter produces all of its output
  void EnlargeOutputRequestedRegion(DataObject *data) ITK_OVERRIDE;

private:
  HashImageFilter(const Self &); //purposely not implemented
  void operator=(const Self &);  //purposely not implemented


  HashFunction m_HashFunction;
};


} // end namespace itk


#include "itkHashImageFilter.hxx"

#endif // itkHashImageFilter_h
