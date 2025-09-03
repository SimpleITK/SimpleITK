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
import os.path
import copy
from copy import deepcopy
from pathlib import Path

import SimpleITK as sitk

try:
    import pickle5 as pickle
except ImportError:
    import pickle


@pytest.fixture
def test_dir(tmp_path):
    """Fixture providing a temporary directory for test outputs"""
    return tmp_path


def _assert_transform_equal(tx1, tx2, msg=None):
    """Utility to compare 2 transforms"""
    assert tx1.__class__ == tx2.__class__, f"{msg}: Classes differ"
    assert tx1.GetDimension() == tx2.GetDimension(), f"{msg}: Dimensions differ"
    assert tx1.GetFixedParameters() == tx2.GetFixedParameters(), f"{msg}: Fixed parameters differ"
    assert tx1.GetParameters() == tx2.GetParameters(), f"{msg}: Parameters differ"


def _assert_composite_equal(ctx1, ctx2, msg=None):
    """method to compare CompositeTransforms"""
    assert ctx1.GetNumberOfTransforms() == ctx2.GetNumberOfTransforms(), f"{msg}: Number of transforms differs"
    assert ctx1.GetNumberOfFixedParameters() == ctx2.GetNumberOfFixedParameters(), f"{msg}: Number of fixed parameters differs"
    assert ctx1.GetFixedParameters() == ctx2.GetFixedParameters(), f"{msg}: Fixed parameters differ"
    assert ctx1.GetNumberOfParameters() == ctx2.GetNumberOfParameters(), f"{msg}: Number of parameters differs"
    assert ctx1.GetParameters() == ctx2.GetParameters(), f"{msg}: Parameters differ"
    _assert_transform_equal(ctx1, ctx2, msg)

    for idx in range(ctx1.GetNumberOfTransforms()):
        tx1 = ctx1.GetNthTransform(idx)
        tx2 = ctx2.GetNthTransform(idx)
        _assert_transform_equal(tx1, tx2, f"{msg}: Comparing transform {idx}")


# Test Cases
def test_bspline_constructor():
    img1 = sitk.Image([10, 10], sitk.sitkFloat64)
    img1 += -0.1

    img2 = sitk.Image([10, 10], sitk.sitkFloat64)
    img2 -= 0.1

    tx = sitk.BSplineTransform([img1, img2], 2)
    assert tx.GetOrder() == 2


def test_bspline_pickle():
    M = [0, 1, 1, 0]

    img1 = sitk.Image([10, 10], sitk.sitkFloat64)
    img1.SetOrigin((0.01, 5.2))
    img1.SetDirection(M)
    img1 += -0.1

    img2 = sitk.Image([10, 10], sitk.sitkFloat64)
    img2.SetOrigin([0.01, 5.2])
    img2.SetDirection(M)
    img2 -= 0.1

    tx = sitk.BSplineTransform([img1, img2], 3)
    dump = pickle.dumps(tx)
    tx2 = pickle.loads(dump)

    _assert_transform_equal(tx, tx2)


def test_bspline_pickle_file(test_dir):
    """Test the custom pickling and un-pickling interface"""
    M = [0, 1, 1, 0]

    img1 = sitk.Image([10, 10], sitk.sitkFloat64)
    img1.SetOrigin((0.01, 5.2))
    img1.SetDirection(M)
    img1 = sitk.AdditiveGaussianNoise(img1)

    img2 = sitk.Image([10, 10], sitk.sitkFloat64)
    img2.SetOrigin((0.01, 5.2))
    img2.SetDirection(M)
    img2 = sitk.AdditiveGaussianNoise(img2)

    tx = sitk.BSplineTransform([img1, img2], 3)

    fname = test_dir / "bspline_protocol_default.pickle"
    with open(fname, "wb") as fp:
        pickle.dump(deepcopy(tx), fp)

    with open(fname, "rb") as fp:
        ret = pickle.load(fp)

    _assert_transform_equal(ret, ret, "Pickle file with default protocol")


def test_displacement_pickle():
    displacement = sitk.Image((512, 512), sitk.sitkVectorFloat64, 2)
    displacement.SetOrigin((6, 5.2))

    tx = sitk.DisplacementFieldTransform(displacement)
    dump = pickle.dumps(tx)
    tx2 = pickle.loads(dump)

    _assert_transform_equal(tx, tx2)


def test_affine_pickle():
    tx = sitk.AffineTransform(3)
    tx.SetCenter([2.3, 4.5, 6.7])
    tx.SetMatrix([9, 8, 7, 6, 5, 4, 3, 2, 1])

    dump = pickle.dumps(tx)
    tx2 = pickle.loads(dump)

    _assert_transform_equal(tx, tx2)


def test_translation_pickle():
    tx = sitk.TranslationTransform(2)
    tx.SetOffset([1.23456, 9876.54321])

    dump = pickle.dumps(tx)
    tx2 = pickle.loads(dump)

    _assert_transform_equal(tx, tx2)


def test_composite_pickle():
    ctx = sitk.CompositeTransform([sitk.Transform()])

    ptx = pickle.loads(pickle.dumps(ctx))
    _assert_composite_equal(ctx, ptx)

    ctx = sitk.CompositeTransform(
        [
            sitk.AffineTransform(2),
            sitk.Euler2DTransform(),
            sitk.TranslationTransform(2),
            sitk.AffineTransform(2),
        ]
    )

    ptx = pickle.loads(pickle.dumps(ctx))
    _assert_composite_equal(ctx, ptx)

    displacement = sitk.Image([64] * 3, sitk.sitkVectorFloat64, 3)
    displacement.SetOrigin((7, 8.9, 6))

    tx1 = sitk.DisplacementFieldTransform(displacement)

    img1 = sitk.Image([5] * 3, sitk.sitkFloat64)
    img1.SetOrigin((0.01, 2.3, 4.5))
    img2 = deepcopy(img1)
    img3 = deepcopy(img1)

    img1 += -0.1
    img2 -= 0.1
    img3 += -0.3

    tx2 = sitk.BSplineTransform([img1, img2, img3], 3)

    ctx = sitk.CompositeTransform([sitk.AffineTransform(3), tx1, tx2])
    ptx = pickle.loads(pickle.dumps(ctx))
    _assert_composite_equal(ctx, ptx)


@pytest.mark.parametrize("transform_info", [
    ("AffineTransform", (3,)),
    ("BSplineTransform", (3, 3)),
    ("DisplacementFieldTransform", (3,)),
    ("Euler2DTransform", ()),
    ("Euler3DTransform", ()),
    ("ScaleSkewVersor3DTransform", ()),
    ("ScaleTransform", (3,)),
    ("ScaleVersor3DTransform", ()),
    ("Similarity2DTransform", ()),
    ("Similarity3DTransform", ()),
    ("Transform", ()),
    ("TranslationTransform", (3,)),
    ("VersorRigid3DTransform", ()),
    ("VersorTransform", ()),
    ("CompositeTransform", (3,)),
])
def test_name(transform_info):
    """Testing GetName method"""
    transform_name, args = transform_info
    tx = getattr(sitk, transform_name)(*args)
    assert transform_name == tx.GetName()


@pytest.mark.parametrize("transform_info", [
    ("AffineTransform", (3,)),
    ("BSplineTransform", (3, 3)),
    ("DisplacementFieldTransform", (3,)),
    ("Euler2DTransform", ()),
    ("Euler3DTransform", ()),
    ("ScaleSkewVersor3DTransform", ()),
    ("ScaleTransform", (3,)),
    ("ScaleVersor3DTransform", ()),
    ("Similarity2DTransform", ()),
    ("Similarity3DTransform", ()),
    ("Transform", ()),
    ("TranslationTransform", (3,)),
    ("VersorRigid3DTransform", ()),
    ("VersorTransform", ()),
    ("CompositeTransform", (3,)),
])
def test_default_pickle(transform_info):
    """Test pickling/unpickling of minimally constructed transforms"""
    transform_name, args = transform_info
    tx = getattr(sitk, transform_name)(*args)

    tx2 = pickle.loads(pickle.dumps(tx))
    _assert_transform_equal(tx, tx2, f"Testing {tx.GetName()}")

    tx3 = pickle.loads(pickle.dumps(sitk.Transform(tx)))
    _assert_transform_equal(
        tx,
        tx3,
        f"Testing {tx.GetName()} from Transform"
    )


@pytest.mark.parametrize("transform_info", [
    ("AffineTransform", (3,)),
    ("AffineTransform", (2,)),
    ("BSplineTransform", (3, 3)),
    ("BSplineTransform", (2, 3)),
    ("BSplineTransform", (2, 2)),
    ("DisplacementFieldTransform", (3,)),
    ("DisplacementFieldTransform", (2,)),
    ("Euler2DTransform", ()),
    ("Euler3DTransform", ()),
    ("ScaleSkewVersor3DTransform", ()),
    ("ScaleTransform", (2,)),
    ("ScaleTransform", (3,)),
    ("ScaleVersor3DTransform", ()),
    ("Similarity2DTransform", ()),
    ("Similarity3DTransform", ()),
    ("Transform", ()),
    ("TranslationTransform", (3,)),
    ("TranslationTransform", (2,)),
    ("VersorRigid3DTransform", ()),
    ("VersorTransform", ()),
    ("CompositeTransform", (3,)),
])
def test_downcast(transform_info):
    """Test Downcast method with minimally constructed transforms"""
    transform_name, args = transform_info
    tx = getattr(sitk, transform_name)(*args)

    tx2 = sitk.Transform(tx)
    tx3 = tx2.Downcast()

    _assert_transform_equal(tx, tx3)
    assert tx.__class__ == tx3.__class__, f"Testing {tx.GetName()}"


def test_deepcopy():
    """Test the custom __deepcopy__ method"""
    tx = sitk.AffineTransform(2)
    tx.SetMatrix([0.6, -0.5, -0.2, 0.8])

    tx_dc = deepcopy(tx)
    _assert_transform_equal(tx, tx_dc)

    tx_dc.SetCenter([7, 8])
    assert tx.GetCenter() != tx_dc.GetCenter()

    tx_c = copy.copy(tx)
    _assert_transform_equal(tx, tx_c)

    tx_c.SetCenter([9, 10])
    assert tx.GetCenter() != tx_c.GetCenter()


@pytest.mark.parametrize("transform_info", [
    ("AffineTransform", (3,)),
    ("AffineTransform", (2,)),
    ("BSplineTransform", (3, 3)),
    ("BSplineTransform", (2, 3)),
    ("BSplineTransform", (2, 2)),
    ("DisplacementFieldTransform", (3,)),
    ("DisplacementFieldTransform", (2,)),
    ("Euler2DTransform", ()),
    ("Euler3DTransform", ()),
    ("ScaleSkewVersor3DTransform", ()),
    ("ScaleTransform", (2,)),
    ("ScaleTransform", (3,)),
    ("ScaleVersor3DTransform", ()),
    ("Similarity2DTransform", ()),
    ("Similarity3DTransform", ()),
    ("Transform", ()),
    ("TranslationTransform", (3,)),
    ("TranslationTransform", (2,)),
    ("VersorRigid3DTransform", ()),
    ("VersorTransform", ()),
    ("CompositeTransform", (3,)),
])
@pytest.mark.parametrize("ext", ["txt", "tfm",  "hdf", "mat"])
def test_readwrite(transform_info, ext, test_dir):
    """Test reading and writing transforms"""

    transform_name, args = transform_info

    # Disable CompositeTransform with 'mat' extension
    if transform_name == "CompositeTransform" and ext == "mat":
        pytest.skip("CompositeTransform does not support 'mat' file format.")

    tx = getattr(sitk, transform_name)(*args)

    # test with concrete transform and Path object
    fname = test_dir / f"test_readwrite_{transform_name}.{ext}"

    print( f"Testing I/O {transform_name} with {ext} and filename: {fname}")

    sitk.WriteTransform(tx, fname)
    read_tx = sitk.ReadTransform(fname)
    _assert_transform_equal(tx, read_tx.Downcast(), f"Testing I/O {transform_name} with {ext}")
    _assert_transform_equal(read_tx, read_tx.Downcast(), "Testing ReadTransform downcast")

    # test with base transform class, and a regular string
    sitk.WriteTransform(sitk.Transform(tx), str(fname))
    read_tx = sitk.ReadTransform(str(fname))
    _assert_transform_equal(tx, read_tx.Downcast(), f"Testing I/O Transform {transform_name} with {ext}")
    _assert_transform_equal(read_tx, read_tx.Downcast(), "Testing ReadTransform downcast")


def test_downcast_returned():
    """Test python specific methods where returned type is downcasted to derived class."""
    tx = sitk.AffineTransform(3)
    itx = tx.GetInverse()
    assert tx.__class__ == itx.__class__
    assert tx.GetDimension() == itx.GetDimension()

    tx = sitk.Euler2DTransform()
    itx = tx.GetInverse()
    assert tx.__class__ == itx.__class__
    assert tx.GetDimension() == itx.GetDimension()

    tx_list = [
        sitk.AffineTransform(2),
        sitk.Euler2DTransform(),
        sitk.TranslationTransform(2),
        sitk.AffineTransform(2),
    ]
    ctx = sitk.CompositeTransform(tx_list)

    assert ctx.GetBackTransform().__class__ == sitk.AffineTransform

    for i, itx in enumerate(tx_list):
        assert ctx.GetNthTransform(i).__class__ == itx.__class__
