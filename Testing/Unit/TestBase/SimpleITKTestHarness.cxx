
#include "SimpleITKTestHarness.h"
#include "SimpleITKTestHarnessPaths.h"

#include "sitkConditional.h"
#include "sitkPixelIDValues.h"
#include "sitkProcessObject.h"

#include <itksys/SystemTools.hxx>
#include <itksys/Process.h>


DataFinder::DataFinder() :
  mDirectory(TEST_HARNESS_DATA_DIRECTORY),
  mOutputDirectory(TEST_HARNESS_TEMP_DIRECTORY)
{
}

void DataFinder::SetDirectory ( const char* dir )
{
  mDirectory = dir;
}


void DataFinder::SetDirectory ( std::string dir )
{
  mDirectory = dir;
}


void DataFinder::SetOutputDirectory ( std::string dir )
{
  mOutputDirectory = dir;
}



std::string DataFinder::GetDirectory () const
{
  return mDirectory;
}

std::string DataFinder::GetOutputDirectory () const
{
  return mOutputDirectory;
}

std::string DataFinder::GetOutputFile ( std::string filename ) const
{
  return mOutputDirectory + "/" + filename;
}

std::string DataFinder::GetBuildDirectory () const
{
  return std::string ( SIMPLEITK_BINARY_DIR );
}

std::string DataFinder::GetPathSeparator () const
{
#ifdef WIN32
  return ";";
#else
  return ":";
#endif
}

bool DataFinder::FileExists ( const std::string &filename ) const
{
  return itksys::SystemTools::FileExists ( filename.c_str() );
}

std::string DataFinder::GetFile ( const std::string &filename ) const
{
  std::string name;

  name = mDirectory + "/" + filename;
  if (this->FileExists(name))
    return name;

  // fall back to source code path
  name = std::string(SIMPLEITK_SOURCE_DIR) + "/Testing/Data/" + filename;

  return name;
}


//
//
//


ProcessObjectCommand::ProcessObjectCommand(itk::simple::ProcessObject &po)
  : m_Process(po)
{
}

ProgressUpdate::ProgressUpdate(itk::simple::ProcessObject &po)
  : ProcessObjectCommand(po),
    m_Progress(0.0)
{
}

void ProgressUpdate::Execute( )
{
  std::cout << "Progress: " << m_Process.GetProgress() << std::endl;
  m_Progress =  m_Process.GetProgress();
}

AbortAtCommand::AbortAtCommand(itk::simple::ProcessObject &po, float abortAt)
  : ProcessObjectCommand(po),
    m_AbortAt(abortAt)
{
}

void AbortAtCommand::Execute( )
{
  std::cout << "p: " << m_Process.GetProgress() << std::endl;
  if ( m_Process.GetProgress() >= m_AbortAt )
    {
    std::cout << "aborting..." << std::endl;
    m_Process.Abort();
    }
}

CountCommand::CountCommand(itk::simple::ProcessObject &po)
  : ProcessObjectCommand(po),
    m_Count(0)
{
}

void CountCommand::Execute( )
{
  ++m_Count;
}

void * GetBufferAsVoid( itk::simple::Image &sitkImage)
{

  namespace sitk = itk::simple;
  void *sitkBufferPtr = NULL;

  switch( sitkImage.GetPixelIDValue() )
    {
    case sitk::sitkUnknown:
      break;
    case sitk::ConditionalValue< sitk::sitkVectorUInt8 != sitk::sitkUnknown, sitk::sitkVectorUInt8, -14 >::Value:
    case sitk::ConditionalValue< sitk::sitkUInt8 != sitk::sitkUnknown, sitk::sitkUInt8, -2 >::Value:
      sitkBufferPtr = (void *)sitkImage.GetBufferAsUInt8();
      break;
    case sitk::ConditionalValue< sitk::sitkVectorInt8 != sitk::sitkUnknown, sitk::sitkVectorInt8, -15 >::Value:
    case sitk::ConditionalValue< sitk::sitkInt8 != sitk::sitkUnknown, sitk::sitkInt8, -3 >::Value:
      sitkBufferPtr = (void *)sitkImage.GetBufferAsInt8();
      break;
    case sitk::ConditionalValue< sitk::sitkVectorUInt16 != sitk::sitkUnknown, sitk::sitkVectorUInt16, -16 >::Value:
    case sitk::ConditionalValue< sitk::sitkUInt16 != sitk::sitkUnknown, sitk::sitkUInt16, -4 >::Value:
      sitkBufferPtr = (void *)sitkImage.GetBufferAsUInt16();
      break;
    case sitk::ConditionalValue< sitk::sitkVectorInt16 != sitk::sitkUnknown, sitk::sitkVectorInt16, -17 >::Value:
    case sitk::ConditionalValue< sitk::sitkInt16 != sitk::sitkUnknown, sitk::sitkInt16, -5 >::Value:
      sitkBufferPtr = (void *)sitkImage.GetBufferAsInt16();
      break;
    case sitk::ConditionalValue< sitk::sitkVectorUInt32 != sitk::sitkUnknown, sitk::sitkVectorUInt32, -18 >::Value:
    case sitk::ConditionalValue< sitk::sitkUInt32 != sitk::sitkUnknown, sitk::sitkUInt32, -6 >::Value:
      sitkBufferPtr = (void *)sitkImage.GetBufferAsUInt32();
      break;
    case sitk::ConditionalValue< sitk::sitkVectorInt32 != sitk::sitkUnknown, sitk::sitkVectorInt32, -19 >::Value:
    case sitk::ConditionalValue< sitk::sitkInt32 != sitk::sitkUnknown, sitk::sitkInt32, -7 >::Value:
      sitkBufferPtr = (void *)sitkImage.GetBufferAsInt32();
      break;
    case sitk::ConditionalValue< sitk::sitkVectorUInt64 != sitk::sitkUnknown, sitk::sitkVectorUInt64, -20 >::Value:
    case sitk::ConditionalValue< sitk::sitkUInt64 != sitk::sitkUnknown, sitk::sitkUInt64, -8 >::Value:
      sitkBufferPtr = (void *)sitkImage.GetBufferAsUInt64();
      break;
    case sitk::ConditionalValue< sitk::sitkVectorInt64 != sitk::sitkUnknown, sitk::sitkVectorInt64, -21 >::Value:
    case sitk::ConditionalValue< sitk::sitkInt64 != sitk::sitkUnknown, sitk::sitkInt64, -9 >::Value:
      sitkBufferPtr = (void *)sitkImage.GetBufferAsInt64();
     break;
    case sitk::ConditionalValue< sitk::sitkVectorFloat32 != sitk::sitkUnknown, sitk::sitkVectorFloat32, -22 >::Value:
    case sitk::ConditionalValue< sitk::sitkFloat32 != sitk::sitkUnknown, sitk::sitkFloat32, -10 >::Value:
      sitkBufferPtr = (void *)sitkImage.GetBufferAsFloat();
      break;
    case sitk::ConditionalValue< sitk::sitkVectorFloat64 != sitk::sitkUnknown, sitk::sitkVectorFloat64, -23 >::Value:
    case sitk::ConditionalValue< sitk::sitkFloat64 != sitk::sitkUnknown, sitk::sitkFloat64, -11 >::Value:
      sitkBufferPtr = (void *)sitkImage.GetBufferAsDouble();
      break;
    case sitk::ConditionalValue< sitk::sitkComplexFloat32 != sitk::sitkUnknown, sitk::sitkComplexFloat32, -12 >::Value:
      //sitkBufferPtr = (void *)sitkImage.GetBufferAsComplexFloat32();
      break;
    case sitk::ConditionalValue< sitk::sitkComplexFloat64 != sitk::sitkUnknown, sitk::sitkComplexFloat64, -13 >::Value:
      //sitkBufferPtr = (void *)sitkImage.GetBufferAsComplexFloat64();
      break;
      break;
  default:
    ;
    }
  return sitkBufferPtr;
}


::testing::AssertionResult VectorDoubleRMSPredFormat(const char* expr1,
                                                     const char* expr2,
                                                     const char* rms_error_expr,
                                                     const std::vector<double> &val1,
                                                     const std::vector<double> &val2,
                                                     double rms_error) {
  if (val1.size() != val2.size())
    {
    return testing::AssertionFailure()
      << "The size of " << expr1 << " and " << expr2
      << " different, where\n"
      << expr1 << " evaluates to " << val1 << ",\n"
      << expr2 << " evaluates to " << val2 << ".";

    }
  double total = 0.0;
  for ( unsigned int i = 0; i < val1.size(); ++i )
    {
    double temp = (val1[i]-val2[i]);
    total += temp*temp;
    }
  const double rms = sqrt(total);
  if (rms <= rms_error) return ::testing::AssertionSuccess();

  return ::testing::AssertionFailure()
      << "The RMS difference between " << expr1 << " and " << expr2
      << " is " << rms << ",\n  which exceeds " << rms_error_expr << ", where\n"
      << expr1 << " evaluates to " << val1 << ",\n"
      << expr2 << " evaluates to " << val2 << ", and\n"
      << rms_error_expr << " evaluates to " << rms_error << ".";
}
