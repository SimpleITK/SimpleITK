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
import numpy as np
import SimpleITK as sitk

# Test dimensions
sizeX = 4
sizeY = 5
sizeZ = 3


def _check_sitk_to_numpy_type(sitkType, numpyType):
    """Helper to check SimpleITK to numpy type conversion"""
    image = sitk.Image((9, 10), sitkType, 1)
    a = sitk.GetArrayFromImage(image)
    assert numpyType == a.dtype, f"Expected numpy type {numpyType}, got {a.dtype}"
    assert (10, 9) == a.shape, f"Expected shape (10, 9), got {a.shape}"


@pytest.mark.parametrize("sitk_type,numpy_type", [
    (sitk.sitkUInt8, np.uint8),
    (sitk.sitkUInt16, np.uint16),
    (sitk.sitkUInt32, np.uint32),
    (sitk.sitkInt8, np.int8),
    (sitk.sitkInt16, np.int16),
    (sitk.sitkInt32, np.int32),
    (sitk.sitkFloat32, np.float32),
    (sitk.sitkFloat64, np.float64),
    (sitk.sitkComplexFloat32, np.complex64),
    (sitk.sitkComplexFloat64, np.complex128),
    (sitk.sitkVectorUInt8, np.uint8),
    (sitk.sitkVectorInt8, np.int8),
    (sitk.sitkVectorUInt16, np.uint16),
    (sitk.sitkVectorInt16, np.int16),
    (sitk.sitkVectorUInt32, np.uint32),
    (sitk.sitkVectorInt32, np.int32),
    (sitk.sitkVectorFloat32, np.float32),
    (sitk.sitkVectorFloat64, np.float64),
])
def test_type_to_numpy(sitk_type, numpy_type):
    """Test conversion from all SimpleITK pixel types to numpy types"""
    if sitk_type != sitk.sitkUnknown:
        _check_sitk_to_numpy_type(sitk_type, numpy_type)

    # Additional optional types based on platform support
    if sitk.sitkUInt64 != sitk.sitkUnknown:
        _check_sitk_to_numpy_type(sitk.sitkUInt64, np.uint64)
    if sitk.sitkInt64 != sitk.sitkUnknown:
        _check_sitk_to_numpy_type(sitk.sitkInt64, np.int64)
    if sitk.sitkVectorUInt64 != sitk.sitkUnknown:
        _check_sitk_to_numpy_type(sitk.sitkVectorUInt64, np.uint64)
    if sitk.sitkVectorInt64 != sitk.sitkUnknown:
        _check_sitk_to_numpy_type(sitk.sitkVectorInt64, np.int64)


def test_to_numpy_and_back():
    """Test converting an image to numpy and back"""
    img = sitk.GaussianSource(
        sitk.sitkFloat32, [100, 100], sigma=[10] * 3, mean=[50, 50]
    )
    h = sitk.Hash(img)

    # convert the image to and from a numpy array
    img = sitk.GetImageFromArray(sitk.GetArrayFromImage(img))
    assert h == sitk.Hash(img), "Image hash changed after numpy conversion"


@pytest.mark.parametrize("shape,is_vector,expected_size,expected_type,expected_components", [
    ((2, 3), False, (3, 2), sitk.sitkFloat32, None),
    ((2, 3), True, (3, 2), sitk.sitkVectorFloat32, 1),
    ((2, 3, 5), False, (5, 3, 2), sitk.sitkFloat32, None),
    ((2, 3, 5), True, (3, 2), sitk.sitkVectorFloat32, 5),
])
def test_isVector(shape, is_vector, expected_size, expected_type, expected_components):
    """Test behavior of isVector option"""
    nda = np.arange(np.prod(shape), dtype=np.float32).reshape(shape)
    img = sitk.GetImageFromArray(nda, isVector=is_vector)

    assert img.GetSize() == expected_size, f"Expected size {expected_size}, got {img.GetSize()}"
    assert img.GetPixelID() == expected_type, f"Expected type {expected_type}, got {img.GetPixelID()}"

    if expected_components is not None:
        assert img.GetNumberOfComponentsPerPixel() == expected_components, \
            f"Expected {expected_components} components, got {img.GetNumberOfComponentsPerPixel()}"


def test_complex_image_to_numpy():
    """Test converting complex images between SimpleITK and numpy"""
    # 2D test
    img_real = sitk.GaussianSource(
        sitk.sitkFloat32, [100, 100], sigma=[10] * 3, mean=[50, 50]
    )
    img_imaginary = sitk.GaussianSource(
        sitk.sitkFloat32, [100, 100], sigma=[20] * 3, mean=[10, 10]
    )
    img = sitk.RealAndImaginaryToComplex(img_real, img_imaginary)
    h = sitk.Hash(img)

    nda = sitk.GetArrayFromImage(img)
    assert nda.shape == (100, 100), f"Expected shape (100, 100), got {nda.shape}"
    assert nda[0, 0] == img.GetPixel([0, 0]), "Pixel values don't match at (0,0)"
    assert nda[2, 1] == img.GetPixel([1, 2]), "Pixel values don't match at (1,2)"

    img2 = sitk.GetImageFromArray(nda)
    assert h == sitk.Hash(img2), "Image hash changed after numpy conversion"
    assert img.GetSize() == (100, 100), f"Expected size (100, 100), got {img.GetSize()}"

    # 4D test
    img = sitk.Image([10, 9, 8, 7], sitk.sitkComplexFloat64)
    h = sitk.Hash(img)

    nda = sitk.GetArrayFromImage(img)
    assert nda.shape == (7, 8, 9, 10), f"Expected shape (7,8,9,10), got {nda.shape}"
    assert nda[0, 0, 0, 0] == 0 + 0j, "Expected zero complex value"

    img2 = sitk.GetImageFromArray(nda)
    assert img2.GetSize() == img.GetSize(), "Size mismatch after conversion"
    assert img2.GetNumberOfComponentsPerPixel() == img.GetNumberOfComponentsPerPixel(), \
        "Component count changed"
    assert h == sitk.Hash(img2), "Image hash changed after numpy conversion"


def test_vector_image_to_numpy():
    """Test converting vector images between SimpleITK and numpy"""
    # 2D test
    img = sitk.PhysicalPointSource(sitk.sitkVectorFloat32, [3, 4])
    h = sitk.Hash(img)

    nda = sitk.GetArrayFromImage(img)
    assert nda.shape == (4, 3, 2), f"Expected shape (4,3,2), got {nda.shape}"
    assert nda[0, 0].tolist() == [0, 0], "Vector values don't match at (0,0)"
    assert nda[2, 1].tolist() == [1, 2], "Vector values don't match at (2,1)"
    assert nda[0, :, 0].tolist() == [0, 1, 2], "Vector values along axis don't match"

    img2 = sitk.GetImageFromArray(nda, isVector=True)
    assert h == sitk.Hash(img2), "Image hash changed after numpy conversion"

    # 3D test
    img = sitk.PhysicalPointSource(sitk.sitkVectorFloat32, [3, 4, 5])
    h = sitk.Hash(img)

    nda = sitk.GetArrayFromImage(img)
    assert nda.shape == (5, 4, 3, 3), f"Expected shape (5,4,3,3), got {nda.shape}"
    assert nda[0, 0, 0].tolist() == [0, 0, 0], "Vector values don't match at (0,0,0)"
    assert nda[0, 0, :, 0].tolist() == [0, 1, 2], "Vector values along axis don't match"
    assert nda[0, :, 1, 1].tolist() == [0, 1, 2, 3], "Vector values along axis don't match"

    img2 = sitk.GetImageFromArray(nda)
    assert img2.GetSize() == img.GetSize(), "Size mismatch after conversion"
    assert img2.GetNumberOfComponentsPerPixel() == img.GetNumberOfComponentsPerPixel(), \
        "Component count changed"
    assert h == sitk.Hash(img2), "Image hash changed after numpy conversion"


@pytest.mark.parametrize("slice_expr", [
    "arr[::2, ...]",
    "arr",
    "arr[2:, :, ::3]"
])
def test_non_contiguous(slice_expr):
    """Test converting non-contiguous numpy arrays to SimpleITK Image"""
    arr = np.arange(5 * 7 * 11, dtype=np.int32).reshape(5, 7, 11)
    sliced = eval(slice_expr)  # Safe since we control the input
    img = sitk.GetImageFromArray(sliced)

    # Verify the image dimensions match the sliced array
    expected_shape = sliced.shape[::-1]  # Reverse shape for SimpleITK convention
    assert img.GetSize() == expected_shape, \
        f"Expected size {expected_shape}, got {img.GetSize()}"


@pytest.mark.parametrize("dtype", [
    "byte", "ubyte", "short", "ushort", "intc", "uintc",
    "uint", "longlong", "ulonglong"
])
def test_image_from_native_type(dtype):
    """Test converting from native numpy scalar types to SimpleITK"""
    arr = np.zeros([4, 5], dtype=np.dtype(dtype))
    img = sitk.GetImageFromArray(arr)
    assert img.GetSize() == (5, 4), f"Expected size (5,4), got {img.GetSize()}"


def test_legacy_2d():
    """Test 2D SimpleITK Image to numpy array conversion"""
    image = sitk.Image(sizeX, sizeY, sitk.sitkInt32)
    for j in range(sizeY):
        for i in range(sizeX):
            image[i, j] = j * sizeX + i

    arr = sitk.GetArrayFromImage(image)
    assert isinstance(arr, np.ndarray), "Result should be numpy array"
    assert arr.shape == (sizeY, sizeX), f"Expected shape ({sizeY},{sizeX}), got {arr.shape}"


def test_legacy_3d():
    """Test 3D SimpleITK Image to numpy array conversion"""
    image = sitk.Image(sizeX, sizeY, sizeZ, sitk.sitkFloat32)
    for k in range(sizeZ):
        for j in range(sizeY):
            for i in range(sizeX):
                image[i, j, k] = (sizeY * k + j) * sizeX + i

    arr = sitk.GetArrayFromImage(image)
    assert isinstance(arr, np.ndarray), "Result should be numpy array"
    assert arr.shape == (sizeZ, sizeY, sizeX), \
        f"Expected shape ({sizeZ},{sizeY},{sizeX}), got {arr.shape}"


@pytest.mark.parametrize("dims,dtype", [
    ((sizeY, sizeX), np.float64),
    ((sizeZ, sizeY, sizeX), np.int16)
])
def test_legacy_array2sitk(dims, dtype):
    """Test numpy array to SimpleITK Image conversion"""
    size = np.prod(dims)
    arr = np.arange(size, dtype=dtype).reshape(dims)

    image = sitk.GetImageFromArray(arr)
    assert image.GetSize() == dims[::-1], \
        f"Expected size {dims[::-1]}, got {image.GetSize()}"

    # Test some sample points
    assert (image[0, 0, 0] if len(dims) == 3 else image[0, 0]) == 0
    assert (image[1, 1, 0] if len(dims) == 3 else image[1, 1]) == 5
    assert (image[2, 2, 0] if len(dims) == 3 else image[2, 2]) == 10
