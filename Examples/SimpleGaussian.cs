using System;

namespace itk.simple.examples {
    class SimpleGaussianExample {
        static void Main(string[] args) {
          try {
              if (args.Length < 3) {
                  Console.WriteLine("Usage: SimpleGaussian <input> <sigma> <output>");
                  return;
              }
              ImageFileReader reader = new ImageFileReader();
              reader.setFilename(args[0]);
              SmartPointerImage image = reader.execute();

              Console.WriteLine(image.toString());

              Gaussian gaussian = new Gaussian();

              gaussian.setSigma(Double.Parse(args[1]));
              image = gaussian.execute(image);

              Console.WriteLine(image.toString());

              ImageFileWriter writer = new ImageFileWriter();
              writer.setFilename(args[2]);
              writer.execute(image);
          } catch (Exception ex) {
              Console.WriteLine(ex);
          }
        }
    }
}
