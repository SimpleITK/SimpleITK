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

// A SimpleITK example demonstrating various image grid manipulation
// techniques.

import org.itk.simple.*;

class ImageGridManipulation {

    public static void main(String[] args) {

        if (args.length < 2) {
            System.out.println("Usage: ImageGridManipulation <input-1> <input-2>");
            return;
        }

        // Two vector images of same pixel type and dimension expected
        Image image1 = SimpleITK.readImage(args[0]);
        Image image2 = SimpleITK.readImage(args[1]);

        // Join two N-D Vector images to form an (N+1)-D image
        JoinSeriesImageFilter join = new JoinSeriesImageFilter();
        Image joinedImage = join.execute(image1, image2);

        // Extract first three channels of joined image (assuming RGB)
        VectorIndexSelectionCastImageFilter select = new VectorIndexSelectionCastImageFilter();
        select.setOutputPixelType(PixelIDValueEnum.sitkUInt8);

        select.setIndex(0);
        Image channel1Image = select.execute(joinedImage);
        select.setIndex(1);
        Image channel2Image = select.execute(joinedImage);
        select.setIndex(2);
        Image channel3Image = select.execute(joinedImage);

        // Recompose image (should be same as joined_image)
        ComposeImageFilter compose = new ComposeImageFilter();
        Image composedImage = compose.execute(channel1Image, channel2Image, channel3Image);

        // Select same subregion using ExtractImageFilter
        ExtractImageFilter extract = new ExtractImageFilter();
        VectorUInt32 size = new VectorUInt32();
        size.add(30L); size.add(30L); size.add(0L);
        VectorInt32 index = new VectorInt32();
        index.add(10); index.add(10); index.add(0);
        extract.setSize(size);
        extract.setIndex(index);
        Image extractedImage = extract.execute(composedImage);

        // Select same sub-region using CropImageFilter (NOTE: CropImageFilter cannot
        // reduce dimensions unlike ExtractImageFilter, so cropped_image is a three
        // dimensional image with depth of 1)
        CropImageFilter crop = new CropImageFilter();
        VectorUInt32 lowerBoundary = new VectorUInt32();
        lowerBoundary.add(10L); lowerBoundary.add(10L); lowerBoundary.add(0L);
        VectorUInt32 upperBoundary = new VectorUInt32();
        upperBoundary.add((long)(composedImage.getWidth() - 40));
        upperBoundary.add((long)(composedImage.getHeight() - 40));
        upperBoundary.add(1L);
        crop.setLowerBoundaryCropSize(lowerBoundary);
        crop.setUpperBoundaryCropSize(upperBoundary);
        Image croppedImage = crop.execute(composedImage);
    }
}
