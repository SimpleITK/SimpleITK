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
import tempfile
import os.path
import shutil

import SimpleITK as sitk
try:
    import pickle5 as pickle
except ImportError:
    import pickle


class TransformTests(unittest.TestCase):
    """Tests for the Python interface for Transform classes"""

    def setUp(self):
        super(TransformTests, self).setUp()

        # Register a "assertEqual" function for all transform types, there appears no way to support subclasses
        transform_type_list = [sitk.AffineTransform,
                               sitk.BSplineTransform,
                               sitk.DisplacementFieldTransform,
                               sitk.Euler2DTransform,
                               sitk.Euler3DTransform,
                               sitk.ScaleSkewVersor3DTransform,
                               sitk.ScaleTransform,
                               sitk.ScaleVersor3DTransform,
                               sitk.Similarity2DTransform,
                               sitk.Similarity3DTransform,
                               sitk.Transform,
                               sitk.TranslationTransform,
                               sitk.VersorRigid3DTransform,
                               sitk.VersorTransform]

        for transform_type in transform_type_list:
            self.addTypeEqualityFunc(transform_type, self.assertTransformEqual)

        # Create a temporary directory for output files
        self.test_dir = tempfile.mkdtemp()

    def tearDown(self):

        # Delete the temporary directory and files contained within. Perhaps if tests fail then the output should  stick
        # around to debug the problem
        shutil.rmtree(self.test_dir)

    def assertTransformEqual(self, tx1, tx2, msg=None):
        """Utility to compare 2 transforms"""

        self.assertEqual(tx1.__class__, tx2.__class__)
        self.assertEqual(tx1.GetDimension(), tx2.GetDimension())
        self.assertEqual(tx1.GetFixedParameters(), tx2.GetFixedParameters())
        self.assertEqual(tx1.GetParameters(), tx2.GetParameters())

    def test_bspline_constructor(self):

        img1 = sitk.Image([10, 10], sitk.sitkFloat64)
        img1 += -.1

        img2 = sitk.Image([10, 10], sitk.sitkFloat64)
        img2 -= 0.1

        tx = sitk.BSplineTransform([img1, img2], 2)
        self.assertEqual(tx.GetOrder(), 2)

    def test_bspline_pickle(self):

        M = [0, 1,
             1, 0]

        img1 = sitk.Image([10, 10], sitk.sitkFloat64)
        img1.SetOrigin((.01, 5.2))
        img1.SetDirection(M)
        img1 += -.1

        img2 = sitk.Image([10, 10], sitk.sitkFloat64)
        img2.SetOrigin([.01, 5.2])
        img2.SetDirection(M)
        img2 -= 0.1

        tx = sitk.BSplineTransform([img1, img2], 3)
        dump = pickle.dumps(tx)
        tx2 = pickle.loads(dump)

        self.assertEqual(tx, tx2)

    def test_bspline_pickle_file(self):
        """Test the custom pickling and un-pickling interface"""

        import copy

        M = [0, 1,
             1, 0]

        img1 = sitk.Image([10, 10], sitk.sitkFloat64)
        img1.SetOrigin((.01, 5.2))
        img1.SetDirection(M)
        img1 = sitk.AdditiveGaussianNoise(img1)

        img2 = sitk.Image([10, 10], sitk.sitkFloat64)
        img2.SetOrigin((.01, 5.2))
        img2.SetDirection(M)
        img2 = sitk.AdditiveGaussianNoise(img2)

        tx = sitk.BSplineTransform([img1, img2], 3)

        fname = os.path.join(self.test_dir, "bspline_protocol_default.pickle")
        with open(fname, 'wb') as fp:
            p = pickle.dump(copy.deepcopy(tx), fp)

        with open(fname, 'rb') as fp:
            ret = pickle.load(fp)

        self.assertEqual(ret, ret, msg="pickle file with default protocol")


    def test_displacement_pickle(self):

        displacement = sitk.Image((512, 512), sitk.sitkVectorFloat64, 2)
        displacement.SetOrigin((6, 5.2))

        tx = sitk.DisplacementFieldTransform(displacement)
        dump = pickle.dumps(tx)
        tx2 = pickle.loads(dump)

        self.assertEqual(tx, tx2)

    def test_affine_pickle(self):
        tx = sitk.AffineTransform(3)

        tx.SetCenter([2.3, 4.5, 6.7])
        tx.SetMatrix([9, 8, 7, 6, 5, 4, 3, 2, 1])

        dump = pickle.dumps(tx)
        tx2 = pickle.loads(dump)

        self.assertEqual(tx, tx2)

    def test_translation_pickle(self):
        tx = sitk.TranslationTransform(2)
        tx.SetOffset([1.23456, 9876.54321])

        dump = pickle.dumps(tx)
        tx2 = pickle.loads(dump)

        self.assertEqual(tx, tx2)

    def test_deepcopy(self):
        """Test the custom __deepcopy__ method"""

        import copy

        tx = sitk.AffineTransform(2)

        tx.SetMatrix([.6, -.5, -.2, .8])

        tx_dc = copy.deepcopy(tx)

        self.assertEqual(tx, tx_dc)

        tx_dc.SetCenter([7, 8])
        self.assertNotEqual(tx.GetCenter(), tx_dc.GetCenter())

        tx_c = copy.copy(tx)

        self.assertEqual(tx, tx_c)

        tx_c.SetCenter([9, 10])
        self.assertNotEqual(tx.GetCenter(), tx_c.GetCenter())


if __name__ == '__main__':
    unittest.main()
