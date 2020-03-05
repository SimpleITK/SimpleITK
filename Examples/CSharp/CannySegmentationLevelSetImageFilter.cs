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

using System;
using System.Globalization;

using PixelId = itk.simple.PixelIDValueEnum;
using SitkImage = itk.simple.Image;

namespace itk.simple.examples
{
    public class Program
    {
        static void Main(string[] args)
        {
            if (args.Length < 8)
            {
                Console.WriteLine("Missing Parameters ");
                Console.WriteLine("Usage: " + System.AppDomain.CurrentDomain.FriendlyName +
                                  "inputImage initialModel outputImage cannyThreshold " +
                                  "cannyVariance advectionWeight initialModelIsovalue maximumIterations ");
                return;
            }

            string inputFilename = args[0];
            string initialModelFilename = args[1];

            string outputFilename = args[2];

            double cannyThreshold = double.Parse(args[3], CultureInfo.InvariantCulture);
            double cannyVariance = double.Parse(args[4], CultureInfo.InvariantCulture);
            double advectionWeight = double.Parse(args[5], CultureInfo.InvariantCulture);
            double intialModelIsovalue = double.Parse(args[6], CultureInfo.InvariantCulture);
            uint maxIterations = uint.Parse(args[7], CultureInfo.InvariantCulture);

            // Read input image

            SitkImage inputImage = SimpleITK.ReadImage(inputFilename, PixelId.sitkFloat32);
            SitkImage initialModel = SimpleITK.ReadImage(initialModelFilename, PixelId.sitkFloat32);

            //  The input image will be processed with a few iterations of
            //  feature-preserving diffusion.  We create a filter and set the
            //  appropriate parameters.

            GradientAnisotropicDiffusionImageFilter diffusion=new GradientAnisotropicDiffusionImageFilter();
            diffusion.SetConductanceParameter(1.0);
            diffusion.SetTimeStep(0.125);
            diffusion.SetNumberOfIterations(5);
            SitkImage diffusedImage=diffusion.Execute(inputImage);

            // As with the other ITK level set segmentation filters, the terms of the
            // CannySegmentationLevelSetImageFilter level set equation can be
            // weighted by scalars.  For this application we will modify the relative
            // weight of the advection term.  The propagation and curvature term weights
            // are set to their defaults of 0 and 1, respectively.

            CannySegmentationLevelSetImageFilter cannySegmentation = new CannySegmentationLevelSetImageFilter();
            cannySegmentation.SetAdvectionScaling(advectionWeight);
            cannySegmentation.SetCurvatureScaling(1.0);
            cannySegmentation.SetPropagationScaling(0.0);

            //  The maximum number of iterations is specified from the command line.
            //  It may not be desirable in some applications to run the filter to
            //  convergence.  Only a few iterations may be required.

            cannySegmentation.SetMaximumRMSError(0.01);
            cannySegmentation.SetNumberOfIterations(maxIterations);

            //  There are two important parameters in the
            //  CannySegmentationLevelSetImageFilter to control the behavior of the
            //  Canny edge detection.  The variance parameter controls the
            //  amount of Gaussian smoothing on the input image.  The threshold
            //  parameter indicates the lowest allowed value in the output image.
            //  Thresholding is used to suppress Canny edges whose gradient magnitudes
            //  fall below a certain value.

            cannySegmentation.SetThreshold(cannyThreshold);
            cannySegmentation.SetVariance(cannyVariance);

            // Finally, it is very important to specify the isovalue of the surface in
            // the initial model input image. In a binary image, for example, the
            // isosurface is found midway between the foreground and background values.

            cannySegmentation.SetIsoSurfaceValue(intialModelIsovalue);

            SitkImage output = cannySegmentation.Execute(initialModel, diffusedImage);

            BinaryThresholdImageFilter thresholder= new BinaryThresholdImageFilter();
            thresholder.SetUpperThreshold(10.0);
            thresholder.SetLowerThreshold(0.0);

            thresholder.SetOutsideValue(0);
            thresholder.SetInsideValue(255);
            output=thresholder.Execute(output);


            output = SimpleITK.Cast(output, PixelIDValueEnum.sitkUInt8);

            SimpleITK.WriteImage(output,outputFilename);

            // Print out some useful information
            Console.WriteLine("");
            Console.WriteLine("Max. no. iterations: {0}", cannySegmentation.GetNumberOfIterations());
            Console.WriteLine("Max. RMS error: {0}", cannySegmentation.GetMaximumRMSError());
            Console.WriteLine("");
            Console.WriteLine("No. elpased iterations: {0}", cannySegmentation.GetElapsedIterations());
            Console.WriteLine("RMS change: {0}", cannySegmentation.GetRMSChange());

        }
    }
}
