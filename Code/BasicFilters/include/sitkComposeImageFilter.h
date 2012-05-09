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
#ifndef __sitkComposeImageFilter_h
#define __sitkComposeImageFilter_h

#include "sitkImageFilter.h"
#include "sitkPixelIDTokens.h"
#include "sitkDualMemberFunctionFactory.h"

#include <memory>

namespace itk
{
namespace simple
{

/** \class ComposeImageFilter
 *
 * This filter joins together a set a scalar images into a single
 * VectorImage. All the input image must be the same type and have the
 * same image size and physical locations of the pixels.
 *
 */
class SITKBasicFilters0_EXPORT ComposeImageFilter
  : public ImageFilter<1>
{
public:
  typedef ComposeImageFilter      Self;

  /**
   * Default Constructor that takes no arguments and initializes
   * default parameters
    */
  ComposeImageFilter();

  /** Define the pixels types supported by this filter */
  typedef BasicPixelIDTypeList PixelIDTypeList;


  /** Name of this class */
  std::string GetName() const { return std::string ( "Compose"); }

  // See super class for doxygen
  std::string ToString() const;

  // See super class for doxygen
  Image Execute ( const std::vector<Image> & );
  Image Execute ( const Image &image );

private:


  /** Setup for member function dispatching */
  typedef Image (Self::*MemberFunctionType)( const std::vector<Image> & );
  template <class TImageType> Image ExecuteInternal ( const std::vector<Image>& images );


  friend struct detail::MemberFunctionAddressor<MemberFunctionType>;
  std::auto_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;


};

Image SITKBasicFilters0_EXPORT Compose ( const std::vector<Image>& images );

}
}
#endif
