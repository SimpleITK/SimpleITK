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

// A SimpleITK example demonstrating fast symmetric forces Demons image registration.

import org.itk.simple.*;

public class DemonsRegistration2 {
    public static void main(String[] args) {
        if (args.length < 3) {
            System.out.println("Usage: DemonsRegistration2 <fixedImageFile> <movingImageFile> [initialTransformFile] <outputTransformFile>");
            System.exit(1);
        }

        // Read the fixed and moving images
        Image fixed = SimpleITK.readImage(args[0]);
        Image moving = SimpleITK.readImage(args[1]);

        // Perform histogram matching of the moving image to the fixed image
        HistogramMatchingImageFilter matcher = new HistogramMatchingImageFilter();
        if (fixed.getPixelID() == PixelIDValueEnum.sitkUInt8 || fixed.getPixelID() == PixelIDValueEnum.sitkInt8) {
            matcher.setNumberOfHistogramLevels(128);
        } else {
            matcher.setNumberOfHistogramLevels(1024);
        }
        matcher.setNumberOfMatchPoints(7);
        matcher.thresholdAtMeanIntensityOn();
        moving = matcher.execute(moving, fixed);

        // The fast symmetric forces Demons Registration Filter
        // Note there is a whole family of Demons Registration algorithms included in SimpleITK
        FastSymmetricForcesDemonsRegistrationFilter demons = new FastSymmetricForcesDemonsRegistrationFilter();
        demons.setNumberOfIterations(200);
        // Standard deviation for Gaussian smoothing of displacement field
        demons.setStandardDeviations(1.0);

        // Add iteration callback
        IterationUpdate cmd = new IterationUpdate(demons);
        demons.addCommand(EventEnum.sitkIterationEvent, cmd);

        Image displacementField;
        if (args.length > 3) {
            Transform initialTransform = SimpleITK.readTransform(args[2]);
            // Shift output argument
            String outputTransformFile = args[3];
            TransformToDisplacementFieldFilter toDisplacementFilter = new TransformToDisplacementFieldFilter();
            toDisplacementFilter.setReferenceImage(fixed);
            displacementField = toDisplacementFilter.execute(initialTransform);
            displacementField = demons.execute(fixed, moving, displacementField);
            // Write output
            Transform outTx = new DisplacementFieldTransform(displacementField);
            SimpleITK.writeTransform(outTx, outputTransformFile);
        } else {
            displacementField = demons.execute(fixed, moving);
            Transform outTx = new DisplacementFieldTransform(displacementField);
            SimpleITK.writeTransform(outTx, args[2]);
        }

        System.out.println("-------");
        System.out.println("Number Of Iterations: " + demons.getElapsedIterations());
        System.out.println(" RMS: " + demons.getRMSChange());

        // Visualization (if SITK_NOSHOW is not set)
        if (System.getenv("SITK_NOSHOW") == null) {
            ResampleImageFilter resampler = new ResampleImageFilter();
            resampler.setReferenceImage(fixed);
            resampler.setInterpolator(InterpolatorEnum.sitkLinear);
            resampler.setDefaultPixelValue(100);
            resampler.setTransform(new DisplacementFieldTransform(displacementField));

            Image out = resampler.execute(moving);
            Image simg1 = SimpleITK.cast(SimpleITK.rescaleIntensity(fixed), PixelIDValueEnum.sitkUInt8);
            Image simg2 = SimpleITK.cast(SimpleITK.rescaleIntensity(out), PixelIDValueEnum.sitkUInt8);
            Image cimg = SimpleITK.compose(simg1, simg2, SimpleITK.add(SimpleITK.divide(simg1, 2.0), SimpleITK.divide(simg2, 2.0)));
            SimpleITK.show(cimg, "DeformableRegistration2 Composition");
        }
    }

    // Callback class for iteration events
    static class IterationUpdate extends Command {
        private FastSymmetricForcesDemonsRegistrationFilter filter;
        public IterationUpdate(FastSymmetricForcesDemonsRegistrationFilter filter) {
            super();
            this.filter = filter;
        }
        public void execute() {
            System.out.format("%3d = %10.5f\n", filter.getElapsedIterations(), filter.getMetric());
        }
    }
}
