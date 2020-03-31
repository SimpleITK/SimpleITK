
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
