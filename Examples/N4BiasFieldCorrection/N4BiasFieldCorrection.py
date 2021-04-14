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

from __future__ import print_function

import SimpleITK as sitk
import sys
import os

if len(sys.argv) < 2:
    print("Usage: N4BiasFieldCorrection inputImage " +
          "outputImage [shrinkFactor] [maskImage] [numberOfIterations] " +
          "[numberOfFittingLevels]")
    sys.exit(1)

inputImage = sitk.ReadImage(sys.argv[1], sitk.sitkFloat32)
image = inputImage

if len(sys.argv) > 4:
    maskImage = sitk.ReadImage(sys.argv[4], sitk.sitkUint8)
else:
    maskImage = sitk.OtsuThreshold(inputImage, 0, 1, 200)

if len(sys.argv) > 3:
    image = sitk.Shrink(inputImage,
                             [int(sys.argv[3])] * inputImage.GetDimension())
    maskImage = sitk.Shrink(maskImage,
                            [int(sys.argv[3])] * inputImage.GetDimension())

corrector = sitk.N4BiasFieldCorrectionImageFilter()

numberFittingLevels = 4

if len(sys.argv) > 6:
    numberFittingLevels = int(sys.argv[6])

if len(sys.argv) > 5:
    corrector.SetMaximumNumberOfIterations([int(sys.argv[5])]
                                           * numberFittingLevels)

corrected_image = corrector.Execute(image, maskImage)


log_bias_field = corrector.GetLogBiasFieldAsImage(inputImage)

bias_field = inputImage / sitk.Exp( log_bias_field )

sitk.WriteImage(corrected_image, sys.argv[2])

if ("SITK_NOSHOW" not in os.environ):
    sitk.Show(corrected_image, "N4 Corrected")
