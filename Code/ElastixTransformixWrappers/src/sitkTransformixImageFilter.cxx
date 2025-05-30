#include "sitkTransformixImageFilter.h"
#include "sitkTransformixImageFilterImpl.h"

namespace itk::simple
{

TransformixImageFilter ::TransformixImageFilter()
  : m_Pimple(std::make_unique<TransformixImageFilterImpl>())
{}

TransformixImageFilter ::~TransformixImageFilter() = default;

std::string
TransformixImageFilter ::GetName() const
{
  return this->m_Pimple->GetName();
}

void
TransformixImageFilter ::SetMovingImage(const Image & movingImage)
{
  this->m_Pimple->SetMovingImage(movingImage);
}

Image &
TransformixImageFilter ::GetMovingImage()
{
  return this->m_Pimple->GetMovingImage();
}

void
TransformixImageFilter ::RemoveMovingImage()
{
  this->m_Pimple->RemoveMovingImage();
}

void
TransformixImageFilter ::SetFixedPointSetFileName(const std::string movingPointSetFileName)
{
  this->m_Pimple->SetFixedPointSetFileName(movingPointSetFileName);
}

std::string
TransformixImageFilter ::GetFixedPointSetFileName()
{
  return this->m_Pimple->GetFixedPointSetFileName();
}

void
TransformixImageFilter ::RemoveFixedPointSetFileName()
{
  this->m_Pimple->RemoveFixedPointSetFileName();
}

void
TransformixImageFilter ::SetComputeSpatialJacobian(const bool computeSpatialJacobian)
{
  this->m_Pimple->SetComputeSpatialJacobian(computeSpatialJacobian);
}

bool
TransformixImageFilter ::GetComputeSpatialJacobian()
{
  return this->m_Pimple->GetComputeSpatialJacobian();
}

void
TransformixImageFilter ::ComputeSpatialJacobianOn()
{
  this->m_Pimple->SetComputeSpatialJacobian(true);
}

void
TransformixImageFilter ::ComputeSpatialJacobianOff()
{
  this->m_Pimple->SetComputeSpatialJacobian(false);
}

void
TransformixImageFilter ::SetComputeDeterminantOfSpatialJacobian(const bool computeDeterminantOfSpatialJacobian)
{
  this->m_Pimple->SetComputeDeterminantOfSpatialJacobian(computeDeterminantOfSpatialJacobian);
}

bool
TransformixImageFilter ::GetComputeDeterminantOfSpatialJacobian()
{
  return this->m_Pimple->GetComputeDeterminantOfSpatialJacobian();
}

void
TransformixImageFilter ::ComputeDeterminantOfSpatialJacobianOn()
{
  this->m_Pimple->SetComputeDeterminantOfSpatialJacobian(true);
}

void
TransformixImageFilter ::ComputeDeterminantOfSpatialJacobianOff()
{
  this->m_Pimple->SetComputeDeterminantOfSpatialJacobian(false);
}

void
TransformixImageFilter ::SetComputeDeformationField(const bool computeDeformationField)
{
  this->m_Pimple->SetComputeDeformationField(computeDeformationField);
}

bool
TransformixImageFilter ::GetComputeDeformationField()
{
  return this->m_Pimple->GetComputeDeformationField();
}

void
TransformixImageFilter ::ComputeDeformationFieldOn()
{
  this->m_Pimple->SetComputeDeformationField(true);
}

void
TransformixImageFilter ::ComputeDeformationFieldOff()
{
  this->m_Pimple->SetComputeDeformationField(false);
}

void
TransformixImageFilter ::SetOutputDirectory(const std::string outputDirectory)
{
  this->m_Pimple->SetOutputDirectory(outputDirectory);
}

std::string
TransformixImageFilter ::GetOutputDirectory()
{
  return this->m_Pimple->GetOutputDirectory();
}

void
TransformixImageFilter ::RemoveOutputDirectory()
{
  this->m_Pimple->RemoveOutputDirectory();
}

void
TransformixImageFilter ::SetLogFileName(std::string logFileName)
{
  this->m_Pimple->SetLogFileName(logFileName);
}

std::string
TransformixImageFilter ::GetLogFileName()
{
  return this->m_Pimple->GetLogFileName();
}

void
TransformixImageFilter ::RemoveLogFileName()
{
  this->m_Pimple->RemoveLogFileName();
}

void
TransformixImageFilter ::SetLogToFile(bool logToFile)
{
  this->m_Pimple->SetLogToFile(logToFile);
}

bool
TransformixImageFilter ::GetLogToFile()
{
  return this->m_Pimple->GetLogToFile();
}

void
TransformixImageFilter ::LogToFileOn()
{
  this->m_Pimple->SetLogToFile(true);
}

void
TransformixImageFilter ::LogToFileOff()
{
  this->m_Pimple->SetLogToFile(false);
}

void
TransformixImageFilter ::SetLogToConsole(bool logToConsole)
{
  this->m_Pimple->SetLogToConsole(logToConsole);
}

bool
TransformixImageFilter ::GetLogToConsole()
{
  return this->m_Pimple->GetLogToConsole();
}

void
TransformixImageFilter ::LogToConsoleOn()
{
  this->m_Pimple->SetLogToConsole(true);
}

void
TransformixImageFilter ::LogToConsoleOff()
{
  this->m_Pimple->SetLogToConsole(false);
}

void
TransformixImageFilter ::SetTransformParameterMap(const ParameterMapVectorType transformParameterMapVector)
{
  this->m_Pimple->SetTransformParameterMap(transformParameterMapVector);
}

void
TransformixImageFilter ::SetTransformParameterMap(const ParameterMapType transformParameterMap)
{
  this->m_Pimple->SetTransformParameterMap(transformParameterMap);
}

void
TransformixImageFilter ::AddTransformParameterMap(const ParameterMapType transformParameterMap)
{
  this->m_Pimple->AddTransformParameterMap(transformParameterMap);
}

TransformixImageFilter::ParameterMapVectorType
TransformixImageFilter ::GetTransformParameterMap()
{
  return this->m_Pimple->GetTransformParameterMap();
}

unsigned int
TransformixImageFilter ::GetNumberOfTransformParameterMaps()
{
  return this->m_Pimple->GetNumberOfTransformParameterMaps();
}

void
TransformixImageFilter ::SetTransformParameter(const ParameterKeyType key, const ParameterValueType value)
{
  this->m_Pimple->SetTransformParameter(key, value);
}

void
TransformixImageFilter ::SetTransformParameter(const ParameterKeyType key, const ParameterValueVectorType value)
{
  this->m_Pimple->SetTransformParameter(key, value);
}

void
TransformixImageFilter ::SetTransformParameter(const unsigned int       index,
                                               const ParameterKeyType   key,
                                               const ParameterValueType value)
{
  this->m_Pimple->SetTransformParameter(index, key, value);
}

void
TransformixImageFilter ::SetTransformParameter(const unsigned int             index,
                                               const ParameterKeyType         key,
                                               const ParameterValueVectorType value)
{
  this->m_Pimple->SetTransformParameter(index, key, value);
}

void
TransformixImageFilter ::AddTransformParameter(const ParameterKeyType key, const ParameterValueType value)
{
  this->m_Pimple->AddTransformParameter(key, value);
}

void
TransformixImageFilter ::AddTransformParameter(const unsigned int       index,
                                               const ParameterKeyType   key,
                                               const ParameterValueType value)
{
  this->m_Pimple->AddTransformParameter(index, key, value);
}

TransformixImageFilter::ParameterValueVectorType
TransformixImageFilter ::GetTransformParameter(const ParameterKeyType key)
{
  return this->m_Pimple->GetTransformParameter(key);
}

TransformixImageFilter::ParameterValueVectorType
TransformixImageFilter ::GetTransformParameter(const unsigned int index, const ParameterKeyType key)
{
  return this->m_Pimple->GetTransformParameter(index, key);
}

void
TransformixImageFilter ::RemoveTransformParameter(const ParameterKeyType key)
{
  this->m_Pimple->RemoveTransformParameter(key);
}

void
TransformixImageFilter ::RemoveTransformParameter(const unsigned int index, const ParameterKeyType key)
{
  this->m_Pimple->RemoveTransformParameter(index, key);
}

TransformixImageFilter::ParameterMapType
TransformixImageFilter ::ReadParameterFile(const std::string parameterFileName)
{
  return this->m_Pimple->ReadParameterFile(parameterFileName);
}

void
TransformixImageFilter ::WriteParameterFile(const ParameterMapType parameterMap, const std::string parameterFileName)
{
  this->m_Pimple->WriteParameterFile(parameterMap, parameterFileName);
}

void
TransformixImageFilter ::PrintParameterMap()
{
  this->m_Pimple->PrintParameterMap();
}

void
TransformixImageFilter ::PrintParameterMap(const ParameterMapType parameterMap)
{
  this->m_Pimple->PrintParameterMap(parameterMap);
}

void
TransformixImageFilter ::PrintParameterMap(const ParameterMapVectorType parameterMapVector)
{
  this->m_Pimple->PrintParameterMap(parameterMapVector);
}

Image
TransformixImageFilter ::Execute()
{
  return this->m_Pimple->Execute();
}

Image
TransformixImageFilter ::GetResultImage()
{
  return this->m_Pimple->GetResultImage();
}

Image
TransformixImageFilter ::GetDeformationField()
{
  return this->m_Pimple->GetDeformationField();
}

/**
 * Procedural interface
 */

Image
Transformix(const Image &                                  movingImage,
            const TransformixImageFilter::ParameterMapType parameterMap,
            const bool                                     logToConsole,
            const std::string                              outputDirectory)
{
  TransformixImageFilter::ParameterMapVectorType parameterMapVector;
  parameterMapVector.push_back(parameterMap);
  return Transformix(movingImage, parameterMapVector, logToConsole, outputDirectory);
}

Image
Transformix(const Image &                                        movingImage,
            const TransformixImageFilter::ParameterMapVectorType parameterMapVector,
            const bool                                           logToConsole,
            const std::string                                    outputDirectory)
{
  TransformixImageFilter stfx;
  stfx.SetMovingImage(movingImage);
  stfx.SetTransformParameterMap(parameterMapVector);
  stfx.SetOutputDirectory(outputDirectory);
  stfx.LogToFileOn();
  stfx.SetLogToConsole(logToConsole);

  return stfx.Execute();
}

} // namespace itk::simple
