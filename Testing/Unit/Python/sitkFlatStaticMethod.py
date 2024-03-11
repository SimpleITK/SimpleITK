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
import unittest
import tempfile
import shutil
import SimpleITK as sitk
from pathlib import Path


class FlatStatic(unittest.TestCase):

    def setUp(self):
        # Create a temporary directory for output files
        self.test_dir = Path(tempfile.mkdtemp())

        img = sitk.Image([10, 10], sitk.sitkInt16)
        self.test_dcm_file = self.test_dir / "test.dcm"
        sitk.WriteImage(img, self.test_dcm_file)

    def tearDown(self):
        # Delete the temporary directory and files contained within. Perhaps if tests fail then the output should  stick
        # around to debug the problem
        shutil.rmtree(self.test_dir)

    def test_ProcessObject(self):
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
        self.assertEqual(
            sitk.ProcessObject_GetGlobalDefaultCoordinateTolerance(), 2.0e-6
        )

        sitk.ProcessObject_SetGlobalDefaultDirectionTolerance(2.2e-6)
        self.assertEqual(
            sitk.ProcessObject_GetGlobalDefaultDirectionTolerance(), 2.2e-6
        )

        sitk.ProcessObject_SetGlobalDefaultNumberOfThreads(2)
        self.assertEqual(sitk.ProcessObject_GetGlobalDefaultNumberOfThreads(), 2)

    def test_IO(self):
        sitk.ImageSeriesReader_GetGDCMSeriesIDs(str(self.test_dir))

        sitk.ImageReaderBase_GetImageIOFromFileName(str(self.test_dcm_file))

    def test_Version(self):
        # Just test one method here
        sitk.Version_VersionString()


if __name__ == "__main__":
    unittest.main()
