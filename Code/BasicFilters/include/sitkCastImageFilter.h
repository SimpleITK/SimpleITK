#ifndef __sitkCastImageFilter_h
#define __sitkCastImageFilter_h

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
 */
class CastImageFilter
  : public ImageFilter
{
public:
  typedef CastImageFilter      Self;

  /** Set/Get the output pixel type */
  Self& SetOutputPixelType( PixelIDValueType pixelID );
  PixelIDValueType GetOutputPixelType( void ) const;

  /**
   * Default Constructor that takes no arguments and initializes
   * default parameters
    */
  CastImageFilter();

  /** Name of this class */
  std::string GetName() const { return std::string ( "Cast"); }

  // See super class for doxygen
  std::string ToString() const;

  // See super class for doxygen
  Image Execute ( const Image & );

private:

  PixelIDValueType m_OutputPixelType;

  /** Methods to actually implement conversion from one image type
   * to another.
   *
   * These methods implement CastImageFilter,
   * ImageToVectorImageFilter, and LabelImageToLabelMapImageFilter
   * respectively.
   *
   * @{
   */
  template<typename TImageType, typename TOutputImageType>
  Image ExecuteInternalCast( const Image& inImage );

  template<typename TImageType, typename TOutputImageType>
  Image ExecuteInternalToVector( const Image& inImage );

  template<typename TImageType, typename TOutputImageType>
  Image ExecuteInternalToLabel( const Image& inImage );
  /** @} */

// SWIG does not appear to process private classes correctly
#ifndef SWIG

  /** An addressor of ExecuteInternalCast to be utilized with
   * registering member functions with the factory.
   */
  template < class TMemberFunctionPointer >
  struct CastAddressor
  {
    typedef typename ::detail::FunctionTraits<TMemberFunctionPointer>::ClassType ObjectType;

    template< typename TImageType1, typename TImageType2 >
    TMemberFunctionPointer operator() ( void ) const
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
    typedef typename ::detail::FunctionTraits<TMemberFunctionPointer>::ClassType ObjectType;

    template< typename TImageType1, typename TImageType2 >
    TMemberFunctionPointer operator() ( void ) const
    {
      return &ObjectType::template ExecuteInternalToVector< TImageType1, TImageType2 >;
    }
  };

  /** An addressor of ExecuteInternalToLabel to be utilized with
   * registering member functions with the factory.
   */
  template < class TMemberFunctionPointer >
  struct ToLabelAddressor
  {
    typedef typename ::detail::FunctionTraits<TMemberFunctionPointer>::ClassType ObjectType;

    template< typename TImageType1, typename TImageType2 >
    TMemberFunctionPointer operator() ( void ) const
    {
      return &ObjectType::template ExecuteInternalToLabel< TImageType1, TImageType2 >;
    }
  };
#endif

  /**
  * The methods are used to instantiate and register member functions
  * with the factory. Each function is split into a separate file to
  * make the compilation units smaller, and take less time to compile.
  * @{
  */
  void RegisterMemberFactory2();
  void RegisterMemberFactory2v();
  void RegisterMemberFactory2l();
  void RegisterMemberFactory3();
  void RegisterMemberFactory3v();
  void RegisterMemberFactory3l();
  /** @} */

  typedef Image (Self::*MemberFunctionType)( const Image& );
  std::auto_ptr<detail::DualMemberFunctionFactory<MemberFunctionType> > m_DualMemberFactory;

};

  Image Cast ( const Image& image, PixelIDValueType pixelID );

}
}
#endif
