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

if len(sys.argv) < 8:
    print("Usage:", sys.argv[0],
          "<inputImage> <outputImage> <sigma> <InitialDistance>",
          "<PropagationScaling> <seedX> <seedY> <?seedZ>")
    sys.exit(1)

inputImage = sys.argv[1]
outputImage = sys.argv[2]
sigma = float(sys.argv[3])
initialDistance = float(sys.argv[4])
propagationScaling = float(sys.argv[5])
seed = [float(sys.argv[6]), float(sys.argv[7])]

if len(sys.argv) > 8:
    seed.append(float(sys.argv[8]))

reader = sitk.ImageFileReader()
reader.SetFileName(inputImage)
image = reader.Execute()

gradientMagnitude = sitk.GradientMagnitudeRecursiveGaussianImageFilter()
gradientMagnitude.SetSigma(sigma)

featureImage = sitk.BoundedReciprocal(gradientMagnitude.Execute(image))

seedImage = sitk.Image(image.GetSize()[0], image.GetSize()[1], sitk.sitkUInt8)
seedImage.SetSpacing(image.GetSpacing())
seedImage.SetOrigin(image.GetOrigin())
seedImage.SetDirection(image.GetDirection())
seedImage[seedImage.TransformPhysicalPointToIndex(seed)] = 1

distance = sitk.SignedMaurerDistanceMapImageFilter()
distance.InsideIsPositiveOff()
distance.UseImageSpacingOn()

initialImage = sitk.BinaryThreshold(distance.Execute(seedImage), -1000, 10)
initialImage = sitk.Cast(initialImage, featureImage.GetPixelID()) * -1 + 0.5

geodesicActiveContour = sitk.GeodesicActiveContourLevelSetImageFilter()
geodesicActiveContour.SetPropagationScaling(propagationScaling)
geodesicActiveContour.SetCurvatureScaling(.5)
geodesicActiveContour.SetAdvectionScaling(1.0)
geodesicActiveContour.SetMaximumRMSError(0.01)
geodesicActiveContour.SetNumberOfIterations(1000)

levelset = geodesicActiveContour.Execute(initialImage, featureImage)

print("RMS Change: ", geodesicActiveContour.GetRMSChange())
print("Elapsed Iterations: ", geodesicActiveContour.GetElapsedIterations())

contour = sitk.BinaryContour(sitk.BinaryThreshold(levelset, -1000, 0))

if ("SITK_NOSHOW" not in os.environ):
    sitk.Show(sitk.LabelOverlay(image, contour), "Levelset Countour")
