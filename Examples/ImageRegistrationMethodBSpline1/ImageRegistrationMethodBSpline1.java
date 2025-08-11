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

/**
 * A SimpleITK example demonstrating image registration using the
 * BSplineTransform and the ComplexCorrelation metric.
 */

import org.itk.simple.*;
import java.text.DecimalFormat;

class IterationUpdate extends Command {
    private ImageRegistrationMethod method;

    public IterationUpdate(ImageRegistrationMethod m) {
        method = m;
    }

    public void execute() {
        DecimalFormat df = new DecimalFormat("0.00000");
        System.out.println(String.format("%3d = %10s",
                          method.getOptimizerIteration(),
                          df.format(method.getMetricValue())));
    }
}

public class ImageRegistrationMethodBSpline1 {

    public static void main(String[] args) throws Exception {
        if (args.length < 3) {
            System.out.println("Usage: ImageRegistrationMethodBSpline1 <fixedImageFile> <movingImageFile> <outputTransformFile>");
            System.exit(1);
        }

        Image fixedImage = SimpleITK.readImage(args[0], PixelIDValueEnum.sitkFloat32);
        Image movingImage = SimpleITK.readImage(args[1], PixelIDValueEnum.sitkFloat32);

        // Create transform domain mesh size vector
        VectorUInt32 transformDomainMeshSize = new VectorUInt32();
        for (int i = 0; i < movingImage.getDimension(); i++) {
            transformDomainMeshSize.add(8L);
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
        R.setMetricAsCorrelation();

        R.setOptimizerAsLBFGSB(1e-5, 100, 5, 1000, 1e7);

        R.setInitialTransform(tx, true);
        R.setInterpolator(InterpolatorEnum.sitkLinear);

        IterationUpdate cmd = new IterationUpdate(R);
        R.addCommand(EventEnum.sitkIterationEvent, cmd);

        Transform outTx = R.execute(fixedImage, movingImage);

        System.out.println("-------");
        System.out.println(outTx.toString());
        System.out.println("Optimizer stop condition: " + R.getOptimizerStopConditionDescription());
        System.out.println(" Iteration: " + R.getOptimizerIteration());
        System.out.println(" Metric value: " + R.getMetricValue());

        SimpleITK.writeTransform(outTx, args[2]);

        ResampleImageFilter resampler = new ResampleImageFilter();
        resampler.setReferenceImage(fixedImage);
        resampler.setInterpolator(InterpolatorEnum.sitkLinear);
        resampler.setDefaultPixelValue(100);
        resampler.setTransform(outTx);

        Image outputImage = resampler.execute(movingImage);
        Image simg1 = SimpleITK.cast(SimpleITK.rescaleIntensity(fixedImage), PixelIDValueEnum.sitkUInt8);
        Image simg2 = SimpleITK.cast(SimpleITK.rescaleIntensity(outputImage), PixelIDValueEnum.sitkUInt8);
        Image cimg = SimpleITK.compose(simg1, simg2, SimpleITK.divide(SimpleITK.add(simg1, simg2), 2));

        if (System.getenv("SITK_NOSHOW") == null) {
            SimpleITK.show(cimg, "ImageRegistrationMethodBSpline1 Composition");
        }
    }
}
