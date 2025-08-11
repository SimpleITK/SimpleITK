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
            System.out.print("Scales: ["+scales.get(0));
            for (int i = 1; i < scales.size(); i++) {
                System.out.print(", " + scales.get(i));
            }
            System.out.println("]");
        }

        VectorDouble pos = method.getOptimizerPosition();
        DecimalFormat df = new DecimalFormat("0.00000");
        System.out.print(String.format("%3d = %7s : [",
                        method.getOptimizerIteration(),
                        df.format(method.getMetricValue())) + df.format(pos.get(0)));
        for (int i = 1; i < pos.size(); i++) {
            System.out.print(", " + df.format(pos.get(i)));
        }
        System.out.println("]");
    }
}

public class ImageRegistrationMethodExhaustive {

    public static void main(String[] args) throws Exception {
        if (args.length < 3) {
            System.out.println("Usage: ImageRegistrationMethodExhaustive <fixedImageFile> <movingImageFile> <outputTransformFile>");
            System.exit(1);
        }

        Image fixedImage = SimpleITK.readImage(args[0], PixelIDValueEnum.sitkFloat32);
        Image movingImage = SimpleITK.readImage(args[1], PixelIDValueEnum.sitkFloat32);

        ImageRegistrationMethod R = new ImageRegistrationMethod();

        R.setMetricAsMattesMutualInformation(50); // numberOfHistogramBins

        long samplePerAxis = 12;
        Transform tx = null;

        if (fixedImage.getDimension() == 2) {
            tx = new Euler2DTransform();
            // Set the number of samples (radius) in each dimension, with a default step size of 1.0
            VectorUInt32 exhaustiveSteps = new VectorUInt32();
            exhaustiveSteps.add(samplePerAxis / 2);
            exhaustiveSteps.add(0L);
            exhaustiveSteps.add(0L);
            R.setOptimizerAsExhaustive(exhaustiveSteps);
            // Utilize the scale to set the step size for each dimension
            VectorDouble scales = new VectorDouble();
            scales.add(2.0 * Math.PI / samplePerAxis);
            scales.add(1.0);
            scales.add(1.0);
            R.setOptimizerScales(scales);
        } else if (fixedImage.getDimension() == 3) {
            tx = new Euler3DTransform();
            VectorUInt32 exhaustiveSteps = new VectorUInt32();
            exhaustiveSteps.add(samplePerAxis / 2);
            exhaustiveSteps.add(samplePerAxis / 2);
            exhaustiveSteps.add(samplePerAxis / 4);
            exhaustiveSteps.add(0L);
            exhaustiveSteps.add(0L);
            exhaustiveSteps.add(0L);
            R.setOptimizerAsExhaustive(exhaustiveSteps);
            VectorDouble scales = new VectorDouble();
            scales.add(2.0 * Math.PI / samplePerAxis);
            scales.add(2.0 * Math.PI / samplePerAxis);
            scales.add(2.0 * Math.PI / samplePerAxis);
            scales.add(1.0);
            scales.add(1.0);
            scales.add(1.0);
            R.setOptimizerScales(scales);
        }

        // Initialize the transform with a translation and the center of rotation from the moments of intensity.
        tx = SimpleITK.centeredTransformInitializer(fixedImage, movingImage, tx);

        R.setInitialTransform(tx);
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

        if (System.getenv("SITK_NOSHOW") == null) {
            ResampleImageFilter resampler = new ResampleImageFilter();
            resampler.setReferenceImage(fixedImage);
            resampler.setInterpolator(InterpolatorEnum.sitkLinear);
            resampler.setDefaultPixelValue(1);
            resampler.setTransform(outTx);

            Image output = resampler.execute(movingImage);

            Image simg1 = SimpleITK.cast(SimpleITK.rescaleIntensity(fixedImage), PixelIDValueEnum.sitkUInt8);
            Image simg2 = SimpleITK.cast(SimpleITK.rescaleIntensity(output), PixelIDValueEnum.sitkUInt8);
            Image cimg = SimpleITK.compose(simg1, simg2, SimpleITK.divide(SimpleITK.add(simg1, simg2), 2.0));
            SimpleITK.show(cimg, "ImageRegistrationExhaustive Composition");
        }
    }
}
