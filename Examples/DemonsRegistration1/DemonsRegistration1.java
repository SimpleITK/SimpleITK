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

// A SimpleITK example demonstrating the classic Demons image registration.

import org.itk.simple.Image;
import org.itk.simple.SimpleITK;
import org.itk.simple.HistogramMatchingImageFilter;
import org.itk.simple.DemonsRegistrationFilter;
import org.itk.simple.Transform;
import org.itk.simple.PixelIDValueEnum;
import org.itk.simple.EventEnum;
import org.itk.simple.Command;

public class DemonsRegistration1 {
    public static void main(String[] args) {
        if (args.length < 3) {
            System.out.println("Usage: DemonsRegistration1 <fixedImageFile> <movingImageFile> <outputTransformFile>");
            System.exit(1);
        }

        // Read the fixed and moving images as float32
        Image fixed = SimpleITK.readImage(args[0], PixelIDValueEnum.sitkFloat32);
        Image moving = SimpleITK.readImage(args[1], PixelIDValueEnum.sitkFloat32);

        // Perform histogram matching of the moving image to the fixed image
        HistogramMatchingImageFilter matcher = new HistogramMatchingImageFilter();
        matcher.setNumberOfHistogramLevels(1024);
        matcher.setNumberOfMatchPoints(7);
        matcher.thresholdAtMeanIntensityOn();
        moving = matcher.execute(moving, fixed);

        // The basic Demons Registration Filter
        // Note there is a whole family of Demons Registration algorithms included in SimpleITK
        DemonsRegistrationFilter demons = new DemonsRegistrationFilter();
        demons.setNumberOfIterations(50);
        // Standard deviation for Gaussian smoothing of displacement field
        demons.setStandardDeviations(1.0);

        // Add iteration callback
        IterationUpdate cmd = new IterationUpdate(demons);
        demons.addCommand(EventEnum.sitkIterationEvent, cmd);

        Image displacementField = demons.execute(fixed, moving);

        System.out.println("-------");
        System.out.println("Number Of Iterations: " + demons.getElapsedIterations());
        System.out.println(" RMS: " + demons.getRMSChange());

        // Create and write the displacement field transform
        Transform outTx = new org.itk.simple.DisplacementFieldTransform(displacementField);
        SimpleITK.writeTransform(outTx, args[2]);
    }

    // Callback class for iteration events
    static class IterationUpdate extends Command {
        private DemonsRegistrationFilter filter;

        public IterationUpdate(DemonsRegistrationFilter filter) {
            super();
            this.filter = filter;
        }

        public void execute() {
            System.out.format("%3d = %10.5f\n", filter.getElapsedIterations(), filter.getMetric());
        }
    }
}
