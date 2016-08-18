/*=========================================================================
*
*  Copyright Insight Software Consortium
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
inline std::ostream& operator<< (std::ostream& os, const std::vector<double>& v)
 {
   if ( v.empty() )
     {
     return os << "[ ]";
     }

   os << "[ ";
   std::copy( v.begin(), v.end()-1, std::ostream_iterator<double>(os, ", ") );
   return os << v.back() << " ]";
 }

#include <string>
#include <vector>
#include <gtest/gtest.h>
#include <SimpleITKTestHarnessPaths.h>

#include "sitkImage.h"
#include "sitkCommand.h"

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
  DataFinder ();

  void SetDirectory ( const char* dir );

  void SetDirectory ( std::string dir );

  void SetOutputDirectory ( std::string dir );

  std::string GetDirectory () const;
  std::string GetOutputDirectory () const;
  std::string GetOutputFile ( std::string filename ) const;
  std::string GetBuildDirectory ()    const;
  std::string GetPathSeparator () const;


  bool FileExists ( const std::string &filename ) const;

  std::string GetFile ( const std::string &filename ) const;

protected:
  std::string mDirectory;
  std::string mOutputDirectory;
  std::string mRuntimeDirectory;
};

extern DataFinder dataFinder;



/** Base Command Class which holds onto a process object
 */
class ProcessObjectCommand
  : public itk::simple::Command
{
public:
  ProcessObjectCommand(itk::simple::ProcessObject &po);

protected:
  itk::simple::ProcessObject &m_Process;
};

/** Print the progress to the std::cout
 */
class ProgressUpdate
  : public ProcessObjectCommand
{
public:
  ProgressUpdate(itk::simple::ProcessObject &po);

  virtual void Execute( );

  float m_Progress;
};

/** Command which will invoke ProcessObject::Abort when AbortAt
 * progress is reached.
 */
class AbortAtCommand
  : public ProcessObjectCommand
{
public:
  AbortAtCommand(itk::simple::ProcessObject &po, float abortAt);

  virtual void Execute( );

  float m_AbortAt;
};

/** Command which counts the number of time the command has been
 * invoked.
 */
class CountCommand
  : public ProcessObjectCommand
{
public:
  CountCommand(itk::simple::ProcessObject &po);

  virtual void Execute( );

  int m_Count;
};



inline std::vector<double> v2(double v1, double v2)
{
  std::vector<double> temp(2);
  temp[0]=v1;temp[1]=v2;
  return temp;
}

inline std::vector<double> v3(double v1, double v2, double v3)
{
  std::vector<double> temp(3);
  temp[0]=v1;temp[1]=v2;temp[2]=v3;
  return temp;
}

inline std::vector<double> v4(double v1, double v2, double v3, double v4)
{
  std::vector<double> temp(4);
  temp[0]=v1;temp[1]=v2;temp[2]=v3;temp[3]=v4;
  return temp;
}

inline std::vector<double> v6(double v1, double v2, double v3,
                              double v4, double v5, double v6)
{
  std::vector<double> temp(6);
  temp[0]=v1;temp[1]=v2;temp[2]=v3;
  temp[3]=v4;temp[4]=v5;temp[5]=v6;
  return temp;
}


inline std::vector<double> v9(double v1, double v2, double v3,
                              double v4, double v5, double v6,
                              double v7, double v8, double v9)
{
  std::vector<double> temp(9);
  temp[0]=v1;temp[1]=v2;temp[2]=v3;
  temp[3]=v4;temp[4]=v5;temp[5]=v6;
  temp[6]=v7;temp[7]=v8;temp[8]=v9;
  return temp;
}

inline std::vector<double> v12(double v1, double v2, double v3,
                               double v4, double v5, double v6,
                               double v7, double v8, double v9,
                               double v10, double v11, double v12)
{
  std::vector<double> temp(12);
  temp[0]=v1;temp[1]=v2;temp[2]=v3;
  temp[3]=v4;temp[4]=v5;temp[5]=v6;
  temp[6]=v7;temp[7]=v8;temp[8]=v9;
  temp[9]=v10;temp[10]=v11;temp[11]=v12;
  return temp;
}


::testing::AssertionResult VectorDoubleRMSPredFormat(const char* expr1,
                                                     const char* expr2,
                                                     const char* rms_error_expr,
                                                     const std::vector<double> &val1,
                                                     const std::vector<double> &val2,
                                                     double rms_error);



#define EXPECT_VECTOR_DOUBLE_NEAR(val1, val2, rms_error)                \
  EXPECT_PRED_FORMAT3(VectorDoubleRMSPredFormat,                        \
                      val1, val2, rms_error)



#include "sitkImageCompare.h"

#endif
