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
import java.text.DecimalFormat;

class IterationUpdate extends Command {
    private ImageRegistrationMethod method;

    public IterationUpdate(ImageRegistrationMethod m) {
        method = m;
    }

    public void execute() {
        if (method.getOptimizerIteration() == 0) {
            VectorDouble scales = method.getOptimizerScales();
            System.out.print("Estimated Scales: [" + scales.get(0));
            for (int i = 1; i < scales.size(); i++) {
                System.out.print(", " + scales.get(i));
            }
            System.out.println("]");
        }

        VectorDouble pos = method.getOptimizerPosition();
        DecimalFormat df = new DecimalFormat("0.00000");
        System.out.print(String.format("%3d = %7s : [",
                        method.getOptimizerIteration(),
                        df.format(method.getMetricValue())));
        System.out.print(df.format(pos.get(0)));
        for (int i = 1; i < pos.size(); i++) {
            System.out.print(", " + df.format(pos.get(i)));
        }
        System.out.println("]");
    }
}

public class ImageRegistrationMethod3 {

    public static void main(String[] args) throws Exception {
        if (args.length < 3) {
            System.out.println("Usage: ImageRegistrationMethod3 <fixedImageFile> <movingImageFile> <outputTransformFile>");
            System.exit(1);
        }

        Image fixed = SimpleITK.readImage(args[0], PixelIDValueEnum.sitkFloat32);

        Image moving = SimpleITK.readImage(args[1], PixelIDValueEnum.sitkFloat32);

        ImageRegistrationMethod R = new ImageRegistrationMethod();

        R.setMetricAsCorrelation();

        R.setOptimizerAsRegularStepGradientDescent(2.0,   // learningRate
                                                   1e-4,  // minStep
                                                   500,   // numberOfIterations
                                                   0.5,   // relaxationFactor
                                                   1e-8); // gradientMagnitudeTolerance
        R.setOptimizerScalesFromIndexShift();

        Transform tx = SimpleITK.centeredTransformInitializer(fixed, moving, new Similarity2DTransform());
        R.setInitialTransform(tx);

        R.setInterpolator(InterpolatorEnum.sitkLinear);

        IterationUpdate cmd = new IterationUpdate(R);
        R.addCommand(EventEnum.sitkIterationEvent, cmd);

        Transform outTx = R.execute(fixed, moving);

        System.out.println("-------");
        System.out.println(outTx.toString());
        System.out.println("Optimizer stop condition: " + R.getOptimizerStopConditionDescription());
        System.out.println(" Iteration: " + R.getOptimizerIteration());
        System.out.println(" Metric value: " + R.getMetricValue());

        SimpleITK.writeTransform(outTx, args[2]);

        ResampleImageFilter resampler = new ResampleImageFilter();
        resampler.setReferenceImage(fixed);
        resampler.setInterpolator(InterpolatorEnum.sitkLinear);
        resampler.setDefaultPixelValue(100);
        resampler.setTransform(outTx);

        Image output = resampler.execute(moving);

        Image simg1 = SimpleITK.cast(SimpleITK.rescaleIntensity(fixed), PixelIDValueEnum.sitkUInt8);
        Image simg2 = SimpleITK.cast(SimpleITK.rescaleIntensity(output), PixelIDValueEnum.sitkUInt8);
        Image cimg = SimpleITK.compose(simg1, simg2, SimpleITK.divide(SimpleITK.add(simg1, simg2), 2.0));

        if (System.getenv("SITK_NOSHOW") == null) {
            SimpleITK.show(cimg, "ImageRegistration3 Composition");
        }
    }
}
