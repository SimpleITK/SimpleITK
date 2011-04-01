#ifndef __sitkImageFileReader_h
#define __sitkImageFileReader_h

#include "sitkMacro.h"
#include "sitkImage.h"
#include "sitkImageReaderBase.h"
#include "sitkMemberFunctionFactory.h"

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
      : public ImageReaderBase
    {
    public:
      typedef ImageFileReader Self;

      Self& SetFileName ( std::string fn );
      std::string GetFileName();
      Image Execute();

      ImageFileReader();

    protected:

      template <class TImageType> Image ExecuteInternal ( void );

    private:

      // function pointer type
      typedef Image (Self::*MemberFunctionType)( void );

      // friend to get access to executeInternal member
      friend struct detail::MemberFunctionAddressor<MemberFunctionType>;
      std::auto_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;

      std::string m_FileName;
    };

    Image ReadImage ( std::string filename );
  }
}

#endif
