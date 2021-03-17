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

// These examples are used in the I/O documentation page. The IO.rst file
// pulls the code examples based their line numbers in this file. So any
// change in the line numbers of the code below will break the I/O page.


import org.itk.simple.*;

class SimpleIO {

static void example1(String inputImageFileName, String outputImageFileName) {
  ImageFileReader reader = new ImageFileReader();
  reader.setImageIO("PNGImageIO");
  reader.setFileName(inputImageFileName);
  Image image = reader.execute();

  ImageFileWriter writer = new ImageFileWriter();
  writer.setFileName(outputImageFileName);
  writer.execute(image);
}

static void example2(String inputImageFileName, String outputImageFileName) {
  Image image = SimpleITK.readImage(inputImageFileName, PixelIDValueEnum.sitkUnknown, "PNGImageIO");
  SimpleITK.writeImage(image, outputImageFileName);
}

static void example3() {
  Euler2DTransform basic_transform = new Euler2DTransform();
  double[] t = {2.0, 3.0};
  VectorDouble trans = new VectorDouble(t);
  basic_transform.setTranslation(trans);

  SimpleITK.writeTransform(basic_transform, "euler2D.tfm");
  Transform read_result = SimpleITK.readTransform("euler2D.tfm");

  assert basic_transform.getClass() != read_result.getClass();
}

public static void main(String argv[]) {

 if ( argv.length < 2 ) {
   System.out.println("Usage: java SimpleIO <input> <output>");
   return;
 }

 example1(argv[0], argv[1]);
 example2(argv[0], argv[1]);
 example3();

}

}
