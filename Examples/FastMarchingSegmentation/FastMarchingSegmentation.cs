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

//INPUTS:  {BrainProtonDensitySlice.png}
//    OUTPUTS: {FastMarchingImageFilterOutput5.png}
//    ARGUMENTS:    81 114 1.0  -0.5  3.0   100 100


using System;

using SitkImage = itk.simple.Image;
using System.Globalization;

namespace itk.simple.examples
{
    public class FastMarchingSegmentation
    {
        static void Main(string[] args)
        {
            if (args.Length < 9)
            {
                Console.WriteLine("Missing Parameters ");
                Console.WriteLine("Usage: " + System.AppDomain.CurrentDomain.FriendlyName +
                                  " inputImage outputImage seedX seedY " +
                                  " Sigma SigmoidAlpha SigmoidBeta TimeThreshold");
                return;
            }

            string inputFilename = args[0];
            string outputFilename = args[1];

            uint[] seedPosition = { Convert.ToUInt32(args[2]), Convert.ToUInt32(args[3]),0 };

            double sigma = double.Parse(args[4], CultureInfo.InvariantCulture);
            double alpha = double.Parse(args[5], CultureInfo.InvariantCulture); ;
            double beta = double.Parse(args[6], CultureInfo.InvariantCulture);
            double timeThreshold = double.Parse(args[7], CultureInfo.InvariantCulture);
            double stoppingTime = double.Parse(args[8], CultureInfo.InvariantCulture);

            // Read input image

            SitkImage inputImage = SimpleITK.ReadImage(inputFilename, PixelIDValueEnum.sitkFloat32);

            //  The input image will be processed with a few iterations of
            //  feature-preserving diffusion.  We create a filter and set the
            //  appropriate parameters.

            CurvatureAnisotropicDiffusionImageFilter smoothing = new CurvatureAnisotropicDiffusionImageFilter();
            smoothing.SetTimeStep(0.125);
            smoothing.SetNumberOfIterations(5);
            smoothing.SetConductanceParameter(9.0);
            SitkImage smoothingOutput = smoothing.Execute(inputImage);

            SitkImage gradientMagnitudeOutput = SimpleITK.GradientMagnitudeRecursiveGaussian(smoothingOutput, sigma);

            SitkImage sigmoidOutput = SimpleITK.Sigmoid(gradientMagnitudeOutput, alpha, beta, 1.0, 0.0);


            FastMarchingImageFilter fastMarching = new FastMarchingImageFilter();

            //VectorUIntList trialPoints; Add trialPoints into list if using multiple seeds. Here we only use one seedpoint

            VectorUInt32 trialPoint = new VectorUInt32(3);
            trialPoint.Add(seedPosition[0]);
            trialPoint.Add(seedPosition[1]);
            trialPoint.Add(seedPosition[2]);

            fastMarching.AddTrialPoint(trialPoint);

            //  Since the front representing the contour will propagate continuously
            //  over time, it is desirable to stop the process once a certain time has
            //  been reached. This allows us to save computation time under the
            //  assumption that the region of interest has already been computed. The
            //  value for stopping the process is defined with the method
            //  SetStoppingValue(). In principle, the stopping value should be a
            //  little bit higher than the threshold value.

            fastMarching.SetStoppingValue(stoppingTime);

            SitkImage fastmarchingOutput = fastMarching.Execute(sigmoidOutput);

            BinaryThresholdImageFilter thresholder = new BinaryThresholdImageFilter();
            thresholder.SetLowerThreshold(0.0);
            thresholder.SetUpperThreshold(timeThreshold);
            thresholder.SetOutsideValue(0);
            thresholder.SetInsideValue(255);
            SitkImage result = thresholder.Execute(fastmarchingOutput);

            SimpleITK.WriteImage(result, outputFilename);

        }
    }
}
