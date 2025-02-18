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

ElastixImageFilter::Self &
ElastixImageFilter ::SetFixedImage(const Image & fixedImage)
{
  this->m_Pimple->SetFixedImage(fixedImage);
  return *this;
}

ElastixImageFilter::Self &
ElastixImageFilter ::SetFixedImage(const VectorOfImage & fixedImages)
{
  this->m_Pimple->SetFixedImage(fixedImages);
  return *this;
}

ElastixImageFilter::Self &
ElastixImageFilter ::AddFixedImage(const Image & fixedImage)
{
  this->m_Pimple->AddFixedImage(fixedImage);
  return *this;
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

ElastixImageFilter::Self &
ElastixImageFilter ::RemoveFixedImage(const unsigned long index)
{
  this->m_Pimple->RemoveFixedImage(index);
  return *this;
}

ElastixImageFilter::Self &
ElastixImageFilter ::RemoveFixedImage()
{
  this->m_Pimple->RemoveFixedImage();
  return *this;
}

unsigned int
ElastixImageFilter ::GetNumberOfFixedImages()
{
  return this->m_Pimple->GetNumberOfFixedImages();
}

ElastixImageFilter::Self &
ElastixImageFilter ::SetMovingImage(const Image & movingImage)
{
  this->m_Pimple->SetMovingImage(movingImage);
  return *this;
}

ElastixImageFilter::Self &
ElastixImageFilter ::SetMovingImage(const VectorOfImage & movingImages)
{
  this->m_Pimple->SetMovingImage(movingImages);
  return *this;
}

ElastixImageFilter::Self &
ElastixImageFilter ::AddMovingImage(const Image & movingImage)
{
  this->m_Pimple->AddMovingImage(movingImage);
  return *this;
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

ElastixImageFilter::Self &
ElastixImageFilter ::RemoveMovingImage(const unsigned long index)
{
  this->m_Pimple->RemoveMovingImage(index);
  return *this;
}

ElastixImageFilter::Self &
ElastixImageFilter ::RemoveMovingImage()
{
  this->m_Pimple->RemoveMovingImage();
  return *this;
}

unsigned int
ElastixImageFilter ::GetNumberOfMovingImages()
{
  return this->m_Pimple->GetNumberOfMovingImages();
}

ElastixImageFilter::Self &
ElastixImageFilter ::SetFixedMask(const Image & fixedMask)
{
  this->m_Pimple->SetFixedMask(fixedMask);
  return *this;
}

ElastixImageFilter::Self &
ElastixImageFilter ::SetFixedMask(const VectorOfImage & fixedMasks)
{
  this->m_Pimple->SetFixedMask(fixedMasks);
  return *this;
}

ElastixImageFilter::Self &
ElastixImageFilter ::AddFixedMask(const Image & fixedMask)
{
  this->m_Pimple->AddFixedMask(fixedMask);
  return *this;
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

ElastixImageFilter::Self &
ElastixImageFilter ::RemoveFixedMask(const unsigned long index)
{
  this->m_Pimple->RemoveFixedMask(index);
  return *this;
}

ElastixImageFilter::Self &
ElastixImageFilter ::RemoveFixedMask()
{
  this->m_Pimple->RemoveFixedMask();
  return *this;
}

unsigned int
ElastixImageFilter ::GetNumberOfFixedMasks()
{
  return this->m_Pimple->GetNumberOfFixedMasks();
}

ElastixImageFilter::Self &
ElastixImageFilter ::SetMovingMask(const Image & movingMask)
{
  this->m_Pimple->SetMovingMask(movingMask);
  return *this;
}

ElastixImageFilter::Self &
ElastixImageFilter ::SetMovingMask(const VectorOfImage & movingMasks)
{
  this->m_Pimple->SetMovingMask(movingMasks);
  return *this;
}

ElastixImageFilter::Self &
ElastixImageFilter ::AddMovingMask(const Image & movingMask)
{
  this->m_Pimple->AddMovingMask(movingMask);
  return *this;
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

ElastixImageFilter::Self &
ElastixImageFilter ::RemoveMovingMask(const unsigned long index)
{
  this->m_Pimple->RemoveMovingMask(index);
  return *this;
}

ElastixImageFilter::Self &
ElastixImageFilter ::RemoveMovingMask()
{
  this->m_Pimple->RemoveMovingMask();
  return *this;
}

unsigned int
ElastixImageFilter ::GetNumberOfMovingMasks()
{
  return this->m_Pimple->GetNumberOfMovingMasks();
}

ElastixImageFilter::Self &
ElastixImageFilter ::SetFixedPointSetFileName(const std::string fixedPointSetFileName)
{
  this->m_Pimple->SetFixedPointSetFileName(fixedPointSetFileName);
  return *this;
}

std::string
ElastixImageFilter ::GetFixedPointSetFileName()
{
  return this->m_Pimple->GetFixedPointSetFileName();
}

ElastixImageFilter::Self &
ElastixImageFilter ::RemoveFixedPointSetFileName()
{
  this->m_Pimple->RemoveFixedPointSetFileName();
  return *this;
}

ElastixImageFilter::Self &
ElastixImageFilter ::SetMovingPointSetFileName(const std::string movingPointSetFileName)
{
  this->m_Pimple->SetMovingPointSetFileName(movingPointSetFileName);
  return *this;
}

std::string
ElastixImageFilter ::GetMovingPointSetFileName()
{
  return this->m_Pimple->GetMovingPointSetFileName();
}

ElastixImageFilter::Self &
ElastixImageFilter ::RemoveMovingPointSetFileName()
{
  this->m_Pimple->RemoveMovingImage();
  return *this;
}

ElastixImageFilter::Self &
ElastixImageFilter ::SetOutputDirectory(const std::string outputDirectory)
{
  this->m_Pimple->SetOutputDirectory(outputDirectory);
  return *this;
}

std::string
ElastixImageFilter ::GetOutputDirectory()
{
  return this->m_Pimple->GetOutputDirectory();
}

ElastixImageFilter::Self &
ElastixImageFilter ::RemoveOutputDirectory()
{
  this->m_Pimple->RemoveOutputDirectory();
  return *this;
}

ElastixImageFilter::Self &
ElastixImageFilter ::SetLogFileName(std::string logFileName)
{
  this->m_Pimple->SetLogFileName(logFileName);
  return *this;
}

std::string
ElastixImageFilter ::GetLogFileName()
{
  return this->m_Pimple->GetLogFileName();
}

ElastixImageFilter::Self &
ElastixImageFilter ::RemoveLogFileName()
{
  this->m_Pimple->RemoveLogFileName();
  return *this;
}

ElastixImageFilter::Self &
ElastixImageFilter ::SetLogToFile(bool logToFile)
{
  this->m_Pimple->SetLogToFile(logToFile);
  return *this;
}

bool
ElastixImageFilter ::GetLogToFile()
{
  return this->m_Pimple->GetLogToFile();
}

ElastixImageFilter::Self &
ElastixImageFilter ::LogToFileOn()
{
  this->m_Pimple->LogToFileOn();
  return *this;
}

ElastixImageFilter::Self &
ElastixImageFilter ::LogToFileOff()
{
  this->m_Pimple->LogToFileOff();
  return *this;
}

ElastixImageFilter::Self &
ElastixImageFilter ::SetLogToConsole(bool logToConsole)
{
  this->m_Pimple->SetLogToConsole(logToConsole);
  return *this;
}

bool
ElastixImageFilter ::GetLogToConsole()
{
  return this->m_Pimple->GetLogToConsole();
}

ElastixImageFilter::Self &
ElastixImageFilter ::LogToConsoleOn()
{
  this->m_Pimple->LogToConsoleOn();
  return *this;
}

ElastixImageFilter::Self &
ElastixImageFilter ::LogToConsoleOff()
{
  this->m_Pimple->LogToConsoleOff();
  return *this;
}

ElastixImageFilter::Self &
ElastixImageFilter ::SetNumberOfThreads(int n)
{
  this->m_Pimple->SetNumberOfThreads(n);
  return *this;
}

int
ElastixImageFilter ::GetNumberOfThreads()
{
  return this->m_Pimple->GetNumberOfThreads();
}

ElastixImageFilter::Self &
ElastixImageFilter ::SetParameterMap(const std::string  transformName,
                                     const unsigned int numberOfResolutions,
                                     const double       finalGridSpacingInPhysicalUnits)
{
  this->m_Pimple->SetParameterMap(transformName, numberOfResolutions, finalGridSpacingInPhysicalUnits);
  return *this;
}

ElastixImageFilter::Self &
ElastixImageFilter ::SetParameterMap(const ParameterMapType parameterMap)
{
  this->m_Pimple->SetParameterMap(parameterMap);
  return *this;
}

ElastixImageFilter::Self &
ElastixImageFilter ::SetParameterMap(const ParameterMapVectorType parameterMapVector)
{
  this->m_Pimple->SetParameterMap(parameterMapVector);
  return *this;
}

ElastixImageFilter::Self &
ElastixImageFilter ::AddParameterMap(const ParameterMapType parameterMap)
{
  this->m_Pimple->AddParameterMap(parameterMap);
  return *this;
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

ElastixImageFilter::Self &
ElastixImageFilter ::SetInitialTransformParameterFileName(const std::string initialTransformParameterFileName)
{
  this->m_Pimple->SetInitialTransformParameterFileName(initialTransformParameterFileName);
  return *this;
}

std::string
ElastixImageFilter ::GetInitialTransformParameterFileName()
{
  return this->m_Pimple->GetInitialTransformParameterFileName();
}

ElastixImageFilter::Self &
ElastixImageFilter ::RemoveInitialTransformParameterFileName()
{
  this->m_Pimple->RemoveInitialTransformParameterFileName();
  return *this;
}

ElastixImageFilter::Self &
ElastixImageFilter ::SetParameter(const ParameterKeyType key, const ParameterValueType value)
{
  this->m_Pimple->SetParameter(key, value);
  return *this;
}

ElastixImageFilter::Self &
ElastixImageFilter ::SetParameter(const ParameterKeyType key, const ParameterValueVectorType value)
{
  this->m_Pimple->SetParameter(key, value);
  return *this;
}

ElastixImageFilter::Self &
ElastixImageFilter ::SetParameter(const unsigned int index, const ParameterKeyType key, const ParameterValueType value)
{
  this->m_Pimple->SetParameter(index, key, value);
  return *this;
}

ElastixImageFilter::Self &
ElastixImageFilter ::SetParameter(const unsigned int             index,
                                  const ParameterKeyType         key,
                                  const ParameterValueVectorType value)
{
  this->m_Pimple->SetParameter(index, key, value);
  return *this;
}

ElastixImageFilter::Self &
ElastixImageFilter ::AddParameter(const ParameterKeyType key, const ParameterValueType value)
{
  this->m_Pimple->AddParameter(key, value);
  return *this;
}

ElastixImageFilter::Self &
ElastixImageFilter ::AddParameter(const ParameterKeyType key, const ParameterValueVectorType value)
{
  this->m_Pimple->AddParameter(key, value);
  return *this;
}

ElastixImageFilter::Self &
ElastixImageFilter ::AddParameter(const unsigned int index, const ParameterKeyType key, const ParameterValueType value)
{
  this->m_Pimple->AddParameter(index, key, value);
  return *this;
}

ElastixImageFilter::Self &
ElastixImageFilter ::AddParameter(const unsigned int             index,
                                  const ParameterKeyType         key,
                                  const ParameterValueVectorType value)
{
  this->m_Pimple->AddParameter(index, key, value);
  return *this;
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

ElastixImageFilter::Self &
ElastixImageFilter ::RemoveParameter(const ParameterKeyType key)
{
  this->m_Pimple->RemoveParameter(key);
  return *this;
}

ElastixImageFilter::Self &
ElastixImageFilter ::RemoveParameter(const unsigned int index, const ParameterKeyType key)
{
  this->m_Pimple->RemoveParameter(index, key);
  return *this;
}

ElastixImageFilter::ParameterMapType
ElastixImageFilter ::ReadParameterFile(const std::string fileName)
{
  return this->m_Pimple->ReadParameterFile(fileName);
}

ElastixImageFilter::Self &
ElastixImageFilter ::WriteParameterFile(const ParameterMapType parameterMap, const std::string parameterFileName)
{
  this->m_Pimple->WriteParameterFile(parameterMap, parameterFileName);
  return *this;
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

ElastixImageFilter::Self &
ElastixImageFilter ::PrintParameterMap()
{
  this->m_Pimple->PrintParameterMap();
  return *this;
}

ElastixImageFilter::Self &
ElastixImageFilter ::PrintParameterMap(const ParameterMapType parameterMap)
{
  this->m_Pimple->PrintParameterMap(parameterMap);
  return *this;
}

ElastixImageFilter::Self &
ElastixImageFilter ::PrintParameterMap(const ParameterMapVectorType parameterMapVector)
{
  this->m_Pimple->PrintParameterMap(parameterMapVector);
  return *this;
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
