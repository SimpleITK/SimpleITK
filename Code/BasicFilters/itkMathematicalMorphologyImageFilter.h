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
#ifndef __itkMathematicalMorphologyImageFilter_h
#define __itkMathematicalMorphologyImageFilter_h

#include "itkFlatStructuringElement.h"
#include "itkBinaryErodeImageFilter.h"
#include "itkBinaryDilateImageFilter.h"
#include "itkGrayscaleErodeImageFilter.h"
#include "itkGrayscaleDilateImageFilter.h"

namespace itk
{
/**
 * \class MathematicalMorphologyImageFilter
 * \brief Specialization of the ITK mathematical morphology filters.
 *
 * This filter simplifies the API of the ITK mathematical morphology
 * filters to make easier to expose them at the Simple ITK layer.
 *
 */
template< class TInputImage, class TOutputImage >
class MathematicalMorphologyImageFilter:
  public ImageToImageFilter< TInputImage, TOutputImage >
{
public:
  /** Standard class typedefs. */
  typedef MathematicalMorphologyImageFilter Self;
  typedef ImageToImageFilter< TInputImage, TOutputImage > Superclass;
  typedef SmartPointer< Self >       Pointer;
  typedef SmartPointer< const Self > ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(MathematicalMorphologyImageFilter, ImageToImageFilter);

  /** Enum defining the operation to be applied to the input image. */
  typedef enum {
   BinaryErode, BinaryDilate, GrayscaleErode, GrayscaleDilate } OperationType;

  /** Define the type of mathematical morphology operation to be applied to the
   * input image. See the type OperationType enum for a list of valid options. */
  itkSetMacro( Operation, OperationType );
  itkGetMacro( Operation, OperationType );


protected:

  MathematicalMorphologyImageFilter();
  virtual ~MathematicalMorphologyImageFilter(){}
  void PrintSelf(std::ostream & os, Indent indent) const;

  void GenerateData();

private:
  MathematicalMorphologyImageFilter(const Self &); //purposely not implemented
  void operator=(const Self &);         //purposely not implemented

  typedef FlatStructuringElement< TOutputImage::ImageDimension > KernelType;

  typedef BinaryErodeImageFilter< TInputImage, TOutputImage, KernelType >       BinaryErodeFilterType;
  typedef BinaryDilateImageFilter< TInputImage, TOutputImage, KernelType >      BinaryDilateFilterType;
  typedef GrayscaleErodeImageFilter< TInputImage, TOutputImage, KernelType >    GrayscaleErodeFilterType;
  typedef GrayscaleDilateImageFilter< TInputImage, TOutputImage, KernelType >   GrayscaleDilateFilterType;

  OperationType  m_Operation;

};
} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkMathematicalMorphologyImageFilter.txx"
#endif

#endif
