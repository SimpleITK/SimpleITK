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

import sys
import gc
import unittest
import contextlib
import SimpleITK as sitk

# Check Python version for buffer protocol support
BUFFER_PROTOCOL_AVAILABLE = sys.version_info >= (3, 12)

try:
    import numpy as np

    NUMPY_AVAILABLE = True
except ImportError:
    NUMPY_AVAILABLE = False
    np = None


@contextlib.contextmanager
def _buffer_protocol_disabled():
    """Temporarily remove __buffer__ from the Image class so numpy falls back
    to __array_interface__."""
    original_buffer = None
    if hasattr(sitk.Image, "__buffer__"):
        original_buffer = sitk.Image.__buffer__
        delattr(sitk.Image, "__buffer__")
    try:
        yield
    finally:
        if original_buffer is not None:
            sitk.Image.__buffer__ = original_buffer


# ============================================================================
# __buffer__ Protocol Tests (Python 3.12+)
# ============================================================================


@unittest.skipUnless(BUFFER_PROTOCOL_AVAILABLE, "Requires Python 3.12+")
class TestBufferProtocol(unittest.TestCase):
    """Tests for Image.__buffer__() method using memoryview"""

    def test_buffer_scalar_2d(self):
        """Test buffer protocol with 2D scalar image"""
        img = sitk.Image([5, 7], sitk.sitkFloat32)
        mv = memoryview(img)

        self.assertEqual(mv.shape, (7, 5), f"Expected shape (7, 5), got {mv.shape}")
        self.assertEqual(mv.format, "f", f"Expected format 'f', got {mv.format}")
        self.assertEqual(mv.ndim, 2, f"Expected ndim 2, got {mv.ndim}")
        self.assertTrue(mv.readonly, "Buffer should be read-only")
        self.assertTrue(mv.c_contiguous, "Buffer should be C-contiguous")

    def test_buffer_scalar_3d(self):
        """Test buffer protocol with 3D scalar image"""
        img = sitk.Image([3, 5, 7], sitk.sitkInt16)
        mv = memoryview(img)

        self.assertEqual(
            mv.shape, (7, 5, 3), f"Expected shape (7, 5, 3), got {mv.shape}"
        )
        self.assertEqual(mv.format, "h", f"Expected format 'h', got {mv.format}")
        self.assertEqual(mv.ndim, 3, f"Expected ndim 3, got {mv.ndim}")
        self.assertTrue(mv.readonly, "Buffer should be read-only")

    def test_buffer_vector_2d(self):
        """Test buffer protocol with 2D vector image"""
        img = sitk.Image([5, 7], sitk.sitkVectorFloat32, 3)
        mv = memoryview(img)

        self.assertEqual(
            mv.shape, (7, 5, 3), f"Expected shape (7, 5, 3), got {mv.shape}"
        )
        self.assertEqual(mv.format, "f", f"Expected format 'f', got {mv.format}")
        self.assertEqual(mv.ndim, 3, f"Expected ndim 3, got {mv.ndim}")
        self.assertTrue(mv.readonly, "Buffer should be read-only")

    def test_buffer_vector_1_component(self):
        """Test buffer protocol with vector image having 1 component"""
        img = sitk.Image([4, 6], sitk.sitkVectorFloat64, 1)
        mv = memoryview(img)

        self.assertEqual(
            mv.shape, (6, 4, 1), f"Expected shape (6, 4, 1), got {mv.shape}"
        )
        self.assertEqual(mv.format, "d", f"Expected format 'd', got {mv.format}")
        self.assertEqual(mv.ndim, 3, f"Expected ndim 3, got {mv.ndim}")

    def test_buffer_complex(self):
        """Test buffer protocol with complex image"""
        img = sitk.Image([4, 6], sitk.sitkComplexFloat64)
        mv = memoryview(img)

        self.assertEqual(mv.shape, (6, 4), f"Expected shape (6, 4), got {mv.shape}")
        self.assertEqual(mv.format, "Zd", f"Expected format 'Zd', got {mv.format}")
        self.assertEqual(mv.ndim, 2, f"Expected ndim 2, got {mv.ndim}")
        self.assertEqual(mv.itemsize, 16, f"Expected itemsize 16, got {mv.itemsize}")

    def test_buffer_formats(self):
        """Test buffer protocol format strings for all scalar types"""
        cases = [
            (sitk.sitkUInt8, "B"),
            (sitk.sitkInt8, "b"),
            (sitk.sitkUInt16, "H"),
            (sitk.sitkInt16, "h"),
            (sitk.sitkUInt32, "I"),
            (sitk.sitkInt32, "i"),
            (sitk.sitkUInt64, "Q"),
            (sitk.sitkInt64, "q"),
            (sitk.sitkFloat32, "f"),
            (sitk.sitkFloat64, "d"),
        ]
        for pixel_type, expected_format in cases:
            with self.subTest(pixel_type=pixel_type):
                img = sitk.Image([3, 5], pixel_type)
                mv = memoryview(img)
                self.assertEqual(
                    mv.format,
                    expected_format,
                    f"Expected format '{expected_format}', got '{mv.format}'",
                )

    def test_buffer_readonly(self):
        """Test that buffer is read-only"""
        img = sitk.Image([3, 5], sitk.sitkFloat32)
        mv = memoryview(img)

        self.assertTrue(mv.readonly, "Buffer should be read-only")
        with self.assertRaisesRegex(TypeError, "cannot modify read-only memory"):
            mv[0, 0] = 1.0

    def test_buffer_survives_image_deletion(self):
        """Test that buffer data remains valid after image deletion"""
        img = sitk.Image([3, 5], sitk.sitkFloat32)
        mv = memoryview(img)

        original_shape = mv.shape
        original_format = mv.format

        # Delete image - buffer should keep data alive
        del img
        gc.collect()

        self.assertEqual(mv.shape, original_shape)
        self.assertEqual(mv.format, original_format)

    def test_buffer_strides(self):
        """Test buffer strides are correct for C-contiguous layout"""
        img = sitk.Image([3, 5, 7], sitk.sitkFloat32)
        mv = memoryview(img)

        # For shape (7, 5, 3) with itemsize 4: strides should be (60, 12, 4)
        expected_strides = (60, 12, 4)
        self.assertEqual(
            mv.strides,
            expected_strides,
            f"Expected strides {expected_strides}, got {mv.strides}",
        )

    def test_buffer_multiple_views(self):
        """Test creating multiple memoryviews from same image"""
        img = sitk.Image([3, 5], sitk.sitkInt32)
        mv1 = memoryview(img)
        mv2 = memoryview(img)

        self.assertEqual(mv1.shape, mv2.shape)
        self.assertEqual(mv1.format, mv2.format)
        self.assertEqual(mv1.strides, mv2.strides)


# ============================================================================
# __array_interface__ Tests (requires numpy)
# ============================================================================


@unittest.skipUnless(NUMPY_AVAILABLE, "Requires numpy")
class TestArrayInterface(unittest.TestCase):
    """Tests for Image.__array_interface__ property"""

    def test_array_interface_exists(self):
        """Test that __array_interface__ attribute exists"""
        img = sitk.Image([3, 5], sitk.sitkFloat32)
        self.assertTrue(
            hasattr(img, "__array_interface__"), "Image should have __array_interface__"
        )
        self.assertIsInstance(
            img.__array_interface__, dict, "__array_interface__ should be a dict"
        )

    def test_array_interface_scalar_2d(self):
        """Test __array_interface__ with 2D scalar image"""
        img = sitk.Image([5, 7], sitk.sitkFloat32)
        iface = img.__array_interface__

        self.assertEqual(
            iface["shape"], (7, 5), f"Expected shape (7, 5), got {iface['shape']}"
        )
        self.assertEqual(
            iface["typestr"],
            "|f4",
            f"Expected typestr '|f4', got {iface['typestr']}",
        )
        self.assertEqual(iface["version"], 3, f"Expected version 3, got {iface['version']}")
        self.assertIn("data", iface, "Should have 'data' key")

    def test_array_interface_scalar_3d(self):
        """Test __array_interface__ with 3D scalar image"""
        img = sitk.Image([3, 5, 7], sitk.sitkInt16)
        iface = img.__array_interface__

        self.assertEqual(
            iface["shape"], (7, 5, 3), f"Expected shape (7, 5, 3), got {iface['shape']}"
        )
        self.assertEqual(
            iface["typestr"],
            "|i2",
            f"Expected typestr '|i2', got {iface['typestr']}",
        )

    def test_array_interface_vector_2d(self):
        """Test __array_interface__ with 2D vector image"""
        img = sitk.Image([5, 7], sitk.sitkVectorFloat32, 3)
        iface = img.__array_interface__

        self.assertEqual(
            iface["shape"], (7, 5, 3), f"Expected shape (7, 5, 3), got {iface['shape']}"
        )
        self.assertEqual(
            iface["typestr"],
            "|f4",
            f"Expected typestr '|f4', got {iface['typestr']}",
        )

    def test_array_interface_vector_1_component(self):
        """Test __array_interface__ with vector image having 1 component"""
        img = sitk.Image([4, 6], sitk.sitkVectorFloat64, 1)
        iface = img.__array_interface__

        # Note: Implementation doesn't include component dimension when num_components == 1
        self.assertEqual(
            iface["shape"], (6, 4, 1), f"Expected shape (6, 4, 1), got {iface['shape']}"
        )
        self.assertEqual(
            iface["typestr"],
            "|f8",
            f"Expected typestr '|f8', got {iface['typestr']}",
        )

    def test_array_interface_complex(self):
        """Test __array_interface__ with complex image"""
        img = sitk.Image([4, 6], sitk.sitkComplexFloat64)
        iface = img.__array_interface__

        self.assertEqual(
            iface["shape"], (6, 4), f"Expected shape (6, 4), got {iface['shape']}"
        )
        self.assertEqual(
            iface["typestr"],
            "|c16",
            f"Expected typestr '|c16', got {iface['typestr']}",
        )

    def test_array_interface_strides(self):
        """Test __array_interface__ strides are omitted for C-contiguous data"""
        img = sitk.Image([3, 5, 7], sitk.sitkFloat32)
        iface = img.__array_interface__

        # For C-contiguous arrays, strides can be omitted. If present, for
        # shape (7, 5, 3) with itemsize 4, strides should be (60, 12, 4)
        if "strides" in iface:
            self.assertEqual(
                iface["strides"],
                (60, 12, 4),
                f"Expected strides (60, 12, 4), got {iface['strides']}",
            )

    def test_numpy_asarray_via_array_interface(self):
        """Test numpy.asarray uses __array_interface__ when __buffer__ is disabled"""
        with _buffer_protocol_disabled():
            img = sitk.Image([5, 7], sitk.sitkFloat32)

            self.assertFalse(
                hasattr(img, "__buffer__"), "__buffer__ should be disabled for this test"
            )

            # NumPy should now use __array_interface__
            arr = np.asarray(img)

            self.assertEqual(
                arr.shape, (7, 5), f"Expected shape (7, 5), got {arr.shape}"
            )
            self.assertEqual(
                arr.dtype, np.float32, f"Expected dtype float32, got {arr.dtype}"
            )
            self.assertFalse(arr.flags["WRITEABLE"], "Array should be read-only")

    def test_array_interface_readonly(self):
        """Test that __array_interface__ provides read-only data"""
        img = sitk.Image([3, 5], sitk.sitkFloat32)
        iface = img.__array_interface__

        # The 'data' field is a memoryview object. NumPy will respect the
        # readonly flag from the buffer protocol
        self.assertIn("data", iface, "Should have 'data' key")
        data = iface["data"]
        self.assertTrue(hasattr(data, "readonly"), "data should be a memoryview or similar")
        if hasattr(data, "readonly"):
            self.assertTrue(data.readonly, "data should be read-only")

    def test_array_interface_keeps_image_alive(self):
        """Test that __array_interface__ holds reference to image"""
        img = sitk.Image([3, 5], sitk.sitkFloat32)
        initial_refcount = sys.getrefcount(img)

        # Access __array_interface__ - this creates ImageBuffer internally
        iface = img.__array_interface__

        self.assertGreater(
            sys.getrefcount(img),
            initial_refcount,
            "Image refcount should increase when __array_interface__ is accessed",
        )

    def test_array_interface_typestrs(self):
        """Test __array_interface__ typestr for all scalar types (using native byte order)"""
        cases = [
            (sitk.sitkUInt8, "|u1"),
            (sitk.sitkInt8, "|i1"),
            (sitk.sitkUInt16, "|u2"),
            (sitk.sitkInt16, "|i2"),
            (sitk.sitkUInt32, "|u4"),
            (sitk.sitkInt32, "|i4"),
            (sitk.sitkUInt64, "|u8"),
            (sitk.sitkInt64, "|i8"),
            (sitk.sitkFloat32, "|f4"),
            (sitk.sitkFloat64, "|f8"),
            (sitk.sitkComplexFloat32, "|c8"),
            (sitk.sitkComplexFloat64, "|c16"),
        ]
        for pixel_type, expected_typestr in cases:
            with self.subTest(pixel_type=pixel_type):
                img = sitk.Image([3, 5], pixel_type)
                iface = img.__array_interface__
                self.assertEqual(
                    iface["typestr"],
                    expected_typestr,
                    f"Expected typestr '{expected_typestr}', got '{iface['typestr']}'",
                )


# ============================================================================
# Integration Tests with numpy
# ============================================================================


@unittest.skipUnless(NUMPY_AVAILABLE, "Requires numpy")
class TestNumpyIntegration(unittest.TestCase):
    """Test interaction between buffer protocol, __array_interface__, and numpy"""

    def _protocol_modes(self):
        """Python <3.12: only array_interface. Python 3.12+: both buffer and
        array_interface."""
        modes = ["array_interface"]
        if BUFFER_PROTOCOL_AVAILABLE:
            modes.append("buffer")
        return modes

    @contextlib.contextmanager
    def _mode(self, mode):
        if mode == "array_interface" and BUFFER_PROTOCOL_AVAILABLE:
            with _buffer_protocol_disabled():
                yield
        else:
            yield

    def test_numpy_array_readonly(self):
        """Test that numpy arrays from SimpleITK images are read-only"""
        for mode in self._protocol_modes():
            with self.subTest(mode=mode), self._mode(mode):
                img = sitk.Image([3, 5], sitk.sitkFloat32)
                arr = np.asarray(img)

                self.assertFalse(arr.flags["WRITEABLE"], "Array should be read-only")
                with self.assertRaisesRegex(ValueError, "read-only"):
                    arr[0, 0] = 1.0

    def test_numpy_array_vector_shape(self):
        """Test numpy array shape for vector images"""
        for mode in self._protocol_modes():
            with self.subTest(mode=mode), self._mode(mode):
                img = sitk.Image([3, 5], sitk.sitkVectorFloat32, 4)
                arr = np.asarray(img)

                self.assertEqual(
                    arr.shape, (5, 3, 4), f"Expected shape (5, 3, 4), got {arr.shape}"
                )

                img = sitk.Image([3, 5], sitk.sitkVectorFloat64, 1)
                arr = np.asarray(img)

                self.assertEqual(
                    arr.shape, (5, 3, 1), f"Expected shape (5, 3, 1), got {arr.shape}"
                )

    def test_numpy_array_complex_dtype(self):
        """Test numpy array dtype for complex images"""
        for mode in self._protocol_modes():
            with self.subTest(mode=mode), self._mode(mode):
                img = sitk.Image([3, 5], sitk.sitkComplexFloat64)
                arr = np.asarray(img)

                self.assertEqual(
                    arr.dtype,
                    np.complex128,
                    f"Expected dtype complex128, got {arr.dtype}",
                )

    def test_numpy_shares_memory(self):
        """Test that numpy array shares memory with SimpleITK image"""
        for mode in self._protocol_modes():
            with self.subTest(mode=mode), self._mode(mode):
                img = sitk.Image([3, 5], sitk.sitkFloat32)
                img.SetPixel([1, 2], 42.0)

                arr = np.asarray(img)

                # Array should reflect the image data (reversed indices due to order)
                self.assertEqual(
                    arr[2, 1], 42.0, f"Expected value 42.0, got {arr[2, 1]}"
                )

    def test_numpy_copy_vs_view(self):
        """Test difference between np.asarray (view) and np.array (copy)"""
        for mode in self._protocol_modes():
            with self.subTest(mode=mode), self._mode(mode):
                img = sitk.Image([3, 5], sitk.sitkFloat32)

                # asarray creates a view
                view = np.asarray(img)

                # array creates a copy
                copy = np.array(img)

                self.assertTrue(
                    np.array_equal(view, copy), "View and copy should have same data"
                )

                self.assertTrue(copy.flags["WRITEABLE"], "Copy should be writeable")
                self.assertFalse(view.flags["WRITEABLE"], "View should be read-only")


if __name__ == "__main__":
    unittest.main()
