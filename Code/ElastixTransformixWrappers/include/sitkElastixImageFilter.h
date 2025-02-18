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
#ifndef sitkElastixImageFilter_h
#define sitkElastixImageFilter_h

#include "sitkElastixTransformixWrappers.h"
#include "sitkCommon.h"
#include "sitkImage.h"

#include <map>
#include <memory> // For unique_ptr.
#include <string>
#include <vector>

namespace itk::simple
{

/** \class ElastixImageFilter
 * \brief The class that wraps the elastix registration library.
 */
class SITKElastix_EXPORT ElastixImageFilter
{
public:
  /** \brief Default-constructor. */
  ElastixImageFilter();

  /** \brief Destructor. */
  ~ElastixImageFilter();

  typedef ElastixImageFilter Self;

  typedef std::vector<Image> VectorOfImage;

  typedef std::string                                          ParameterKeyType;
  typedef std::string                                          ParameterValueType;
  typedef std::vector<ParameterValueType>                      ParameterValueVectorType;
  typedef ParameterValueVectorType::iterator                   ParameterValueVectorIterator;
  typedef std::map<ParameterKeyType, ParameterValueVectorType> ParameterMapType;
  typedef std::vector<ParameterMapType>                        ParameterMapVectorType;
  typedef ParameterMapType::iterator                           ParameterMapIterator;
  typedef ParameterMapType::const_iterator                     ParameterMapConstIterator;

  std::string
  GetName() const;

  /** \brief Sets a fixed image. Stores the image into the container of fixed images. */
  SITK_RETURN_SELF_TYPE_HEADER
  SetFixedImage(const Image & fixedImage);

  /** \brief Sets multiple fixed images. Stores the images into the container of fixed images. */
  SITK_RETURN_SELF_TYPE_HEADER
  SetFixedImage(const VectorOfImage & fixedImages);

  /** \brief Adds an image to the end of the container of fixed images. */
  SITK_RETURN_SELF_TYPE_HEADER
  AddFixedImage(const Image & fixedImage);

  /** \brief Retrieves a reference to the fixed image at the specified (zero-based) \p index. */
  Image &
  GetFixedImage(const unsigned long index);

  /** \brief Retrieves a reference to the container of fixed images. */
  VectorOfImage &
  GetFixedImage();

  /** \brief Removes an image at the specified (zero-based) \p index from the container of fixed images. */
  SITK_RETURN_SELF_TYPE_HEADER
  RemoveFixedImage(const unsigned long index);

  /** \brief Removes all fixed images. */
  SITK_RETURN_SELF_TYPE_HEADER
  RemoveFixedImage();

  /** \brief Returns the number of fixed images. */
  unsigned int
  GetNumberOfFixedImages();

  /** \brief Sets a moving image. Stores the image into the container of moving images. */
  SITK_RETURN_SELF_TYPE_HEADER
  SetMovingImage(const Image & movingImages);

  /** \brief Sets multiple moving images. Stores the images into the container of moving images. */
  SITK_RETURN_SELF_TYPE_HEADER
  SetMovingImage(const VectorOfImage & movingImage);

  /** \brief Adds an image to the end of the container of moving images. */
  SITK_RETURN_SELF_TYPE_HEADER
  AddMovingImage(const Image & movingImage);

  /** \brief Retrieves a reference to the moving image at the specified (zero-based) \p index. */
  Image &
  GetMovingImage(const unsigned long index);

  /** \brief Retrieves a reference to the moving image at the specified (zero-based) \p index. */
  VectorOfImage &
  GetMovingImage();

  /** \brief Removes an image at the specified (zero-based) \p index from the container of moving images. */
  SITK_RETURN_SELF_TYPE_HEADER
  RemoveMovingImage(const unsigned long index);

  /** \brief Removes all moving images. */
  SITK_RETURN_SELF_TYPE_HEADER
  RemoveMovingImage();

  /** \brief Returns the number of moving images. */
  unsigned int
  GetNumberOfMovingImages();

  /** \brief Sets a fixed mask. Stores the image into the container of fixed masks. */
  SITK_RETURN_SELF_TYPE_HEADER
  SetFixedMask(const Image & fixedMask);

  /** \brief Sets multiple fixed masks. Stores the images into the container of fixed masks. */
  SITK_RETURN_SELF_TYPE_HEADER
  SetFixedMask(const VectorOfImage & fixedMasks);

  /** \brief Adds an image to the end of the container of fixed masks. */
  SITK_RETURN_SELF_TYPE_HEADER
  AddFixedMask(const Image & fixedMask);

  /** \brief Retrieves a reference to the fixed mask at the specified (zero-based) \p index. */
  Image &
  GetFixedMask(const unsigned long index);

  /** \brief Retrieves a reference to the container of fixed masks. */
  VectorOfImage &
  GetFixedMask();

  /** \brief Removes an image at the specified (zero-based) \p index from the container of fixed masks. */
  SITK_RETURN_SELF_TYPE_HEADER
  RemoveFixedMask(const unsigned long index);

  /** \brief Removes all fixed masks. */
  SITK_RETURN_SELF_TYPE_HEADER
  RemoveFixedMask();

  /** \brief Returns the number of fixed masks. */
  unsigned int
  GetNumberOfFixedMasks();

  /** \brief Sets a moving mask. Stores the image into the container of moving masks. */
  SITK_RETURN_SELF_TYPE_HEADER
  SetMovingMask(const Image & movingMask);

  /** \brief Sets multiple moving masks. Stores the images into the container of moving masks. */
  SITK_RETURN_SELF_TYPE_HEADER
  SetMovingMask(const VectorOfImage & movingMasks);

  /** \brief Adds an image to the end of the container of moving masks. */
  SITK_RETURN_SELF_TYPE_HEADER
  AddMovingMask(const Image & movingMask);

  /** \brief Retrieves a reference to the moving mask at the specified (zero-based) \p index. */
  Image &
  GetMovingMask(const unsigned long index);

  /** \brief Retrieves a reference to the container of moving masks. */
  VectorOfImage &
  GetMovingMask();

  /** \brief Removes an image at the specified (zero-based) \p index from the container of moving masks. */
  SITK_RETURN_SELF_TYPE_HEADER
  RemoveMovingMask(const unsigned long index);

  /** \brief Removes all moving masks. */
  SITK_RETURN_SELF_TYPE_HEADER
  RemoveMovingMask();

  /** \brief Returns the number of moving masks. */
  unsigned int
  GetNumberOfMovingMasks();

  /** \brief Specifies a set of points from the fixed image by a point set file, \p fixedPointSetFileName. */
  SITK_RETURN_SELF_TYPE_HEADER
  SetFixedPointSetFileName(const std::string fixedPointSetFileName);

  /** \brief Returns the name of the current point set file of points from the fixed image. */
  std::string
  GetFixedPointSetFileName();

  /** \brief Clears the current point set file name of points from the fixed image. */
  SITK_RETURN_SELF_TYPE_HEADER
  RemoveFixedPointSetFileName();

  /** \brief Specifies a set of points from the moving image by a point set file, \p movingPointSetFileName. */
  SITK_RETURN_SELF_TYPE_HEADER
  SetMovingPointSetFileName(const std::string movingPointSetFileName);

  /** \brief Returns the name of the current point set file of points from the moving image. */
  std::string
  GetMovingPointSetFileName();

  /** \brief Clears the current point set file name of points from the moving image. */
  SITK_RETURN_SELF_TYPE_HEADER
  RemoveMovingPointSetFileName();

  /** \brief Sets the output directory. */
  SITK_RETURN_SELF_TYPE_HEADER
  SetOutputDirectory(const std::string outputDirectory);

  /** \brief Returns the current output directory. */
  std::string
  GetOutputDirectory();

  /** \brief Clears the name of the current output directory. (Does not remove the actual directory.) */
  SITK_RETURN_SELF_TYPE_HEADER
  RemoveOutputDirectory();

  /** \brief Sets the name of the current log file. */
  SITK_RETURN_SELF_TYPE_HEADER
  SetLogFileName(const std::string logFileName);

  /** \brief Returns the name of the current log file. */
  std::string
  GetLogFileName();

  /** \brief Clears the name of the current log file. */
  SITK_RETURN_SELF_TYPE_HEADER
  RemoveLogFileName();

  /** \brief Switches logging to file on (`true`) or off (`false`), as specified by its function argument. */
  SITK_RETURN_SELF_TYPE_HEADER
  SetLogToFile(const bool logToFile);

  /** \brief Returns whether logging to file is switched on. */
  bool
  GetLogToFile();

  /** \brief Switches logging to file on */
  SITK_RETURN_SELF_TYPE_HEADER
  LogToFileOn();

  /** \brief Switches logging to file off. */
  SITK_RETURN_SELF_TYPE_HEADER
  LogToFileOff();

  /** \brief Switches logging to console on (`true`) or off (`false`), as specified by its function argument. */
  SITK_RETURN_SELF_TYPE_HEADER
  SetLogToConsole(bool);

  /** \brief Returns whether logging to console is switched on. */
  bool
  GetLogToConsole();

  /** \brief Switches logging to console on */
  SITK_RETURN_SELF_TYPE_HEADER
  LogToConsoleOn();

  /** \brief Switches logging to console off */
  SITK_RETURN_SELF_TYPE_HEADER
  LogToConsoleOff();

  /** \brief Sets the maximum number of threads to the specified number \p n.
   * \note As a side effect, it may modify the *global* maximum number of threads, as it internally calls ITK's
   * `MultiThreaderBase.SetGlobalMaximumNumberOfThreads`. */
  SITK_RETURN_SELF_TYPE_HEADER
  SetNumberOfThreads(int n);

  /** \brief Returns the current maximum number of threads. */
  int
  GetNumberOfThreads();

  /** \brief Specifies the parameter map by a \p transformName ("translation", "rigid" , "affine", "nonrigid", or
   * "bspline"), and optionally \p numberOfResolutions and \p finalGridSpacingInPhysicalUnits. */
  SITK_RETURN_SELF_TYPE_HEADER
  SetParameterMap(const std::string  transformName,
                  const unsigned int numberOfResolutions = 4u,
                  const double       finalGridSpacingInPhysicalUnits = 10.0);

  /** \brief Specifies multiple parameter maps. */
  SITK_RETURN_SELF_TYPE_HEADER
  SetParameterMap(const std::vector<std::map<std::string, std::vector<std::string>>> parameterMapVector);
  SITK_RETURN_SELF_TYPE_HEADER
  SetParameterMaps(const std::vector<std::map<std::string, std::vector<std::string>>> parameterMapVector)
  {
    return SetParameterMap(parameterMapVector);
  }

  /** \brief Specifies a single parameter map. */
  SITK_RETURN_SELF_TYPE_HEADER
  SetParameterMap(const std::map<std::string, std::vector<std::string>> parameterMap);

  /** \brief Adds a parameter map to the container of parameter maps. */
  SITK_RETURN_SELF_TYPE_HEADER
  AddParameterMap(const std::map<std::string, std::vector<std::string>> parameterMap);

  /** \brief Returns a copy of the parameter maps. */
  std::vector<std::map<std::string, std::vector<std::string>>>
  GetParameterMap();
  std::vector<std::map<std::string, std::vector<std::string>>>
  GetParameterMaps()
  {
    return GetParameterMap();
  };

  /** \brief Returns the default parameter map for the specified function arguments (\p transformName may be
   * "translation", "rigid" , "affine", "nonrigid", or "bspline"). */
  std::map<std::string, std::vector<std::string>>
  GetDefaultParameterMap(const std::string  transformName,
                         const unsigned int numberOfResolutions = 4,
                         const double       finalGridSpacingInPhysicalUnits = 10.0);

  /** \brief Returns the number of parameter maps. */
  unsigned int
  GetNumberOfParameterMaps();

  /** \brief Sets the value of the parameter specified by \p key, in all parameter maps. */
  SITK_RETURN_SELF_TYPE_HEADER
  SetParameter(const std::string key, const std::string value);

  /** \brief Sets the values of the parameter specified by \p key, in all parameter maps. */
  SITK_RETURN_SELF_TYPE_HEADER
  SetParameter(const std::string key, const std::vector<std::string> value);

  /** \brief Sets the value of the parameter specified by \p key, in the parameter map at the specified (zero-based) \p
   * index. */
  SITK_RETURN_SELF_TYPE_HEADER
  SetParameter(const unsigned int index, const std::string key, const std::string value);

  /** \brief Sets the values of the parameter specified by \p key, in the parameter map at the specified (zero-based) \p
   * index. */
  SITK_RETURN_SELF_TYPE_HEADER
  SetParameter(const unsigned int index, const std::string key, const std::vector<std::string> value);

  /** \brief Adds a parameter specified by \p key, with the specified value to all parameter maps. */
  SITK_RETURN_SELF_TYPE_HEADER
  AddParameter(const std::string key, const std::string value);

  /** \brief Adds a parameter specified by \p key, with the specified value to the parameter map at the specified
   * (zero-based) \p index. */
  SITK_RETURN_SELF_TYPE_HEADER
  AddParameter(const unsigned int index, const std::string key, const std::string value);

  /** \brief Adds a parameter specified by \p key, with the specified values to all parameter maps. */
  SITK_RETURN_SELF_TYPE_HEADER
  AddParameter(const std::string key, const std::vector<std::string> value);

  /** \brief Adds a parameter specified by \p key, with the specified values to the parameter map at the specified
   * (zero-based) \p index. */
  SITK_RETURN_SELF_TYPE_HEADER
  AddParameter(const unsigned int index, const std::string key, const std::vector<std::string> value);

  /** \brief Retrieves the values of the parameter specified by \p key, when there is only one parameter map. */
  std::vector<std::string>
  GetParameter(const std::string key);

  /** \brief Retrieves the values of the parameter specified by \p key, from the parameter map at the specified
   * (zero-based) \p index. */
  std::vector<std::string>
  GetParameter(const unsigned int index, const std::string key);

  /** \brief Removes the parameter specified by \p key from all parameter maps. */
  SITK_RETURN_SELF_TYPE_HEADER
  RemoveParameter(const std::string key);

  /** \brief Removes the parameter specified by \p key from the parameter map at the specified (zero-based) \p index. */
  SITK_RETURN_SELF_TYPE_HEADER
  RemoveParameter(const unsigned int index, const std::string key);

  /** \brief Specifies the initial transformation by the specified transform parameter file name. */
  SITK_RETURN_SELF_TYPE_HEADER
  SetInitialTransformParameterFileName(const std::string initialTransformParmaterFileName);

  /** \brief Returns the initial transform parameter file name. */
  std::string
  GetInitialTransformParameterFileName();

  /** \brief Clears the initial transform parameter file name. */
  SITK_RETURN_SELF_TYPE_HEADER
  RemoveInitialTransformParameterFileName();

  /** \brief Reads the parameter file specified by \p filename, and returns its content as a parameter map. */
  std::map<std::string, std::vector<std::string>>
  ReadParameterFile(const std::string filename);

  /** \brief Writes a parameter map to the file, specified by \p filename. */
  SITK_RETURN_SELF_TYPE_HEADER
  WriteParameterFile(const std::map<std::string, std::vector<std::string>> parameterMap, const std::string filename);

  /** \brief Executes the registration, and returns the result image.
   * \note Before executing, the number of moving images must equal the number of fixed images,
   * the number of fixed masks must be either zero, or one, or equal to the number of fixed images,
   * and the number of moving masks must be either zero, or one, or equal to the number of moving images
   */
  Image
  Execute();

  /** \brief Returns all transform parameter maps. */
  std::vector<std::map<std::string, std::vector<std::string>>>
  GetTransformParameterMap();

  /** \brief Returns the transform parameter map at the specified (zero-based) \p index. */
  std::map<std::string, std::vector<std::string>>
  GetTransformParameterMap(const unsigned int index);

  /** \brief Returns the result image. */
  Image
  GetResultImage();

  /** \brief Prints all parameter maps to standard output. */
  SITK_RETURN_SELF_TYPE_HEADER
  PrintParameterMap();

  /** \brief Prints the specified parameter map to standard output. */
  SITK_RETURN_SELF_TYPE_HEADER
  PrintParameterMap(const ParameterMapType parameterMapVector);

  /** \brief Prints the specified parameter maps to standard output. */
  SITK_RETURN_SELF_TYPE_HEADER
  PrintParameterMap(const ParameterMapVectorType parameterMapVector);

private:
  class ElastixImageFilterImpl;
  const std::unique_ptr<ElastixImageFilterImpl> m_Pimple;
};

// Procedural Interface
SITKElastix_EXPORT std::map<std::string, std::vector<std::string>>
                   GetDefaultParameterMap(const std::string  transform,
                                          const unsigned int numberOfResolutions = 4,
                                          const double       finalGridSpacingInPhysicalUnits = 8.0);
SITKElastix_EXPORT std::map<std::string, std::vector<std::string>>
                   ReadParameterFile(const std::string filename);
SITKElastix_EXPORT void
WriteParameterFile(const std::map<std::string, std::vector<std::string>> parameterMap, const std::string filename);
SITKElastix_EXPORT void
PrintParameterMap(const std::map<std::string, std::vector<std::string>> parameterMap);
SITKElastix_EXPORT void
PrintParameterMap(const std::vector<std::map<std::string, std::vector<std::string>>> parameterMapVector);
SITKElastix_EXPORT Image
Elastix(const Image &     fixedImage,
        const Image &     movingImage,
        const bool        logToConsole = false,
        const bool        logToFile = false,
        const std::string outputDirectory = ".");
SITKElastix_EXPORT Image
Elastix(const Image &     fixedImage,
        const Image &     movingImage,
        const Image &     fixedMask,
        const Image &     movingMask,
        const bool        logToConsole = false,
        const bool        logToFile = false,
        const std::string outputDirectory = ".");
SITKElastix_EXPORT Image
Elastix(const Image &     fixedImage,
        const Image &     movingImage,
        const std::string defaultParameterMapName,
        const bool        logToConsole = false,
        const bool        logToFile = false,
        const std::string outputDirectory = ".");
SITKElastix_EXPORT Image
Elastix(const Image &                                         fixedImage,
        const Image &                                         movingImage,
        const std::map<std::string, std::vector<std::string>> parameterMap,
        const bool                                            logToConsole = false,
        const bool                                            logToFile = false,
        const std::string                                     outputDirectory = ".");
SITKElastix_EXPORT Image
Elastix(const Image &                                                      fixedImage,
        const Image &                                                      movingImage,
        const std::vector<std::map<std::string, std::vector<std::string>>> parameterMapVector,
        const bool                                                         logToConsole = false,
        const bool                                                         logToFile = false,
        const std::string                                                  outputDirectory = ".");
SITKElastix_EXPORT Image
Elastix(const Image &     fixedImage,
        const Image &     movingImage,
        const std::string defaultParameterMapName,
        const Image &     fixedMask,
        const Image &     movingMask,
        const bool        logToConsole = false,
        const bool        logToFile = false,
        const std::string outputDirectory = ".");
SITKElastix_EXPORT Image
Elastix(const Image & fixedImage,
        const Image & movingImage,
        const std::map<std::string, std::vector<std::string>>,
        const Image &     fixedMask,
        const Image &     movingMask,
        const bool        logToConsole = false,
        const bool        logToFile = false,
        const std::string outputDirectory = ".");
SITKElastix_EXPORT Image
Elastix(const Image &                                                fixedImage,
        const Image &                                                movingImage,
        std::vector<std::map<std::string, std::vector<std::string>>> parameterMapVector,
        const Image &                                                fixedMask,
        const Image &                                                movingMask,
        const bool                                                   logToConsole = false,
        const bool                                                   logToFile = false,
        const std::string                                            outputDirectory = ".");

} // namespace itk::simple

#endif // sitkElastixImageFilter_h
