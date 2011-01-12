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
    reader.setFilename(argv[0]);
    SmartPointerImage img = reader.execute();

    SmartPointerPixelContainer pixels = img.getPixelContainer();


   int imageSize = 1024 * 1024;

   int value = 19;

   int8Array array = new int8Array(imageSize);
   for (int i=0; i<imageSize; i++) {
      array.setitem(i,value);
   }

   pixels.setBuffer( array.cast() );

   array.frompointer( pixels.getBuffer() );

  }

}
