#include <memory>

#include "sitkTransformixImageFilter.h"
#include "sitkTransformixImageFilterImpl.h"
#include "sitkCastImageFilter.h"
#include "sitkImageConvert.h"
#include "sitkInternalUtilities.h"
#include "sitkImageConvert.hxx"

namespace itk::simple
{

namespace
{
const std::string
GetPixelIDValueAsElastixParameter(PixelIDValueType type)
{

  if (type == sitkUnknown)
  {
    // Unknown must be first because other enums may be -1 if they are
    // not instantiated
    return "Unknown pixel id";
  }
  else if (type == sitkUInt8)
  {
    return "unsigned char";
  }
  else if (type == sitkInt8)
  {
    return "char";
  }
  else if (type == sitkUInt16)
  {
    return "unsigned short";
  }
  else if (type == sitkInt16)
  {
    return "short";
  }
  else if (type == sitkUInt32)
  {
    return "unsigned int";
  }
  else if (type == sitkInt32)
  {
    return "int";
  }
  else if (type == sitkUInt64)
  {
    return "unsigned long";
  }
  else if (type == sitkInt64)
  {
    return "long";
  }
  else if (type == sitkFloat32)
  {
    return "float";
  }
  else if (type == sitkFloat64)
  {
    return "double";
  }
  else
  {
    return "Unsupported pixel type.";
  }
}


PixelIDValueType
GetPixelIDValueFromElastixString(const std::string & enumString)
{

  if (enumString == "sitkUnknown")
  {
    // Unknown must be first because other enums may be -1 if they are
    // not instantiated
    return sitkUnknown;
  }
  else if (enumString == "unsigned char")
  {
    return sitkUInt8;
  }
  else if (enumString == "char")
  {
    return sitkInt8;
  }
  else if (enumString == "unsigned short")
  {
    return sitkUInt16;
  }
  else if (enumString == "short")
  {
    return sitkInt16;
  }
  else if (enumString == "unsigned int")
  {
    return sitkUInt32;
  }
  else if (enumString == "int")
  {
    return sitkInt32;
  }
  else if (enumString == "float")
  {
    return sitkFloat32;
  }
  else if (enumString == "double")
  {
    return sitkFloat64;
  }
  else
  {
    return -99;
  }
}

} // namespace

TransformixImageFilter::TransformixImageFilterImpl ::TransformixImageFilterImpl()
{
  // Register this class with SimpleITK
  this->m_MemberFactory = std::make_unique<detail::MemberFunctionFactory<MemberFunctionType>>(this);
  this->m_MemberFactory->RegisterMemberFunctions<FloatPixelIDTypeList, 2>();
  this->m_MemberFactory->RegisterMemberFunctions<FloatPixelIDTypeList, 3>();

#if SITK_MAX_DIMENSION >= 4
  m_MemberFactory->RegisterMemberFunctions<FloatPixelIDTypeList, 4>();
#endif

  this->m_MovingImage = Image();
  this->m_ResultImage = Image();
  this->m_DeformationField = Image();

  this->m_TransformParameterMapVector = ParameterMapVectorType();

  this->m_ComputeSpatialJacobian = false;
  this->m_ComputeDeterminantOfSpatialJacobian = false;
  this->m_ComputeDeformationField = false;
  this->m_MovingPointSetFileName = "";

  this->m_OutputDirectory = ".";
  this->m_LogFileName = "";

  this->m_LogToFile = false;
  this->m_LogToConsole = true;
}

TransformixImageFilter::TransformixImageFilterImpl ::~TransformixImageFilterImpl() {}

Image
TransformixImageFilter::TransformixImageFilterImpl ::Execute()
{
  const PixelIDValueEnum MovingImagePixelEnum = this->m_MovingImage.GetPixelID();
  const unsigned int     MovingImageDimension = this->m_MovingImage.GetDimension();

  if (this->m_MemberFactory->HasMemberFunction(sitkFloat32, MovingImageDimension))
  {
    return this->m_MemberFactory->GetMemberFunction(sitkFloat32, MovingImageDimension)();
  }

  sitkExceptionMacro(<< "TransformixImageFilter does not support the combination of image type "
                     << GetPixelIDValueAsElastixParameter(MovingImagePixelEnum) << " and dimension "
                     << MovingImageDimension << ". This a serious error. "
                     << "Contact developers at https://github.com/kaspermarstal/SimpleElastix/issues.");
}

template <typename TMovingImage>
Image
TransformixImageFilter::TransformixImageFilterImpl ::ExecuteInternal()
{
  typedef itk::TransformixFilter<TMovingImage>    TransformixFilterType;
  typedef typename TransformixFilterType::Pointer TransforimxFilterPointer;

  using MovingImageType = typename TransformixFilterType::InputImageType;

  typename MovingImageType::Pointer result;

  try
  {
    TransforimxFilterPointer transformixFilter = TransformixFilterType::New();

    if (!this->IsEmpty(this->m_MovingImage))
    {
      transformixFilter->SetMovingImage(itkDynamicCastInDebugMode<TMovingImage *>(
        Cast(this->GetMovingImage(), static_cast<PixelIDValueEnum>(GetPixelIDValueFromElastixString("float")))
          .GetITKBase()));
    }

    transformixFilter->SetFixedPointSetFileName(this->GetFixedPointSetFileName());
    transformixFilter->SetComputeSpatialJacobian(this->GetComputeSpatialJacobian());
    transformixFilter->SetComputeDeterminantOfSpatialJacobian(this->GetComputeDeterminantOfSpatialJacobian());
    transformixFilter->SetComputeDeformationField(this->GetComputeDeformationField());

    transformixFilter->SetOutputDirectory(this->GetOutputDirectory());
    transformixFilter->SetLogFileName(this->GetLogFileName());
    transformixFilter->SetLogToFile(this->GetLogToFile());
    transformixFilter->SetLogToConsole(this->GetLogToConsole());

    ParameterMapVectorType transformParameterMapVector = this->m_TransformParameterMapVector;
    for (unsigned int i = 0; i < transformParameterMapVector.size(); i++)
    {
      transformParameterMapVector[i]["FixedInternalImagePixelType"] = ParameterValueVectorType(1, "float");
      transformParameterMapVector[i]["MovingInternalImagePixelType"] = ParameterValueVectorType(1, "float");
    }

    ParameterObjectPointer parameterObject = ParameterObjectType::New();
    parameterObject->SetParameterMaps(transformParameterMapVector);
    transformixFilter->SetTransformParameterObject(parameterObject);
    transformixFilter->Update();

    if (!this->IsEmpty(this->GetMovingImage()))
    {
      result = transformixFilter->GetOutput();
    }

    if (this->GetComputeDeformationField())
    {
      this->m_DeformationField =
        Image(itk::simple::GetVectorImageFromImage(transformixFilter->GetOutputDeformationField(), true));
      this->m_DeformationField.MakeUnique();
    }
  }
  catch (itk::ExceptionObject & e)
  {
    sitkExceptionMacro(<< e);
  }

  this->m_ResultImage = itk::simple::Image(result);

  return this->m_ResultImage;
}

std::string
TransformixImageFilter::TransformixImageFilterImpl ::GetName() const
{
  const std::string name = std::string("TransformixImageFilter");
  return name;
}

void
TransformixImageFilter::TransformixImageFilterImpl ::SetMovingImage(const Image & movingImage)
{
  this->m_MovingImage = movingImage;
}

Image &
TransformixImageFilter::TransformixImageFilterImpl ::GetMovingImage()
{
  return this->m_MovingImage;
}

void
TransformixImageFilter::TransformixImageFilterImpl ::RemoveMovingImage()
{
  this->SetMovingImage(Image());
}

void
TransformixImageFilter::TransformixImageFilterImpl ::SetFixedPointSetFileName(const std::string movingPointSetFileName)
{
  this->m_MovingPointSetFileName = movingPointSetFileName;
}

std::string
TransformixImageFilter::TransformixImageFilterImpl ::GetFixedPointSetFileName()
{
  return this->m_MovingPointSetFileName;
}

void
TransformixImageFilter::TransformixImageFilterImpl ::RemoveFixedPointSetFileName()
{
  this->m_MovingPointSetFileName = std::string();
}

void
TransformixImageFilter::TransformixImageFilterImpl ::SetComputeSpatialJacobian(const bool computeSpatialJacobian)
{
  this->m_ComputeSpatialJacobian = computeSpatialJacobian;
}

bool
TransformixImageFilter::TransformixImageFilterImpl ::GetComputeSpatialJacobian()
{
  return this->m_ComputeSpatialJacobian;
}

void
TransformixImageFilter::TransformixImageFilterImpl ::ComputeSpatialJacobianOn()
{
  this->SetComputeSpatialJacobian(true);
}

void
TransformixImageFilter::TransformixImageFilterImpl ::ComputeSpatialJacobianOff()
{
  this->SetComputeSpatialJacobian(false);
}

void
TransformixImageFilter::TransformixImageFilterImpl ::SetComputeDeterminantOfSpatialJacobian(
  const bool computeDeterminantOfSpatialJacobian)
{
  this->m_ComputeDeterminantOfSpatialJacobian = computeDeterminantOfSpatialJacobian;
}

bool
TransformixImageFilter::TransformixImageFilterImpl ::GetComputeDeterminantOfSpatialJacobian()
{
  return this->m_ComputeDeterminantOfSpatialJacobian;
}

void
TransformixImageFilter::TransformixImageFilterImpl ::ComputeDeterminantOfSpatialJacobianOn()
{
  this->SetComputeDeterminantOfSpatialJacobian(true);
}

void
TransformixImageFilter::TransformixImageFilterImpl ::ComputeDeterminantOfSpatialJacobianOff()
{
  this->SetComputeDeterminantOfSpatialJacobian(false);
}

void
TransformixImageFilter::TransformixImageFilterImpl ::SetComputeDeformationField(const bool computeDeformationField)
{
  this->m_ComputeDeformationField = computeDeformationField;
}

bool
TransformixImageFilter::TransformixImageFilterImpl ::GetComputeDeformationField()
{
  return this->m_ComputeDeformationField;
}

void
TransformixImageFilter::TransformixImageFilterImpl ::ComputeDeformationFieldOn()
{
  this->SetComputeDeformationField(true);
}

void
TransformixImageFilter::TransformixImageFilterImpl ::ComputeDeformationFieldOff()
{
  this->SetComputeDeformationField(false);
}

void
TransformixImageFilter::TransformixImageFilterImpl ::SetOutputDirectory(const std::string outputDirectory)
{
  this->m_OutputDirectory = outputDirectory;
}

std::string
TransformixImageFilter::TransformixImageFilterImpl ::GetOutputDirectory()
{
  return this->m_OutputDirectory;
}

void
TransformixImageFilter::TransformixImageFilterImpl ::RemoveOutputDirectory()
{
  this->m_OutputDirectory = std::string();
}

void
TransformixImageFilter::TransformixImageFilterImpl ::SetLogFileName(std::string logFileName)
{
  this->m_LogFileName = logFileName;
}

std::string
TransformixImageFilter::TransformixImageFilterImpl ::GetLogFileName()
{
  return this->m_LogFileName;
}

void
TransformixImageFilter::TransformixImageFilterImpl ::RemoveLogFileName()
{
  this->m_LogFileName = std::string();
}

void
TransformixImageFilter::TransformixImageFilterImpl ::SetLogToFile(bool logToFile)
{
  this->m_LogToFile = logToFile;
}

bool
TransformixImageFilter::TransformixImageFilterImpl ::GetLogToFile()
{
  return this->m_LogToFile;
}

void
TransformixImageFilter::TransformixImageFilterImpl ::LogToFileOn()
{
  this->SetLogToFile(true);
}

void
TransformixImageFilter::TransformixImageFilterImpl ::LogToFileOff()
{
  this->SetLogToFile(false);
}

void
TransformixImageFilter::TransformixImageFilterImpl ::SetLogToConsole(bool logToConsole)
{
  this->m_LogToConsole = logToConsole;
}

bool
TransformixImageFilter::TransformixImageFilterImpl ::GetLogToConsole()
{
  return this->m_LogToConsole;
}

void
TransformixImageFilter::TransformixImageFilterImpl ::LogToConsoleOn()
{
  this->SetLogToConsole(true);
}

void
TransformixImageFilter::TransformixImageFilterImpl ::LogToConsoleOff()
{
  this->SetLogToConsole(false);
}

void
TransformixImageFilter::TransformixImageFilterImpl ::SetTransformParameterMap(
  const ParameterMapVectorType parameterMapVector)
{
  this->m_TransformParameterMapVector = parameterMapVector;
}

void
TransformixImageFilter::TransformixImageFilterImpl ::SetTransformParameterMap(const ParameterMapType parameterMap)
{
  ParameterMapVectorType parameterMapVector;
  parameterMapVector.push_back(parameterMap);
  this->SetTransformParameterMap(parameterMapVector);
}

void
TransformixImageFilter::TransformixImageFilterImpl ::AddTransformParameterMap(const ParameterMapType parameterMap)
{
  this->m_TransformParameterMapVector.push_back(parameterMap);
}

TransformixImageFilter::TransformixImageFilterImpl::ParameterMapVectorType
TransformixImageFilter::TransformixImageFilterImpl ::GetTransformParameterMap()
{
  return this->m_TransformParameterMapVector;
}

unsigned int
TransformixImageFilter::TransformixImageFilterImpl ::GetNumberOfTransformParameterMaps()
{
  return this->m_TransformParameterMapVector.size();
}

void
TransformixImageFilter::TransformixImageFilterImpl ::SetTransformParameter(const ParameterKeyType   key,
                                                                           const ParameterValueType value)
{
  for (unsigned int i = 0; i < this->m_TransformParameterMapVector.size(); i++)
  {
    this->SetTransformParameter(i, key, value);
  }
}

void
TransformixImageFilter::TransformixImageFilterImpl ::SetTransformParameter(const ParameterKeyType         key,
                                                                           const ParameterValueVectorType value)
{
  for (unsigned int i = 0; i < this->m_TransformParameterMapVector.size(); i++)
  {
    this->SetTransformParameter(i, key, value);
  }
}

void
TransformixImageFilter::TransformixImageFilterImpl ::SetTransformParameter(const unsigned int       index,
                                                                           const ParameterKeyType   key,
                                                                           const ParameterValueType value)
{
  if (index >= this->m_TransformParameterMapVector.size())
  {
    sitkExceptionMacro("Parameter map index is out of range (index: "
                       << index << "; number of transform parameters maps: "
                       << this->m_TransformParameterMapVector.size() << "). Note that indexes are zero-based.");
  }

  this->m_TransformParameterMapVector[index][key] = ParameterValueVectorType(1, value);
}

void
TransformixImageFilter::TransformixImageFilterImpl ::SetTransformParameter(const unsigned int             index,
                                                                           const ParameterKeyType         key,
                                                                           const ParameterValueVectorType value)
{
  if (index >= this->m_TransformParameterMapVector.size())
  {
    sitkExceptionMacro("Parameter map index is out of range (index: "
                       << index << ", number of transform parameters maps: "
                       << this->m_TransformParameterMapVector.size() << "). Note that indexes are zero-based.");
  }

  this->m_TransformParameterMapVector[index][key] = value;
}

void
TransformixImageFilter::TransformixImageFilterImpl ::AddTransformParameter(const ParameterKeyType   key,
                                                                           const ParameterValueType value)
{
  for (unsigned int i = 0; i < this->m_TransformParameterMapVector.size(); i++)
  {
    this->AddTransformParameter(i, key, value);
  }
}

void
TransformixImageFilter::TransformixImageFilterImpl ::AddTransformParameter(const unsigned int       index,
                                                                           const ParameterKeyType   key,
                                                                           const ParameterValueType value)
{
  if (index >= this->m_TransformParameterMapVector.size())
  {
    sitkExceptionMacro("Parameter map index is out of range (index: "
                       << index << ", number of transform parameters maps: "
                       << this->m_TransformParameterMapVector.size() << "). Note that indexes are zero-based.");
  }

  if (this->m_TransformParameterMapVector[index].find(key) == this->m_TransformParameterMapVector[index].end())
  {
    this->SetTransformParameter(index, key, value);
  }
  else
  {
    this->m_TransformParameterMapVector[index][key].push_back(value);
  }
}

TransformixImageFilter::TransformixImageFilterImpl::ParameterValueVectorType
TransformixImageFilter::TransformixImageFilterImpl ::GetTransformParameter(const ParameterKeyType key)
{
  if (this->m_TransformParameterMapVector.size() > 0)
  {
    sitkExceptionMacro("An index is needed when more than one transform parameter map is present. Please specify the "
                       "parameter map number as the first argument.");
  }

  return this->GetTransformParameter(0, key);
}

TransformixImageFilter::TransformixImageFilterImpl::ParameterValueVectorType
TransformixImageFilter::TransformixImageFilterImpl ::GetTransformParameter(const unsigned int     index,
                                                                           const ParameterKeyType key)
{
  if (index >= this->m_TransformParameterMapVector.size())
  {
    sitkExceptionMacro("Parameter map index is out of range (index: "
                       << index << ", number of transform parameters maps: "
                       << this->m_TransformParameterMapVector.size() << "). Note that indexes are zero-based.");
  }

  return this->m_TransformParameterMapVector[index][key];
}

void
TransformixImageFilter::TransformixImageFilterImpl ::RemoveTransformParameter(const ParameterKeyType key)
{
  for (unsigned int i = 0; i < this->m_TransformParameterMapVector.size(); i++)
  {
    this->RemoveTransformParameter(i, key);
  }
}

void
TransformixImageFilter::TransformixImageFilterImpl ::RemoveTransformParameter(const unsigned int     index,
                                                                              const ParameterKeyType key)
{
  if (index >= this->m_TransformParameterMapVector.size())
  {
    sitkExceptionMacro("Parameter map index is out of range (index: "
                       << index << ", number of transform parameters maps: "
                       << this->m_TransformParameterMapVector.size() << "). Note that indexes are zero-based.");
  }

  this->m_TransformParameterMapVector[index].erase(key);
}

TransformixImageFilter::TransformixImageFilterImpl::ParameterMapType
TransformixImageFilter::TransformixImageFilterImpl ::ReadParameterFile(const std::string filename)
{
  ParameterFileParserPointer parser = ParameterFileParserType::New();
  parser->SetParameterFileName(filename);
  try
  {
    parser->ReadParameterFile();
  }
  catch (itk::ExceptionObject & e)
  {
    std::cout << e.what() << std::endl;
  }

  return parser->GetParameterMap();
}

void
TransformixImageFilter::TransformixImageFilterImpl ::WriteParameterFile(const ParameterMapType parameterMap,
                                                                        const std::string      parameterFileName)
{
  ParameterObjectPointer parameterObject = ParameterObjectType::New();
  parameterObject->WriteParameterFile(parameterMap, parameterFileName);
}

void
TransformixImageFilter::TransformixImageFilterImpl ::PrintParameterMap()
{
  this->PrintParameterMap(this->GetTransformParameterMap());
}

void
TransformixImageFilter::TransformixImageFilterImpl ::PrintParameterMap(const ParameterMapType parameterMap)
{
  ParameterMapVectorType parameterMapVector = ParameterMapVectorType(1);
  parameterMapVector[0] = parameterMap;
  this->PrintParameterMap(parameterMapVector);
}

void
TransformixImageFilter::TransformixImageFilterImpl ::PrintParameterMap(const ParameterMapVectorType parameterMapVector)
{
  ParameterObjectPointer parameterObject = ParameterObjectType::New();
  parameterObject->SetParameterMaps(parameterMapVector);
  parameterObject->Print(std::cout);
}

Image
TransformixImageFilter::TransformixImageFilterImpl ::GetResultImage()
{
  if (this->IsEmpty(this->m_ResultImage))
  {
    sitkExceptionMacro("No result image found. Has transformix run yet?")
  }

  return this->m_ResultImage;
}

Image
TransformixImageFilter::TransformixImageFilterImpl ::GetDeformationField()
{
  if (this->IsEmpty(this->m_DeformationField))
  {
    sitkExceptionMacro(
      "No deformation field found. Has transformix run yet? Have you called ComputeDeformationFieldOn()?")
  }

  return this->m_DeformationField;
}

bool
TransformixImageFilter::TransformixImageFilterImpl ::IsEmpty(const Image & image)
{
  bool isEmpty = image.GetWidth() == 0 && image.GetHeight() == 0;
  return isEmpty;
}

} // namespace itk::simple
