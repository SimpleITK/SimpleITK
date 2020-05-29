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

import os
import sys

import SimpleITK as sitk

if len(sys.argv) < 4:
    print("Usage: %s <input> <sigma> <output>" % (sys.argv[0]))
    sys.exit(1)

image = sitk.ReadImage(sys.argv[1])

pixelID = image.GetPixelID()

image = sitk.SmoothingRecursiveGaussian(image, float(sys.argv[2]))

sitk.WriteImage(sitk.Cast(image, pixelID), sys.argv[3])

if ("SITK_NOSHOW" not in os.environ):
    sitk.Show(sitk.Cast(image, pixelID), "Simple Gaussian Procedural")
