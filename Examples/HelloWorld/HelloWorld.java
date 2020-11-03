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

import org.itk.simple.*;

class HelloWorld {

  public static void main(String argv[]) {

    // Create an image
    PixelIDValueEnum pixelType = PixelIDValueEnum.sitkUInt8;
    long[] isize = {128, 128};
    VectorUInt32 imageSize = new VectorUInt32( isize );
    Image image = new Image( imageSize, pixelType );

    // Create a face image
    double[] fsize = {64., 64.};
    VectorDouble faceSize = new VectorDouble( fsize );
    double[] fcenter = {64., 64.};
    VectorDouble faceCenter = new VectorDouble( fcenter );
    Image face = SimpleITK.gaussianSource( pixelType, imageSize, faceSize, faceCenter );

    // Create eye images
    double[] esize = {5., 5.};
    VectorDouble eyeSize = new VectorDouble( esize );
    double[] e1center = {48., 48.};
    VectorDouble eye1Center = new VectorDouble( e1center );
    double[] e2center = {80., 48.};
    VectorDouble eye2Center = new VectorDouble( e2center );
    Image eye1 = SimpleITK.gaussianSource( pixelType, imageSize, eyeSize, eye1Center, 150 );
    Image eye2 = SimpleITK.gaussianSource( pixelType, imageSize, eyeSize, eye2Center, 150 );

    // Apply the eyes to the face
    face = SimpleITK.subtract( face, eye1 );
    face = SimpleITK.subtract( face, eye2 );
    face = SimpleITK.binaryThreshold( face, 200., 255., (short) 255 );

    // Create the mouth
    double[] mradius = {30., 20.};
    VectorDouble mouthRadius = new VectorDouble( mradius );
    double[] mcenter = {64., 76.};
    VectorDouble mouthCenter = new VectorDouble( mcenter );
    Image mouth = SimpleITK.gaussianSource( pixelType, imageSize, mouthRadius, mouthCenter );
    mouth = SimpleITK.binaryThreshold( mouth, 200, 255, (short) 255 );
    mouth = SimpleITK.subtract( 255, mouth );

    // Paste the mouth onto the face
    long[] msize = {64, 18};
    VectorUInt32 mouthSize = new VectorUInt32( msize );
    int[] mloc = {32, 76};
    VectorInt32 mouthLoc = new VectorInt32( mloc );
    face = SimpleITK.paste( face, mouth, mouthSize, mouthLoc, mouthLoc );

    // Apply the face to the original image
    image = SimpleITK.add( image, face );

    // Display the results
    if(System.getenv("SITK_NOSHOW") == null) {
      SimpleITK.show( image, "Hello World: Java", true );
    }
  }

}
