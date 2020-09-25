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
from copy import deepcopy

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

        self.addTypeEqualityFunc(sitk.CompositeTransform, self.assertCompositeEqual)

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



    def assertCompositeEqual(self, ctx1, ctx2, msg=None):
        """ method to compare CompositeTransforms"""

        self.assertEqual(ctx1.GetNumberOfTransforms(), ctx2.GetNumberOfTransforms())
        self.assertEqual(ctx1.GetNumberOfFixedParameters(), ctx2.GetNumberOfFixedParameters())
        self.assertEqual(ctx1.GetFixedParameters(), ctx2.GetFixedParameters())
        self.assertEqual(ctx1.GetNumberOfParameters(), ctx2.GetNumberOfParameters())
        self.assertEqual(ctx1.GetParameters(), ctx2.GetParameters())
        self.assertTransformEqual(ctx1, ctx2, msg);

        for idx in range(ctx1.GetNumberOfTransforms()):
            tx1 = ctx1.GetNthTransform(idx)
            tx2 = ctx2.GetNthTransform(idx)

            self.assertTransformEqual(tx1, tx2, msg="Comparing transform {0}: {1}".format(idx, msg))


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

    def test_composite_pickle(self):
        ctx = sitk.CompositeTransform( [sitk.Transform()] )

        ptx = pickle.loads(pickle.dumps(ctx))
        self.assertEqual(ctx, ptx)

        ctx = sitk.CompositeTransform( [sitk.AffineTransform(2),
                                        sitk.Euler2DTransform(),
                                        sitk.TranslationTransform(2),
                                        sitk.AffineTransform(2)] );

        ptx = pickle.loads(pickle.dumps(ctx))
        self.assertEqual(ctx, ptx)

        displacement = sitk.Image([64]*3, sitk.sitkVectorFloat64, 3)
        displacement.SetOrigin((7, 8.9, 6))

        tx1 = sitk.DisplacementFieldTransform(displacement)

        img1 = sitk.Image([5]*3, sitk.sitkFloat64)
        img1.SetOrigin((.01, 2.3, 4.5))
        img2 = deepcopy(img1)
        img3 = deepcopy(img1)

        img1 += -.1
        img2 -= 0.1
        img3 += -.3

        tx2 = sitk.BSplineTransform([img1, img2, img3], 3)

        ctx = sitk.CompositeTransform( [sitk.AffineTransform(3),
                                        tx1,
                                        tx2] )
        ptx = pickle.loads(pickle.dumps(ctx))
        self.assertEqual(ctx, ptx)

    def test_name(self):
        """Testing GetName method"""

        transforms = {
            'AffineTransform': (3,),
            'BSplineTransform': (3, 3),
            'DisplacementFieldTransform': (3,),
            'Euler2DTransform': (),
            'Euler3DTransform': (),
            'ScaleSkewVersor3DTransform': (),
            'ScaleTransform': (3,),
            'ScaleVersor3DTransform': (),
            'Similarity2DTransform': (),
            'Similarity3DTransform': (),
            'Transform': (),
            'TranslationTransform': (3,),
            'VersorRigid3DTransform': (),
            'VersorTransform': (),
            'CompositeTransform': (3,)
        }

        for k, v in transforms.items():
            tx = getattr(sitk, k)(*v)

            self.assertEqual(k, tx.GetName())

    def test_default_pickle(self):
        """Test pickling/unpickling of minimally constructed transforms"""

        transforms = {
            'AffineTransform': (3,),
            'BSplineTransform': (3, 3),
            'DisplacementFieldTransform': (3,),
            'Euler2DTransform': (),
            'Euler3DTransform': (),
            'ScaleSkewVersor3DTransform': (),
            'ScaleTransform': (3,),
            'ScaleVersor3DTransform': (),
            'Similarity2DTransform': (),
            'Similarity3DTransform': (),
            'Transform': (),
            'TranslationTransform': (3,),
            'VersorRigid3DTransform': (),
            'VersorTransform': (),
            'CompositeTransform': (3,)
        }

        for k, v in transforms.items():
            tx = getattr(sitk, k)(*v)

            tx2 = pickle.loads(pickle.dumps(tx))

            self.assertEqual(tx, tx2, msg="Testing {0}".format(tx.GetName()))

            tx3 = pickle.loads(pickle.dumps(sitk.Transform(tx)))

            self.assertEqual(tx, tx3, msg="Testing {0} from Transform: {1} {2}".format(tx.GetName(), tx3, sitk.Transform(tx).Downcast()))


    def test_downcast(self):
        """Test Downcast method with minimally constructed transforms"""

        transforms = {
            'AffineTransform': (3,),
            'AffineTransform': (2,),
            'BSplineTransform': (3, 3),
            'BSplineTransform': (2, 3),
            'BSplineTransform': (2, 2),
            'DisplacementFieldTransform': (3,),
            'DisplacementFieldTransform': (2,),
            'Euler2DTransform': (),
            'Euler3DTransform': (),
            'ScaleSkewVersor3DTransform': (),
            'ScaleTransform': (2,),
            'ScaleTransform': (3,),
            'ScaleVersor3DTransform': (),
            'Similarity2DTransform': (),
            'Similarity3DTransform': (),
            'Transform': (),
            'TranslationTransform': (3,),
            'TranslationTransform': (2,),
            'VersorRigid3DTransform': (),
            'VersorTransform': (),
            'CompositeTransform' : (3,)
        }

        for k, v in transforms.items():
            print("Testing {0}".format(k))
            tx = getattr(sitk, k)(*v)

            tx2 = sitk.Transform(tx)

            tx3 = tx2.Downcast()

            self.assertEqual(tx, tx3)
            self.assertEqual(tx.__class__, tx3.__class__, msg="Testing {0}".format(tx.GetName()))


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

    def test_readwrite(self):
        """Test reading and writing transforms"""

        transforms = {
            'AffineTransform': (3,),
            'AffineTransform': (2,),
            'BSplineTransform': (3, 3),
            'BSplineTransform': (2, 3),
            'BSplineTransform': (2, 2),
            'DisplacementFieldTransform': (3,),
            'DisplacementFieldTransform': (2,),
            'Euler2DTransform': (),
            'Euler3DTransform': (),
            'ScaleSkewVersor3DTransform': (),
            'ScaleTransform': (2,),
            'ScaleTransform': (3,),
            'ScaleVersor3DTransform': (),
            'Similarity2DTransform': (),
            'Similarity3DTransform': (),
            'Transform': (),
            'TranslationTransform': (3,),
            'TranslationTransform': (2,),
            'VersorRigid3DTransform': (),
            'VersorTransform': (),
            'CompositeTransform' : (3,)
        }

        extensions = [
            "txt",
            "tfm",
            "xfm", # requires ITKIOTransformMINC module enabled
            "hdf",
            "mat"
        ]

        tx_extension = "txt"

        for ext in extensions:
            for k, v in transforms.items():

                fname = os.path.join(self.test_dir, "test_readwrite_"+k+"."+tx_extension)

                print("Testing I/O {0} with {1}".format(k,ext))
                tx = getattr(sitk, k)(*v)

                sitk.WriteTransform(tx, fname)
                read_tx = sitk.ReadTransform(fname)
                self.assertEqual(tx, read_tx.Downcast())


if __name__ == '__main__':

    unittest.main()
