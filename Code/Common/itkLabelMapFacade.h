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
  #ifndef __itkLabelMapFacade_h
  #define __itkLabelMapFacade_h

  #include "itkLabelMap.h"

  namespace itk
  {
  /** \class LabelMapFacade
   *  \brief Adds PixelContainer API to a LabelMap
   *
   * LabelMapFacade is intended to add a fake API for GetPixelContainer()
   * to its base class, the LabelMap.
   *
   * \ingroup ImageObjects
   * \ingroup LabeledImageObject
   */
  template< class TLabelObject >
class ITK_EXPORT LabelMapFacade : public LabelMap< TLabelObject >
{
public:
  /** Standard class typedefs */
  typedef LabelMapFacade               Self;
  typedef LabelMap< TLabelObject>      Superclass;
  typedef SmartPointer< Self >         Pointer;
  typedef SmartPointer< const Self >   ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro( LabelMapFacade, LabelMap );

  typedef TLabelObject LabelObjectType;

  typedef typename Superclass::SizeValueType SizeValueType;

  /** Label typedef support. */
  typedef typename LabelObjectType::LabelType LabelType;
  typedef LabelType                           PixelType;

  /** Container used to store pixels in the image.
   *  This type is only provided here for keeping the API consistency of the Image family.
   *  The label map doesn't really store pixels in the way images do.
   */
  typedef ImportImageContainer< SizeValueType, PixelType > PixelContainer;

  /** Return a pointer to the container.
   *  This is NULL on purpose since LabelMaps do not really use a pixel buffer.
   */
  PixelContainer * GetPixelContainer() { return NULL; }
  const PixelContainer * GetPixelContainer() const { return NULL; }

protected:
  LabelMapFacade();
  virtual ~LabelMapFacade() {}
  void PrintSelf(std::ostream & os, Indent indent) const;

private:
  LabelMapFacade(const Self &); //purposely not implemented
  void operator=(const Self &); //purposely not implemented
};
} // end namespace itk

#endif
