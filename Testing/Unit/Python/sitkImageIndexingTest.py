#==========================================================================
#
#   Copyright NumFOCUS
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

    def doImageAssign(self, img, idx, value):
        img[idx] = value

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
        self.assertEqual(len(img[-4:-1:-2,-2:-1:1]), 0)



        self.assertImageNDArrayEquals(img[1:3,0:2], nda[0:2,1:3])
        self.assertImageNDArrayEquals(img[1:,2:],nda[2:,1:])
        self.assertImageNDArrayEquals(img[:3,:4],nda[:4,:3])
        self.assertImageNDArrayEquals(img[1:,2:],nda[2:,1:])

        self.assertImageNDArrayEquals(img[1:4:2,0:2:2],nda[0:2:2,1:4:2])
        self.assertImageNDArrayEquals(img[1::2,0::2],nda[0::2,1::2])
        self.assertImageNDArrayEquals(img[:3:2,:2:2],nda[:2:2,:3:2])

        # check step size indexing
        self.assertImageNDArrayEquals(img[::2,:],nda[:,::2])
        self.assertImageNDArrayEquals(img[:,::2],nda[::2,:])
        self.assertImageNDArrayEquals(img[::2,::2],nda[::2,::2])
        self.assertImageNDArrayEquals(img[::3,:],nda[:,::3])
        self.assertImageNDArrayEquals(img[:,::3],nda[::3,:])
        self.assertImageNDArrayEquals(img[::3,::3],nda[::3,::3])
        self.assertImageNDArrayEquals(img[::2,::3],nda[::3,::2])
        self.assertImageNDArrayEquals(img[::3,::2],nda[::2,::3])



        # some negative cases
        self.assertImageNDArrayEquals(img[-4:-1,-2:-1],nda[-2:-1,-4:-1])
        self.assertImageNDArrayEquals(img[-1:-4:-2,-2:-1:1],nda[-2:-1:1,-1:-4:-2])
        self.assertImageNDArrayEquals(img[::-1,:],nda[:,::-1])

        # check some exceptions
        self.assertRaises(IndexError, lambda : img[0,3] )
        self.assertRaises(IndexError, lambda : img[5,0] )
        self.assertRaises(IndexError, lambda : img[5,0] )
        self.assertRaises(IndexError, lambda : img[-6,0] )
        self.assertRaises(IndexError, lambda : img[-5,-4] )
        self.assertRaises(IndexError, lambda : img[1] )
        self.assertRaises(IndexError, lambda : img[1,1,1] )

        # check empty image
        self.assertImageNDArrayEquals(img[-1:0,-1:0], nda[-1:0,-1:0])

        self.assertImageNDArrayEquals(img[...], nda[...])
        self.assertImageNDArrayEquals(img[...,1:3], nda[1:3,...])
        self.assertImageNDArrayEquals(img[-2:0,...], nda[...,-2:0])

    def test_setitem(self):
        """ testing __setitem__ with pasting to roi"""

        nda = np.linspace(0, 59, 60).reshape(3, 4, 5)

        img = sitk.GetImageFromArray(nda)

        img[1:3, 2:4, 0:2] = sitk.Image([2, 2, 2], sitk.sitkFloat64) + 1
        self.assertTrue(all([px == 1 for px in img[1:3, 2:4, 0:2]]))
        img[0:1, 0:1, 0:1] = sitk.Image([1, 1, 1], sitk.sitkFloat64) + 2
        self.assertEqual(2, img.GetPixel(0, 0, 0))
        img[0:1, 0:2, 0:3] = sitk.Image([2, 3], sitk.sitkFloat64) + 3
        self.assertTrue(all([px == 3 for px in img[0:1, 0:2, 0:3]]))
        img[0:2, 0:1, 0:3] = sitk.Image([2, 3], sitk.sitkFloat64) + 4
        self.assertTrue(all([px == 4 for px in img[0:2, 0:1, 0:3]]))
        img[0:2, 0:3, 0:1] = sitk.Image([2, 3], sitk.sitkFloat64) + 5
        self.assertTrue(all([px == 5 for px in img[0:2, 0:3, 0:1]]))

        img[-1, 0:1, 0:3] = sitk.Image([1, 3], sitk.sitkFloat64) + 6
        self.assertTrue(all([px == 6 for px in img[-1, 0:1, 0:3]]))
        img[1:2, 1, 0:3] = sitk.Image([1, 3], sitk.sitkFloat64) + 7
        self.assertTrue(all([px == 7 for px in img[1:2, 1, 0:3]]))
        img[2:3, 0:3, 1] = sitk.Image([1, 3], sitk.sitkFloat64) + 8
        self.assertTrue(all([px == 8 for px in img[2:3, 0:3, 1]]))

        img[..., 2:4, 2:3] = sitk.Image([5, 2, 1], sitk.sitkFloat64) + 9
        self.assertTrue(all([px == 9 for px in img[:, 2:4, 2:3]]))
        img[-2, ...] = sitk.Image([4, 3], sitk.sitkFloat64) + 10
        self.assertTrue(all([px == 10 for px in img[-2, :, :]]))
        img[...] = sitk.Image([5, 4, 3], sitk.sitkFloat64) + 11
        self.assertTrue(all([px == 11 for px in img]))
        img[2, 3:4, 1:2, ...] = sitk.Image([1, 1], sitk.sitkFloat64) + 12
        self.assertTrue(all([px == 12 for px in img[2, 3:4, 1:2]]))

        with self.assertRaises(IndexError):
            img[1:3, 2:4] = sitk.Image([2, 2, 2], sitk.sitkFloat64)

        self.assertRaises(IndexError,
                          lambda: self.doImageAssign(img, (slice(0, 2),) * 3, sitk.Image([2, 2], sitk.sitkFloat64)))
        self.assertRaises(IndexError,
                          lambda: self.doImageAssign(img, (slice(0, 2),) * 3, sitk.Image([2, 2, 1], sitk.sitkFloat64)))
        self.assertRaises(IndexError,
                          lambda: self.doImageAssign(img, (slice(0, 2),) * 3, sitk.Image([2, 1, 2], sitk.sitkFloat64)))
        self.assertRaises(IndexError,
                          lambda: self.doImageAssign(img, (slice(0, 2),) * 3, sitk.Image([1, 2, 2], sitk.sitkFloat64)))

    def test_5d_setitem(self):
        """ testing __setitem__ with pasting to 5D roi"""

        # Check if we have 5D Image support
        try:
            sitk.Image([2]*5, sitk.sitkFloat32)
        except RuntimeError:
            return  # exit and don't run the test

        size = [19, 17, 13, 2, 3]
        img = sitk.Image(size, sitk.sitkFloat64)

        img[0, 0, 0, 0, 0] = 1
        self.assertEqual(1, img.GetPixel([0, 0, 0, 0, 0]))

        img[-19, -17, -13, -2, -3] = 2
        self.assertEqual(2, img.GetPixel([0, 0, 0, 0, 0]))

        img[:, :, :, 0, 0] = sitk.Image(size[:3], sitk.sitkFloat64) + 3
        self.assertEqual(3, img.GetPixel([0, 0, 0, 0, 0]))
        self.assertTrue(all([px == 3 for px in img[:, :, :, 0, 0]]))

        img[:, 1, 1, :, 2] = sitk.Image((size[0], size[3]), sitk.sitkFloat64) + 4
        self.assertEqual(4, img.GetPixel([0, 1, 1, 0, 2]))
        self.assertEqual(4, img[0, 1, 1, 0, 2])
        self.assertTrue(all([px == 4 for px in img[:, 1, 1, :, 2]]))

        img = sitk.Image(size, sitk.sitkUInt8)
        img[..., 0] = 1
        self.assertTrue(all([px == 1 for px in img[:, :, :, :, 0]]))
        img[..., 0, 1] = 2
        self.assertTrue(all([px == 2 for px in img[:, :, :, 0, 1]]))
        img[3, ..., 0] = 3
        self.assertTrue(all([px == 3 for px in img[3, :, :, :, 0]]))
        img[3, 15, ..., 2] = 4
        self.assertTrue(all([px == 4 for px in img[3, 15, :, :, 2]]))
        img[1, 2:3, ...] = 5
        self.assertTrue(all([px == 5 for px in img[1, 2:3, :, :, :]]))


    def test_constant_setitem(self):
        """ testing __setitem__ with pasting to 5D roi"""

        img = sitk.Image([10,  11], sitk.sitkVectorUInt8, 3)

        img[0:2, 4:11] = 1
        self.assertTrue(all([px == (1, 1, 1) for px in img[0:2, 4:11]]))

        img[2, 4:11] = 2
        self.assertTrue(all([px == (2, 2, 2) for px in img[2:3, 4:11]]))

        img[..., 4] = 3
        self.assertTrue(all(px == (3, 3, 3) for px in img[:, 4:5]))

        img[2, ...] = 4
        self.assertTrue(all(px == (4, 4, 4) for px in img[2:3, :]))

    def test_constant_5d_setitem(self):
        """ testing __setitem__ with pasting to 5D roi"""

        # Check if we have 5D Image support
        try:
            sitk.Image([2]*5, sitk.sitkFloat32)
        except RuntimeError:
            return  # exit and don't run the test

        size = [19, 17, 13, 2, 3]
        img = sitk.Image(size, sitk.sitkInt32)

        img[:, :, 1, 1, 1] = 1
        self.assertEqual(0, img.GetPixel([0, 0, 0, 0, 0]))
        self.assertEqual(1, img[0, 0, 1, 1, 1])
        self.assertTrue(all([px == 1 for px in img[:, :, 1, 1, 1]]))

        img[:, :, 2, 0, :] = 2
        self.assertEqual(0, img.GetPixel([0, 0, 0, 0, 0]))
        self.assertEqual(1, img[0, 0, 1, 1, 1])
        self.assertTrue(all([px == 2 for px in img[:, :, 2, 0, :]]))

        img[:, :, :, :, :] = 3
        self.assertEqual(3, img.GetPixel([0, 0, 0, 0, 0]))
        self.assertTrue(all([px == 3 for px in img]))

        img[1:3, 2:4, 3:5, 0:2, 0:2] = 4
        self.assertEqual(3, img.GetPixel([0, 0, 0, 0, 2]))
        self.assertEqual(4, img.GetPixel([1, 2, 3, 0, 0]))
        self.assertTrue(all([px == 4 for px in img[1:3, 2:4, 3:5, 0:2, 0:2]]))

    def test_3d_extract(self):
         """testing __getitem__ for extracting 2D slices from 3D image"""

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

         test_array = np.array([0,1,2,3,4]*6).reshape(3,2,5)
         test_array = test_array.swapaxes(2,0)
         test_img = sitk.GetImageFromArray(test_array)
         sliced = test_img[:,:,::2]
         self.assertEqual(sliced.GetSize(), (3,2,3))

         self.assertImageNDArrayEquals(img[...,2], nda[2,...])
         self.assertImageNDArrayEquals(img[-1,...], nda[...,-1])
         self.assertImageNDArrayEquals(img[2,...,2:0:-1], nda[2:0:-1,...,2])


    def test_3d(self):
         """testing __getitem__ for 3D sub-region"""

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

         self.assertImageNDArrayEquals(img[1,...], nda[...,1])
         self.assertImageNDArrayEquals(img[2, 1:3 ,...], nda[...,1:3,2])
         self.assertImageNDArrayEquals(img[...], nda[...])
         self.assertImageNDArrayEquals(img[...,-2], nda[-2,...])


    def test_4d_extract(self):
         """testing __getitem__ for extracting slices from 4D image"""


         # Check if we have 4D Image support
         try:
             sitk.Image([2,2,2,2], sitk.sitkFloat32)
         except RuntimeError:
             return # exit and don't run the test

         nda = np.linspace(0, 119, 120 ).reshape(2,3,4,5)

         img = sitk.GetImageFromArray( nda, isVector=False )


         self.assertRaises(IndexError, lambda : img[5,0] )
         self.assertRaises(IndexError, lambda : img[0,5,:,:] )
         self.assertRaises(IndexError, lambda : img[0, 1, 2,:] )
         self.assertRaises(IndexError, lambda : img[:,0,3] )
         self.assertRaises(IndexError, lambda : img[:,0,3,:,:] )
         self.assertRaises(IndexError, lambda : img[:,0,3,4,:] )
         self.assertRaises(IndexError, lambda : img[2,0,3,4,:] )
         self.assertRaises(IndexError, lambda : img[:,1:1,3,:] )
         self.assertRaises(IndexError, lambda : img[:,:,1:0,3] )
         self.assertRaises(IndexError, lambda : img[0,1,2,:] )

         self.assertImageNDArrayEquals(img[1], nda[:,:,:,1])
         self.assertImageNDArrayEquals(img[-1], nda[:,:,:,-1])
         self.assertImageNDArrayEquals(img[:,-2], nda[:,:,-2])
         self.assertImageNDArrayEquals(img[:,:,2,:], nda[:,2])
         self.assertImageNDArrayEquals(img[:,:,:,1], nda[1])


         # check 4D to 2D cases
         self.assertImageNDArrayEquals(img[0,3], nda[:,:,3,0] )
         self.assertImageNDArrayEquals(img[-1,0], nda[:,:,0,-1] )
         self.assertImageNDArrayEquals(img[-3,:,:,1], nda[1,:,:,-3] )
         self.assertImageNDArrayEquals(img[::-1,3,2,1:2], nda[1:2,2,3,::-1] )


         self.assertImageNDArrayEquals(img[::-1,:,-2,:], nda[:,-2,:,::-1])
         self.assertImageNDArrayEquals(img[::-1,0,:,0:-1], nda[0:-1,:,0,::-1])


         self.assertImageNDArrayEquals(img[-1,...], nda[...,-1])

         self.assertImageNDArrayEquals(img[...,0], nda[0,...])


    def test_4d(self):
         """testing __getitem__ for getting 4D sub-regions"""

         # Check if we have 4D Image support
         try:
             sitk.Image([2,2,2,2], sitk.sitkFloat32)
         except RuntimeError:
             return # exit and don't run the test

         nda = np.linspace(0, 119, 120 ).reshape(2,3,4,5)

         img = sitk.GetImageFromArray( nda, isVector=False )

         # check some exceptions
         self.assertRaises(IndexError, lambda : img[0,1,0,0,0] )
         self.assertRaises(IndexError, lambda : img[0,4,0,0] )
         self.assertRaises(IndexError, lambda : img[0,0,0,2] )
         self.assertRaises(IndexError, lambda : img[-6,0,0,0] )
         self.assertRaises(IndexError, lambda : img[0,0,0,-3] )

         # check basic indexing
         self.assertEqual( img[0,0,0,0], 0.0 )
         self.assertEqual( img[(1,0,0,0)], 1.0 )
         self.assertEqual( img[[2,0,0,0]], 2.0 )
         self.assertEqual( img[3,2,1,0], 33.0 )
         self.assertEqual( img[-4,-3,-2,-1], 86.0 )
         self.assertEqual( img[-4,-3,-2,-1], nda[-1,-2,-3,-4] )


         self.assertImageNDArrayEquals(img[1:-1,1:-1,1:-1], nda[1:-1,1:-1,1:-1])
         self.assertImageNDArrayEquals(img[1:-1,1:-1,1:-1], nda[1:-1,1:-1,1:-1,:])
         self.assertImageNDArrayEquals(img[:,:,:,1:2],nda[1:2,:,:,:])
         self.assertImageNDArrayEquals(img[3:6,1:5,2:4,0:2],nda[0:2,2:4,1:5,3:6])
         self.assertImageNDArrayEquals(img[1:,2:,:2,:],nda[:,:2,2:,1:])

         # some negative cases
         self.assertImageNDArrayEquals(img[::-1,::-1,::-1,::-1], nda[::-1,::-1,::-1,::-1])
         self.assertImageNDArrayEquals(img[:,::-2,::-1,::-3], nda[::-3,::-1,::-2,:])
         self.assertImageNDArrayEquals(img[-1:-4:-1,:,:,:], nda[:,:,:,-1:-4:-1])


    def test_5d(self):
         """testing __getitem__ for 5D image"""

         # Check if we have 5D Image support
         try:
             sitk.Image([2]*5, sitk.sitkFloat32)
         except RuntimeError:
             return # exit and don't run the test

         nda = np.linspace(0, 719, 720 ).reshape(2,3,4,5,6)

         img = sitk.GetImageFromArray( nda, isVector=False )

         # check some exceptions
         self.assertRaises(IndexError, lambda : img[0,1,0,0,0,0] )
         self.assertRaises(IndexError, lambda : img[0,0,4,0,0] )
         self.assertRaises(IndexError, lambda : img[0,0,0,0,2] )
         self.assertRaises(IndexError, lambda : img[-7,0,0,0,0] )
         self.assertRaises(IndexError, lambda : img[0,0,0,0,-3] )

         self.assertEqual( img[0,0,0,0,0], 0.0 )
         self.assertEqual( img[(1,0,0,0,0)], 1.0 )
         self.assertEqual( img[[2,0,0,0,0]], 2.0 )
         self.assertEqual( img[3,2,1,0,0], 45.0 )
         self.assertEqual( img[-5,-4,-3,-2,-1], 517.0 )
         self.assertEqual( img[-5,-4,-3,-2,-1], nda[-1,-2,-3,-4,-5] )

         self.assertImageNDArrayEquals(img[::-1,::-1,::-1,::-1,::-1], nda[::-1,::-1,::-1,::-1,::-1])
         self.assertImageNDArrayEquals(img[::-1,::1,::-1,::1,::-1], nda[::-1,::1,::-1,::1,::-1])
         self.assertImageNDArrayEquals(img[::2,::-1,::3,::-2,:], nda[:,::-2,::3,::-1,::2])

         self.assertImageNDArrayEquals(img[1:4,4,0:2,:,:], nda[:,:,0:2,4,1:4])
         self.assertImageNDArrayEquals(img[1:3,3:0:-1,0,:,1], nda[1,:,0,3:0:-1,1:3])
         self.assertImageNDArrayEquals(img[2,::2,3,::-1,0], nda[0,::-1,3,::2,2])


         self.assertImageNDArrayEquals(img[5,...], nda[...,5])
         self.assertImageNDArrayEquals(img[5,:4,3,2,...], nda[...,2,3,:4,5])
         self.assertImageNDArrayEquals(img[5,4,:3,...,1], nda[1,...,:3,4,5])
         self.assertImageNDArrayEquals(img[5,...,-1,1], nda[1,-1,...,5])
         self.assertImageNDArrayEquals(img[...], nda[...])


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
