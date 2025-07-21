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
/// A SimpleITK example demonstrating how to read a DICOM series,
/// modify it, and then write a new DICOM series.
/// </summary>

using System;
using System.Collections.Generic;
using System.IO;
using itk.simple;

namespace itk.simple.examples
{
    public class DicomSeriesReadModifySeriesWrite
    {
        public static void Main(string[] args)
        {
            if (args.Length < 2)
            {
                Console.WriteLine("Usage: DicomSeriesReadModifySeriesWrite <input_directory_with_DICOM_series> <output_directory>");
                return;
            }

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
            seriesReader.MetaDataDictionaryArrayUpdateOn();
            seriesReader.LoadPrivateTagsOn();
            Image image3D = seriesReader.Execute();

            // Modify the image (blurring)
            Image filteredImage = SimpleITK.DiscreteGaussian(image3D);

            // Write the 3D image as a series
            // IMPORTANT: There are many DICOM tags that need to be updated when you modify
            //            an original image. This is a delicate operation and requires
            //            knowledge of the DICOM standard. This example only modifies some.
            //            For a more complete list of tags that need to be modified see:
            //                http://gdcm.sourceforge.net/wiki/index.php/Writing_DICOM

            ImageFileWriter writer = new ImageFileWriter();
            // Use the study/series/frame of reference information given in the meta-data
            // dictionary and not the automatically generated information from the file IO
            writer.KeepOriginalImageUIDOn();

            // Copy relevant tags from the original meta-data dictionary (private tags are
            // also accessible).
            string[] tagsToCopy = {
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

            string modificationTime = DateTime.Now.ToString("HHmmss");
            string modificationDate = DateTime.Now.ToString("yyyyMMdd");

            // Copy some of the tags and add the relevant tags indicating the change.
            // For the series instance UID (0020|000e), each of the components is a number,
            // cannot start with zero, and separated by a '.' We create a unique series ID
            // using the date and time.
            // NOTE: Always represent DICOM tags using lower case hexadecimals.
            VectorDouble direction = filteredImage.GetDirection();
            List<KeyValuePair<string, string>> seriesTagValues = new List<KeyValuePair<string, string>>();

            // Copy existing tags
            foreach (string tag in tagsToCopy)
            {
                if (seriesReader.HasMetaDataKey(0, tag))
                {
                    seriesTagValues.Add(new KeyValuePair<string, string>(tag, seriesReader.GetMetaData(0, tag)));
                }
            }

            // Add modification tags
            seriesTagValues.AddRange(new List<KeyValuePair<string, string>>
            {
                new KeyValuePair<string, string>("0008|0031", modificationTime), // Series Time
                new KeyValuePair<string, string>("0008|0021", modificationDate), // Series Date
                new KeyValuePair<string, string>("0008|0008", "DERIVED\\SECONDARY"), // Image Type
                new KeyValuePair<string, string>("0020|000e", "1.2.826.0.1.3680043.2.1125." + modificationDate + ".1" + modificationTime), // Series Instance UID
            });

            // Image Orientation (Patient)
            string orientation = string.Format("{0}\\{1}\\{2}\\{3}\\{4}\\{5}",
                direction[0], direction[3], direction[6], direction[1], direction[4], direction[7]);
            seriesTagValues.Add(new KeyValuePair<string, string>("0020|0037", orientation));

            // Series Description
            string seriesDescription = "";
            if (seriesReader.HasMetaDataKey(0, "0008|103e"))
            {
                seriesDescription = seriesReader.GetMetaData(0, "0008|103e");
            }
            seriesDescription += " Processed-SimpleITK";
            seriesTagValues.Add(new KeyValuePair<string, string>("0008|103e", seriesDescription));

            ExtractImageFilter extractFilter = new ExtractImageFilter();
            VectorUInt32 size = filteredImage.GetSize();
            size[2] = 1; // Extract single slice
            extractFilter.SetSize(size);
            for (int i = 0; i < (int)filteredImage.GetDepth(); i++)
            {
                extractFilter.SetIndex(new VectorInt32(new int[] { 0, 0, i }));
                Image imageSlice = extractFilter.Execute(filteredImage);

                // Tags shared by the series.
                foreach (var tagValue in seriesTagValues)
                {
                    imageSlice.SetMetaData(tagValue.Key, tagValue.Value);
                }

                // Slice specific tags.
                // Instance Creation Date
                imageSlice.SetMetaData("0008|0012", DateTime.Now.ToString("yyyyMMdd"));
                // Instance Creation Time
                imageSlice.SetMetaData("0008|0013", DateTime.Now.ToString("HHmmss"));

                // Image Position (Patient)
                VectorDouble position = filteredImage.TransformIndexToPhysicalPoint(new VectorInt64(new long[] { 0, 0, i }));
                imageSlice.SetMetaData("0020|0032", position[0].ToString() + "\\" + position[1].ToString() + "\\" + position[2].ToString());

                // Instance Number
                imageSlice.SetMetaData("0020|0013", i.ToString());

                // Write to the output directory and add the extension dcm, to force writing
                // in DICOM format.
                writer.SetFileName(Path.Combine(args[1], i.ToString() + ".dcm"));
                writer.Execute(imageSlice);
            }
        }
    }
}
