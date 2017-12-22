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
     * with the ReadImageInformation method.
     *
     * \sa itk::simple::ReadImage for the procedural interface
     */
    class SITKIO_EXPORT ImageFileReader
      : public ImageReaderBase
    {
    public:
      typedef ImageFileReader Self;

      /** Print ourselves to string */
      virtual std::string ToString() const;

      /** return user readable name of the filter */
      virtual std::string GetName() const { return std::string("ImageFileReader"); }

      SITK_RETURN_SELF_TYPE_HEADER SetFileName ( const std::string &fn );
      std::string GetFileName() const;

      Image Execute();

      ImageFileReader();

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
      void ReadImageInformation(void);

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
      PixelIDValueEnum GetPixelID( void ) const;
      PixelIDValueType GetPixelIDValue( void ) const;
      unsigned int GetDimension( void ) const;
      unsigned int GetNumberOfComponents( void ) const;
      const std::vector<double> &GetOrigin( void ) const;
      const std::vector<double> &GetSpacing( void ) const;
      const std::vector<double> &GetDirection() const;
      const std::vector<uint64_t> &GetSize( void ) const;
      /* @} */

      /** \brief Get the meta-data dictionary keys
       *
       * This is only valid after successful ReadImageInformation or Execute
       * of this filter.
       *
       * Returns a vector of keys to the key/value entries in the
       * file's meta-data dictionary. Iterate through with these keys
       * to get the values.
       **/
      std::vector<std::string> GetMetaDataKeys( void ) const;

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

    protected:

      template <class TImageType> Image ExecuteInternal ( itk::ImageIOBase * );

      /** Internal method which update's this classes stored meta-data
       * and image information.
       */
      void UpdateImageInformationFromImageIO( const itk::ImageIOBase* iobase );

    private:

      // function pointer type
      typedef Image (Self::*MemberFunctionType)( itk::ImageIOBase * );

      // friend to get access to executeInternal member
      friend struct detail::MemberFunctionAddressor<MemberFunctionType>;
      nsstd::auto_ptr<detail::MemberFunctionFactory<MemberFunctionType> > m_MemberFactory;


      nsstd::function<std::vector<std::string>()> m_pfGetMetaDataKeys;
      nsstd::function<bool(const std::string &)> m_pfHasMetaDataKey;
      nsstd::function<std::string(const std::string &)> m_pfGetMetaData;

      std::string m_FileName;

      nsstd::auto_ptr<MetaDataDictionary> m_MetaDataDictionary;

      PixelIDValueEnum     m_PixelType;
      unsigned int         m_Dimension;
      unsigned int         m_NumberOfComponents;
      std::vector<double>  m_Direction;
      std::vector<double>  m_Origin;
      std::vector<double>  m_Spacing;

      std::vector<uint64_t> m_Size;
    };

  /**
   * \brief ReadImage is a procedural interface to the ImageFileReader
   *     class which is convenient for most image reading tasks.
   *
   *     For more complicated use cases such as requiring loading of
   *     all tags, including private ones, from a DICOM file the
   *     object oriented interface should be used. The reader can be explicitly
   *     set to load all tags (LoadPrivateTagsOn()).
   */
  SITKIO_EXPORT Image ReadImage ( const std::string &filename, PixelIDValueEnum outputPixelType = sitkUnknown );
  }
}

#endif
