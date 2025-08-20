#=========================================================================
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
#==========================================================================*/

# WARNING: This file is copied by CMake. Do not edit manually.

import SimpleITK
import pytest
import tempfile
import subprocess
from pathlib import Path
import sys
import os


@pytest.fixture
def data_finder():
    """Fixture to provide data finder functionality"""
    class DataFinder:
        def __init__(self):
            # Import configured constants
            from conftest_constants import TEST_HARNESS_DATA_DIRECTORY, TEST_HARNESS_TEMP_DIRECTORY

            self.data_directory = Path(TEST_HARNESS_DATA_DIRECTORY)
            self.output_directory = Path(TEST_HARNESS_TEMP_DIRECTORY)
            self._compare_driver = None

        @property
        def compare_driver(self):
            """Lazy property to get the sitkCompareDriver executable from environment variable"""
            if self._compare_driver is None:
                compare_driver_path = os.environ.get('SITK_COMPARE_DRIVER_EXECUTABLE')
                if compare_driver_path:
                    self._compare_driver = Path(compare_driver_path)
                else:
                    raise RuntimeError("SITK_COMPARE_DRIVER_EXECUTABLE environment variable not set. It is automatically set by the CTest environment.")
            return self._compare_driver

        def get_file(self, filename):
            """Find test data file, checking data directory first then fallback locations"""
            primary_path = self.data_directory / filename
            if primary_path.exists():
                return str(primary_path)
            return str(primary_path)

        def get_compare_driver(self):
            """Get the path to the sitkCompareDriver executable"""
            return str(self.compare_driver)

        def get_output_directory(self):
            """Get output directory for temporary files"""
            return str(self.output_directory)

        def get_output_file(self, filename):
            """Get full path for output file in temporary directory"""
            return str(self.output_directory / filename)

        def file_exists(self, filename):
            """Check if file exists (utility method like C++ version)"""
            return Path(filename).exists()

    return DataFinder()



class SimpleITKTestBase:
    """Base class with common test infrastructure for SimpleITK filter tests"""

    def assert_hash_match(self, image, expected_hash, hash_type, test_tag):
        """Assert that image hash matches expected value"""
        hasher = SimpleITK.HashImageFilter()
        if hash_type.upper() == "MD5":
            hasher.SetHashFunction(SimpleITK.HashImageFilter.MD5)
        elif hash_type.upper() == "SHA1":
            hasher.SetHashFunction(SimpleITK.HashImageFilter.SHA1)
        else:
            raise ValueError(f"Unsupported hash type: {hash_type}")

        actual_hash = hasher.Execute(image)
        assert actual_hash == expected_hash, \
            f"{hash_type} hash mismatch in {test_tag}: expected {expected_hash}, got {actual_hash}"

    def extract_slice(self, image):
        """Extract center slice from 3D image, return as-is for 2D"""
        if image.GetDimension() == 3:
            size = list(image.GetSize())
            index = [0, 0, size[2] // 2]  # Center slice
            size[2] = 1
            return SimpleITK.RegionOfInterest(image, size, index)
        return image

    def normalize_and_save(self, image, filename):
        """Normalize image for visualization and save as PNG"""
        norm_image = image

        # Handle different pixel types similar to C++ implementation
        if image.GetPixelIDValue() == SimpleITK.sitkLabelUInt8:
            norm_image = SimpleITK.Cast(image, SimpleITK.sitkUInt8)
        elif image.GetPixelIDValue() == SimpleITK.sitkLabelUInt16:
            norm_image = SimpleITK.Cast(image, SimpleITK.sitkUInt16)
        elif image.GetPixelIDValue() == SimpleITK.sitkLabelUInt32:
            norm_image = SimpleITK.Cast(image, SimpleITK.sitkUInt32)
        elif image.GetPixelIDValue() == SimpleITK.sitkLabelUInt64:
            norm_image = SimpleITK.Cast(image, SimpleITK.sitkUInt64)
        elif (image.GetPixelIDValue() == SimpleITK.sitkComplexFloat64 or
              image.GetPixelIDValue() == SimpleITK.sitkComplexFloat32):
            norm_image = SimpleITK.ComplexToModulus(image)
        elif image.GetNumberOfComponentsPerPixel() != 1:
            # Use magnitude for vector images
            norm_image = SimpleITK.VectorMagnitude(image)

        # Extract center slice
        norm_image = self.extract_slice(norm_image)

        # Rescale to 0-255 and convert to uint8
        out_image = SimpleITK.RescaleIntensity(norm_image, 0, 255)
        out_image = SimpleITK.Cast(out_image, SimpleITK.sitkUInt8)

        SimpleITK.WriteImage(out_image, filename)

    def assert_image_tolerance_match(self, test_filename, baseline_filename, tolerance, test_tag, data_finder):
        """Assert that test image matches baseline within tolerance using sitkCompareDriver executable"""

        # Build command for sitkCompareDriver
        compare_driver = data_finder.get_compare_driver()
        cmd = [data_finder.get_compare_driver(),
                "--compare",
                str(test_filename), str(baseline_filename), str(tolerance)]

        try:
            # Run sitkCompareDriver
            result = subprocess.run(cmd, capture_output=False,  timeout=300)

            # Check exit code
            if result.returncode != 0:
                pytest.fail(f"Image comparison failed in {test_tag}: sitkCompareDriver returned {result.returncode}")

        except subprocess.TimeoutExpired:
            pytest.fail(f"Image comparison timed out in {test_tag}")
        except Exception as e:
            pytest.fail(f"Failed to run sitkCompareDriver for {test_tag}: {e}")
