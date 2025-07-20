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
 * A SimpleITK example demonstrating how to write a DICOM series.
 */

import org.itk.simple.*;
import java.io.*;
import java.util.*;
import java.text.SimpleDateFormat;
import java.nio.*;


public class DicomSeriesFromArray {
    private static ImageFileWriter writer = new ImageFileWriter();

    /**
     * Write slices to output directory
     */
    static void writeSlices(List<String[]> seriesTag, Image inImage, String outDir, int i) throws Exception {
      SliceImageFilter sliceFilter = new SliceImageFilter();
      sliceFilter.setStart(new VectorInt32(new int[]{0,0,i}));
      sliceFilter.setStep(1);
      sliceFilter.setStop(new VectorInt32(new int[]{0,0,i+1}));
      Image imageSlice = sliceFilter.execute(inImage);

        // Tags shared by the series.
        for (String[] tagValue : seriesTag) {
            imageSlice.setMetaData(tagValue[0], tagValue[1]);
        }

        // Slice specific tags.
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyyMMdd");
        SimpleDateFormat timeFormat = new SimpleDateFormat("HHmmss");
        Date now = new Date();

        // Instance Creation Date
        imageSlice.setMetaData("0008|0012", dateFormat.format(now));
        // Instance Creation Time
        imageSlice.setMetaData("0008|0013", timeFormat.format(now));

        // Setting the type to CT so that the slice location is preserved and
        // the thickness is carried over.
        imageSlice.setMetaData("0008|0060", "CT");

        // (0020, 0032) image position patient determines the 3D spacing between slices.
        // Image Position (Patient)
        VectorDouble position = inImage.transformIndexToPhysicalPoint(new VectorInt64(new long[]{0,0,i}));
        StringJoiner posJoiner = new StringJoiner("\\");
        for (int j = 0; j < position.size(); j++) {
            posJoiner.add(String.valueOf(position.get(j)));
        }
        imageSlice.setMetaData("0020|0032", posJoiner.toString());

        // Instance Number
        imageSlice.setMetaData("0020|0013", String.valueOf(i));

        // Write to the output directory and add the extension dcm, to force
        // writing in DICOM format.
        writer.setFileName(new File(outDir, i + ".dcm").getAbsolutePath());
        writer.execute(imageSlice);
    }

    public static void main(String[] args) throws Exception {
        if (args.length < 1) {
            System.out.println("Usage: DicomSeriesFromArray <output_directory>");
            System.exit(1);
        }

        // Set pixel type to sitkInt16 or sitkFloat64
        PixelIDValueEnum pixelType = PixelIDValueEnum.sitkInt16;

        // Create image from random data array based on the pixel type
        VectorUInt32 imageSize = new VectorUInt32();
        imageSize.add(512);
        imageSize.add(512);
        imageSize.add(256);

        int totalPixels = 512 * 512 * 256;
        Random rand = new Random();
        Image newImg;

        if (pixelType == PixelIDValueEnum.sitkInt16) {
            short[] randomData = new short[totalPixels];
            for (int i = 0; i < totalPixels; i++) {
                randomData[i] = (short)(rand.nextInt(2001) - 1000); // Range -1000 to 1000
            }
            newImg = SimpleITK.importAsInt16(randomData, imageSize);
        } else if (pixelType == PixelIDValueEnum.sitkFloat64) {
            double[] randomData = new double[totalPixels];
            for (int i = 0; i < totalPixels; i++) {
                randomData[i] = (rand.nextDouble() * 2000.0) - 1000.0; // Range -1000 to 1000
            }
            newImg = SimpleITK.importAsFloat64(randomData, imageSize);
        } else {
            throw new IllegalArgumentException("Unsupported pixel type");
        }

        newImg.setSpacing(new VectorDouble(new double[]{2.5, 3.5, 4.5}));

        // Write the 3D image as a series
        // IMPORTANT: There are many DICOM tags that need to be updated when you modify
        //            an original image. This is a delicate operation and requires
        //            knowledge of the DICOM standard. This example only modifies some.
        //            For a more complete list of tags that need to be modified see:
        //                  http://gdcm.sourceforge.net/wiki/index.php/Writing_DICOM
        //            If it is critical for your work to generate valid DICOM files,
        //            It is recommended to use David Clunie's Dicom3tools to validate
        //            the files:
        //                  http://www.dclunie.com/dicom3tools.html

        // Use the study/series/frame of reference information given in the meta-data
        // dictionary and not the automatically generated information from the file IO
        writer.keepOriginalImageUIDOn();

        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyyMMdd");
        SimpleDateFormat timeFormat = new SimpleDateFormat("HHmmss");
        Date now = new Date();
        String modificationTime = timeFormat.format(now);
        String modificationDate = dateFormat.format(now);

        // Copy some of the tags and add the relevant tags indicating the change.
        // For the series instance UID (0020|000e), each of the components is a number,
        // cannot start with zero, and separated by a '.' We create a unique series ID
        // using the date and time.
        VectorDouble direction = newImg.getDirection();
        List<String[]> seriesTagValues = new ArrayList<>();
        seriesTagValues.add(new String[]{"0008|0031", modificationTime}); // Series Time
        seriesTagValues.add(new String[]{"0008|0021", modificationDate}); // Series Date
        seriesTagValues.add(new String[]{"0008|0008", "DERIVED\\SECONDARY"}); // Image Type
        seriesTagValues.add(new String[]{"0020|000e", "1.2.826.0.1.3680043.2.1125." + modificationDate + ".1" + modificationTime}); // Series Instance UID

        // Image Orientation (Patient)
        String orientation = String.format("%f\\%f\\%f\\%f\\%f\\%f",
            direction.get(0), direction.get(3), direction.get(6),
            direction.get(1), direction.get(4), direction.get(7));
        seriesTagValues.add(new String[]{"0020|0037", orientation});
        seriesTagValues.add(new String[]{"0008|103e", "Created-SimpleITK"}); // Series Description

        if (pixelType == PixelIDValueEnum.sitkFloat64) {
            // If we want to write floating point values, we need to use the rescale
            // slope, "0028|1053", to select the number of digits we want to keep.
            double rescaleSlope = 0.001; // keep three digits after the decimal point
            seriesTagValues.add(new String[]{"0028|1053", String.valueOf(rescaleSlope)}); // rescale slope
            seriesTagValues.add(new String[]{"0028|1052", "0"}); // rescale intercept
            seriesTagValues.add(new String[]{"0028|0100", "16"}); // bits allocated
            seriesTagValues.add(new String[]{"0028|0101", "16"}); // bits stored
            seriesTagValues.add(new String[]{"0028|0102", "15"}); // high bit
            seriesTagValues.add(new String[]{"0028|0103", "1"}); // pixel representation
        }

        // Write slices to output directory
        for (int i = 0; i < newImg.getDepth(); i++) {
            writeSlices(seriesTagValues, newImg, args[0], i);
        }

        // Re-read the series
        // Read the original series. First obtain the series file names using the
        // image series reader.
        String dataDirectory = args[0];
        VectorString seriesIDs = ImageSeriesReader.getGDCMSeriesIDs(dataDirectory);
        if (seriesIDs.size() == 0) {
            System.out.println("ERROR: given directory \"" + dataDirectory + "\" does not contain a DICOM series.");
            System.exit(1);
        }

        VectorString seriesFileNames = ImageSeriesReader.getGDCMSeriesFileNames(dataDirectory, seriesIDs.get(0));

        ImageSeriesReader seriesReader = new ImageSeriesReader();
        seriesReader.setFileNames(seriesFileNames);

        // Configure the reader to load all of the DICOM tags (public+private):
        // By default tags are not loaded (saves time).
        // By default if tags are loaded, the private tags are not loaded.
        // We explicitly configure the reader to load tags, including the
        // private ones.
        seriesReader.loadPrivateTagsOn();
        Image image3D = seriesReader.execute();

        VectorDouble readSpacing = image3D.getSpacing();
        VectorDouble originalSpacing = newImg.getSpacing();
        System.out.printf("[%f, %f, %f] vs [%f, %f, %f]%n",
            readSpacing.get(0), readSpacing.get(1), readSpacing.get(2),
            originalSpacing.get(0), originalSpacing.get(1), originalSpacing.get(2));
    }
}
