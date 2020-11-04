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

namespace itk.simple.examples {
  class HelloWorld {

    static void Main(string[] args) {

      try {

        // Create an image
        PixelIDValueEnum pixelType = PixelIDValueEnum.sitkUInt8;
        VectorUInt32 imageSize = new VectorUInt32( new uint[] { 128, 128 } );
        Image image = new Image( imageSize, pixelType );

        // Create a face image
        VectorDouble faceSize = new VectorDouble( new double[] { 64, 64 } );
        VectorDouble faceCenter = new VectorDouble( new double[] { 64, 64 } );
        Image face = SimpleITK.GaussianSource( pixelType, imageSize, faceSize, faceCenter );

        // Create eye images
        VectorDouble eyeSize = new VectorDouble( new double[] { 5, 5 } );
        VectorDouble eye1Center = new VectorDouble( new double[] { 48, 48 } );
        VectorDouble eye2Center = new VectorDouble( new double[] { 80, 48 } );
        Image eye1 = SimpleITK.GaussianSource( pixelType, imageSize, eyeSize, eye1Center, 150 );
        Image eye2 = SimpleITK.GaussianSource( pixelType, imageSize, eyeSize, eye2Center, 150 );

        // Apply the eyes to the face
        face = SimpleITK.Subtract( face, eye1 );
        face = SimpleITK.Subtract( face, eye2 );
        face = SimpleITK.BinaryThreshold( face, 200, 255, 255 );


        // Create the mouth
        VectorDouble mouthRadii = new VectorDouble( new double[] { 30, 20 } );
        VectorDouble mouthCenter = new VectorDouble( new double[] { 64, 76 } );
        Image mouth = SimpleITK.GaussianSource( pixelType, imageSize, mouthRadii, mouthCenter );
        mouth = SimpleITK.BinaryThreshold( mouth, 200, 255, 255 );
        mouth = SimpleITK.Subtract( 255, mouth );

        // Paste the mouth onto the face
        VectorUInt32 mouthSize = new VectorUInt32( new uint[] { 64, 18 } );
        VectorInt32 mouthLoc = new VectorInt32(  new int[] { 32, 76 } );
        face = SimpleITK.Paste( face, mouth, mouthSize, mouthLoc, mouthLoc );

        // Apply the face to the original image
        image = SimpleITK.Add( image, face );

        // Display the results
        if (Environment.GetEnvironmentVariable("SITK_NOSHOW") == null)
          SimpleITK.Show( image, "Hello World: CSharp", true );

      } catch (Exception ex) {
        Console.WriteLine(ex);
      }
    }

  }
}
