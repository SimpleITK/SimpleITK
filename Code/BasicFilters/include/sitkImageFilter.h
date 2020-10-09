/*=========================================================================
*
*  Copyright NumFOCUS
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
#ifndef sitkImageFilter_h
#define sitkImageFilter_h

#include "sitkMacro.h"
#include "sitkMemberFunctionFactory.h"
#include "sitkBasicFilters.h"
#include "sitkProcessObject.h"

namespace itk {

  namespace simple {

  /** \class ImageFilter
   * \brief The base interface for SimpleITK filters that take one input image
   *
   * All SimpleITK filters which take one input image should inherit from this
   * class
   */
  class SITKBasicFilters0_EXPORT ImageFilter:
      public ProcessObject
  {
    public:
      using Self = ImageFilter;

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
      virtual ~ImageFilter() = 0;

    protected:

      // Simple ITK must use a zero based index
      template< class TImageType>
      static void FixNonZeroIndex( TImageType * img )
      {
        assert( img );

        typename TImageType::RegionType r = img->GetLargestPossibleRegion();
        typename TImageType::IndexType idx = r.GetIndex();

        for( unsigned int i = 0; i < TImageType::ImageDimension; ++i )
          {

          if ( idx[i] != 0 )
            {
            // if any of the indicies are non-zero, then just fix it
            typename TImageType::PointType o;
            img->TransformIndexToPhysicalPoint( idx, o );
            img->SetOrigin( o );

            idx.Fill( 0 );
            r.SetIndex( idx );

            // Need to set the buffered region to match largest
            img->SetRegions( r );

            return;
            }
          }

      }

      /** Verify the dimension of image1 matches the dimension of
       * image2, and if not then an exception is thrown.
       */
      void CheckImageMatchingDimension(const Image &image1, const Image& image2, const std::string &image2Name );

      /** Verify the pixel type of image1 matches the pixel type of
       * image2, and if different then an exception is thrown.
       */
      void CheckImageMatchingPixelType(const Image &image1, const Image& image2, const std::string &image2Name );

      /** Verify the size in pixel of image1 matches the size of
       * image2, and if different then an exception is thrown.
       */
      void CheckImageMatchingSize(const Image &image1, const Image& image2, const std::string &image2Name );
  };
  }
}
#endif
