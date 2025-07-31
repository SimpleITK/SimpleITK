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

/// <summary>
/// A SimpleITK example demonstrating image registration using Mattes mutual
/// information as the metric.
/// </summary>

using System;
using itk.simple;

namespace itk.simple.examples
{
    class IterationUpdate : Command
    {
        private ImageRegistrationMethod m_Method;

        public IterationUpdate(ImageRegistrationMethod m)
        {
            m_Method = m;
        }

        public override void Execute()
        {
            VectorDouble pos = m_Method.GetOptimizerPosition();
            Console.Write("{0,3} = {1,10:F5} : [",
                         m_Method.GetOptimizerIteration(),
                         m_Method.GetMetricValue());
            for (int i = 0; i < pos.Count; i++)
            {
                if (i > 0) Console.Write(", ");
                Console.Write("{0:F5}", pos[i]);
            }
            Console.WriteLine("]");
        }
    }

    class ImageRegistrationMethod4
    {
        static void Main(string[] args)
        {
            if (args.Length < 3)
            {
                Console.WriteLine("Usage: ImageRegistrationMethod4 <fixedImageFile> <movingImageFile> <outputTransformFile> [numberOfBins] [samplingPercentage]");
                return;
            }

            Image fixedImage = SimpleITK.ReadImage(args[0], PixelIDValueEnum.sitkFloat32);
            Image movingImage = SimpleITK.ReadImage(args[1], PixelIDValueEnum.sitkFloat32);

            uint numberOfBins = 24;
            double samplingPercentage = 0.10;

            if (args.Length > 3)
            {
                numberOfBins = uint.Parse(args[3]);
            }
            if (args.Length > 4)
            {
                samplingPercentage = double.Parse(args[4]);
            }

            ImageRegistrationMethod R = new ImageRegistrationMethod();
            R.SetMetricAsMattesMutualInformation(numberOfBins);
            R.SetMetricSamplingPercentage(samplingPercentage);
            R.SetMetricSamplingStrategy(ImageRegistrationMethod.MetricSamplingStrategyType.RANDOM);
            R.SetOptimizerAsRegularStepGradientDescent(1.0, 0.001, 200);
            R.SetInitialTransform(new TranslationTransform(fixedImage.GetDimension()));
            R.SetInterpolator(InterpolatorEnum.sitkLinear);

            IterationUpdate cmd = new IterationUpdate(R);
            R.AddCommand(EventEnum.sitkIterationEvent, cmd);

            Transform outTx = R.Execute(fixedImage, movingImage);

            Console.WriteLine("-------");
            Console.WriteLine(outTx.ToString());
            Console.WriteLine("Optimizer stop condition: " + R.GetOptimizerStopConditionDescription());
            Console.WriteLine(" Iteration: " + R.GetOptimizerIteration());
            Console.WriteLine(" Metric value: " + R.GetMetricValue());

            SimpleITK.WriteTransform(outTx, args[2]);

            ResampleImageFilter resampler = new ResampleImageFilter();
            resampler.SetReferenceImage(fixedImage);
            resampler.SetInterpolator(InterpolatorEnum.sitkLinear);
            resampler.SetDefaultPixelValue(100);
            resampler.SetTransform(outTx);

            Image output = resampler.Execute(movingImage);
            Image simg1 = SimpleITK.Cast(SimpleITK.RescaleIntensity(fixedImage), PixelIDValueEnum.sitkUInt8);
            Image simg2 = SimpleITK.Cast(SimpleITK.RescaleIntensity(output), PixelIDValueEnum.sitkUInt8);
            Image cimg = SimpleITK.Compose(simg1, simg2, SimpleITK.Divide(SimpleITK.Add(simg1, simg2), 2));

            // Show the composition image if SITK_NOSHOW environment variable is not set
            if (Environment.GetEnvironmentVariable("SITK_NOSHOW") == null)
            {
                SimpleITK.Show(cimg, "ImageRegistration4 Composition");
            }
        }
    }
}
