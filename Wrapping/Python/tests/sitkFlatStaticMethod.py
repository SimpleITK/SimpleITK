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
import pytest
import SimpleITK as sitk
from pathlib import Path


@pytest.fixture
def test_data(tmp_path):
    """Create a test directory with a DICOM file for testing."""
    img = sitk.Image([10, 10], sitk.sitkInt16)
    test_dcm_file = tmp_path / "test.dcm"
    sitk.WriteImage(img, test_dcm_file)

    # Return a dictionary with the test data
    return {"test_dir": tmp_path, "test_dcm_file": test_dcm_file}

def test_ProcessObject():
    sitk.ProcessObject_GlobalDefaultDebugOff()
    sitk.ProcessObject_GlobalDefaultDebugOn()
    assert sitk.ProcessObject_GetGlobalDefaultDebug()
    sitk.ProcessObject_SetGlobalDefaultDebug(False)
    assert not sitk.ProcessObject_GetGlobalDefaultDebug()

    sitk.ProcessObject_GlobalWarningDisplayOff()
    sitk.ProcessObject_GlobalWarningDisplayOn()
    assert sitk.ProcessObject_GetGlobalWarningDisplay()
    sitk.ProcessObject_SetGlobalWarningDisplay(False)
    assert not sitk.ProcessObject_GetGlobalWarningDisplay()

    sitk.ProcessObject_SetGlobalDefaultCoordinateTolerance(2.0e-6)
    assert sitk.ProcessObject_GetGlobalDefaultCoordinateTolerance() == 2.0e-6

    sitk.ProcessObject_SetGlobalDefaultDirectionTolerance(2.2e-6)
    assert sitk.ProcessObject_GetGlobalDefaultDirectionTolerance() == 2.2e-6

    sitk.ProcessObject_SetGlobalDefaultNumberOfThreads(2)
    assert sitk.ProcessObject_GetGlobalDefaultNumberOfThreads() == 2

def test_IO(test_data):
    sitk.ImageSeriesReader_GetGDCMSeriesIDs(str(test_data["test_dir"]))
    sitk.ImageReaderBase_GetImageIOFromFileName(str(test_data["test_dcm_file"]))

def test_Version():
    # Just test one method here
    sitk.Version_VersionString()
