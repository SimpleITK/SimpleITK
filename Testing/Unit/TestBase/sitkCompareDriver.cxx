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

#include "SimpleITK.h"
#include "SimpleITKTestHarness.h"

#include "sitkTransformCompare.h"

#include "itksys/Process.h"
#include "itksys/SystemTools.hxx"
#include <iostream>


namespace sitk = itk::simple;

// declared in SimpleITKTestHarness
DataFinder dataFinder;

namespace
{



struct TransformCompareType
{
  char * transform;
  char * displacement;
  float tolerance;
};

struct CompareType
{
  char * test;
  char * baseline;
  float tolerance;
};

using HashPairType = std::pair< const char *, std::vector<std::string> >;
using ArgumentsList = std::vector< char * >;
using ArgumentStringType = char **;

// A structure to hold regression test parameters
typedef struct
{
  std::vector< CompareType > compareList;
  std::vector< HashPairType > hashTestList;
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

char my_to_lower(const char c)
{
  return static_cast<char>( ::tolower(c));
}

void usage()
{
  std::cerr << "usage: sitkCompareDriver [options] -- prg [args]" << std::endl;
  std::cerr << "       sitkCompareDriver [options]" << std::endl;
  std::cerr << std::endl;
  std::cerr << "sitkCompareDriver is used to compare images and transforms to baselines for testing. Optionally, it can run a test program to produce output to test." << std::endl;
  std::cerr << std::endl;
// The name of these parameters are compatible with the name of the
// itkTestDriver arguments.
  std::cerr << "Options:" << std::endl;
  std::cerr << "  --compare TEST BASELINE [tolerance]" << std::endl;
  std::cerr << "      Compare the TEST image to the BASELINE one." << std::endl;
  std::cerr << "      This option can be used several times." << std::endl;
  std::cerr << std::endl;
  std::cerr << "  --compare-MD5 TEST md5hash0 [ md5hash1 ... ]" << std::endl;
  std::cerr << "      Compare the TEST image file's md5 hash to the provided hash." << std::endl;
  std::cerr << "      md5hash0 is required and assumed to be a hash." << std::endl;
  std::cerr << "      Additional arguments are considered hashes when the string is 32 hexi-decimal characters. " << std::endl;
  std::cerr << "      This option can be used several times for multiple comparisons." << std::endl;
  std::cerr << std::endl;
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
    std::cout << argv[i] << " ";
    }

  std::cout << std::endl;
  argv[args.size()] = nullptr;

#ifdef DEBUG
  std::cout << "Invoke Process: ";
  for ( unsigned int i = 0; i < args.size(); i++ )
    {
    std::cout << argv[i] << " ";
    }
  std::cout << std::endl;
#endif


  itksysProcess *process = itksysProcess_New();
  itksysProcess_SetCommand(process, argv);
  itksysProcess_SetPipeShared(process, itksysProcess_Pipe_STDOUT, true);
  itksysProcess_SetPipeShared(process, itksysProcess_Pipe_STDERR, true);
  itksysProcess_Execute(process);
  itksysProcess_WaitForExit(process, nullptr);

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



int ProcessArguments(int *ac, ArgumentStringType *av, ProcessedOutputType * processedOutput = nullptr )
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
     if ( !skip && strcmp((*av)[i], "--compare") == 0 )
      {
      if ( i + 2 >= *ac )
        {
        usage();
        return 1;
        }
      char * test = (*av)[i + 1];
      char * baseline = (*av)[i + 2];

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

      std::cout << "Image Compare: " << test << " " << baseline << " " << tolerance << std::endl;
      CompareType c = {test, baseline, tolerance};
      regressionTestParameters.compareList.push_back( c );
      }
     else if ( !skip && strcmp((*av)[i], "--compare-MD5") == 0 )
      {

      if ( i + 2 >= *ac )
        {
        usage();
        return 1;
        }
      const char *filename = (*av)[i + 1];
      std::string md5hash0 =  (*av)[i + 2];

     // convert hash to all lowercase letters
     std::transform(md5hash0.begin(), md5hash0.end(), md5hash0.begin(), my_to_lower );

     // check that the hash is of expected format
     if ( md5hash0.size() != 32 ||
          md5hash0.find_first_not_of( "0123456789abcdef" ) != std::string::npos )
       {
       std::cerr << "Warning: argument does not appear to be a valid md5 hash \"" << md5hash0 << "\"." << std::endl;
       }

     std::vector< std::string > hashVector;
     hashVector.push_back( md5hash0 );

     (*av) += 3;
     (*ac) -= 3;

     // continue eating hash values
     while ( *ac - i > 0 )
       {
       std::string md5hashN = (*av)[i];

       // convert hash to all lowercase letters
       std::transform(md5hashN.begin(), md5hashN.end(), md5hashN.begin(), my_to_lower );

       // check if the next argument is a hash
       if ( md5hashN.size() != 32 ||
            md5hashN.find_first_not_of( "0123456789abcdef" ) != std::string::npos )
         {
         break;
         }
       // add the hash
       hashVector.push_back( md5hashN );

       // successful hash,
       // move the arguments along
       ++(*av);
       --(*ac);
       }

       std::cout << "Image Hash: " << filename;
       for(unsigned int j = 0; j < hashVector.size(); ++j)
         {
         std::cout << " " << hashVector[j];
         }
       std::cout << std::endl;
       regressionTestParameters.hashTestList.emplace_back( filename, hashVector  );

      }
    else if ( !skip && strcmp((*av)[i], "--") == 0 )
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

      std::cout << "Transform Compare: " << transform << " " << displacement << " " << tolerance << std::endl;
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

// For a baselineFilename of 'something.ext' search for existing files with names of the format 'something.#.ext'
// starting at 1, until the filename does not exist. Then return a list the existing files discovered.
std::vector<std::string> GetExistingBaselineFileNames( const std::string &baselineFilename )
{
    // Generate all possible baseline file names

    const std::string extension = itksys::SystemTools::GetFilenameLastExtension(baselineFilename);
    const std::string name = itksys::SystemTools::GetFilenameWithoutLastExtension(baselineFilename);
    const std::string path = itksys::SystemTools::GetFilenamePath(baselineFilename);
    std::vector<std::string> baselineFilenames;
    baselineFilenames.push_back(baselineFilename);

    int x = 0;

    while (++x) {
        std::ostringstream filename_stream;
        filename_stream << path << "/"
                        << name << "." << x << extension;

        const std::string filename(filename_stream.str());

        if (!itksys::SystemTools::FileExists(filename, true)) {
            break;
        }
        baselineFilenames.push_back(filename);
    }

    return baselineFilenames;
}

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

    // check md5 hashes
    for (size_t i = 0; i < regressionTestParameters.hashTestList.size(); ++i )
      {
      const char * const testFilename = regressionTestParameters.hashTestList[i].first;
      const std::vector<std::string> &hashTestList = regressionTestParameters.hashTestList[i].second;

      std::cout << "Reading test image: \"" <<  testFilename << "\"..." << std::endl;
      const sitk::Image testImage = sitk::ReadImage(testFilename);
      const std::string actualHashValue = itk::simple::Hash( testImage, itk::simple::HashImageFilter::MD5 ); \

      const bool passed = std::find(hashTestList.begin(), hashTestList.end(), actualHashValue) != hashTestList.end();

      if (!passed)
        {
        const std::string TestImageFilename = dataFinder.GetOutputFile ( actualHashValue + ".png");
        try
          {
          sitk::Image testSlice = ImageCompare::extractSlice(testImage);
          ImageCompare::NormalizeAndSave( testSlice, TestImageFilename );

          std::cout << "<DartMeasurementFile name=\"TestImage\" type=\"image/png\">";
          std::cout << TestImageFilename << "</DartMeasurementFile>" << std::endl;
          }
        catch (std::exception &e)
          {
          std::cerr << "Unexpected error while writing image:" << e.what() << std::endl;
          }
        catch (...)
          {
          std::cerr << "Unknown Error while writing image for measurement" << std::endl;
          }
        const std::string outFileName =  dataFinder.GetOutputFile ( actualHashValue + ".nrrd" );
        itk::simple::WriteImage( testImage, outFileName);
        std::cerr << "Saved actual image as " << outFileName << std::endl;
        ++result;
        }
      }

      // compare transforms
      for (size_t i = 0; i < regressionTestParameters.transformTestList.size(); ++i)
      {
        const char * transformFileName = regressionTestParameters.transformTestList[i].transform;
        const char * baselineFileName = regressionTestParameters.transformTestList[i].displacement;
        const float  tolerance = regressionTestParameters.transformTestList[i].tolerance;


        std::cout << "Reading test transform: \"" << transformFileName << "\"..." << std::endl;
        sitk::Transform transform = sitk::ReadTransform(transformFileName);

        // Generate all possible baseline file names
        const std::vector<std::string> baselineFilenames = GetExistingBaselineFileNames(baselineFileName);

        std::string bestBaselineName = *baselineFilenames.begin();
        float       bestRMS = std::numeric_limits<float>::max();


        std::vector<std::string>::const_iterator iterName;
        for (iterName = baselineFilenames.begin(); iterName != baselineFilenames.end(); ++iterName)
        {
          sitk::Image baseline(0, 0, sitk::sitkUInt8);
          float       RMS = -1.0;

          try
          {

            std::cout << "Reading baseline displacement: \"" << *iterName << "\"..." << std::endl;
            baseline = sitk::ReadImage(*iterName);
          }
          catch (std::exception & e)
          {
            std::cerr << "Failed to load transform " + *iterName + " because: " + e.what();
            continue;
          }

          TransformCompare compare;
          compare.SetTolerance(tolerance);

          RMS = compare.Compare(transform, baseline, false);
          std::string shortFileName = itksys::SystemTools::GetFilenameName(*iterName);
          std::cout << "<DartMeasurement name=\"RMSDifference " << shortFileName << "\" type=\"numeric/float\">" << RMS
                    << "</DartMeasurement>" << std::endl;

          if (RMS == -1.0)
          {
            std::cerr << compare.GetMessage() << std::endl;
          }
          else if (RMS >= 0.0 && RMS < bestRMS)
          {
            bestBaselineName = *iterName;
            bestRMS = RMS;
          }
        }

        if ( bestRMS > fabs ( tolerance ) )
        {
            TransformCompare compare;
            compare.SetTolerance(tolerance);

            const sitk::Image baseline =  sitk::ReadImage( bestBaselineName );
            compare.Compare( transform, baseline, true );

            ++result;
        }
    }

    // compare images
    for (size_t i = 0; i < regressionTestParameters.compareList.size(); ++i )
      {
      const char * const testFilename = regressionTestParameters.compareList[i].test;
      const char * const baselineFilename = regressionTestParameters.compareList[i].baseline;
      float tolerance = regressionTestParameters.compareList[i].tolerance;

      std::cout << "Reading test image: \"" <<  testFilename << "\"..." << std::endl;
      sitk::Image test = sitk::ReadImage(testFilename);

      ImageCompare imageCompare;
      imageCompare.setTolerance(tolerance);

      // Generate all possible baseline file names
      const std::vector<std::string> baselineFilenames = GetExistingBaselineFileNames( baselineFilename );

      std::vector<std::string>::const_iterator iterName;
      std::string bestBaselineName =  *baselineFilenames.begin();
      float bestRMS = std::numeric_limits<float>::max();

      const sitk::Image testSlice = ImageCompare::extractSlice(test);

      for ( iterName = baselineFilenames.begin(); iterName != baselineFilenames.end(); ++iterName )
        {

        sitk::Image baseline( 0, 0, sitk::sitkUInt8 );

        try
          {
          std::cout << "Reading baseline image: \"" <<  *iterName << "\"..." << std::endl;
          baseline = sitk::ReadImage(*iterName );
          }
        catch ( std::exception& e )
          {
          std::cerr << "Failed to load image " +*iterName + " because: " + e.what();
          continue;
          }

        float RMS = -1.0;
        std::cout << "Slice Dim: " << testSlice.GetDimension() << std::endl;
        if (baseline.GetSize() != test.GetSize())
          {
          std::cout << "Using Extracted Slice for comparison." << std::endl;
          RMS = imageCompare.testImages(testSlice, baseline, false,  *iterName);
          }
        else
          {
          RMS = imageCompare.testImages(test, baseline, false,  *iterName);
          }

        if ( RMS == -1.0 )
          {
          std::cerr << imageCompare.getMessage() << std::endl;
          }
        else if ( RMS >= 0.0 && RMS < bestRMS )
          {
          bestBaselineName = *iterName;
          bestRMS = RMS;
          }

        }

      if ( bestRMS > fabs ( tolerance ) )
        {
          const sitk::Image baseline =  sitk::ReadImage( bestBaselineName );
          if (baseline.GetSize() != test.GetSize())
            {
            imageCompare.testImages( testSlice, baseline, true, bestBaselineName );
            }
          else
            {
            imageCompare.testImages(test, baseline, true,  bestBaselineName);
            }
          ++result;
        }

      }

    }


  return result;
}
