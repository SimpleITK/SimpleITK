#ifndef __sitkImageFileReader_h
#define __sitkImageFileReader_h

#include "sitkMacro.h"
#include "sitkImage.h"
#include "sitkImageReaderBase.h"

namespace itk {
  namespace simple {

    /** \class ImageFileReader
     * \brief Read a 2D or 3D image and return a smart pointer to a SimpleITK
     * image
     *
     * This reader handles scalar and vector images and returns an image with
     * the same type as the file on disk.
     */
    class ImageFileReader
      : public ImageReaderBase< ImageFileReader >
    {
    public:
      typedef ImageFileReader Self;

      Self& SetFileName ( std::string fn );
      std::string GetFileName();
      Image Execute();

    protected:
      friend class ImageReaderBase< ImageFileReader >;

      // methods which utlize the EnableIf idiom to conditionally
      // instatiate ad execute the implementation
      template <class TImageType>
      typename EnableIf<IsInstantiated<TImageType>::Value, Image >::Type
      ExecuteInternal ( );
      template <class TImageType>
      typename DisableIf<IsInstantiated<TImageType>::Value, Image >::Type
      ExecuteInternal ( );

    private:

      std::string m_FileName;
    };

    Image ReadImage ( std::string filename );
  }
}

#endif
