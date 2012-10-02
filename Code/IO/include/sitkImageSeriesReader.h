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
#ifndef __sitkImageSeriesReader_h
#define __sitkImageSeriesReader_h

#include "sitkMacro.h"
#include "sitkImage.h"
#include "sitkImageReaderBase.h"
#include "sitkMemberFunctionFactory.h"

namespace itk {
  namespace simple {

    /** \class ImageSeriesReader
     * \brief Read series of image into a SimpleITK image
     *
     */
    class SITKIO_EXPORT ImageSeriesReader
      : public ImageReaderBase
    {
    public:
      typedef ImageSeriesReader Self;

      ImageSeriesReader();

      /** \brief Generate a sequence of filenames from a directory
       * with DICOM series.
       *
       * This method generates a sequence of filenames whose filenames
       * points to a DICOM file. The ordering is based of one of
       * several strategies, which will read all images in the
       * directory ( assuming there is only one study/series ).
       *
       * \param directory Set the directory that contains the DICOM series.
       * \param useSeriesDetails Use additional series information such as ProtocolName and SeriesName to identify when a single SeriesUID contains multiple 3D volumes - as can occur with perfusion and DTI imaging.
       * \param loadSequences Parse any sequences in the DICOM file. This makes loading DICOM files faster when sequences are not needed.
       * \param loadPrivateTags Parse any private tags in the DICOM file. Defaults to false to skip private tags. This makes loading DICOM files faster when private tags are not needed.
       *
       * \sa itk::GDCMSeriesFileNames
       */
      static std::vector<std::string> GetGDCMSeriesFileNames( const std::string &directory,
                                                              bool useSeriesDetails= true,
                                                              bool recursive = false,
                                                              bool loadSequences = false,
                                                              bool loadPrivateTags = false );

      Self& SetFileNames ( const std::vector<std::string> &fns );
      const std::vector<std::string> &GetFileNames() const;

      Image Execute();

    protected:

      template <class TImageType> Image ExecuteInternal ( void );

    private:

      // function pointer type
      typedef Image (Self::*MemberFunctionType)( void );

      // friend to get access to executeInternal member
      friend struct detail::MemberFunctionAddressor<MemberFunctionType>;
      std::auto_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;

      std::vector<std::string> m_FileNames;
    };
  SITKIO_EXPORT Image ReadImage ( const std::vector<std::string> &filenames );
  }
}

#endif
