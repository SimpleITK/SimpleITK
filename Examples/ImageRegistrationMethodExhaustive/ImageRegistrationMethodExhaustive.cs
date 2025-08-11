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
/// A SimpleITK example demonstrating image registration using the exhaustive optimizer.
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
            if (m_Method.GetOptimizerIteration() == 0)
            {
                VectorDouble scales = m_Method.GetOptimizerScales();
                Console.Write("Scales: [" + scales[0]);
                for (int i = 1; i < scales.Count; i++)
                {
                    Console.Write(", " + scales[i]);
                }
                Console.WriteLine("]");
            }

            VectorDouble pos = m_Method.GetOptimizerPosition();
            Console.Write("{0,3} = {1,7:F5} : [{2:F5}",
                         m_Method.GetOptimizerIteration(),
                         m_Method.GetMetricValue(),
                         pos[0]);
            for (int i = 1; i < pos.Count; i++)
            {
                Console.Write(", {0:F5}", pos[i]);
            }
            Console.WriteLine("]");
        }
    }

    class ImageRegistrationMethodExhaustive
    {
        static void Main(string[] args)
        {
            if (args.Length < 3)
            {
                Console.WriteLine("Usage: ImageRegistrationMethodExhaustive <fixedImageFile> <movingImageFile> <outputTransformFile>");
                return;
            }

            Image fixedImage = SimpleITK.ReadImage(args[0], PixelIDValueEnum.sitkFloat32);
            Image movingImage = SimpleITK.ReadImage(args[1], PixelIDValueEnum.sitkFloat32);

            ImageRegistrationMethod R = new ImageRegistrationMethod();

            R.SetMetricAsMattesMutualInformation(50); // numberOfHistogramBins

            int samplePerAxis = 12;
            Transform tx = null;

            if (fixedImage.GetDimension() == 2)
            {
                tx = new Euler2DTransform();
                // Set the number of samples (radius) in each dimension, with a default step size of 1.0
                VectorUInt32 exhaustiveSteps = new VectorUInt32(new uint[] { (uint)(samplePerAxis / 2), 0, 0 });
                R.SetOptimizerAsExhaustive(exhaustiveSteps);
                // Utilize the scale to set the step size for each dimension
                VectorDouble scales = new VectorDouble(new double[] { 2.0 * Math.PI / samplePerAxis, 1.0, 1.0 });
                R.SetOptimizerScales(scales);
            }
            else if (fixedImage.GetDimension() == 3)
            {
                tx = new Euler3DTransform();
                VectorUInt32 exhaustiveSteps = new VectorUInt32(new uint[] {
                    (uint)(samplePerAxis / 2),
                    (uint)(samplePerAxis / 2),
                    (uint)(samplePerAxis / 4),
                    0, 0, 0
                });
                R.SetOptimizerAsExhaustive(exhaustiveSteps);
                VectorDouble scales = new VectorDouble(new double[] {
                    2.0 * Math.PI / samplePerAxis,
                    2.0 * Math.PI / samplePerAxis,
                    2.0 * Math.PI / samplePerAxis,
                    1.0, 1.0, 1.0
                });
                R.SetOptimizerScales(scales);
            }

            // Initialize the transform with a translation and the center of rotation from the moments of intensity.
            tx = SimpleITK.CenteredTransformInitializer(fixedImage, movingImage, tx);

            R.SetInitialTransform(tx);
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

            if (Environment.GetEnvironmentVariable("SITK_NOSHOW") == null)
            {
                ResampleImageFilter resampler = new ResampleImageFilter();
                resampler.SetReferenceImage(fixedImage);
                resampler.SetInterpolator(InterpolatorEnum.sitkLinear);
                resampler.SetDefaultPixelValue(1);
                resampler.SetTransform(outTx);

                Image output = resampler.Execute(movingImage);

                Image simg1 = SimpleITK.Cast(SimpleITK.RescaleIntensity(fixedImage), PixelIDValueEnum.sitkUInt8);
                Image simg2 = SimpleITK.Cast(SimpleITK.RescaleIntensity(output), PixelIDValueEnum.sitkUInt8);
                Image cimg = SimpleITK.Compose(simg1, simg2, SimpleITK.Divide(SimpleITK.Add(simg1, simg2), 2));
                SimpleITK.Show(cimg, "ImageRegistrationExhaustive Composition");
            }
        }
    }
}
