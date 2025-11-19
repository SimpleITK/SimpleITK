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
import sys
import gc
import unittest
import SimpleITK as sitk
from SimpleITK._SimpleITK import ImageBuffer


def calculate_expected_strides(size, itemsize, num_components=None):
    """Calculate expected strides for C-contiguous layout (ITK order reversed).

    Args:
        size: tuple of dimensions in ITK order (x, y, z, ...)
        itemsize: size of one element in bytes
        num_components: number of components per pixel (for vector images), or None for scalar

    Returns:
        tuple of strides in numpy order (reversed from ITK)
    """
    shape = size[::-1]
    if num_components is not None:
        shape = shape + (num_components,)

    strides = []
    stride = itemsize
    for i in range(len(shape) - 1, -1, -1):
        strides.insert(0, stride)
        stride *= shape[i]

    return tuple(strides)


def get_expected_format(pixel_type):
    """Get expected format string for a given pixel type."""
    format_map = {
        sitk.sitkUInt8: "B",
        sitk.sitkInt8: "b",
        sitk.sitkUInt16: "H",
        sitk.sitkInt16: "h",
        sitk.sitkUInt32: "I",
        sitk.sitkInt32: "i",
        sitk.sitkUInt64: "Q",
        sitk.sitkInt64: "q",
        sitk.sitkFloat32: "f",
        sitk.sitkFloat64: "d",
        sitk.sitkComplexFloat32: "Zf",
        sitk.sitkComplexFloat64: "Zd",
        sitk.sitkVectorUInt8: "B",
        sitk.sitkVectorInt8: "b",
        sitk.sitkVectorUInt16: "H",
        sitk.sitkVectorInt16: "h",
        sitk.sitkVectorUInt32: "I",
        sitk.sitkVectorInt32: "i",
        sitk.sitkVectorUInt64: "Q",
        sitk.sitkVectorInt64: "q",
        sitk.sitkVectorFloat32: "f",
        sitk.sitkVectorFloat64: "d",
    }
    return format_map.get(pixel_type, "B")


class ImageBufferTest(unittest.TestCase):
    SCALAR_TYPES = [
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
    ]

    COMPLEX_TYPES = [
        (sitk.sitkComplexFloat32, 8),
        (sitk.sitkComplexFloat64, 16),
    ]

    VECTOR_TYPES = [
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
    ]

    LABEL_TYPES = [
        sitk.sitkLabelUInt8,
        sitk.sitkLabelUInt16,
        sitk.sitkLabelUInt32,
        sitk.sitkLabelUInt64,
    ]

    def test_scalar_types(self):
        """Test ImageBuffer creation and memoryview for all scalar types"""
        for pixel_type in self.SCALAR_TYPES:
            with self.subTest(pixel_type=pixel_type):
                img = sitk.Image([3, 5, 7], pixel_type)

                buf = ImageBuffer(img)

                self.assertIs(
                    buf._image_ref,
                    img,
                    "_image_ref should reference the original image",
                )

                mv = memoryview(buf)

                expected_format = get_expected_format(pixel_type)
                self.assertEqual(
                    mv.format,
                    expected_format,
                    f"Expected format '{expected_format}', got '{mv.format}'",
                )

                self.assertEqual(
                    mv.shape, (7, 5, 3), f"Expected shape (7, 5, 3), got {mv.shape}"
                )

                self.assertEqual(mv.ndim, 3, f"Expected ndim 3, got {mv.ndim}")

                self.assertTrue(mv.readonly, "Buffer should be read-only")

                expected_strides = calculate_expected_strides((3, 5, 7), mv.itemsize)
                self.assertEqual(
                    mv.strides,
                    expected_strides,
                    f"Expected strides {expected_strides}, got {mv.strides}",
                )

                self.assertTrue(mv.c_contiguous, "Buffer should be C-contiguous")
                self.assertTrue(
                    not mv.f_contiguous or mv.ndim <= 1,
                    "Buffer should not be Fortran-contiguous",
                )

    def test_complex_types(self):
        """Test ImageBuffer creation and memoryview for complex types"""
        for pixel_type, expected_itemsize in self.COMPLEX_TYPES:
            with self.subTest(pixel_type=pixel_type):
                img = sitk.Image([2, 4, 6], pixel_type)

                buf = ImageBuffer(img)

                mv = memoryview(buf)

                expected_format = get_expected_format(pixel_type)
                self.assertEqual(
                    mv.format,
                    expected_format,
                    f"Expected format '{expected_format}', got '{mv.format}'",
                )

                self.assertEqual(
                    mv.shape, (6, 4, 2), f"Expected shape (6, 4, 2), got {mv.shape}"
                )

                self.assertEqual(
                    mv.itemsize,
                    expected_itemsize,
                    f"Expected itemsize {expected_itemsize}, got {mv.itemsize}",
                )

                self.assertTrue(mv.readonly, "Buffer should be read-only")

    def test_vector_types(self):
        """Test ImageBuffer creation and memoryview for vector types"""
        for pixel_type, num_components in self.VECTOR_TYPES:
            with self.subTest(pixel_type=pixel_type, num_components=num_components):
                img = sitk.Image([3, 5, 7], pixel_type, num_components)

                buf = ImageBuffer(img)

                self.assertIs(
                    buf._image_ref,
                    img,
                    "_image_ref should reference the original image",
                )

                mv = memoryview(buf)

                expected_format = get_expected_format(pixel_type)
                self.assertEqual(
                    mv.format,
                    expected_format,
                    f"Expected format '{expected_format}', got '{mv.format}'",
                )

                expected_shape = (7, 5, 3, num_components)
                self.assertEqual(
                    mv.shape,
                    expected_shape,
                    f"Expected shape {expected_shape}, got {mv.shape}",
                )

                self.assertEqual(mv.ndim, 4, f"Expected ndim 4, got {mv.ndim}")

                self.assertTrue(mv.readonly, "Buffer should be read-only")

                expected_strides = calculate_expected_strides(
                    (3, 5, 7), mv.itemsize, num_components
                )
                self.assertEqual(
                    mv.strides,
                    expected_strides,
                    f"Expected strides {expected_strides}, got {mv.strides}",
                )

    def test_label_types_raise_exception(self):
        """Test that label types raise an exception"""
        for pixel_type in self.LABEL_TYPES:
            with self.subTest(pixel_type=pixel_type):
                img = sitk.Image([3, 5, 7], pixel_type)

                # Creating ImageBuffer should succeed
                buf = ImageBuffer(img)

                # But creating memoryview should fail
                with self.assertRaisesRegex(BufferError, "unknown or label pixel type"):
                    memoryview(buf)

    def test_image_ref_attribute(self):
        """Test that _image_ref attribute correctly references the source image"""
        img = sitk.Image([3, 5, 7], sitk.sitkUInt8)
        buf = ImageBuffer(img)

        self.assertIs(
            buf._image_ref, img, "_image_ref should be the same object as the original image"
        )

        self.assertIsInstance(
            buf._image_ref, sitk.Image, "_image_ref should be a SimpleITK Image"
        )

        self.assertEqual(buf._image_ref.GetSize(), img.GetSize(), "Size should match")
        self.assertEqual(
            buf._image_ref.GetPixelID(), img.GetPixelID(), "Pixel type should match"
        )
        self.assertEqual(
            buf._image_ref.GetDimension(),
            img.GetDimension(),
            "Dimension should match",
        )

        # _image_ref should be read-only (we can access it but the attribute itself is read-only)
        with self.assertRaises(AttributeError):
            buf._image_ref = sitk.Image([1, 1], sitk.sitkUInt8)

    def test_dimensions(self):
        """Test ImageBuffer with different dimensionalities"""
        cases = [
            ([5, 7], (7, 5)),  # 2D
            ([3, 5, 7], (7, 5, 3)),  # 3D
            ([2, 3, 5, 7], (7, 5, 3, 2)),  # 4D
            ([2, 3, 5, 7, 11], (11, 7, 5, 3, 2)),  # 5D
        ]
        for size, expected_shape in cases:
            with self.subTest(size=size):
                img = sitk.Image(size, sitk.sitkFloat32)
                buf = ImageBuffer(img)
                mv = memoryview(buf)

                self.assertEqual(
                    mv.shape,
                    expected_shape,
                    f"Expected shape {expected_shape}, got {mv.shape}",
                )
                self.assertEqual(
                    mv.ndim,
                    len(expected_shape),
                    f"Expected ndim {len(expected_shape)}, got {mv.ndim}",
                )

    def test_buffer_survives_image_deletion(self):
        """Test that buffer remains valid after the image is deleted"""
        img = sitk.Image([3, 5, 7], sitk.sitkUInt16)
        buf = ImageBuffer(img)

        self.assertIs(
            buf._image_ref, img, "_image_ref should reference the original image"
        )

        mv = memoryview(buf)

        self.assertEqual(mv.shape, (7, 5, 3))
        self.assertEqual(mv.format, "H")

        del img
        gc.collect()

        self.assertIsNotNone(buf._image_ref, "_image_ref should keep the image alive")
        self.assertEqual(
            buf._image_ref.GetSize(),
            (3, 5, 7),
            "Image should still be accessible via _image_ref",
        )

        del buf
        gc.collect()

        self.assertEqual(mv.shape, (7, 5, 3))
        self.assertEqual(mv.format, "H")
        self.assertTrue(mv.readonly)

        self.assertEqual(mv.nbytes, 3 * 5 * 7 * 2)  # 2 bytes per uint16

    def test_memoryview_readonly(self):
        """Test that memoryview from ImageBuffer is read-only"""
        img = sitk.Image([3, 5], sitk.sitkFloat32)
        buf = ImageBuffer(img)
        mv = memoryview(buf)

        self.assertTrue(mv.readonly, "Memoryview should be read-only")

        with self.assertRaisesRegex(TypeError, "cannot modify read-only memory"):
            mv[0] = 1.0

    def test_get_weak_memoryview_default(self):
        """Test get_weak_memoryview with default flags"""
        img = sitk.Image([3, 5, 7], sitk.sitkFloat32)
        buf = ImageBuffer(img)

        mv = buf.get_weak_memoryview()

        self.assertEqual(mv.shape, (7, 5, 3))
        self.assertEqual(mv.format, "f")
        self.assertTrue(mv.readonly, "Default should be read-only")

        # Should still work after deleting buf reference, but img must remain
        # alive (weak reference)
        del buf
        gc.collect()
        self.assertEqual(mv.shape, (7, 5, 3))

    def test_get_weak_memoryview_with_flags(self):
        """Test get_weak_memoryview with various buffer protocol flags"""
        import inspect

        if not hasattr(inspect, "BufferFlags"):
            self.skipTest("BufferFlags not available (requires Python 3.12+)")

        BufferFlags = inspect.BufferFlags
        img = sitk.Image([4, 6], sitk.sitkInt32)

        # Test with FULL_RO (full read-only)
        buf = ImageBuffer(img)
        mv = buf.get_weak_memoryview(BufferFlags.FULL_RO)
        self.assertTrue(mv.readonly)
        self.assertEqual(mv.shape, (6, 4))
        self.assertEqual(mv.format, "i")

        # Test with SIMPLE (simple buffer)
        buf = ImageBuffer(img)
        mv = buf.get_weak_memoryview(BufferFlags.SIMPLE)
        self.assertTrue(mv.readonly)
        # memoryview appears to be using uninitialized value in shape
        self.assertEqual(mv.shape, (6 * 4,))
        self.assertEqual(mv.ndim, 1)
        self.assertEqual(mv.format, "B")

        # Test with RECORDS (structured data)
        buf = ImageBuffer(img)
        mv = buf.get_weak_memoryview(BufferFlags.RECORDS_RO)
        self.assertTrue(mv.readonly)
        self.assertEqual(mv.shape, (6, 4))
        self.assertEqual(mv.format, "i")

    def test_get_weak_memoryview_readonly_enforcement(self):
        """Test that get_weak_memoryview always returns read-only memoryview"""
        img = sitk.Image([3, 5], sitk.sitkFloat64)
        buf = ImageBuffer(img)

        mv = buf.get_weak_memoryview()

        self.assertTrue(mv.readonly, "get_weak_memoryview should always return read-only")

        with self.assertRaisesRegex(TypeError, "cannot modify read-only memory"):
            mv[0, 0] = 99.0

    def test_get_weak_memoryview_no_strong_reference(self):
        """Test that get_weak_memoryview does NOT keep strong reference to image"""
        img = sitk.Image([3, 5], sitk.sitkFloat32)
        initial_refcount = sys.getrefcount(img)

        buf = ImageBuffer(img)
        buf_refcount = sys.getrefcount(img)

        # ImageBuffer holds a reference
        self.assertGreater(buf_refcount, initial_refcount)

        # get_weak_memoryview should not increase reference count beyond the
        # buffer's reference
        mv = buf.get_weak_memoryview()

        # Keep img alive, delete buf
        del buf
        gc.collect()

        # memoryview should still work while img is alive
        self.assertEqual(mv.shape, (5, 3))

        # Now delete img - this demonstrates the "weak" nature. The
        # memoryview will have a dangling pointer (undefined behavior if
        # accessed), so it is not safe to use mv past this point.
        del img
        gc.collect()

    def test_get_weak_memoryview_multiple_calls(self):
        """Test multiple calls to get_weak_memoryview from same ImageBuffer"""
        img = sitk.Image([3, 5, 7], sitk.sitkUInt16)
        buf = ImageBuffer(img)

        mv1 = buf.get_weak_memoryview()
        mv2 = buf.get_weak_memoryview()
        mv3 = buf.get_weak_memoryview()

        self.assertEqual(mv1.shape, (7, 5, 3))
        self.assertEqual(mv2.shape, (7, 5, 3))
        self.assertEqual(mv3.shape, (7, 5, 3))
        self.assertEqual(mv1.format, "H")
        self.assertEqual(mv2.format, "H")
        self.assertEqual(mv3.format, "H")
        self.assertTrue(all(mv.readonly for mv in [mv1, mv2, mv3]))

        self.assertEqual(mv1.nbytes, mv2.nbytes)
        self.assertEqual(mv2.nbytes, mv3.nbytes)

    def test_get_weak_memoryview_vector_image(self):
        """Test get_weak_memoryview with vector pixel types"""
        img = sitk.Image([4, 6], sitk.sitkVectorFloat32, 3)
        buf = ImageBuffer(img)

        mv = buf.get_weak_memoryview()

        # Shape should be (y, x, components) = (6, 4, 3)
        self.assertEqual(mv.shape, (6, 4, 3))
        self.assertEqual(mv.format, "f")
        self.assertTrue(mv.readonly)
        self.assertEqual(mv.ndim, 3)

    def test_get_weak_memoryview_complex_image(self):
        """Test get_weak_memoryview with complex pixel types"""
        img = sitk.Image([3, 5], sitk.sitkComplexFloat64)
        buf = ImageBuffer(img)

        mv = buf.get_weak_memoryview()

        self.assertEqual(mv.shape, (5, 3))
        self.assertEqual(mv.format, "Zd")  # Complex double
        self.assertTrue(mv.readonly)
        self.assertEqual(mv.itemsize, 16)  # 2 * 8 bytes

    def test_multiple_buffers_same_image(self):
        """Test creating multiple buffers from the same image"""
        img = sitk.Image([3, 5, 7], sitk.sitkInt16)

        buf1 = ImageBuffer(img)
        buf2 = ImageBuffer(img)

        self.assertIs(
            buf1._image_ref, img, "buf1._image_ref should reference the original image"
        )
        self.assertIs(
            buf2._image_ref, img, "buf2._image_ref should reference the original image"
        )
        self.assertIs(
            buf1._image_ref,
            buf2._image_ref,
            "Both buffers should reference the same image",
        )

        mv1 = memoryview(buf1)
        mv2 = memoryview(buf2)

        self.assertEqual(mv1.shape, mv2.shape)
        self.assertEqual(mv1.format, mv2.format)
        self.assertEqual(mv1.strides, mv2.strides)
        self.assertEqual(mv1.nbytes, mv2.nbytes)

    def test_image_reference_chain(self):
        """Test that ImageBuffer and memoryview maintain references to the source image"""
        img = sitk.Image([3, 5], sitk.sitkFloat32)
        initial_refcount = sys.getrefcount(img)

        # Create buffer - should increase refcount
        buf = ImageBuffer(img)

        self.assertIs(
            buf._image_ref, img, "_image_ref should reference the original image"
        )

        self.assertGreater(
            sys.getrefcount(img),
            initial_refcount,
            "ImageBuffer should hold a reference to the image",
        )

        buf_refcount = sys.getrefcount(img)

        # Create memoryview - should increase refcount further (holds ref to buffer)
        mv = memoryview(buf)

        self.assertGreaterEqual(
            sys.getrefcount(img),
            buf_refcount,
            "Memoryview should indirectly maintain image reference",
        )

        # Delete buffer - image should still be alive due to memoryview
        del buf
        gc.collect()

        self.assertGreaterEqual(
            sys.getrefcount(img),
            initial_refcount,
            "Image should remain alive while memoryview exists",
        )

        self.assertEqual(mv.shape, (5, 3))

        # Delete memoryview - now image reference should be released
        del mv
        gc.collect()

        self.assertEqual(
            sys.getrefcount(img),
            initial_refcount,
            "All references should be released after memoryview deletion",
        )

    def test_c_contiguous(self):
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

        self.assertTrue(mv.c_contiguous, "Buffer should be C-contiguous")
        self.assertFalse(mv.f_contiguous, "Buffer should not be Fortran-contiguous")
        self.assertTrue(mv.contiguous, "Buffer should be contiguous")

        # Flatten the memoryview and verify the sequence. The memoryview
        # shape is (7, 5, 3) in numpy order (z, y, x); when flattened, it
        # should be the same sequence as we wrote.
        flat = mv.cast("B")
        flat = flat.cast(mv.format, [math.prod(mv.shape)])

        expected_sequence = list(range(3 * 5 * 7))  # 0 to 104
        actual_sequence = flat.tolist()

        self.assertEqual(
            actual_sequence,
            expected_sequence,
            f"Flattened sequence doesn't match. First 10: {actual_sequence[:10]}, "
            f"Last 10: {actual_sequence[-10:]}",
        )

    def test_no_suboffsets(self):
        """Test that buffer has no suboffsets (simple layout)"""
        img = sitk.Image([3, 5, 7], sitk.sitkInt32)
        buf = ImageBuffer(img)
        mv = memoryview(buf)

        # Note: memoryview doesn't expose suboffsets directly in Python, but
        # we can verify the buffer is contiguous which implies no suboffsets
        self.assertTrue(mv.contiguous, "Buffer should be contiguous (no suboffsets)")


if __name__ == "__main__":
    unittest.main()
