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

/// <summary>
/// A SimpleITK example demonstrating landmark registration.
/// </summary>

using System;
using itk.simple;

namespace itk.simple.examples
{
    class LandmarkRegistration
    {
        static void Main(string[] args)
        {
            // Black image with a small white square in it.
            Image fixedImage = new Image(100, 100, PixelIDValueEnum.sitkUInt8);
            // Paste a white square (9x9 pixels with value 200) at position [11, 11]
            PasteImageFilter pasteFilter = new PasteImageFilter();
            pasteFilter.SetSourceSize(new VectorUInt32(new uint[] {9, 9}));
            pasteFilter.SetSourceIndex(new VectorInt32(new int[] {0, 0}));
            pasteFilter.SetDestinationIndex(new VectorInt32(new int[] {11, 11}));
            fixedImage = pasteFilter.Execute(fixedImage, 200);

            // Black image with a small grey square at a different location.
            Image movingImage = new Image(100, 100, PixelIDValueEnum.sitkUInt8);
            // Paste a grey square (9x9 pixels with value 69) at position [51, 51]
            pasteFilter.SetDestinationIndex(new VectorInt32(new int[] {51, 51}));
            movingImage = pasteFilter.Execute(movingImage, 69);

            // Landmarks are 3 corners of the squares.
            // 3 (X, Y) pairs are flattened into 1-d lists.
            VectorDouble fixedLandmarks = new VectorDouble(new double[] {10, 10, 20, 10, 20, 20});
            VectorDouble movingLandmarks = new VectorDouble(new double[] {50, 50, 60, 50, 60, 60});

            // Set up the LandmarkBasedTransformInitializerFilter.
            LandmarkBasedTransformInitializerFilter landmarkInitializer = new LandmarkBasedTransformInitializerFilter();

            landmarkInitializer.SetFixedLandmarks(fixedLandmarks);
            landmarkInitializer.SetMovingLandmarks(movingLandmarks);

            Transform transform = new Euler2DTransform();

            // Compute the transform.
            Transform outputTransform = landmarkInitializer.Execute(transform);

            Console.WriteLine(outputTransform.ToString());

            // Resample the transformed moving image onto the fixed image.
            Image outputImage = SimpleITK.Resample(movingImage, fixedImage, outputTransform, InterpolatorEnum.sitkLinear, 150);

            // Write the resampled image.
            SimpleITK.WriteImage(outputImage, "landmark_example.png");

            // Write the transform.
            string outName;
            if (args.Length > 0)
            {
                outName = args[0];
            }
            else
            {
                outName = "landmark_transform.tfm";
            }

            SimpleITK.WriteTransform(outputTransform, outName);
        }
    }
}
