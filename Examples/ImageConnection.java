/*=========================================================================
*
*  Copyright Insight Software Consortium
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

class ImageConnection {

  public static void main(String argv[]) {

    // do some simple operations
    System.out.println("SimpleITK says 'Hello World' from Java");

    if ( argv.length < 2 ) {
      System.out.println("Usage: java ImageConnection <input> <output>");
      return;
    }

    ImageFileReader reader = new ImageFileReader();

    reader.setFileName(argv[0]);

    Image img = reader.execute();

    PixelContainer pixelsContainer = img.getPixelContainer();

   java.math.BigInteger t = pixelsContainer.getNumberOfPixels();

    int numberOfPixels = t.intValue();

    int [] buffer = new int[ numberOfPixels ];


    buffer[0] = 13;
    buffer[1] =  2;
    buffer[2] = 19;

    pixelsContainer.setBufferAsUnsignedInt8( buffer, numberOfPixels );
  }

}
