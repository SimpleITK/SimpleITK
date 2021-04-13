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

import java.math.BigInteger;
import static java.lang.Math.toIntExact;
import org.itk.simple.*;

/* This class is needed because on some systems uint64_t gets converted to long
 * while on others it becomes a BigInteger. */
class BigIntegerFix
  {
  public static long Convert( long value )
    {
    return value;
    }

  public static long Convert( BigInteger value )
    {
    return value.longValue();
    }
  }

class sitkImageTests
  {

  public static void main(String argv[])
    {
    int npass = 0;
    int nfail = 0;

    System.out.println("[==========] Running Java.ImageTests");


    System.out.println("[----------]");
    System.out.println("[ RUN      ] Java.BasicImageTest");
    if (BasicImageTest())
      {
      System.out.println("[       OK ] Java.BasicImageTest");
      npass++;
      }
    else
      {
      System.out.println("[     FAIL ] Java.BasicImageTest");
      nfail++;
      }
    System.out.println("[----------]");

    System.out.println("[----------]");
    System.out.println("[ RUN      ] Java.ImageBufferTest");
    if (ImageBufferTest())
      {
      System.out.println("[       OK ] Java.ImageBufferTest");
      npass++;
      }
    else
      {
      System.out.println("[     FAIL ] Java.ImageBufferTest");
      nfail++;
      }
    System.out.println("[----------]");

    System.out.println("[----------]");
    System.out.println("[ RUN      ] Java.LabelShapeStatisticsTest");
    if (LabelShapeStatisticsTest())
      {
      System.out.println("[       OK ] Java.LabelShapeStatisticsTest");
      npass++;
      }
    else
      {
      System.out.println("[     FAIL ] Java.LabelShapeStatisticsTest");
      nfail++;
      }
    System.out.println("[----------]");
    System.out.println("[==========]");

    if (nfail == 0)
      {
      System.out.println("[  PASSED  ]");
      }
    else
      {
      System.out.println("[  FAILED  ]");
      System.exit(1);
      }
    }

  public static boolean BasicImageTest()
    {
    long[] v = {1,1};
    VectorUInt32 idx = new VectorUInt32( v );

    int size = 10;
    short val = 42;

    Image image = new Image(size, size, PixelIDValueEnum.sitkUInt8);

    image.setPixelAsUInt8(idx, val);

    try
      {
      if (size != image.getWidth())
        {
        throw new Exception("Bad width");
        }
      }
    catch (Exception e)
      {
      return false;
      }

    short newval;

    newval = image.getPixelAsUInt8(idx);

    try
      {
      if (newval != val)
        {
        throw new Exception("Bad pixel value");
        }
      }
    catch (Exception e)
      {
      return false;
      }
    return true;
    }

  public static boolean ImageBufferTest()
    {
      long[] v = {2,3,4};
    VectorUInt32 idx = new VectorUInt32( v );

    int size = 7*8*9;
    short val = 42;

    Image image = new Image(7,8,9, PixelIDValueEnum.sitkUInt8);
    image.setPixelAsUInt8(idx, (short)99);

    // Low level method is not recommended, but has been useful when
    // interfacing with other low level C based libraries in Java
    long ptr = image.getBufferAsNativePointer();

    if (ptr == 0)
      {
        System.out.println("Null native buffer pointer");
        return false;
      }

    java.nio.Buffer b1 = image.getBufferAsBuffer();

    if (b1.capacity() != size)
      {
        System.out.println("Capacity is not as expected");
        return false;
      }

    if (!b1.isDirect())
      {
        System.out.println("Buffer is not direct");
        return false;
      }

    if (b1.isReadOnly())
      {
        System.out.println("Buffer is read-only");
        return false;
      }

    java.nio.ByteBuffer bb = (java.nio.ByteBuffer) b1;

    if (bb.get(0) != 0)
      {
        System.out.println("Expected 0 value");
        return false;
      }

    if (bb.get(2+7*3+7*8*4) != 99)
      {
        System.out.println("Expected 99 value");
        return false;
      }



    return true;
    }

  public static boolean LabelShapeStatisticsTest()
    {
    int size = 10;
    long i;
    long j;
    short val = 1;


    /* Make a 10x10 test image */
    Image image = new Image(size, size, PixelIDValueEnum.sitkUInt8);
    VectorUInt32 idx = new VectorUInt32( 2, 0 );

    /* Fill in a 4x4 square in the middle of the image */
    for (j=4; j<8; j++)
      {
      idx.set(1, j);
      for (i=4; i<8; i++)
        {
        idx.set(0, i);
        image.setPixelAsUInt8(idx, val);
        }
      }

    try
      {
      /* Run statistics on the test image */
      LabelShapeStatisticsImageFilter filter = new LabelShapeStatisticsImageFilter();
      filter.execute(image);

      VectorInt64 labels = filter.getLabels();
      long numberOfLabels =  BigIntegerFix.Convert( filter.getNumberOfLabels() );
      if (numberOfLabels != 1)
        {
        throw new Exception("Wrong number of labels");
        }
      long npix;
      double perim;

      System.out.println("Label,\t#pix,\tperimeter");
      for (i=0; i<numberOfLabels; i++)
        {
        int label = toIntExact(labels.get(toIntExact(i)));
        npix =  BigIntegerFix.Convert( filter.getNumberOfPixels(label) );
        perim = filter.getPerimeter(label);
        System.out.format( "%d,\t%d,\t%f\n", label, npix, perim );

        /* The first (and only) label should have 16 pixels */
        if (i==0)
          {
          if (npix != 16)
            {
            throw new Exception("Wrong number of pixels");
            }
          }
        }
      }
    catch (Exception e)
      {
      return false;
      }

    return true;
  }

}
