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

import org.itk.simple.*;

public class ImageRegistrationOptimizerWeights {

    public static void main(String[] args) throws Exception {
        if (args.length < 3) {
            System.out.println("Usage: ImageRegistrationOptimizerWeights <fixedImageFile> <movingImageFile> <outputTransformFile>");
            System.exit(1);
        }

        Image fixedImage = SimpleITK.readImage(args[0], PixelIDValueEnum.sitkFloat32);
        Image movingImage = SimpleITK.readImage(args[1], PixelIDValueEnum.sitkFloat32);

        // initialization
        Transform transform = SimpleITK.centeredTransformInitializer(
            fixedImage,
            movingImage,
            new Euler3DTransform(),
            CenteredTransformInitializerFilter.OperationModeType.GEOMETRY);

        // registration
        ImageRegistrationMethod registrationMethod = new ImageRegistrationMethod();
        registrationMethod.setMetricAsCorrelation();
        registrationMethod.setMetricSamplingStrategy(ImageRegistrationMethod.MetricSamplingStrategyType.NONE);
        registrationMethod.setInterpolator(InterpolatorEnum.sitkLinear);
        registrationMethod.setOptimizerAsGradientDescent(1.0,   // learningRate
                                                         300,   // numberOfIterations
                                                         1e-6,  // convergenceMinimumValue
                                                         10);   // convergenceWindowSize
        registrationMethod.setOptimizerScalesFromPhysicalShift();
        registrationMethod.setInitialTransform(transform, true);  // inPlace=true

        // Set optimizer weights: [0, 0, 1, 1, 1, 1] - disable rotation around x and y axes
        VectorDouble weights = new VectorDouble();
        weights.add(0.0); weights.add(0.0); weights.add(1.0);
        weights.add(1.0); weights.add(1.0); weights.add(1.0);
        registrationMethod.setOptimizerWeights(weights);

        registrationMethod.execute(fixedImage, movingImage);

        System.out.println("-------");
        System.out.println("Final transform parameters: " + transform.getParameters());
        System.out.println("Optimizer stop condition: " + registrationMethod.getOptimizerStopConditionDescription());
        System.out.println("Iteration: " + registrationMethod.getOptimizerIteration());
        System.out.println("Metric value: " + registrationMethod.getMetricValue());

        SimpleITK.writeTransform(transform, args[2]);
    }
}
