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
#ifndef sitkTransformixImageFilter_h
#define sitkTransformixImageFilter_h

#include "sitkElastixTransformixWrappers.h"
#include "sitkCommon.h"
#include "sitkImage.h"

#include <map>
#include <memory> // For unique_ptr.
#include <string>
#include <vector>

namespace itk::simple
{

class SITKElastix_EXPORT TransformixImageFilter
{
public:
  TransformixImageFilter();
  ~TransformixImageFilter();

  typedef TransformixImageFilter Self;

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

  SITK_RETURN_SELF_TYPE_HEADER
  SetMovingImage(const Image & movingImage);
  Image &
  GetMovingImage();
  SITK_RETURN_SELF_TYPE_HEADER
  RemoveMovingImage();

  SITK_RETURN_SELF_TYPE_HEADER
  SetFixedPointSetFileName(const std::string movingPointSetFileName);
  std::string
  GetFixedPointSetFileName();
  SITK_RETURN_SELF_TYPE_HEADER
  RemoveFixedPointSetFileName();

  SITK_RETURN_SELF_TYPE_HEADER
  SetComputeSpatialJacobian(const bool);
  bool
  GetComputeSpatialJacobian();
  SITK_RETURN_SELF_TYPE_HEADER
  ComputeSpatialJacobianOn();
  SITK_RETURN_SELF_TYPE_HEADER
  ComputeSpatialJacobianOff();

  SITK_RETURN_SELF_TYPE_HEADER
  SetComputeDeterminantOfSpatialJacobian(const bool);
  bool
  GetComputeDeterminantOfSpatialJacobian();
  SITK_RETURN_SELF_TYPE_HEADER
  ComputeDeterminantOfSpatialJacobianOn();
  SITK_RETURN_SELF_TYPE_HEADER
  ComputeDeterminantOfSpatialJacobianOff();

  SITK_RETURN_SELF_TYPE_HEADER
  SetComputeDeformationField(bool);
  bool
  GetComputeDeformationField();
  SITK_RETURN_SELF_TYPE_HEADER
  ComputeDeformationFieldOn();
  SITK_RETURN_SELF_TYPE_HEADER
  ComputeDeformationFieldOff();

  SITK_RETURN_SELF_TYPE_HEADER
  SetOutputDirectory(const std::string outputDirectory);
  std::string
  GetOutputDirectory();
  SITK_RETURN_SELF_TYPE_HEADER
  RemoveOutputDirectory();

  SITK_RETURN_SELF_TYPE_HEADER
  SetLogFileName(const std::string logFileName);
  std::string
  GetLogFileName();
  SITK_RETURN_SELF_TYPE_HEADER
  RemoveLogFileName();

  SITK_RETURN_SELF_TYPE_HEADER
  SetLogToFile(const bool logToFile);
  bool
  GetLogToFile();
  SITK_RETURN_SELF_TYPE_HEADER
  LogToFileOn();
  SITK_RETURN_SELF_TYPE_HEADER
  LogToFileOff();

  SITK_RETURN_SELF_TYPE_HEADER
  SetLogToConsole(const bool logToConsole);
  bool
  GetLogToConsole();
  SITK_RETURN_SELF_TYPE_HEADER
  LogToConsoleOn();
  SITK_RETURN_SELF_TYPE_HEADER
  LogToConsoleOff();

  SITK_RETURN_SELF_TYPE_HEADER
  SetTransformParameterMap(const std::vector<std::map<std::string, std::vector<std::string>>> parameterMapVector);
  SITK_RETURN_SELF_TYPE_HEADER
  SetTransformParameterMaps(const std::vector<std::map<std::string, std::vector<std::string>>> parameterMapVector)
  {
    return SetTransformParameterMap(parameterMapVector);
  }
  SITK_RETURN_SELF_TYPE_HEADER
  SetTransformParameterMap(const std::map<std::string, std::vector<std::string>> parameterMap);
  SITK_RETURN_SELF_TYPE_HEADER
  AddTransformParameterMap(const std::map<std::string, std::vector<std::string>> parameterMap);
  std::vector<std::map<std::string, std::vector<std::string>>>
  GetTransformParameterMap();
  std::vector<std::map<std::string, std::vector<std::string>>>
  GetTransformParameterMaps()
  {
    return GetTransformParameterMap();
  }
  unsigned int
  GetNumberOfTransformParameterMaps();

  SITK_RETURN_SELF_TYPE_HEADER
  SetTransformParameter(const std::string key, const std::string value);
  SITK_RETURN_SELF_TYPE_HEADER
  SetTransformParameter(const std::string key, const std::vector<std::string> value);
  SITK_RETURN_SELF_TYPE_HEADER
  SetTransformParameter(const unsigned int index, const std::string key, const std::string value);
  SITK_RETURN_SELF_TYPE_HEADER
  SetTransformParameter(const unsigned int index, const std::string key, const std::vector<std::string> value);
  SITK_RETURN_SELF_TYPE_HEADER
  AddTransformParameter(const std::string key, const std::string value);
  SITK_RETURN_SELF_TYPE_HEADER
  AddTransformParameter(const unsigned int index, const std::string key, const std::string value);
  std::vector<std::string>
  GetTransformParameter(const std::string key);
  std::vector<std::string>
  GetTransformParameter(const unsigned int index, const std::string key);
  SITK_RETURN_SELF_TYPE_HEADER
  RemoveTransformParameter(const std::string key);
  SITK_RETURN_SELF_TYPE_HEADER
  RemoveTransformParameter(const unsigned int index, const std::string key);

  std::map<std::string, std::vector<std::string>>
  ReadParameterFile(const std::string parameterFileName);
  SITK_RETURN_SELF_TYPE_HEADER
  WriteParameterFile(const std::map<std::string, std::vector<std::string>> parameterMap,
                     const std::string                                     parameterFileName);

  SITK_RETURN_SELF_TYPE_HEADER
  PrintParameterMap();
  SITK_RETURN_SELF_TYPE_HEADER
  PrintParameterMap(const std::map<std::string, std::vector<std::string>> parameterMap);
  SITK_RETURN_SELF_TYPE_HEADER
  PrintParameterMap(const std::vector<std::map<std::string, std::vector<std::string>>> parameterMapVector);

  Image
  Execute();

  Image
  GetResultImage();
  Image
  GetDeformationField();

private:
  class TransformixImageFilterImpl;
  const std::unique_ptr<TransformixImageFilterImpl> m_Pimple;
};

// Procedural Interface
SITKElastix_EXPORT Image
Transformix(const Image &                                         movingImage,
            const std::map<std::string, std::vector<std::string>> parameterMap,
            const bool                                            logToConsole = false,
            const std::string                                     outputDirectory = ".");
SITKElastix_EXPORT Image
Transformix(const Image &                                                      movingImage,
            const std::vector<std::map<std::string, std::vector<std::string>>> parameterMapVector,
            const bool                                                         logToConsole = false,
            const std::string                                                  outputDirectory = ".");

} // namespace itk::simple

#endif // sitkTransformixImageFilter_h
