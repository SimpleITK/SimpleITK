#==========================================================================
#
#   Copyright Insight Software Consortium
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#          http://www.apache.org/licenses/LICENSE-2.0.txt
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#
#==========================================================================*/
from __future__ import print_function
import sys
import unittest


import SimpleITK as sitk
import numpy as np


class TestImageIndexingInterface(unittest.TestCase):
    """This tests the indexing feature for the Image class. """


    def setUp(self):
        pass

    def assertImageNDArrayEquals(self, img, nda, msg=""):
        for p,n in zip(img, nda.flat):
            self.assertEqual( p, n, msg )


    def _helper_check_sitk_to_numpy_type(self, sitkType, numpyType):
        image = sitk.Image( (9, 10), sitkType, 1 )
        a = sitk.GetArrayFromImage( image )
        self.assertEqual( numpyType, a.dtype )
        self.assertEqual( (10, 9), a.shape )


    def test_2d(self):
        """testing __getitem__ for 2D image"""

        nda = np.linspace(0, 14, 15 ).reshape(3,5)

        img = sitk.GetImageFromArray( nda )

        self.assertEqual( img.GetSize(), (5,3) )

        # check basic indexing
        self.assertEqual( img[0,0], 0.0 )
        self.assertEqual( img[(1,0)], 1.0 )
        self.assertEqual( img[[2,0]], 2.0 )
        self.assertEqual( img[1,2], 11.0 )
        self.assertEqual( img[-1,-2], 9.0 )

        # check default slice indexing
        self.assertImageNDArrayEquals(img[:,:],nda)
        self.assertImageNDArrayEquals(img[:],nda)
        self.assertImageNDArrayEquals(img[::-1,::-1],nda[::-1,::-1])

        # out of bounds cases and empty
        self.assertEqual(len(img[:,5:6]), 0)
        self.assertEqual(len(img[:,2:1]), 0)
        self.assertEqual(len(img[-6:0,:]), 0)
        self.assertEqual(len(img[0:0,:]), 0)



        self.assertImageNDArrayEquals(img[1:3,0:2], nda[0:2,1:3])
        self.assertImageNDArrayEquals(img[1:,2:],nda[2:,1:])
        self.assertImageNDArrayEquals(img[:3,:4],nda[:4,:3])
        self.assertImageNDArrayEquals(img[1:,2:],nda[2:,1:])

        self.assertImageNDArrayEquals(img[1:4:2,0:2:2],nda[0:2:2,1:4:2])
        self.assertImageNDArrayEquals(img[1::2,0::2],nda[0::2,1::2])
        self.assertImageNDArrayEquals(img[:3:2,:2:2],nda[:2:2,:3:2])


        # some negative cases
        self.assertImageNDArrayEquals(img[-4:-1,-2:-1],nda[-2:-1,-4:-1])
        self.assertImageNDArrayEquals(img[-4:-1:-2,-2:-1:1],nda[-2:-1:1,-4:-1:-2])
        self.assertImageNDArrayEquals(img[::-1,:],nda[:,::-1])

        # check some exceptions
        self.assertRaises(IndexError, lambda : img[0,3] )
        self.assertRaises(IndexError, lambda : img[5,0] )
        self.assertRaises(IndexError, lambda : img[5,0] )
        self.assertRaises(IndexError, lambda : img[-6,0] )
        self.assertRaises(IndexError, lambda : img[-5,-4] )
        self.assertRaises(IndexError, lambda : img[1] )
        self.assertRaises(IndexError, lambda : img[1,1,1] )


    def test_3d_extract(self):
         """testing __getitem__ for extrating 2D slices from 3D image"""

         nda = np.linspace(0, 59, 60 ).reshape(3,4,5)

         img = sitk.GetImageFromArray( nda )

         # check some exceptions
         self.assertRaises(IndexError, lambda : img[0,3] )
         self.assertRaises(IndexError, lambda : img[:,0,3] )
         self.assertRaises(IndexError, lambda : img[:,1:1,3] )
         self.assertRaises(IndexError, lambda : img[:,1:0,3] )

         self.assertImageNDArrayEquals(img[1], nda[:,:,1])
         self.assertImageNDArrayEquals(img[-1], nda[:,:,-1])
         self.assertImageNDArrayEquals(img[:,-2], nda[:,-2])
         self.assertImageNDArrayEquals(img[:,:,2], nda[2])

         self.assertImageNDArrayEquals(img[::-1,:,-2], nda[-2,:,::-1])
         self.assertImageNDArrayEquals(img[::-1,0,1:-1], nda[1:-1,0,::-1])


    def test_3d(self):
         """testing __getitem__ for extrating 2D slices from 3D image"""

         nda = np.linspace(0, 59, 60 ).reshape(3,4,5)

         img = sitk.GetImageFromArray( nda )

         # check some exceptions
         self.assertRaises(IndexError, lambda : img[0,3,0,0] )
         self.assertRaises(IndexError, lambda : img[0,4,0] )
         self.assertRaises(IndexError, lambda : img[0,0,3] )
         self.assertRaises(IndexError, lambda : img[-6,0,0] )
         self.assertRaises(IndexError, lambda : img[0,0,-4] )

         # check basic indexing
         self.assertEqual( img[0,0,0], 0.0 )
         self.assertEqual( img[(1,0,0)], 1.0 )
         self.assertEqual( img[[2,0,0]], 2.0 )
         self.assertEqual( img[3,2,1], 33.0 )
         self.assertEqual( img[-3,-2,-1], 52.0 )


         self.assertImageNDArrayEquals(img[1:-1,1:-1,1:-1], nda[1:-1,1:-1,1:-1])
         self.assertImageNDArrayEquals(img[:,:,1:2],nda[1:2,:,:])
         self.assertImageNDArrayEquals(img[1:5,2:4,0:2],nda[0:2,2:4,1:5])
         self.assertImageNDArrayEquals(img[1:,2:,:2],nda[:2,2:,1:])

         # some negative cases
         self.assertImageNDArrayEquals(img[::-1,::-1,::-1], nda[::-1,::-1,::-1])
         self.assertImageNDArrayEquals(img[:,::-2,::-1], nda[::-1,::-2,:])
         self.assertImageNDArrayEquals(img[-1:-4:-1,:,:], nda[:,:,-1:-4:-1])

    def test_compare(self):

        img = sitk.Image(1,1,sitk.sitkFloat32)
        self.assertEqual(img.GetPixel(0,0), 0.0)

        self.assertEqual((img<0).GetPixel(0,0), 0)
        self.assertEqual((img<=0).GetPixel(0,0), 1)

        self.assertEqual((0>img).GetPixel(0,0), 0)
        self.assertEqual((0>=img).GetPixel(0,0), 1)

        self.assertEqual((img>0).GetPixel(0,0), 0)
        self.assertEqual((img>=0).GetPixel(0,0), 1)

        self.assertEqual((0<img).GetPixel(0,0), 0)
        self.assertEqual((0<=img).GetPixel(0,0), 1)

        img.SetPixel(0,0, 0.5)

        self.assertEqual((img<0.5).GetPixel(0,0), 0)
        self.assertEqual((img<=0.5).GetPixel(0,0), 1)

        self.assertEqual((0.5>img).GetPixel(0,0), 0)
        self.assertEqual((0.5>=img).GetPixel(0,0), 1)

        self.assertEqual((img>0.5).GetPixel(0,0), 0)
        self.assertEqual((img>=0.5).GetPixel(0,0), 1)

        self.assertEqual((0.5<img).GetPixel(0,0), 0)
        self.assertEqual((0.5<=img).GetPixel(0,0), 1)

        self.assertEqual((img<-1).GetPixel(0,0), 0)
        self.assertEqual((img<=-1).GetPixel(0,0), 0)

        self.assertEqual((-1>img).GetPixel(0,0), 0)
        self.assertEqual((-1>=img).GetPixel(0,0), 0)

        self.assertEqual((img>-1).GetPixel(0,0), 1)
        self.assertEqual((img>=-1).GetPixel(0,0), 1)

        self.assertEqual((-1<img).GetPixel(0,0), 1)
        self.assertEqual((-1<=img).GetPixel(0,0), 1)

if __name__ == '__main__':
    unittest.main()
