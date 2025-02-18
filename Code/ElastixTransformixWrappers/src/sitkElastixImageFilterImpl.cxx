#include <memory>

#include "sitkElastixImageFilter.h"
#include "sitkElastixImageFilterImpl.h"
#include "sitkCastImageFilter.h"
#include "sitkInternalUtilities.h"

namespace itk::simple
{

ElastixImageFilter::ElastixImageFilterImpl ::ElastixImageFilterImpl(void)
{
  // Register this class with SimpleITK
  this->m_DualMemberFactory = std::make_unique<detail::DualMemberFunctionFactory<MemberFunctionType>>(this);
  this->m_DualMemberFactory->RegisterMemberFunctions<FloatPixelIDTypeList, FloatPixelIDTypeList, 2>();
  this->m_DualMemberFactory->RegisterMemberFunctions<FloatPixelIDTypeList, FloatPixelIDTypeList, 3>();

#if SITK_MAX_DIMENSION >= 4
  this->m_DualMemberFactory->RegisterMemberFunctions<FloatPixelIDTypeList, FloatPixelIDTypeList, 4>();
#endif

  this->m_FixedImages = VectorOfImage();
  this->m_MovingImages = VectorOfImage();
  this->m_FixedMasks = VectorOfImage();
  this->m_MovingMasks = VectorOfImage();
  this->m_ResultImage = Image();

  this->m_ParameterMapVector = ParameterMapVectorType();
  this->m_TransformParameterMapVector = ParameterMapVectorType();

  this->m_FixedPointSetFileName = "";
  this->m_MovingPointSetFileName = "";

  this->m_OutputDirectory = ".";
  this->m_LogFileName = "";

  this->m_LogToFile = false;
  this->m_LogToConsole = true;

  // Use all available threads by default
  this->m_NumberOfThreads = 0;

  ParameterMapVectorType defaultParameterMap;
  defaultParameterMap.push_back(ParameterObjectType::GetDefaultParameterMap("translation"));
  defaultParameterMap.push_back(ParameterObjectType::GetDefaultParameterMap("affine"));
  defaultParameterMap.push_back(ParameterObjectType::GetDefaultParameterMap("bspline"));
  this->SetParameterMap(defaultParameterMap);
}

ElastixImageFilter::ElastixImageFilterImpl ::~ElastixImageFilterImpl(void) {}


Image
ElastixImageFilter::ElastixImageFilterImpl ::Execute(void)
{
  if (this->GetNumberOfFixedImages() == 0)
  {
    sitkExceptionMacro("Fixed image not set.");
  }

  if (this->GetNumberOfMovingImages() == 0)
  {
    sitkExceptionMacro("Moving image not set.");
  }

  const PixelIDValueEnum FixedImagePixelID = this->GetFixedImage(0).GetPixelID();
  const unsigned int     FixedImageDimension = this->GetFixedImage(0).GetDimension();
  const PixelIDValueEnum MovingImagePixelID = this->GetMovingImage(0).GetPixelID();
  const unsigned int     MovingImageDimension = this->GetMovingImage(0).GetDimension();

  for (unsigned int i = 1; i < this->GetNumberOfFixedImages(); ++i)
  {
    if (this->GetFixedImage(i).GetDimension() != FixedImageDimension)
    {
      sitkExceptionMacro("Fixed images must be of same dimension (fixed image at index 0 is of dimension "
                         << this->GetFixedImage(0).GetDimension() << ", fixed image at index " << i
                         << " is of dimension \"" << this->GetFixedImage(i).GetDimension() << "\").");
    }
  }

  for (unsigned int i = 1; i < this->GetNumberOfMovingImages(); ++i)
  {
    if (this->GetMovingImage(i).GetDimension() != FixedImageDimension)
    {
      sitkExceptionMacro(
        "Moving images must be of same dimension as fixed images (fixed image at index 0 is of dimension "
        << this->GetFixedImage(0).GetDimension() << ", moving image at index " << i << " is of dimension \""
        << this->GetMovingImage(i).GetDimension() << "\").");
    }
  }

  if (this->GetNumberOfFixedMasks() != 0 && this->GetNumberOfFixedMasks() != 1 &&
      this->GetNumberOfFixedMasks() != this->GetNumberOfFixedImages())
  {
    sitkExceptionMacro("Number of fixed masks must be 0, 1 or " << this->GetNumberOfFixedImages()
                                                                << " (the number of fixed images).")
  }

  if (this->GetNumberOfMovingMasks() != 0 && this->GetNumberOfMovingMasks() != 1 &&
      this->GetNumberOfMovingMasks() != this->GetNumberOfMovingImages())
  {
    sitkExceptionMacro("Number of moving masks must be 0, 1 or " << this->GetNumberOfMovingImages()
                                                                 << " (the number of moving images).")
  }

  for (unsigned int i = 0; i < this->GetNumberOfFixedMasks(); ++i)
  {
    if (this->GetFixedMask(i).GetPixelID() != sitkUInt8)
    {
      sitkExceptionMacro("Fixed mask must be of pixel type sitkUInt8 but fixed mask "
                         << i << " is of type \"" << GetPixelIDValueAsString(this->GetFixedMask(i).GetPixelID())
                         << "\". Cast with `SimpleITK.Cast(mask, sitk.sitkUInt8)`.");
    }

    if (this->GetFixedMask(i).GetDimension() != FixedImageDimension)
    {
      sitkExceptionMacro("Fixed masks must be of same dimension as fixed images (fixed images are of dimension "
                         << this->GetFixedImage(0).GetDimension() << ", fixed mask at index " << i
                         << " is of dimension \"" << this->GetFixedMask(i).GetDimension() << "\").");
    }

    if (this->GetFixedMask(i).GetOrigin() != this->GetFixedImage(i).GetOrigin())
    {
      sitkExceptionMacro("Fixed masks must have same origins as fixed images (fixed image at index 0 has origin at "
                         << this->GetFixedImage(i).GetOrigin() << ", fixed mask at index " << i << " has origin at  \""
                         << this->GetFixedMask(i).GetOrigin() << "\").");
    }

    if (this->GetFixedMask(i).GetDirection() != this->GetFixedImage(i).GetDirection())
    {
      sitkExceptionMacro("Fixed masks must have same direction cosines as fixed images (fixed image at index "
                         << i << " has direction cosine " << this->GetFixedImage(i).GetDirection()
                         << ", fixed mask at index " << i << " has direction cosine \""
                         << this->GetFixedMask(i).GetDirection() << "\").");
    }

    if (this->GetFixedMask(i).GetSpacing() != this->GetFixedImage(i).GetSpacing())
    {
      sitkExceptionMacro("Fixed masks must have same spacing as fixed images (fixed image at index "
                         << i << " has spacing " << this->GetFixedImage(i).GetSpacing() << ", fixed mask at index " << i
                         << " has spacing  \"" << this->GetFixedMask(i).GetSpacing() << "\").");
    }
  }

  for (unsigned int i = 0; i < this->GetNumberOfMovingMasks(); ++i)
  {
    if (this->GetMovingMask(i).GetPixelID() != sitkUInt8)
    {
      sitkExceptionMacro("Moving mask must be of pixel type sitkUInt8 but moving mask "
                         << i << " is of type \"" << GetPixelIDValueAsString(this->GetFixedMask(i).GetPixelID())
                         << "\". Cast with `SimpleITK.Cast(mask, sitk.sitkUInt8)`.");
    }

    if (this->GetMovingMask(i).GetDimension() != MovingImageDimension)
    {
      sitkExceptionMacro("Moving masks must be of same dimension as moving images (moving images are of dimension "
                         << this->GetMovingImage(0).GetDimension() << ", moving mask at index " << i
                         << " is of dimension \"" << this->GetMovingMask(i).GetDimension() << "\").");
    }

    if (this->GetMovingMask(i).GetOrigin() != this->GetMovingImage(i).GetOrigin())
    {
      sitkExceptionMacro("Moving masks must have same origins as moving images (moving image at index "
                         << i << " has origin " << this->GetMovingImage(i).GetOrigin() << ", moving mask at index " << i
                         << " has origin \"" << this->GetMovingMask(i).GetOrigin() << "\").");
    }

    if (this->GetMovingMask(i).GetDirection() != this->GetMovingImage(i).GetDirection())
    {
      sitkExceptionMacro("Moving masks must have same direction cosines as moving images (moving image at index "
                         << i << " has direction cosine " << this->GetMovingImage(i).GetDirection()
                         << ", moving mask at index " << i << " has direction cosine \""
                         << this->GetMovingMask(i).GetDirection() << "\").");
    }

    if (this->GetMovingMask(i).GetSpacing() != this->GetMovingImage(i).GetSpacing())
    {
      sitkExceptionMacro("Moving masks must have same spacing as moving images (moving image at index "
                         << i << " has spacing " << this->GetMovingImage(i).GetSpacing() << ", moving mask at index "
                         << i << " has spacing  \"" << this->GetMovingMask(i).GetSpacing() << "\").");
    }
  }

  if (this->m_DualMemberFactory->HasMemberFunction(sitkFloat32, sitkFloat32, FixedImageDimension))
  {
    return this->m_DualMemberFactory->GetMemberFunction(sitkFloat32, sitkFloat32, FixedImageDimension)();
  }

  sitkExceptionMacro(<< "ElastixImageFilter does not support the combination of " << FixedImageDimension
                     << "-dimensional " << GetPixelIDValueAsString(FixedImagePixelID) << " fixed image and a "
                     << MovingImageDimension << "-dimensional " << GetPixelIDValueAsString(MovingImagePixelID)
                     << " moving image. ")
}

template <typename TFixedImage, typename TMovingImage>
Image
ElastixImageFilter::ElastixImageFilterImpl ::DualExecuteInternal(void)
{
  typedef itk::ElastixRegistrationMethod<TFixedImage, TMovingImage> ElastixRegistrationMethodType;
  typedef typename ElastixRegistrationMethodType::Pointer           ElastixRegistrationMethodPointer;
  typedef typename ElastixRegistrationMethodType::FixedMaskType     FixedMaskType;
  typedef typename ElastixRegistrationMethodType::MovingMaskType    MovingMaskType;

  using FixedImageType = typename ElastixRegistrationMethodType::FixedImageType;

  typename FixedImageType::Pointer output;

  try
  {
    ElastixRegistrationMethodPointer elastixFilter = ElastixRegistrationMethodType::New();

    for (unsigned int i = 0; i < this->GetNumberOfFixedImages(); ++i)
    {
      elastixFilter->AddFixedImage(
        itkDynamicCastInDebugMode<TFixedImage *>(Cast(this->GetFixedImage(i), sitkFloat32).GetITKBase()));
    }

    for (unsigned int i = 0; i < this->GetNumberOfMovingImages(); ++i)
    {
      elastixFilter->AddMovingImage(
        itkDynamicCastInDebugMode<TMovingImage *>(Cast(this->GetMovingImage(i), sitkFloat32).GetITKBase()));
    }

    for (unsigned int i = 0; i < this->GetNumberOfFixedMasks(); ++i)
    {
      elastixFilter->AddFixedMask(itkDynamicCastInDebugMode<FixedMaskType *>(this->GetFixedMask(i).GetITKBase()));
    }

    for (unsigned int i = 0; i < this->GetNumberOfMovingMasks(); ++i)
    {
      elastixFilter->AddMovingMask(itkDynamicCastInDebugMode<MovingMaskType *>(this->GetMovingMask(i).GetITKBase()));
    }

    elastixFilter->SetInitialTransformParameterFileName(this->GetInitialTransformParameterFileName());
    elastixFilter->SetFixedPointSetFileName(this->GetFixedPointSetFileName());
    elastixFilter->SetMovingPointSetFileName(this->GetMovingPointSetFileName());

    elastixFilter->SetOutputDirectory(this->GetOutputDirectory());
    elastixFilter->SetLogFileName(this->GetLogFileName());
    elastixFilter->SetLogToFile(this->GetLogToFile());
    elastixFilter->SetLogToConsole(this->GetLogToConsole());
    elastixFilter->SetNumberOfThreads(this->GetNumberOfThreads());

    ParameterMapVectorType parameterMapVector = this->m_ParameterMapVector;
    for (unsigned int i = 0; i < parameterMapVector.size(); i++)
    {
      parameterMapVector[i]["FixedInternalImagePixelType"] = ParameterValueVectorType(1, "float");
      parameterMapVector[i]["MovingInternalImagePixelType"] = ParameterValueVectorType(1, "float");
    }

    // Always set WriteResultImage to true. If WriteResultImage is false, elastixFilter will not produce an output
    // image, and the call to itk::simple::Image() below will throw a "LargestPossibleRegion != BufferedRegion"
    // exception. We also need the output image to honor SimpleITK's convention of Execute() always returning an image.
    parameterMapVector[parameterMapVector.size() - 1]["WriteResultImage"] = ParameterValueVectorType(1, "true");

    ParameterObjectPointer parameterObject = ParameterObjectType::New();
    parameterObject->SetParameterMaps(parameterMapVector);
    elastixFilter->SetParameterObject(parameterObject);

    elastixFilter->Update();

    output = elastixFilter->GetOutput();

    this->m_TransformParameterMapVector = elastixFilter->GetTransformParameterObject()->GetParameterMaps();
  }
  catch (itk::ExceptionObject & e)
  {
    sitkExceptionMacro(<< e);
  }


  // Convert to SimpleITK image after Elastix filter has been destroyed to avoid issue with multiple references to the
  // image buffer.
  this->m_ResultImage = Image(output);

  return this->m_ResultImage;
}

std::string
ElastixImageFilter::ElastixImageFilterImpl ::GetName(void) const
{
  const std::string name = "ElastixImageFilter";
  return name;
}

void
ElastixImageFilter::ElastixImageFilterImpl ::SetFixedImage(const Image & fixedImage)
{
  if (this->IsEmpty(fixedImage))
  {
    sitkExceptionMacro("Image is empty.")
  }

  this->RemoveFixedImage();
  this->m_FixedImages.push_back(fixedImage);
}

void
ElastixImageFilter::ElastixImageFilterImpl ::SetFixedImage(const VectorOfImage & fixedImages)
{
  if (fixedImages.size() == 0u)
  {
    sitkExceptionMacro("Cannot set fixed images from empty vector");
  }

  this->RemoveFixedImage();
  this->m_FixedImages = fixedImages;
}

void
ElastixImageFilter::ElastixImageFilterImpl ::AddFixedImage(const Image & fixedImage)
{
  if (this->IsEmpty(fixedImage))
  {
    sitkExceptionMacro("Image is empty.")
  }

  this->m_FixedImages.push_back(fixedImage);
}

Image &
ElastixImageFilter::ElastixImageFilterImpl ::GetFixedImage(const unsigned long index)
{
  if (index < this->m_FixedImages.size())
  {
    return this->m_FixedImages[index];
  }

  sitkExceptionMacro(
    "Index out of range (index: " << index << ", number of fixed images: " << this->m_FixedImages.size() << ")");
}

ElastixImageFilter::ElastixImageFilterImpl::VectorOfImage &
ElastixImageFilter::ElastixImageFilterImpl ::GetFixedImage(void)
{
  return this->m_FixedImages;
}

void
ElastixImageFilter::ElastixImageFilterImpl ::RemoveFixedImage(const unsigned long index)
{
  if (index < this->m_FixedImages.size())
  {
    this->m_FixedImages.erase(this->m_FixedImages.begin() + index);
  }

  sitkExceptionMacro(
    "Index out of range (index: " << index << ", number of fixed images: " << this->m_FixedImages.size() << ")");
}

void
ElastixImageFilter::ElastixImageFilterImpl ::RemoveFixedImage(void)
{
  this->m_FixedImages.clear();
}

unsigned int
ElastixImageFilter::ElastixImageFilterImpl ::GetNumberOfFixedImages(void)
{
  return this->m_FixedImages.size();
}

void
ElastixImageFilter::ElastixImageFilterImpl ::SetMovingImage(const Image & movingImage)
{
  if (this->IsEmpty(movingImage))
  {
    sitkExceptionMacro("Image is empty.")
  }

  this->RemoveMovingImage();
  this->m_MovingImages.push_back(movingImage);
}

void
ElastixImageFilter::ElastixImageFilterImpl ::SetMovingImage(const VectorOfImage & movingImages)
{
  if (movingImages.size() == 0u)
  {
    sitkExceptionMacro("Cannot set moving images from empty vector");
  }

  this->RemoveMovingImage();
  this->m_MovingImages = movingImages;
}

void
ElastixImageFilter::ElastixImageFilterImpl ::AddMovingImage(const Image & movingImage)
{
  if (this->IsEmpty(movingImage))
  {
    sitkExceptionMacro("Image is empty.")
  }

  this->m_MovingImages.push_back(movingImage);
}

Image &
ElastixImageFilter::ElastixImageFilterImpl ::GetMovingImage(const unsigned long index)
{
  if (index < this->m_MovingImages.size())
  {
    return this->m_MovingImages[index];
  }

  sitkExceptionMacro(
    "Index out of range (index: " << index << ", number of moving images: " << this->m_MovingImages.size() << ")");
}

ElastixImageFilter::ElastixImageFilterImpl::VectorOfImage &
ElastixImageFilter::ElastixImageFilterImpl ::GetMovingImage(void)
{
  return this->m_MovingImages;
}

void
ElastixImageFilter::ElastixImageFilterImpl ::RemoveMovingImage(const unsigned long index)
{
  if (index < this->m_MovingImages.size())
  {
    this->m_MovingImages.erase(this->m_MovingImages.begin() + index);
  }

  sitkExceptionMacro(
    "Index out of range (index: " << index << ", number of moving images: " << this->m_MovingImages.size() << ")");
}

void
ElastixImageFilter::ElastixImageFilterImpl ::RemoveMovingImage(void)
{
  this->m_MovingImages.clear();
}

unsigned int
ElastixImageFilter::ElastixImageFilterImpl ::GetNumberOfMovingImages(void)
{
  return this->m_MovingImages.size();
}

void
ElastixImageFilter::ElastixImageFilterImpl ::SetFixedMask(const Image & fixedMask)
{
  if (this->IsEmpty(fixedMask))
  {
    sitkExceptionMacro("Image is empty.")
  }

  this->RemoveFixedMask();
  this->m_FixedMasks.push_back(fixedMask);
}

void
ElastixImageFilter::ElastixImageFilterImpl ::SetFixedMask(const VectorOfImage & fixedMasks)
{
  if (fixedMasks.size() == 0u)
  {
    sitkExceptionMacro("Cannot set fixed images from empty vector");
  }

  this->RemoveFixedMask();
  this->m_FixedMasks = fixedMasks;
}

void
ElastixImageFilter::ElastixImageFilterImpl ::AddFixedMask(const Image & fixedMask)
{
  if (this->IsEmpty(fixedMask))
  {
    sitkExceptionMacro("Image is empty.")
  }

  this->m_FixedMasks.push_back(fixedMask);
}

Image &
ElastixImageFilter::ElastixImageFilterImpl ::GetFixedMask(const unsigned long index)
{
  if (index < this->m_FixedMasks.size())
  {
    return this->m_FixedMasks[index];
  }

  sitkExceptionMacro("Index out of range (index: " << index << ", number of fixed masks: " << this->m_FixedMasks.size()
                                                   << ")");
}

ElastixImageFilter::VectorOfImage &
ElastixImageFilter::ElastixImageFilterImpl ::GetFixedMask(void)
{
  return this->m_FixedMasks;
}

void
ElastixImageFilter::ElastixImageFilterImpl ::RemoveFixedMask(const unsigned long index)
{
  if (index < this->m_FixedMasks.size())
  {
    this->m_FixedMasks.erase(this->m_FixedMasks.begin() + index);
  }

  sitkExceptionMacro("Index out of range (index: " << index << ", number of fixed masks: " << this->m_FixedMasks.size()
                                                   << ")");
}

void
ElastixImageFilter::ElastixImageFilterImpl ::RemoveFixedMask(void)
{
  this->m_FixedMasks.clear();
}

unsigned int
ElastixImageFilter::ElastixImageFilterImpl ::GetNumberOfFixedMasks(void)
{
  return this->m_FixedMasks.size();
}

void
ElastixImageFilter::ElastixImageFilterImpl ::SetMovingMask(const Image & movingMask)
{
  if (this->IsEmpty(movingMask))
  {
    sitkExceptionMacro("Image is empty.")
  }

  this->RemoveMovingMask();
  this->m_MovingMasks.push_back(movingMask);
}

void
ElastixImageFilter::ElastixImageFilterImpl ::SetMovingMask(const VectorOfImage & movingMasks)
{
  if (movingMasks.size() == 0u)
  {
    sitkExceptionMacro("Cannot set moving masks from empty vector");
  }

  this->RemoveMovingMask();
  this->m_MovingMasks = movingMasks;
}

void
ElastixImageFilter::ElastixImageFilterImpl ::AddMovingMask(const Image & movingMask)
{
  if (this->IsEmpty(movingMask))
  {
    sitkExceptionMacro("Image is empty.")
  }

  this->m_MovingMasks.push_back(movingMask);
}

Image &
ElastixImageFilter::ElastixImageFilterImpl ::GetMovingMask(const unsigned long index)
{
  if (index < this->m_MovingMasks.size())
  {
    return this->m_MovingMasks[index];
  }

  sitkExceptionMacro(
    "Index out of range (index: " << index << ", number of moving masks: " << this->m_MovingMasks.size() << ")");
}

ElastixImageFilter::ElastixImageFilterImpl::VectorOfImage &
ElastixImageFilter::ElastixImageFilterImpl ::GetMovingMask(void)
{
  return this->m_MovingMasks;
}

void
ElastixImageFilter::ElastixImageFilterImpl ::RemoveMovingMask(const unsigned long index)
{
  if (index < this->m_MovingMasks.size())
  {
    this->m_MovingMasks.erase(this->m_MovingMasks.begin() + index);
  }

  sitkExceptionMacro(
    "Index out of range (index: " << index << ", number of moving masks: " << this->m_MovingMasks.size() << ")");
}

void
ElastixImageFilter::ElastixImageFilterImpl ::RemoveMovingMask(void)
{
  this->m_MovingMasks.clear();
}

unsigned int
ElastixImageFilter::ElastixImageFilterImpl ::GetNumberOfMovingMasks(void)
{
  return this->m_MovingMasks.size();
}

void
ElastixImageFilter::ElastixImageFilterImpl ::SetFixedPointSetFileName(const std::string fixedPointSetFileName)
{
  this->m_FixedPointSetFileName = fixedPointSetFileName;
}

std::string
ElastixImageFilter::ElastixImageFilterImpl ::GetFixedPointSetFileName(void)
{
  return this->m_FixedPointSetFileName;
}

void
ElastixImageFilter::ElastixImageFilterImpl ::RemoveFixedPointSetFileName(void)
{
  this->m_FixedPointSetFileName = "";
}

void
ElastixImageFilter::ElastixImageFilterImpl ::SetMovingPointSetFileName(const std::string movingPointSetFileName)
{
  this->m_MovingPointSetFileName = movingPointSetFileName;
}

std::string
ElastixImageFilter::ElastixImageFilterImpl ::GetMovingPointSetFileName(void)
{
  return this->m_MovingPointSetFileName;
}

void
ElastixImageFilter::ElastixImageFilterImpl ::RemoveMovingPointSetFileName(void)
{
  this->m_MovingPointSetFileName = "";
}

void
ElastixImageFilter::ElastixImageFilterImpl ::SetOutputDirectory(const std::string outputDirectory)
{
  this->m_OutputDirectory = outputDirectory;
}

std::string
ElastixImageFilter::ElastixImageFilterImpl ::GetOutputDirectory(void)
{
  return this->m_OutputDirectory;
}

void
ElastixImageFilter::ElastixImageFilterImpl ::RemoveOutputDirectory(void)
{
  this->m_OutputDirectory = "";
}

void
ElastixImageFilter::ElastixImageFilterImpl ::SetLogFileName(std::string logFileName)
{
  this->m_LogFileName = logFileName;
}

std::string
ElastixImageFilter::ElastixImageFilterImpl ::GetLogFileName(void)
{
  return this->m_LogFileName;
}

void
ElastixImageFilter::ElastixImageFilterImpl ::RemoveLogFileName(void)
{
  this->m_LogFileName = "";
}

void
ElastixImageFilter::ElastixImageFilterImpl ::SetLogToFile(bool logToFile)
{
  this->m_LogToFile = logToFile;
}

bool
ElastixImageFilter::ElastixImageFilterImpl ::GetLogToFile(void)
{
  return this->m_LogToFile;
}

void
ElastixImageFilter::ElastixImageFilterImpl ::LogToFileOn()
{
  this->SetLogToFile(true);
}

void
ElastixImageFilter::ElastixImageFilterImpl ::LogToFileOff()
{
  this->SetLogToFile(false);
}

void
ElastixImageFilter::ElastixImageFilterImpl ::SetLogToConsole(bool logToConsole)
{
  this->m_LogToConsole = logToConsole;
}

bool
ElastixImageFilter::ElastixImageFilterImpl ::GetLogToConsole(void)
{
  return this->m_LogToConsole;
}

void
ElastixImageFilter::ElastixImageFilterImpl ::LogToConsoleOn()
{
  this->SetLogToConsole(true);
}

void
ElastixImageFilter::ElastixImageFilterImpl ::LogToConsoleOff()
{
  this->SetLogToConsole(false);
}

void
ElastixImageFilter::ElastixImageFilterImpl ::SetNumberOfThreads(int n)
{
  this->m_NumberOfThreads = n;
}

int
ElastixImageFilter::ElastixImageFilterImpl ::GetNumberOfThreads()
{
  return this->m_NumberOfThreads;
}

void
ElastixImageFilter::ElastixImageFilterImpl ::SetParameterMap(const std::string  transformName,
                                                             const unsigned int numberOfResolutions,
                                                             const double       finalGridSpacingInPhysicalUnits)
{
  ParameterMapType parameterMap =
    ParameterObjectType::GetDefaultParameterMap(transformName, numberOfResolutions, finalGridSpacingInPhysicalUnits);
  this->SetParameterMap(parameterMap);
}

void
ElastixImageFilter::ElastixImageFilterImpl ::SetParameterMap(const ParameterMapType parameterMap)
{
  ParameterMapVectorType parameterMapVector = ParameterMapVectorType(1, parameterMap);
  this->SetParameterMap(parameterMapVector);
}

void
ElastixImageFilter::ElastixImageFilterImpl ::SetParameterMap(const ParameterMapVectorType parameterMapVector)
{
  this->m_ParameterMapVector = parameterMapVector;
}

void
ElastixImageFilter::ElastixImageFilterImpl ::AddParameterMap(const ParameterMapType parameterMap)
{
  this->m_ParameterMapVector.push_back(parameterMap);
}

ElastixImageFilter::ElastixImageFilterImpl::ParameterMapVectorType
ElastixImageFilter::ElastixImageFilterImpl ::GetParameterMap(void)
{
  return this->m_ParameterMapVector;
}

unsigned int
ElastixImageFilter::ElastixImageFilterImpl ::GetNumberOfParameterMaps(void)
{
  return this->m_ParameterMapVector.size();
}

void
ElastixImageFilter::ElastixImageFilterImpl ::SetInitialTransformParameterFileName(
  const std::string initialTransformParameterFileName)
{
  this->m_InitialTransformParameterMapFileName = initialTransformParameterFileName;
}

std::string
ElastixImageFilter::ElastixImageFilterImpl ::GetInitialTransformParameterFileName(void)
{
  return m_InitialTransformParameterMapFileName;
}

void
ElastixImageFilter::ElastixImageFilterImpl ::RemoveInitialTransformParameterFileName(void)
{
  this->m_InitialTransformParameterMapFileName = "";
}

void
ElastixImageFilter::ElastixImageFilterImpl ::SetParameter(const ParameterKeyType key, const ParameterValueType value)
{
  for (unsigned int i = 0; i < this->m_ParameterMapVector.size(); i++)
  {
    this->SetParameter(i, key, value);
  }
}

void
ElastixImageFilter::ElastixImageFilterImpl ::SetParameter(const ParameterKeyType         key,
                                                          const ParameterValueVectorType value)
{
  for (unsigned int i = 0; i < this->m_ParameterMapVector.size(); i++)
  {
    this->SetParameter(i, key, value);
  }
}

void
ElastixImageFilter::ElastixImageFilterImpl ::SetParameter(const unsigned int       index,
                                                          const ParameterKeyType   key,
                                                          const ParameterValueType value)
{
  if (index >= this->m_ParameterMapVector.size())
  {
    sitkExceptionMacro("Parameter map index is out of range (index: " << index << "; number of parameters maps: "
                                                                      << this->m_ParameterMapVector.size()
                                                                      << "). Note that indexes are zero-based.");
  }

  this->m_ParameterMapVector[index][key] = ParameterValueVectorType(1, value);
}

void
ElastixImageFilter::ElastixImageFilterImpl ::SetParameter(const unsigned int             index,
                                                          const ParameterKeyType         key,
                                                          const ParameterValueVectorType value)
{
  if (index >= this->m_ParameterMapVector.size())
  {
    sitkExceptionMacro("Parameter map index is out of range (index: " << index << ", number of parameters maps: "
                                                                      << this->m_ParameterMapVector.size()
                                                                      << "). Note that indexes are zero-based.");
  }

  this->m_ParameterMapVector[index][key] = value;
}

void
ElastixImageFilter::ElastixImageFilterImpl ::AddParameter(const ParameterKeyType key, const ParameterValueType value)
{
  for (unsigned int i = 0; i < this->m_ParameterMapVector.size(); i++)
  {
    this->AddParameter(i, key, value);
  }
}

void
ElastixImageFilter::ElastixImageFilterImpl ::AddParameter(const ParameterKeyType         key,
                                                          const ParameterValueVectorType value)
{
  for (unsigned int i = 0; i < this->m_ParameterMapVector.size(); i++)
  {
    this->AddParameter(i, key, value);
  }
}

void
ElastixImageFilter::ElastixImageFilterImpl ::AddParameter(const unsigned int       index,
                                                          const ParameterKeyType   key,
                                                          const ParameterValueType value)
{
  if (index >= this->m_ParameterMapVector.size())
  {
    sitkExceptionMacro("Parameter map index is out of range (index: " << index << ", number of parameters maps: "
                                                                      << this->m_ParameterMapVector.size()
                                                                      << "). Note that indexes are zero-based.");
  }

  if (this->m_ParameterMapVector[index].find(key) == this->m_ParameterMapVector[index].end())
  {
    this->SetParameter(index, key, value);
  }
  else
  {
    this->m_ParameterMapVector[index][key].push_back(value);
  }
}

void
ElastixImageFilter::ElastixImageFilterImpl ::AddParameter(const unsigned int             index,
                                                          const ParameterKeyType         key,
                                                          const ParameterValueVectorType value)
{
  if (index >= this->m_ParameterMapVector.size())
  {
    sitkExceptionMacro("Parameter map index is out of range (index: " << index << ", number of parameters maps: "
                                                                      << this->m_ParameterMapVector.size()
                                                                      << "). Note that indexes are zero-based.");
  }

  if (this->m_ParameterMapVector[index].find(key) == this->m_ParameterMapVector[index].end())
  {
    this->SetParameter(index, key, value);
  }
  else
  {
    for (unsigned int i = 0; i < value.size(); i++)
    {
      this->m_ParameterMapVector[index][key].push_back(value[i]);
    }
  }
}

ElastixImageFilter::ElastixImageFilterImpl::ParameterValueVectorType
ElastixImageFilter::ElastixImageFilterImpl ::GetParameter(const ParameterKeyType key)
{
  if (this->m_ParameterMapVector.size() > 1)
  {
    sitkExceptionMacro("An index is needed when more than one parameter map is present. Please specify the parameter "
                       "map number as the first argument.");
  }

  return this->GetParameter(0, key);
}

ElastixImageFilter::ElastixImageFilterImpl::ParameterValueVectorType
ElastixImageFilter::ElastixImageFilterImpl ::GetParameter(const unsigned int index, const ParameterKeyType key)
{
  if (index >= this->m_ParameterMapVector.size())
  {
    sitkExceptionMacro("Parameter map index is out of range (index: " << index << ", number of parameters maps: "
                                                                      << this->m_ParameterMapVector.size()
                                                                      << "). Note that indexes are zero-based.");
  }

  return this->m_ParameterMapVector[index][key];
}

void
ElastixImageFilter::ElastixImageFilterImpl ::RemoveParameter(const ParameterKeyType key)
{
  for (unsigned int i = 0; i < this->m_ParameterMapVector.size(); i++)
  {
    this->RemoveParameter(i, key);
  }
}

void
ElastixImageFilter::ElastixImageFilterImpl ::RemoveParameter(const unsigned int index, const ParameterKeyType key)
{
  if (index >= this->m_ParameterMapVector.size())
  {
    sitkExceptionMacro("Parameter map index is out of range (index: " << index << ", number of parameters maps: "
                                                                      << this->m_ParameterMapVector.size()
                                                                      << "). Note that indexes are zero-based.");
  }

  this->m_ParameterMapVector[index].erase(key);
}

ElastixImageFilter::ElastixImageFilterImpl::ParameterMapType
ElastixImageFilter::ElastixImageFilterImpl ::ReadParameterFile(const std::string fileName)
{
  ParameterObjectPointer parameterObject = ParameterObjectType::New();
  parameterObject->ReadParameterFile(fileName);
  return parameterObject->GetParameterMap(0);
}

void
ElastixImageFilter::ElastixImageFilterImpl ::WriteParameterFile(const ParameterMapType parameterMap,
                                                                const std::string      parameterFileName)
{
  ParameterObjectPointer parameterObject = ParameterObjectType::New();
  parameterObject->WriteParameterFile(parameterMap, parameterFileName);
}

ElastixImageFilter::ElastixImageFilterImpl::ParameterMapType
ElastixImageFilter::ElastixImageFilterImpl ::GetDefaultParameterMap(const std::string  transformName,
                                                                    const unsigned int numberOfResolutions,
                                                                    const double       finalGridSpacingInPhysicalUnits)
{
  return ParameterObjectType::GetDefaultParameterMap(
    transformName, numberOfResolutions, finalGridSpacingInPhysicalUnits);
}

ElastixImageFilter::ElastixImageFilterImpl::ParameterMapVectorType
ElastixImageFilter::ElastixImageFilterImpl ::GetTransformParameterMap(void)
{
  if (this->m_TransformParameterMapVector.size() == 0)
  {
    sitkExceptionMacro("Number of transform parameter maps: 0. Run registration with Execute().");
  }

  return this->m_TransformParameterMapVector;
}

ElastixImageFilter::ElastixImageFilterImpl::ParameterMapType
ElastixImageFilter::ElastixImageFilterImpl ::GetTransformParameterMap(const unsigned int index)
{
  if (this->GetNumberOfParameterMaps() == 0)
  {
    sitkExceptionMacro("Number of transform parameter maps: 0. Run registration with Execute().");
  }

  if (this->GetNumberOfParameterMaps() <= index)
  {
    sitkExceptionMacro("Index exceeds number of transform parameter maps (index: "
                       << index << ", number of parameter maps: " << this->GetNumberOfParameterMaps() << ").");
  }

  return this->m_TransformParameterMapVector[index];
}

Image
ElastixImageFilter::ElastixImageFilterImpl ::GetResultImage(void)
{
  if (this->IsEmpty(this->m_ResultImage))
  {
    sitkExceptionMacro("No result image found. Run registration with Execute().")
  }

  return this->m_ResultImage;
}

void
ElastixImageFilter::ElastixImageFilterImpl ::PrintParameterMap(void)
{
  if (this->GetNumberOfParameterMaps() == 0)
  {
    sitkExceptionMacro("Cannot print parameter maps: Number of parameter maps is 0.")
  }

  this->PrintParameterMap(this->GetParameterMap());
}

void
ElastixImageFilter::ElastixImageFilterImpl ::PrintParameterMap(const ParameterMapType parameterMap)
{
  this->PrintParameterMap(ParameterMapVectorType(1, parameterMap));
}

void
ElastixImageFilter::ElastixImageFilterImpl ::PrintParameterMap(const ParameterMapVectorType parameterMapVector)
{
  ParameterObjectPointer parameterObject = ParameterObjectType::New();
  parameterObject->SetParameterMaps(parameterMapVector);
  parameterObject->Print(std::cout);
}

bool
ElastixImageFilter::ElastixImageFilterImpl ::IsEmpty(const Image & image)
{
  const bool isEmpty = image.GetWidth() == 0 && image.GetHeight() == 0;
  return isEmpty;
}

} // namespace itk::simple
