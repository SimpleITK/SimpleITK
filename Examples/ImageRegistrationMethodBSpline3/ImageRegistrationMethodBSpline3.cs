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

// A SimpleITK example demonstrating image registration using the
// BSplineTransform and the JointHistogramMutualInformation metric.

using System;
using itk.simple;

namespace itk.simple.examples
{
    class IterationUpdate : Command
    {
        private ImageRegistrationMethod m_Method;
        private Transform m_BSplineTransform;

        public IterationUpdate(ImageRegistrationMethod m, Transform bsplineTransform)
        {
            m_Method = m;
            m_BSplineTransform = bsplineTransform;
        }

        public override void Execute()
        {
            if (m_Method.GetOptimizerIteration() == 0)
            {
                // The BSpline is resized before the first optimizer
                // iteration is completed per level. Print the transform object
                // to show the adapted BSpline transform.
                Console.WriteLine(m_BSplineTransform.ToString());
            }

            Console.WriteLine(String.Format("{0,3} = {1,10:F5}",
                             m_Method.GetOptimizerIteration(),
                             m_Method.GetMetricValue()));
        }
    }

    class MultiResolutionIterationUpdate : Command
    {
        private ImageRegistrationMethod m_Method;

        public MultiResolutionIterationUpdate(ImageRegistrationMethod m)
        {
            m_Method = m;
        }

        public override void Execute()
        {
            if (m_Method.GetCurrentLevel() > 0)
            {
                Console.WriteLine(String.Format("Optimizer stop condition: {0}",
                                 m_Method.GetOptimizerStopConditionDescription()));
                Console.WriteLine(String.Format(" Iteration: {0}", m_Method.GetOptimizerIteration()));
                Console.WriteLine(String.Format(" Metric value: {0}", m_Method.GetMetricValue()));
            }

            Console.WriteLine("--------- Resolution Changing ---------");
        }
    }

    class ImageRegistrationMethodBSpline3
    {
        static void Main(string[] args)
        {
            if (args.Length < 3)
            {
                Console.WriteLine("Usage: {0} <fixedImageFile> <movingImageFile> <outputTransformFile>",
                    System.AppDomain.CurrentDomain.FriendlyName);
                return;
            }

            Image fixedImage = SimpleITK.ReadImage(args[0], PixelIDValueEnum.sitkFloat32);
            Image movingImage = SimpleITK.ReadImage(args[1], PixelIDValueEnum.sitkFloat32);

            VectorUInt32 transformDomainMeshSize = new VectorUInt32();
            for (uint i = 0; i < fixedImage.GetDimension(); i++)
            {
                transformDomainMeshSize.Add(2);
            }

            BSplineTransform tx = SimpleITK.BSplineTransformInitializer(fixedImage, transformDomainMeshSize);

            Console.WriteLine(String.Format("Initial Number of Parameters: {0}", tx.GetNumberOfParameters()));

            ImageRegistrationMethod R = new ImageRegistrationMethod();
            R.SetMetricAsJointHistogramMutualInformation();

            double learningRate = 5.0;
            uint numberOfIterations = 100;
            double convergenceMinimumValue = 1e-4;
            uint convergenceWindowSize = 5;
            R.SetOptimizerAsGradientDescentLineSearch(learningRate, numberOfIterations,
                                                     convergenceMinimumValue, convergenceWindowSize);

            R.SetInterpolator(InterpolatorEnum.sitkLinear);

            VectorUInt32 scaleFactors = new VectorUInt32();
            scaleFactors.Add(1); scaleFactors.Add(2); scaleFactors.Add(5);
            R.SetInitialTransformAsBSpline(tx, true, scaleFactors);

            VectorUInt32 shrinkFactors = new VectorUInt32();
            shrinkFactors.Add(4); shrinkFactors.Add(2); shrinkFactors.Add(1);
            R.SetShrinkFactorsPerLevel(shrinkFactors);

            VectorDouble smoothingSigmas = new VectorDouble();
            smoothingSigmas.Add(4); smoothingSigmas.Add(2); smoothingSigmas.Add(1);
            R.SetSmoothingSigmasPerLevel(smoothingSigmas);

            IterationUpdate cmd1 = new IterationUpdate(R, tx);
            R.AddCommand(EventEnum.sitkIterationEvent, cmd1);

            MultiResolutionIterationUpdate cmd2 = new MultiResolutionIterationUpdate(R);
            R.AddCommand(EventEnum.sitkMultiResolutionIterationEvent, cmd2);

            Transform outTx = R.Execute(fixedImage, movingImage);

            Console.WriteLine("-------");
            Console.WriteLine(tx.ToString());
            Console.WriteLine(outTx.ToString());
            Console.WriteLine(String.Format("Optimizer stop condition: {0}", R.GetOptimizerStopConditionDescription()));
            Console.WriteLine(String.Format(" Iteration: {0}", R.GetOptimizerIteration()));
            Console.WriteLine(String.Format(" Metric value: {0}", R.GetMetricValue()));

            SimpleITK.WriteTransform(outTx, args[2]);

            if (Environment.GetEnvironmentVariable("SITK_NOSHOW") == null)
            {
                ResampleImageFilter resampler = new ResampleImageFilter();
                resampler.SetReferenceImage(fixedImage);
                resampler.SetInterpolator(InterpolatorEnum.sitkLinear);
                resampler.SetDefaultPixelValue(100);
                resampler.SetTransform(outTx);

                Image outputImage = resampler.Execute(movingImage);
                Image simg1 = SimpleITK.Cast(SimpleITK.RescaleIntensity(fixedImage), PixelIDValueEnum.sitkUInt8);
                Image simg2 = SimpleITK.Cast(SimpleITK.RescaleIntensity(outputImage), PixelIDValueEnum.sitkUInt8);
                Image cimg = SimpleITK.Compose(simg1, simg2, SimpleITK.Divide(SimpleITK.Add(simg1, simg2), 2.0));

                SimpleITK.Show(cimg, "Image Registration Composition");
            }
        }
    }
}
