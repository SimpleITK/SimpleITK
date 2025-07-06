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

// A SimpleITK example demonstrating how to convert and resize DICOM files to common image types.

using System;
using System.Collections.Generic;
using System.IO;
using itk.simple;

namespace itk.simple.examples
{
    public class DicomConvert
    {
        public static void Main(string[] args)
        {
            if (args.Length < 2)
            {
                Console.WriteLine("Usage: DicomConvert <root_of_data_directory> <output_file_extension> [--w width] [--od output_directory]");
                return;
            }
            string rootDir = args[0];
            string outputExt = args[1];
            int? width = null;
            string outDir = null;
            for (int i = 2; i < args.Length; ++i)
            {
                if (args[i] == "--w" && i + 1 < args.Length)
                {
                    width = int.Parse(args[++i]);
                }
                else if (args[i] == "--od" && i + 1 < args.Length)
                {
                    outDir = args[++i];
                }
            }
            var inputFiles = new List<string>();
            WalkDir(new DirectoryInfo(rootDir), inputFiles);
            var fileNames = new List<string>();
            if (outDir != null)
            {
                for (int i = 0; i < inputFiles.Count; ++i)
                {
                    fileNames.Add(Path.Combine(outDir, i.ToString()));
                }
            }
            else
            {
                fileNames.AddRange(inputFiles);
            }
            var outputFiles = new List<string>();
            foreach (var f in fileNames)
            {
                outputFiles.Add(f + "." + outputExt);
            }
            var res = new List<bool>();
            for (int i = 0; i < inputFiles.Count; ++i)
            {
                res.Add(ConvertImage(inputFiles[i], outputFiles[i], width));
            }
            var filteredInput = new List<string>();
            var filteredOutput = new List<string>();
            for (int i = 0; i < res.Count; ++i)
            {
                if (res[i])
                {
                    filteredInput.Add(inputFiles[i]);
                    filteredOutput.Add(outputFiles[i]);
                }
            }
            string csvDir = outDir ?? Directory.GetCurrentDirectory();
            using (var writer = new StreamWriter(Path.Combine(csvDir, "file_names.csv")))
            {
                writer.WriteLine("input file name,output file name");
                for (int i = 0; i < filteredInput.Count; ++i)
                {
                    writer.WriteLine(filteredInput[i] + ","+ filteredOutput[i]);
                }
            }
        }

        static void WalkDir(DirectoryInfo dir, List<string> files)
        {
            foreach (var f in dir.GetFileSystemInfos())
            {
                if ((f.Attributes & FileAttributes.Directory) == FileAttributes.Directory)
                {
                    WalkDir((DirectoryInfo)f, files);
                }
                else
                {
                    files.Add(f.FullName);
                }
            }
        }

        static bool ConvertImage(string inputFile, string outputFile, int? newWidth)
        {
            try
            {
                var reader = new ImageFileReader();
                // Only read DICOM images
                reader.SetImageIO("GDCMImageIO");
                reader.SetFileName(inputFile);
                var image = reader.Execute();
                var imageSize = image.GetSize();
                // If 3D image with single slice, treat as 2D
                if (imageSize.Count == 3 && imageSize[2] == 1) {
                  ExtractImageFilter extractFilter = new ExtractImageFilter();
                  extractFilter.SetIndex(new VectorInt32( new int[] { 0, 0, 0 }));
                  imageSize[2] = 0;
                  extractFilter.SetSize(imageSize);
                  image = extractFilter.Execute(image);
                }
                // Resample if new width is specified
                if (newWidth.HasValue)
                {
                    var originalSize = image.GetSize();
                    var originalSpacing = image.GetSpacing();
                    double newSpacing = ((originalSize[0] - 1) * originalSpacing[0]) / (newWidth.Value - 1);
                    long newHeight = (long)(((originalSize[1] - 1) * originalSpacing[1]) / newSpacing);
                    image = SimpleITK.Resample(image, new VectorUInt32(new long[] { newWidth.Value, newHeight }), new Transform(), InterpolatorEnum.sitkLinear,
                        image.GetOrigin(), new VectorDouble(new double[] { newSpacing, newSpacing }), image.GetDirection(), 0, image.GetPixelID());
                }
                // If a single channel image, rescale to [0,255] and cast to UInt8.
                if (image.GetNumberOfComponentsPerPixel() == 1)
                {
                    image = SimpleITK.RescaleIntensity(image, 0, 255);
                    image = SimpleITK.Cast(image, PixelIDValueEnum.sitkUInt8);
                }
                SimpleITK.WriteImage(image, outputFile);
                return true;
            }
            catch
            {
                return false;
            }
        }
    }
}
