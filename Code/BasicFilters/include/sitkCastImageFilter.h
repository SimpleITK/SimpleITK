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
#ifndef sitkCastImageFilter_h
#define sitkCastImageFilter_h

#include "sitkImageFilter.h"
#include "sitkPixelIDTokens.h"
#include "sitkDualMemberFunctionFactory.h"

#include <memory>

namespace itk
{
namespace simple
{

/** \class CastImageFilter
 * \brief A hybrid cast image filter to convert images to other types
 * of images.
 *
 * Several different ITK classes are implemented under the hood, to
 * convert between different image types.
 *
 * \sa itk::simple::Cast for the procedural interface
 */
class SITKBasicFilters_EXPORT CastImageFilter
  : public ImageFilter
{
public:
  using Self = CastImageFilter;

  /** Set/Get the output pixel type */
  SITK_RETURN_SELF_TYPE_HEADER SetOutputPixelType( PixelIDValueEnum pixelID );
  PixelIDValueEnum GetOutputPixelType( ) const;

  ~CastImageFilter() override;

  /**
   * Default Constructor that takes no arguments and initializes
   * default parameters
    */
  CastImageFilter();

  /** Name of this class */
  std::string GetName() const override { return std::string ("CastImageFilter"); }

  // See super class for doxygen
  std::string ToString() const override;

  // See super class for doxygen
  Image Execute ( const Image & );

private:

  PixelIDValueEnum m_OutputPixelType;

  /** Methods to actually implement conversion from one image type
   * to another.
   *
   * These methods implement CastImageFilter,
   * ComposeImageFilter, and LabelImageToLabelMapImageFilter
   * respectively.
   *
   * @{
   */
  template<typename TImageType, typename TOutputImageType>
  Image ExecuteInternalCast( const Image& inImage );

  template<typename TImageType, typename TOutputImageType>
  Image ExecuteInternalToVector( const Image& inImage );

  template<typename TImageType, typename TOutputImageType>
  Image ExecuteInternalVectorToImage( const Image& inImage );

  template<typename TImageType, typename TOutputImageType>
  Image ExecuteInternalToLabel( const Image& inImage );

  template<typename TImageType, typename TOutputImageType>
  Image ExecuteInternalLabelToImage( const Image& inImage );
  /** @} */

// SWIG does not appear to process private classes correctly
#ifndef SWIG

  /** An addressor of ExecuteInternalCast to be utilized with
   * registering member functions with the factory.
   */
  template < class TMemberFunctionPointer >
  struct CastAddressor
  {
    using ObjectType = typename ::detail::FunctionTraits<TMemberFunctionPointer>::ClassType;

    template< typename TImageType1, typename TImageType2 >
    TMemberFunctionPointer operator() ( ) const
    {
      return &ObjectType::template ExecuteInternalCast< TImageType1, TImageType2 >;
    }
  };

  /** An addressor of ExecuteInternalToVector to be utilized with
   * registering member functions with the factory.
   */
  template < class TMemberFunctionPointer >
  struct ToVectorAddressor
  {
    using ObjectType = typename ::detail::FunctionTraits<TMemberFunctionPointer>::ClassType;

    template< typename TImageType1, typename TImageType2 >
    TMemberFunctionPointer operator() ( ) const
    {
      using OutputImageType = typename TImageType2::template Rebind<typename TImageType2::PixelType, TImageType1::ImageDimension-1>::Type;
      return &ObjectType::template ExecuteInternalToVector< TImageType1, OutputImageType >;
    }
  };

  /** An addressor of ExecuteInternalVectorToImage to be utilized with
   * registering member functions with the factory.
   */
  template < class TMemberFunctionPointer >
  struct VectorToImageAddressor
  {
    using ObjectType = typename ::detail::FunctionTraits<TMemberFunctionPointer>::ClassType;

    template< typename TImageType1, typename TImageType2 >
    TMemberFunctionPointer operator() ( ) const
    {
      using OutputImageType = typename TImageType2::template Rebind<typename TImageType2::PixelType, TImageType1::ImageDimension+1>::Type;
      return &ObjectType::template ExecuteInternalVectorToImage< TImageType1, OutputImageType >;
    }
  };


  /** An addressor of ExecuteInternalToLabel to be utilized with
   * registering member functions with the factory.
   */
  template < class TMemberFunctionPointer >
  struct ToLabelAddressor
  {
    using ObjectType = typename ::detail::FunctionTraits<TMemberFunctionPointer>::ClassType;

    template< typename TImageType1, typename TImageType2 >
    TMemberFunctionPointer operator() ( ) const
    {
      return &ObjectType::template ExecuteInternalToLabel< TImageType1, TImageType2 >;
    }
  };

 /** An addressor of ExecuteInternalToLabel to be utilized with
   * registering member functions with the factory.
   */
  template < class TMemberFunctionPointer >
  struct LabelToAddressor
  {
    using ObjectType = typename ::detail::FunctionTraits<TMemberFunctionPointer>::ClassType;

    template< typename TImageType1, typename TImageType2 >
    TMemberFunctionPointer operator() ( ) const
    {
      return &ObjectType::template ExecuteInternalLabelToImage< TImageType1, TImageType2 >;
    }
  };
#endif

  /**
  * These methods are used to instantiate and register member functions
  * with the factory. Each function is split into a separate file to
  * make the compilation units smaller, and take less time to compile.
  * @{
  */
  void RegisterMemberFactory2();
  void RegisterMemberFactory3();
  void RegisterMemberFactory4();
  /** @} */

  typedef Image (Self::*MemberFunctionType)( const Image& );
  std::unique_ptr<detail::DualMemberFunctionFactory<MemberFunctionType> > m_DualMemberFactory;

};

  SITKBasicFilters_EXPORT Image Cast ( const Image& image, PixelIDValueEnum pixelID );

}
}
#endif
