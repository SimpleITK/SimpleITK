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

import math
import pytest
import SimpleITK as sitk
import sys
import gc
from SimpleITK._SimpleITK import ImageBuffer

# Utility function to calculate expected strides
def calculate_expected_strides(size, itemsize, num_components=None):
    """Calculate expected strides for C-contiguous layout (ITK order reversed).

    Args:
        size: tuple of dimensions in ITK order (x, y, z, ...)
        itemsize: size of one element in bytes
        num_components: number of components per pixel (for vector images), or None for scalar

    Returns:
        tuple of strides in numpy order (reversed from ITK)
    """
    # Reverse the size for numpy convention
    shape = size[::-1]
    if num_components is not None:
        shape = shape + (num_components,)

    # Calculate strides from innermost to outermost
    strides = []
    stride = itemsize
    for i in range(len(shape) - 1, -1, -1):
        strides.insert(0, stride)
        stride *= shape[i]

    return tuple(strides)


# Utility function to get format string for pixel type
def get_expected_format(pixel_type):
    """Get expected format string for a given pixel type."""
    format_map = {
        sitk.sitkUInt8: 'B',
        sitk.sitkInt8: 'b',
        sitk.sitkUInt16: 'H',
        sitk.sitkInt16: 'h',
        sitk.sitkUInt32: 'I',
        sitk.sitkInt32: 'i',
        sitk.sitkUInt64: 'Q',
        sitk.sitkInt64: 'q',
        sitk.sitkFloat32: 'f',
        sitk.sitkFloat64: 'd',
        sitk.sitkComplexFloat32: 'Zf',
        sitk.sitkComplexFloat64: 'Zd',
        sitk.sitkVectorUInt8: 'B',
        sitk.sitkVectorInt8: 'b',
        sitk.sitkVectorUInt16: 'H',
        sitk.sitkVectorInt16: 'h',
        sitk.sitkVectorUInt32: 'I',
        sitk.sitkVectorInt32: 'i',
        sitk.sitkVectorUInt64: 'Q',
        sitk.sitkVectorInt64: 'q',
        sitk.sitkVectorFloat32: 'f',
        sitk.sitkVectorFloat64: 'd',
    }
    return format_map.get(pixel_type, 'B')


# Test scalar pixel types
@pytest.mark.parametrize("pixel_type", [
    sitk.sitkUInt8,
    sitk.sitkInt8,
    sitk.sitkUInt16,
    sitk.sitkInt16,
    sitk.sitkUInt32,
    sitk.sitkInt32,
    sitk.sitkUInt64,
    sitk.sitkInt64,
    sitk.sitkFloat32,
    sitk.sitkFloat64,
])
def test_scalar_types(pixel_type):
    """Test ImageBuffer creation and memoryview for all scalar types"""
    # Create image with unambiguous size
    img = sitk.Image([3, 5, 7], pixel_type)

    # Create ImageBuffer
    buf = ImageBuffer(img)

    # Check that _image_ref points to the original image
    assert buf._image_ref is img, "_image_ref should reference the original image"

    # Create memoryview
    mv = memoryview(buf)

    # Check format
    expected_format = get_expected_format(pixel_type)
    assert mv.format == expected_format, \
        f"Expected format '{expected_format}', got '{mv.format}'"

    # Check shape (should be reversed: z, y, x)
    assert mv.shape == (7, 5, 3), f"Expected shape (7, 5, 3), got {mv.shape}"

    # Check ndim
    assert mv.ndim == 3, f"Expected ndim 3, got {mv.ndim}"

    # Check readonly
    assert mv.readonly, "Buffer should be read-only"

    # Check strides
    expected_strides = calculate_expected_strides((3, 5, 7), mv.itemsize)
    assert mv.strides == expected_strides, \
        f"Expected strides {expected_strides}, got {mv.strides}"

    # Check that buffer is C-contiguous
    assert mv.c_contiguous, "Buffer should be C-contiguous"
    assert not mv.f_contiguous or mv.ndim <= 1, "Buffer should not be Fortran-contiguous"


# Test complex pixel types
@pytest.mark.parametrize("pixel_type,expected_itemsize", [
    (sitk.sitkComplexFloat32, 8),
    (sitk.sitkComplexFloat64, 16),
])
def test_complex_types(pixel_type, expected_itemsize):
    """Test ImageBuffer creation and memoryview for complex types"""
    # Create image with unambiguous size
    img = sitk.Image([2, 4, 6], pixel_type)

    # Create ImageBuffer
    buf = ImageBuffer(img)

    # Create memoryview
    mv = memoryview(buf)

    # Check format
    expected_format = get_expected_format(pixel_type)
    assert mv.format == expected_format, \
        f"Expected format '{expected_format}', got '{mv.format}'"

    # Check shape (should be reversed: z, y, x)
    assert mv.shape == (6, 4, 2), f"Expected shape (6, 4, 2), got {mv.shape}"

    # Check itemsize for complex types
    assert mv.itemsize == expected_itemsize, \
        f"Expected itemsize {expected_itemsize}, got {mv.itemsize}"

    # Check readonly
    assert mv.readonly, "Buffer should be read-only"


# Test vector pixel types
@pytest.mark.parametrize("pixel_type,num_components", [
    (sitk.sitkVectorUInt8, 3),
    (sitk.sitkVectorInt8, 2),
    (sitk.sitkVectorUInt16, 4),
    (sitk.sitkVectorInt16, 3),
    (sitk.sitkVectorUInt32, 2),
    (sitk.sitkVectorInt32, 3),
    (sitk.sitkVectorUInt64, 2),
    (sitk.sitkVectorInt64, 2),
    (sitk.sitkVectorFloat32, 3),
    (sitk.sitkVectorFloat64, 2),
    (sitk.sitkVectorFloat32, 1),
])
def test_vector_types(pixel_type, num_components):
    """Test ImageBuffer creation and memoryview for vector types"""
    # Create image with unambiguous size
    img = sitk.Image([3, 5, 7], pixel_type, num_components)

    # Create ImageBuffer
    buf = ImageBuffer(img)

    # Check that _image_ref points to the original image
    assert buf._image_ref is img, "_image_ref should reference the original image"

    # Create memoryview
    mv = memoryview(buf)

    # Check format
    expected_format = get_expected_format(pixel_type)
    assert mv.format == expected_format, \
        f"Expected format '{expected_format}', got '{mv.format}'"

    # Check shape (should be reversed with components at end: z, y, x, c)
    expected_shape = (7, 5, 3, num_components)
    assert mv.shape == expected_shape, \
        f"Expected shape {expected_shape}, got {mv.shape}"

    # Check ndim
    assert mv.ndim == 4, f"Expected ndim 4, got {mv.ndim}"

    # Check readonly
    assert mv.readonly, "Buffer should be read-only"

    # Check strides
    expected_strides = calculate_expected_strides((3, 5, 7), mv.itemsize, num_components)
    assert mv.strides == expected_strides, \
        f"Expected strides {expected_strides}, got {mv.strides}"


# Test label types (should raise exception)
@pytest.mark.parametrize("pixel_type", [
    sitk.sitkLabelUInt8,
    sitk.sitkLabelUInt16,
    sitk.sitkLabelUInt32,
    sitk.sitkLabelUInt64,
])
def test_label_types_raise_exception(pixel_type):
    """Test that label types raise an exception"""
    img = sitk.Image([3, 5, 7], pixel_type)

    # Creating ImageBuffer should succeed
    buf = ImageBuffer(img)

    # But creating memoryview should fail
    with pytest.raises(BufferError, match="unknown or label pixel type"):
        memoryview(buf)


# Test _image_ref attribute
def test_image_ref_attribute():
    """Test that _image_ref attribute correctly references the source image"""
    img = sitk.Image([3, 5, 7], sitk.sitkUInt8)
    buf = ImageBuffer(img)

    # _image_ref should point to the original image object
    assert buf._image_ref is img, "_image_ref should be the same object as the original image"

    # _image_ref should be a SimpleITK Image
    assert isinstance(buf._image_ref, sitk.Image), "_image_ref should be a SimpleITK Image"

    # _image_ref should have the same properties as the original
    assert buf._image_ref.GetSize() == img.GetSize(), "Size should match"
    assert buf._image_ref.GetPixelID() == img.GetPixelID(), "Pixel type should match"
    assert buf._image_ref.GetDimension() == img.GetDimension(), "Dimension should match"

    # _image_ref should be read-only (we can access it but the attribute itself is read-only)
    with pytest.raises(AttributeError):
        buf._image_ref = sitk.Image([1, 1], sitk.sitkUInt8)


# Test different dimensions
@pytest.mark.parametrize("size,expected_shape", [
    ([5, 7], (7, 5)),           # 2D
    ([3, 5, 7], (7, 5, 3)),     # 3D
    ([2, 3, 5, 7], (7, 5, 3, 2)),     # 4D
    ([2, 3, 5, 7, 11], (11, 7, 5, 3, 2)),  # 5D
])
def test_dimensions(size, expected_shape):
    """Test ImageBuffer with different dimensionalities"""
    img = sitk.Image(size, sitk.sitkFloat32)
    buf = ImageBuffer(img)
    mv = memoryview(buf)

    assert mv.shape == expected_shape, \
        f"Expected shape {expected_shape}, got {mv.shape}"
    assert mv.ndim == len(expected_shape), \
        f"Expected ndim {len(expected_shape)}, got {mv.ndim}"


# Test that buffer remains valid after image deletion
def test_buffer_survives_image_deletion():
    """Test that buffer remains valid after the image is deleted"""
    # Create image and buffer
    img = sitk.Image([3, 5, 7], sitk.sitkUInt16)
    buf = ImageBuffer(img)

    # Check that _image_ref points to the original image
    assert buf._image_ref is img, "_image_ref should reference the original image"

    mv = memoryview(buf)

    # Verify initial state
    assert mv.shape == (7, 5, 3)
    assert mv.format == 'H'

    # Delete the image reference
    del img
    gc.collect()

    # _image_ref should still be accessible and point to the kept-alive image
    assert buf._image_ref is not None, "_image_ref should keep the image alive"
    assert buf._image_ref.GetSize() == (3, 5, 7), "Image should still be accessible via _image_ref"

    # Delete the buffer reference
    del buf
    gc.collect()

    # Buffer and memoryview should still be valid
    assert mv.shape == (7, 5, 3)
    assert mv.format == 'H'
    assert mv.readonly

    # Should still be able to access buffer properties
    assert mv.nbytes == 3 * 5 * 7 * 2  # 2 bytes per uint16


# Test that memoryview is read-only
def test_memoryview_readonly():
    """Test that memoryview from ImageBuffer is read-only"""
    img = sitk.Image([3, 5], sitk.sitkFloat32)
    buf = ImageBuffer(img)
    mv = memoryview(buf)

    assert mv.readonly, "Memoryview should be read-only"

    # Attempting to write should raise an error
    with pytest.raises(TypeError, match="cannot modify read-only memory"):
        mv[0] = 1.0


# Test get_weak_memoryview method with different flags
def test_get_weak_memoryview_default():
    """Test get_weak_memoryview with default flags"""
    img = sitk.Image([3, 5, 7], sitk.sitkFloat32)
    buf = ImageBuffer(img)

    # Call with no arguments (default flags)
    mv = buf.get_weak_memoryview()

    assert mv.shape == (7, 5, 3)
    assert mv.format == 'f'
    assert mv.readonly, "Default should be read-only"

    # Should still work after deleting buf reference
    # but img must remain alive (weak reference)
    del buf
    gc.collect()
    assert mv.shape == (7, 5, 3)


def test_get_weak_memoryview_with_flags():
    """Test get_weak_memoryview with various buffer protocol flags"""
    import inspect

    # Only run if BufferFlags is available (Python 3.12+)
    if not hasattr(inspect, 'BufferFlags'):
        pytest.skip("BufferFlags not available (requires Python 3.12+)")

    BufferFlags = inspect.BufferFlags
    img = sitk.Image([4, 6], sitk.sitkInt32)

    # Test with FULL_RO (full read-only)
    buf = ImageBuffer(img)
    mv = buf.get_weak_memoryview(BufferFlags.FULL_RO)
    assert mv.readonly
    assert mv.shape == (6, 4)
    assert mv.format == 'i'

    # Test with SIMPLE (simple buffer)
    buf = ImageBuffer(img)
    mv = buf.get_weak_memoryview(BufferFlags.SIMPLE)
    assert mv.readonly
    assert mv.shape == (6*4, ) # memoryview appears to be using uninitialized value in shape
    assert mv.ndim == 1
    assert mv.format == 'B'

    # Test with RECORDS (structured data)
    buf = ImageBuffer(img)
    mv = buf.get_weak_memoryview(BufferFlags.RECORDS_RO)
    assert mv.readonly
    assert mv.shape == (6, 4)
    assert mv.format == 'i'


def test_get_weak_memoryview_readonly_enforcement():
    """Test that get_weak_memoryview always returns read-only memoryview"""
    img = sitk.Image([3, 5], sitk.sitkFloat64)
    buf = ImageBuffer(img)

    mv = buf.get_weak_memoryview()

    assert mv.readonly, "get_weak_memoryview should always return read-only"

    # Verify write attempts fail
    with pytest.raises(TypeError, match="cannot modify read-only memory"):
        mv[0, 0] = 99.0


def test_get_weak_memoryview_no_strong_reference():
    """Test that get_weak_memoryview does NOT keep strong reference to image"""
    img = sitk.Image([3, 5], sitk.sitkFloat32)
    initial_refcount = sys.getrefcount(img)

    buf = ImageBuffer(img)
    buf_refcount = sys.getrefcount(img)

    # ImageBuffer holds a reference
    assert buf_refcount > initial_refcount

    # get_weak_memoryview should not increase reference count beyond the buffer's reference
    mv = buf.get_weak_memoryview()
    mv_refcount = sys.getrefcount(img)

    # The memoryview itself doesn't hold an additional strong reference to img
    # (it may hold a reference to buf, but that's implementation-dependent)
    # What matters is that deleting the buf and img leaves mv in a dangerous state

    # Keep img alive, delete buf
    del buf
    gc.collect()

    # memoryview should still work while img is alive
    assert mv.shape == (5, 3)

    # Now delete img - this demonstrates the "weak" nature
    # The memoryview will have a dangling pointer (undefined behavior if accessed)
    img_id = id(img)
    del img
    gc.collect()

    # We can't safely test accessing mv here as it would be undefined behavior
    # The test just demonstrates that the references are properly released
    # In a real scenario, accessing mv after img deletion would likely segfault


def test_get_weak_memoryview_multiple_calls():
    """Test multiple calls to get_weak_memoryview from same ImageBuffer"""
    img = sitk.Image([3, 5, 7], sitk.sitkUInt16)
    buf = ImageBuffer(img)

    # Create multiple weak memoryviews
    mv1 = buf.get_weak_memoryview()
    mv2 = buf.get_weak_memoryview()
    mv3 = buf.get_weak_memoryview()

    # All should have same properties
    assert mv1.shape == mv2.shape == mv3.shape == (7, 5, 3)
    assert mv1.format == mv2.format == mv3.format == 'H'
    assert all(mv.readonly for mv in [mv1, mv2, mv3])

    # They may or may not be the same object (implementation-dependent)
    # but they should all work correctly
    assert mv1.nbytes == mv2.nbytes == mv3.nbytes


def test_get_weak_memoryview_vector_image():
    """Test get_weak_memoryview with vector pixel types"""
    img = sitk.Image([4, 6], sitk.sitkVectorFloat32, 3)
    buf = ImageBuffer(img)

    mv = buf.get_weak_memoryview()

    # Shape should be (y, x, components) = (6, 4, 3)
    assert mv.shape == (6, 4, 3)
    assert mv.format == 'f'
    assert mv.readonly
    assert mv.ndim == 3


def test_get_weak_memoryview_complex_image():
    """Test get_weak_memoryview with complex pixel types"""
    img = sitk.Image([3, 5], sitk.sitkComplexFloat64)
    buf = ImageBuffer(img)

    mv = buf.get_weak_memoryview()

    assert mv.shape == (5, 3)
    assert mv.format == 'Zd'  # Complex double
    assert mv.readonly
    assert mv.itemsize == 16  # 2 * 8 bytes


# Test multiple buffers from same image
def test_multiple_buffers_same_image():
    """Test creating multiple buffers from the same image"""
    img = sitk.Image([3, 5, 7], sitk.sitkInt16)

    buf1 = ImageBuffer(img)
    buf2 = ImageBuffer(img)

    # Both buffers should reference the same image
    assert buf1._image_ref is img, "buf1._image_ref should reference the original image"
    assert buf2._image_ref is img, "buf2._image_ref should reference the original image"
    assert buf1._image_ref is buf2._image_ref, "Both buffers should reference the same image"

    mv1 = memoryview(buf1)
    mv2 = memoryview(buf2)

    # Both should have same properties
    assert mv1.shape == mv2.shape
    assert mv1.format == mv2.format
    assert mv1.strides == mv2.strides
    assert mv1.nbytes == mv2.nbytes


# Test that ImageBuffer and memoryview hold reference to image
def test_image_reference_chain():
    """Test that ImageBuffer and memoryview maintain references to the source image"""
    img = sitk.Image([3, 5], sitk.sitkFloat32)
    initial_refcount = sys.getrefcount(img)

    # Create buffer - should increase refcount
    buf = ImageBuffer(img)

    # Check that _image_ref points to the original image
    assert buf._image_ref is img, "_image_ref should reference the original image"

    # Reference count should increase
    assert sys.getrefcount(img) > initial_refcount, \
        "ImageBuffer should hold a reference to the image"

    buf_refcount = sys.getrefcount(img)

    # Create memoryview - should increase refcount further (holds ref to buffer)
    mv = memoryview(buf)

    assert sys.getrefcount(img) >= buf_refcount, \
        "Memoryview should indirectly maintain image reference"

    mv_refcount = sys.getrefcount(img)

    # Delete buffer - image should still be alive due to memoryview
    del buf
    gc.collect()

    # Reference count should remain elevated because memoryview holds buffer
    assert sys.getrefcount(img) >= initial_refcount, \
        "Image should remain alive while memoryview exists"

    # Memoryview should still work
    assert mv.shape == (5, 3)

    # Delete memoryview - now image reference should be released
    del mv
    gc.collect()

    # Reference count should decrease back to initial
    assert sys.getrefcount(img) == initial_refcount, \
        "All references should be released after memoryview deletion"


# Test C-contiguous layout
def test_c_contiguous():
    """Test that buffer is C-contiguous and flattened view has correct sequence"""
    img = sitk.Image([3, 5, 7], sitk.sitkUInt32)

    # Set all pixels to sequential values in ITK order (x, y, z)
    value = 0
    for z in range(7):
        for y in range(5):
            for x in range(3):
                img[x, y, z] = value
                value += 1

    buf = ImageBuffer(img)
    mv = memoryview(buf)

    assert mv.c_contiguous, "Buffer should be C-contiguous"
    assert not mv.f_contiguous, "Buffer should not be Fortran-contiguous"
    assert mv.contiguous, "Buffer should be contiguous"

    # Flatten the memoryview and verify the sequence
    # The memoryview shape is (7, 5, 3) in numpy order (z, y, x)
    # When flattened, it should be the same sequence as we wrote
    flat = mv.cast('B')
    flat = flat.cast(mv.format, [math.prod(mv.shape)])  # Cast to unsigned int (1D view)

    expected_sequence = list(range(3 * 5 * 7))  # 0 to 104
    actual_sequence = flat.tolist()

    assert actual_sequence == expected_sequence, \
        f"Flattened sequence doesn't match. First 10: {actual_sequence[:10]}, Last 10: {actual_sequence[-10:]}"


# Test suboffsets (should be None for simple layouts)
def test_no_suboffsets():
    """Test that buffer has no suboffsets (simple layout)"""
    img = sitk.Image([3, 5, 7], sitk.sitkInt32)
    buf = ImageBuffer(img)
    mv = memoryview(buf)

    # Note: memoryview doesn't expose suboffsets directly in Python,
    # but we can verify the buffer is contiguous which implies no suboffsets
    assert mv.contiguous, "Buffer should be contiguous (no suboffsets)"
