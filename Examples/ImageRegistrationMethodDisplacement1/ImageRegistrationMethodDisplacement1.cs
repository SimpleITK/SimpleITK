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

// This example demonstrates displacement field registration
// combining affine and displacement field transforms.

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
                Console.WriteLine(String.Format("\tLevel: {0,3}", m_Method.GetCurrentLevel()));
                VectorDouble scales = m_Method.GetOptimizerScales();
                Console.Write(String.Format("\tScales: [{0:F5}", scales[0]));
                for (int i = 1; i < scales.Count; i++)
                {
                    Console.Write(String.Format(", {0:F5}", scales[i]));
                }
                Console.WriteLine("]");
            }
            Console.WriteLine(String.Format("#{0}", m_Method.GetOptimizerIteration()));
            Console.WriteLine(String.Format("\tMetric Value: {0:F5}", m_Method.GetMetricValue()));
            Console.WriteLine(String.Format("\tLearning Rate: {0:F5}", m_Method.GetOptimizerLearningRate()));
            if (m_Method.GetOptimizerConvergenceValue() != Double.MaxValue)
            {
                Console.WriteLine(String.Format("\tConvergence Value: {0:E}", m_Method.GetOptimizerConvergenceValue()));
            }
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
            Console.WriteLine(String.Format("\tStop Condition: {0}", m_Method.GetOptimizerStopConditionDescription()));
            Console.WriteLine("============= Resolution Change =============");
        }
    }

    class ImageRegistrationMethodDisplacement1
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

            Transform initialTx = SimpleITK.CenteredTransformInitializer(fixedImage, movingImage,
                new AffineTransform(fixedImage.GetDimension()));

            ImageRegistrationMethod R = new ImageRegistrationMethod();

            // First registration stage with affine transform
            VectorUInt32 shrinkFactors = new VectorUInt32();
            shrinkFactors.Add(3); shrinkFactors.Add(2); shrinkFactors.Add(1);

            VectorDouble smoothingSigmas = new VectorDouble();
            smoothingSigmas.Add(2.0); smoothingSigmas.Add(1.0); smoothingSigmas.Add(1.0);

            R.SetShrinkFactorsPerLevel(shrinkFactors);
            R.SetSmoothingSigmasPerLevel(smoothingSigmas);

            R.SetMetricAsJointHistogramMutualInformation(20);
            R.MetricUseFixedImageGradientFilterOff();

            double learningRate = 1.0;
            uint numberOfIterations = 100;
            double convergenceMinimumValue = 1e-6;
            uint convergenceWindowSize = 10;
            ImageRegistrationMethod.EstimateLearningRateType estimateLearningRate =
                ImageRegistrationMethod.EstimateLearningRateType.EachIteration;
            R.SetOptimizerAsGradientDescent(learningRate, numberOfIterations,
                                           convergenceMinimumValue, convergenceWindowSize, estimateLearningRate);

            R.SetOptimizerScalesFromPhysicalShift();
            R.SetInitialTransform(initialTx);
            R.SetInterpolator(InterpolatorEnum.sitkLinear);

            IterationUpdate cmd = new IterationUpdate(R);
            R.AddCommand(EventEnum.sitkIterationEvent, cmd);

            MultiResolutionIterationUpdate cmd2 = new MultiResolutionIterationUpdate(R);
            R.AddCommand(EventEnum.sitkMultiResolutionIterationEvent, cmd2);

            Transform outTx1 = R.Execute(fixedImage, movingImage);

            Console.WriteLine("-------");
            Console.WriteLine(outTx1.ToString());
            Console.WriteLine(String.Format("Optimizer stop condition: {0}", R.GetOptimizerStopConditionDescription()));
            Console.WriteLine(String.Format(" Iteration: {0}", R.GetOptimizerIteration()));
            Console.WriteLine(String.Format(" Metric value: {0}", R.GetMetricValue()));

            // Second registration stage with displacement field
            Image displacementField = new Image(fixedImage.GetSize(), PixelIDValueEnum.sitkVectorFloat64);
            displacementField.CopyInformation(fixedImage);
            DisplacementFieldTransform displacementTx = new DisplacementFieldTransform(displacementField);
            double varianceForUpdateField = 0.0;
            double varianceForTotalField = 1.5;
            displacementTx.SetSmoothingGaussianOnUpdate(varianceForUpdateField, varianceForTotalField);

            R.SetMovingInitialTransform(outTx1);
            R.SetInitialTransform(displacementTx, true);

            R.SetMetricAsANTSNeighborhoodCorrelation(4);
            R.MetricUseFixedImageGradientFilterOff();

            // Reset shrink factors and smoothing sigmas for second stage
            shrinkFactors = new VectorUInt32();
            shrinkFactors.Add(3); shrinkFactors.Add(2); shrinkFactors.Add(1);

            smoothingSigmas = new VectorDouble();
            smoothingSigmas.Add(2.0); smoothingSigmas.Add(1.0); smoothingSigmas.Add(1.0);

            R.SetShrinkFactorsPerLevel(shrinkFactors);
            R.SetSmoothingSigmasPerLevel(smoothingSigmas);

            R.SetOptimizerScalesFromPhysicalShift();

            learningRate = 1.0;
            numberOfIterations = 300;
            convergenceMinimumValue = 1e-6;
            convergenceWindowSize = 10;
            estimateLearningRate = ImageRegistrationMethod.EstimateLearningRateType.EachIteration;
            R.SetOptimizerAsGradientDescent(learningRate, numberOfIterations,
                                           convergenceMinimumValue, convergenceWindowSize, estimateLearningRate);

            R.Execute(fixedImage, movingImage);

            Console.WriteLine("-------");
            Console.WriteLine(displacementTx.ToString());
            Console.WriteLine(String.Format("Optimizer stop condition: {0}", R.GetOptimizerStopConditionDescription()));
            Console.WriteLine(String.Format(" Iteration: {0}", R.GetOptimizerIteration()));
            Console.WriteLine(String.Format(" Metric value: {0}", R.GetMetricValue()));

            VectorOfTransform transforms = new VectorOfTransform();
            transforms.Add(outTx1);
            transforms.Add(displacementTx);
            CompositeTransform outTx = new CompositeTransform(transforms);
            SimpleITK.WriteTransform(outTx, args[2]);
        }
    }
}
