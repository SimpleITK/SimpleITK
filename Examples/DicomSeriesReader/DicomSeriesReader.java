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

import org.itk.simple.*;

public class DicomSeriesReader {
  public static void main(String[] args) {

    if (args.length < 2) {
      System.out.println("Usage: DicomSeriesReader <input_directory> <output_file>");
      System.exit(1);
    }

    System.out.println("Reading Dicom directory: " + args[0]);

    ImageSeriesReader imageSeriesReader = new ImageSeriesReader();
    final VectorString dicomNames = ImageSeriesReader.getGDCMSeriesFileNames(args[0]);
    imageSeriesReader.setFileNames(dicomNames);

    Image image = imageSeriesReader.execute();

    VectorUInt32 size = image.getSize();
    System.out.println("Image size: " + size.get(0) + " " + size.get(1) + " " + size.get(2));

    System.out.println("Writing " + args[1]);

    SimpleITK.writeImage(image, args[1]);
  }
}
