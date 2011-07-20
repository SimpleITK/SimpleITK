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
