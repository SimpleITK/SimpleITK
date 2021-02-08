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
 * Simple test of SimpleITK's java wrapping
 */


import org.itk.simple.*;

class ImageIOSelection {

  public static void main(String argv[]) {

    if ( argv.length < 1 ) {
      System.out.println("Usage: java ImageIOSelection image_file_name");
      return;
    }

    org.itk.simple.ImageFileReader reader = new org.itk.simple.ImageFileReader();

    // Find out which image IOs are supported
    VectorString image_ios;
    image_ios = reader.getRegisteredImageIOs();
    System.out.print("The supported image IOs are: ");
    System.out.println(image_ios);
    System.out.println("--------------------");

    // Another option is to just print the reader and see which
    // IOs are supported
    System.out.println(reader.toString());
    System.out.println("--------------------");

    reader.setImageIO("PNGImageIO");
    reader.setFileName(argv[0]);

    try {
      Image img = reader.execute();
      System.out.println("Read image: " + argv[0]);
    } catch(Exception e) {
      System.out.println("Read failed: " + e);
    }

  }

}
