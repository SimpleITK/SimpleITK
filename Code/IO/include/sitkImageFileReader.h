/*=========================================================================
*
*  Copyright NumFOCUS
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
#ifndef sitkImageFileReader_h
#define sitkImageFileReader_h

#include "sitkMacro.h"
#include "sitkImage.h"
#include "sitkImageReaderBase.h"
#include "sitkMemberFunctionFactory.h"


namespace itk {

  class MetaDataDictionary;

  namespace simple {

    /** \class ImageFileReader
     * \brief Read an image file and return a SimpleITK Image.
     *
     * The reader can handle scalar images, and vector images. Pixel
     * types such as RGB, RGBA are loaded as multi-component
     * images with vector pixel types. Additionally, tensor images are
     * loaded with the pixel type being a 1-d vector.
     *
     * An interface is also provided to access the information from
     * the underlying itk::ImageIO. This information can be loaded
     * with the ReadImageInformation method. The information is from
     * the itk::ImageIO interface. In some degenerate cases reading
     * the bulk data may produce different results. Please see
     * itk::ImageFileReader for more details.
     *
     * Reading takes place by the ITK ImageIO factory mechanism. ITK
     * contains many ImageIO classes which are responsible for reading
     * separate file formats. By default, each ImageIO is asked if it
     * "can read" the file, and the first one which "can read" the
     * format is used. The list of available ImageIOs can be obtained
     * using the GetRegisteredImageIOs method. The ImageIO used can be
     * overridden with the SetImageIO method. This is useful in cases
     * when multiple ImageIOs "can read" the file and the user wants
     * to select a specific IO (not the first).
     *
     * \sa itk::simple::ReadImage for the procedural interface
     */
    class SITKIO_EXPORT ImageFileReader
      : public ImageReaderBase
    {
    public:
      using Self = ImageFileReader;

      ~ImageFileReader() override;

      ImageFileReader();

      /** Print ourselves to string */
      std::string ToString() const override;

      /** return user readable name of the filter */
      std::string GetName() const override { return std::string("ImageFileReader"); }

      SITK_RETURN_SELF_TYPE_HEADER SetFileName ( const std::string &fn );
      std::string GetFileName() const;

      Image Execute() override;

      // Interface methods to access image file's meta-data and image
      // information after calling Execute or after calling
      // MetaDataRead, which does not load the bulk pixel data.

      /** \brief Read only the meta-data and image information in the file.
       *
       * This method can be used to determine what the size and pixel
       * type of an image file is without reading the whole
       * image. Even if SimpleITK does not support an image of a
       * certain dimension or type, the meta-information can still be
       * read.
       */
      void ReadImageInformation();

      /** \brief Image information methods updated via ReadImageInformation
       *
       * These accessor methods are valid after a call to ReadImageInformation
       * or Execute. They contain the image information from the file
       * via the itk::ImageIO. Information such as NumberOfComponents
       * is based of the file format, so the number of components for
       * internal types such as RGB or complex may not be described
       * the same as with SimpleITK's Image interface.
       *
       * The PixelID has been converted from the ITK type to
       * SimpleITK's interpretation, and will not change when loaded
       * as a SimpleITK Image.
       * @{
       */
      PixelIDValueEnum GetPixelID( ) const;
      PixelIDValueType GetPixelIDValue( ) const;
      unsigned int GetDimension( ) const;
      unsigned int GetNumberOfComponents( ) const;
      const std::vector<double> &GetOrigin( ) const;
      const std::vector<double> &GetSpacing( ) const;
      const std::vector<double> &GetDirection() const;
      const std::vector<uint64_t> &GetSize( ) const;
      /** @} */

      /** \brief Get the meta-data dictionary keys
       *
       * This is only valid after successful ReadImageInformation or Execute
       * of this filter.
       *
       * Returns a vector of keys to the key/value entries in the
       * file's meta-data dictionary. Iterate through with these keys
       * to get the values.
       **/
      std::vector<std::string> GetMetaDataKeys( ) const;

      /** \brief Query a meta-data dictionary for the existence of a key.
       **/
      bool HasMetaDataKey( const std::string &key ) const;

      /** \brief Get the value of a meta-data dictionary entry as a string.
       *
       * If the key is not in the dictionary then an exception is
       * thrown.
       *
       * String types in the dictionary are returned as their native
       * string. Other types are printed to string before returning.
       **/
      std::string GetMetaData( const std::string &key ) const;


      /** \brief size of image to extract from file.
       *
       * By default the reader loads the entire image, this is
       * specified when the size has zero length.
       *
       * If specified, then the image returned from `Execute` will be
       * of this size. If the ImageIO and file support reading just a
       * region, then the reader will perform streaming.
       *
       * The dimension of the image can be reduced by specifying a
       * dimension's size as 0. For example a size of $[10,20,30,0,0]$
       * results in a 3D image with size of $[10,20,30]$. This
       * enables reading a 5D image into a 3D image. If the length of
       * the specified size is greater than the dimension of the image
       * file, an exception will be generated. If the size's length is
       * less than the image's dimension then the missing values are
       * assumed to be zero.
       *
       * When the dimension of the image is reduced, the direction
       * cosine matrix will be set to the identity. However, the
       * spacing for the selected axis will remain. The matrix from
       * the file can still be obtained by
       * ImageFileReader::GetDirection.
       *
       * /sa ExtractImageFilter
       */
      SITK_RETURN_SELF_TYPE_HEADER SetExtractSize( const std::vector<unsigned int> &size);
      const std::vector<unsigned int> &GetExtractSize( ) const;


      /** \brief starting index from the image on disk to extract.
       *
       * Missing dimensions are treated the same as 0.
       *
       * /sa ExtractImageFilter
       */
      SITK_RETURN_SELF_TYPE_HEADER SetExtractIndex( const std::vector<int> &index );
      const std::vector<int> &GetExtractIndex(  ) const;

    protected:

      template <class TImageType> Image ExecuteInternal ( itk::ImageIOBase * );

      /** Internal method which update's this classes stored meta-data
       * and image information.
       */
      void UpdateImageInformationFromImageIO( const itk::ImageIOBase* iobase );

    private:

      // Internal method used implement extracting a region from the reader
      template <class TImageType, class TInternalImageType>
        Image ExecuteExtract( TInternalImageType * itkImage );

      // function pointer type
      typedef Image (Self::*MemberFunctionType)( itk::ImageIOBase * );

      // friend to get access to executeInternal member
      friend struct detail::MemberFunctionAddressor<MemberFunctionType>;
      std::unique_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;


      std::function<std::vector<std::string>()> m_pfGetMetaDataKeys;
      std::function<bool(const std::string &)> m_pfHasMetaDataKey;
      std::function<std::string(const std::string &)> m_pfGetMetaData;

      std::string m_FileName;

      std::unique_ptr<MetaDataDictionary> m_MetaDataDictionary;

      PixelIDValueEnum     m_PixelType;
      unsigned int         m_Dimension;
      unsigned int         m_NumberOfComponents;
      std::vector<double>  m_Direction;
      std::vector<double>  m_Origin;
      std::vector<double>  m_Spacing;

      std::vector<uint64_t> m_Size;

      std::vector<unsigned int> m_ExtractSize;
      std::vector<int>          m_ExtractIndex;
    };

  /**
   * \brief ReadImage is a procedural interface to the ImageFileReader
   *     class which is convenient for most image reading tasks.
   *
   *  \param filename the filename of an Image e.g. "cthead.mha"
   *  \param outputPixelType see ImageReaderBase::SetOutputPixelType
   *  \param imageIO see ImageReaderBase::SetImageIO
   *
   * \sa itk::simple::ImageFileReader for reading a single file.
   * \sa itk::simple::ImageSeriesReader for reading a series and meta-data dictionaries.
   */
  SITKIO_EXPORT Image ReadImage ( const std::string &filename,
                                  PixelIDValueEnum outputPixelType = sitkUnknown,
                                  const std::string &imageIO = "");
  }
}

#endif
