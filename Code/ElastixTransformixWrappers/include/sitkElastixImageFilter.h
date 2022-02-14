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
#include <string>
#include <vector>

namespace itk {
  namespace simple {

/** \class ElastixImageFilter
* \brief The class that wraps the elastix registration library.
*/
class SITKElastix_EXPORT ElastixImageFilter
{
public:

  ElastixImageFilter();
  ~ElastixImageFilter();

  typedef ElastixImageFilter Self;

  typedef std::vector< Image >                                    VectorOfImage;

  typedef std::string                                             ParameterKeyType;
  typedef std::string                                             ParameterValueType;
  typedef std::vector< ParameterValueType >                       ParameterValueVectorType;
  typedef ParameterValueVectorType::iterator                      ParameterValueVectorIterator;
  typedef std::map< ParameterKeyType, ParameterValueVectorType >  ParameterMapType;
  typedef std::vector< ParameterMapType >                         ParameterMapVectorType;
  typedef ParameterMapType::iterator                              ParameterMapIterator;
  typedef ParameterMapType::const_iterator                        ParameterMapConstIterator;

  const std::string GetName();

  /** \brief Sets a fixed image.
   *
   * @{
   */
  SITK_RETURN_SELF_TYPE_HEADER SetFixedImage( const Image& fixedImage );
  /**@}*/

  /** \brief Sets multiple fixed images.
   *
   * @{
   */
  SITK_RETURN_SELF_TYPE_HEADER SetFixedImage( const VectorOfImage& fixedImages );
  /**@}*/

  // TODO: Add Doxygen documentation for all methods.
  SITK_RETURN_SELF_TYPE_HEADER AddFixedImage( const Image& fixedImage );


  Image& GetFixedImage( const unsigned long index );
  VectorOfImage& GetFixedImage();
  SITK_RETURN_SELF_TYPE_HEADER RemoveFixedImage( const unsigned long index );
  SITK_RETURN_SELF_TYPE_HEADER RemoveFixedImage();
  unsigned int GetNumberOfFixedImages();

  SITK_RETURN_SELF_TYPE_HEADER SetMovingImage( const Image& movingImages );
  SITK_RETURN_SELF_TYPE_HEADER SetMovingImage( const VectorOfImage& movingImage );
  SITK_RETURN_SELF_TYPE_HEADER AddMovingImage( const Image& movingImage );
  Image& GetMovingImage( const unsigned long index );
  VectorOfImage& GetMovingImage();
  SITK_RETURN_SELF_TYPE_HEADER RemoveMovingImage( const unsigned long index );
  SITK_RETURN_SELF_TYPE_HEADER RemoveMovingImage();
  unsigned int GetNumberOfMovingImages();

  SITK_RETURN_SELF_TYPE_HEADER SetFixedMask( const Image& fixedMask );
  SITK_RETURN_SELF_TYPE_HEADER SetFixedMask( const VectorOfImage& fixedMasks );
  SITK_RETURN_SELF_TYPE_HEADER AddFixedMask( const Image& fixedMask );
  Image& GetFixedMask( const unsigned long index );
  VectorOfImage& GetFixedMask();
  SITK_RETURN_SELF_TYPE_HEADER RemoveFixedMask( const unsigned long index );
  SITK_RETURN_SELF_TYPE_HEADER RemoveFixedMask();
  unsigned int GetNumberOfFixedMasks();

  SITK_RETURN_SELF_TYPE_HEADER SetMovingMask( const Image& movingMask );
  SITK_RETURN_SELF_TYPE_HEADER SetMovingMask( const VectorOfImage& movingMasks );
  SITK_RETURN_SELF_TYPE_HEADER AddMovingMask( const Image& movingMask );
  Image& GetMovingMask( const unsigned long index );
  VectorOfImage& GetMovingMask();
  SITK_RETURN_SELF_TYPE_HEADER RemoveMovingMask( const unsigned long index );
  SITK_RETURN_SELF_TYPE_HEADER RemoveMovingMask();
  unsigned int GetNumberOfMovingMasks();

  SITK_RETURN_SELF_TYPE_HEADER SetFixedPointSetFileName( const std::string movingPointSetFileName );
  std::string GetFixedPointSetFileName();
  SITK_RETURN_SELF_TYPE_HEADER RemoveFixedPointSetFileName();

  SITK_RETURN_SELF_TYPE_HEADER SetMovingPointSetFileName( const std::string movingPointSetFileName );
  std::string GetMovingPointSetFileName();
  SITK_RETURN_SELF_TYPE_HEADER RemoveMovingPointSetFileName();

  SITK_RETURN_SELF_TYPE_HEADER SetOutputDirectory( const std::string outputDirectory );
  std::string GetOutputDirectory();
  SITK_RETURN_SELF_TYPE_HEADER RemoveOutputDirectory();

  SITK_RETURN_SELF_TYPE_HEADER SetLogFileName( const std::string logFileName );
  std::string GetLogFileName();
  SITK_RETURN_SELF_TYPE_HEADER RemoveLogFileName();

  SITK_RETURN_SELF_TYPE_HEADER SetLogToFile( const bool logToFile );
  bool GetLogToFile();
  SITK_RETURN_SELF_TYPE_HEADER LogToFileOn();
  SITK_RETURN_SELF_TYPE_HEADER LogToFileOff();

  SITK_RETURN_SELF_TYPE_HEADER SetLogToConsole( bool );
  bool GetLogToConsole();
  SITK_RETURN_SELF_TYPE_HEADER LogToConsoleOn();
  SITK_RETURN_SELF_TYPE_HEADER LogToConsoleOff();

  SITK_RETURN_SELF_TYPE_HEADER SetNumberOfThreads( int n );
  int GetNumberOfThreads();

  SITK_RETURN_SELF_TYPE_HEADER SetParameterMap( const std::string transformName, const unsigned int numberOfResolutions = 4u, const double finalGridSpacingInPhysicalUnits = 10.0 );
  SITK_RETURN_SELF_TYPE_HEADER SetParameterMap( const std::vector< std::map< std::string, std::vector< std::string > > > parameterMapVector );
  SITK_RETURN_SELF_TYPE_HEADER SetParameterMap( const std::map< std::string, std::vector< std::string > > parameterMap );
  SITK_RETURN_SELF_TYPE_HEADER AddParameterMap( const std::map< std::string, std::vector< std::string > > parameterMap );
  std::vector< std::map< std::string, std::vector< std::string > > > GetParameterMap();
  std::map< std::string, std::vector< std::string > > GetDefaultParameterMap( const std::string transformName, const unsigned int numberOfResolutions = 4, const double finalGridSpacingInPhysicalUnits = 10.0 );
  unsigned int GetNumberOfParameterMaps();

  SITK_RETURN_SELF_TYPE_HEADER SetParameter( const std::string key, const std::string value );
  SITK_RETURN_SELF_TYPE_HEADER SetParameter( const std::string key, const std::vector< std::string > value );
  SITK_RETURN_SELF_TYPE_HEADER SetParameter( const unsigned int index, const std::string key, const std::string value );
  SITK_RETURN_SELF_TYPE_HEADER SetParameter( const unsigned int index, const std::string key, const std::vector< std::string > value );
  SITK_RETURN_SELF_TYPE_HEADER AddParameter( const std::string key, const std::string value );
  SITK_RETURN_SELF_TYPE_HEADER AddParameter( const unsigned int index, const std::string key, const std::string value );
  SITK_RETURN_SELF_TYPE_HEADER AddParameter( const std::string key, const std::vector< std::string > value );
  SITK_RETURN_SELF_TYPE_HEADER AddParameter( const unsigned int index, const std::string key, const std::vector< std::string > value );
  std::vector< std::string > GetParameter( const std::string key );
  std::vector< std::string > GetParameter( const unsigned int index, const std::string key );
  SITK_RETURN_SELF_TYPE_HEADER RemoveParameter( const std::string key );
  SITK_RETURN_SELF_TYPE_HEADER RemoveParameter( const unsigned int index, const std::string key );

  SITK_RETURN_SELF_TYPE_HEADER SetInitialTransformParameterFileName( const std::string initialTransformParmaterFileName );
  std::string GetInitialTransformParameterFileName();
  SITK_RETURN_SELF_TYPE_HEADER RemoveInitialTransformParameterFileName();

  std::map< std::string, std::vector< std::string > > ReadParameterFile( const std::string filename );
  SITK_RETURN_SELF_TYPE_HEADER WriteParameterFile( const std::map< std::string, std::vector< std::string > > parameterMap, const std::string filename );

  Image Execute();
  std::vector< std::map< std::string, std::vector< std::string > > > GetTransformParameterMap();
  std::map< std::string, std::vector< std::string > > GetTransformParameterMap( const unsigned int index );
  Image GetResultImage();

  SITK_RETURN_SELF_TYPE_HEADER PrintParameterMap();
  SITK_RETURN_SELF_TYPE_HEADER PrintParameterMap( const ParameterMapType parameterMapVector );
  SITK_RETURN_SELF_TYPE_HEADER PrintParameterMap( const ParameterMapVectorType parameterMapVector );

private:

  class ElastixImageFilterImpl;
  ElastixImageFilterImpl* m_Pimple;

};

// Procedural Interface
SITKElastix_EXPORT std::map< std::string, std::vector< std::string > > GetDefaultParameterMap( const std::string transform, const unsigned int numberOfResolutions = 4, const double finalGridSpacingInPhysicalUnits = 8.0 );
SITKElastix_EXPORT std::map< std::string, std::vector< std::string > > ReadParameterFile( const std::string filename );
SITKElastix_EXPORT void WriteParameterFile( const std::map< std::string, std::vector< std::string > > parameterMap, const std::string filename );
SITKElastix_EXPORT void PrintParameterMap( const std::map< std::string, std::vector< std::string > > parameterMap );
SITKElastix_EXPORT void PrintParameterMap( const std::vector< std::map< std::string, std::vector< std::string > > > parameterMapVector );
SITKElastix_EXPORT Image Elastix( const Image& fixedImage, const Image& movingImage, const bool logToConsole = false, const bool logToFile = false, const std::string outputDirectory = "." );
SITKElastix_EXPORT Image Elastix( const Image& fixedImage, const Image& movingImage, const Image& fixedMask, const Image& movingMask, const bool logToConsole = false, const bool logToFile = false, const std::string outputDirectory = "." );
SITKElastix_EXPORT Image Elastix( const Image& fixedImage, const Image& movingImage, const std::string defaultParameterMapName, const bool logToConsole = false, const bool logToFile = false, const std::string outputDirectory = "." );
SITKElastix_EXPORT Image Elastix( const Image& fixedImage, const Image& movingImage, const std::map< std::string, std::vector< std::string > > parameterMap, const bool logToConsole = false, const bool logToFile = false, const std::string outputDirectory = "." );
SITKElastix_EXPORT Image Elastix( const Image& fixedImage, const Image& movingImage, const std::vector< std::map< std::string, std::vector< std::string > > > parameterMapVector, const bool logToConsole = false, const bool logToFile = false, const std::string outputDirectory = "." );
SITKElastix_EXPORT Image Elastix( const Image& fixedImage, const Image& movingImage, const std::string defaultParameterMapName, const Image& fixedMask, const Image& movingMask, const bool logToConsole = false, const bool logToFile = false, const std::string outputDirectory = "." );
SITKElastix_EXPORT Image Elastix( const Image& fixedImage, const Image& movingImage, const std::map< std::string, std::vector< std::string > >, const Image& fixedMask, const Image& movingMask, const bool logToConsole = false, const bool logToFile = false, const std::string outputDirectory = "." );
SITKElastix_EXPORT Image Elastix( const Image& fixedImage, const Image& movingImage, std::vector< std::map< std::string, std::vector< std::string > > > parameterMapVector, const Image& fixedMask, const Image& movingMask, const bool logToConsole = false, const bool logToFile = false, const std::string outputDirectory = "." );

} // end namespace simple
} // end namespace itk

#endif // sitkElastixImageFilter_h
