#ifndef sitktransformiximagefilterimpl_h
#define sitktransformiximagefilterimpl_h

// SimpleITK
#include "sitkTransformixImageFilter.h"
#include "sitkMemberFunctionFactory.h"

// Transformix
#include "itkTransformixFilter.h"
#include "elxParameterObject.h"

namespace itk::simple
{

class SITKElastix_HIDDEN TransformixImageFilter::TransformixImageFilterImpl
{
public:
  TransformixImageFilterImpl();
  ~TransformixImageFilterImpl();

  typedef TransformixImageFilterImpl Self;

  typedef elastix::ParameterObject                      ParameterObjectType;
  typedef ParameterObjectType::Pointer                  ParameterObjectPointer;
  typedef ParameterObjectType::ParameterMapType         ParameterMapType;
  typedef ParameterObjectType::ParameterMapVectorType   ParameterMapVectorType;
  typedef ParameterMapType::iterator                    ParameterMapIterator;
  typedef ParameterMapType::const_iterator              ParameterMapConstIterator;
  typedef itk::ParameterFileParser                      ParameterFileParserType;
  typedef ParameterFileParserType::Pointer              ParameterFileParserPointer;
  typedef ParameterObjectType::ParameterKeyType         ParameterKeyType;
  typedef ParameterObjectType::ParameterValueType       ParameterValueType;
  typedef ParameterObjectType::ParameterValueVectorType ParameterValueVectorType;

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
  SetTransformParameterMap(const std::map<std::string, std::vector<std::string>> parameterMap);
  void
  AddTransformParameterMap(const std::map<std::string, std::vector<std::string>> parameterMap);
  std::vector<std::map<std::string, std::vector<std::string>>>
  GetTransformParameterMap();
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
  ReadParameterFile(const std::string filename);
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

  bool
  IsEmpty(const Image & image);

  // Definitions for SimpleITK member factory
  typedef Image (Self::*MemberFunctionType)();
  template <class TMovingImage>
  Image
  ExecuteInternal();
  friend struct detail::MemberFunctionAddressor<MemberFunctionType>;
  std::unique_ptr<detail::MemberFunctionFactory<MemberFunctionType>> m_MemberFactory;

  Image m_MovingImage;
  Image m_ResultImage;
  Image m_DeformationField;

  ParameterMapVectorType m_TransformParameterMapVector;

  bool        m_ComputeSpatialJacobian;
  bool        m_ComputeDeterminantOfSpatialJacobian;
  bool        m_ComputeDeformationField;
  std::string m_MovingPointSetFileName;

  std::string m_OutputDirectory;
  std::string m_LogFileName;

  bool m_LogToConsole;
  bool m_LogToFile;
};

} // namespace itk::simple

#endif // sitktransformiximagefilterimpl_h
