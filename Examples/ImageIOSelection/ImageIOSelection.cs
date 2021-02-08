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
using System;
using itk.simple;

namespace itk.simple.examples {
    class ImageIOSelection {
        static void Main(string[] args) {
            try {
                if (args.Length < 1) {
                    Console.WriteLine("Usage: ImageIOSelection image_input_file");
                    return;
                }

                // Find out which image IOs are supported
                ImageFileReader reader = new ImageFileReader();
                itk.simple.VectorString image_ios = reader.GetRegisteredImageIOs();
                Console.Write("The supported image IOs are: ");
                for (int i=0; i<image_ios.Count; i++) {
                    Console.Write(image_ios[i] + " ");
                }
                Console.WriteLine("\n--------------------");

                // Another option is to just print the reader and see which
                // IOs are supported
                Console.WriteLine(reader.ToString());
                Console.WriteLine("--------------------");

                // Force the use of a specific IO. If the IO doesn't support
                // reading the image type it will throw an exception.
                reader.SetImageIO("PNGImageIO");
                reader.SetFileName(args[0]);
                Image image = reader.Execute();
                Console.WriteLine("Read image: " + args[0]);

            } catch (Exception ex) {
                Console.WriteLine("Read failed: " + ex);
            }
        }
    }
}
