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

// A SimpleITK example demonstrating the classic Demons image registration.

using System;
using itk.simple;

namespace itk.simple.examples
{
    public class DemonsRegistration1
    {
        public class IterationUpdate : Command
        {
            private DemonsRegistrationFilter filter;
            public IterationUpdate(DemonsRegistrationFilter filter)
            {
                this.filter = filter;
            }
            public override void Execute()
            {
                Console.WriteLine(string.Format("{0,3} = {1,10:F5}", filter.GetElapsedIterations(), filter.GetMetric()));
            }
        }

        public static void Main(string[] args)
        {
            if (args.Length < 3)
            {
                Console.WriteLine("Usage: DemonsRegistration1 <fixedImageFile> <movingImageFile> <outputTransformFile>");
                return;
            }

            var fixedImage = SimpleITK.ReadImage(args[0], PixelIDValueEnum.sitkFloat32);
            var movingImage = SimpleITK.ReadImage(args[1], PixelIDValueEnum.sitkFloat32);

            // Perform histogram matching of the moving image to the fixed image
            var matcher = new HistogramMatchingImageFilter();
            matcher.SetNumberOfHistogramLevels(1024);
            matcher.SetNumberOfMatchPoints(7);
            matcher.ThresholdAtMeanIntensityOn();
            movingImage = matcher.Execute(movingImage, fixedImage);

            // The basic Demons Registration Filter
            // Note there is a whole family of Demons Registration algorithms included in SimpleITK
            var demons = new DemonsRegistrationFilter();
            demons.SetNumberOfIterations(50);
            // Standard deviation for Gaussian smoothing of displacement field
            demons.SetStandardDeviations(1.0);

            // Add iteration callback
            var cmd = new IterationUpdate(demons);
            demons.AddCommand(EventEnum.sitkIterationEvent, cmd);

            var displacementField = demons.Execute(fixedImage, movingImage);

            Console.WriteLine("-------");
            Console.WriteLine(string.Format("Number Of Iterations: {0}", demons.GetElapsedIterations()));
            Console.WriteLine(string.Format(" RMS: {0}", demons.GetRMSChange()));

            // Create and write the displacement field transform
            var outTx = new DisplacementFieldTransform(displacementField);
            SimpleITK.WriteTransform(outTx, args[2]);
        }
    }
}
