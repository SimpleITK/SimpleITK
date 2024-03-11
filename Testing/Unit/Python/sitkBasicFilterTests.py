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

    def test_procedure_resample(self):
        """Test the custom Resample procedure."""

        img = sitk.GaborSource(sitk.sitkFloat32, [64, 64], frequency=0.05)

        tx = sitk.Euler2DTransform([32, 32], 0.1, [2, -3])

        filter = sitk.ResampleImageFilter()
        filter.SetTransform(tx)
        filter.SetOutputPixelType(sitk.sitkFloat64)
        filter.SetDefaultPixelValue(255)
        filter.SetReferenceImage(img)

        baseline_image = filter.Execute(img)

        self.assertImageAlmostEqual(
            baseline_image,
            sitk.Resample(img, tx, sitk.sitkLinear, 255.0, sitk.sitkFloat64, False),
        )
        self.assertImageAlmostEqual(
            baseline_image,
            sitk.Resample(
                img, img, tx, sitk.sitkLinear, 255.0, sitk.sitkFloat64, False
            ),
        )
        self.assertImageAlmostEqual(
            baseline_image,
            sitk.Resample(
                img,
                (64, 64),
                tx,
                sitk.sitkLinear,
                (0.0, 0.0),
                (1.0, 1.0),
                (1.0, 0.0, 0.0, 1.0),
                255.0,
                sitk.sitkFloat64,
                False,
            ),
        )

        self.assertImageAlmostEqual(
            baseline_image,
            sitk.Resample(
                img,
                transform=tx,
                defaultPixelValue=255.0,
                outputPixelType=sitk.sitkFloat64,
            ),
        )
        self.assertImageAlmostEqual(
            baseline_image,
            sitk.Resample(
                img,
                img,
                transform=tx,
                defaultPixelValue=255.0,
                outputPixelType=sitk.sitkFloat64,
            ),
        )
        self.assertImageAlmostEqual(
            baseline_image,
            sitk.Resample(
                img,
                [64, 64],
                transform=tx,
                defaultPixelValue=255.0,
                outputPixelType=sitk.sitkFloat64,
            ),
        )

        self.assertImageAlmostEqual(
            baseline_image,
            sitk.Resample(
                img,
                referenceImage=img,
                transform=tx,
                defaultPixelValue=255.0,
                outputPixelType=sitk.sitkFloat64,
            ),
        )
        self.assertImageAlmostEqual(
            baseline_image,
            sitk.Resample(
                img,
                size=(64, 64),
                transform=tx,
                defaultPixelValue=255.0,
                outputPixelType=sitk.sitkFloat64,
            ),
        )

        with self.assertRaises(TypeError) as cm:
            sitk.Resample(img, img, wrong_keyword1=img)
        self.assertTrue("unexpected keyword argument" in str(cm.exception))

        with self.assertRaises(TypeError) as cm:
            sitk.Resample(img, [64, 64], wrong_keyword2=img)
        self.assertTrue("unexpected keyword argument" in str(cm.exception))

        with self.assertRaises(TypeError) as cm:
            sitk.Resample(img, referenceImage=img, wrong_keyword3=img)
        self.assertTrue("unexpected keyword argument" in str(cm.exception))

        with self.assertRaises(TypeError) as cm:
            sitk.Resample(img, size=[64, 64], wrong_keyword4=img)
        self.assertTrue("unexpected keyword argument" in str(cm.exception))

        with self.assertRaises(TypeError) as cm:
            sitk.Resample(img, tx, wrong_keyword5=img)
        self.assertTrue("unexpected keyword argument" in str(cm.exception))

    def test_paste_filter(self):

        img1 = sitk.GaborSource(sitk.sitkFloat32, [64, 64, 64], frequency=0.05)
        img2 = sitk.Image([32, 32, 32], sitk.sitkFloat32)

        sitk.Paste(img1, img2)

    def test_landmark_based_transform_initializer(self):
        """
        Test downcast of LandmarkBasedTransformInitializer return Transform
        :return:
        """

        point_set = [i for i in range(12)]

        tx_initializer = sitk.LandmarkBasedTransformInitializerFilter()
        tx_initializer.SetFixedLandmarks(point_set)
        tx_initializer.SetMovingLandmarks(point_set)

        self.assertEqual(
            tx_initializer.Execute(sitk.Euler2DTransform()).__class__,
            sitk.Euler2DTransform,
        )
        self.assertEqual(
            tx_initializer.Execute(sitk.Similarity2DTransform()).__class__,
            sitk.Similarity2DTransform,
        )
        self.assertEqual(
            tx_initializer.Execute(sitk.AffineTransform(2)).__class__,
            sitk.AffineTransform,
        )

        self.assertEqual(
            tx_initializer.Execute(sitk.VersorRigid3DTransform()).__class__,
            sitk.VersorRigid3DTransform,
        )
        self.assertEqual(
            tx_initializer.Execute(sitk.Similarity3DTransform()).__class__,
            sitk.Similarity3DTransform,
        )
        self.assertEqual(
            tx_initializer.Execute(sitk.ScaleVersor3DTransform()).__class__,
            sitk.ScaleVersor3DTransform,
        )
        self.assertEqual(
            tx_initializer.Execute(sitk.AffineTransform(3)).__class__,
            sitk.AffineTransform,
        )

    def test_centered_transfrom_initializer(self):
        """Test CenteredTransformInitializer to check that return Transform is downcasted"""

        transforms_3d = {
            "AffineTransform": (3,),
            "Euler3DTransform": (),
            "ScaleSkewVersor3DTransform": (),
            "ScaleTransform": (3,),
            "ScaleVersor3DTransform": (),
            "Similarity3DTransform": (),
            "VersorRigid3DTransform": (),
            "VersorTransform": (),
        }

        fixed = sitk.Image([16, 16, 16], sitk.sitkFloat32)
        fixed.SetOrigin([32, 32, 32])
        moving = sitk.Image([16, 16, 16], sitk.sitkFloat32)

        tx_initializer = sitk.CenteredTransformInitializerFilter()
        tx_initializer.SetOperationMode(
            sitk.CenteredTransformInitializerFilter.GEOMETRY
        )

        for transform_name, parameters in transforms_3d.items():
            tx = getattr(sitk, transform_name)(*parameters)

            result_tx = tx_initializer.Execute(fixed, moving, tx)
            self.assertEqual(result_tx.__class__, tx.__class__)

            result_tx = sitk.CenteredTransformInitializer(
                fixed, moving, tx, sitk.CenteredTransformInitializerFilter.GEOMETRY
            )
            self.assertEqual(result_tx.__class__, tx.__class__)

    def test_minimum_maximum(self):
        """
        Test the manual written MinimumMaximum procedural method
        :return:
        """

        img = sitk.Image([32, 32], sitk.sitkFloat32)

        self.assertEqual(sitk.MinimumMaximum(img), (0.0, 0.0))

        img[0, 0] = -1.0
        img[10, 10] = 2.0
        self.assertEqual(sitk.MinimumMaximum(img), (-1.0, 2.0))

        img = sitk.Image([32, 32], sitk.sitkUInt8)
        self.assertEqual(sitk.MinimumMaximum(img), (0.0, 0.0))

        img += 1
        img[10, 10] = 255
        self.assertEqual(sitk.MinimumMaximum(img), (1.0, 255.0))


if __name__ == "__main__":
    unittest.main()
