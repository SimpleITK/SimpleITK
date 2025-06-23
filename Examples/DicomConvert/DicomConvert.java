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
            Image image = reader.execute();
            // If 3D image with single slice, treat as 2D
            VectorUInt32 imageSize = image.getSize();
            if (imageSize.size() == 3 && imageSize.get(2).longValue() == 1) {
                ExtractImageFilter extractFilter = new ExtractImageFilter();
                extractFilter.setIndex(new VectorInt32(new int[]{0, 0, 0}));
                imageSize.set(2, 0L);
                extractFilter.setSize(imageSize);
                image = extractFilter.execute(image);
            }
            // Resample if new width is specified
            if (newWidth != null) {
                VectorUInt32 originalSize = image.getSize();
                VectorDouble originalSpacing = image.getSpacing();
                double newSpacing = ((originalSize.get(0) - 1) * originalSpacing.get(0)) / (newWidth - 1);
                long newHeight = (long)(((originalSize.get(1) - 1) * originalSpacing.get(1)) / newSpacing);
                image = SimpleITK.resample(image, new VectorUInt32(new long[]{newWidth, newHeight}), new Transform(), InterpolatorEnum.sitkLinear,
                    image.getOrigin(), new VectorDouble(new double[]{newSpacing, newSpacing}), image.getDirection(), 0, image.getPixelID());
            }
            // If a single channel image, rescale to [0,255] and cast to UInt8.
            if (image.getNumberOfComponentsPerPixel() == 1) {
                image = SimpleITK.rescaleIntensity(image, 0, 255);
                image = SimpleITK.cast(image, PixelIDValueEnum.sitkUInt8);
            }
            SimpleITK.writeImage(image, outputFile);
            return true;
        } catch (Exception e) {
            return false;
        }
    }
}
