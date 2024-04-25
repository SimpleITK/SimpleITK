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
#ifndef __SimpleITKTestHarness_h
#define __SimpleITKTestHarness_h


#include <ostream>
#include <vector>
#include <iterator>
#include <algorithm>

// This is needed before the gtest include for lookup of the operator
// to work with clang 5.1
template <typename T>
inline std::ostream &
operator<<(std::ostream & os, const std::vector<T> & v)
{
  if (v.empty())
  {
    return os << "[ ]";
  }

  os << "[ ";
  std::copy(v.begin(), v.end() - 1, std::ostream_iterator<T>(os, ", "));
  return os << v.back() << " ]";
}

#include <string>
#include <vector>
#include <gtest/gtest.h>

#include "sitkImage.h"
#include "sitkCommand.h"
#include "sitkLogger.h"

// Class to help us find test data
//
/*
 * DataFinder maintains several directory paths.  It also
 * helps us find executables.
 *
 * Set/GetDirectory  -- Test Data directory
 *                      should be ITK/Testing/Data
 * Set/GetOutputDirectory -- Temporary directory
 *                      SimpleITK-build/Testing/Temporary
 * GetOutputFile --     File in the temp directory
 * GetBuildDirectory -- SimpleITK-build
 *                      Returns GetExecutableDirectory + "/" + filename
 */
class DataFinder
{

public:
  DataFinder();

  void
  SetDirectory(const char * dir);

  void
  SetDirectory(std::string dir);

  void
  SetOutputDirectory(std::string dir);

  std::string
  GetDirectory() const;
  std::string
  GetOutputDirectory() const;
  std::string
  GetOutputFile(std::string filename) const;
  std::string
  GetBuildDirectory() const;
  std::string
  GetPathSeparator() const;


  bool
  FileExists(const std::string & filename) const;

  std::string
  GetFile(const std::string & filename) const;

protected:
  std::string mDirectory;
  std::string mOutputDirectory;
  std::string mRuntimeDirectory;
};

extern DataFinder dataFinder;


// A mockup of a logger which saves messages to strings.
class MockLogger : public itk::simple::LoggerBase
{
public:
  MockLogger() = default;

  ~MockLogger() override = default;

  void
  DisplayText(const char * t) override
  {
    m_DisplayText << t;
  }

  void
  DisplayErrorText(const char * t) override
  {
    m_DisplayErrorText << t;
  }

  void
  DisplayWarningText(const char * t) override
  {
    m_DisplayWarningText << t;
  }

  void
  DisplayGenericOutputText(const char * t) override
  {
    m_DisplayGenericOutputText << t;
  }

  void
  DisplayDebugText(const char * t) override
  {
    m_DisplayDebugText << t;
  }

  void
  Clear()
  {
    m_DisplayText.str("");
    m_DisplayErrorText.str("");
    m_DisplayWarningText.str("");
    m_DisplayGenericOutputText.str("");
    m_DisplayDebugText.str("");
  }

  std::stringstream m_DisplayText;
  std::stringstream m_DisplayErrorText;
  std::stringstream m_DisplayWarningText;
  std::stringstream m_DisplayGenericOutputText;
  std::stringstream m_DisplayDebugText;
};

/** Base Command Class which holds onto a process object
 */
class ProcessObjectCommand : public itk::simple::Command
{
public:
  ProcessObjectCommand(itk::simple::ProcessObject & po);

protected:
  itk::simple::ProcessObject & m_Process;
};

/** Print the progress to the std::cout
 */
class ProgressUpdate : public ProcessObjectCommand
{
public:
  ProgressUpdate(itk::simple::ProcessObject & po);

  void
  Execute() override;

  float m_Progress;
};

/** Command which will invoke ProcessObject::Abort when AbortAt
 * progress is reached.
 */
class AbortAtCommand : public ProcessObjectCommand
{
public:
  AbortAtCommand(itk::simple::ProcessObject & po, float abortAt);

  void
  Execute() override;

  float m_AbortAt;
};

/** Command which counts the number of time the command has been
 * invoked.
 */
class CountCommand : public ProcessObjectCommand
{
public:
  CountCommand(itk::simple::ProcessObject & po);

  void
  Execute() override;

  int m_Count;
};


inline std::vector<double>
v2(double v1, double v2)
{
  return std::vector<double>{ v1, v2 };
}

inline std::vector<double>
v3(double v1, double v2, double v3)
{
  return std::vector<double>{ v1, v2, v3 };
}

inline std::vector<double>
v4(double v1, double v2, double v3, double v4)
{
  return std::vector<double>{ v1, v2, v3, v4 };
}


inline std::vector<double>
v5(double v1, double v2, double v3, double v4, double v5)
{
  return std::vector<double>{ v1, v2, v3, v4, v5 };
}

inline std::vector<double>
v6(double v1, double v2, double v3, double v4, double v5, double v6)
{
  return std::vector<double>{ v1, v2, v3, v4, v5, v6 };
}

inline std::vector<double>
v7(double v1, double v2, double v3, double v4, double v5, double v6, double v7)
{
  return std::vector<double>{ v1, v2, v3, v4, v5, v6, v7 };
}


inline std::vector<double>
v9(double v1, double v2, double v3, double v4, double v5, double v6, double v7, double v8, double v9)
{
  return std::vector<double>{ v1, v2, v3, v4, v5, v6, v7, v8, v9 };
}

inline std::vector<double>
v12(double v1,
    double v2,
    double v3,
    double v4,
    double v5,
    double v6,
    double v7,
    double v8,
    double v9,
    double v10,
    double v11,
    double v12)
{
  return std::vector<double>{ v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12 };
}


::testing::AssertionResult
VectorDoubleRMSPredFormat(const char *                expr1,
                          const char *                expr2,
                          const char *                rms_error_expr,
                          const std::vector<double> & val1,
                          const std::vector<double> & val2,
                          double                      rms_error);

template <typename T1, typename T2>
::testing::AssertionResult
VectorRMSPredFormat(const char *            expr1,
                    const char *            expr2,
                    const char *            rms_error_expr,
                    const std::vector<T1> & val1,
                    const std::vector<T2> & val2,
                    double                  rms_error)
{
  if (val1.size() != val2.size())
  {
    return testing::AssertionFailure() << "The size of " << expr1 << " and " << expr2 << " different, where\n"
                                       << expr1 << " evaluates to " << val1 << ",\n"
                                       << expr2 << " evaluates to " << val2 << ".";
  }
  double total = 0.0;
  for (unsigned int i = 0; i < val1.size(); ++i)
  {
    const double temp = static_cast<double>(val1[i] - val2[i]);
    total += temp * temp;
  }
  const double rms = sqrt(total);
  if (rms <= rms_error)
    return ::testing::AssertionSuccess();

  return ::testing::AssertionFailure() << "The RMS difference between " << expr1 << " and " << expr2 << " is " << rms
                                       << ",\n  which exceeds " << rms_error_expr << ", where\n"
                                       << expr1 << " evaluates to " << val1 << ",\n"
                                       << expr2 << " evaluates to " << val2 << ", and\n"
                                       << rms_error_expr << " evaluates to " << rms_error << ".";
}


#define EXPECT_VECTOR_DOUBLE_NEAR(val1, val2, rms_error) \
  EXPECT_PRED_FORMAT3(VectorDoubleRMSPredFormat, val1, val2, rms_error)

/** A custom GTest macro for comparing 2 std vector-like objects. This
 * verifies that the root mean squares error between the two array-like
 * objects doesn't exceed the given error.
 */
#define EXPECT_VECTOR_NEAR(val1, val2, rms_error) EXPECT_PRED_FORMAT3(VectorRMSPredFormat, val1, val2, rms_error)


#include "sitkImageCompare.h"

#endif
