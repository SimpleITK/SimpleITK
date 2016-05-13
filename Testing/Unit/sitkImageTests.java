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

import java.math.BigInteger;
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
    int ntests = 2;
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
    if (npass == ntests)
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
    int[] v = {1,1};
    VectorUInt32 idx = new VectorUInt32( v.length );

    for (int i = 0; i < v.length; i++)
      {
      idx.set( i, v[i] );
      }

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

  public static boolean LabelShapeStatisticsTest()
    {
    int size = 10;
    int i;
    long j;
    short val = 1;


    /* Make a 10x10 test image */
    Image image = new Image(size, size, PixelIDValueEnum.sitkUInt8);
    VectorUInt32 idx = new VectorUInt32( 2 );

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
      j = BigIntegerFix.Convert( filter.getNumberOfLabels() );
      if (j != 1)
        {
        throw new Exception("Wrong number of labels");
        }
      long npix;
      double perim;

      System.out.println("Label,\t#pix,\tperimeter");
      for (i=0; i<j; i++)
        {
        npix = BigIntegerFix.Convert( filter.getNumberOfPixels(labels.get(i)) );
        perim = filter.getPerimeter( labels.get(i) );
        System.out.format( "%d,\t%d,\t%f\n", labels.get(i), npix, perim );

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
