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

import pytest
import SimpleITK as sitk
import sys
import tempfile
import os.path
import shutil
import copy

try:
    import pickle5 as pickle
except ImportError:
    import pickle


def assert_image_equal(img1, img2, msg=None):
    """utility to compare two images"""
    assert img1.GetPixelID() == img2.GetPixelID()
    assert img1.GetOrigin() == img2.GetOrigin()
    assert img1.GetSpacing() == img2.GetSpacing()
    assert img1.GetDirection() == img2.GetDirection()
    assert img1.GetMetaDataKeys() == img2.GetMetaDataKeys()

    for k in img1.GetMetaDataKeys():
        assert img1.GetMetaData(k) == img2.GetMetaData(k)

    assert sitk.Hash(img1) == sitk.Hash(img2)


@pytest.fixture
def test_dir():
    temp_dir = tempfile.mkdtemp()
    yield temp_dir
    shutil.rmtree(temp_dir)


def test_deepcopy():
    """Test the custom __deepcopy__ method"""
    sz = [10, 10]
    img = sitk.Image(sz, sitk.sitkFloat32)
    img[1, 2] = 3.14
    img.SetSpacing([1.2, 3.4])

    img_dc = copy.deepcopy(img)
    assert_image_equal(img, img_dc)

    img_dc.SetOrigin([7, 8])
    assert img.GetOrigin() != img_dc.GetOrigin()

    img_dc.SetOrigin(img.GetOrigin())
    img_dc[9, 9] = 1.234
    assert sitk.Hash(img) != sitk.Hash(img_dc)

    img_c = copy.copy(img)
    assert_image_equal(img, img_c)

    img_c.SetOrigin([7, 8])
    assert img.GetOrigin() != img_c.GetOrigin()


def test_get_item_metadata():
    """Test the __getitem__ with a string to access meta-data dictionary"""

    img = sitk.Image([10, 9, 11], sitk.sitkFloat32)
    img.SetSpacing([0.3, 0.1, 0.2])
    img.SetOrigin([-3.0, -2.0, -1.0])

    assert img["spacing"] == (0.3, 0.1, 0.2)
    assert img["origin"] == (-3.0, -2.0, -1.0)
    assert img["direction"] == (1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0)

    with pytest.raises(KeyError):
        img[""]

    with pytest.raises(KeyError):
        img["does_not_exit"]


def test_setitem_metadata():
    """Test the __setitem__ with a string to access meta-data dictionary"""

    img = sitk.Image([10, 9], sitk.sitkFloat32)

    img["spacing"] = [0.3, 0.1, 0.2]
    assert img["spacing"] == (0.3, 0.1)
    assert img.GetSpacing() == (0.3, 0.1)

    img["origin"] = [-3.0, -2.0, -1.0]
    assert img["origin"] == (-3.0, -2.0)
    assert img.GetOrigin() == (-3.0, -2.0)

    with pytest.raises(RuntimeError):
        img["direction"] = (-1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0)

    img["direction"] = (-1.0, 0.0, 0.0, 1.0)
    assert img["direction"] == (-1.0, 0.0, 0.0, 1.0)
    assert img.GetDirection() == (-1.0, 0.0, 0.0, 1.0)

    with pytest.raises(TypeError):
        img["test"] = 1


def test_delitem_metadata():
    """Test the __delitem__ with a string key to remove elements from meta-data"""
    img = sitk.Image([10, 9], sitk.sitkFloat32)

    for k in ["origin", "spacing", "direction"]:
        with pytest.raises(KeyError):
            del img[k]

    for k in [1.0, [1, 2], (3, 4)]:
        with pytest.raises(TypeError):
            k in img


def test_contains_metadata():
    """Test the __contains__ with a string key"""
    img = sitk.Image([10, 9], sitk.sitkFloat32)

    for k in ["origin", "spacing", "direction"]:
        assert k in img

    for k in [1.0, [1, 2], (3, 4)]:
        with pytest.raises(TypeError):
            k in img


def test_pickle_file(test_dir):
    """Test the custom pickling and un-pickling interface"""
    img = sitk.Image([10, 9, 11], sitk.sitkFloat32)
    img = sitk.AdditiveGaussianNoise(img)

    # test the default protocol
    fname = os.path.join(test_dir, "image_protocol_default.pickle")
    with open(fname, "wb") as fp:
        pickle.dump(copy.deepcopy(img), fp)

    with open(fname, "rb") as fp:
        ret = pickle.load(fp)

    assert_image_equal(img, ret)

    # test all available protocols
    for prot in reversed(range(1, pickle.HIGHEST_PROTOCOL + 1)):
        fname = os.path.join(test_dir, f"image_protocol_{prot}.pickle")
        print(f"Testing pickle protocol {fname}.")

        with open(fname, "wb") as fp:
            pickle.dump(copy.deepcopy(img), fp, protocol=prot)

        with open(fname, "rb") as fp:
            ret = pickle.load(fp)

        assert_image_equal(img, ret)


def test_pickle():
    """Test the custom pickling and un-pickling interface"""
    img = sitk.Image([10, 9, 11], sitk.sitkFloat32)
    img = sitk.AdditiveGaussianNoise(img)

    p = pickle.dumps(copy.deepcopy(img))
    ret = pickle.loads(p)
    assert_image_equal(img, ret)

    # test all available protocols
    for prot in reversed(range(1, pickle.HIGHEST_PROTOCOL + 1)):
        print(f"Testing pickle protocol {prot}.")
        p = pickle.dumps(copy.deepcopy(img), protocol=prot)
        ret = pickle.loads(p)
        assert_image_equal(img, ret)


def test_iterable():
    """Test that the Image object is iterable"""
    image = sitk.Image(10, 10, sitk.sitkInt32)
    image[9, 9] = 10
    assert sum(image) == 10


def test_set_get_pixel():
    """Test methods for setting and getting pixel"""
    image = sitk.Image(10, 10, sitk.sitkInt32)

    image.SetPixel(0, 0, 1)
    image[[0, 1]] = 2
    image[9, 9] = 3
    image.SetPixel([0, 2], 4)

    assert image.GetPixel(1, 1) == 0
    assert image.GetPixel([0, 2]) == 4
    assert image[0, 1] == 2
    assert image[[9, 9]] == 3
    assert len(image) == 100


def test_inplace_operators():
    """Test in place operators with images"""
    image1 = sitk.Image([2, 2], sitk.sitkFloat64)
    image2 = image1 + 1.0
    image1["test"] = "value"

    assert image1[1, 1] == 0.0
    assert image2[1, 1] == 1.0
    assert image1["test"] == "value"

    image1 += image2
    assert image1[1, 1] == 1.0
    assert image1["test"] == "value"

    image1 *= image2 + 5.5
    assert image1[0, 0] == 6.5
    assert image1["test"] == "value"

    image1 -= image2
    assert image1[0, 0] == 5.5
    assert image1["test"] == "value"

    image1 /= image2 * 2.0
    assert image1[0, 0] == 2.75
    assert image1["test"] == "value"

    image1 //= image2 * 2.0
    assert image1[0, 0] == 1.0
    assert image1["test"] == "value"

    image1 **= image2
    assert image1[0, 0] == 1.0
    assert image1["test"] == "value"

    # Test binary operations
    image1 = sitk.Image([3, 3], sitk.sitkUInt32)
    image2 = sitk.Image([3, 3], sitk.sitkUInt32)
    image1["test"] = "value"

    image1 += image2 + 0b10001110101
    assert image1[1, 1] == 1141
    assert image1["test"] == "value"

    image1 &= image2 + 0b11111111011
    assert image1[1, 1] == 1137
    assert image1["test"] == "value"

    image1 |= image2 + 0b00000000111
    assert image1[1, 1] == 1143
    assert image1["test"] == "value"

    image1 ^= image2 + 0b00000001101
    assert image1[1, 1] == 1146
    assert image1["test"] == "value"

    image1 %= image2 + 4
    assert image1[1, 1] == 2
    assert image1["test"] == "value"


def test_inplace_operators_exception():
    """Test exception generated during inplace operation"""
    size = [1, 1]
    img = sitk.Image(size, sitk.sitkUInt32)
    img["test"] = "1"

    with pytest.raises(RuntimeError):
        img += sitk.Cast(img, sitk.sitkFloat32)

    # Check the image and meta-data dictionary are the same
    assert img.GetSize() == tuple(size)
    assert "test" in img
    assert img["test"] == "1"


def test_inplace_operators_constants():
    """Test in place operators with numeric constants"""
    image = sitk.Image([2, 2], sitk.sitkFloat64)
    image["test"] = "value"

    assert image[0, 0] == 0.0
    assert image["test"] == "value"

    image += 3.125
    assert image[0, 0] == 3.125
    assert image["test"] == "value"

    image *= 2.0
    assert image[0, 0] == 6.25
    assert image["test"] == "value"

    image -= 4.0
    assert image[0, 0] == 2.25
    assert image["test"] == "value"

    image /= 0.25
    assert image[0, 0] == 9.0
    assert image["test"] == "value"

    image //= 2.2
    assert image[0, 0] == 4.0
    assert image["test"] == "value"

    image **= 2.0
    assert image[0, 0] == 16.0
    assert image["test"] == "value"

    # Test binary operations
    image = sitk.Image([3, 3], sitk.sitkUInt32)
    image["test"] = "value"

    image += 0b10001110101
    assert image[1, 1] == 1141
    assert image["test"] == "value"

    image &= 0b11111111011
    assert image[1, 1] == 1137
    assert image["test"] == "value"

    image |= 0b00000000111
    assert image[1, 1] == 1143
    assert image["test"] == "value"

    image ^= 0b00000001101
    assert image[1, 1] == 1146
    assert image["test"] == "value"

    image %= 4
    assert image[1, 1] == 2
    assert image["test"] == "value"


def test_evaluate_at_continuous_index():
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
        assert result == 0.0
        assert type(result) == float

    for pixel_type in (sitk.sitkComplexFloat32, sitk.sitkComplexFloat64):
        image = sitk.Image([2, 2], pixel_type)
        result = image.EvaluateAtContinuousIndex([0.5, 0.5])
        assert result == complex(0.0, 0.0)
        assert type(result) == complex

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
        assert len(result) == 7
        assert all(i == 0 for i in result)


def test_evaluate_at_physical_point():
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
        assert result == 0.0
        assert type(result) == float

    for pixel_type in (sitk.sitkComplexFloat32, sitk.sitkComplexFloat64):
        image = sitk.Image([2, 2], pixel_type)
        result = image.EvaluateAtPhysicalPoint([0.5, 0.5])
        assert result == complex(0.0, 0.0)
        assert type(result) == complex

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
        assert len(result) == 7
        assert all(i == 0 for i in result)


def test_masked_assign():

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
        assert image[0, 0] == 0
        assert image[1, 0] == 2
        assert image[0, 1] == 2
        assert image[1, 1] == 0
        assert image["test"] == "value"

    for pixel_type in (sitk.sitkComplexFloat32, sitk.sitkComplexFloat64):
        image = sitk.Image([2, 2], pixel_type)
        image["test"] = "value"

        image2 = sitk.Image([2, 2], pixel_type)
        image2 -= 1
        image[mask_image] = image2

        assert image[0, 0] == 0
        assert image[1, 0] == complex(-1, 0)
        assert image[0, 1] == complex(-1, 0)
        assert image[1, 1] == 0
        assert image["test"] == "value"

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

        assert all(i == 0 for i in image[0, 0])
        assert all(i == 2 for i in image[1, 0])
        assert all(i == 2 for i in image[0, 1])
        assert all(i == 0 for i in image[1, 1])
        assert image["test"] == "value"


def test_masked_assign_constant():

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
        assert image[0, 0] == 0
        assert image[1, 0] == 2
        assert image[0, 1] == 2
        assert image[1, 1] == 0
        assert image["test"] == "value"

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
        assert all(i == 0 for i in image[0, 0])
        assert all(i == 2 for i in image[1, 0])
        assert all(i == 2 for i in image[0, 1])
        assert all(i == 0 for i in image[1, 1])
        assert image["test"] == "value"


def test_legacy():
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
    assert image.GetPixel(1, 1) == 0

    image *= image
    assert image.GetPixel(1, 1) == 0

    # True division will results in "nan" while
    image /= image
    image //= image

    image = image * 0
