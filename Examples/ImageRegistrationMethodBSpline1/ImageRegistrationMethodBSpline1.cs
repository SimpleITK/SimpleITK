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
/// A SimpleITK example demonstrating image registration using the
/// BSplineTransform and the ComplexCorrelation metric.
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
            Console.WriteLine("{0,3} = {1,10:F5}",
                             m_Method.GetOptimizerIteration(),
                             m_Method.GetMetricValue());
        }
    }

    class ImageRegistrationMethodBSpline1
    {
        static void Main(string[] args)
        {
            if (args.Length < 3)
            {
                Console.WriteLine("Usage: {0} <fixedImageFile> <movingImageFile> <outputTransformFile>",
                                 "ImageRegistrationMethodBSpline1");
                return;
            }

            Image fixedImage = SimpleITK.ReadImage(args[0], PixelIDValueEnum.sitkFloat32);
            Image movingImage = SimpleITK.ReadImage(args[1], PixelIDValueEnum.sitkFloat32);

            // Create transform domain mesh size vector
            VectorUInt32 transformDomainMeshSize = new VectorUInt32();
            for (uint i = 0; i < movingImage.GetDimension(); i++)
            {
                transformDomainMeshSize.Add(8);
            }

            Transform tx = SimpleITK.BSplineTransformInitializer(fixedImage, transformDomainMeshSize);

            Console.WriteLine("Initial Parameters:");
            VectorDouble initialParams = tx.GetParameters();
            Console.Write("[" + initialParams[0].ToString("F5"));
            for (int i = 1; i < initialParams.Count; i++)
            {
                Console.Write(", " + initialParams[i].ToString("F5"));
            }
            Console.WriteLine("]");

            ImageRegistrationMethod R = new ImageRegistrationMethod();
            R.SetMetricAsCorrelation();

            R.SetOptimizerAsLBFGSB(gradientConvergenceTolerance: 1e-5,
                                   numberOfIterations: 100,
                                   maximumNumberOfCorrections: 5,
                                   maximumNumberOfFunctionEvaluations: 1000,
                                   costFunctionConvergenceFactor: 1e7);

            R.SetInitialTransform(tx, true);
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

            Image outputImage = resampler.Execute(movingImage);
            Image simg1 = SimpleITK.Cast(SimpleITK.RescaleIntensity(fixedImage), PixelIDValueEnum.sitkUInt8);
            Image simg2 = SimpleITK.Cast(SimpleITK.RescaleIntensity(outputImage), PixelIDValueEnum.sitkUInt8);
            Image cimg = SimpleITK.Compose(simg1, simg2, SimpleITK.Divide(SimpleITK.Add(simg1, simg2), 2));

            if (Environment.GetEnvironmentVariable("SITK_NOSHOW") == null)
            {
                SimpleITK.Show(cimg, "ImageRegistrationMethodBSpline1 Composition");
            }
        }
    }
}
