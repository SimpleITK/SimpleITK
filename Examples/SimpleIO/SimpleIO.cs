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
using System.Diagnostics;
using itk.simple;
using sitk = itk.simple.SimpleITK;

// These examples are used in the I/O documentation page. The IO.rst file
// pulls the code examples based their line numbers in this file. So any
// change in the line numbers of the code below will break the I/O page.

namespace itk.simple.examples {
    class SimpleIO {

static void example1(string inputImageFileName, string outputImageFileName) {
  ImageFileReader reader = new ImageFileReader();
  reader.SetImageIO("PNGImageIO");
  reader.SetFileName(inputImageFileName);
  Image image = reader.Execute();

  ImageFileWriter writer = new ImageFileWriter();
  writer.SetFileName(outputImageFileName);
  writer.Execute(image);
}

static void example2(string inputImageFileName, string outputImageFileName) {
  Image image = sitk.ReadImage(inputImageFileName, PixelIDValueEnum.sitkUnknown, "PNGImageIO");
  sitk.WriteImage(image, outputImageFileName);
}

static void example3() {
  Euler2DTransform basic_transform = new Euler2DTransform();
  VectorDouble trans = new VectorDouble( new double[] {2.0, 3.0} );
  basic_transform.SetTranslation(trans);

  sitk.WriteTransform(basic_transform, "euler2D.tfm");

  Transform read_result = sitk.ReadTransform("euler2D.tfm");

  Debug.Assert( basic_transform.GetName() != read_result.GetName() );
}

static void Main(string[] args) {
  try {
    if (args.Length < 2) {
      Console.WriteLine("Usage: SimpleIO <input> <output>");
      return;
    }

    example1(args[0], args[1]);
    example2(args[0], args[1]);
    example3();


  } catch (Exception ex) {
    Console.WriteLine(ex);
  }
}

    } // class SimpleIO
} // namespace itk.simple.examples
