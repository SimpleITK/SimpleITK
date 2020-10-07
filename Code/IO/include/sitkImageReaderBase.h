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
#ifndef sitkImageReaderBase_h
#define sitkImageReaderBase_h

#include "sitkProcessObject.h"
#include "sitkPixelIDValues.h"
#include "sitkIO.h"

namespace itk {

// Forward declaration for pointer
class ImageIOBase;

template<class T>
class SmartPointer;

  namespace simple {

    /** \class ImageReaderBase
     * \brief An abstract base class for image readers
     *
     */
    class SITKIO_EXPORT ImageReaderBase :
      public ProcessObject
    {
    public:
      using Self = ImageReaderBase;

      ~ImageReaderBase() override;

      ImageReaderBase();


      /** \brief Set/Get The output PixelType of the image.
       *
       * By default the value is sitkUnknown, which enable the output
       * pixel type to be same as the file. If the pixel type is
       * specified then the itk::ConvertPixelBuffer will be used to
       * convert the pixels.
       * @{
       */
      SITK_RETURN_SELF_TYPE_HEADER SetOutputPixelType( PixelIDValueEnum pixelID );
      PixelIDValueEnum GetOutputPixelType( ) const;
      /* @} */

      virtual Image Execute() = 0;

      std::string ToString() const override;

      /** \brief Get a vector of the names of registered itk ImageIOs
       */
      virtual std::vector<std::string> GetRegisteredImageIOs() const;

      /** \brief Set/Get loading private DICOM tags into Image's MetaData
       *
       * Unknown private tags may be encoded with Base64 encoding.
       * @{
       */
      virtual SITK_RETURN_SELF_TYPE_HEADER  SetLoadPrivateTags(bool loadPrivateTags);
      virtual bool GetLoadPrivateTags() const;
      virtual void LoadPrivateTagsOn();
      virtual void LoadPrivateTagsOff();
      /* @} */


      /** \brief Set/Get name of ImageIO to use
       *
       * An option to override the automatically detected ImageIO used
       * to read the image. The available ImageIOs are listed by the
       * GetRegisteredImageIOs method. If the ImageIO can not be
       * constructed an exception will be generated. If the ImageIO
       * can not read the file an exception will be generated.
       *
       * The  default value is an empty string (""). This indicates
       * that the ImageIO will be automatically determined by the ITK
       * ImageIO factory mechanism.
       * @{
       */
      virtual SITK_RETURN_SELF_TYPE_HEADER SetImageIO(const std::string &imageio);
      virtual std::string GetImageIO( ) const;
      /* @} */

      /** \brief Get the automatic ImageIO from the ImageIOFactory
       *
       * Returns the name of ImageIO automatically detected to read the
       * file. The file is required to exist, and the file may be opened
       * and/or the file extension examined. If an error is
       * encountered such as the file does not exist, then an empty
       * string ("") will be returned.
       */
      static std::string GetImageIOFromFileName(const std::string &fileName);

    protected:

      itk::SmartPointer<ImageIOBase> GetImageIOBase(const std::string &fileName);

      void GetPixelIDFromImageIO( const std::string &fileName,
                                  PixelIDValueType &outPixelType,
                                  unsigned int & outDimensions );
      void GetPixelIDFromImageIO( const itk::ImageIOBase* iobase,
                                  PixelIDValueType &outPixelType,
                                  unsigned int & outDimensions );

      unsigned int GetDimensionFromImageIO( const std::string &fileName, unsigned int i );
      unsigned int GetDimensionFromImageIO( const itk::ImageIOBase* iobase, unsigned int i );


    private:

      PixelIDValueType ExecuteInternalReadScalar( int componentType );

      PixelIDValueType ExecuteInternalReadVector( int componentType );

      PixelIDValueType ExecuteInternalReadComplex( int componentType );


      PixelIDValueEnum m_OutputPixelType;
      bool             m_LoadPrivateTags;

      std::string      m_ImageIOName;

    };
  }
}


#endif // sitkImageReaderBase_h
