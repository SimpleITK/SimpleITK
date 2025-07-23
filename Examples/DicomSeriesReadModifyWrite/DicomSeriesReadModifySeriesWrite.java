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
 * A SimpleITK example demonstrating how to read a DICOM series,
 * modify it, and then write a new DICOM series.
 */

import org.itk.simple.*;
import java.io.*;
import java.util.*;
import java.text.SimpleDateFormat;

public class DicomSeriesReadModifySeriesWrite {

    public static void main(String[] args) throws Exception {
        if (args.length < 2) {
            System.out.println("Usage: DicomSeriesReadModifySeriesWrite <input_directory_with_DICOM_series> <output_directory>");
            System.exit(1);
        }

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
        seriesReader.metaDataDictionaryArrayUpdateOn();
        seriesReader.loadPrivateTagsOn();
        Image image3D = seriesReader.execute();

        // Modify the image (blurring)
        Image filteredImage = SimpleITK.discreteGaussian(image3D);

        // Write the 3D image as a series
        // IMPORTANT: There are many DICOM tags that need to be updated when you modify
        //            an original image. This is a delicate operation and requires
        //            knowledge of the DICOM standard. This example only modifies some.
        //            For a more complete list of tags that need to be modified see:
        //                http://gdcm.sourceforge.net/wiki/index.php/Writing_DICOM

        ImageFileWriter writer = new ImageFileWriter();
        // Use the study/series/frame of reference information given in the meta-data
        // dictionary and not the automatically generated information from the file IO
        writer.keepOriginalImageUIDOn();

        // Copy relevant tags from the original meta-data dictionary (private tags are
        // also accessible).
        String[] tagsToCopy = {
            "0010|0010",  // Patient Name
            "0010|0020",  // Patient ID
            "0010|0030",  // Patient Birth Date
            "0020|000d",  // Study Instance UID, for machine consumption
            "0020|0010",  // Study ID, for human consumption
            "0008|0020",  // Study Date
            "0008|0030",  // Study Time
            "0008|0050",  // Accession Number
            "0008|0060"   // Modality
        };

        SimpleDateFormat timeFormat = new SimpleDateFormat("HHmmss");
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyyMMdd");
        Date now = new Date();
        String modificationTime = timeFormat.format(now);
        String modificationDate = dateFormat.format(now);

        // Copy some of the tags and add the relevant tags indicating the change.
        // For the series instance UID (0020|000e), each of the components is a number,
        // cannot start with zero, and separated by a '.' We create a unique series ID
        // using the date and time.
        // NOTE: Always represent DICOM tags using lower case hexadecimals.
        VectorDouble direction = filteredImage.getDirection();
        List<String[]> seriesTagValues = new ArrayList<>();

        // Copy existing tags
        for (String tag : tagsToCopy) {
            if (seriesReader.hasMetaDataKey(0, tag)) {
                seriesTagValues.add(new String[]{tag, seriesReader.getMetaData(0, tag)});
            }
        }

        // Add modification tags
        seriesTagValues.add(new String[]{"0008|0031", modificationTime}); // Series Time
        seriesTagValues.add(new String[]{"0008|0021", modificationDate}); // Series Date
        seriesTagValues.add(new String[]{"0008|0008", "DERIVED\\SECONDARY"}); // Image Type
        seriesTagValues.add(new String[]{"0020|000e", "1.2.826.0.1.3680043.2.1125." + modificationDate + ".1" + modificationTime}); // Series Instance UID

        // Image Orientation (Patient)
        String orientation = String.format("%f\\%f\\%f\\%f\\%f\\%f",
            direction.get(0), direction.get(3), direction.get(6),
            direction.get(1), direction.get(4), direction.get(7));
        seriesTagValues.add(new String[]{"0020|0037", orientation});

        // Series Description
        String seriesDescription = "";
        if (seriesReader.hasMetaDataKey(0, "0008|103e")) {
            seriesDescription = seriesReader.getMetaData(0, "0008|103e");
        }
        seriesDescription += " Processed-SimpleITK";
        seriesTagValues.add(new String[]{"0008|103e", seriesDescription});

        ExtractImageFilter extractFilter = new ExtractImageFilter();
        VectorUInt32 size = filteredImage.getSize();
        size.set(2, 1L);
        extractFilter.setSize(size);
        for (int i = 0; i < filteredImage.getDepth(); i++) {
            extractFilter.setIndex(new VectorInt32(new int[]{0, 0, i}));
            Image imageSlice = extractFilter.execute(filteredImage);

            // Tags shared by the series.
            for (String[] tagValue : seriesTagValues) {
                imageSlice.setMetaData(tagValue[0], tagValue[1]);
            }

            // Slice specific tags.
            SimpleDateFormat instanceDateFormat = new SimpleDateFormat("yyyyMMdd");
            SimpleDateFormat instanceTimeFormat = new SimpleDateFormat("HHmmss");
            Date instanceNow = new Date();

            // Instance Creation Date
            imageSlice.setMetaData("0008|0012", instanceDateFormat.format(instanceNow));
            // Instance Creation Time
            imageSlice.setMetaData("0008|0013", instanceTimeFormat.format(instanceNow));

            // Image Position (Patient)
            VectorDouble position = filteredImage.transformIndexToPhysicalPoint(new VectorInt64(new long[]{0, 0, i}));
            StringJoiner posJoiner = new StringJoiner("\\");
            for (int j = 0; j < position.size(); j++) {
                posJoiner.add(String.valueOf(position.get(j)));
            }
            imageSlice.setMetaData("0020|0032", posJoiner.toString());

            // Instance Number
            imageSlice.setMetaData("0020|0013", String.valueOf(i));

            // Write to the output directory and add the extension dcm, to force writing
            // in DICOM format.
            writer.setFileName(new File(args[1], i + ".dcm").getAbsolutePath());
            writer.execute(imageSlice);
        }
    }
}
