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
 * A SimpleITK example demonstrating N4 bias field correction.
 */

import org.itk.simple.*;

public class N4BiasFieldCorrection {

    public static void main(String[] args) throws Exception {
        if (args.length < 2) {
            System.out.println("Usage: N4BiasFieldCorrection inputImage outputImage"
                + " [shrinkFactor] [maskImage] [numberOfIterations]"
                + " [numberOfFittingLevels]");
            return;
        }

        // Read input image
        Image inputImage = SimpleITK.readImage(args[0], PixelIDValueEnum.sitkFloat32);
        Image image = inputImage;

        Image maskImage;
        if (args.length > 3) {
            maskImage = SimpleITK.readImage(args[3], PixelIDValueEnum.sitkUInt8);
        } else {
            maskImage = SimpleITK.otsuThreshold(image, (short)0, (short)1, 200);
        }

        long shrinkFactor = 1;
        if (args.length > 2) {
            shrinkFactor = Long.parseLong(args[2]);
            VectorUInt32 shrink = new VectorUInt32();
            for (long i = 0; i < image.getDimension(); i++) {
                shrink.add(shrinkFactor);
            }
            image = SimpleITK.shrink(inputImage, shrink);
            maskImage = SimpleITK.shrink(maskImage, shrink);
        }

        N4BiasFieldCorrectionImageFilter corrector = new N4BiasFieldCorrectionImageFilter();

        long numFittingLevels = 4;

        if (args.length > 5) {
            numFittingLevels = Long.parseLong(args[5]);
        }

        if (args.length > 4) {
            long it = Long.parseLong(args[4]);
            VectorUInt32 iterations = new VectorUInt32();
            for (long i = 0; i < numFittingLevels; i++) {
                iterations.add(it);
            }
            corrector.setMaximumNumberOfIterations(iterations);
        }

        Image correctedImage = corrector.execute(image, maskImage);

        Image logBiasField = corrector.getLogBiasFieldAsImage(inputImage);

        Image correctedImageFullResolution = SimpleITK.divide(inputImage, SimpleITK.exp(logBiasField));

        SimpleITK.writeImage(correctedImageFullResolution, args[1]);

        if (shrinkFactor > 1) {
            SimpleITK.writeImage(correctedImage, "Java-Example-N4BiasFieldCorrection-shrunk.nrrd");
        }

        if (System.getenv("SITK_NOSHOW") == null) {
            SimpleITK.show(correctedImage, "N4 Corrected");
        }
    }
}
