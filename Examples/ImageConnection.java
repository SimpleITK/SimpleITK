/**
 * Simple test of SimpleITK's java wrapping
 */

import org.itk.simple.*;

class ImageConnection {

  public static void main(String argv[]) {

    if ( argv.length < 2 ) {
      System.out.println("Usage: java ImageConnection <input> <output>");
      return;
    }

    ImageFileReader reader = new ImageFileReader();
    reader.setFileName(argv[0]);
    Image img = reader.execute();

    PixelContainer pixelsContainer = img.getPixelContainer();

    int8Array pixelsArray = int8Array.frompointer( pixelsContainer.getBufferAsInt8() );

    java.math.BigInteger numberOfPixels = pixelsContainer.getNumberOfPixels();

    int8Array anotherPixelsArray = new int8Array( numberOfPixels.longValue(), true );

  }

}
