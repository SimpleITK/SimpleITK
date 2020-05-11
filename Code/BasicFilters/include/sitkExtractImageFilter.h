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
#ifndef sitkExtractImageFilter_h
#define sitkExtractImageFilter_h

#include <memory>

#include "sitkBasicFilters.h"
#include "sitkImageFilter.h"

namespace itk {
  namespace simple {

    /**\class ExtractImageFilter
     * \brief Decrease the image size by cropping the image to the selected region bounds.
     *
     * ExtractImageFilter changes the image boundary of an image by
     * removing pixels outside the target region. The region is
     * specified as a Size and Index. The Size must
     * be specified, while the Index defaults to zeros.
     *
     * ExtractImageFilter can collapses dimensions so that the input
     * image may have more dimensions than the output image (i.e. 4-D
     * input image to a 3-D output image). To specify what dimensions
     * to collapse, the Size must be specified. For any dimension dim
     * where the Size[dim] == 0, that dimension is collapsed. The
     * index to collapse on is specified by Index[dim]. For example,
     * we have a image 4D = a 4x4x4x4 image, and we want to get a 3D
     * image, 3D = a 4x4x4 image, specified as [x,y,z,2] from 4D
     * (i.e. the 3rd "time" slice from 4D). The Size = [4,4,4,0] and
     * Index = [0,0,0,2].
     *
     * The number of dimension in Size and Index must at least
     * dimension of the input image. The number of non-zero dimensions
     * in Size determines the output dimension.
     *
     * Determining the direction of the collapsed output image from an
     * larger dimensional input space is an ill defined problem in
     * general. It is required that the application developer select
     * the desired transformation strategy for collapsing direction
     * cosines. The strategy defaults to the guess approach. Direction
     * Collapsing Strategies: 1) DirectionCollapseToUnknown(); This is
     * the default in ITK and the filter can not run when this is
     * set. 1) DirectionCollapseToIdentity(); Output has identity
     * direction no matter what 2) DirectionCollapseToSubmatrix();
     * Output direction is the sub-matrix if it is positive definite,
     * else throw an exception.
     *
     * This filter is implemented as a multithreaded filter. It
     * provides a DynamicThreadedGenerateData() method for its
     * implementation.
     *
     * \see CropImageFilter
     * \sa itk::simple::Extract for the procedural interface
     * \sa itk::ExtractImageFilter for the Doxygen on the original ITK class.
     */
    class SITKBasicFilters_EXPORT ExtractImageFilter : public ImageFilter {
    public:
      using Self = ExtractImageFilter;

      /** Destructor */
      virtual ~ExtractImageFilter();

      /** Default Constructor that takes no arguments and initializes
       * default parameters */
      ExtractImageFilter();

      /** Define the pixels types supported by this filter */
      using PixelIDTypeList = NonLabelPixelIDTypeList;

      /** \brief Set the size of the region to extract.
       *
       * The size of the region to extract should be
       * specified. Dimensions which have a size of 0 are
       * collapsed. The number of non-zero sized determines the output
       * dimension.
       */
      SITK_RETURN_SELF_TYPE_HEADER SetSize ( std::vector<unsigned int> Size ) { this->m_Size = std::move(Size); return *this; }

      /** \brief Get the size of the region to extract.
       */
      std::vector<unsigned int> GetSize() const { return this->m_Size; }

      /** \brief Set the starting index of the input image to extract.
       *
       * The index defaults to all zeros.
       */
      SITK_RETURN_SELF_TYPE_HEADER SetIndex ( std::vector<int> Index ) { this->m_Index = std::move(Index); return *this; }

      /** \brief Get the starting index to extract.
       */
      std::vector<int> GetIndex() const { return this->m_Index; }

      typedef enum {DIRECTIONCOLLAPSETOUNKOWN,DIRECTIONCOLLAPSETOIDENTITY,DIRECTIONCOLLAPSETOSUBMATRIX,DIRECTIONCOLLAPSETOGUESS} DirectionCollapseToStrategyType;

      /** \brief Set the strategy to be used to collapse physical space dimensions.
       *
       * DIRECTIONCOLLAPSETOIDENTITY Set
       * the strategy so that all collapsed images have an identity
       * direction. Use this strategy when you know that retention of
       * the physical space orientation of the collapsed image is not
       * important.
       *
       * DIRECTIONCOLLAPSETOGUESS Set the
       * strategy so that all collapsed images where output direction
       * is the sub-matrix if it is positive definite, else return
       * identity. This is backwards compatible with ITKv3, but is
       * highly discouraged because the results are difficult to
       * anticipate under differing data scenarios.
       *
       * DIRECTIONCOLLAPSETOSUBMATRIX Set the strategy so that all
       * collapsed images where output direction is the sub-matrix if
       * it is positive definite, else throw an exception. Use this
       * strategy when it is known that properly identified physical
       * space sub-volumes can be reliably extracted from a higher
       * dimensional space. For example when the application
       * programmer knows that a 4D image is 3D+time, and that the 3D
       * sub-space is properly defined.
       */
      SITK_RETURN_SELF_TYPE_HEADER SetDirectionCollapseToStrategy ( DirectionCollapseToStrategyType DirectionCollapseToStrategy ) { this->m_DirectionCollapseToStrategy = DirectionCollapseToStrategy; return *this; }

      /** Get the currently set strategy for collapsing directions of physical space.
       */
      DirectionCollapseToStrategyType GetDirectionCollapseToStrategy() const { return this->m_DirectionCollapseToStrategy; }

      /** Name of this class */
      std::string GetName() const { return "ExtractImageFilter"; }

      /** Print ourselves out */
      std::string ToString() const;


      /** Execute the filter on the input image */
#ifndef SWIG
      Image Execute ( Image&& image1 );
#endif
      Image Execute ( const Image& image1 );

    private:

      /** Setup for member function dispatching */

      using MemberFunctionType = Image (Self::*)( const Image& image1 );
      template <class TImageType> Image ExecuteInternal ( const Image& image1 );

      friend struct detail::MemberFunctionAddressor<MemberFunctionType>;

      std::unique_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;


      template <class TImageType, unsigned int OutputDimension>
        Image ExecuteInternal ( const TImageType *image1, unsigned int outputDimension, std::integral_constant<unsigned int, OutputDimension> meta );
      template <class TImageType>
        Image ExecuteInternal ( const TImageType *image1, unsigned int outputDimension, std::integral_constant<unsigned int, 1> meta );


      std::vector<unsigned int>  m_Size{std::vector<unsigned int>(SITK_MAX_DIMENSION, 1)};

      std::vector<int>  m_Index{std::vector<int>(SITK_MAX_DIMENSION, 0)};

      DirectionCollapseToStrategyType  m_DirectionCollapseToStrategy{itk::simple::ExtractImageFilter::DIRECTIONCOLLAPSETOGUESS};


      bool m_InPlace{false};
    };

    /**\
     * \brief Decrease the image size by cropping the image to the selected region bounds.
     *
     * This function directly calls the execute method of ExtractImageFilter
     * in order to support a procedural API
     *
     * \sa itk::simple::ExtractImageFilter for the object oriented interface
     * @{
     */
#ifndef SWIG
     SITKBasicFilters_EXPORT Image Extract ( Image&& image1, std::vector<unsigned int> size = std::vector<unsigned int>(SITK_MAX_DIMENSION, 1), std::vector<int> index = std::vector<int>(SITK_MAX_DIMENSION, 0), ExtractImageFilter::DirectionCollapseToStrategyType directionCollapseToStrategy = itk::simple::ExtractImageFilter::DIRECTIONCOLLAPSETOGUESS );
#endif
     SITKBasicFilters_EXPORT Image Extract ( const Image& image1, std::vector<unsigned int> size = std::vector<unsigned int>(SITK_MAX_DIMENSION, 1), std::vector<int> index = std::vector<int>(SITK_MAX_DIMENSION, 0), ExtractImageFilter::DirectionCollapseToStrategyType directionCollapseToStrategy = itk::simple::ExtractImageFilter::DIRECTIONCOLLAPSETOGUESS );

     /** @} */
  }
}
#endif
