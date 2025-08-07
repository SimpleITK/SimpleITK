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
/// A SimpleITK example demonstrating image registration using optimizer weights.
/// </summary>

using System;
using itk.simple;

namespace itk.simple.examples
{
    class ImageRegistrationOptimizerWeights
    {
        static void Main(string[] args)
        {
            if (args.Length < 3)
            {
                Console.WriteLine("Usage: ImageRegistrationOptimizerWeights <fixedImageFile> <movingImageFile> <outputTransformFile>");
                return;
            }

            Image fixedImage = SimpleITK.ReadImage(args[0], PixelIDValueEnum.sitkFloat32);
            Image movingImage = SimpleITK.ReadImage(args[1], PixelIDValueEnum.sitkFloat32);

            // initialization
            Transform transform = SimpleITK.CenteredTransformInitializer(
                fixedImage,
                movingImage,
                new Euler3DTransform(),
                CenteredTransformInitializerFilter.OperationModeType.GEOMETRY);

            // registration
            ImageRegistrationMethod registrationMethod = new ImageRegistrationMethod();
            registrationMethod.SetMetricAsCorrelation();
            registrationMethod.SetMetricSamplingStrategy(ImageRegistrationMethod.MetricSamplingStrategyType.NONE);
            registrationMethod.SetInterpolator(InterpolatorEnum.sitkLinear);
            registrationMethod.SetOptimizerAsGradientDescent(1.0,   // learningRate
                                                             300,   // numberOfIterations
                                                             1e-6,  // convergenceMinimumValue
                                                             10);   // convergenceWindowSize
            registrationMethod.SetOptimizerScalesFromPhysicalShift();
            registrationMethod.SetInitialTransform(transform, true);  // inPlace=true

            // Set optimizer weights: [0, 0, 1, 1, 1, 1] - disable rotation around x and y axes
            VectorDouble weights = new VectorDouble(new double[] { 0, 0, 1, 1, 1, 1 });
            registrationMethod.SetOptimizerWeights(weights);

            registrationMethod.Execute(fixedImage, movingImage);

            Console.WriteLine("-------");
            Console.WriteLine("Final transform parameters: " + transform.GetParameters());
            Console.WriteLine("Optimizer stop condition: " + registrationMethod.GetOptimizerStopConditionDescription());
            Console.WriteLine("Iteration: " + registrationMethod.GetOptimizerIteration());
            Console.WriteLine("Metric value: " + registrationMethod.GetMetricValue());

            SimpleITK.WriteTransform(transform, args[2]);
        }
    }
}
