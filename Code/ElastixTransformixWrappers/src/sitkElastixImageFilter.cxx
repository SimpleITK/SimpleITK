#include "sitkElastixImageFilter.h"
#include "sitkElastixImageFilterImpl.h"

namespace itk::simple
{

ElastixImageFilter ::ElastixImageFilter()
  : m_Pimple(std::make_unique<ElastixImageFilterImpl>())
{}

ElastixImageFilter ::~ElastixImageFilter() = default;

std::string
ElastixImageFilter ::GetName() const
{
  return this->m_Pimple->GetName();
}

void
ElastixImageFilter ::SetFixedImage(const Image & fixedImage)
{
  this->m_Pimple->SetFixedImage(fixedImage);
}

void
ElastixImageFilter ::SetFixedImage(const VectorOfImage & fixedImages)
{
  this->m_Pimple->SetFixedImage(fixedImages);
}

void
ElastixImageFilter ::AddFixedImage(const Image & fixedImage)
{
  this->m_Pimple->AddFixedImage(fixedImage);
}

Image &
ElastixImageFilter ::GetFixedImage(const unsigned long index)
{
  return this->m_Pimple->GetFixedImage(index);
}

ElastixImageFilter::VectorOfImage &
ElastixImageFilter ::GetFixedImage()
{
  return this->m_Pimple->GetFixedImage();
}

void
ElastixImageFilter ::RemoveFixedImage(const unsigned long index)
{
  this->m_Pimple->RemoveFixedImage(index);
}

void
ElastixImageFilter ::RemoveFixedImage()
{
  this->m_Pimple->RemoveFixedImage();
}

unsigned int
ElastixImageFilter ::GetNumberOfFixedImages()
{
  return this->m_Pimple->GetNumberOfFixedImages();
}

void
ElastixImageFilter ::SetMovingImage(const Image & movingImage)
{
  this->m_Pimple->SetMovingImage(movingImage);
}

void
ElastixImageFilter ::SetMovingImage(const VectorOfImage & movingImages)
{
  this->m_Pimple->SetMovingImage(movingImages);
}

void
ElastixImageFilter ::AddMovingImage(const Image & movingImage)
{
  this->m_Pimple->AddMovingImage(movingImage);
}

Image &
ElastixImageFilter ::GetMovingImage(const unsigned long index)
{
  return this->m_Pimple->GetMovingImage(index);
}

ElastixImageFilter::VectorOfImage &
ElastixImageFilter ::GetMovingImage()
{
  return this->m_Pimple->GetMovingImage();
}

void
ElastixImageFilter ::RemoveMovingImage(const unsigned long index)
{
  this->m_Pimple->RemoveMovingImage(index);
}

void
ElastixImageFilter ::RemoveMovingImage()
{
  this->m_Pimple->RemoveMovingImage();
}

unsigned int
ElastixImageFilter ::GetNumberOfMovingImages()
{
  return this->m_Pimple->GetNumberOfMovingImages();
}

void
ElastixImageFilter ::SetFixedMask(const Image & fixedMask)
{
  this->m_Pimple->SetFixedMask(fixedMask);
}

void
ElastixImageFilter ::SetFixedMask(const VectorOfImage & fixedMasks)
{
  this->m_Pimple->SetFixedMask(fixedMasks);
}

void
ElastixImageFilter ::AddFixedMask(const Image & fixedMask)
{
  this->m_Pimple->AddFixedMask(fixedMask);
}

Image &
ElastixImageFilter ::GetFixedMask(const unsigned long index)
{
  return this->m_Pimple->GetFixedMask(index);
}

ElastixImageFilter::VectorOfImage &
ElastixImageFilter ::GetFixedMask()
{
  return this->m_Pimple->GetFixedMask();
}

void
ElastixImageFilter ::RemoveFixedMask(const unsigned long index)
{
  this->m_Pimple->RemoveFixedMask(index);
}

void
ElastixImageFilter ::RemoveFixedMask()
{
  this->m_Pimple->RemoveFixedMask();
}

unsigned int
ElastixImageFilter ::GetNumberOfFixedMasks()
{
  return this->m_Pimple->GetNumberOfFixedMasks();
}

void
ElastixImageFilter ::SetMovingMask(const Image & movingMask)
{
  this->m_Pimple->SetMovingMask(movingMask);
}

void
ElastixImageFilter ::SetMovingMask(const VectorOfImage & movingMasks)
{
  this->m_Pimple->SetMovingMask(movingMasks);
}

void
ElastixImageFilter ::AddMovingMask(const Image & movingMask)
{
  this->m_Pimple->AddMovingMask(movingMask);
}

Image &
ElastixImageFilter ::GetMovingMask(const unsigned long index)
{
  return this->m_Pimple->GetMovingMask(index);
}

ElastixImageFilter::VectorOfImage &
ElastixImageFilter ::GetMovingMask()
{
  return this->m_Pimple->GetMovingMask();
}

void
ElastixImageFilter ::RemoveMovingMask(const unsigned long index)
{
  this->m_Pimple->RemoveMovingMask(index);
}

void
ElastixImageFilter ::RemoveMovingMask()
{
  this->m_Pimple->RemoveMovingMask();
}

unsigned int
ElastixImageFilter ::GetNumberOfMovingMasks()
{
  return this->m_Pimple->GetNumberOfMovingMasks();
}

void
ElastixImageFilter ::SetFixedPointSetFileName(const std::string fixedPointSetFileName)
{
  this->m_Pimple->SetFixedPointSetFileName(fixedPointSetFileName);
}

std::string
ElastixImageFilter ::GetFixedPointSetFileName()
{
  return this->m_Pimple->GetFixedPointSetFileName();
}

void
ElastixImageFilter ::RemoveFixedPointSetFileName()
{
  this->m_Pimple->RemoveFixedPointSetFileName();
}

void
ElastixImageFilter ::SetMovingPointSetFileName(const std::string movingPointSetFileName)
{
  this->m_Pimple->SetMovingPointSetFileName(movingPointSetFileName);
}

std::string
ElastixImageFilter ::GetMovingPointSetFileName()
{
  return this->m_Pimple->GetMovingPointSetFileName();
}

void
ElastixImageFilter ::RemoveMovingPointSetFileName()
{
  this->m_Pimple->RemoveMovingImage();
}

void
ElastixImageFilter ::SetOutputDirectory(const std::string outputDirectory)
{
  this->m_Pimple->SetOutputDirectory(outputDirectory);
}

std::string
ElastixImageFilter ::GetOutputDirectory()
{
  return this->m_Pimple->GetOutputDirectory();
}

void
ElastixImageFilter ::RemoveOutputDirectory()
{
  this->m_Pimple->RemoveOutputDirectory();
}

void
ElastixImageFilter ::SetLogFileName(std::string logFileName)
{
  this->m_Pimple->SetLogFileName(logFileName);
}

std::string
ElastixImageFilter ::GetLogFileName()
{
  return this->m_Pimple->GetLogFileName();
}

void
ElastixImageFilter ::RemoveLogFileName()
{
  this->m_Pimple->RemoveLogFileName();
}

void
ElastixImageFilter ::SetLogToFile(bool logToFile)
{
  this->m_Pimple->SetLogToFile(logToFile);
}

bool
ElastixImageFilter ::GetLogToFile()
{
  return this->m_Pimple->GetLogToFile();
}

void
ElastixImageFilter ::LogToFileOn()
{
  this->m_Pimple->LogToFileOn();
}

void
ElastixImageFilter ::LogToFileOff()
{
  this->m_Pimple->LogToFileOff();
}

void
ElastixImageFilter ::SetLogToConsole(bool logToConsole)
{
  this->m_Pimple->SetLogToConsole(logToConsole);
}

bool
ElastixImageFilter ::GetLogToConsole()
{
  return this->m_Pimple->GetLogToConsole();
}

void
ElastixImageFilter ::LogToConsoleOn()
{
  this->m_Pimple->LogToConsoleOn();
}

void
ElastixImageFilter ::LogToConsoleOff()
{
  this->m_Pimple->LogToConsoleOff();
}

void
ElastixImageFilter ::SetNumberOfThreads(int n)
{
  this->m_Pimple->SetNumberOfThreads(n);
}

int
ElastixImageFilter ::GetNumberOfThreads()
{
  return this->m_Pimple->GetNumberOfThreads();
}

void
ElastixImageFilter ::SetParameterMap(const std::string  transformName,
                                     const unsigned int numberOfResolutions,
                                     const double       finalGridSpacingInPhysicalUnits)
{
  this->m_Pimple->SetParameterMap(transformName, numberOfResolutions, finalGridSpacingInPhysicalUnits);
}

void
ElastixImageFilter ::SetParameterMap(const ParameterMapType parameterMap)
{
  this->m_Pimple->SetParameterMap(parameterMap);
}

void
ElastixImageFilter ::SetParameterMap(const ParameterMapVectorType parameterMapVector)
{
  this->m_Pimple->SetParameterMap(parameterMapVector);
}

void
ElastixImageFilter ::AddParameterMap(const ParameterMapType parameterMap)
{
  this->m_Pimple->AddParameterMap(parameterMap);
}

ElastixImageFilter::ParameterMapVectorType
ElastixImageFilter ::GetParameterMap()
{
  return this->m_Pimple->GetParameterMap();
}

unsigned int
ElastixImageFilter ::GetNumberOfParameterMaps()
{
  return this->m_Pimple->GetNumberOfParameterMaps();
}

void
ElastixImageFilter ::SetInitialTransformParameterFileName(const std::string initialTransformParameterFileName)
{
  this->m_Pimple->SetInitialTransformParameterFileName(initialTransformParameterFileName);
}

std::string
ElastixImageFilter ::GetInitialTransformParameterFileName()
{
  return this->m_Pimple->GetInitialTransformParameterFileName();
}

void
ElastixImageFilter ::RemoveInitialTransformParameterFileName()
{
  this->m_Pimple->RemoveInitialTransformParameterFileName();
}

void
ElastixImageFilter ::SetParameter(const ParameterKeyType key, const ParameterValueType value)
{
  this->m_Pimple->SetParameter(key, value);
}

void
ElastixImageFilter ::SetParameter(const ParameterKeyType key, const ParameterValueVectorType value)
{
  this->m_Pimple->SetParameter(key, value);
}

void
ElastixImageFilter ::SetParameter(const unsigned int index, const ParameterKeyType key, const ParameterValueType value)
{
  this->m_Pimple->SetParameter(index, key, value);
}

void
ElastixImageFilter ::SetParameter(const unsigned int             index,
                                  const ParameterKeyType         key,
                                  const ParameterValueVectorType value)
{
  this->m_Pimple->SetParameter(index, key, value);
}

void
ElastixImageFilter ::AddParameter(const ParameterKeyType key, const ParameterValueType value)
{
  this->m_Pimple->AddParameter(key, value);
}

void
ElastixImageFilter ::AddParameter(const ParameterKeyType key, const ParameterValueVectorType value)
{
  this->m_Pimple->AddParameter(key, value);
}

void
ElastixImageFilter ::AddParameter(const unsigned int index, const ParameterKeyType key, const ParameterValueType value)
{
  this->m_Pimple->AddParameter(index, key, value);
}

void
ElastixImageFilter ::AddParameter(const unsigned int             index,
                                  const ParameterKeyType         key,
                                  const ParameterValueVectorType value)
{
  this->m_Pimple->AddParameter(index, key, value);
}

ElastixImageFilter::ParameterValueVectorType
ElastixImageFilter ::GetParameter(const ParameterKeyType key)
{
  return this->m_Pimple->GetParameter(key);
}

ElastixImageFilter::ParameterValueVectorType
ElastixImageFilter ::GetParameter(const unsigned int index, const ParameterKeyType key)
{
  return this->m_Pimple->GetParameter(index, key);
}

void
ElastixImageFilter ::RemoveParameter(const ParameterKeyType key)
{
  this->m_Pimple->RemoveParameter(key);
}

void
ElastixImageFilter ::RemoveParameter(const unsigned int index, const ParameterKeyType key)
{
  this->m_Pimple->RemoveParameter(index, key);
}

ElastixImageFilter::ParameterMapType
ElastixImageFilter ::ReadParameterFile(const std::string fileName)
{
  return this->m_Pimple->ReadParameterFile(fileName);
}

void
ElastixImageFilter ::WriteParameterFile(const ParameterMapType parameterMap, const std::string parameterFileName)
{
  this->m_Pimple->WriteParameterFile(parameterMap, parameterFileName);
}

ElastixImageFilter::ParameterMapType
ElastixImageFilter ::GetDefaultParameterMap(const std::string  transformName,
                                            const unsigned int numberOfResolutions,
                                            const double       finalGridSpacingInPhysicalUnits)
{
  return this->m_Pimple->GetDefaultParameterMap(transformName, numberOfResolutions, finalGridSpacingInPhysicalUnits);
}

Image
ElastixImageFilter ::Execute()
{
  return this->m_Pimple->Execute();
}

ElastixImageFilter::ParameterMapVectorType
ElastixImageFilter ::GetTransformParameterMap()
{
  return this->m_Pimple->GetTransformParameterMap();
}

ElastixImageFilter::ParameterMapType
ElastixImageFilter ::GetTransformParameterMap(const unsigned int index)
{
  return this->m_Pimple->GetTransformParameterMap(index);
}

Image
ElastixImageFilter ::GetResultImage()
{
  return this->m_Pimple->GetResultImage();
}

void
ElastixImageFilter ::PrintParameterMap()
{
  this->m_Pimple->PrintParameterMap();
}

void
ElastixImageFilter ::PrintParameterMap(const ParameterMapType parameterMap)
{
  this->m_Pimple->PrintParameterMap(parameterMap);
}

void
ElastixImageFilter ::PrintParameterMap(const ParameterMapVectorType parameterMapVector)
{
  this->m_Pimple->PrintParameterMap(parameterMapVector);
}

/**
 * Procedural interface
 */

ElastixImageFilter::ParameterMapType
GetDefaultParameterMap(std::string        transform,
                       const unsigned int numberOfResolutions,
                       const double       finalGridSpacingInPhysicalUnits)
{
  ElastixImageFilter                   selx;
  ElastixImageFilter::ParameterMapType parameterMap =
    selx.GetDefaultParameterMap(transform, numberOfResolutions, finalGridSpacingInPhysicalUnits);
  return parameterMap;
}

ElastixImageFilter::ParameterMapType
ReadParameterFile(const std::string fileName)
{
  ElastixImageFilter                   selx;
  ElastixImageFilter::ParameterMapType parameterMap = selx.ReadParameterFile(fileName);
  return parameterMap;
}

void
WriteParameterFile(const ElastixImageFilter::ParameterMapType parameterMap, const std::string filename)
{
  ElastixImageFilter selx;
  selx.WriteParameterFile(parameterMap, filename);
}

void
PrintParameterMap(const ElastixImageFilter::ParameterMapType parameterMap)
{
  ElastixImageFilter::ParameterMapVectorType parameterMapVector =
    ElastixImageFilter::ParameterMapVectorType(1, parameterMap);
  PrintParameterMap(parameterMapVector);
}

void
PrintParameterMap(const ElastixImageFilter::ParameterMapVectorType parameterMapVector)
{
  ElastixImageFilter selx;
  selx.SetParameterMap(parameterMapVector);
  selx.PrintParameterMap();
}

Image
Elastix(const Image &     fixedImage,
        const Image &     movingImage,
        const bool        logToConsole,
        const bool        logToFile,
        const std::string outputDirectory)
{
  ElastixImageFilter selx;
  selx.SetFixedImage(fixedImage);
  selx.SetMovingImage(movingImage);
  selx.SetLogToFile(logToFile);
  selx.SetLogToConsole(logToConsole);
  selx.SetOutputDirectory(outputDirectory);

  return selx.Execute();
}

Image
Elastix(const Image &     fixedImage,
        const Image &     movingImage,
        const Image &     fixedMask,
        const Image &     movingMask,
        const bool        logToConsole,
        const bool        logToFile,
        const std::string outputDirectory)
{
  ElastixImageFilter selx;
  selx.SetFixedImage(fixedImage);
  selx.SetMovingImage(movingImage);
  selx.SetFixedMask(fixedMask);
  selx.SetMovingMask(movingMask);
  selx.SetLogToFile(logToFile);
  selx.SetLogToConsole(logToConsole);
  selx.SetOutputDirectory(outputDirectory);

  return selx.Execute();
}

Image
Elastix(const Image &     fixedImage,
        const Image &     movingImage,
        const std::string defaultParameterMapName,
        const bool        logToConsole,
        const bool        logToFile,
        const std::string outputDirectory)
{
  return Elastix(
    fixedImage, movingImage, GetDefaultParameterMap(defaultParameterMapName), logToConsole, logToFile, outputDirectory);
}

Image
Elastix(const Image &                              fixedImage,
        const Image &                              movingImage,
        const ElastixImageFilter::ParameterMapType parameterMap,
        const bool                                 logToConsole,
        const bool                                 logToFile,
        const std::string                          outputDirectory)
{
  ElastixImageFilter::ParameterMapVectorType parameterMapVector =
    ElastixImageFilter::ParameterMapVectorType(1, parameterMap);
  return Elastix(fixedImage, movingImage, parameterMapVector, logToConsole, logToFile, outputDirectory);
}

Image
Elastix(const Image &                                    fixedImage,
        const Image &                                    movingImage,
        const ElastixImageFilter::ParameterMapVectorType parameterMapVector,
        const bool                                       logToConsole,
        const bool                                       logToFile,
        const std::string                                outputDirectory)
{
  ElastixImageFilter selx;
  selx.SetFixedImage(fixedImage);
  selx.SetMovingImage(movingImage);
  selx.SetParameterMap(parameterMapVector);
  selx.SetLogToFile(logToFile);
  selx.SetLogToConsole(logToConsole);
  selx.SetOutputDirectory(outputDirectory);

  return selx.Execute();
}

Image
Elastix(const Image &     fixedImage,
        const Image &     movingImage,
        const std::string defaultParameterMapName,
        const Image &     fixedMask,
        const Image &     movingMask,
        const bool        logToConsole,
        const bool        logToFile,
        const std::string outputDirectory)
{
  return Elastix(fixedImage,
                 movingImage,
                 GetDefaultParameterMap(defaultParameterMapName),
                 fixedMask,
                 movingMask,
                 logToConsole,
                 logToFile,
                 outputDirectory);
}

Image
Elastix(const Image &                              fixedImage,
        const Image &                              movingImage,
        const ElastixImageFilter::ParameterMapType parameterMap,
        const Image &                              fixedMask,
        const Image &                              movingMask,
        bool                                       logToConsole,
        const bool                                 logToFile,
        std::string                                outputDirectory)
{
  ElastixImageFilter::ParameterMapVectorType parameterMapVector =
    ElastixImageFilter::ParameterMapVectorType(1, parameterMap);
  return Elastix(
    fixedImage, movingImage, parameterMapVector, fixedMask, movingMask, logToConsole, logToFile, outputDirectory);
}

Image
Elastix(const Image &                              fixedImage,
        const Image &                              movingImage,
        ElastixImageFilter::ParameterMapVectorType parameterMapVector,
        const Image &                              fixedMask,
        const Image &                              movingMask,
        bool                                       logToConsole,
        const bool                                 logToFile,
        std::string                                outputDirectory)
{
  ElastixImageFilter selx;
  selx.SetFixedImage(fixedImage);
  selx.SetMovingImage(movingImage);
  selx.SetParameterMap(parameterMapVector);
  selx.SetFixedMask(fixedMask);
  selx.SetMovingMask(movingMask);
  selx.SetLogToFile(logToFile);
  selx.SetLogToConsole(logToConsole);
  selx.SetOutputDirectory(outputDirectory);

  return selx.Execute();
}

} // namespace itk::simple
