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
    class Transformix
    {
        static void Main(string[] args)
        {
            if (args.Length < 3)
            {
                Console.WriteLine("Usage: tfx <inputImage> <parameterFile> <outputImage>");
                return;
            }

            // Instantiate transformix
            TransformixImageFilter transformixImageFilter = new TransformixImageFilter();
            transformixImageFilter.LogToConsoleOn();

            // Read input
            transformixImageFilter.SetMovingImage(SimpleITK.ReadImage(args[0]));
            transformixImageFilter.SetTransformParameterMap(SimpleITK.ReadParameterFile(args[1]));

            // Run warp
            transformixImageFilter.Execute();

            // Write result image
            SimpleITK.WriteImage(transformixImageFilter.GetResultImage(), args[2]);
        }
    }
}
