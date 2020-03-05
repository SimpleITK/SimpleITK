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

sizeX = 4
sizeY = 5
sizeZ = 3


class TestNumpySimpleITKInterface(unittest.TestCase):
    """ This tests numpy array <-> SimpleITK Image conversion. """


    def setUp(self):
        pass


    def _helper_check_sitk_to_numpy_type(self, sitkType, numpyType):
        image = sitk.Image( (9, 10), sitkType, 1 )
        a = sitk.GetArrayFromImage( image )
        self.assertEqual( numpyType, a.dtype )
        self.assertEqual( (10, 9), a.shape )

    def test_type_to_numpy(self):
        "try all sitk pixel type to convert to numpy"

        self._helper_check_sitk_to_numpy_type(sitk.sitkUInt8, np.uint8)
        self._helper_check_sitk_to_numpy_type(sitk.sitkUInt16, np.uint16)
        self._helper_check_sitk_to_numpy_type(sitk.sitkUInt32, np.uint32)
        if sitk.sitkUInt64 != sitk.sitkUnknown:
            self._helper_check_sitk_to_numpy_type(sitk.sitkUInt64, np.uint64)
        self._helper_check_sitk_to_numpy_type(sitk.sitkInt8, np.int8)
        self._helper_check_sitk_to_numpy_type(sitk.sitkInt16, np.int16)
        self._helper_check_sitk_to_numpy_type(sitk.sitkInt32, np.int32)
        if sitk.sitkInt64 != sitk.sitkUnknown:
            self._helper_check_sitk_to_numpy_type(sitk.sitkInt64, np.int64)
        self._helper_check_sitk_to_numpy_type(sitk.sitkFloat32, np.float32)
        self._helper_check_sitk_to_numpy_type(sitk.sitkFloat64, np.float64)
        self._helper_check_sitk_to_numpy_type(sitk.sitkComplexFloat32, np.complex64)
        self._helper_check_sitk_to_numpy_type(sitk.sitkComplexFloat64, np.complex128)
        self._helper_check_sitk_to_numpy_type(sitk.sitkVectorUInt8, np.uint8)
        self._helper_check_sitk_to_numpy_type(sitk.sitkVectorInt8, np.int8)
        self._helper_check_sitk_to_numpy_type(sitk.sitkVectorUInt16, np.uint16)
        self._helper_check_sitk_to_numpy_type(sitk.sitkVectorInt16, np.int16)
        self._helper_check_sitk_to_numpy_type(sitk.sitkVectorUInt32, np.uint32)
        self._helper_check_sitk_to_numpy_type(sitk.sitkVectorInt32, np.int32)
        if sitk.sitkVectorUInt64 != sitk.sitkUnknown:
            self._helper_check_sitk_to_numpy_type(sitk.sitkVectorUInt64, np.uint64)
        if sitk.sitkVectorInt64 != sitk.sitkUnknown:
            self._helper_check_sitk_to_numpy_type(sitk.sitkVectorInt64, np.int64)
        self._helper_check_sitk_to_numpy_type(sitk.sitkVectorFloat32, np.float32)
        self._helper_check_sitk_to_numpy_type(sitk.sitkVectorFloat64, np.float64)
        #self._helper_check_sitk_to_numpy_type(sitk.sitkLabelUInt8, np.uint8)
        #self._helper_check_sitk_to_numpy_type(sitk.sitkLabelUInt16, np.uint16)
        #self._helper_check_sitk_to_numpy_type(sitk.sitkLabelUInt32, np.uint32)
        #self._helper_check_sitk_to_numpy_type(sitk.sitkLabelUInt64, np.uint64)

    def test_to_numpy_and_back(self):
        """Test converting an image to numpy and back"""

        img = sitk.GaussianSource( sitk.sitkFloat32,  [100,100], sigma=[10]*3, mean = [50,50] )

        h = sitk.Hash( img )

        # convert the image to and fro a numpy array
        img = sitk.GetImageFromArray( sitk.GetArrayFromImage( img ) )

        self.assertEqual( h, sitk.Hash( img ))

    def test_isVector(self):
        """ Test Behavior of isVector option. """

        # Check 2D
        nda = np.arange(6, dtype=np.float32).reshape([2,3])

        img = sitk.GetImageFromArray(nda)
        self.assertEqual(img.GetSize(), nda.shape[::-1])
        self.assertEqual(img.GetPixelID(), sitk.sitkFloat32)
        self.assertEqual(img.GetPixel([1,0]), 1)

        img = sitk.GetImageFromArray(nda, isVector=False)
        self.assertEqual(img.GetSize(), nda.shape[::-1])
        self.assertEqual(img.GetPixelID(), sitk.sitkFloat32)
        self.assertEqual(img.GetPixel([1,0]), 1)

        img = sitk.GetImageFromArray(nda, isVector=True)
        self.assertEqual(img.GetSize(), nda.shape[::-1])
        self.assertEqual(img.GetPixelID(), sitk.sitkVectorFloat32)
        self.assertEqual(img.GetNumberOfComponentsPerPixel(), 1)
        self.assertEqual(img.GetPixel([1,0]), (1,))


        # Check 3D
        nda = np.arange(30, dtype=np.float32).reshape([2,3,5])

        img = sitk.GetImageFromArray(nda)
        self.assertEqual(img.GetSize(), nda.shape[::-1])
        self.assertEqual(img.GetPixelID(), sitk.sitkFloat32)
        self.assertEqual(img.GetPixel([1,0,0]), 1)
        self.assertEqual(img.GetPixel([0,1,0]), 5)

        img = sitk.GetImageFromArray(nda, isVector=False)
        self.assertEqual(img.GetSize(), nda.shape[::-1])
        self.assertEqual(img.GetPixelID(), sitk.sitkFloat32)
        self.assertEqual(img.GetPixel([1,0,0]), 1)
        self.assertEqual(img.GetPixel([0,1,0]), 5)

        img = sitk.GetImageFromArray(nda, isVector=True)
        self.assertEqual(img.GetSize(), (3,2))
        self.assertEqual(img.GetPixelID(), sitk.sitkVectorFloat32)
        self.assertEqual(img.GetNumberOfComponentsPerPixel(), 5)
        self.assertEqual(img.GetPixel([1,0,0]), (5,6,7,8,9))
        self.assertEqual(img.GetPixel([0,1,0]), (15,16,17,18,19))

        # Check 4D
        nda = np.arange(210, dtype=np.float32).reshape([3,5,7,2])

        # Special case to default to VectorImage
        img = sitk.GetImageFromArray(nda)
        self.assertEqual(img.GetSize(), (7,5,3))
        self.assertEqual(img.GetPixelID(), sitk.sitkVectorFloat32)
        self.assertEqual(img.GetNumberOfComponentsPerPixel(), 2)
        self.assertEqual(img.GetPixel([1,0,0]), (2,3))
        self.assertEqual(img.GetPixel([0,1,0]), (14,15))


        img = sitk.GetImageFromArray(nda, isVector=True)
        self.assertEqual(img.GetSize(), (7,5,3))
        self.assertEqual(img.GetPixelID(), sitk.sitkVectorFloat32)
        self.assertEqual(img.GetNumberOfComponentsPerPixel(), 2)
        self.assertEqual(img.GetPixel([1,0,0]), (2,3))
        self.assertEqual(img.GetPixel([0,1,0]), (14,15))

        # 4D Image may not be supported by SimpleITK
        try:
            sitk.Image([1]*4, sitk.sitkUInt8)
        except RuntimeError:
            return

        img = sitk.GetImageFromArray(nda, isVector=False)
        self.assertEqual(img.GetSize(), nda.shape[::-1])
        self.assertEqual(img.GetPixelID(), sitk.sitkFloat32)
        self.assertEqual(img.GetPixel([1,0,0,0]), 1)
        self.assertEqual(img.GetPixel([0,1,0,0]), 2)


        nda = np.arange(210*9, dtype=np.float32).reshape([3,5,7,9,2])

        img = sitk.GetImageFromArray(nda, isVector=True)
        self.assertEqual(img.GetSize(), nda.shape[-2::-1])
        self.assertEqual(img.GetPixelID(), sitk.sitkVectorFloat32)
        self.assertEqual(img.GetPixel([1,0,0,0]), (2,3))
        self.assertEqual(img.GetPixel([0,1,0,0]), (18,19))
        self.assertEqual(img.GetPixel([0,0,1,0]), (126,127))


    def test_complex_image_to_numpy(self):
        """Test converting back and forth between numpy and SimpleITK
        images where the SimpleITK image is of complex type."""


        # Check 2D
        img_real = sitk.GaussianSource( sitk.sitkFloat32,  [100,100], sigma=[10]*3, mean = [50,50] )
        img_imaginary = sitk.GaussianSource( sitk.sitkFloat32,  [100,100], sigma=[20]*3, mean = [10,10] )
        img = sitk.RealAndImaginaryToComplex(img_real, img_imaginary);
        h = sitk.Hash( img )

        nda = sitk.GetArrayFromImage(img)

        self.assertEqual(nda.shape, (100,100))
        self.assertEqual(nda[0,0], img.GetPixel([0,0]))
        self.assertEqual(nda[2,1], img.GetPixel([1,2]))

        img2 = sitk.GetImageFromArray( nda )
        self.assertEqual( h, sitk.Hash(img2) )
        self.assertEqual( img.GetSize(), (100,100) )

        # check 4D
        img = sitk.Image( [10, 9, 8, 7], sitk.sitkComplexFloat64 )
        h = sitk.Hash( img )

        nda = sitk.GetArrayFromImage(img)

        self.assertEqual(nda.shape, (7,8,9,10))
        self.assertEqual(nda[0,0,0,0], 0+0j)


        img2 = sitk.GetImageFromArray(nda)
        self.assertEqual(img2.GetSize(), img.GetSize())
        self.assertEqual(img2.GetNumberOfComponentsPerPixel(), img.GetNumberOfComponentsPerPixel())
        self.assertEqual(h, sitk.Hash(img2))


    def test_vector_image_to_numpy(self):
        """Test converting back and forth between numpy and SimpleITK
        images were the SimpleITK image has multiple componets and
        stored as a VectorImage."""


        # Check 2D
        img = sitk.PhysicalPointSource(sitk.sitkVectorFloat32, [3,4])
        h = sitk.Hash( img )

        nda = sitk.GetArrayFromImage(img)

        self.assertEqual(nda.shape, (4,3,2))
        self.assertEqual(nda[0,0].tolist(), [0,0])
        self.assertEqual(nda[2,1].tolist(), [1,2])
        self.assertEqual(nda[0,:,0].tolist(), [0,1,2])

        img2 = sitk.GetImageFromArray( nda, isVector=True)
        self.assertEqual( h, sitk.Hash(img2) )

        # check 3D
        img = sitk.PhysicalPointSource(sitk.sitkVectorFloat32, [3,4,5])
        h = sitk.Hash( img )

        nda = sitk.GetArrayFromImage(img)

        self.assertEqual(nda.shape, (5,4,3,3))
        self.assertEqual(nda[0,0,0].tolist(), [0,0,0])
        self.assertEqual(nda[0,0,:,0].tolist(), [0,1,2])
        self.assertEqual(nda[0,:,1,1].tolist(), [0,1,2,3])


        img2 = sitk.GetImageFromArray(nda)
        self.assertEqual(img2.GetSize(), img.GetSize())
        self.assertEqual(img2.GetNumberOfComponentsPerPixel(), img.GetNumberOfComponentsPerPixel())
        self.assertEqual(h, sitk.Hash(img2))


    def test_legacy(self):
      """Test SimpleITK Image to numpy array."""

      #     self.assertRaises(TypeError, sitk.GetArrayFromImage, 3)

      # 2D image
      image = sitk.Image(sizeX, sizeY, sitk.sitkInt32)
      for j in range(sizeY):
          for i in range(sizeX):
              image[i, j] = j*sizeX + i

      print(sitk.GetArrayFromImage(image))

      self.assertEqual( type (sitk.GetArrayFromImage(image)),  np.ndarray )

      # 3D image
      image = sitk.Image(sizeX, sizeY, sizeZ, sitk.sitkFloat32)
      for k in range(sizeZ):
          for j in range(sizeY):
              for i in range(sizeX):
                  image[i, j, k] = (sizeY*k +j)*sizeX + i

      print(sitk.GetArrayFromImage(image))

      self.assertEqual( type (sitk.GetArrayFromImage(image)),  np.ndarray )

    def test_legacy_array2sitk(self):
      """Test numpy array to SimpleITK Image."""

      arr = np.arange(20, dtype=np.float64)
      arr.shape = (sizeY, sizeX)

      image = sitk.GetImageFromArray(arr)
      self.assertEqual(image.GetSize(), (sizeX, sizeY))
      self.assertEqual(image[0,0], 0.0)
      self.assertEqual(image[1,1], 5.0)
      self.assertEqual(image[2,2], 10.0)

      arr = np.arange(60, dtype=np.int16)
      arr.shape = (sizeZ, sizeY, sizeX)

      image = sitk.GetImageFromArray(arr)

      self.assertEqual(image.GetSize(), (sizeX, sizeY, sizeZ))
      self.assertEqual(image[0,0,0], 0)
      self.assertEqual(image[1,1,1], 25)
      self.assertEqual(image[2,2,2], 50)

if __name__ == '__main__':
    unittest.main()
