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
import sys
import gc
import SimpleITK as sitk

# Check Python version for buffer protocol support
BUFFER_PROTOCOL_AVAILABLE = sys.version_info >= (3, 12)

# Import numpy if available
try:
    import numpy as np
    NUMPY_AVAILABLE = True
except ImportError:
    NUMPY_AVAILABLE = False
    np = None


# ============================================================================
# __buffer__ Protocol Tests (Python 3.12+)
# ============================================================================

@pytest.mark.skipif(not BUFFER_PROTOCOL_AVAILABLE, reason="Requires Python 3.12+")
class TestBufferProtocol:
    """Tests for Image.__buffer__() method using memoryview"""

    def test_buffer_scalar_2d(self):
        """Test buffer protocol with 2D scalar image"""
        img = sitk.Image([5, 7], sitk.sitkFloat32)
        mv = memoryview(img)

        assert mv.shape == (7, 5), f"Expected shape (7, 5), got {mv.shape}"
        assert mv.format == 'f', f"Expected format 'f', got {mv.format}"
        assert mv.ndim == 2, f"Expected ndim 2, got {mv.ndim}"
        assert mv.readonly, "Buffer should be read-only"
        assert mv.c_contiguous, "Buffer should be C-contiguous"

    def test_buffer_scalar_3d(self):
        """Test buffer protocol with 3D scalar image"""
        img = sitk.Image([3, 5, 7], sitk.sitkInt16)
        mv = memoryview(img)

        assert mv.shape == (7, 5, 3), f"Expected shape (7, 5, 3), got {mv.shape}"
        assert mv.format == 'h', f"Expected format 'h', got {mv.format}"
        assert mv.ndim == 3, f"Expected ndim 3, got {mv.ndim}"
        assert mv.readonly, "Buffer should be read-only"

    def test_buffer_vector_2d(self):
        """Test buffer protocol with 2D vector image"""
        img = sitk.Image([5, 7], sitk.sitkVectorFloat32, 3)
        mv = memoryview(img)

        assert mv.shape == (7, 5, 3), f"Expected shape (7, 5, 3), got {mv.shape}"
        assert mv.format == 'f', f"Expected format 'f', got {mv.format}"
        assert mv.ndim == 3, f"Expected ndim 3, got {mv.ndim}"
        assert mv.readonly, "Buffer should be read-only"

    def test_buffer_vector_1_component(self):
        """Test buffer protocol with vector image having 1 component"""
        img = sitk.Image([4, 6], sitk.sitkVectorFloat64, 1)
        mv = memoryview(img)

        assert mv.shape == (6, 4, 1), f"Expected shape (6, 4, 1), got {mv.shape}"
        assert mv.format == 'd', f"Expected format 'd', got {mv.format}"
        assert mv.ndim == 3, f"Expected ndim 3, got {mv.ndim}"

    def test_buffer_complex(self):
        """Test buffer protocol with complex image"""
        img = sitk.Image([4, 6], sitk.sitkComplexFloat64)
        mv = memoryview(img)

        assert mv.shape == (6, 4), f"Expected shape (6, 4), got {mv.shape}"
        assert mv.format == 'Zd', f"Expected format 'Zd', got {mv.format}"
        assert mv.ndim == 2, f"Expected ndim 2, got {mv.ndim}"
        assert mv.itemsize == 16, f"Expected itemsize 16, got {mv.itemsize}"

    @pytest.mark.parametrize("pixel_type,expected_format", [
        (sitk.sitkUInt8, 'B'),
        (sitk.sitkInt8, 'b'),
        (sitk.sitkUInt16, 'H'),
        (sitk.sitkInt16, 'h'),
        (sitk.sitkUInt32, 'I'),
        (sitk.sitkInt32, 'i'),
        (sitk.sitkUInt64, 'Q'),
        (sitk.sitkInt64, 'q'),
        (sitk.sitkFloat32, 'f'),
        (sitk.sitkFloat64, 'd'),
    ])
    def test_buffer_formats(self, pixel_type, expected_format):
        """Test buffer protocol format strings for all scalar types"""
        img = sitk.Image([3, 5], pixel_type)
        mv = memoryview(img)
        assert mv.format == expected_format, f"Expected format '{expected_format}', got '{mv.format}'"

    def test_buffer_readonly(self):
        """Test that buffer is read-only"""
        img = sitk.Image([3, 5], sitk.sitkFloat32)
        mv = memoryview(img)

        assert mv.readonly, "Buffer should be read-only"
        with pytest.raises(TypeError, match="cannot modify read-only memory"):
            mv[0, 0] = 1.0

    def test_buffer_survives_image_deletion(self):
        """Test that buffer data remains valid after image deletion"""
        img = sitk.Image([3, 5], sitk.sitkFloat32)
        mv = memoryview(img)

        # Store original properties
        original_shape = mv.shape
        original_format = mv.format

        # Delete image - buffer should keep data alive
        del img
        gc.collect()

        # Buffer should still be valid
        assert mv.shape == original_shape
        assert mv.format == original_format

    def test_buffer_strides(self):
        """Test buffer strides are correct for C-contiguous layout"""
        img = sitk.Image([3, 5, 7], sitk.sitkFloat32)
        mv = memoryview(img)

        # For shape (7, 5, 3) with itemsize 4:
        # strides should be (60, 12, 4)
        expected_strides = (60, 12, 4)
        assert mv.strides == expected_strides, f"Expected strides {expected_strides}, got {mv.strides}"

    def test_buffer_multiple_views(self):
        """Test creating multiple memoryviews from same image"""
        img = sitk.Image([3, 5], sitk.sitkInt32)
        mv1 = memoryview(img)
        mv2 = memoryview(img)

        assert mv1.shape == mv2.shape
        assert mv1.format == mv2.format
        assert mv1.strides == mv2.strides


# ============================================================================
# __array_interface__ Tests (requires numpy)
# ============================================================================

@pytest.mark.skipif(not NUMPY_AVAILABLE, reason="Requires numpy")
class TestArrayInterface:
    """Tests for Image.__array_interface__ property"""

    @pytest.fixture
    def disable_buffer_protocol(self):
        """
        Context manager fixture to temporarily disable __buffer__ on Image class

        This forces numpy to use __array_interface__ on Python 3.12+
        """
        original_buffer = None
        if hasattr(sitk.Image, '__buffer__'):
            # Save and temporarily remove __buffer__ from Image class
            original_buffer = sitk.Image.__buffer__
            delattr(sitk.Image, '__buffer__')

        yield  # Test runs here

        # Restore __buffer__ if it was removed
        if original_buffer is not None:
            sitk.Image.__buffer__ = original_buffer

    def test_array_interface_exists(self):
        """Test that __array_interface__ attribute exists"""
        img = sitk.Image([3, 5], sitk.sitkFloat32)
        assert hasattr(img, '__array_interface__'), "Image should have __array_interface__"
        assert isinstance(img.__array_interface__, dict), "__array_interface__ should be a dict"

    def test_array_interface_scalar_2d(self):
        """Test __array_interface__ with 2D scalar image"""
        img = sitk.Image([5, 7], sitk.sitkFloat32)
        iface = img.__array_interface__

        assert iface['shape'] == (7, 5), f"Expected shape (7, 5), got {iface['shape']}"
        assert iface['typestr'] == '|f4', f"Expected typestr '|f4', got {iface['typestr']}"
        assert iface['version'] == 3, f"Expected version 3, got {iface['version']}"
        assert 'data' in iface, "Should have 'data' key"

    def test_array_interface_scalar_3d(self):
        """Test __array_interface__ with 3D scalar image"""
        img = sitk.Image([3, 5, 7], sitk.sitkInt16)
        iface = img.__array_interface__

        assert iface['shape'] == (7, 5, 3), f"Expected shape (7, 5, 3), got {iface['shape']}"
        assert iface['typestr'] == '|i2', f"Expected typestr '|i2', got {iface['typestr']}"

    def test_array_interface_vector_2d(self):
        """Test __array_interface__ with 2D vector image"""
        img = sitk.Image([5, 7], sitk.sitkVectorFloat32, 3)
        iface = img.__array_interface__

        assert iface['shape'] == (7, 5, 3), f"Expected shape (7, 5, 3), got {iface['shape']}"
        assert iface['typestr'] == '|f4', f"Expected typestr '|f4', got {iface['typestr']}"

    def test_array_interface_vector_1_component(self):
        """Test __array_interface__ with vector image having 1 component"""
        img = sitk.Image([4, 6], sitk.sitkVectorFloat64, 1)
        iface = img.__array_interface__

        # Note: Implementation doesn't include component dimension when num_components == 1
        assert iface['shape'] == (6, 4, 1), f"Expected shape (6, 4, 1), got {iface['shape']}"
        assert iface['typestr'] == '|f8', f"Expected typestr '|f8', got {iface['typestr']}"

    def test_array_interface_complex(self):
        """Test __array_interface__ with complex image"""
        img = sitk.Image([4, 6], sitk.sitkComplexFloat64)
        iface = img.__array_interface__

        assert iface['shape'] == (6, 4), f"Expected shape (6, 4), got {iface['shape']}"
        assert iface['typestr'] == '|c16', f"Expected typestr '|c16', got {iface['typestr']}"

    def test_array_interface_strides(self):
        """Test __array_interface__ strides are omitted for C-contiguous data"""
        img = sitk.Image([3, 5, 7], sitk.sitkFloat32)
        iface = img.__array_interface__

        # For C-contiguous arrays, strides can be omitted
        # If present, for shape (7, 5, 3) with itemsize 4, strides should be (60, 12, 4)
        if 'strides' in iface:
            assert iface['strides'] == (60, 12, 4), f"Expected strides (60, 12, 4), got {iface['strides']}"

    def test_numpy_asarray_via_array_interface(self, disable_buffer_protocol):
        """Test numpy.asarray uses __array_interface__ when __buffer__ is disabled"""
        # With __buffer__ temporarily removed, numpy should fall back to __array_interface__
        img = sitk.Image([5, 7], sitk.sitkFloat32)

        # Verify __buffer__ is not available
        assert not hasattr(img, '__buffer__'), "__buffer__ should be disabled for this test"

        # NumPy should now use __array_interface__
        arr = np.asarray(img)

        assert arr.shape == (7, 5), f"Expected shape (7, 5), got {arr.shape}"
        assert arr.dtype == np.float32, f"Expected dtype float32, got {arr.dtype}"
        assert not arr.flags['WRITEABLE'], "Array should be read-only"

    def test_array_interface_readonly(self):
        """Test that __array_interface__ provides read-only data"""
        img = sitk.Image([3, 5], sitk.sitkFloat32)
        iface = img.__array_interface__

        # The 'data' field is a memoryview object
        # NumPy will respect the readonly flag from the buffer protocol
        assert 'data' in iface, "Should have 'data' key"
        data = iface['data']
        assert hasattr(data, 'readonly'), "data should be a memoryview or similar"
        if hasattr(data, 'readonly'):
            assert data.readonly, "data should be read-only"

    def test_array_interface_keeps_image_alive(self):
        """Test that __array_interface__ holds reference to image"""
        img = sitk.Image([3, 5], sitk.sitkFloat32)
        initial_refcount = sys.getrefcount(img)

        # Access __array_interface__ - this creates ImageBuffer internally
        iface = img.__array_interface__

        # Reference count should have increased
        assert sys.getrefcount(img) > initial_refcount, \
            "Image refcount should increase when __array_interface__ is accessed"

    @pytest.mark.parametrize("pixel_type,expected_typestr", [
        (sitk.sitkUInt8, '|u1'),
        (sitk.sitkInt8, '|i1'),
        (sitk.sitkUInt16, '|u2'),
        (sitk.sitkInt16, '|i2'),
        (sitk.sitkUInt32, '|u4'),
        (sitk.sitkInt32, '|i4'),
        (sitk.sitkUInt64, '|u8'),
        (sitk.sitkInt64, '|i8'),
        (sitk.sitkFloat32, '|f4'),
        (sitk.sitkFloat64, '|f8'),
        (sitk.sitkComplexFloat32, '|c8'),
        (sitk.sitkComplexFloat64, '|c16'),
    ])
    def test_array_interface_typestrs(self, pixel_type, expected_typestr):
        """Test __array_interface__ typestr for all scalar types (using native byte order)"""
        img = sitk.Image([3, 5], pixel_type)
        iface = img.__array_interface__
        assert iface['typestr'] == expected_typestr, \
            f"Expected typestr '{expected_typestr}', got '{iface['typestr']}'"


# ============================================================================
# Integration Tests with numpy
# ============================================================================

@pytest.mark.skipif(not NUMPY_AVAILABLE, reason="Requires numpy")
class TestNumpyIntegration:
    """Test interaction between buffer protocol, __array_interface__, and numpy"""

    @pytest.fixture(params=[
        pytest.param("buffer", marks=pytest.mark.skipif(not BUFFER_PROTOCOL_AVAILABLE,
                                                        reason="Requires Python 3.12+")),
        pytest.param("array_interface"),
    ])
    def protocol_mode(self, request):
        """
        Fixture that runs tests with different protocols:
        - Python <3.12: runs once with array_interface
        - Python 3.12+: runs twice, once with buffer and once with array_interface
        """
        mode = request.param

        if mode == "array_interface" and BUFFER_PROTOCOL_AVAILABLE:
            # Temporarily disable __buffer__ to force __array_interface__
            original_buffer = None
            if hasattr(sitk.Image, '__buffer__'):
                original_buffer = sitk.Image.__buffer__
                delattr(sitk.Image, '__buffer__')

            yield mode

            # Restore __buffer__
            if original_buffer is not None:
                sitk.Image.__buffer__ = original_buffer
        else:
            yield mode

    def test_numpy_array_readonly(self, protocol_mode):
        """Test that numpy arrays from SimpleITK images are read-only"""
        img = sitk.Image([3, 5], sitk.sitkFloat32)
        arr = np.asarray(img)

        assert not arr.flags['WRITEABLE'], "Array should be read-only"
        with pytest.raises(ValueError, match="read-only"):
            arr[0, 0] = 1.0

    def test_numpy_array_vector_shape(self, protocol_mode):
        """Test numpy array shape for vector images"""
        img = sitk.Image([3, 5], sitk.sitkVectorFloat32, 4)
        arr = np.asarray(img)

        assert arr.shape == (5, 3, 4), f"Expected shape (5, 3, 4), got {arr.shape}"


        img = sitk.Image([3, 5], sitk.sitkVectorFloat64, 1)
        arr = np.asarray(img)

        assert arr.shape == (5, 3, 1), f"Expected shape (5, 3, 1), got {arr.shape}"

    def test_numpy_array_complex_dtype(self, protocol_mode):
        """Test numpy array dtype for complex images"""
        img = sitk.Image([3, 5], sitk.sitkComplexFloat64)
        arr = np.asarray(img)

        assert arr.dtype == np.complex128, f"Expected dtype complex128, got {arr.dtype}"

    def test_numpy_shares_memory(self, protocol_mode):
        """Test that numpy array shares memory with SimpleITK image"""
        img = sitk.Image([3, 5], sitk.sitkFloat32)
        img.SetPixel([1, 2], 42.0)

        arr = np.asarray(img)

        # Array should reflect the image data (reversed indices due to order)
        assert arr[2, 1] == 42.0, f"Expected value 42.0, got {arr[2, 1]}"

    def test_numpy_copy_vs_view(self, protocol_mode):
        """Test difference between np.asarray (view) and np.array (copy)"""
        img = sitk.Image([3, 5], sitk.sitkFloat32)

        # asarray creates a view
        view = np.asarray(img)

        # array creates a copy
        copy = np.array(img)

        # Both should have same data initially
        assert np.array_equal(view, copy), "View and copy should have same data"

        # Copy should be writeable
        assert copy.flags['WRITEABLE'], "Copy should be writeable"
        assert not view.flags['WRITEABLE'], "View should be read-only"
