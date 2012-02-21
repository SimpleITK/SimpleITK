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
#ifndef __sitkImageFilter_h
#define __sitkImageFilter_h

#include "sitkMacro.h"
#include "sitkImage.h"
#include "sitkMemberFunctionFactory.h"
#include "sitkBasicFilters.h"

namespace itk {
  namespace simple {

  /** \class ImageFilter
   * \brief The base interface for SimpleITK filters that take one input image
   *
   * All SimpleITK filters which take one input image should inherit from this
   * class
   */
  class SITKBasicFilters_EXPORT ImageFilter :protected NonCopyable
  {
    public:
      typedef ImageFilter Self;

      //
      // Type List Setup
      //

      //
      // Filter Setup
      //

      /**
       * Default Constructor that takes no arguments and initializes
       * default parameters
       */
      ImageFilter();

      /**
       * Default Destructor
       */
      virtual ~ImageFilter();

      // Print ourselves out
      virtual std::string ToString() const = 0;

      virtual Image Execute ( const Image & ) = 0;

      /** return user readable name fo the filter */
      virtual std::string GetName() const = 0;

    private:

    };


  }
}
#endif
