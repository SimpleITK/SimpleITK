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
import os
import unittest


import SimpleITK as sitk
from multiprocessing.pool import ThreadPool


class ConcurrentImageRead(unittest.TestCase):
    """Testing thread concurrent reading of Images"""

    temp_directory = ""

    def setUp(self):
        pass

    def _create_data(self, img_extension, img_type):
        """Method to create the many temporary image for reading"""
        n = 64
        s = 128
        t = img_type

        files = []

        for i in range(0,n):
            img = sitk.GaussianSource(t, [s,s], mean=[256*(i+1)]*2)
            fname = "g_{0}.{1}".format(i, img_extension)
            if ConcurrentImageRead.temp_directory:
                fname = os.path.join(ConcurrentImageRead.temp_directory, fname)
            files.append(fname)
            sitk.WriteImage(img, files[-1])

        return files

    def _threaded_read_test(self, files, expected_hash):
        """Reads a list of files with thread parallelism, and verifies the hash of the resulting volume."""
        p = ThreadPool()
        img = sitk.JoinSeries(p.map(sitk.ReadImage, files))
        self.assertEqual(img.GetSize()[2], len(files))
        self.assertEqual(sitk.Hash(img), expected_hash)

    @staticmethod
    def generate_test(img_extension, expected_hash, img_type=sitk.sitkUInt32):
        """Generate additional test by adding a generated member function """
        def do_test(self):
            files = self._create_data(img_extension,img_type)
            files *= 64
            self._threaded_read_test(files, expected_hash)

        test_method = do_test
        test_method.__name__ = "test_threaded_read_{0}".format(p_ext_hash[0]);
        setattr(ConcurrentImageRead, test_method.__name__, test_method)


# Programmatically generate tests for different file formats
for p_ext_hash in [("jpg","44fac4bedde4df04b9572ac665d3ac2c5cd00c7d"),
                   ("tiff", "ba713b819c1202dcb0d178df9d2b3222ba1bba44", sitk.sitkUInt16),
                   ("png", "ba713b819c1202dcb0d178df9d2b3222ba1bba44", sitk.sitkUInt16),
                   ("mha","7b91dbdc56c5781edf6c8847b4aa6965566c5c75")]:
    ConcurrentImageRead.generate_test(*p_ext_hash)


if __name__ == '__main__':
    # hacky to get a temporary directory
    if len(sys.argv) > 1:
        ConcurrentImageRead.temp_directory = sys.argv.pop()
    unittest.main()
