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
// BSplineTransform and the MattesMutualInformation metric.

import org.itk.simple.*;

class IterationUpdate extends Command {
    private ImageRegistrationMethod method;

    public IterationUpdate(ImageRegistrationMethod m) {
        method = m;
    }

    public void execute() {
        System.out.printf("%3d", method.getOptimizerIteration());
        System.out.printf(" = %10.5f%n", method.getMetricValue());
        System.out.println("\t#: " + method.getOptimizerPosition().size());
    }
}

class MultiResolutionIterationUpdate extends Command {
    private ImageRegistrationMethod method;

    public MultiResolutionIterationUpdate(ImageRegistrationMethod m) {
        method = m;
    }

    public void execute() {
        System.out.println("--------- Resolution Changing ---------");
    }
}

class ImageRegistrationMethodBSpline2 {

    public static void main(String[] args) {

        if (args.length < 3) {
            System.out.println("Usage: ImageRegistrationMethodBSpline2 <fixedImageFile> <movingImageFile> <outputTransformFile>");
            return;
        }

        Image fixedImage = SimpleITK.readImage(args[0], PixelIDValueEnum.sitkFloat32);
        Image movingImage = SimpleITK.readImage(args[1], PixelIDValueEnum.sitkFloat32);

        // Create transform domain mesh size vector
        VectorUInt32 transformDomainMeshSize = new VectorUInt32();
        for (int i = 0; i < movingImage.getDimension(); i++) {
            transformDomainMeshSize.add(10L);
        }

        Transform tx = SimpleITK.bSplineTransformInitializer(fixedImage, transformDomainMeshSize);

        System.out.println("Initial Parameters:");
        VectorDouble initialParams = tx.getParameters();
        System.out.print("[");
        System.out.printf("%.5f", initialParams.get(0));
        for (int i = 1; i < initialParams.size(); i++) {
            System.out.printf(", %.5f", initialParams.get(i));
        }
        System.out.println("]");

        ImageRegistrationMethod R = new ImageRegistrationMethod();
        R.setMetricAsMattesMutualInformation(50);

        double learningRate = 5.0;
        int numberOfIterations = 100;
        double convergenceMinimumValue = 1e-4;
        int convergenceWindowSize = 5;
        R.setOptimizerAsGradientDescentLineSearch(learningRate, numberOfIterations, convergenceMinimumValue, convergenceWindowSize);
        R.setOptimizerScalesFromPhysicalShift();
        R.setInitialTransform(tx);
        R.setInterpolator(InterpolatorEnum.sitkLinear);

        VectorUInt32 shrinkFactors = new VectorUInt32();
        shrinkFactors.add(6L); shrinkFactors.add(2L); shrinkFactors.add(1L);
        R.setShrinkFactorsPerLevel(shrinkFactors);

        VectorDouble smoothingSigmas = new VectorDouble();
        smoothingSigmas.add(6.0); smoothingSigmas.add(2.0); smoothingSigmas.add(1.0);
        R.setSmoothingSigmasPerLevel(smoothingSigmas);

        IterationUpdate cmd1 = new IterationUpdate(R);
        R.addCommand(EventEnum.sitkIterationEvent, cmd1);

        MultiResolutionIterationUpdate cmd2 = new MultiResolutionIterationUpdate(R);
        R.addCommand(EventEnum.sitkMultiResolutionIterationEvent, cmd2);

        Transform outTx = R.execute(fixedImage, movingImage);

        System.out.println("-------");
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

            SimpleITK.show(cimg, "ImageRegistrationMethodBSpline2 Composition");
        }
    }
}
