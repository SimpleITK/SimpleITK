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
#ifndef __sitkImageFilterExecuteBase_h
#define  __sitkImageFilterExecuteBase_h

#include "sitkProcessObject.h"
#include "sitkImage.h"

namespace itk {
  namespace simple {

  /** \class ImageFilterExecuteBase
   *
   * This class is a abstract base class which provides a protype of
   * the Execute method with a variable number of image parameters.
   */
  template <unsigned int N> struct ImageFilterExecuteBase;

  /** \cond SPECIALIZATION_IMPLEMENTATION */
  template <>
  struct SITKBasicFilters0_EXPORT ImageFilterExecuteBase<0> : public itk::simple::ProcessObject
  {
    virtual ~ImageFilterExecuteBase();
    virtual Image Execute( void ) = 0;
  };

  template <>
  struct SITKBasicFilters0_EXPORT ImageFilterExecuteBase<1> : public ProcessObject
  {
    virtual ~ImageFilterExecuteBase();
    virtual Image Execute( const Image & ) = 0;
  };

  template <>
  struct SITKBasicFilters0_EXPORT ImageFilterExecuteBase<2> : public ProcessObject
  {
    virtual ~ImageFilterExecuteBase();
    virtual Image Execute( const Image &, const Image & ) = 0;
  };

  template <>
  struct SITKBasicFilters0_EXPORT ImageFilterExecuteBase<3> : public ProcessObject
  {
    virtual ~ImageFilterExecuteBase();
    virtual Image Execute( const Image &, const Image &, const Image & ) = 0;
  };

  template <>
  struct SITKBasicFilters0_EXPORT ImageFilterExecuteBase<4> : public ProcessObject
  {
    virtual ~ImageFilterExecuteBase();
    virtual Image Execute( const Image &, const Image &, const Image &, const Image & ) = 0;
  };

  template <>
  struct SITKBasicFilters0_EXPORT ImageFilterExecuteBase<5> : public ProcessObject
  {
    virtual ~ImageFilterExecuteBase();
    virtual Image Execute( const Image &, const Image &, const Image &, const Image &, const Image & ) = 0;
  };

/** \endcond */
  }
}

#endif //  __sitkImageFilterExecuteBase_h
