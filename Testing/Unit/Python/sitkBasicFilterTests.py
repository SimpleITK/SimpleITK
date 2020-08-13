#==========================================================================
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

from __future__ import print_function
import unittest

import SimpleITK as sitk
import sys
import tempfile
import os.path
import shutil



class BasicFiltersTests(unittest.TestCase):
    """Tests for the Python interface for the Image class"""

    def setUp(self):
        super(BasicFiltersTests, self).setUp()
        self.test_dir = tempfile.mkdtemp()


    def assertImageAlmostEqual(self, img1, img2, max_difference=1e-8, msg=None):
        """ Compare with the maximum absolute difference between two images """

        minMaxFilter = sitk.StatisticsImageFilter()
        minMaxFilter.Execute(sitk.Abs(img1 - img2))

        if (minMaxFilter.GetMaximum() > max_difference):
            print("min: ", minMaxFilter.GetMinimum(), " max: ", minMaxFilter.GetMaximum(), " mean: ", minMaxFilter.GetMean())
            self.fail(msg)


    def test_procedure_resample(self):
        """ Test the custom Resample procedure. """

        img = sitk.GaborSource(sitk.sitkFloat32, [64, 64], frequency=.05)

        tx = sitk.Euler2DTransform( [32,32], .1, [2,-3])

        filter = sitk.ResampleImageFilter()
        filter.SetTransform(tx)
        filter.SetOutputPixelType(sitk.sitkFloat64)
        filter.SetDefaultPixelValue(255)
        filter.SetReferenceImage(img)

        baseline_image = filter.Execute(img)

        self.assertImageAlmostEqual( baseline_image,
                                     sitk.Resample(img, tx, sitk.sitkLinear, 255.0, sitk.sitkFloat64, False) )
        self.assertImageAlmostEqual( baseline_image,
                                     sitk.Resample(img, img, tx, sitk.sitkLinear, 255.0, sitk.sitkFloat64, False) )
        self.assertImageAlmostEqual( baseline_image,
                                     sitk.Resample(img, (64, 64), tx, sitk.sitkLinear, (0.0, 0.0), (1.0, 1.0), (1.0, 0.0, 0.0, 1.0), 255.0, sitk.sitkFloat64, False) )

        self.assertImageAlmostEqual( baseline_image,
                                     sitk.Resample(img, transform=tx, defaultPixelValue=255.0, outputPixelType=sitk.sitkFloat64 ) )
        self.assertImageAlmostEqual( baseline_image,
                                     sitk.Resample(img, img, transform=tx, defaultPixelValue=255.0, outputPixelType=sitk.sitkFloat64) )
        self.assertImageAlmostEqual( baseline_image,
                                     sitk.Resample(img, [64, 64], transform=tx, defaultPixelValue=255.0, outputPixelType=sitk.sitkFloat64) )

        self.assertImageAlmostEqual( baseline_image,
                                     sitk.Resample(img, referenceImage=img, transform=tx, defaultPixelValue=255.0, outputPixelType=sitk.sitkFloat64) )
        self.assertImageAlmostEqual( baseline_image,
                                     sitk.Resample(img, size=(64, 64), transform=tx, defaultPixelValue=255.0, outputPixelType=sitk.sitkFloat64 ) )

    def test_paste_filter(self):

        img1 = sitk.GaborSource(sitk.sitkFloat32, [64, 64, 64], frequency=.05)
        img2 = sitk.Image([32,32,32], sitk.sitkFloat32)

        sitk.Paste(img1, img2)


if __name__ == '__main__':
    unittest.main()
