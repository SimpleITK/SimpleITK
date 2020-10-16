#! /usr/bin/env python

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
# ===========================================================================

import unittest
import os

import SimpleITK as sitk


class ExternalViewerTest(unittest.TestCase):
    """Test external viewer launch"""

    IMG = None

    @classmethod
    def setUpClass(cls):
        ExternalViewerTest.IMG = sitk.GaussianSource()
        this_dir = os.path.dirname(os.path.abspath(__file__))

        cmd = 'python ' + this_dir + '/dummy_viewer.py'

        os.environ['SITK_SHOW_COMMAND'] = cmd

    def test_show(self):
        print("\n\nFirst Show Test")
        print("Trying command: ", os.environ['SITK_SHOW_COMMAND'])
        fail = False
        try:
            sitk.Show(ExternalViewerTest.IMG, debugOn=True)
        except BaseException:
            fail = True
        if fail:
            self.fail("Show failed for command " +
                      os.environ['SITK_SHOW_COMMAND'])

    def test_show2(self):
        """Show2 test should work even though we set SITK_SHOW_COMMAND to
        something else, since that var is only read at the beginning.  This set
        is ignored."""
        print("\n\nSecond Show Test")
        os.environ['SITK_SHOW_COMMAND'] = 'none'
        fail = False
        try:
            sitk.Show(ExternalViewerTest.IMG, debugOn=True)
        except BaseException:
            fail = True
        if fail:
            self.fail("Show failed for command " +
                      os.environ['SITK_SHOW_COMMAND'])

    def test_image_viewer(self):
        print("\n\nBasic Image Viewer Test")

        try:
            viewer = sitk.ImageViewer()
            viewer.SetTitle("Basic Image Viewer Test")
            viewer.Execute(ExternalViewerTest.IMG)

            print("\nImageViewer parameters")
            print("    Application: ", viewer.GetApplication())
            print("    Command: ", viewer.GetCommand())
            print("    Extension: ", viewer.GetFileExtension())

            print("\nGlobal ImageViewer parameters")
            print("    Search path: ",
                  sitk.ImageViewer.GetGlobalDefaultSearchPath())
            print("    Default executable names: ",
                  sitk.ImageViewer.GetGlobalDefaultExecutableNames())
            print("    Process delay: ", sitk.ImageViewer.GetProcessDelay())
            print("    Debug flag: ", sitk.ImageViewer.GetGlobalDefaultDebug())
        except BaseException:
            self.fail("Basic Image Viewer Test FAILED")

    def test_bad_image_viewer(self):
        print("\n\nBad Image Viewer Test")
        try:
            viewer = sitk.ImageViewer()
            viewer.SetCommand('none')
            viewer.SetTitle("BAD Image Viewer Test")
            viewer.Execute(ExternalViewerTest.IMG)
        except BaseException:
            print("Exception triggered, as expected")


if __name__ == '__main__':
    unittest.main()
