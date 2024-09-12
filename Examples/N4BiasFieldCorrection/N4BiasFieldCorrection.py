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

""" A SimpleITK example that demonstrates how to apply N4BiasFieldImageFilter
    to an image. """

import sys
import os
import SimpleITK as sitk


def main(args):
    """ A SimpleITK example that demonstrates how to apply N4BiasFieldImageFilter
        to an image. """
    if len(args) < 2:
        print(
            "Usage: N4BiasFieldCorrection inputImage "
            + "outputImage [shrinkFactor] [maskImage] [numberOfIterations] "
            + "[numberOfFittingLevels]"
        )
        sys.exit(1)

    inputImage = sitk.ReadImage(args[1], sitk.sitkFloat32)
    image = inputImage

    if len(args) > 4:
        maskImage = sitk.ReadImage(args[4], sitk.sitkUInt8)
    else:
        maskImage = sitk.OtsuThreshold(inputImage, 0, 1, 200)

    shrinkFactor = 1
    if len(args) > 3:
        shrinkFactor = int(args[3])
        if shrinkFactor > 1:
            image = sitk.Shrink(inputImage, [shrinkFactor] * inputImage.GetDimension())
            maskImage = sitk.Shrink(
                maskImage, [shrinkFactor] * inputImage.GetDimension()
            )

    corrector = sitk.N4BiasFieldCorrectionImageFilter()

    numberFittingLevels = 4

    if len(args) > 6:
        numberFittingLevels = int(args[6])

    if len(args) > 5:
        corrector.SetMaximumNumberOfIterations([int(args[5])] * numberFittingLevels)

    corrected_image = corrector.Execute(image, maskImage)

    log_bias_field = corrector.GetLogBiasFieldAsImage(inputImage)

    corrected_image_full_resolution = inputImage / sitk.Exp(log_bias_field)

    sitk.WriteImage(corrected_image_full_resolution, args[2])

    if shrinkFactor > 1:
        sitk.WriteImage(
            corrected_image, "Python-Example-N4BiasFieldCorrection-shrunk.nrrd"
        )

    return_images = {
        "input_image": inputImage,
        "mask_image": maskImage,
        "log_bias_field": log_bias_field,
        "corrected_image": corrected_image,
    }
    return return_images


if __name__ == "__main__":
    images = main(sys.argv)
    if "SITK_NOSHOW" not in os.environ:
        sitk.Show(images["input_image"], "Input Image 20")
        sitk.Show(images["mask_image"], "Mask Image")
        sitk.Show(images["log_bias_field"], "Log Bias Image")
        sitk.Show(images["corrected_image"], "N4 Corrected")
