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
#ifndef __sitkDualImageFilter_h
#define __sitkDualImageFilter_h

#include "sitkImageFilter.h"

namespace itk {
  namespace simple {

  /** \class DualImageFilter
   * \brief The base interface for SimpleITK filters that take two input images
   *
   * All SimpleITK filters which take two input images should inherit from this
   * class
   */
  class SITKBasicFilters_EXPORT DualImageFilter :
      protected NonCopyable
  {
    public:

      /**
       * Default Constructor that takes no arguments and initializes
       * default parameters
       */
      DualImageFilter() {};


      // Print ourselves out
      virtual std::string ToString() const = 0;

      virtual Image Execute ( const Image&, const Image& ) = 0;

      virtual ~DualImageFilter() {}
    protected:

      template< class TImageType >
        typename TImageType::ConstPointer CastImageToITK( const Image &img )
      {
        typename TImageType::ConstPointer itkImage =
          dynamic_cast < const TImageType* > ( img.GetITKBase() );

        if ( itkImage.IsNull() )
          {
          sitkExceptionMacro( "Unexpected template dispatch error!" );
          }
        return itkImage;
      }

    private:

      //
    };

  }
}
#endif
