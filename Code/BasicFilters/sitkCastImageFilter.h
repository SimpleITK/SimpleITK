#ifndef __sitkCastImageFilter_h
#define __sitkCastImageFilter_h

#include "sitkImageFilter.h"

#include "sitkPixelIDTokens.h"

namespace itk {
  namespace simple {

  /** \brief A hybrid cast image filter to convert basic images to
   * other types.
   *
   * This simple filter converts images of basic pixels into other
   * basic pixels or vector pixels or label maps.
   */
    class CastImageFilter : ImageFilter {
    public:
      typedef CastImageFilter      Self;

      typedef BasicPixelIDTypeList PixelIDTypeList;


      /** Set/Get the output pixel type */
      Self& SetOutputPixelType( PixelIDValueEnum pixelID ) { this->m_OutputPixelType =  PixelIDValueType(pixelID); return *this; }
      Self& SetOutputPixelType( PixelIDValueType pixelID ) { this->m_OutputPixelType = pixelID; return *this; }
      PixelIDValueType GetOutputPixelType( void ) const { return this->m_OutputPixelType; }

      /**
       * Default Constructor that takes no arguments and initializes
       * default parameters
       */
      CastImageFilter();

      // See super class for doxygen
      std::string ToString() const;

      // See super class for doxygen
      Image::Pointer Execute ( Image::Pointer );

    private:

      PixelIDValueType m_OutputPixelType;

      /** Methods to actually implement conversion from one image type
       * to another.
       *
       * The enable if idiom is used only to instatiate these methods
       * with the supported images. The compiler will fall back to the
       * methods with ellipses if this methods is not enabled.
       *
       * These methods implement CastImageFilter,
       * ImageToVectorImageFilter, and LabelImageToLabelMapImageFilter
       * respectively.
       *
       * @{
       */
      template<typename TImageType, typename TOutputImageType>
      typename EnableIf< IsInstantiated<TOutputImageType>::Value, Image::Pointer>::Type
      ExecuteInternalToBasic( const TImageType* inImage );

      template<typename TImageType, typename TOutputImageType>
      typename EnableIf< IsInstantiated<TOutputImageType>::Value, Image::Pointer>::Type
      ExecuteInternalToVector( const TImageType* inImage );

      template<typename TImageType, typename TOutputImageType>
      typename EnableIf< IsInstantiated<TOutputImageType>::Value, Image::Pointer>::Type
      ExecuteInternalToLabel( const TImageType* inImage );
      /** @} */


      /**
       * The following methods should never acutally be executed if
       * the logic is correct in this filter.
       *
       * These methods should only be instantiated for output image
       * types which are not instantiated.
       * @{ */
      template<typename TImageType, typename TOutputImageType>
      Image::Pointer
      ExecuteInternalToBasic( ... ) throw( GenericException )
      { ExecuteDispatchLogicError(); return NULL; }

      template<typename TImageType, typename TOutputImageType>
      Image::Pointer
      ExecuteInternalToVector( ... ) throw( GenericException )
      { ExecuteDispatchLogicError(); return NULL; }

      template<typename TImageType, typename TOutputImageType>
      Image::Pointer
      ExecuteInternalToLabel( ... ) throw( GenericException )
      { ExecuteDispatchLogicError(); return NULL; }
      /** @} */

      /**
       * This method has a failing assert and throws an exception when executed
       */
      static void ExecuteDispatchLogicError( void )  throw( GenericException ) ;

      /** Dispatch methods for the member function factory */
      template <typename TImageType>
      Image::Pointer ExecuteInternal( Image::Pointer image );

      typedef Image::Pointer (Self::*MemberFunctionType)( Image::Pointer );

      friend struct detail::MemberFunctionAddressor<MemberFunctionType>;
      std::auto_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;

    };


  }
}
#endif
