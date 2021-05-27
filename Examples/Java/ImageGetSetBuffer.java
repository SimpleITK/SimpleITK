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

 import org.itk.simple.Image;
 import org.itk.simple.SimpleITK;
 import org.itk.simple.PixelIDValueEnum;


 class ImageGetSetBuffer {

    public static void main(String args[]) {

      if (args.length < 1) {
        System.out.format("Usage: ImageSetGetBuffer <input>");
        System.exit(-1);
      }

      Image image = SimpleITK.readImage(args[0]);

      // The loaded image may be of any type and number of components, so convert to float,
      // so there is a known type.
      if (image.getNumberOfComponentsPerPixel() != 1) {
        image = SimpleITK.cast(image, PixelIDValueEnum.sitkVectorFloat32);
      } else {
        image = SimpleITK.cast(image, PixelIDValueEnum.sitkFloat32);
      }

      java.nio.FloatBuffer buffer = (java.nio.FloatBuffer)image.getBufferAsBuffer();

      System.out.println(buffer.toString());

      for (int i = 0; i < 10 && buffer.hasRemaining(); ++i) {
        System.out.println(buffer.get());
      }

      buffer.rewind();
      while (buffer.hasRemaining()) {
       buffer.put(0);
      }

    }
  }
