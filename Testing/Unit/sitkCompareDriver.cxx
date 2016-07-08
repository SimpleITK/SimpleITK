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

#include "SimpleITK.h"
#include "SimpleITKTestHarness.h"

#include "sitkTransformCompare.h"

#include "itksys/Process.h"
#include <iostream>

DataFinder dataFinder;

namespace sitk = itk::simple;

struct TransformCompareType
{
  char * transform;
  char * displacement;
  float tolerance;
};
typedef std::vector< char * > ArgumentsList;
typedef char ** ArgumentStringType;

// A structure to hold regression test parameters
typedef struct
{
  std::vector< TransformCompareType > transformTestList;
  double intensityTolerance;
  unsigned int numberOfPixelsTolerance;
  unsigned int radiusTolerance;
} RegressionTestParameters;

RegressionTestParameters regressionTestParameters;



struct ProcessedOutputType
{
  bool externalProcessMustBeCalled;

  ArgumentsList args;
};

void usage()
{
  std::cerr << "usage: sitkCompareDriver [options] -- prg [args]" << std::endl;
  std::cerr << "       sitkCompareDriver [options]" << std::endl;
  std::cerr << std::endl;
  std::cerr << "sitkTestDriver run a test program and compare the images or transforms" << std::endl;
  std::cerr << "produced." << std::endl;
  std::cerr << std::endl;
  std::cerr << "Options:" << std::endl;
  std::cerr << "  --compareTransform TRANSFORM DISPLACEMENT [tolerance]" << std::endl;
  std::cerr << "      Compare a test TRANSFORM file to a displacement field image." << std::endl;
  std::cerr << "      The displacement of the TRANSFORM is sampled onto the domain of the DISPLACEMENT image." << std::endl;
  std::cerr << "       The optional tolerance is a root mean squares of the difference between the displacement fields." << std::endl;
  std::cerr << std::endl;
  std::cerr << "  --full-output" << std::endl;
  std::cerr << "      Causes the full output of the test to be passed to cdash." << std::endl;
  std::cerr << std::endl;
  std::cerr << "  --" << std::endl;
  std::cerr << "      The options after -- are not interpreted by this program and passed" << std::endl;
  std::cerr << "      directly to the test program." << std::endl;
  std::cerr << std::endl;
  std::cerr << "  --help" << std::endl;
  std::cerr << "      Display this message and exit." << std::endl;
  std::cerr << std::endl;
}


int TestDriverInvokeProcess(  const ArgumentsList & args )
{
  // a ITK_NULLPTR is required at the end of the table
  char ** argv = new char *[args.size() + 1];
  for ( unsigned int i = 0; i < args.size(); i++ )
    {
    argv[i] = args[i];
    }
  argv[args.size()] = SITK_NULLPTR;

  itksysProcess *process = itksysProcess_New();
  itksysProcess_SetCommand(process, argv);
  itksysProcess_SetPipeShared(process, itksysProcess_Pipe_STDOUT, true);
  itksysProcess_SetPipeShared(process, itksysProcess_Pipe_STDERR, true);
  itksysProcess_Execute(process);
  itksysProcess_WaitForExit(process, SITK_NULLPTR);

  delete[] argv;

  int state = itksysProcess_GetState(process);
  switch( state )
    {
    case itksysProcess_State_Error:
      {
      std::cerr << "sitkCompareDriver: Process error: " << itksysProcess_GetErrorString(process) << std::endl;
      itksysProcess_Delete(process);
      return 1;
      }
    case itksysProcess_State_Exception:
      {
      std::cerr << "sitkCompareDriver: Process exception: " << itksysProcess_GetExceptionString(process) << std::endl;
      itksysProcess_Delete(process);
      return 1;
      }
    case itksysProcess_State_Executing:
      {
      // this is not a possible state after itksysProcess_WaitForExit
      std::cerr << "sitkCompareDriver: Internal error: process can't be in Executing State." << std::endl;
      itksysProcess_Delete(process);
      return 1;
      }
    case itksysProcess_State_Exited:
      {
      // this is the normal case - it is treated later
      break;
      }
    case itksysProcess_State_Expired:
      {
      // this is not a possible state after itksysProcess_WaitForExit
      std::cerr << "sitkCompareDriver: Internal error: process can't be in Expired State." << std::endl;
      itksysProcess_Delete(process);
      return 1;
      }
    case itksysProcess_State_Killed:
      {
      std::cerr << "sitkCompareDriver: The process has been killed." << std::endl;
      itksysProcess_Delete(process);
      return 1;
      }
    case itksysProcess_State_Disowned:
      {
      std::cerr << "sitkCompareDriver: Process disowned." << std::endl;
      itksysProcess_Delete(process);
      return 1;
      }
    default:
      {
      // this is not a possible state after itksysProcess_WaitForExit
      std::cerr << "sitkCompareDriver: Internal error: unknown State." << std::endl;
      itksysProcess_Delete(process);
      return 1;
      }
    }

  int retCode = itksysProcess_GetExitValue(process);
  if ( retCode != 0 )
    {
    std::cerr << "sitkCompareDriver: Process exited with return value: " << retCode << std::endl;
    }
  itksysProcess_Delete(process);
return retCode;
}



int ProcessArguments(int *ac, ArgumentStringType *av, ProcessedOutputType * processedOutput = SITK_NULLPTR )
{

  regressionTestParameters.intensityTolerance  = 2.0;
  regressionTestParameters.numberOfPixelsTolerance = 0;
  regressionTestParameters.radiusTolerance = 0;

  if( processedOutput )
    {
    processedOutput->externalProcessMustBeCalled = false;
    }

  // parse the command line
  int  i = 1;
  bool skip = false;
  while ( i < *ac )
  {
     if ( !skip && strcmp((*av)[i], "--") == 0 )
      {
      skip = true;
      i += 1;
      }
    else if ( !skip && strcmp((*av)[i], "--help") == 0 )
      {
      usage();
      return 1;
      }
    else if ( !skip && strcmp((*av)[i], "--compareTransform") == 0 )
      {
      if ( i + 2 >= *ac )
        {
        usage();
        return 1;
        }
      char * transform = (*av)[i + 1];
      char * displacement = (*av)[i + 2];
      (*av) += 3;
      *ac -= 3;

      float tolerance = 0.0;
      if (i  < *ac && strncmp((*av)[i], "--", 2) != 0)
        {
        const float f = atof( (*av)[i] );

        if ( f == 0.0 )
          usage();

        tolerance = f;
        ++(*av);
        --(*ac);
        }

      TransformCompareType c = {transform, displacement, tolerance};
      regressionTestParameters.transformTestList.push_back( c );
      }
    else if ( !skip && strcmp((*av)[i], "--full-output") == 0 )
      {
      // emit the string to tell ctest that the full output should be
      // passed to cdash.
      std::cout << "CTEST_FULL_OUTPUT" << std::endl;
      (*av) += 1;
      *ac -= 1;
      }
    else if ( !skip && strcmp((*av)[i], "--no-process") == 0 )
      {
      // The test driver needs to invoke another executable
      // For example, the python interpreter to run Wrapping tests.
      if( processedOutput )
        {
        processedOutput->externalProcessMustBeCalled = false;
        }
      (*av) += 1;
      *ac -= 1;
      }
    else if ( skip &&  processedOutput )
      {
      processedOutput->externalProcessMustBeCalled = true;
      processedOutput->args.push_back((*av)[i]);
      i += 1;
      }
    else
      {
      std::cerr << "Unhandled argument \"" << (*av)[i] << "\"." << std::endl;
      usage();
      return 1;
      }
  }

  return 0;
}




int main(int argc, char *argv[])
{

  ProcessedOutputType po;

  int result = ProcessArguments(&argc, &argv, &po);

  if( result )
    {
    // There was a problem parsing the arguments, so usage has already
    // been printed, just return
    return EXIT_FAILURE;
    }

  if ( po.externalProcessMustBeCalled && po.args.empty() )
    {
    usage();
    return 1;
    }

  if ( !po.externalProcessMustBeCalled && !po.args.empty() )
    {
    std::cerr << "args: " << po.args[0] << std::endl;
    usage();
    return 1;
    }

  if ( !result && po.externalProcessMustBeCalled )
    {
    result = TestDriverInvokeProcess( po.args );
    }

  if( result==0 )
    {

    // compare transforms
    for (size_t i = 0; i < regressionTestParameters.transformTestList.size(); ++i )
      {
      const char * transformFileName =  regressionTestParameters.transformTestList[i].transform;
      const char * baselineFileName = regressionTestParameters.transformTestList[i].displacement;
      const float tolerance = regressionTestParameters.transformTestList[i].tolerance;
      std::cout << "Reading test transform: \"" <<  transformFileName << "\"..." << std::endl;
      sitk::Transform transform = sitk::ReadTransform(transformFileName);

      std::cout << "Reading baseline displacement: \"" << baselineFileName << "\"..." << std::endl;
      sitk::Image baseline = sitk::ReadImage(baselineFileName);

      TransformCompare compare;
      compare.SetTolerance(tolerance);
      if (!compare.Compare(transform, baseline))
        {
        result += 1;
        }
      }


    }


  return result;
}
