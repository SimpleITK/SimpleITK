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
    print("Usage: %s <input>" % (sys.argv[0]))
    sys.exit(1)

image = sitk.Cast(sitk.ReadImage(sys.argv[1]), sitk.sitkFloat32)

edges = sitk.CannyEdgeDetection(image, lowerThreshold=200, upperThreshold=400,
                                variance=[4] * 3)

stats = sitk.StatisticsImageFilter()
stats.Execute(image)

if ("SITK_NOSHOW" not in os.environ):
    sitk.Show(sitk.Maximum(image * 0.5, edges * stats.GetMaximum() * .5))
