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
                Console.Write("Estimated Scales: [{0}", scales[0]);
                for (int i = 1; i < scales.Count; i++)
                {
                    Console.Write(", {0}", scales[i]);
                }
                Console.WriteLine("]");
            }

            VectorDouble pos = m_Method.GetOptimizerPosition();
            Console.Write("{0,3} = {1,7:F5} : [",
                         m_Method.GetOptimizerIteration(),
                         m_Method.GetMetricValue());
            Console.Write("{0:F5}", pos[0]);
            for (int i = 1; i < pos.Count; i++)
            {
                Console.Write(", {0:F5}", pos[i]);
            }
            Console.WriteLine("]");
        }
    }

    class ImageRegistrationMethod3
    {
        static void Main(string[] args)
        {
            if (args.Length < 3)
            {
                Console.WriteLine("Usage: ImageRegistrationMethod3 <fixedImageFile> <movingImageFile> <outputTransformFile>");
                return;
            }

            var fixedImage = SimpleITK.ReadImage(args[0], PixelIDValueEnum.sitkFloat32);
            var movingImage = SimpleITK.ReadImage(args[1], PixelIDValueEnum.sitkFloat32);

            ImageRegistrationMethod R = new ImageRegistrationMethod();

            R.SetMetricAsCorrelation();

            R.SetOptimizerAsRegularStepGradientDescent(2.0,   // learningRate
                                                       1e-4,  // minStep
                                                       500,   // numberOfIterations
                                                       0.5,   // relaxationFactor
                                                       1e-8); // gradientMagnitudeTolerance
            R.SetOptimizerScalesFromIndexShift();

            Transform tx = SimpleITK.CenteredTransformInitializer(fixedImage, movingImage, new Similarity2DTransform());
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

            ResampleImageFilter resampler = new ResampleImageFilter();
            resampler.SetReferenceImage(fixedImage);
            resampler.SetInterpolator(InterpolatorEnum.sitkLinear);
            resampler.SetDefaultPixelValue(100);
            resampler.SetTransform(outTx);

            Image output = resampler.Execute(movingImage);

            Image simg1 = SimpleITK.Cast(SimpleITK.RescaleIntensity(fixedImage), PixelIDValueEnum.sitkUInt8);
            Image simg2 = SimpleITK.Cast(SimpleITK.RescaleIntensity(output), PixelIDValueEnum.sitkUInt8);
            Image cimg = SimpleITK.Compose(simg1, simg2, SimpleITK.Divide(SimpleITK.Add(simg1, simg2), 2));

            if (Environment.GetEnvironmentVariable("SITK_NOSHOW") == null)
            {
                SimpleITK.Show(cimg, "ImageRegistration3 Composition");
            }
        }
    }
}
