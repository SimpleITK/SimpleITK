/*=========================================================================
*
*  Copyright Insight Software Consortium
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
#ifndef sitkImageSeriesWriter_h
#define sitkImageSeriesWriter_h

#include "sitkMacro.h"
#include "sitkImage.h"
#include "sitkProcessObject.h"
#include "sitkIO.h"
#include "sitkMemberFunctionFactory.h"

namespace itk {
  namespace simple {

    /** \class ImageSeriesWriter
     * \brief Writer series of image from a SimpleITK image.
     *
     * The ImageSeriesWriter is for writing a 3D image as a series of
     * 2D images. A list of names for the series of 2D images must be
     * provided, and an exception will be generated if the number of
     * file names does not match the size of the image in the z-direction.
     *
     * DICOM series cannot be written with this class, as an exception
     * will be generated. To write a DICOM series the individual
     * slices must be extracted, proper DICOM tags must be added to
     * the dictionaries, then written with the ImageFileWriter.
     *
     * \sa itk::simple::WriteImage for the procedural interface
     **/
    class SITKIO_EXPORT ImageSeriesWriter
      : public ProcessObject
    {
    public:
      typedef ImageSeriesWriter Self;

      ImageSeriesWriter();

      /** Print ourselves to string */
      virtual std::string ToString() const;

      /** return user readable name fo the filter */
      virtual std::string GetName() const { return std::string("ImageSeriesWriter"); }

      /** \brief Enable compression if available for file type.
       *
       * These methods Set/Get/Toggle the UseCompression flag which
       * get's passed to image file's itk::ImageIO object. This is
       * only a request as not all file formatts support compression.
       * @{ */
      SITK_RETURN_SELF_TYPE_HEADER SetUseCompression( bool UseCompression );
      bool GetUseCompression( void ) const;

      SITK_RETURN_SELF_TYPE_HEADER UseCompressionOn( void ) { return this->SetUseCompression(true); }
      SITK_RETURN_SELF_TYPE_HEADER UseCompressionOff( void ) { return this->SetUseCompression(false); }
      /** @} */

      /** The filenames to where the image slices are written.
        *
        * The number of filenames must match the number of slices in
        * the image.
        * @{ */
      SITK_RETURN_SELF_TYPE_HEADER SetFileNames ( const std::vector<std::string> &fileNames );
      const std::vector<std::string> &GetFileNames() const;
      /** @} */


      SITK_RETURN_SELF_TYPE_HEADER Execute( const Image& );
      SITK_RETURN_SELF_TYPE_HEADER Execute( const Image &image, const std::vector<std::string> &inFileNames, bool inUseCompression );

    protected:

      template <class TImageType> Self &ExecuteInternal ( const Image& inImage );

    private:

      // function pointer type
      typedef Self& (Self::*MemberFunctionType)( const Image& );

      // friend to get access to executeInternal member
      friend struct detail::MemberFunctionAddressor<MemberFunctionType>;
      nsstd::auto_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;

      bool m_UseCompression;
      std::vector<std::string> m_FileNames;
    };

  SITKIO_EXPORT void WriteImage ( const Image & image, const std::vector<std::string> &fileNames, bool inUseCompression=false );
  }
}

#endif
