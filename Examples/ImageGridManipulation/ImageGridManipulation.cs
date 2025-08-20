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
/// A SimpleITK example demonstrating various image grid manipulation
/// techniques.
/// </summary>

using System;
using itk.simple;

namespace itk.simple.examples
{
    class ImageGridManipulation
    {
        static void Main(string[] args)
        {
            if (args.Length < 2)
            {
                Console.WriteLine("Usage: {0} <input-1> <input-2>",
                    System.AppDomain.CurrentDomain.FriendlyName);
                return;
            }

            // Two vector images of same pixel type and dimension expected
            Image image1 = SimpleITK.ReadImage(args[0]);
            Image image2 = SimpleITK.ReadImage(args[1]);

            // Join two N-D Vector images to form an (N+1)-D image
            JoinSeriesImageFilter join = new JoinSeriesImageFilter();
            Image joinedImage = join.Execute(image1, image2);

            // Extract first three channels of joined image (assuming RGB)
            VectorIndexSelectionCastImageFilter select = new VectorIndexSelectionCastImageFilter();
            select.SetOutputPixelType(PixelIDValueEnum.sitkUInt8);

            select.SetIndex(0);
            Image channel1Image = select.Execute(joinedImage);
            select.SetIndex(1);
            Image channel2Image = select.Execute(joinedImage);
            select.SetIndex(2);
            Image channel3Image = select.Execute(joinedImage);

            // Recompose image (should be same as joined_image)
            ComposeImageFilter compose = new ComposeImageFilter();
            Image composedImage = compose.Execute(channel1Image, channel2Image, channel3Image);

            // Select same subregion using ExtractImageFilter
            ExtractImageFilter extract = new ExtractImageFilter();
            VectorUInt32 size = new VectorUInt32(new uint[] { 30, 30, 0 });
            VectorInt32 index = new VectorInt32(new int[] { 10, 10, 0 });
            extract.SetSize(size);
            extract.SetIndex(index);
            Image extractedImage = extract.Execute(composedImage);

            // Select same sub-region using CropImageFilter (NOTE: CropImageFilter cannot
            // reduce dimensions unlike ExtractImageFilter, so cropped_image is a three
            // dimensional image with depth of 1)
            CropImageFilter crop = new CropImageFilter();
            VectorUInt32 lowerBoundary = new VectorUInt32(new uint[] { 10, 10, 0 });
            VectorUInt32 upperBoundary = new VectorUInt32(new uint[] {
                composedImage.GetWidth() - 40,
                composedImage.GetHeight() - 40,
                1
            });
            crop.SetLowerBoundaryCropSize(lowerBoundary);
            crop.SetUpperBoundaryCropSize(upperBoundary);
            Image croppedImage = crop.Execute(composedImage);
        }
    }
}
