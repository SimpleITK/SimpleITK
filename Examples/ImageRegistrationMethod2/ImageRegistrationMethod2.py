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

import SimpleITK as sitk
import sys
import os


def command_iteration(method):
    print(
        f"{method.GetOptimizerIteration():3} "
        + f" = {method.GetMetricValue():7.5f} "
        + f" : {method.GetOptimizerPosition()}"
    )


def main(args):
    if len(args) < 3:
        print(
            "Usage:",
            "ImageRegistrationMethod2",
            "<fixedImageFilter> <movingImageFile>  <outputTransformFile>",
        )
        sys.exit(1)

    fixed = sitk.ReadImage(args[1], sitk.sitkFloat32)
    fixed = sitk.Normalize(fixed)
    fixed = sitk.DiscreteGaussian(fixed, 2.0)

    moving = sitk.ReadImage(args[2], sitk.sitkFloat32)
    moving = sitk.Normalize(moving)
    moving = sitk.DiscreteGaussian(moving, 2.0)

    R = sitk.ImageRegistrationMethod()

    R.SetMetricAsJointHistogramMutualInformation()

    R.SetOptimizerAsGradientDescentLineSearch(
        learningRate=1.0,
        numberOfIterations=200,
        convergenceMinimumValue=1e-5,
        convergenceWindowSize=5,
    )

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
    resampler.SetDefaultPixelValue(1)
    resampler.SetTransform(outTx)

    out = resampler.Execute(moving)

    simg1 = sitk.Cast(sitk.RescaleIntensity(fixed), sitk.sitkUInt8)
    simg2 = sitk.Cast(sitk.RescaleIntensity(out), sitk.sitkUInt8)
    cimg = sitk.Compose(simg1, simg2, simg1 // 2.0 + simg2 // 2.0)

    return {"fixed": fixed,
            "moving": moving,
            "composition": cimg}


if __name__ == "__main__":
    return_dict = main(sys.argv)
    if "SITK_NOSHOW" not in os.environ:
        sitk.Show(return_dict["composition"], "ImageRegistration2 Composition")
