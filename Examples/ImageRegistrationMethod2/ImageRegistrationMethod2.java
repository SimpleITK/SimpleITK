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
        System.out.println(String.format("%3d = %10s : [%s, %s]",
                          method.getOptimizerIteration(),
                          df.format(method.getMetricValue()),
                          df.format(pos.get(0)), df.format(pos.get(1))));
    }
}

public class ImageRegistrationMethod2 {

    public static void main(String[] args) throws Exception {
        if (args.length < 3) {
            System.out.println("Usage: ImageRegistrationMethod2 <fixedImageFile> <movingImageFile> <outputTransformFile>");
            System.exit(1);
        }

        ImageFileReader reader = new ImageFileReader();
        reader.setOutputPixelType(PixelIDValueEnum.sitkFloat32);

        reader.setFileName(args[0]);
        Image fixedImage = reader.execute();
        fixedImage = SimpleITK.normalize(fixedImage);
        fixedImage = SimpleITK.discreteGaussian(fixedImage, 2.0);

        reader.setFileName(args[1]);
        Image movingImage = reader.execute();
        movingImage = SimpleITK.normalize(movingImage);
        movingImage = SimpleITK.discreteGaussian(movingImage, 2.0);

        ImageRegistrationMethod R = new ImageRegistrationMethod();
        R.setMetricAsJointHistogramMutualInformation();

        double learningRate = 1.0;
        int numberOfIterations = 200;
        double convergenceMinimumValue = 1e-4;
        int convergenceWindowSize = 5;

        R.setOptimizerAsGradientDescentLineSearch(learningRate,
                                                  numberOfIterations,
                                                  convergenceMinimumValue,
                                                  convergenceWindowSize);

        R.setInitialTransform(new TranslationTransform(fixedImage.getDimension()));
        R.setInterpolator(InterpolatorEnum.sitkLinear);

        IterationUpdate cmd = new IterationUpdate(R);
        R.addCommand(EventEnum.sitkIterationEvent, cmd);

        Transform outTx = R.execute(fixedImage, movingImage);

        outTx.writeTransform(args[2]);
    }
}
