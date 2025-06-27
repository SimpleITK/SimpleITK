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
/// A SimpleITK example demonstrating how to print a DICOM image's tags.
/// </summary>

using System;
using System.Collections.Generic;
using itk.simple;

namespace itk.simple.examples
{
    public class DicomImagePrintTags
    {
        /// <summary>
        /// A SimpleITK script that prints a DICOM image's tags.
        /// </summary>
        public static void Main(string[] args)
        {
            if (args.Length < 1)
            {
                Console.WriteLine("Usage: DicomImagePrintTags <input_file>");
                return;
            }

            var reader = new ImageFileReader();

            reader.SetFileName(args[0]);
            reader.LoadPrivateTagsOn();

            reader.ReadImageInformation();

            foreach (string k in reader.GetMetaDataKeys())
            {
                Console.WriteLine(string.Format("({0}) = = \"{1}\"", k, reader.GetMetaData(k)));
            }

            var size = reader.GetSize();
            Console.Write("Image Size: [" + size[0]);
            for (int i = 1; i < size.Count; i++)
            {
                Console.Write(", " + size[i]);
            }
            Console.WriteLine("]");

            Console.WriteLine("Image PixelType: " + SimpleITK.GetPixelIDValueAsString(reader.GetPixelID()));
        }
    }
}
