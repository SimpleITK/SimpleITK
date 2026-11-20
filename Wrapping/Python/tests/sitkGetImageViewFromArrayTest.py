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
# ==========================================================================

import gc
import weakref

import numpy as np
import pytest
import SimpleITK as sitk


def test_scalar_2d_roundtrip():
    arr = np.zeros((7, 5), dtype=np.uint16)
    img = sitk.GetImageViewFromArray(arr)

    assert img.GetSize() == (5, 7)
    assert img.GetPixelID() == sitk.sitkUInt16


def test_scalar_3d_roundtrip():
    arr = np.zeros((7, 5, 3), dtype=np.float32)
    img = sitk.GetImageViewFromArray(arr)

    assert img.GetSize() == (3, 5, 7)
    assert img.GetPixelID() == sitk.sitkFloat32


def test_vector_image():
    arr = np.zeros((6, 4, 3), dtype=np.float32)
    img = sitk.GetImageViewFromArray(arr, isVector=True)

    assert img.GetSize() == (4, 6)
    assert img.GetNumberOfComponentsPerPixel() == 3
    assert img.GetPixelID() == sitk.sitkVectorFloat32


def test_write_through_array_to_image():
    arr = np.zeros((5, 3), dtype=np.int32)
    img = sitk.GetImageViewFromArray(arr)

    arr[2, 1] = 42
    assert img[1, 2] == 42


def test_write_through_image_to_array():
    arr = np.zeros((5, 3), dtype=np.int32)
    img = sitk.GetImageViewFromArray(arr)

    img[1, 2] = 99
    assert arr[2, 1] == 99


def test_default_geometry():
    arr = np.zeros((5, 3), dtype=np.uint8)
    img = sitk.GetImageViewFromArray(arr)

    assert img.GetSpacing() == (1.0, 1.0)
    assert img.GetOrigin() == (0.0, 0.0)


def test_rejects_read_only_array():
    arr = np.zeros((5, 3), dtype=np.uint8)
    arr.flags.writeable = False

    with pytest.raises(ValueError, match="writable"):
        sitk.GetImageViewFromArray(arr)


def test_rejects_non_contiguous_array():
    arr = np.zeros((5, 6), dtype=np.uint8)
    non_contiguous = arr[:, ::2]  # every-other-column view, not C-contiguous

    with pytest.raises(ValueError, match="contiguous"):
        sitk.GetImageViewFromArray(non_contiguous)


def test_rejects_transposed_array():
    arr = np.zeros((5, 6), dtype=np.uint8)

    with pytest.raises(ValueError, match="contiguous"):
        sitk.GetImageViewFromArray(arr.T)


def test_rejects_unsupported_dimension():
    arr = np.zeros((5,), dtype=np.uint8)

    with pytest.raises(ValueError, match="2D or 3D"):
        sitk.GetImageViewFromArray(arr)


def test_rejects_complex_dtype():
    arr = np.zeros((5, 3), dtype=np.complex64)

    with pytest.raises(TypeError):
        sitk.GetImageViewFromArray(arr)


def test_buffer_pinned_after_array_deleted():
    """The Image must keep working after the original array variable is
    gone - this is the entire point of the feature."""
    arr = np.arange(5 * 3, dtype=np.int32).reshape(5, 3)
    img = sitk.GetImageViewFromArray(arr)

    del arr
    gc.collect()

    assert img[1, 2] == 2 * 3 + 1  # img[x, y] corresponds to arr[y, x]
    img[0, 0] = 123
    assert img[0, 0] == 123


def test_buffer_released_when_image_is_deleted():
    """The pinned buffer export must actually be released - and release the
    array - once the last Image referencing it is gone, not held forever."""
    arr = np.zeros((5, 3), dtype=np.float32)
    img = sitk.GetImageViewFromArray(arr)

    released = []
    finalizer = weakref.finalize(arr, released.append, True)

    del arr
    gc.collect()
    assert not released, "array must stay alive while the Image still references its buffer"

    del img
    gc.collect()
    assert released, "array must be released once the Image referencing its buffer is gone"
    assert finalizer.alive is False


def test_buffer_pinned_through_shallow_copy():
    """A shallow copy (img2 = img, or Image(img)) shares the same underlying
    ITK image, so the pinned buffer must survive as long as either exists."""
    arr = np.zeros((5, 3), dtype=np.uint16)
    img = sitk.GetImageViewFromArray(arr)
    img2 = sitk.Image(img)  # shallow copy - shares the same underlying ITK image

    del arr
    del img
    gc.collect()

    img2[0, 0] = 7
    assert img2[0, 0] == 7
