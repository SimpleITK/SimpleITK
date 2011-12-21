#ifndef __sitkImageFilterExecuteBase_h
#define  __sitkImageFilterExecuteBase_h

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
  struct ImageFilterExecuteBase<0>
  {
    virtual Image Execute( void ) = 0;
  };

  template <>
  struct ImageFilterExecuteBase<1>
  {
    virtual Image Execute( const Image & ) = 0;
  };

  template <>
  struct ImageFilterExecuteBase<2>
  {
    virtual Image Execute( const Image &, const Image & ) = 0;
  };

  template <>
  struct ImageFilterExecuteBase<3>
  {
    virtual Image Execute( const Image &, const Image &, const Image & ) = 0;
  };

  template <>
  struct ImageFilterExecuteBase<4>
  {
    virtual Image Execute( const Image &, const Image &, const Image &, const Image & ) = 0;
  };

  template <>
  struct ImageFilterExecuteBase<5>
  {
    virtual Image Execute( const Image &, const Image &, const Image &, const Image &, const Image & ) = 0;
  };

/** \endcond */
  }
}

#endif //  __sitkImageFilterExecuteBase_h
