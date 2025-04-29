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

  void
  SetMovingImage(const Image & movingImage);
  Image &
  GetMovingImage();
  void
  RemoveMovingImage();

  void
  SetFixedPointSetFileName(const std::string movingPointSetFileName);
  std::string
  GetFixedPointSetFileName();
  void
  RemoveFixedPointSetFileName();

  void
  SetComputeSpatialJacobian(const bool);
  bool
  GetComputeSpatialJacobian();
  void
  ComputeSpatialJacobianOn();
  void
  ComputeSpatialJacobianOff();

  void
  SetComputeDeterminantOfSpatialJacobian(const bool);
  bool
  GetComputeDeterminantOfSpatialJacobian();
  void
  ComputeDeterminantOfSpatialJacobianOn();
  void
  ComputeDeterminantOfSpatialJacobianOff();

  void
  SetComputeDeformationField(bool);
  bool
  GetComputeDeformationField();
  void
  ComputeDeformationFieldOn();
  void
  ComputeDeformationFieldOff();

  void
  SetOutputDirectory(const std::string outputDirectory);
  std::string
  GetOutputDirectory();
  void
  RemoveOutputDirectory();

  void
  SetLogFileName(const std::string logFileName);
  std::string
  GetLogFileName();
  void
  RemoveLogFileName();

  void
  SetLogToFile(const bool logToFile);
  bool
  GetLogToFile();
  void
  LogToFileOn();
  void
  LogToFileOff();

  void
  SetLogToConsole(const bool logToConsole);
  bool
  GetLogToConsole();
  void
  LogToConsoleOn();
  void
  LogToConsoleOff();

  void
  SetTransformParameterMap(const std::vector<std::map<std::string, std::vector<std::string>>> parameterMapVector);
  void
  SetTransformParameterMaps(const std::vector<std::map<std::string, std::vector<std::string>>> parameterMapVector)
  {
    return SetTransformParameterMap(parameterMapVector);
  }
  void
  SetTransformParameterMap(const std::map<std::string, std::vector<std::string>> parameterMap);
  void
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

  void
  SetTransformParameter(const std::string key, const std::string value);
  void
  SetTransformParameter(const std::string key, const std::vector<std::string> value);
  void
  SetTransformParameter(const unsigned int index, const std::string key, const std::string value);
  void
  SetTransformParameter(const unsigned int index, const std::string key, const std::vector<std::string> value);
  void
  AddTransformParameter(const std::string key, const std::string value);
  void
  AddTransformParameter(const unsigned int index, const std::string key, const std::string value);
  std::vector<std::string>
  GetTransformParameter(const std::string key);
  std::vector<std::string>
  GetTransformParameter(const unsigned int index, const std::string key);
  void
  RemoveTransformParameter(const std::string key);
  void
  RemoveTransformParameter(const unsigned int index, const std::string key);

  std::map<std::string, std::vector<std::string>>
  ReadParameterFile(const std::string parameterFileName);
  void
  WriteParameterFile(const std::map<std::string, std::vector<std::string>> parameterMap,
                     const std::string                                     parameterFileName);

  void
  PrintParameterMap();
  void
  PrintParameterMap(const std::map<std::string, std::vector<std::string>> parameterMap);
  void
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
