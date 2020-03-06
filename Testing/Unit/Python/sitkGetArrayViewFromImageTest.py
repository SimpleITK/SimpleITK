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
import datetime as dt
import timeit


import SimpleITK as sitk
import numpy as np

sizeX = 4
sizeY = 5
sizeZ = 3
newSimpleITKPixelValueInt32 = -3000
newNumPyElementValueInt32   = 200



class TestNumpySimpleITKMemoryviewInterface(unittest.TestCase):
    """ This tests numpy array <-> SimpleITK Image conversion. """

    def setUp(self):
        pass

    def _helper_check_sitk_to_numpy_type(self, sitkType, numpyType):
        if sitkType == sitk.sitkUnknown:
            return
        image = sitk.Image((9, 10), sitkType, 1)
        a = sitk.GetArrayViewFromImage(image)
        self.assertEqual(numpyType, a.dtype)
        self.assertEqual((10, 9), a.shape)

    def test_type_to_numpy(self):
        "try all sitk pixel types to convert to NumPy array view"

        self._helper_check_sitk_to_numpy_type(sitk.sitkUInt8, np.uint8)
        self._helper_check_sitk_to_numpy_type(sitk.sitkUInt16, np.uint16)
        self._helper_check_sitk_to_numpy_type(sitk.sitkUInt32, np.uint32)
        self._helper_check_sitk_to_numpy_type(sitk.sitkUInt64, np.uint64)
        self._helper_check_sitk_to_numpy_type(sitk.sitkInt8, np.int8)
        self._helper_check_sitk_to_numpy_type(sitk.sitkInt16, np.int16)
        self._helper_check_sitk_to_numpy_type(sitk.sitkInt32, np.int32)
        self._helper_check_sitk_to_numpy_type(sitk.sitkInt64, np.int64)
        self._helper_check_sitk_to_numpy_type(sitk.sitkFloat32, np.float32)
        self._helper_check_sitk_to_numpy_type(sitk.sitkFloat64, np.float64)
        self._helper_check_sitk_to_numpy_type(sitk.sitkVectorUInt8, np.uint8)
        self._helper_check_sitk_to_numpy_type(sitk.sitkVectorInt8, np.int8)
        self._helper_check_sitk_to_numpy_type(sitk.sitkVectorUInt16, np.uint16)
        self._helper_check_sitk_to_numpy_type(sitk.sitkVectorInt16, np.int16)
        self._helper_check_sitk_to_numpy_type(sitk.sitkVectorUInt32, np.uint32)
        self._helper_check_sitk_to_numpy_type(sitk.sitkVectorInt32, np.int32)
        self._helper_check_sitk_to_numpy_type(sitk.sitkVectorUInt64, np.uint64)
        self._helper_check_sitk_to_numpy_type(sitk.sitkVectorInt64, np.int64)
        self._helper_check_sitk_to_numpy_type(sitk.sitkVectorFloat32, np.float32)
        self._helper_check_sitk_to_numpy_type(sitk.sitkVectorFloat64, np.float64)

    def test_to_numpy_and_back(self):
        """Test converting an image to NumPy array view and back"""

        img = sitk.GaussianSource( sitk.sitkFloat32, [100,100], sigma=[10]*3, mean=[50,50] )

        h = sitk.Hash( img )

        img2 = sitk.GetImageFromArray( sitk.GetArrayViewFromImage(img))
        self.assertEqual( h, sitk.Hash( img2 ))

    def test_vector_image_to_numpy(self):
        """Test converting back and forth between NumPy array view and SimpleITK
        images where the SimpleITK image has multiple components and
        stored as a VectorImage."""


        # Check 2D
        img = sitk.PhysicalPointSource(sitk.sitkVectorFloat32, [3,4])
        h = sitk.Hash( img )

        nda = sitk.GetArrayViewFromImage(img)

        self.assertEqual(nda.shape, (4,3,2))
        self.assertEqual(nda[0,0].tolist(), [0,0])
        self.assertEqual(nda[2,1].tolist(), [1,2])
        self.assertEqual(nda[0,:,0].tolist(), [0,1,2])

        img2 = sitk.GetImageFromArray(nda, isVector=True)
        self.assertEqual(h, sitk.Hash(img2))


        # check 3D
        img = sitk.PhysicalPointSource(sitk.sitkVectorFloat32, [3,4,5])
        h = sitk.Hash(img)

        nda = sitk.GetArrayViewFromImage(img)

        self.assertEqual(nda.shape, (5,4,3,3))
        self.assertEqual(nda[0,0,0].tolist(), [0,0,0])
        self.assertEqual(nda[0,0,:,0].tolist(), [0,1,2])
        self.assertEqual(nda[0,:,1,1].tolist(), [0,1,2,3])


        img2 = sitk.GetImageFromArray(nda)
        self.assertEqual(img2.GetSize(), img.GetSize())
        self.assertEqual(img2.GetNumberOfComponentsPerPixel(), img.GetNumberOfComponentsPerPixel())
        self.assertEqual(h, sitk.Hash(img2))

    def test_arrayview_writable(self):
        """Test correct behavior of writablity to the returned array view."""

        img = sitk.Image((9, 10), sitk.sitkFloat32, 1)

        a = sitk.GetArrayViewFromImage(img)

        with self.assertRaises(ValueError):
            a.fill(0)


    def test_processing_time(self):
      """Check the processing time the conversions from SimpleITK Image
         to numpy array (GetArrayViewFromImage) and
         numpy memoryview (GetArrayViewFromImage)."""

      # Performance test for SimpleITK Image -> NumPy array
      img = sitk.GaussianSource(sitk.sitkFloat32, [3000,3000], sigma=[10]*3, mean=[50,50])

      print("\nGet NumPy array from 3000x3000 SimpleITK Image")
      nparray_time_elapsed = min(timeit.repeat(lambda: sitk.GetArrayFromImage(img), repeat=5, number=1))
      print ("Processing time of GetArrayFromImage (Copy operation)  :: {0} (us)".format(nparray_time_elapsed*1e6))

      npview_time_elapsed = min(timeit.repeat(lambda: sitk.GetArrayViewFromImage(img), repeat=5, number=1))
      print ("Processing time of GetArrayViewFromImage (Array view)      :: {0} (us)".format(npview_time_elapsed*1e6))

      self.assertTrue( nparray_time_elapsed > npview_time_elapsed)

      # Performance test for NumPy array -> SimpleITK Image
      Big_nparray = np.zeros((3000,3000), dtype=np.int64);



if __name__ == '__main__':
    unittest.main()
