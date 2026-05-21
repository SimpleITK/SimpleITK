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

namespace itk.simple.examples
{
    class Elastix
    {
        static void Main(string[] args)
        {
            if (args.Length < 5)
            {
                Console.WriteLine("Usage: elx <fixedImage> <movingImage> <parameterFile> <outputImage> <outputParameterFile>");
                return;
            }

            // Instantiate SimpleElastix
            ElastixImageFilter elastixImageFilter = new ElastixImageFilter();

            // Read input
            elastixImageFilter.SetFixedImage(SimpleITK.ReadImage(args[0]));
            elastixImageFilter.SetMovingImage(SimpleITK.ReadImage(args[1]));
            elastixImageFilter.SetParameterMap(SimpleITK.ReadParameterFile(args[2]));
            elastixImageFilter.LogToConsoleOn();

            // Run registration
            elastixImageFilter.Execute();

            // Write result image
            SimpleITK.WriteImage(elastixImageFilter.GetResultImage(), args[3]);

            // Write parameter file. This example only supports one parameter map and one transform parameter map.
            SimpleITK.WriteParameterFile(elastixImageFilter.GetTransformParameterMaps()[0], args[4]);
        }
    }
}
