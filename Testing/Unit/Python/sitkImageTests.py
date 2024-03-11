# ==========================================================================
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
# ==========================================================================*/

import unittest

import SimpleITK as sitk
import sys
import tempfile
import os.path
import shutil


class ImageTests(unittest.TestCase):
    """Tests for the Python interface for the Image class"""

    def setUp(self):
        super(ImageTests, self).setUp()
        self.addTypeEqualityFunc(sitk.Image, self.assertImageEqual)
        self.test_dir = tempfile.mkdtemp()

    def tearDown(self):
        shutil.rmtree(self.test_dir)

    def assertImageEqual(self, img1, img2, msg=None):
        """utility to compare two images"""
        self.assertEqual(img1.GetPixelID(), img2.GetPixelID())
        self.assertEqual(img1.GetOrigin(), img2.GetOrigin())
        self.assertEqual(img1.GetSpacing(), img2.GetSpacing())
        self.assertEqual(img1.GetDirection(), img2.GetDirection())

        self.assertEqual(img1.GetMetaDataKeys(), img2.GetMetaDataKeys())

        for k in img1.GetMetaDataKeys():
            self.assertEqual(img1.GetMetaData(k), img2.GetMetaData(k))

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

    def test_get_item_metadata(self):
        """Test the __getitem__ with a string to access meta-data dictionary"""

        img = sitk.Image([10, 9, 11], sitk.sitkFloat32)
        img.SetSpacing([0.3, 0.1, 0.2])
        img.SetOrigin([-3.0, -2.0, -1.0])

        self.assertEqual(img["spacing"], (0.3, 0.1, 0.2))
        self.assertEqual(img["origin"], (-3.0, -2.0, -1.0))
        self.assertEqual(
            img["direction"], (1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0)
        )

        with self.assertRaises(KeyError):
            img[""]

        with self.assertRaises(KeyError):
            img["does_not_exit"]

    def test_setitem_metadata(self):
        """Test the __setitem__ with a string to access meta-data dictionary"""

        img = sitk.Image([10, 9], sitk.sitkFloat32)

        img["spacing"] = [0.3, 0.1, 0.2]
        self.assertEqual(img["spacing"], (0.3, 0.1))
        self.assertEqual(img.GetSpacing(), (0.3, 0.1))

        img["origin"] = [-3.0, -2.0, -1.0]
        self.assertEqual(img["origin"], (-3.0, -2.0))
        self.assertEqual(img.GetOrigin(), (-3.0, -2.0))

        with self.assertRaises(RuntimeError):
            img["direction"] = (-1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0)

        img["direction"] = (-1.0, 0.0, 0.0, 1.0)
        self.assertEqual(img["direction"], (-1.0, 0.0, 0.0, 1.0))
        self.assertEqual(img.GetDirection(), (-1.0, 0.0, 0.0, 1.0))

        with self.assertRaises(TypeError):
            img["test"] = 1

    def test_delitem_metadata(self):
        """Test the __delitem__ with a string key to remove elements from meta-data"""

        img = sitk.Image([10, 9], sitk.sitkFloat32)

        for k in ["origin", "spacing", "direction"]:
            with self.assertRaises(KeyError):
                del img[k]

        for k in [1.0, [1, 2], (3, 4)]:
            with self.assertRaises(TypeError):
                k in img

    def test_contains_metadata(self):
        """Test the __contains__ with a string key"""

        img = sitk.Image([10, 9], sitk.sitkFloat32)

        for k in ["origin", "spacing", "direction"]:
            self.assertTrue(k in img)

        for k in [1.0, [1, 2], (3, 4)]:
            with self.assertRaises(TypeError):
                k in img

    def test_pickle_file(self):
        """Test the custom pickling and un-pickling interface"""

        try:
            import pickle5 as pickle
        except ImportError:
            import pickle

        import copy

        # test the default protocol
        img = sitk.Image([10, 9, 11], sitk.sitkFloat32)
        img = sitk.AdditiveGaussianNoise(img)

        fname = os.path.join(self.test_dir, "image_protocol_default.pickle")
        with open(fname, "wb") as fp:
            p = pickle.dump(copy.deepcopy(img), fp)

        with open(fname, "rb") as fp:
            ret = pickle.load(fp)

        self.assertEqual(img, ret, msg="pickle file with default protocol")

        # test all available protocols
        for prot in reversed(range(1, pickle.HIGHEST_PROTOCOL + 1)):
            fname = os.path.join(
                self.test_dir, "image_protocol_{0}.pickle".format(prot)
            )

            print("Testing pickle protocol {0}.".format(fname))
            with open(fname, "wb") as fp:
                pickle.dump(copy.deepcopy(img), fp, protocol=prot)

            with open(fname, "rb") as fp:
                ret = pickle.load(fp)

            self.assertEqual(img, ret, msg="pickle file with {0}".format(fname))

    def test_pickle(self):
        """Test the custom pickling and un-pickling interface"""

        try:
            import pickle5 as pickle
        except ImportError:
            import pickle

        import copy

        # test the default protocol
        img = sitk.Image([10, 9, 11], sitk.sitkFloat32)
        img = sitk.AdditiveGaussianNoise(img)

        p = pickle.dumps(copy.deepcopy(img))
        ret = pickle.loads(p)

        self.assertEqual(img, ret, msg="pickle with default protocol")

        # test all available protocols
        for prot in reversed(range(1, pickle.HIGHEST_PROTOCOL + 1)):
            print("Testing pickle protocol {0}.".format(prot))
            p = pickle.dumps(copy.deepcopy(img), protocol=prot)
            ret = pickle.loads(p)
            self.assertEqual(img, ret, msg="pickle with {0} protocol".format(prot))

    def test_iterable(self):
        """Test that the Image object is iterable"""

        # create image filled with zeros
        image = sitk.Image(10, 10, sitk.sitkInt32)

        image[9, 9] = 10

        self.assertEqual(sum(image), 10)

    def test_set_get_pixel(self):
        """Test methods for setting and getting pixel"""

        # create image filled with zeros
        image = sitk.Image(10, 10, sitk.sitkInt32)

        image.SetPixel(0, 0, 1)
        image[[0, 1]] = 2
        image[9, 9] = 3
        image.SetPixel([0, 2], 4)

        self.assertEqual(image.GetPixel(1, 1), 0)
        self.assertEqual(image.GetPixel([0, 2]), 4)

        self.assertEqual(image[0, 1], 2)
        self.assertEqual(image[[9, 9]], 3)

        self.assertEqual(len(image), 100)

    def test_inplace_operators(self):
        """Test in place operators with images"""

        image1 = sitk.Image([2, 2], sitk.sitkFloat64)
        image2 = image1 + 1.0
        image1["test"] = "value"

        self.assertEqual(image1[1, 1], 0.0)
        self.assertEqual(image2[1, 1], 1.0)
        self.assertEqual(image1["test"], "value")

        image1 += image2
        self.assertEqual(image1[1, 1], 1.0)
        self.assertEqual(image1["test"], "value")

        image1 *= image2 + 5.5
        self.assertEqual(image1[0, 0], 6.5)
        self.assertEqual(image1["test"], "value")

        image1 -= image2
        self.assertEqual(image1[0, 0], 5.5)
        self.assertEqual(image1["test"], "value")

        image1 /= image2 * 2.0
        self.assertEqual(image1[0, 0], 2.75)
        self.assertEqual(image1["test"], "value")

        image1 //= image2 * 2.0
        self.assertEqual(image1[0, 0], 1.0)
        self.assertEqual(image1["test"], "value")

        image1 **= image2
        self.assertEqual(image1[0, 0], 1.0)
        self.assertEqual(image1["test"], "value")

        image1 = sitk.Image([3, 3], sitk.sitkUInt32)
        image2 = sitk.Image([3, 3], sitk.sitkUInt32)
        image1["test"] = "value"

        image1 += image2 + 0b10001110101
        self.assertEqual(image1[1, 1], 1141)
        self.assertEqual(image1["test"], "value")

        image1 &= image2 + 0b11111111011
        self.assertEqual(image1[1, 1], 1137)
        self.assertEqual(image1["test"], "value")

        image1 |= image2 + 0b00000000111
        self.assertEqual(image1[1, 1], 1143)
        self.assertEqual(image1["test"], "value")

        image1 ^= image2 + 0b00000001101
        self.assertEqual(image1[1, 1], 1146)
        self.assertEqual(image1["test"], "value")

        image1 %= image2 + 4
        self.assertEqual(image1[1, 1], 2)
        self.assertEqual(image1["test"], "value")

    def test_inplace_operators_exception(self):
        """Test exception generated during inplace operation"""

        size = [1, 1]
        img = sitk.Image(size, sitk.sitkUInt32)
        img["test"] = "1"
        try:
            img += sitk.Cast(img, sitk.sitkFloat32)
        except RuntimeError:
            pass
        else:
            assert False  # Failed to throw exception

        # Check the image and meta-data dictionary are the sane.
        self.assertEqual(img.GetSize(), tuple(size))
        self.assertTrue("test" in img)
        self.assertEqual(img["test"], "1")

    def test_inplace_operators_constants(self):
        """Test in place operators with numeric constants"""

        image = sitk.Image([2, 2], sitk.sitkFloat64)
        image["test"] = "value"

        self.assertEqual(image[0, 0], 0.0)
        self.assertEqual(image["test"], "value")

        image += 3.125
        self.assertEqual(image[0, 0], 3.125)
        self.assertEqual(image["test"], "value")

        image *= 2.0
        self.assertEqual(image[0, 0], 6.25)
        self.assertEqual(image["test"], "value")

        image -= 4.0
        self.assertEqual(image[0, 0], 2.25)
        self.assertEqual(image["test"], "value")

        image /= 0.25
        self.assertEqual(image[0, 0], 9.0)
        self.assertEqual(image["test"], "value")

        image //= 2.2
        self.assertEqual(image[0, 0], 4.0)
        self.assertEqual(image["test"], "value")

        image **= 2.0
        self.assertEqual(image[0, 0], 16.0)
        self.assertEqual(image["test"], "value")

        image = sitk.Image([3, 3], sitk.sitkUInt32)
        image["test"] = "value"

        image += 0b10001110101
        self.assertEqual(image[1, 1], 1141)
        self.assertEqual(image["test"], "value")

        image &= 0b11111111011
        self.assertEqual(image[1, 1], 1137)
        self.assertEqual(image["test"], "value")

        image |= 0b00000000111
        self.assertEqual(image[1, 1], 1143)
        self.assertEqual(image["test"], "value")

        image ^= 0b00000001101
        self.assertEqual(image[1, 1], 1146)
        self.assertEqual(image["test"], "value")

        image %= 4
        self.assertEqual(image[1, 1], 2)
        self.assertEqual(image["test"], "value")

    def test_evaluate_at_continuous_index(self):
        """Test for EvaluateAtContinuousIndex"""

        for pixel_type in (
            sitk.sitkFloat32,
            sitk.sitkFloat64,
            sitk.sitkUInt8,
            sitk.sitkInt8,
            sitk.sitkUInt16,
            sitk.sitkInt16,
            sitk.sitkUInt32,
            sitk.sitkInt32,
            sitk.sitkUInt64,
            sitk.sitkInt64,
        ):
            image = sitk.Image([2, 2], pixel_type)
            result = image.EvaluateAtContinuousIndex([0.5, 0.5])
            self.assertEqual(result, 0.0)
            self.assertEqual(type(result), float)

        for pixel_type in (sitk.sitkComplexFloat32, sitk.sitkComplexFloat64):
            image = sitk.Image([2, 2], pixel_type)
            result = image.EvaluateAtContinuousIndex([0.5, 0.5])
            self.assertEqual(result, complex(0.0, 0.0))
            self.assertEqual(type(result), complex)

        for pixel_type in (
            sitk.sitkVectorFloat32,
            sitk.sitkVectorFloat64,
            sitk.sitkVectorUInt8,
            sitk.sitkVectorInt8,
            sitk.sitkVectorUInt16,
            sitk.sitkVectorInt16,
            sitk.sitkVectorUInt32,
            sitk.sitkVectorInt32,
            sitk.sitkVectorUInt64,
            sitk.sitkVectorInt64,
        ):
            image = sitk.Image([2, 2], pixel_type, 7)
            result = image.EvaluateAtContinuousIndex([0.5, 0.5])
            self.assertEqual(len(result), 7)
            self.assertTrue(all(i == 0 for i in result))

    def test_evaluate_at_physical_point(self):
        """Test for EvaluateAtPhysicalPoint"""

        for pixel_type in (
            sitk.sitkFloat32,
            sitk.sitkFloat64,
            sitk.sitkUInt8,
            sitk.sitkInt8,
            sitk.sitkUInt16,
            sitk.sitkInt16,
            sitk.sitkUInt32,
            sitk.sitkInt32,
            sitk.sitkUInt64,
            sitk.sitkInt64,
        ):
            image = sitk.Image([2, 2], pixel_type)
            result = image.EvaluateAtPhysicalPoint([0.5, 0.5])
            self.assertEqual(result, 0.0)
            self.assertEqual(type(result), float)

        for pixel_type in (sitk.sitkComplexFloat32, sitk.sitkComplexFloat64):
            image = sitk.Image([2, 2], pixel_type)
            result = image.EvaluateAtPhysicalPoint([0.5, 0.5])
            self.assertEqual(result, complex(0.0, 0.0))
            self.assertEqual(type(result), complex)

        for pixel_type in (
            sitk.sitkVectorFloat32,
            sitk.sitkVectorFloat64,
            sitk.sitkVectorUInt8,
            sitk.sitkVectorInt8,
            sitk.sitkVectorUInt16,
            sitk.sitkVectorInt16,
            sitk.sitkVectorUInt32,
            sitk.sitkVectorInt32,
            sitk.sitkVectorUInt64,
            sitk.sitkVectorInt64,
        ):
            image = sitk.Image([2, 2], pixel_type, 7)
            result = image.EvaluateAtPhysicalPoint([0.5, 0.5])
            self.assertEqual(len(result), 7)
            self.assertTrue(all(i == 0 for i in result))

    def test_masked_assign(self):

        mask_image = sitk.Image([2, 2], sitk.sitkUInt8)
        mask_image[0, 1] = 1
        mask_image[1, 0] = 2
        for pixel_type in (
            sitk.sitkFloat32,
            sitk.sitkFloat64,
            sitk.sitkUInt8,
            sitk.sitkInt8,
            sitk.sitkUInt16,
            sitk.sitkInt16,
            sitk.sitkUInt32,
            sitk.sitkInt32,
            sitk.sitkUInt64,
            sitk.sitkInt64,
        ):
            image = sitk.Image([2, 2], pixel_type)
            image["test"] = "value"

            image2 = sitk.Image([2, 2], pixel_type)
            image2 += 2

            image[mask_image] = image2
            self.assertEqual(image[0, 0], 0)
            self.assertEqual(image[1, 0], 2)
            self.assertEqual(image[0, 1], 2)
            self.assertEqual(image[1, 1], 0)
            self.assertEqual(image["test"], "value")

        for pixel_type in (sitk.sitkComplexFloat32, sitk.sitkComplexFloat64):
            image = sitk.Image([2, 2], pixel_type)
            image["test"] = "value"

            image2 = sitk.Image([2, 2], pixel_type)
            image2 -= 1
            image[mask_image] = image2

            self.assertEqual(image[0, 0], 0)
            self.assertEqual(image[1, 0], complex(-1, 0))
            self.assertEqual(image[0, 1], complex(-1, 0))
            self.assertEqual(image[1, 1], 0)
            self.assertEqual(image["test"], "value")

        for pixel_type in (
            sitk.sitkVectorFloat32,
            sitk.sitkVectorFloat64,
            sitk.sitkVectorUInt8,
            sitk.sitkVectorInt8,
            sitk.sitkVectorUInt16,
            sitk.sitkVectorInt16,
            sitk.sitkVectorUInt32,
            sitk.sitkVectorInt32,
            sitk.sitkVectorUInt64,
            sitk.sitkVectorInt64,
        ):
            image = sitk.Image([2, 2], pixel_type, 4)
            image["test"] = "value"

            image2 = sitk.Image([2, 2], pixel_type, 4)
            image2 += 2

            image[mask_image] = image2

            self.assertTrue(all(i == 0 for i in image[0, 0]))
            self.assertTrue(all(i == 2 for i in image[1, 0]), image[1, 0])
            self.assertTrue(all(i == 2 for i in image[0, 1]))
            self.assertTrue(all(i == 0 for i in image[1, 1]))
            self.assertEqual(image["test"], "value")

    def test_masked_assign_constant(self):

        mask_image = sitk.Image([2, 2], sitk.sitkUInt8)
        mask_image[0, 1] = 1
        mask_image[1, 0] = 2
        for pixel_type in (
            sitk.sitkFloat32,
            sitk.sitkFloat64,
            sitk.sitkUInt8,
            sitk.sitkInt8,
            sitk.sitkUInt16,
            sitk.sitkInt16,
            sitk.sitkUInt32,
            sitk.sitkInt32,
            sitk.sitkUInt64,
            sitk.sitkInt64,
        ):
            image = sitk.Image([2, 2], pixel_type)
            image["test"] = "value"

            image[mask_image] = 2
            self.assertEqual(image[0, 0], 0)
            self.assertEqual(image[1, 0], 2)
            self.assertEqual(image[0, 1], 2)
            self.assertEqual(image[1, 1], 0)
            self.assertEqual(image["test"], "value")

        for pixel_type in (
            sitk.sitkVectorFloat32,
            sitk.sitkVectorFloat64,
            sitk.sitkVectorUInt8,
            sitk.sitkVectorInt8,
            sitk.sitkVectorUInt16,
            sitk.sitkVectorInt16,
            sitk.sitkVectorUInt32,
            sitk.sitkVectorInt32,
            sitk.sitkVectorUInt64,
            sitk.sitkVectorInt64,
        ):
            image = sitk.Image([2, 2], pixel_type)
            image["test"] = "value"

            image[mask_image] = 2
            self.assertTrue(all(i == 0 for i in image[0, 0]))
            self.assertTrue(all(i == 2 for i in image[1, 0]), image[1, 0])
            self.assertTrue(all(i == 2 for i in image[0, 1]))
            self.assertTrue(all(i == 0 for i in image[1, 1]))
            self.assertEqual(image["test"], "value")

    def test_legacy(self):
        """This is old testing cruft before unittest"""

        image = sitk.Image(10, 10, sitk.sitkInt32)

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
        self.assertEqual(image.GetPixel(1, 1), 0)

        image *= image
        self.assertEqual(image.GetPixel(1, 1), 0)

        # True division will results in "nan" while
        image /= image
        image //= image

        image = image * 0


if __name__ == "__main__":
    unittest.main()
