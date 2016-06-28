
#include "SimpleITKTestHarness.h"


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
