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


""" Apply SimpleITK's SmoothGaussianImageFilter to an image. """

import os
import sys
import SimpleITK as sitk


def main(args):
    """ Apply SimpleITK's SmoothGaussianImageFilter to an image. """
    if len(args) < 4:
        print("Usage: SimpleGaussian <input> <sigma> <output>")
        sys.exit(1)

    reader = sitk.ImageFileReader()
    reader.SetFileName(args[1])
    input_image = reader.Execute()

    pixelID = input_image.GetPixelID()

    gaussian = sitk.SmoothingRecursiveGaussianImageFilter()
    gaussian.SetSigma(float(args[2]))
    blur_image = gaussian.Execute(input_image)

    caster = sitk.CastImageFilter()
    caster.SetOutputPixelType(pixelID)
    blur_image = caster.Execute(blur_image)

    writer = sitk.ImageFileWriter()
    writer.SetFileName(args[3])
    writer.Execute(blur_image)

    return_dict = {"input_image": input_image, "blur_image": blur_image}
    return return_dict


# Display the results
if __name__ == "__main__":
    in_image, out_image = main(sys.argv)
    if "SITK_NOSHOW" not in os.environ:
        sitk.Show(out_image, "Simple Gaussian")
