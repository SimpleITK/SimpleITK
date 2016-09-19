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
#ifndef itkUnaryGeneratorImageFilter_h
#define itkUnaryGeneratorImageFilter_h

#include "itkMath.h"
#include "itkInPlaceImageFilter.h"
#include "itkImageRegionIteratorWithIndex.h"
#include "nsstd/functional.h"

namespace itk
{
/** \class UnaryGeneratorImageFilter
 * \brief Implements pixel-wise generic operation on one image.
 *
 * This class is parameterized over the type of the input image and
 * the type of the output image. The functor is not a template
 * parameter, but can be set with a function that instantiates and
 * "generates" a ThreadedGenerateData method to be call during
 * execution.
 *
 * UnaryGeneratorImageFilter allows the output dimension of the filter
 * to be larger than the input dimension. Thus subclasses of the
 * UnaryGeneratorImageFilter can be used to promote a 2D image to a 3D
 * image, etc.
 *
 * \sa UnaryFunctorImageFilter
 * \sa BinaryFunctorImageFilter TernaryFunctorImageFilter
 *
 * \ingroup IntensityImageFilters MultiThreaded
 *
 * \wiki
 * \endwiki
 */
template< typename TInputImage, typename TOutputImage >
class UnaryGeneratorImageFilter:public InPlaceImageFilter< TInputImage, TOutputImage >
{
public:
  /** Standard class typedefs. */
  typedef UnaryGeneratorImageFilter                         Self;
  typedef InPlaceImageFilter< TInputImage, TOutputImage > Superclass;
  typedef SmartPointer< Self >                            Pointer;
  typedef SmartPointer< const Self >                      ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(UnaryGeneratorImageFilter, InPlaceImageFilter);

  typedef TInputImage                              InputImageType;
  typedef typename    InputImageType::ConstPointer InputImagePointer;
  typedef typename    InputImageType::RegionType   InputImageRegionType;
  typedef typename    InputImageType::PixelType    InputImagePixelType;

  typedef TOutputImage                             OutputImageType;
  typedef typename     OutputImageType::Pointer    OutputImagePointer;
  typedef typename     OutputImageType::RegionType OutputImageRegionType;
  typedef typename     OutputImageType::PixelType  OutputImagePixelType;

  template <typename TFunctor>
  void SetFunctor( const TFunctor & functor)
  {
    m_functor = simple::nsstd::bind( &Self::ThreadedGenerateData<TFunctor>,
                                     this,
                                     functor,
                                     simple::nsstd::placeholders::_1,
                                     simple::nsstd::placeholders::_2);
    this->Modified();
  }


protected:
  UnaryGeneratorImageFilter();
  virtual ~UnaryGeneratorImageFilter() {}

  /** UnaryGeneratorImageFilter can produce an image which is a different
   * resolution than its input image.  As such, UnaryGeneratorImageFilter
   * needs to provide an implementation for
   * GenerateOutputInformation() in order to inform the pipeline
   * execution model.  The original documentation of this method is
   * below.
   *
   * \sa ProcessObject::GenerateOutputInformaton()  */
  virtual void GenerateOutputInformation() ITK_OVERRIDE;



  /** UnaryGeneratorImageFilter is implemented as a multithreaded filter.
   * Therefore, this implementation provides a ThreadedGenerateData() routine
   * which is called for each processing thread.
   *
   * The template method is instantiated by the SetFunctor method, and
   * the generated code is run during the update.
   *
   * \sa ImageToImageFilter::ThreadedGenerateData(),
   *     ImageToImageFilter::GenerateData()  */
  template <typename TFunctor>
  void ThreadedGenerateData(const TFunctor &, const OutputImageRegionType & outputRegionForThread,
                            ThreadIdType threadId);
  void ThreadedGenerateData(const OutputImageRegionType & outputRegionForThread,
                            ThreadIdType threadId) ITK_OVERRIDE;

private:
  ITK_DISALLOW_COPY_AND_ASSIGN(UnaryGeneratorImageFilter);

  simple::nsstd::function<void(const OutputImageRegionType &, ThreadIdType)> m_functor;


};
} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkUnaryGeneratorImageFilter.hxx"
#endif

#endif
