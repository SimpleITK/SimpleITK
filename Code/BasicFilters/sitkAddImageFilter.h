#ifndef __sitkAddImageFilter_h
#define __sitkAddImageFilter_h

#include "sitkMacro.h"
#include "sitkMemberFunctionFactory.h"
#include "sitkImage.h"



namespace itk {
  namespace simple {

    class AddImageFilter {
    public:
      typedef AddImageFilter Self;

      //
      // Type List Setup
      //

      // function pointer type
      typedef Image::Pointer (Self::*MemberFunctionType)( Image::Pointer, Image::Pointer );

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
      AddImageFilter();

      // Print ourselves out
      std::string ToString();

      Image::Pointer Execute ( Image::Pointer, Image::Pointer );

    private:


      template <class TImageType>
      Image::Pointer ExecuteInternal ( Image::Pointer image, Image::Pointer image2 );

      // friend to get access to executeInternal member
      friend struct detail::MemberFunctionAddressor<Self, MemberFunctionType>;


      std::auto_ptr<detail::MemberFunctionFactory<Self> > m_MemberFactory;
    };


  }
}
#endif
