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

import org.itk.simple.*;

class IterationUpdate extends Command {
    private ImageRegistrationMethod method;

    public IterationUpdate(ImageRegistrationMethod m) {
        method = m;
    }

    public void execute() {
        if (method.getOptimizerIteration() == 0) {
            System.out.printf("\tLevel: %3d%n", method.getCurrentLevel());
            VectorDouble scales = method.getOptimizerScales();
            System.out.printf("\tScales: [%.5f", scales.get(0));
            for (int i = 1; i < scales.size(); i++) {
                System.out.printf(", %.5f", scales.get(i));
            }
            System.out.println("]");
        }
        System.out.printf("#%d%n", method.getOptimizerIteration());
        System.out.printf("\tMetric Value: %.5f%n", method.getMetricValue());
        System.out.printf("\tLearning Rate: %.5f%n", method.getOptimizerLearningRate());
        if (method.getOptimizerConvergenceValue() != Double.MAX_VALUE) {
            System.out.printf("\tConvergence Value: %E%n", method.getOptimizerConvergenceValue());
        }
    }
}

class MultiResolutionIterationUpdate extends Command {
    private ImageRegistrationMethod method;

    public MultiResolutionIterationUpdate(ImageRegistrationMethod m) {
        method = m;
    }

    public void execute() {
        System.out.printf("\tStop Condition: %s%n", method.getOptimizerStopConditionDescription());
        System.out.println("============= Resolution Change =============");
    }
}

class ImageRegistrationMethodDisplacement1 {

    public static void main(String[] args) {

        if (args.length < 3) {
            System.out.println("Usage: ImageRegistrationMethodDisplacement1 <fixedImageFile> <movingImageFile> <outputTransformFile>");
            return;
        }

        Image fixedImage = SimpleITK.readImage(args[0], PixelIDValueEnum.sitkFloat32);
        Image movingImage = SimpleITK.readImage(args[1], PixelIDValueEnum.sitkFloat32);

        Transform initialTx = SimpleITK.centeredTransformInitializer(fixedImage, movingImage,
            new AffineTransform(fixedImage.getDimension()));

        ImageRegistrationMethod R = new ImageRegistrationMethod();

        // First registration stage with affine transform
        VectorUInt32 shrinkFactors = new VectorUInt32();
        shrinkFactors.add(3L); shrinkFactors.add(2L); shrinkFactors.add(1L);

        VectorDouble smoothingSigmas = new VectorDouble();
        smoothingSigmas.add(2.0); smoothingSigmas.add(1.0); smoothingSigmas.add(1.0);

        R.setShrinkFactorsPerLevel(shrinkFactors);
        R.setSmoothingSigmasPerLevel(smoothingSigmas);

        R.setMetricAsJointHistogramMutualInformation(20);
        R.metricUseFixedImageGradientFilterOff();

        double learningRate = 1.0;
        int numberOfIterations = 100;
        double convergenceMinimumValue = 1e-6;
        int convergenceWindowSize = 10;
        ImageRegistrationMethod.EstimateLearningRateType estimateLearningRate =
            ImageRegistrationMethod.EstimateLearningRateType.EachIteration;
        R.setOptimizerAsGradientDescent(learningRate, numberOfIterations,
                                       convergenceMinimumValue, convergenceWindowSize, estimateLearningRate);

        R.setOptimizerScalesFromPhysicalShift();
        R.setInitialTransform(initialTx);
        R.setInterpolator(InterpolatorEnum.sitkLinear);

        IterationUpdate cmd = new IterationUpdate(R);
        R.addCommand(EventEnum.sitkIterationEvent, cmd);

        MultiResolutionIterationUpdate cmd2 = new MultiResolutionIterationUpdate(R);
        R.addCommand(EventEnum.sitkMultiResolutionIterationEvent, cmd2);

        Transform outTx1 = R.execute(fixedImage, movingImage);

        System.out.println("-------");
        System.out.println(outTx1.toString());
        System.out.printf("Optimizer stop condition: %s%n", R.getOptimizerStopConditionDescription());
        System.out.printf(" Iteration: %d%n", R.getOptimizerIteration());
        System.out.printf(" Metric value: %f%n", R.getMetricValue());

        // Second registration stage with displacement field
        Image displacementField = new Image(fixedImage.getSize(), PixelIDValueEnum.sitkVectorFloat64);
        displacementField.copyInformation(fixedImage);
        DisplacementFieldTransform displacementTx = new DisplacementFieldTransform(displacementField);
        double varianceForUpdateField = 0.0;
        double varianceForTotalField = 1.5;
        displacementTx.setSmoothingGaussianOnUpdate(varianceForUpdateField, varianceForTotalField);

        R.setMovingInitialTransform(outTx1);
        R.setInitialTransform(displacementTx, true);

        R.setMetricAsANTSNeighborhoodCorrelation(4);
        R.metricUseFixedImageGradientFilterOff();

        // Reset shrink factors and smoothing sigmas for second stage
        shrinkFactors = new VectorUInt32();
        shrinkFactors.add(3L); shrinkFactors.add(2L); shrinkFactors.add(1L);

        smoothingSigmas = new VectorDouble();
        smoothingSigmas.add(2.0); smoothingSigmas.add(1.0); smoothingSigmas.add(1.0);

        R.setShrinkFactorsPerLevel(shrinkFactors);
        R.setSmoothingSigmasPerLevel(smoothingSigmas);

        R.setOptimizerScalesFromPhysicalShift();

        learningRate = 1.0;
        numberOfIterations = 300;
        convergenceMinimumValue = 1e-6;
        convergenceWindowSize = 10;
        estimateLearningRate = ImageRegistrationMethod.EstimateLearningRateType.EachIteration;
        R.setOptimizerAsGradientDescent(learningRate, numberOfIterations,
                                       convergenceMinimumValue, convergenceWindowSize, estimateLearningRate);

        R.execute(fixedImage, movingImage);

        System.out.println("-------");
        System.out.println(displacementTx.toString());
        System.out.printf("Optimizer stop condition: %s%n", R.getOptimizerStopConditionDescription());
        System.out.printf(" Iteration: %d%n", R.getOptimizerIteration());
        System.out.printf(" Metric value: %f%n", R.getMetricValue());

        VectorOfTransform transforms = new VectorOfTransform();
        transforms.add(outTx1);
        transforms.add(displacementTx);
        CompositeTransform outTx = new CompositeTransform(transforms);
        SimpleITK.writeTransform(outTx, args[2]);
    }
}
