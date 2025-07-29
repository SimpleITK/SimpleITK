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
        VectorDouble pos = method.getOptimizerPosition();
        DecimalFormat df = new DecimalFormat("0.00000");
        System.out.print(String.format("%3d = %10s : [",
                        method.getOptimizerIteration(),
                        df.format(method.getMetricValue())));
        for (int i = 0; i < pos.size(); i++) {
            if (i > 0) System.out.print(", ");
            System.out.print(df.format(pos.get(i)));
        }
        System.out.println("]");
    }
}

public class ImageRegistrationMethod4 {

    public static void main(String[] args) throws Exception {
        if (args.length < 3) {
            System.out.println("Usage: ImageRegistrationMethod4 <fixedImageFile> <movingImageFile> <outputTransformFile> [numberOfBins] [samplingPercentage]");
            System.exit(1);
        }

        Image fixed = SimpleITK.readImage(args[0], PixelIDValueEnum.sitkFloat32);
        Image moving = SimpleITK.readImage(args[1], PixelIDValueEnum.sitkFloat32);

        int numberOfBins = 24;
        double samplingPercentage = 0.10;

        if (args.length > 3) {
            numberOfBins = Integer.parseInt(args[3]);
        }
        if (args.length > 4) {
            samplingPercentage = Double.parseDouble(args[4]);
        }

        ImageRegistrationMethod R = new ImageRegistrationMethod();
        R.setMetricAsMattesMutualInformation(numberOfBins);
        R.setMetricSamplingPercentage(samplingPercentage);
        R.setMetricSamplingStrategy(ImageRegistrationMethod.MetricSamplingStrategyType.RANDOM);
        R.setOptimizerAsRegularStepGradientDescent(1.0, 0.001, 200);
        R.setInitialTransform(new TranslationTransform(fixed.getDimension()));
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

        // Show the composition image if SITK_NOSHOW environment variable is not set
        if (System.getenv("SITK_NOSHOW") == null) {
            SimpleITK.show(cimg, "ImageRegistration4 Composition");
        }
    }
}
