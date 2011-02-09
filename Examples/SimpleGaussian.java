/**
 * Simple test of SimpleITK's java wrapping
 */

import org.itk.simple.*;

class SimpleGaussian {

  public static void main(String argv[]) {

    // do some simple operations
    System.out.println("SimpleITK says 'Hello World' from Java");

    if ( argv.length < 3 ) {
      System.out.println("Usage: java SimpleGaussian <input> <sigma> <output>");
      return;
    }

    ImageFileReader reader = new ImageFileReader();
    reader.setFileName(argv[0]);
    SmartPointerImage img = reader.execute();

    RecursiveGaussianImageFilter filt = new RecursiveGaussianImageFilter();
    SmartPointerImage blurredImg = filt.execute(img);

    ImageFileWriter writer = new ImageFileWriter();
    writer.setFileName(argv[1]);
    writer.execute(blurredImg);

  }

}
