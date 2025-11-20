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

import timeit
import pytest
import numpy as np
import SimpleITK as sitk
import SimpleITK._pixel_types as pixel_types

# Test dimensions
sizeX = 4
sizeY = 5
sizeZ = 3


def check_sitk_to_numpy_type(sitkType: int, numpyType: np.dtype) -> None:
    """Helper to check SimpleITK to NumPy type conversion via array view.

    Args:
        sitkType: SimpleITK pixel type (e.g., sitk.sitkUInt8)
        numpyType: Expected NumPy dtype
    """
    if sitkType == sitk.sitkUnknown:
        pytest.skip("Unknown SimpleITK type")

    image = sitk.Image((9, 10), sitkType, 1)
    a = sitk.GetArrayViewFromImage(image)
    assert numpyType == a.dtype, f"Expected numpy type {numpyType}, got {a.dtype}"
    if pixel_types.is_vector(sitkType):
        assert (10, 9, 1) == a.shape, f"Expected shape (10, 9, 1), got {a.shape}"
    else:
        assert (10, 9) == a.shape, f"Expected shape (10, 9), got {a.shape}"


@pytest.mark.parametrize(
    "sitk_type,numpy_type",
    [
        (sitk.sitkUInt8, np.uint8),
        (sitk.sitkUInt16, np.uint16),
        (sitk.sitkUInt32, np.uint32),
        (sitk.sitkUInt64, np.uint64),
        (sitk.sitkInt8, np.int8),
        (sitk.sitkInt16, np.int16),
        (sitk.sitkInt32, np.int32),
        (sitk.sitkInt64, np.int64),
        (sitk.sitkFloat32, np.float32),
        (sitk.sitkFloat64, np.float64),
        (sitk.sitkVectorUInt8, np.uint8),
        (sitk.sitkVectorInt8, np.int8),
        (sitk.sitkVectorUInt16, np.uint16),
        (sitk.sitkVectorInt16, np.int16),
        (sitk.sitkVectorUInt32, np.uint32),
        (sitk.sitkVectorInt32, np.int32),
        (sitk.sitkVectorUInt64, np.uint64),
        (sitk.sitkVectorInt64, np.int64),
        (sitk.sitkVectorFloat32, np.float32),
        (sitk.sitkVectorFloat64, np.float64),
    ],
)
def test_type_to_numpy(sitk_type, numpy_type):
    """Test conversion of all SimpleITK pixel types to NumPy array view"""
    check_sitk_to_numpy_type(sitk_type, numpy_type)


def test_to_numpy_and_back():
    """Test converting an image to NumPy array view and back

    This test verifies that:
    1. An image can be converted to a NumPy array view
    2. The array view can be converted back to an image
    3. The resulting image matches the original
    """
    img = sitk.GaussianSource(
        sitk.sitkFloat32, [100, 100], sigma=[10] * 3, mean=[50, 50]
    )
    original_hash = sitk.Hash(img)

    # Convert to array view and back
    img2 = sitk.GetImageFromArray(sitk.GetArrayViewFromImage(img))
    assert (
        original_hash == sitk.Hash(img2)
    ), "Image hash changed after array view conversion"


@pytest.mark.parametrize(
    "dims,expected_shape,test_points",
    [
        # 2D vector image
        ([3, 4], (4, 3, 2), [((0, 0), [0, 0]), ((2, 1), [1, 2])]),
        # 3D vector image
        ([3, 4, 5], (5, 4, 3, 3), [((0, 0, 0), [0, 0, 0])]),
    ],
)
def test_vector_image_to_numpy(dims, expected_shape, test_points):
    """Test converting vector images between NumPy array view and SimpleITK

    Tests both 2D and 3D vector images, verifying:
    1. Array shape is correct
    2. Vector values at specific points match expected values
    3. Conversion back to image maintains data integrity
    """
    img = sitk.PhysicalPointSource(sitk.sitkVectorFloat32, dims)
    original_hash = sitk.Hash(img)

    # Get array view and verify shape
    nda = sitk.GetArrayViewFromImage(img)
    assert nda.shape == expected_shape, f"Expected shape {expected_shape}, got {nda.shape}"

    # Check specific points
    for point, expected_value in test_points:
        actual = nda[point].tolist()
        assert actual == expected_value, \
            f"At point {point}, expected {expected_value}, got {actual}"

    # Convert back to image and verify
    if len(dims) == 2:
        img2 = sitk.GetImageFromArray(nda, isVector=True)
    else:
        img2 = sitk.GetImageFromArray(nda)

    assert img2.GetSize() == img.GetSize(), "Image size changed after conversion"
    assert img2.GetNumberOfComponentsPerPixel() == img.GetNumberOfComponentsPerPixel(), \
        "Number of components changed"
    assert original_hash == sitk.Hash(img2), "Image hash changed after conversion"


def test_arrayview_writable():
    """Test that array views are correctly marked as non-writable

    This test verifies that:
    1. The array view is marked as non-writable
    2. Attempts to modify the array view raise appropriate errors
    """
    img = sitk.Image((3, 4), sitk.sitkFloat32, 1)
    array_view = sitk.GetArrayViewFromImage(img)

    # Check writable flag
    assert not array_view.flags["WRITEABLE"], "Array view should not be writable"

    # Check direct assignment
    with pytest.raises(ValueError, match="assignment destination is read-only"):
        array_view[1, 2] = 1

    # Check array modification method
    with pytest.raises(ValueError, match="assignment destination is read-only"):
        array_view.fill(0)


@pytest.mark.benchmark
def test_processing_time():
    """Benchmark conversion performance between SimpleITK and NumPy

    Compares performance between:
    1. GetArrayFromImage (copy operation)
    2. GetArrayViewFromImage (view operation)

    The array view operation should be significantly faster as it avoids copying.
    """
    # Create large test image
    img = sitk.GaussianSource(
        sitk.sitkFloat32, [3000, 3000], sigma=[10] * 3, mean=[50, 50]
    )

    # Time array copy operation
    array_time = min(
        timeit.repeat(lambda: sitk.GetArrayFromImage(img), repeat=5, number=1)
    )

    # Time array view operation
    view_time = min(
        timeit.repeat(lambda: sitk.GetArrayViewFromImage(img), repeat=5, number=1)
    )

    # View operation should be faster than copy
    assert view_time < array_time, \
        f"Array view ({view_time*1e6:.2f}µs) should be faster than array copy ({array_time*1e6:.2f}µs)"
