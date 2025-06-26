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
import pytest
from pathlib import Path


import SimpleITK as sitk
from multiprocessing.pool import ThreadPool


def create_data(tmp_path, img_extension, img_type):
    """Method to create the many temporary images for reading."""
    n = 64
    s = 128
    t = img_type

    files = []

    for i in range(0, n):
        img = sitk.GaussianSource(t, [s, s], mean=[256 * (i + 1)] * 2)
        fname = tmp_path / f"g_{i}.{img_extension}"
        files.append(str(fname))
        sitk.WriteImage(img, files[-1])

    return files


def threaded_read_test(files, expected_hash):
    """Reads a list of files with thread parallelism, and verifies the hash of the resulting volume."""
    p = ThreadPool()
    img = sitk.JoinSeries(p.map(sitk.ReadImage, files))
    assert img.GetSize()[2] == len(files)
    assert sitk.Hash(img) == expected_hash


# Test parameters: (extension, expected hash, image type)
test_parameters = [
    ("jpg", "44fac4bedde4df04b9572ac665d3ac2c5cd00c7d", sitk.sitkUInt8),
    ("tiff", "ba713b819c1202dcb0d178df9d2b3222ba1bba44", sitk.sitkUInt16),
    ("png", "ba713b819c1202dcb0d178df9d2b3222ba1bba44", sitk.sitkUInt16),
    ("nii", "7b91dbdc56c5781edf6c8847b4aa6965566c5c75", sitk.sitkUInt32),
    ("mha", "7b91dbdc56c5781edf6c8847b4aa6965566c5c75", sitk.sitkUInt32),
]


@pytest.mark.parametrize("img_extension,expected_hash,img_type", test_parameters)
def test_threaded_read(tmp_path, img_extension, expected_hash, img_type):
    """Test thread concurrent reading of images in various formats."""
    files = create_data(tmp_path, img_extension, img_type)
    files *= 64
    threaded_read_test(files, expected_hash)
