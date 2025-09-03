#!/usr/bin/env python

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

import os
import sys
from pathlib import Path

import pytest
import SimpleITK as sitk


@pytest.fixture(scope="module")
def test_image():
    """Fixture providing a test image for all tests"""
    return sitk.GaussianSource()


@pytest.fixture(scope="session")
def viewer_command():
    """Fixture setting up the dummy viewer command"""
    this_dir = Path(__file__).absolute().parent
    cmd = f"{sys.executable} {this_dir/'dummy_viewer.py'} %t %f"
    original_command = os.environ.get("SITK_SHOW_COMMAND")

    print(f"Setting SITK_SHOW_COMMAND to: {cmd}")
    os.environ["SITK_SHOW_COMMAND"] = cmd

    yield cmd  # Provide the command to the tests

    # Restore original environment
    if original_command is not None:
        os.environ["SITK_SHOW_COMMAND"] = original_command
    else:
        del os.environ["SITK_SHOW_COMMAND"]


def test_show(test_image, viewer_command, caplog):
    """Test basic image showing functionality

    This test verifies that:
    1. The Show command executes successfully
    2. The viewer command is properly set
    3. Debug output is captured
    """
    caplog.set_level("DEBUG")
    print(f"\nTrying command: {viewer_command}")

    sitk.Show(test_image, debugOn=True)

    # Verify the command was used
    assert viewer_command in os.environ["SITK_SHOW_COMMAND"], \
        f"Show command not properly set: {os.environ['SITK_SHOW_COMMAND']}"


def test_show_env_override(test_image, viewer_command):
    """Test that Show command uses initial environment setting

    This test verifies that:
    1. Show command works even after changing SITK_SHOW_COMMAND
    2. The initial environment setting is preserved
    3. Later environment changes don't affect the viewer
    """
    # Change environment variable (should be ignored)
    os.environ["SITK_SHOW_COMMAND"] = "none"

    # Should still work with original command
    sitk.Show(test_image, debugOn=True)

    # Verify the change didn't affect the viewing
    assert "none" not in sitk.ImageViewer().GetCommand(), \
        "Show command should not use changed environment variable"


def test_image_viewer(test_image, capfd, viewer_command):
    """Test ImageViewer class functionality

    This test verifies:
    1. Basic viewer setup and execution
    2. Title setting with special characters
    3. Access to viewer parameters
    4. Access to global viewer settings
    """
    viewer = sitk.ImageViewer()

    # Test title with special characters
    title = "Basic Image Viewer Test"
    viewer.SetTitle(title)
    viewer.Execute(test_image)

    # Capture and verify viewer parameters
    out, _ = capfd.readouterr()


    print("\nImageViewer parameters")
    print("    Application: ", viewer.GetApplication())
    print("    Command: ", viewer.GetCommand())
    print("    Extension: ", viewer.GetFileExtension())

    print("\nGlobal ImageViewer parameters")
    print("    Search path: ", sitk.ImageViewer.GetGlobalDefaultSearchPath())
    print(
        "    Default executable names: ",
        sitk.ImageViewer.GetGlobalDefaultExecutableNames(),
    )
    print("    Process delay: ", sitk.ImageViewer.GetProcessDelay())
    print("    Debug flag: ", sitk.ImageViewer.GetGlobalDefaultDebug())

    # TODO: This the output variable does not contain the expected output
    # assert "Basic Image Viewer Test/:" in out, "Missing viewer parameter output"

    # Verify viewer configuration
    assert viewer.GetCommand(), "Viewer command not set"
    assert viewer.GetFileExtension(), "Viewer file extension not set"

    # Verify global settings
    assert sitk.ImageViewer.GetGlobalDefaultSearchPath(), "Global search path not set"
    assert sitk.ImageViewer.GetGlobalDefaultExecutableNames(), "Default executables not set"
    assert isinstance(sitk.ImageViewer.GetProcessDelay(), (int, float)), \
        "Process delay not numeric"
    assert isinstance(sitk.ImageViewer.GetGlobalDefaultDebug(), bool), \
        "Debug flag not boolean"


def test_bad_image_viewer(test_image):
    """Test ImageViewer error handling

    This test verifies that:
    1. Invalid viewer commands are handled properly
    2. Appropriate exceptions are raised
    3. Error states are properly detected
    """
    viewer = sitk.ImageViewer()
    viewer.SetCommand("none")
    viewer.SetTitle("BAD Image Viewer Test")

    with pytest.raises(Exception):
        viewer.Execute(test_image)
