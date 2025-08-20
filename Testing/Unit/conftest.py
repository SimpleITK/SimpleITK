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
import math
from pathlib import Path
import sys



@pytest.fixture
def data_finder():
    """Fixture to provide data finder functionality"""
    class DataFinder:
        def __init__(self):# Import configured constants
            from conftest_constants import TEST_HARNESS_DATA_DIRECTORY, TEST_HARNESS_TEMP_DIRECTORY, SITK_COMPARE_DRIVER

            self.data_directory = Path(TEST_HARNESS_DATA_DIRECTORY)
            self.output_directory = Path(TEST_HARNESS_TEMP_DIRECTORY)
            self.compare_driver = Path(SITK_COMPARE_DRIVER)

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

    def compute_image_difference(self, test_image, baseline_image):
        """Compute RMS difference between two images"""
        print(f"Comparing {baseline_image} with {test_image}")
        # Verify same dimensions
        if (baseline_image.GetSize() != test_image.GetSize()):
            raise ValueError("Image dimensions are different")

        try:
            # Compute squared difference based on image type
            if (baseline_image.GetPixelID() == SimpleITK.sitkComplexFloat32 or
                baseline_image.GetPixelID() == SimpleITK.sitkComplexFloat64):
                # Complex image handling
                diff = SimpleITK.Subtract(test_image, baseline_image)
                conj = SimpleITK.RealAndImaginaryToComplex(
                    SimpleITK.ComplexToReal(diff),
                    SimpleITK.Multiply(SimpleITK.ComplexToImaginary(diff), -1.0)
                )
                diff_squared = SimpleITK.ComplexToReal(SimpleITK.Multiply(diff, conj))
            elif baseline_image.GetNumberOfComponentsPerPixel() > 1:
                # Vector image handling
                diff = SimpleITK.Subtract(
                    SimpleITK.Cast(test_image, SimpleITK.sitkVectorFloat32),
                    SimpleITK.Cast(baseline_image, SimpleITK.sitkVectorFloat32)
                )

                # Sum of squared components
                diff_squared = SimpleITK.Pow(SimpleITK.VectorIndexSelectionCast(diff, 0), 2.0)
                for i in range(1, diff.GetNumberOfComponentsPerPixel()):
                    temp = SimpleITK.Pow(SimpleITK.VectorIndexSelectionCast(diff, i), 2.0)
                    diff_squared = SimpleITK.Add(temp, diff_squared)

                diff_squared = SimpleITK.Divide(diff_squared, diff.GetNumberOfComponentsPerPixel())
            else:
                # Scalar image handling
                diff = SimpleITK.Cast(test_image, SimpleITK.sitkFloat32) - SimpleITK.Cast(baseline_image, SimpleITK.sitkFloat32)

                diff_squared = diff*diff
            # Compute RMS
            stats = SimpleITK.StatisticsImageFilter()
            stats.Execute(diff_squared)
            print(f"{stats}")

            rms = math.sqrt(stats.GetMean())

            # If rms is nan then 0 will be returned
            if rms >= 0.0:
                return rms, diff_squared
            return 0.0, diff_squared

        except Exception as e:
            print(f"Failed to compute image difference: {e}", file=sys.stderr)
            return -1, None

    def assert_image_tolerance_match(self, test_image, baseline_filename, tolerance, test_tag, data_finder):
        """Assert that test image matches baseline within tolerance"""
        # Extract center slice for comparison
        test_slice = self.extract_slice(test_image)

        # Look for baseline file
        baseline_path = data_finder.get_file(f"Baseline/{baseline_filename}")

        if not Path(baseline_path).exists():
            # Create new baseline if it doesn't exist
            output_dir = data_finder.get_output_directory()
            newbaseline_dir = Path(output_dir) / "Newbaseline"
            newbaseline_dir.mkdir(parents=True, exist_ok=True)
            new_baseline = newbaseline_dir / baseline_filename
            SimpleITK.WriteImage(test_slice, str(new_baseline))
            pytest.fail(f"Baseline does not exist, wrote {new_baseline}\\ncp {new_baseline} {baseline_path}")

        # Find best matching baseline (handle multiple numbered baselines)
        baseline_files = [baseline_path]
        x = 0
        while True:
            x += 1
            numbered_baseline = baseline_path.replace('.nrrd', f'.{x}.nrrd')
            numbered_path = data_finder.get_file(f"Baseline/{Path(numbered_baseline).name}")
            if Path(numbered_path).exists():
                baseline_files.append(numbered_path)
            else:
                break

        best_rms = float('inf')
        best_baseline = baseline_files[0]

        # Test against all baselines and find the best match
        for baseline_file in baseline_files:
            try:
                baseline = SimpleITK.ReadImage(baseline_file)
                rms, _ = self.compute_image_difference(test_slice, baseline)

                if rms >= 0.0 and rms < best_rms:
                    best_baseline = baseline_file
                    best_rms = rms

            except Exception as e:
                pytest.fail(f"Failed to load baseline image {baseline_file}: {e}")

        # Report measurement for dashboard
        short_filename = Path(baseline_filename).name
        print(f'<DartMeasurement name="RMSEDifference {short_filename}" type="numeric/float">{best_rms}</DartMeasurement>')

        if best_rms > abs(tolerance):
            # Generate detailed error report
            baseline = SimpleITK.ReadImage(best_baseline)
            rms, diff_squared = self.compute_image_difference(test_slice, baseline)

            output_dir = Path(data_finder.get_output_directory())
            output_dir.mkdir(parents=True, exist_ok=True)

            # Save diagnostic images
            volume_name = output_dir / f"{short_filename}"
            SimpleITK.WriteImage(test_slice, str(volume_name))

            expected_png = output_dir / f"{short_filename}_Expected.png"
            actual_png = output_dir / f"{short_filename}_Actual.png"
            diff_png = output_dir / f"{short_filename}_Difference.png"

            try:
                self.normalize_and_save(baseline, str(expected_png))
                self.normalize_and_save(test_slice, str(actual_png))


                # Report files to dashboard
                print(f'<DartMeasurementFile name="ExpectedImage" type="image/png">{expected_png}</DartMeasurementFile>')
                print(f'<DartMeasurementFile name="ActualImage" type="image/png">{actual_png}</DartMeasurementFile>')
                print(f'<DartMeasurementFile name="DifferenceImage" type="image/png">{diff_png}</DartMeasurementFile>')

                # Report difference statistics
                if diff_squared is not None:
                    diff_stats = SimpleITK.StatisticsImageFilter()
                    diff_stats.Execute(SimpleITK.Sqrt(diff_squared))
                    print(f'<DartMeasurement name="DifferenceImage Minimum" type="numeric/double">{diff_stats.GetMinimum()}</DartMeasurement>')
                    print(f'<DartMeasurement name="DifferenceImage Maximum" type="numeric/double">{diff_stats.GetMaximum()}</DartMeasurement>')
                    print(f'<DartMeasurement name="DifferenceImage Mean" type="numeric/double">{diff_stats.GetMean()}</DartMeasurement>')


            except Exception as e:
                print(f"Exception encountered while trying to normalize and save images for dashboard: {e}")

            print(f'<DartMeasurement name="RMSEDifference" type="numeric/float">{rms}</DartMeasurement>')
            print(f'<DartMeasurement name="Tolerance" type="numeric/float">{tolerance}</DartMeasurement>')

            pytest.fail(f"Image comparison failed in {test_tag}: RMS difference {rms} exceeds tolerance {tolerance}")
