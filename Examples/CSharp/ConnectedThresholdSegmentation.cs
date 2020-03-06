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
using sitk = itk.simple;

namespace itk.simple.examples
{
    public class Program
    {
        static void Main(string[] args)
        {
            if (args.Length < 6)
            {
                Console.WriteLine("Missing Parameters ");
                Console.WriteLine("Usage: " + System.AppDomain.CurrentDomain.FriendlyName +
                                  " inputImage outputImage" +
                                  " lowerThreshold upperThreshold seedX seedY [seed2X seed2Y ... ]");
                return;
            }

            string inputFilename = args[0];
            string outputFilename = args[1];

            double lowerThreshold = double.Parse(args[2], CultureInfo.InvariantCulture);
            double upperThreshold = double.Parse(args[3], CultureInfo.InvariantCulture);

            //
            // Read the image
            //

            SitkImage inputImage = SimpleITK.ReadImage(inputFilename, PixelIDValueEnum.sitkFloat32);

            //
            // Blur using CurvatureFlowImageFilter
            //
            CurvatureFlowImageFilter blurFilter = new sitk.CurvatureFlowImageFilter();
            blurFilter.SetNumberOfIterations(5);
            blurFilter.SetTimeStep(0.125);
            inputImage = blurFilter.Execute(inputImage);


            //
            // Set up ConnectedThresholdImageFilter for segmentation
            //

            ConnectedThresholdImageFilter segmentationFilter = new sitk.ConnectedThresholdImageFilter();
            segmentationFilter.SetLower(lowerThreshold);
            segmentationFilter.SetUpper(upperThreshold);
            segmentationFilter.SetReplaceValue(255);

            for (uint i = 4; i + 1 < args.Length; i += 2)
            {
                VectorUInt32 seed = new VectorUInt32(new uint[] { Convert.ToUInt32(args[i]), Convert.ToUInt32(args[i + 1]), 0 });
                segmentationFilter.AddSeed(seed);
                Console.WriteLine("Adding a seed at: ");
                for (int j = 0; j + 1 < seed.Count; j++)
                {
                    Console.WriteLine(seed[j] + " ");
                }
            }
            SitkImage outImage = segmentationFilter.Execute(inputImage);

            //
            // Write out the resulting file
            //

            SimpleITK.WriteImage(outImage, outputFilename);

            return;
        }
    }
}
