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

import org.itk.simple.*;

class IterationUpdate extends Command {
    private ImageRegistrationMethod method;
    private Transform bsplineTransform;

    public IterationUpdate(ImageRegistrationMethod m, Transform bsplineTransform) {
        method = m;
        this.bsplineTransform = bsplineTransform;
    }

    public void execute() {
        if (method.getOptimizerIteration() == 0) {
            // The BSpline is resized before the first optimizer
            // iteration is completed per level. Print the transform object
            // to show the adapted BSpline transform.
            System.out.println(bsplineTransform.toString());
        }

        System.out.printf("%3d = %10.5f%n",
                         method.getOptimizerIteration(),
                         method.getMetricValue());
    }
}

class MultiResolutionIterationUpdate extends Command {
    private ImageRegistrationMethod method;

    public MultiResolutionIterationUpdate(ImageRegistrationMethod m) {
        method = m;
    }

    public void execute() {
        if (method.getCurrentLevel() > 0) {
            System.out.println("Optimizer stop condition: " + method.getOptimizerStopConditionDescription());
            System.out.println(" Iteration: " + method.getOptimizerIteration());
            System.out.println(" Metric value: " + method.getMetricValue());
        }

        System.out.println("--------- Resolution Changing ---------");
    }
}

class ImageRegistrationMethodBSpline3 {

    public static void main(String[] args) {

        if (args.length < 3) {
            System.out.println("Usage: ImageRegistrationMethodBSpline3 <fixedImageFile> <movingImageFile> <outputTransformFile>");
            return;
        }

        Image fixedImage = SimpleITK.readImage(args[0], PixelIDValueEnum.sitkFloat32);
        Image movingImage = SimpleITK.readImage(args[1], PixelIDValueEnum.sitkFloat32);

        // Create transform domain mesh size vector
        VectorUInt32 transformDomainMeshSize = new VectorUInt32();
        for (int i = 0; i < fixedImage.getDimension(); i++) {
            transformDomainMeshSize.add(2L);
        }

        BSplineTransform tx = SimpleITK.bSplineTransformInitializer(fixedImage, transformDomainMeshSize);

        System.out.println("Initial Number of Parameters: " + tx.getNumberOfParameters());

        ImageRegistrationMethod R = new ImageRegistrationMethod();
        R.setMetricAsJointHistogramMutualInformation();

        double learningRate = 5.0;
        int numberOfIterations = 100;
        double convergenceMinimumValue = 1e-4;
        int convergenceWindowSize = 5;
        R.setOptimizerAsGradientDescentLineSearch(learningRate, numberOfIterations,
                                                 convergenceMinimumValue, convergenceWindowSize);

        R.setInterpolator(InterpolatorEnum.sitkLinear);

        VectorUInt32 scaleFactors = new VectorUInt32();
        scaleFactors.add(1L); scaleFactors.add(2L); scaleFactors.add(5L);
        R.setInitialTransformAsBSpline(tx, true, scaleFactors);

        VectorUInt32 shrinkFactors = new VectorUInt32();
        shrinkFactors.add(4L); shrinkFactors.add(2L); shrinkFactors.add(1L);
        R.setShrinkFactorsPerLevel(shrinkFactors);

        VectorDouble smoothingSigmas = new VectorDouble();
        smoothingSigmas.add(4.0); smoothingSigmas.add(2.0); smoothingSigmas.add(1.0);
        R.setSmoothingSigmasPerLevel(smoothingSigmas);

        IterationUpdate cmd1 = new IterationUpdate(R, tx);
        R.addCommand(EventEnum.sitkIterationEvent, cmd1);

        MultiResolutionIterationUpdate cmd2 = new MultiResolutionIterationUpdate(R);
        R.addCommand(EventEnum.sitkMultiResolutionIterationEvent, cmd2);

        Transform outTx = R.execute(fixedImage, movingImage);

        System.out.println("-------");
        System.out.println(tx.toString());
        System.out.println(outTx.toString());
        System.out.println("Optimizer stop condition: " + R.getOptimizerStopConditionDescription());
        System.out.println(" Iteration: " + R.getOptimizerIteration());
        System.out.println(" Metric value: " + R.getMetricValue());

        SimpleITK.writeTransform(outTx, args[2]);

        if (System.getenv("SITK_NOSHOW") == null) {
            ResampleImageFilter resampler = new ResampleImageFilter();
            resampler.setReferenceImage(fixedImage);
            resampler.setInterpolator(InterpolatorEnum.sitkLinear);
            resampler.setDefaultPixelValue(100);
            resampler.setTransform(outTx);

            Image outputImage = resampler.execute(movingImage);
            Image simg1 = SimpleITK.cast(SimpleITK.rescaleIntensity(fixedImage), PixelIDValueEnum.sitkUInt8);
            Image simg2 = SimpleITK.cast(SimpleITK.rescaleIntensity(outputImage), PixelIDValueEnum.sitkUInt8);
            Image cimg = SimpleITK.compose(simg1, simg2, SimpleITK.divide(SimpleITK.add(simg1, simg2), 2.0));

            SimpleITK.show(cimg, "Image Registration Composition");
        }
    }
}
