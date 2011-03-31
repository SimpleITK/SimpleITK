#ifndef __sitkImageReaderBase_h
#define __sitkImageReaderBase_h


#include "sitkNonCopyable.h"

#include <itkImageIOBase.h>

namespace itk {
  namespace simple {

    /** \class ImageReaderBase
     * \brief An abract base class for image readers
     *
     */
    template <typename TDerived>
    class ImageReaderBase :
      protected NonCopyable
    {
    public:
      // The default constructor and the destructor will be implicitly
      // declared as public.

    protected:

      Image ImageIODispatch( const std::string &fileName );

    private:
      template < unsigned int VImageDimension >
      Image ExecuteInternalReadScalar( itk::ImageIOBase::IOComponentType componentType );

      template < unsigned int VImageDimension >
      Image ExecuteInternalReadVector( itk::ImageIOBase::IOComponentType componentType );

      template <typename TImageType >
      Image ExecuteInternal( void )
      {
        return static_cast<TDerived*>(this)->ExecuteInternal<TImageType>();
      }

    };
  }
}

#include "sitkImageReaderBase.txx"


#endif // __sitkImageReaderBase_h
