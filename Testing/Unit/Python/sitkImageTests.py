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
import unittest

import SimpleITK as sitk
import sys


class ImageTests(unittest.TestCase):
    """These tests are suppose to test the python interface to the sitk::Image"""

    def setUp(self):
        super(ImageTests, self).setUp()
        self.addTypeEqualityFunc(sitk.Image, self.assertImageEqual)

    def assertImageEqual(self, img1, img2, msg=None):
        """ utility to compare two images"""
        self.assertEqual(img1.GetPixelID(), img2.GetPixelID())
        self.assertEqual(img1.GetOrigin(), img2.GetOrigin())
        self.assertEqual(img1.GetSpacing(), img2.GetSpacing())
        self.assertEqual(img1.GetDirection(), img2.GetDirection())

        self.assertEqual(img1.GetMetaDataKeys(), img2.GetMetaDataKeys())

        for k in img1.GetMetaDataKeys():
            aself.assertEqual(img1.GetMetaData(k), img2.GetMetaData(k))

        self.assertEqual(sitk.Hash(img1), sitk.Hash(img2))

    def test_deepcopy(self):
        """Test the custom __deepcopy__ method"""

        import copy

        sz = [10, 10]
        img = sitk.Image(sz, sitk.sitkFloat32)
        img[1, 2] = 3.14
        img.SetSpacing([1.2, 3.4])

        img_dc = copy.deepcopy(img)

        self.assertEqual(img, img_dc)

        img_dc.SetOrigin([7, 8])
        self.assertNotEqual(img.GetOrigin(), img_dc.GetOrigin())

        img_dc.SetOrigin(img.GetOrigin())

        img_dc[9, 9] = 1.234
        self.assertNotEqual(sitk.Hash(img), sitk.Hash(img_dc))

        img_c = copy.copy(img)
        self.assertEqual(img, img_c)

        img_c.SetOrigin([7, 8])
        self.assertNotEqual(img.GetOrigin(), img_c.GetOrigin())


    def test_iterable(self):
        """Test that the Image object is iterable"""

         # create image filled with zeros
        image = sitk.Image( 10, 10, sitk.sitkInt32 )

        image[9,9] = 10;

        self.assertEqual(sum( image ), 10)

    def test_set_get_pixel(self):
        """Test methods for setting and getting pixel"""

        # create image filled with zeros
        image = sitk.Image( 10, 10, sitk.sitkInt32 )

        image.SetPixel( 0, 0, 1 )
        image[ [0,1] ]  = 2
        image[ 9,9 ]  = 3
        image.SetPixel( [0, 2], 4 )

        self.assertEqual(image.GetPixel(1,1), 0 )
        self.assertEqual(image.GetPixel([0,2]), 4 )

        self.assertEqual(image[0,1], 2)
        self.assertEqual(image[[ 9,9 ]], 3)



        self.assertEqual(len( image ), 100)


    def test_legacy(self):
        """ This is old testing cruft before tehe unittest enlightenment """

        image = sitk.Image( 10, 10, sitk.sitkInt32 )

        image + image
        image + 1
        1 + image
        image - image
        image - 1
        1 - image
        image * image
        image * 1
        1 * image
        image / image
        1.0 / image
        image / 1.0
        image // image
        image // 1
        1 // image
        image & image
        image | image
        image ^ image
        ~image

        image += image
        image -= image
        self.assertEqual(image.GetPixel(1,1), 0 )

        image *= image
        self.assertEqual(image.GetPixel(1,1), 0 )


        # True division will results in "nan" while
        image /= image
        image //= image

        image = image * 0


if __name__ == '__main__':
    unittest.main()
