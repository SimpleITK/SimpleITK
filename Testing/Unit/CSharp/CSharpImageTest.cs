using System;
using itk.simple;
using sitk = itk.simple.SimpleITK;
using PixelId = itk.simple.PixelIDValueEnum;

namespace itk.simple {
    /// <summary>Test itk.simple.Image.</summary>
    public class CSharpImageTest {
        public const int ExitSuccess = 0;
        public const int ExitFailure = 1;

        public static int CheckHash(Image img, string expectedHash, ref int success)
        {
        HashImageFilter hasher = new HashImageFilter();
        string actualHash = hasher.Execute(img);
        if (actualHash != expectedHash)
        {
         success = ExitFailure;
         Console.WriteLine("Expected hash: \"{0}\" actual hash: \"{1}\".", expectedHash, actualHash );         
        }       
        return 0;
        }       

        /// <summary>Main entry point.</summary>
        public static int Main (string[] args) {
            int success = ExitSuccess;
            try {
                Image image = new Image(100, 100, PixelId.sitkInt8);
                Image image2 = new Image(100, 100, PixelId.sitkInt8);

                
                image += 10;
                image -= 1;
                CheckHash(image, "1cda91cc1bf474a25d6365f7fa7ef1fc75b3c7c9", ref success);
                image *= 2;
                image /= 3;
                CheckHash(image, "856f68940ff670209aa9d60f38fc4cca1880f647", ref success);
                

                // image with just one 7 reset zero
                image *= 0;
                VectorUInt32 idx = new VectorUInt32();
                idx.Add(0);
                idx.Add(0);
                image.SetPixelAsInt8( idx, 7 );
                
                // Unary operators
                CheckHash(-image, "fe7e0c8ac8252189cf5766a352397bc62dd42e4d", ref success);
                CheckHash(+image, "6cccaa2d5c958e79ebd5ca4a0b00bee747797c8d", ref success);
                CheckHash(!image, "f4695dbf5bc9ea2796b2e4f360ea4b5ecbf70c37", ref success);
                CheckHash(~image, "746470f03126f653cc23265e0b1c1fe16a952745", ref success);
                CheckHash(image, "6cccaa2d5c958e79ebd5ca4a0b00bee747797c8d", ref success);     


                // Comparison operators
                CheckHash( image < 7, "f4695dbf5bc9ea2796b2e4f360ea4b5ecbf70c37", ref success);  
                CheckHash( image > 7, "f907b7bf318b79fd6b9da589646f8b1dac77d0c8", ref success);  
                CheckHash( image <= 7, "cef864600fc947062ac359fe9a7cc049c7273b8e", ref success);  
                CheckHash( image >= 7, "52f583bfeb07a6c4c5a26b28f8ae180bf8e0079b", ref success);  

                CheckHash( image < image2, "f907b7bf318b79fd6b9da589646f8b1dac77d0c8", ref success);  
                CheckHash( image > image2, "52f583bfeb07a6c4c5a26b28f8ae180bf8e0079b", ref success);  
                CheckHash( image <= image2, "f4695dbf5bc9ea2796b2e4f360ea4b5ecbf70c37", ref success);  
                CheckHash( image >= image2, "cef864600fc947062ac359fe9a7cc049c7273b8e", ref success);  

                // Binary bitwise operators 
                image &= 5;;
                image |= 7;
                image ^= 8;
                CheckHash(image, "0c26e6610c876b83cf681688eb8e80b952a394ce", ref success);

                image &= image;
                image ^= image;
                image |= image;
                CheckHash( image, "f907b7bf318b79fd6b9da589646f8b1dac77d0c8", ref success);  // just zeros

                
                // image of 1s
                image *= 0;
                image += 1;

                image += image;
                image -= image;
                image *= image;
                image /= image;
                CheckHash(image, "287046eafd10b9984977f6888ea50ea50fe846b5", ref success);  

                image = new Image(100, 100, PixelId.sitkInt8);
                IntPtr buffer = image.GetBufferAsInt8();
                image = new Image(100, 100, PixelId.sitkUInt8);
                buffer = image.GetBufferAsUInt8();

                image = new Image(100, 100, PixelId.sitkInt16);
                buffer = image.GetBufferAsInt16();
                image = new Image(100, 100, PixelId.sitkUInt16);
                buffer = image.GetBufferAsUInt16();

                image = new Image(100, 100, PixelId.sitkInt32);
                buffer = image.GetBufferAsInt32();
                image = new Image(100, 100, PixelId.sitkUInt32);
                buffer = image.GetBufferAsUInt32();

                image = new Image(100, 100, PixelId.sitkInt64);
                buffer = image.GetBufferAsInt64();
                image = new Image(100, 100, PixelId.sitkUInt64);
                buffer = image.GetBufferAsUInt64();

                image = new Image(100, 100, PixelId.sitkFloat32);
                buffer = image.GetBufferAsFloat();
                image = new Image(100, 100, PixelId.sitkFloat64);
                buffer = image.GetBufferAsDouble();

                buffer = image.GetBufferAsVoid();

                if (buffer == IntPtr.Zero)
                {
                  success = ExitFailure;
                  Console.WriteLine("GetBufferAsVoid returned 0.");
                }

            } catch (Exception ex) {
                success = ExitFailure;
                Console.WriteLine(ex);
            }
            return success;
        }
    }
}
