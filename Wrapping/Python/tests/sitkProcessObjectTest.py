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
import SimpleITK as sitk


@pytest.mark.parametrize("filter_class", [
    # Manually written filters
    sitk.CastImageFilter,
    sitk.HashImageFilter,
    sitk.StatisticsImageFilter,
    sitk.LabelStatisticsImageFilter,
    # Generated filters
    sitk.AddImageFilter,
    sitk.FastMarchingImageFilter,
    sitk.BinaryDilateImageFilter,
    sitk.GaussianImageSource,
    sitk.JoinSeriesImageFilter,
])
def test_ProcessObject_base(filter_class):
    """Test that ProcessObject is the superclass of various filters"""
    assert issubclass(filter_class, sitk.ProcessObject), \
        f"{filter_class.__name__} should be a subclass of ProcessObject"


def test_ProcessObject_static():
    """Test wrapping of static methods"""
    sitk.ProcessObject.SetGlobalDefaultThreader("PLATFORM")


def test_ProcessObject_lambda_Command():
    """Test lambda Command event handling

    Verifies that:
    1. Lambda commands are correctly registered and executed
    2. Start events are triggered
    3. Progress events report correct progress
    4. Event handlers can modify state through list references
    """
    f = sitk.CastImageFilter()

    def s(var, value):
        var[0] = value

    # Use lists to store values since they're mutable (passed by reference)
    start = [0]
    stop = [0]
    progress = [0.0]

    # Register event handlers using lambdas
    f.AddCommand(sitk.sitkStartEvent, lambda start=start: s(start, start[0] + 1))
    f.AddCommand(sitk.sitkStartEvent, lambda stop=stop: s(stop, stop[0] + 1))
    f.AddCommand(sitk.sitkProgressEvent, lambda p=progress: s(p, f.GetProgress()))

    # Execute filter
    f.Execute(sitk.Image(10, 10, sitk.sitkFloat32))

    # Verify event handlers were called correctly
    assert start[0] == 1, "Start event handler should be called once"
    assert stop[0] == 1, "Stop event handler should be called once"
    assert progress[0] == 1.0, "Final progress should be 1.0"


def test_ProcessObject_PyCommand():
    """Test PyCommand class functionality

    Verifies that:
    1. PyCommand objects can be created and registered
    2. Callbacks are executed properly
    3. Progress is tracked correctly
    4. Command cleanup works as expected
    """
    f = sitk.CastImageFilter()
    progress = [0.0]

    def prog():
        progress[0] = f.GetProgress()

    # Create and register PyCommand
    cmd = sitk.PyCommand()
    cmd.SetCallbackPyCallable(prog)
    f.AddCommand(sitk.sitkProgressEvent, cmd)

    # First execution - command should update progress
    f.Execute(sitk.Image(10, 10, sitk.sitkFloat32))
    assert progress[0] == 1.0, "Progress should be 1.0 after execution"

    # Reset progress and delete command
    progress[0] = 0.0
    del cmd

    # Second execution - progress should not be updated
    f.Execute(sitk.Image(10, 10, sitk.sitkFloat32))
    assert progress[0] == 0.0, "Progress should remain 0.0 after command deletion"
