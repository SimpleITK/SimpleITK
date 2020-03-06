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

// This example is based on ITK's FastMarchingImageFilter.cxx example


#include <SimpleITK.h>
#include <iostream>
#include <string>
#include <cstdlib>

namespace sitk = itk::simple;


int main(int argc, char *argv[])
{

  if ( argc < 10 )
    {
    std::cerr << "Missing Parameters " << std::endl;
    std::cerr << "Usage: " << argv[0];
    std::cerr << " inputImage  outputImage seedX seedY";
    std::cerr << " Sigma SigmoidAlpha SigmoidBeta TimeThreshold StoppingTime" << std::endl;

    return EXIT_FAILURE;
    }

  const std::string inputFilename(argv[1]);
  const std::string outputFilename(argv[2]);

  unsigned int seedPosition[2];
  seedPosition[0] = atoi( argv[3] );
  seedPosition[1] = atoi( argv[4] );

  const double sigma = atof( argv[5] );
  const double alpha =  atof( argv[6] );
  const double beta  =  atof( argv[7] );
  const double timeThreshold = atof( argv[8] );
  const double stoppingTime = atof( argv[9] );

  sitk::Image inputImage = sitk::ReadImage( inputFilename, sitk::sitkFloat32 );


  sitk::CurvatureAnisotropicDiffusionImageFilter smoothing;
  smoothing.SetTimeStep( 0.125 );
  smoothing.SetNumberOfIterations(  5 );
  smoothing.SetConductanceParameter( 9.0 );
  sitk::Image smoothingOutput = smoothing.Execute( inputImage );

  sitk::GradientMagnitudeRecursiveGaussianImageFilter gradientMagnitude;
  gradientMagnitude.SetSigma(  sigma  );
  sitk::Image gradientMagnitudeOutput = gradientMagnitude.Execute( smoothingOutput );

  sitk::SigmoidImageFilter sigmoid;
  sigmoid.SetOutputMinimum(  0.0  );
  sigmoid.SetOutputMaximum(  1.0  );
  sigmoid.SetAlpha( alpha );
  sigmoid.SetBeta(  beta  );
  sitk::Image sigmoidOutput = sigmoid.Execute( gradientMagnitudeOutput );


  sitk::FastMarchingImageFilter fastMarching;

  std::vector< unsigned int > trialPoint(3);


  trialPoint[0] = seedPosition[0];
  trialPoint[1] = seedPosition[1];

  trialPoint[2] = 0u; // Seed Value

  fastMarching.AddTrialPoint( trialPoint );

  fastMarching.SetStoppingValue(stoppingTime);

  sitk::Image fastmarchingOutput = fastMarching.Execute( sigmoidOutput );


  sitk::BinaryThresholdImageFilter thresholder;
  thresholder.SetLowerThreshold(           0.0  );
  thresholder.SetUpperThreshold( timeThreshold  );
  thresholder.SetOutsideValue(  0  );
  thresholder.SetInsideValue(  255 );

  sitk::Image result = thresholder.Execute(fastmarchingOutput);

  sitk::WriteImage(result, outputFilename);

  return 0;
}
