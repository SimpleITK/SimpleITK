#ifndef __sitkImageSeriesReader_h
#define __sitkImageSeriesReader_h

#include "sitkMacro.h"
#include "sitkImage.h"
#include "sitkImageReaderBase.h"


namespace itk {
  namespace simple {

    /** \class ImageSeriesReader
     * \brief Read series of image into a SimpleITK image
     *
     */
    class ImageSeriesReader
      : public ImageReaderBase< ImageSeriesReader >
    {
    public:
      typedef ImageSeriesReader Self;


      Self& SetFileNames ( const std::vector<std::string> &fns );
      const std::vector<std::string> &GetFileNames() const;

      Image Execute();

    protected:
      friend class ImageReaderBase< ImageSeriesReader >;

      // methods which utlize the EnableIf idiom to conditionally
      // instatiate and execute the implementation
      template <class TImageType>
      typename EnableIf<IsInstantiated<TImageType>::Value, Image >::Type
      ExecuteInternal ( );
      template <class TImageType>
      typename DisableIf<IsInstantiated<TImageType>::Value, Image >::Type
      ExecuteInternal ( );

    private:

      std::vector<std::string> m_FileNames;
    };
  Image ReadImage ( const std::vector<std::string> &filenames );
  }
}

#endif
