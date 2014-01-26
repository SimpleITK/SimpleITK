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
     * \sa itk::simple::ReadImage for the procedural interface
     **/
    class SITKIO_EXPORT ImageSeriesReader
      : public ImageReaderBase
    {
    public:
      typedef ImageSeriesReader Self;

      ImageSeriesReader();

      /** Print ourselves to string */
      virtual std::string ToString() const;

      /** return user readable name fo the filter */
      virtual std::string GetName() const { return std::string("ImageSeriesReader"); }

      /** \brief Generate a sequence of filenames from a directory with a DICOM data set.
       *
       * This method generates a sequence of filenames whose filenames
       * point to DICOM files. The ordering is based of one of
       * several strategies, which will read all images in the
       * directory ( assuming there is only one study/series ).
       *
       * \param directory         Set the directory that contains the DICOM data set.
       * \param recursive         Recursively parse the input directory.
       * \param useSeriesDetails  Use additional series information such as ProtocolName and SeriesName to identify when a single SeriesUID contains multiple 3D volumes - as can occur with perfusion and DTI imaging.
       * \param loadSequences     Parse any sequences in the DICOM data set. Loading DICOM files is faster when sequences are not needed.
       * \param loadPrivateTags   Parse any private tags in the DICOM data set. Defaults to false to skip private tags. Loading DICOM files faster is when private tags are not needed.
       *
       * \sa itk::GDCMSeriesFileNames
       **/
      static std::vector<std::string> GetGDCMSeriesFileNames( const std::string &directory,
                                                              bool useSeriesDetails= true,
                                                              bool recursive = false,
                                                              bool loadSequences = false,
                                                              bool loadPrivateTags = false )
        {
        return ImageSeriesReader::GetGDCMSeriesFileNames( directory, "", useSeriesDetails, recursive, loadSequences, loadPrivateTags );
        }


      /** \brief Generate a sequence of filenames from a directory with a DICOM data set and a series ID.
       *
       * This method generates a sequence of filenames whose filenames
       * point to DICOM files. The data set may contain multiple series.
       * The seriesID string is used to select a specific series.  The
       * ordering of the filenames is based of one of several strategies,
       * which will read all images in the directory ( assuming there is
       * only one study/series ).
       *
       * \param directory         Set the directory that contains the DICOM data set.
       * \param recursive         Recursively parse the input directory.
       * \param seriesID          Set the name that identifies a particular series.
       * \param useSeriesDetails  Use additional series information such as ProtocolName and SeriesName to identify when a single SeriesUID contains multiple 3D volumes - as can occur with perfusion and DTI imaging.
       * \param loadSequences     Parse any sequences in the DICOM data set. Loading DICOM files is faster when sequences are not needed.
       * \param loadPrivateTags   Parse any private tags in the DICOM data set. Defaults to false to skip private tags. Loading DICOM files is faster when private tags are not needed.
       *
       * \sa itk::GDCMSeriesFileNames
       **/
      static std::vector<std::string> GetGDCMSeriesFileNames( const std::string &directory,
                                                              const std::string &seriesID,
                                                              bool useSeriesDetails= true,
                                                              bool recursive = false,
                                                              bool loadSequences = false,
                                                              bool loadPrivateTags = false );

      /** \brief Get all the seriesIDs from a DICOM data set
       *
       * \param directory  The directory that contains the DICOM data set
       * \sa itk::GDCMSeriesFileNames
       **/
      static std::vector<std::string> GetGDCMSeriesIDs( const std::string &directory );

      Self& SetFileNames ( const std::vector<std::string> &fileNames );
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
  SITKIO_EXPORT Image ReadImage ( const std::vector<std::string> &fileNames );
  }
}

#endif
