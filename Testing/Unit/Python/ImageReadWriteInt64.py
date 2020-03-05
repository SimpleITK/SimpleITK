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
import sys
import os
import unittest
import tempfile
import shutil


import SimpleITK as sitk


class ImageReadWriteInt64(unittest.TestCase):
    """Test reading and writing to 64 bit integers"""

    def setUp(self):

        # Create a temporary directory for output files
        self.test_dir = tempfile.mkdtemp()

    def tearDown(self):

        # Delete the temporary directory and files contained within. Perhaps if tests fail then the output should  stick
        # around to debug the problem
        shutil.rmtree(self.test_dir)

    def setUp(self):

        # Create a temporary directory for output files
        self.test_dir = tempfile.mkdtemp()

    def tearDown(self):

        # Delete the create temporary directory and files with  in. Perhaps if tests fail then the output should  stick
        # around to debug the problem
        shutil.rmtree(self.test_dir)

    def _create_img(self, img_type):
        """Method to create an image"""
        img_size = [64]*2

        img = sitk.Image(img_size, img_type)
        img[0,1] = 1
        img[0,2] = 1000
        img[0,3] = 2**33

        if img_type in [sitk.sitkInt8, sitk.sitkInt16, sitk.sitkInt32, sitk.sitkInt64]:
            img[1,0] = -1;
            img[2,0] = -100;
            img[3,0] = -2**34

        return img

    def _read_write_test(self, img, tmp_filename):
        """ """

        base_hash = sitk.Hash(img);
        sitk.WriteImage(img, tmp_filename);
        in_img = sitk.ReadImage(tmp_filename);
        self.assertEqual(base_hash, sitk.Hash(in_img))
        self.assertEqual(img.GetPixelID(), in_img.GetPixelID())
        print(img.GetPixelIDTypeAsString())

    @staticmethod
    def generate_test(img_extension, img_type=sitk.sitkInt64):
        """Generate additional test by adding a generated member function """
        def do_test(self):
            fname = "test64.{0}".format(img_extension)
            fname = os.path.join(self.test_dir, fname)
            img = self._create_img(img_type)
            self._read_write_test(img, fname)

        test_method = do_test
        test_method.__name__ = "test_read_write_int64{0}{1}".format(img_extension,int(img_type))
        setattr(ImageReadWriteInt64, test_method.__name__, test_method)


# Programmatically generate tests for different file formats
for p_ext_hash in [ ("mha", sitk.sitkUInt64),
                    ("mha", sitk.sitkInt64),
                    ("nrrd", sitk.sitkUInt64),
                    ("nrrd", sitk.sitkInt64),
                    ("nii", sitk.sitkUInt64),
                    ("nii", sitk.sitkInt64)]:
    ImageReadWriteInt64.generate_test(*p_ext_hash)


if __name__ == '__main__':
    unittest.main()
