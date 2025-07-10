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
#ifndef sitkImageFileWriter_h
#define sitkImageFileWriter_h

#include "sitkMacro.h"
#include "sitkPathType.h"
#include "sitkImage.h"
#include "sitkMemberFunctionFactory.h"
#include "sitkIO.h"
#include "sitkProcessObject.h"

#include <memory>

namespace itk
{

// Forward declaration for pointer
class ImageIOBase;

template <class T>
class SmartPointer;

namespace simple
{

/** \class ImageFileWriter
 * \brief Write out a SimpleITK image to the specified file location
 *
 * This writer tries to write the image out using the image's type to the
 * location specified in FileName. If writing fails, an ITK exception is
 * thrown.
 *
 * \sa itk::simple::WriteImage for the procedural interface
 */
class SITKIO_EXPORT ImageFileWriter : public ProcessObject
{
public:
  using Self = ImageFileWriter;

  // list of pixel types supported
  using PixelIDTypeList = NonLabelPixelIDTypeList;

  ~ImageFileWriter() override;

  ImageFileWriter();

  /** Print ourselves to string */
  std::string
  ToString() const override;

  /** return user readable name of the filter */
  std::string
  GetName() const override
  {
    return std::string("ImageFileWriter");
  }

  /** \brief Get a vector of the names of registered itk ImageIOs
   */
  virtual std::vector<std::string>
  GetRegisteredImageIOs() const;


  /** \brief Enable compression if available for file type.
   *
   * These methods Set/Get/Toggle the UseCompression flag which
   * gets passed to image file's itk::ImageIO object. This is
   * only a request as not all file formats support compression.
   * @{ */
  void
  SetUseCompression(bool UseCompression);
  bool
  GetUseCompression() const;

  void
  UseCompressionOn()
  {
    return this->SetUseCompression(true);
  }
  void
  UseCompressionOff()
  {
    return this->SetUseCompression(false);
  }
  /** @} */


  /** \brief A hint for the amount of compression to be applied during writing.
   *
   *  After compression is enabled and if the itk::ImageIO support this option, then this value may be used. The range
   * is dependent upon the compression algorithm used. It is generally 0-100 for JPEG like lossy compression and 0-9 for
   * lossless zip or LZW like compression algorithms.  Please see the specific itk::ImageIO for details.
   * @{ */
  void
  SetCompressionLevel(int);
  int
  GetCompressionLevel() const;
  /** @} */

  /** \brief A compression algorithm hint
   *
   * The default is an empty string which enables the default compression of the ImageIO if compression is enabled.
   * If the string identifier is not known a warning is produced and the default compressor is used. Please see the
   * itk::ImageIO for details.
   * @{ */
  void
  SetCompressor(const std::string &);
  std::string
  GetCompressor();
  /** @} */

  /** \brief Set/Get name of ImageIO to use
   *
   * An option to override the automatically detected ImageIO used
   * to write the image. The available ImageIOs are listed by the
   * GetRegisteredImageIOs method. If the ImageIO can not be
   * constructed an exception will be generated.
   *
   * The  default value is an empty string (""). This indicates
   * that the ImageIO will be automatically determined by the ITK
   * ImageIO factory mechanism.
   * @{
   */
  virtual void
  SetImageIO(const std::string & imageio);
  virtual std::string
  GetImageIO() const;
  /* @} */


  /** \brief Use the original study/series/frame of reference.
   *
   * These methods Set/Get/Toggle the KeepOriginalImageUID flag which
   * gets passed to image file's itk::ImageIO object. This is
   * relevant only for the DICOM file format, configuring the writer
   * to use the information in the image's meta-data dictionary or
   * to create new study/series/frame of reference values.
   * @{ */
  void
  SetKeepOriginalImageUID(bool KeepOriginalImageUID);
  bool
  GetKeepOriginalImageUID() const;

  void
  KeepOriginalImageUIDOn()
  {
    return this->SetKeepOriginalImageUID(true);
  }
  void
  KeepOriginalImageUIDOff()
  {
    return this->SetKeepOriginalImageUID(false);
  }
  /** @} */

  void
  SetFileName(const PathType & fileName);
  PathType
  GetFileName() const;

  void
  Execute(const Image &);
  void
  Execute(const Image &, const PathType & inFileName, bool useCompression, int compressionLevel);

private:
  itk::SmartPointer<ImageIOBase>
  GetImageIOBase(const PathType & fileName);

  template <class T>
  void
  ExecuteInternal(const Image &);

  bool        m_UseCompression;
  int         m_CompressionLevel;
  std::string m_Compressor;

  PathType    m_FileName;
  bool        m_KeepOriginalImageUID;
  std::string m_ImageIOName;

  // function pointer type
  typedef void (Self::*MemberFunctionType)(const Image &);

  // friend to get access to executeInternal member
  friend struct detail::MemberFunctionAddressor<MemberFunctionType>;

  detail::MemberFunctionFactory<MemberFunctionType> m_MemberFactory;
};

/**
 * \brief WriteImage is a procedural interface to the ImageFileWriter.
 *     class which is convenient for many image writing tasks.
 *
 *  \param image the input image to be written
 *  \param fileName the filename of an Image e.g. "cthead.mha"
 *  \param useCompression request to compress the written file
 *  \param compressionLevel a hint for the amount of compression to
 *    be applied during writing
 *
 * \sa itk::simple::ImageFileWriter for writing a single file.
 */
SITKIO_EXPORT void
WriteImage(const Image & image, const PathType & fileName, bool useCompression = false, int compressionLevel = -1);
} // namespace simple
} // namespace itk

#endif
