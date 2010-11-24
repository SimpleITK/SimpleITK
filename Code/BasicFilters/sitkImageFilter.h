#ifndef __sitkImageFilter_h
#define __sitkImageFilter_h

#include "sitkMacro.h"
#include "sitkMemberFunctionFactory.h"
#include "sitkImage.h"

#define sitkSingleImageMemberFunctionDispatcher \
typedef Image::Pointer (Self::*MemberFunctionType)( Image::Pointer ); \
template <class TImageType> Image::Pointer ExecuteInternal ( Image::Pointer image ); \
friend struct detail::MemberFunctionAddressor<MemberFunctionType>; \
std::auto_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;

#define sitkSetGetMacro( type, name ) \
  Self & Set##name( const type & value_ ) \
    { \
    this->m_##name = value_; \
    return *this; \
    } \
  type Get##name() const \
    { \
    return this->m_##name; \
    }

#define sitkTransferMemberVariableToFilterMacro( name ) \
  filter->Set##name ( this->m_##name );

namespace itk {
  namespace simple {

    class ImageFilter {
    public:
      typedef ImageFilter Self;

      //
      // Type List Setup
      //

      // list of pixel types supported only basic since rgb and
      // vectors are not supported by this filter
      typedef BasicPixelTypeList PixelTypeList;


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

      virtual Image::Pointer Execute ( Image::Pointer ) = 0;

    private:

    };


  }
}
#endif
