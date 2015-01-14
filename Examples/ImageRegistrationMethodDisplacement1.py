#!/usr/bin/env python
#=========================================================================
#
#  Copyright Insight Software Consortium
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
#=========================================================================

from __future__ import print_function

import SimpleITK as sitk
import sys
import os


def command_iteration(method) :
    print("{0:3} = {1:10.5f}".format(method.GetOptimizerIteration(),
                                     method.GetMetricValue()))

if len ( sys.argv ) < 4:
    print( "Usage: {0} <fixedImageFilter> <movingImageFile> <outputTransformFile>".format(sys.argv[0]))
    sys.exit ( 1 )


fixed = sitk.ReadImage(sys.argv[1], sitk.sitkFloat32)

moving = sitk.ReadImage(sys.argv[2], sitk.sitkFloat32)

initialTx = sitk.CenteredTransformInitializer(fixed, moving, sitk.AffineTransform(fixed.GetDimension()))

R = sitk.ImageRegistrationMethod()

R.SetShrinkFactorsPerLevel([3,2,1])
R.SetSmoothingSigmasPerLevel([2,1,1])

R.SetMetricAsJointHistogramMutualInformation(20)
R.SetMetricSamplingPercentagePerLevel([0.05, 0.2, 0.5])
R.SetMetricSamplingStrategy(R.RANDOM)


R.SetOptimizerAsGradientDescent(learningRate=1.0,
                                numberOfIterations=100,
                                convergenceMinimumValue = 1e-6,
                                convergenceWindowSize = 10,
                                estimateLearningRate = R.EachIteration,
                                maximumStepSizeInPhysicalUnits = 1.0)
R.SetOptimizerScalesFromPhysicalShift()

R.SetInitialTransform(initialTx,inPlace=True)

R.SetInterpolator(sitk.sitkLinear)

R.AddCommand( sitk.sitkIterationEvent, lambda: command_iteration(R) )

outTx = R.Execute(fixed, moving)

print("-------")
print(outTx)
print("Optimizer stop condition: {0}".format(R.GetOptimizerStopConditionDescription()))
print(" Iteration: {0}".format(R.GetOptimizerIteration()))
print(" Metric value: {0}".format(R.GetMetricValue()))


displacementField = sitk.Image(fixed.GetSize(), sitk.sitkVectorFloat64)
displacementField.CopyInformation(fixed)
displacementTx = sitk.DisplacementFieldTransform(displacementField)
del displacementField
displacementTx.SetSmoothingGaussianOnUpdate(varianceForUpdateField=0.5,
                                            varianceForTotalField=1.0)


R.SetMovingInitialTransform(outTx)
R.SetInitialTransform(displacementTx, inPlace=True)

R.SetMetricAsANTSNeighborhoodCorrelation(2)

R.SetShrinkFactorsPerLevel([1]) # TODO get adaptors working!!!
R.SetSmoothingSigmasPerLevel([2])

R.SetOptimizerScalesFromIndexShift()
R.SetOptimizerAsGradientDescent(learningRate=1,
                                numberOfIterations=300,
                                estimateLearningRate=R.EachIteration)


outTx.AddTransform( R.Execute(fixed, moving) )


print("-------")
print(outTx)
print("Optimizer stop condition: {0}".format(R.GetOptimizerStopConditionDescription()))
print(" Iteration: {0}".format(R.GetOptimizerIteration()))
print(" Metric value: {0}".format(R.GetMetricValue()))


sitk.WriteTransform(outTx,  sys.argv[3])

if ( not "SITK_NOSHOW" in os.environ ):

    sitk.Show(displacementTx.GetDisplacementField(), "Displacement Field")

    resampler = sitk.ResampleImageFilter()
    resampler.SetReferenceImage(fixed);
    resampler.SetInterpolator(sitk.sitkLinear)
    resampler.SetDefaultPixelValue(100)
    resampler.SetTransform(outTx)

    out = resampler.Execute(moving)
    simg1 = sitk.Cast(sitk.RescaleIntensity(fixed), sitk.sitkUInt8)
    simg2 = sitk.Cast(sitk.RescaleIntensity(out), sitk.sitkUInt8)
    cimg = sitk.Compose(simg1, simg2, simg1/2.+simg2/2.)
    sitk.Show( cimg, "ImageRegistration1 Composition" )
