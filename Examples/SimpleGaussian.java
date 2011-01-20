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
    reader.SetFileName(argv[0]);
    SmartPointerImage img = reader.Execute();
    
    RecursiveGaussianImageFilter filt = new RecursiveGaussianImageFilter();
    SmartPointerImage blurredImg = filt.Execute(img);
    
    ImageFileWriter writer = new ImageFileWriter();
    writer.SetFileName(argv[1]);
    writer.Execute(blurredImg);
    
  }
  
}
