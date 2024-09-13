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

""" A SimpleITK example demonstrating the FastMarchingImageFilter class. """

import sys
import SimpleITK as sitk


def main(args):
    """ A SimpleITK example demonstrating the FastMarchingImageFilter class. """
    if len(args) < 10:
        print(
            "Usage:",
            "FastMarchingSegmentation",
            "<inputImage> <outputImage> <seedX> <seedY> <Sigma>",
            "<SigmoidAlpha> <SigmoidBeta> <TimeThreshold>",
            "<StoppingTime>",
        )
        sys.exit(1)

    inputFilename = args[1]
    outputFilename = args[2]

    seedPosition = (int(args[3]), int(args[4]))

    sigma = float(args[5])
    alpha = float(args[6])
    beta = float(args[7])
    timeThreshold = float(args[8])
    stoppingTime = float(args[9])

    inputImage = sitk.ReadImage(inputFilename, sitk.sitkFloat32)

    smoothing = sitk.CurvatureAnisotropicDiffusionImageFilter()
    smoothing.SetTimeStep(0.125)
    smoothing.SetNumberOfIterations(5)
    smoothing.SetConductanceParameter(9.0)
    smoothingOutput = smoothing.Execute(inputImage)

    gradientMagnitude = sitk.GradientMagnitudeRecursiveGaussianImageFilter()
    gradientMagnitude.SetSigma(sigma)
    gradientMagnitudeOutput = gradientMagnitude.Execute(smoothingOutput)

    sigmoid = sitk.SigmoidImageFilter()
    sigmoid.SetOutputMinimum(0.0)
    sigmoid.SetOutputMaximum(1.0)
    sigmoid.SetAlpha(alpha)
    sigmoid.SetBeta(beta)
    sigmoidOutput = sigmoid.Execute(gradientMagnitudeOutput)

    fastMarching = sitk.FastMarchingImageFilter()

    seedValue = 0
    trialPoint = (seedPosition[0], seedPosition[1], seedValue)

    fastMarching.AddTrialPoint(trialPoint)

    fastMarching.SetStoppingValue(stoppingTime)

    fastMarchingOutput = fastMarching.Execute(sigmoidOutput)

    thresholder = sitk.BinaryThresholdImageFilter()
    thresholder.SetLowerThreshold(0.0)
    thresholder.SetUpperThreshold(timeThreshold)
    thresholder.SetOutsideValue(0)
    thresholder.SetInsideValue(255)

    result = thresholder.Execute(fastMarchingOutput)

    sitk.WriteImage(result, outputFilename)

    image_dict = {
        "InputImage": inputImage,
        "SpeedImage": sigmoidOutput,
        "TimeCrossingMap": fastMarchingOutput,
        "Segmentation": result,
    }
    return image_dict


if __name__ == "__main__":
    return_dict = main(sys.argv)
