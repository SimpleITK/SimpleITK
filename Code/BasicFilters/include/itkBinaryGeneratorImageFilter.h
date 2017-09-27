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
#ifndef itkBinaryGeneratorImageFilter_h
#define itkBinaryGeneratorImageFilter_h

#include "itkInPlaceImageFilter.h"
#include "itkSimpleDataObjectDecorator.h"

namespace itk
{
/** \class BinaryGeneratorImageFilter
 * \brief Implements pixel-wise generic operation of two images,
 * or of an image and a constant.
 *
 * This class is parameterized over the types of the two input images
 * and the type of the output image.  The functor is not a template
 * parameter, but can be set with a function that instantiates and
 * "generates" a ThreadedGenerateData method to be call during
 * execution.
 *
 * The constant must be of the same type than the pixel type of the corresponding
 * image. It is wrapped in a SimpleDataObjectDecorator so it can be updated through
 * the pipeline. The SetConstant() and GetConstant() methods are provided as shortcuts
 * to set or get the constant value without manipulating the decorator.
 *
 * \sa BinaryFunctorImageFilter
 * \sa UnaryFunctorImageFilter TernaryFunctorImageFilter
 *
 * \ingroup IntensityImageFilters   MultiThreaded
 * \ingroup ITKImageFilterBase
 *
 * \wiki
 * \wikiexample{ImageProcessing/BinaryGeneratorImageFilter,Apply a predefined operation to corresponding pixels in two images}
 * \wikiexample{ImageProcessing/BinaryGeneratorImageFilterCustom,Apply a custom operation to corresponding pixels in two images}
 * \endwiki
 */
template< typename TInputImage1, typename TInputImage2,
          typename TOutputImage  >
class ITK_TEMPLATE_EXPORT BinaryGeneratorImageFilter:
  public InPlaceImageFilter< TInputImage1, TOutputImage >
{
public:
  /** Standard class typedefs. */
  typedef BinaryGeneratorImageFilter                         Self;
  typedef InPlaceImageFilter< TInputImage1, TOutputImage > Superclass;
  typedef SmartPointer< Self >                             Pointer;
  typedef SmartPointer< const Self >                       ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(BinaryGeneratorImageFilter, InPlaceImageFilter);

  /** Some convenient typedefs. */
  typedef TInputImage1                           Input1ImageType;
  typedef typename Input1ImageType::ConstPointer Input1ImagePointer;
  typedef typename Input1ImageType::RegionType   Input1ImageRegionType;
  typedef typename Input1ImageType::PixelType    Input1ImagePixelType;
  typedef SimpleDataObjectDecorator<Input1ImagePixelType>
                                                 DecoratedInput1ImagePixelType;

  typedef TInputImage2                           Input2ImageType;
  typedef typename Input2ImageType::ConstPointer Input2ImagePointer;
  typedef typename Input2ImageType::RegionType   Input2ImageRegionType;
  typedef typename Input2ImageType::PixelType    Input2ImagePixelType;
  typedef SimpleDataObjectDecorator<Input2ImagePixelType>
                                                 DecoratedInput2ImagePixelType;

  typedef TOutputImage                         OutputImageType;
  typedef typename OutputImageType::Pointer    OutputImagePointer;
  typedef typename OutputImageType::RegionType OutputImageRegionType;
  typedef typename OutputImageType::PixelType  OutputImagePixelType;

  /** Connect the first operand for pixel-wise operation. */
  virtual void SetInput1(const TInputImage1 *image1);
  virtual void SetInput1(const DecoratedInput1ImagePixelType *input1);
  virtual void SetInput1(const Input1ImagePixelType &input1);

  /** Set the first operand as a constant. */
  virtual void SetConstant1(const Input1ImagePixelType &input1);

  /** Get the constant value of the first operand. An exception is sent if
   * the first operand is not a constant. */
  virtual const Input1ImagePixelType & GetConstant1() const;

  /** Connect the second operand for pixel-wise operation. */
  virtual void SetInput2(const TInputImage2 *image2);
  virtual void SetInput2(const DecoratedInput2ImagePixelType *input2);
  virtual void SetInput2(const Input2ImagePixelType &input2);

  /** Set the second operand as a constant. */
  virtual void SetConstant2(const Input2ImagePixelType &input2);
  void SetConstant(Input2ImagePixelType ct)
  {
    this->SetConstant2(ct);
  }
  const Input2ImagePixelType & GetConstant() const
  {
    return this->GetConstant2();
  }

  /** Get the constant value of the second operand. An exception is sent if
   * the second operand is not a constant. */
  virtual const Input2ImagePixelType & GetConstant2() const;


  template <typename TFunctor>
  void SetFunctor( const TFunctor &functor)
  {
    m_functor = simple::nsstd::bind( &Self::ThreadedGenerateData<TFunctor>,
                                     this,
                                     functor,
                                     simple::nsstd::placeholders::_1,
                                     simple::nsstd::placeholders::_2);
    this->Modified();
  }


  /** ImageDimension constants */
  itkStaticConstMacro(
    InputImage1Dimension, unsigned int, TInputImage1::ImageDimension);
  itkStaticConstMacro(
    InputImage2Dimension, unsigned int, TInputImage2::ImageDimension);
  itkStaticConstMacro(
    OutputImageDimension, unsigned int, TOutputImage::ImageDimension);

#ifdef ITK_USE_CONCEPT_CHECKING
  // Begin concept checking
  itkConceptMacro( SameDimensionCheck1,
                   ( Concept::SameDimension< itkGetStaticConstMacro(InputImage1Dimension),
                                             itkGetStaticConstMacro(InputImage2Dimension) > ) );
  itkConceptMacro( SameDimensionCheck2,
                   ( Concept::SameDimension< itkGetStaticConstMacro(InputImage1Dimension),
                                             itkGetStaticConstMacro(OutputImageDimension) > ) );
  // End concept checking
#endif

protected:
  BinaryGeneratorImageFilter();
  virtual ~BinaryGeneratorImageFilter() {}

  /** BinaryGeneratorImageFilter can be implemented as a multithreaded filter.
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

  // Needed to take the image information from the 2nd input, if the first one is
  // a simple decorated object.
  virtual void GenerateOutputInformation() ITK_OVERRIDE;

private:
  ITK_DISALLOW_COPY_AND_ASSIGN(BinaryGeneratorImageFilter);

  simple::nsstd::function<void(const OutputImageRegionType &, ThreadIdType)> m_functor;
};
} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkBinaryGeneratorImageFilter.hxx"
#endif

#endif
