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

import math

import pytest

import SimpleITK as sitk

SHIFT = (3.0, -2.0)


@pytest.fixture
def brain_pair(data_finder):
    """A brain slice and a copy translated by SHIFT.

    The moving image is moving(x) = fixed(x + SHIFT), so the expected
    displacement from the fixed domain to the moving domain is -SHIFT.
    """
    fixed = sitk.ReadImage(
        data_finder.get_file("Input/BrainProtonDensitySliceBorder20.png"),
        sitk.sitkFloat32,
    )
    moving = sitk.Resample(
        fixed, fixed, sitk.TranslationTransform(2, SHIFT), sitk.sitkLinear, 0.0
    )
    mask = sitk.Cast(fixed > 50, sitk.sitkUInt8)
    return fixed, moving, mask


def mean_squared_difference(a, b):
    stats = sitk.StatisticsImageFilter()
    stats.Execute(sitk.Square(a - b))
    return stats.GetMean()


def mean_displacement_in_mask(field, mask):
    means = []
    for d in range(field.GetDimension()):
        stats = sitk.LabelStatisticsImageFilter()
        stats.Execute(sitk.VectorIndexSelectionCast(field, d), mask)
        means.append(stats.GetMean(1))
    return means


def test_defaults():
    R = sitk.SyNImageRegistrationMethod()

    assert isinstance(R, sitk.ProcessObject)
    assert R.GetName() == "SyNImageRegistrationMethod"
    assert "SyNImageRegistrationMethod" in str(R)

    assert R.GetInterpolator() == sitk.sitkLinear
    assert list(R.GetNumberOfIterationsPerLevel()) == [100, 70, 50, 20]
    assert R.GetLearningRate() == 0.2
    assert R.GetConvergenceThreshold() == 1e-6
    assert R.GetConvergenceWindowSize() == 10
    assert R.GetGaussianSmoothingVarianceForTheUpdateField() == 3.0
    assert R.GetGaussianSmoothingVarianceForTheTotalField() == 0.0
    assert R.GetDownsampleImagesForMetricDerivatives()
    assert not R.GetAverageMidPointGradients()
    assert R.GetInitialTransformInPlace()
    assert R.GetStopConditionDescription() == ""

    R.SetNumberOfIterationsPerLevel([5, 3])
    assert list(R.GetNumberOfIterationsPerLevel()) == [5, 3]
    R.SetMetricSamplingStrategy(R.REGULAR)
    R.SetMetricSamplingPercentage(0.5, 42)
    assert list(R.GetMetricSamplingPercentagePerLevel()) == [0.5]

    with pytest.raises(RuntimeError):
        R.SetInitialTransform(sitk.AffineTransform(2))


def test_translation_2d(brain_pair):
    fixed, moving, mask = brain_pair

    R = sitk.SyNImageRegistrationMethod()
    R.SetNumberOfIterationsPerLevel([40, 30, 20, 10])

    iterations = []
    levels = []
    R.AddCommand(
        sitk.sitkIterationEvent,
        lambda: iterations.append(
            (R.GetCurrentLevel(), R.GetCurrentIteration(), R.GetMetricValue())
        ),
    )
    R.AddCommand(
        sitk.sitkMultiResolutionIterationEvent,
        lambda: levels.append(R.GetCurrentLevel()),
    )

    tx = R.Execute(fixed, moving)

    assert isinstance(tx, sitk.DisplacementFieldTransform)
    assert levels == [0, 1, 2, 3]
    assert 4 <= len(iterations) <= 100
    assert all(math.isfinite(m) for _, _, m in iterations)
    assert all(it >= 1 for _, it, _ in iterations)
    assert R.GetCurrentLevel() == 3
    assert "level 3" in R.GetStopConditionDescription()

    field = tx.GetDisplacementField()
    inverse_field = tx.GetInverseDisplacementField()
    assert field.GetSize() == fixed.GetSize()
    assert inverse_field.GetSize() == fixed.GetSize()

    mean = mean_displacement_in_mask(field, mask)
    assert mean[0] == pytest.approx(-SHIFT[0], abs=0.5)
    assert mean[1] == pytest.approx(-SHIFT[1], abs=0.5)

    inverse_mean = mean_displacement_in_mask(inverse_field, mask)
    assert inverse_mean[0] == pytest.approx(SHIFT[0], abs=0.5)
    assert inverse_mean[1] == pytest.approx(SHIFT[1], abs=0.5)

    before = mean_squared_difference(fixed, moving)
    after = mean_squared_difference(
        fixed, sitk.Resample(moving, fixed, tx, sitk.sitkLinear, 0.0)
    )
    assert after < 0.25 * before

    inverse = tx.GetInverse()
    for p in [(100.0, 120.0), (80.0, 150.0)]:
        q = inverse.TransformPoint(tx.TransformPoint(p))
        assert q == pytest.approx(p, abs=0.1)


def test_initial_transform_in_place(brain_pair):
    fixed, moving, mask = brain_pair

    R = sitk.SyNImageRegistrationMethod()
    R.SetShrinkFactorsPerLevel([4, 1])
    R.SetSmoothingSigmasPerLevel([1.0, 0.0])
    R.SetNumberOfIterationsPerLevel([5, 3])
    R.SetMetricAsMeanSquares()
    R.SetMetricFixedMask(mask)

    not_in_place = sitk.DisplacementFieldTransform(2)
    R.SetInitialTransform(not_in_place, inPlace=False)
    result = R.Execute(fixed, moving)
    assert not_in_place.GetDisplacementField().GetSize() == (0, 0)
    assert result.GetDisplacementField().GetSize() == fixed.GetSize()

    in_place = sitk.DisplacementFieldTransform(2)
    R.SetInitialTransform(in_place, inPlace=True)
    result = R.Execute(fixed, moving)
    assert in_place.GetDisplacementField().GetSize() == fixed.GetSize()
    assert in_place.GetInverseDisplacementField().GetSize() == fixed.GetSize()
    assert in_place.GetParameters() == result.GetParameters()
    assert R.GetCurrentIteration() == 3

    # The fields are defined on the grid of the last level.
    R.SetShrinkFactorsPerLevel([4, 2])
    result = R.Execute(fixed, moving)
    assert result.GetDisplacementField().GetSize() == sitk.Shrink(fixed, [2, 2]).GetSize()


def test_level_mismatch(brain_pair):
    fixed, moving, _ = brain_pair

    R = sitk.SyNImageRegistrationMethod()
    R.SetNumberOfIterationsPerLevel([5, 3])
    with pytest.raises(RuntimeError):
        R.Execute(fixed, moving)
