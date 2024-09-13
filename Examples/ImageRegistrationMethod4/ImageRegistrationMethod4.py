#!/usr/bin/env python
# =========================================================================
#
#  Copyright NumFOCUS
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#         http://www.apache.org/licenses/LICENSE-2.0.txt
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#
# =========================================================================

""" A SimpleITK example demonstrating image registration using Mattes mutual
    information as the metric. """

import sys
import os
import SimpleITK as sitk


def command_iteration(method):
    """ Callback invoked when the optimization has an iteration. """
    print(
        f"{method.GetOptimizerIteration():3} "
        + f"= {method.GetMetricValue():10.5f} "
        + f": {method.GetOptimizerPosition()}"
    )


def main(args):
    """ A SimpleITK example demonstrating image registration using Mattes mutual
        information as the metric. """

    if len(args) < 3:
        print(
            "Usage:",
            "ImageRegistrationMethod4",
            "<fixedImageFilter> <movingImageFile>",
            "<outputTransformFile> <numberOfBins> <samplingPercentage>",
        )
        sys.exit(1)

    fixed = sitk.ReadImage(args[1], sitk.sitkFloat32)
    moving = sitk.ReadImage(args[2], sitk.sitkFloat32)

    numberOfBins = 24
    samplingPercentage = 0.10

    if len(args) > 4:
        numberOfBins = int(args[4])
    if len(args) > 5:
        samplingPercentage = float(args[5])

    R = sitk.ImageRegistrationMethod()
    R.SetMetricAsMattesMutualInformation(numberOfBins)
    R.SetMetricSamplingPercentage(samplingPercentage, sitk.sitkWallClock)
    R.SetMetricSamplingStrategy(R.RANDOM)
    R.SetOptimizerAsRegularStepGradientDescent(1.0, 0.001, 200)
    R.SetInitialTransform(sitk.TranslationTransform(fixed.GetDimension()))
    R.SetInterpolator(sitk.sitkLinear)

    R.AddCommand(sitk.sitkIterationEvent, lambda: command_iteration(R))

    outTx = R.Execute(fixed, moving)

    print("-------")
    print(outTx)
    print(f"Optimizer stop condition: {R.GetOptimizerStopConditionDescription()}")
    print(f" Iteration: {R.GetOptimizerIteration()}")
    print(f" Metric value: {R.GetMetricValue()}")

    sitk.WriteTransform(outTx, args[3])

    resampler = sitk.ResampleImageFilter()
    resampler.SetReferenceImage(fixed)
    resampler.SetInterpolator(sitk.sitkLinear)
    resampler.SetDefaultPixelValue(100)
    resampler.SetTransform(outTx)

    out = resampler.Execute(moving)
    simg1 = sitk.Cast(sitk.RescaleIntensity(fixed), sitk.sitkUInt8)
    simg2 = sitk.Cast(sitk.RescaleIntensity(out), sitk.sitkUInt8)
    cimg = sitk.Compose(simg1, simg2, simg1 // 2.0 + simg2 // 2.0)

    return {"fixed": fixed, "moving": moving, "composition": cimg}


if __name__ == "__main__":
    return_dict = main(sys.argv)
    if "SITK_NOSHOW" not in os.environ:
        sitk.Show(return_dict["composition"], "ImageRegistration4 Composition")
