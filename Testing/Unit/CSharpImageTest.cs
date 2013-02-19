using System;
using itk.simple;
using sitk = itk.simple.SimpleITK;
using PixelId = itk.simple.PixelIDValueEnum;

namespace itk.simple {
    /// <summary>Test itk.simple.Image.</summary>
    public class CSharpImageTest {
        public const int ExitSuccess = 0;
        public const int ExitFailure = 1;

        /// <summary>Main entry point.</summary>
        public static int Main (string[] args) {
            int success = ExitSuccess;
            try {
                Image image = new Image(100, 100, PixelId.sitkInt8);
                Image image2 = new Image(100, 100, PixelId.sitkInt8);

                // Unary operators
                image = -image;
                image = +image;
                image = !image;
                image = ~image;

                // Binary mathematical operators
                image += 1;
                image -= 1;
                image *= 2;
                image /= 2;

                image += image;
                image -= image;
                image *= image;
                image /= image;

                // Binary bitwise operators
                image &= 2;
                image |= 2;
                image ^= 2;

                image &= image;
                image |= image;
                image ^= image;

                // Comparison operators
                Image binary = image < 1;
                binary = image > 1;
                binary = image <= 1;
                binary = image >= 1;

                binary = image < image2;
                binary = image > image2;
                binary = image <= image2;
                binary = image >= image2;

            } catch (Exception ex) {
                success = ExitFailure;
                Console.WriteLine(ex);
            }
            return success;
        }
    }
}
