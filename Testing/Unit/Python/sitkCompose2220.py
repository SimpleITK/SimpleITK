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

import unittest

import SimpleITK as sitk
import numpy as np


class Compose2220Tests(unittest.TestCase):
    """Test related to GH iss #2220 reported data corruption"""

    def setUp(self):
        super(Compose2220Tests, self).setUp()

    def assertImageAlmostEqual(self, img1, img2, max_difference=1e-8, msg=None):
        """Compare with the maximum absolute difference between two images"""

        minMaxFilter = sitk.StatisticsImageFilter()
        minMaxFilter.Execute(sitk.Abs(img1 - img2))

        if minMaxFilter.GetMaximum() > max_difference:
            print(
                "min: ",
                minMaxFilter.GetMinimum(),
                " max: ",
                minMaxFilter.GetMaximum(),
                " mean: ",
                minMaxFilter.GetMean(),
            )
            self.fail(msg)

    def test_case1(self):
        """
        Reported data corruption in GH issue #2220. Test code provided by the user.

        """

        images = list()
        stack = list()

        size = 400
        for i in range(100):
            data = np.zeros((size, )*3, dtype=np.uint8)
            data[i:(1+i), :, :] = 10+i+1
            images.append(sitk.GetImageFromArray(data))
            stack.append(data)

        img_compose = sitk.Compose(images)

        img_stack = sitk.GetImageFromArray(np.stack(stack, axis=-1))

        self.assertImageAlmostEqual(img_compose, img_stack)

    def test_case2(self):
        size = 400
        nchannels = 100
        images = list()
        for i in range(nchannels):
            d = sitk.Image((size, size, size), sitk.sitkUInt8)
            d[..., i] = 1
            images.append(d)
        img = sitk.Compose(images)
        for i in range(nchannels):
            if sitk.MinimumMaximum(sitk.VectorIndexSelectionCast(img[..., i], i)) != (1, 1):
                print(f"compose filter: problem with component {i}")
                self.fail("compose filter: problem with component")


if __name__ == "__main__":
    unittest.main()
