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
 * A SimpleITK example demonstrating landmark registration.
 */

import org.itk.simple.*;

public class LandmarkRegistration {

    public static void main(String[] args) throws Exception {

        // Black image with a small white square in it.
        Image fixedImage = new Image(100, 100, PixelIDValueEnum.sitkUInt8);
        // Set pixels in rectangle [11:20, 11:20] to 200
        for (long x = 11; x < 20; ++x) {
            for (long y = 11; y < 20; ++y) {
                VectorUInt32 idx = new VectorUInt32();
                idx.add(x);
                idx.add(y);
                fixedImage.setPixelAsUInt8(idx, (short)200);
            }
        }

        // Black image with a small grey square at a different location.
        Image movingImage = new Image(100, 100, PixelIDValueEnum.sitkUInt8);
        // Set pixels in rectangle [51:60, 51:60] to 69
        for (long x = 51; x < 60; ++x) {
            for (long y = 51; y < 60; ++y) {
                VectorUInt32 idx = new VectorUInt32();
                idx.add(x);
                idx.add(y);
                movingImage.setPixelAsUInt8(idx, (short)69);
            }
        }

        // Landmarks are 3 corners of the squares.
        // 3 (X, Y) pairs are flattened into 1-d lists.
        VectorDouble fixedLandmarks = new VectorDouble();
        fixedLandmarks.add(10.0); fixedLandmarks.add(10.0);
        fixedLandmarks.add(20.0); fixedLandmarks.add(10.0);
        fixedLandmarks.add(20.0); fixedLandmarks.add(20.0);

        VectorDouble movingLandmarks = new VectorDouble();
        movingLandmarks.add(50.0); movingLandmarks.add(50.0);
        movingLandmarks.add(60.0); movingLandmarks.add(50.0);
        movingLandmarks.add(60.0); movingLandmarks.add(60.0);

        // Set up the LandmarkBasedTransformInitializerFilter.
        LandmarkBasedTransformInitializerFilter landmarkInitializer = new LandmarkBasedTransformInitializerFilter();

        landmarkInitializer.setFixedLandmarks(fixedLandmarks);
        landmarkInitializer.setMovingLandmarks(movingLandmarks);

        Transform transform = new Euler2DTransform();

        // Compute the transform.
        Transform outputTransform = landmarkInitializer.execute(transform);

        System.out.println(outputTransform.toString());

        // Resample the transformed moving image onto the fixed image.
        Image outputImage = SimpleITK.resample(movingImage, fixedImage, outputTransform, InterpolatorEnum.sitkLinear, 150);

        // Write the resampled image.
        SimpleITK.writeImage(outputImage, "landmark_example.png");

        // Write the transform.
        String outName;
        if (args.length > 0) {
            outName = args[0];
        } else {
            outName = "landmark_transform.tfm";
        }

        SimpleITK.writeTransform(outputTransform, outName);
    }
}
