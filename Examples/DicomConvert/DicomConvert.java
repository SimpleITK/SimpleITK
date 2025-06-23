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
 * A SimpleITK example demonstrating how to convert and resize DICOM files
 * to common image types.
 */

import org.itk.simple.*;
import java.io.*;
import java.util.*;

public class DicomConvert {
    public static void main(String[] args) throws Exception {
        if (args.length < 2) {
            System.out.println("Usage: DicomConvert <root_of_data_directory> <output_file_extension> [--w width] [--od output_directory]");
            System.exit(1);
        }
        String rootDir = args[0];
        String outputExt = args[1];
        Integer width = null;
        String outDir = null;
        for (int i = 2; i < args.length; ++i) {
            if (args[i].equals("--w") && i + 1 < args.length) {
                width = Integer.parseInt(args[++i]);
            } else if (args[i].equals("--od") && i + 1 < args.length) {
                outDir = args[++i];
            }
        }
        List<String> inputFiles = new ArrayList<>();
        walkDir(new File(rootDir), inputFiles);
        List<String> fileNames = new ArrayList<>();
        if (outDir != null) {
            for (int i = 0; i < inputFiles.size(); ++i) {
                fileNames.add(new File(outDir, Integer.toString(i)).getAbsolutePath());
            }
        } else {
            for (String f : inputFiles) {
                fileNames.add(f);
            }
        }
        List<String> outputFiles = new ArrayList<>();
        for (String f : fileNames) {
            outputFiles.add(f + "." + outputExt);
        }
        List<Boolean> res = new ArrayList<>();
        for (int i = 0; i < inputFiles.size(); ++i) {
            res.add(convertImage(inputFiles.get(i), outputFiles.get(i), width));
        }
        List<String> filteredInput = new ArrayList<>();
        List<String> filteredOutput = new ArrayList<>();
        for (int i = 0; i < res.size(); ++i) {
            if (res.get(i)) {
                filteredInput.add(inputFiles.get(i));
                filteredOutput.add(outputFiles.get(i));
            }
        }
        String csvDir = (outDir != null) ? outDir : System.getProperty("user.dir");
        try (PrintWriter writer = new PrintWriter(new File(csvDir, "file_names.csv"), "UTF-8")) {
            writer.println("input file name,output file name");
            for (int i = 0; i < filteredInput.size(); ++i) {
                writer.println(filteredInput.get(i) + "," + filteredOutput.get(i));
            }
        }
    }

    static void walkDir(File dir, List<String> files) {
        for (File f : dir.listFiles()) {
            if (f.isDirectory()) {
                walkDir(f, files);
            } else {
                files.add(f.getAbsolutePath());
            }
        }
    }

    static boolean convertImage(String inputFile, String outputFile, Integer newWidth) {
        try {
            ImageFileReader reader = new ImageFileReader();
            // Only read DICOM images
            reader.setImageIO("GDCMImageIO");
            reader.setFileName(inputFile);
            reader.readImageInformation();
            VectorUInt64 iSize = reader.getSize();
            VectorUInt32 imageSize = new VectorUInt32();
            imageSize.add(iSize.get(0).longValue());
            imageSize.add(iSize.get(1).longValue());
            // If 3D image with single slice, treat as 2D
            if (iSize.size() == 3) {
              if (iSize.get(2).longValue() == 1) {
                   imageSize.add(0L);
                }
                else {
                   imageSize.add(iSize.get(2).longValue());
                }
            }
            reader.setExtractSize(imageSize);
            Image image = reader.execute();
            // Resample if new width is specified
            if (newWidth != null) {
                VectorUInt32 originalSize = image.getSize();
                VectorDouble originalSpacing = image.getSpacing();
                double newSpacing = ((originalSize.get(0) - 1) * originalSpacing.get(0)) / (newWidth - 1);
                long newHeight = (long)(((originalSize.get(1) - 1) * originalSpacing.get(1)) / newSpacing);
                image = SimpleITK.resample(image, new VectorUInt32(new long[]{newWidth, newHeight}), new Transform(), InterpolatorEnum.sitkLinear,
                    image.getOrigin(), new VectorDouble(new double[]{newSpacing, newSpacing}), image.getDirection(), 0, image.getPixelID());
            }
            // If a single channel image, rescale to [0,255]. Also modify the
            // intensity values based on the photometric interpretation. If
            // MONOCHROME2 (minimum should be displayed as black) we don't need to
            // do anything, if image has MONOCHROME1 (minimum should be displayed as
            // white) we flip the intensities. This is a constraint imposed by ITK
            // which always assumes MONOCHROME2.
            if (image.getNumberOfComponentsPerPixel() == 1) {
                image = SimpleITK.rescaleIntensity(image, 0, 255);
                String photoInterp = reader.getMetaData("0028|0004").trim();
                if (photoInterp.equals("MONOCHROME1")) {
                    image = SimpleITK.invertIntensity(image, 255);
                }
                image = SimpleITK.cast(image, PixelIDValueEnum.sitkUInt8);
            }
            SimpleITK.writeImage(image, outputFile);
            return true;
        } catch (Exception e) {
            return false;
        }
    }
}
