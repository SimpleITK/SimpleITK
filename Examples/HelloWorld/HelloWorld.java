/*=========================================================================
*
*  Copyright Insight Software Consortium
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

import org.itk.simple.*;

class HelloWorld {

  public static void main(String argv[]) {

    // Create an image
    PixelIDValueEnum pixelType = PixelIDValueEnum.sitkUInt8;
    VectorUInt32 imageSize = new VectorUInt32( 2 );
    imageSize.set( 0, 128 );
    imageSize.set( 1, 128 );
    Image image = new Image( imageSize, pixelType );

    // Create a face image
    VectorDouble faceSize = new VectorDouble( 2 );
    faceSize.set( 0, 64 );
    faceSize.set( 1, 64 );
    VectorDouble faceCenter = new VectorDouble( 2 );
    faceCenter.set( 0, 64 );
    faceCenter.set( 1, 64 );
    Image face = SimpleITK.gaussianSource( pixelType, imageSize, faceSize, faceCenter );

    // Create eye images
    VectorDouble eyeSize = new VectorDouble( 2 );
    eyeSize.set( 0, 5 );
    eyeSize.set( 1, 5 );
    VectorDouble eye1Center = new VectorDouble( 2 );
    eye1Center.set( 0, 48 );
    eye1Center.set( 1, 48 );
    VectorDouble eye2Center = new VectorDouble( 2 );
    eye2Center.set( 0, 80 );
    eye2Center.set( 1, 48 );
    Image eye1 = SimpleITK.gaussianSource( pixelType, imageSize, eyeSize, eye1Center, 150 );
    Image eye2 = SimpleITK.gaussianSource( pixelType, imageSize, eyeSize, eye2Center, 150 );

    // Apply the eyes to the face
    face = SimpleITK.subtract( face, eye1 );
    face = SimpleITK.subtract( face, eye2 );
    face = SimpleITK.binaryThreshold( face, 200., 255., (short) 255 );

    // Create the mouth
    VectorDouble mouthRadii = new VectorDouble( 2 );
    mouthRadii.set( 0, 30 );
    mouthRadii.set( 1, 20 );
    VectorDouble mouthCenter = new VectorDouble( 2 );
    mouthCenter.set( 0, 64 );
    mouthCenter.set( 1, 76 );
    Image mouth = SimpleITK.gaussianSource( pixelType, imageSize, mouthRadii, mouthCenter );
    mouth = SimpleITK.binaryThreshold( mouth, 200, 255, (short) 255 );
    mouth = SimpleITK.subtract( 255, mouth );

    // Paste the mouth onto the face
    VectorUInt32 mouthSize = new VectorUInt32( 2 );
    mouthSize.set( 0, 64 );
    mouthSize.set( 1, 18 );
    VectorInt32 mouthLoc = new VectorInt32( 2 );
    mouthLoc.set( 0, 32 );
    mouthLoc.set( 1, 76 );
    face = SimpleITK.paste( face, mouth, mouthSize, mouthLoc, mouthLoc );

    // Apply the face to the original image
    image = SimpleITK.add( image, face );

    // Display the results
    SimpleITK.show( image, "Hello World: Java", true );
  }

}
