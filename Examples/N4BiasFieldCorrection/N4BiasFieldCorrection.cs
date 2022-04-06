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
using System;
using itk.simple;
using sitk = itk.simple.SimpleITK;

namespace itk.simple.examples {
  class N4BiasFieldCorrection {
    static void Main(string[] args) {
      try {
        if (args.Length < 2) {
          Console.WriteLine("Usage: N4BiasFieldCorrection inputImage outputImage"
            + " [shrinkFactor] [maskImage] [numberOfIterations]"
            + " [numberOfFittingLevels]\n");

          return;
        }
        // Read input image
        Image inputImage = sitk.ReadImage(args[0], PixelIDValueEnum.sitkFloat32);
        Image image = inputImage;


        Image maskImage;
        if (args.Length>3) {
          maskImage = sitk.ReadImage(args[3], PixelIDValueEnum.sitkUInt8);
        } else {
          maskImage = sitk.OtsuThreshold(image, 0, 1, 200);
        }

        uint shrinkFactor = 1;
        if (args.Length>2) {
          shrinkFactor = UInt32.Parse(args[2]);
          uint[] s_array = new uint[image.GetDimension()];
          for (uint i=0; i<image.GetDimension(); i++) {
            s_array[i] = shrinkFactor;
          }
          VectorUInt32 shrink = new VectorUInt32(s_array);
          image = sitk.Shrink(inputImage, shrink);
          maskImage = sitk.Shrink(maskImage, shrink);
        }

        N4BiasFieldCorrectionImageFilter corrector
          = new N4BiasFieldCorrectionImageFilter();

        uint numFittingLevels = 4;

        if (args.Length>5) {
          numFittingLevels = UInt32.Parse(args[5]);
        }

        if (args.Length>4) {
          uint it = UInt32.Parse(args[4]);
          uint[] it_array = new uint[numFittingLevels];
          for (uint i=0; i<numFittingLevels; i++) {
            it_array[i] = it;
          }
          VectorUInt32 iterations = new VectorUInt32(it_array);
          corrector.SetMaximumNumberOfIterations(iterations);
        }

        Image corrected_image = corrector.Execute(image, maskImage);

        Image log_bias_field = corrector.GetLogBiasFieldAsImage(inputImage);

        Image corrected_image_full_resolution = sitk.Divide(inputImage, sitk.Exp(log_bias_field));

        sitk.WriteImage(corrected_image_full_resolution, args[1]);

        if (shrinkFactor>1) {
          sitk.WriteImage(corrected_image, "CSharp-Example-N4BiasFieldCorrection-shrunk.nrrd");
        }

        if (Environment.GetEnvironmentVariable("SITK_NOSHOW") == null)
          SimpleITK.Show(corrected_image, "N4 Corrected");

      } catch (Exception ex) {
        Console.WriteLine(ex);
      }
    }
  }
}
