#==========================================================================
#
#   Copyright Insight Software Consortium
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
from __future__ import print_function
import sys
import unittest


import SimpleITK as sitk


class ProcessObjectTest(unittest.TestCase):
    """Test the SimpleITK Process Object and related Command classes"""

    def setUp(self):
        pass

    def test_ProcessObject_base(self):
        " Check that ProcessObject is super class of filters"

        # check some manually written filters
        self.assertTrue(issubclass(sitk.CastImageFilter,sitk.ProcessObject))
        self.assertTrue(issubclass(sitk.HashImageFilter,sitk.ProcessObject))
        self.assertTrue(issubclass(sitk.StatisticsImageFilter,sitk.ProcessObject))
        self.assertTrue(issubclass(sitk.LabelStatisticsImageFilter,sitk.ProcessObject))

        # Check some of the different types of generated
        self.assertTrue(issubclass(sitk.AddImageFilter,sitk.ProcessObject))
        self.assertTrue(issubclass(sitk.FastMarchingImageFilter,sitk.ProcessObject))
        self.assertTrue(issubclass(sitk.BinaryDilateImageFilter,sitk.ProcessObject))
        self.assertTrue(issubclass(sitk.GaussianImageSource,sitk.ProcessObject))
        self.assertTrue(issubclass(sitk.JoinSeriesImageFilter,sitk.ProcessObject))


    def test_ProcessObject_lambda_Command(self):
        """Check that the lambda Command on event works"""

        f = sitk.CastImageFilter();

        def s(var,value):
            var[0] = value

        # int/floats are passed by value, use lists to be passed by reference
        start = [0]
        stop = [0]
        p = [0.0]
        f.AddCommand(sitk.sitkStartEvent, lambda start=start: s(start,start[0]+1) )
        f.AddCommand(sitk.sitkStartEvent, lambda stop=stop: s(stop, stop[0]+1) )
        f.AddCommand(sitk.sitkProgressEvent, lambda p=p: s(p, f.GetProgress()) );
        f.Execute(sitk.Image(10,10,sitk.sitkFloat32))

        print( "start: {0} stop: {1} p: {2}".format(start,stop,p))
        self.assertEqual(start,[1])
        self.assertEqual(stop,[1])
        self.assertEqual(p,[1.0])


    def test_ProcessObject_PyCommand(self):
        """Testing PyCommand Class"""

        f = sitk.CastImageFilter();

        p = [0.0]
        def prog():
            p[0] = f.GetProgress();

        cmd = sitk.PyCommand()
        cmd.SetCallbackPyCallable(prog)


        f.AddCommand(sitk.sitkProgressEvent, cmd );
        f.Execute(sitk.Image(10,10,sitk.sitkFloat32))
        self.assertEqual(p,[1.0])

        p = [0.0]
        del cmd


        f.Execute(sitk.Image(10,10,sitk.sitkFloat32))
        self.assertEqual(p,[0.0])


if __name__ == '__main__':
    unittest.main()
