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
/// A SimpleITK example demonstrating how to write a DICOM series.
/// </summary>

using System;
using System.Collections.Generic;
using System.IO;
using itk.simple;

namespace itk.simple.examples
{
    public class DicomSeriesFromArray
    {
        private static ImageFileWriter writer = new ImageFileWriter();

        /// <summary>
        /// Write slices to output directory
        /// </summary>
        static void WriteSlices(List<Tuple<string, string>> seriesTag, Image inImage, string outDir, int i)
        {
            Image imageSlice = inImage.Slice(0, (long)i, 2);

            // Tags shared by the series.
            foreach (var tagValue in seriesTag)
            {
                imageSlice.SetMetaData(tagValue.Item1, tagValue.Item2);
            }

            // Slice specific tags.
            // Instance Creation Date
            imageSlice.SetMetaData("0008|0012", DateTime.Now.ToString("yyyyMMdd"));
            // Instance Creation Time
            imageSlice.SetMetaData("0008|0013", DateTime.Now.ToString("HHmmss"));

            // Setting the type to CT so that the slice location is preserved and
            // the thickness is carried over.
            imageSlice.SetMetaData("0008|0060", "CT");

            // (0020, 0032) image position patient determines the 3D spacing between slices.
            // Image Position (Patient)
            double[] position = inImage.TransformIndexToPhysicalPoint(new long[] { 0, 0, i });
            imageSlice.SetMetaData("0020|0032", string.Join("\\", position));

            // Instance Number
            imageSlice.SetMetaData("0020|0013", i.ToString());

            // Write to the output directory and add the extension dcm, to force
            // writing in DICOM format.
            writer.SetFileName(Path.Combine(outDir, i.ToString() + ".dcm"));
            writer.Execute(imageSlice);
        }

        public static void Main(string[] args)
        {
            if (args.Length < 1)
            {
                Console.WriteLine("Usage: DicomSeriesFromArray <output_directory>");
                return;
            }
            // Set pixel type to sitkInt16 or sitkFloat64
            var pixelType = PixelIDValueEnum.sitkInt16;

            // Create image from random data array based on the pixel type
            Random rand = new Random();
            uint[] imageSize = { 512, 512, 256 };
            int totalPixels = (int)(imageSize[0] * imageSize[1] * imageSize[2]);
            Image newImg;

            if (pixelType == PixelIDValueEnum.sitkInt16)
            {
                short[] randomData = new short[totalPixels];
                for (int i = 0; i < totalPixels; i++)
                {
                    randomData[i] = (short)(rand.Next(-1000, 1001));
                }
                newImg = SimpleITK.ImportAsInt16(randomData, new VectorUInt32(imageSize));
            }
            else if (pixelType == PixelIDValueEnum.sitkFloat64)
            {
                double[] randomData = new double[totalPixels];
                for (int i = 0; i < totalPixels; i++)
                {
                    randomData[i] = rand.NextDouble() * 2000.0 - 1000.0;
                }
                newImg = SimpleITK.ImportAsFloat64(randomData, new VectorUInt32(imageSize));
            }
            else
            {
                throw new ArgumentException("Unsupported pixel type");
            }
            newImg.SetSpacing(new VectorDouble(new double[] { 2.5, 3.5, 4.5 }));

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
            writer.KeepOriginalImageUIDOn();

            string modificationTime = DateTime.Now.ToString("HHmmss");
            string modificationDate = DateTime.Now.ToString("yyyyMMdd");

            // Copy some of the tags and add the relevant tags indicating the change.
            // For the series instance UID (0020|000e), each of the components is a number,
            // cannot start with zero, and separated by a '.' We create a unique series ID
            // using the date and time.
            VectorDouble direction = newImg.GetDirection();
            List<Tuple<string, string>> seriesTagValues = new List<Tuple<string, string>>
            {
                new Tuple<string, string>("0008|0031", modificationTime), // Series Time
                new Tuple<string, string>("0008|0021", modificationDate), // Series Date
                new Tuple<string, string>("0008|0008", "DERIVED\\SECONDARY"), // Image Type
                new Tuple<string, string>("0020|000e", "1.2.826.0.1.3680043.2.1125." + modificationDate + ".1" + modificationTime), // Series Instance UID
                new Tuple<string, string>("0020|0037", string.Format("{0}\\{1}\\{2}\\{3}\\{4}\\{5}",
                    direction[0], direction[3], direction[6], direction[1], direction[4], direction[7])), // Image Orientation (Patient)
                new Tuple<string, string>("0008|103e", "Created-SimpleITK") // Series Description
            };

            if (pixelType == PixelIDValueEnum.sitkFloat64)
            {
                // If we want to write floating point values, we need to use the rescale
                // slope, "0028|1053", to select the number of digits we want to keep.
                double rescaleSlope = 0.001; // keep three digits after the decimal point
                seriesTagValues.AddRange(new List<Tuple<string, string>>
                {
                    new Tuple<string, string>("0028|1053", rescaleSlope.ToString()), // rescale slope
                    new Tuple<string, string>("0028|1052", "0"), // rescale intercept
                    new Tuple<string, string>("0028|0100", "16"), // bits allocated
                    new Tuple<string, string>("0028|0101", "16"), // bits stored
                    new Tuple<string, string>("0028|0102", "15"), // high bit
                    new Tuple<string, string>("0028|0103", "1") // pixel representation
                });
            }

            // Write slices to output directory
            for (int i = 0; i < (int)newImg.GetDepth(); i++)
            {
                WriteSlices(seriesTagValues, newImg, args[0], i);
            }

            // Re-read the series
            // Read the original series. First obtain the series file names using the
            // image series reader.
            string dataDirectory = args[0];
            VectorString seriesIDs = ImageSeriesReader.GetGDCMSeriesIDs(dataDirectory);
            if (seriesIDs.Count == 0)
            {
                Console.WriteLine("ERROR: given directory \"" + dataDirectory + "\" does not contain a DICOM series.");
                return;
            }

            VectorString seriesFileNames = ImageSeriesReader.GetGDCMSeriesFileNames(dataDirectory, seriesIDs[0]);

            ImageSeriesReader seriesReader = new ImageSeriesReader();
            seriesReader.SetFileNames(seriesFileNames);

            // Configure the reader to load all of the DICOM tags (public+private):
            // By default tags are not loaded (saves time).
            // By default if tags are loaded, the private tags are not loaded.
            // We explicitly configure the reader to load tags, including the
            // private ones.
            seriesReader.LoadPrivateTagsOn();
            Image image3D = seriesReader.Execute();

            VectorDouble readSpacing = image3D.GetSpacing();
            VectorDouble originalSpacing = newImg.GetSpacing();
            Console.WriteLine("[{0}, {1}, {2}] vs [{3}, {4}, {5}]",
                readSpacing[0], readSpacing[1], readSpacing[2],
                originalSpacing[0], originalSpacing[1], originalSpacing[2]);
        }
    }
}
