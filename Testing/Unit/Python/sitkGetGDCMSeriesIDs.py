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

import SimpleITK as sitk
import pytest
from pathlib import Path


@pytest.fixture
def test_dir(tmp_path):
    """Fixture providing a temporary directory for test outputs"""
    return tmp_path


def create_study_images(test_dir: Path, studyUID: str, number_of_series: int, number_images_per_series: int) -> list[str]:
    """Create a set of DICOM images for testing.

    Args:
        test_dir: Directory to write the DICOM files
        studyUID: Study UID to use for the images
        number_of_series: Number of series to create
        number_images_per_series: Number of images in each series

    Returns:
        list[str]: List of Series UIDs created
    """
    writer = sitk.ImageFileWriter()
    # Use the study/series/frame of reference information given in the meta-data
    # dictionary and not the automatically generated information from the file IO
    writer.KeepOriginalImageUIDOn()
    series_uids = []
    z_spacing = 0.5

    for i in range(number_of_series):
        seriesUID = f"1.2.826.0.1.3680043.2.1125.{studyUID}{i + 1}.1"
        series_uids.append(seriesUID)

        for j in range(number_images_per_series):
            instance_number = str(j + 1)

            # Create image with incrementing intensity
            image = sitk.Image([2, 2, 1], sitk.sitkInt16) + j
            image.SetOrigin([0, 0, j * z_spacing])

            # Set DICOM metadata
            image.SetMetaData("0020|000e", seriesUID)  # Series Instance UID
            image.SetMetaData("0020,000d", studyUID)   # Study Instance UID
            image.SetMetaData("0020|0013", instance_number)  # Instance Number

            # Write DICOM file
            filepath = test_dir / f"{studyUID}_{seriesUID}_{j}.dcm"
            writer.SetFileName(str(filepath))
            writer.Execute(image)

    return series_uids


@pytest.mark.parametrize("num_studies,num_series,num_images", [
    (0, 0, 0),   # Empty study
    (1, 1, 2),   # Single study, single series, two images
    (1, 2, 2),   # Single study, two series, two images each
    (2, 1, 2),   # Two studies, single series each, two images
    (3, 2, 3),   # Three studies, two series each, three images
])
def test_getgdcmseries(test_dir, num_studies, num_series, num_images):
    """Test the ImageSeriesReader_GetGDCMSeriesIDs method with various study configurations.

    This test verifies that GetGDCMSeriesIDs correctly identifies all DICOM series
    in a directory containing multiple studies, series, and images.

    Args:
        test_dir: pytest fixture providing temporary directory
        num_studies: Number of studies to create
        num_series: Number of series per study
        num_images: Number of images per series
    """
    # Create test images and collect all series UIDs
    expected_series = []
    for i in range(num_studies):
        study_series = create_study_images(
            test_dir,
            str(i + 1),
            num_series,
            num_images
        )
        expected_series.extend(study_series)

    # Get series IDs from directory
    found_series = sitk.ImageSeriesReader.GetGDCMSeriesIDs(str(test_dir))

    # Verify all expected series were found, regardless of order
    assert sorted(expected_series) == sorted(found_series), \
        "Found series IDs do not match expected series IDs"
