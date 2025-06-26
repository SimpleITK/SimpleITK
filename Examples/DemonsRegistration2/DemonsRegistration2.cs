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

// A SimpleITK example demonstrating fast symmetric forces Demons image registration.

using System;
using itk.simple;

namespace itk.simple.examples
{
    public class DemonsRegistration2
    {
        public class IterationUpdate : Command
        {
            private FastSymmetricForcesDemonsRegistrationFilter filter;
            public IterationUpdate(FastSymmetricForcesDemonsRegistrationFilter filter)
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
                Console.WriteLine("Usage: DemonsRegistration2 <fixedImageFile> <movingImageFile> [initialTransformFile] <outputTransformFile>");
                return;
            }

            // Read the fixed and moving images
            var fixedImage = SimpleITK.ReadImage(args[0]);
            var movingImage = SimpleITK.ReadImage(args[1]);

            // Perform histogram matching of the moving image to the fixed image
            var matcher = new HistogramMatchingImageFilter();
            if (fixedImage.GetPixelID() == PixelIDValueEnum.sitkUInt8 || fixedImage.GetPixelID() == PixelIDValueEnum.sitkInt8)
                matcher.SetNumberOfHistogramLevels(128);
            else
                matcher.SetNumberOfHistogramLevels(1024);
            matcher.SetNumberOfMatchPoints(7);
            matcher.ThresholdAtMeanIntensityOn();
            movingImage = matcher.Execute(movingImage, fixedImage);

            // The fast symmetric forces Demons Registration Filter
            // Note there is a whole family of Demons Registration algorithms included in SimpleITK
            var demons = new FastSymmetricForcesDemonsRegistrationFilter();
            demons.SetNumberOfIterations(200);
            // Standard deviation for Gaussian smoothing of displacement field
            demons.SetStandardDeviations(1.0);

            // Add iteration callback
            var cmd = new IterationUpdate(demons);
            demons.AddCommand(EventEnum.sitkIterationEvent, cmd);

            Image displacementField;
            if (args.Length > 3)
            {
                var initialTransform = SimpleITK.ReadTransform(args[2]);
                var outputTransformFile = args[3];
                var toDisplacementFilter = new TransformToDisplacementFieldFilter();
                toDisplacementFilter.SetReferenceImage(fixedImage);
                displacementField = toDisplacementFilter.Execute(initialTransform);
                displacementField = demons.Execute(fixedImage, movingImage, displacementField);
                var outTx = new DisplacementFieldTransform(displacementField);
                SimpleITK.WriteTransform(outTx, outputTransformFile);
            }
            else
            {
                displacementField = demons.Execute(fixedImage, movingImage);
                var outTx = new DisplacementFieldTransform(displacementField);
                SimpleITK.WriteTransform(outTx, args[2]);
            }

            Console.WriteLine("-------");
            Console.WriteLine(string.Format("Number Of Iterations: {0}", demons.GetElapsedIterations()));
            Console.WriteLine(string.Format(" RMS: {0}", demons.GetRMSChange()));

            // Visualization (if SITK_NOSHOW is not set)
            if (Environment.GetEnvironmentVariable("SITK_NOSHOW") == null)
            {
                var resampler = new ResampleImageFilter();
                resampler.SetReferenceImage(fixedImage);
                resampler.SetInterpolator(InterpolatorEnum.sitkLinear);
                resampler.SetDefaultPixelValue(100);
                resampler.SetTransform(new DisplacementFieldTransform(displacementField));

                var outImg = resampler.Execute(movingImage);
                var simg1 = SimpleITK.Cast(SimpleITK.RescaleIntensity(fixedImage), PixelIDValueEnum.sitkUInt8);
                var simg2 = SimpleITK.Cast(SimpleITK.RescaleIntensity(outImg), PixelIDValueEnum.sitkUInt8);
                var cimg = SimpleITK.Compose(simg1, simg2, SimpleITK.Add(SimpleITK.Divide(simg1, 2.0), SimpleITK.Divide(simg2, 2.0)));
                SimpleITK.Show(cimg, "DeformableRegistration2 Composition");
            }
        }
    }
}
