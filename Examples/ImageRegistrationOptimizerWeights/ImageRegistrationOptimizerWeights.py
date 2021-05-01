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

if len(sys.argv) < 4:
    print("Usage:", sys.argv[0], "<fixedImageFile> <movingImageFile>",
          "<outputTransformFile>")
    sys.exit(1)

fixed_image = sitk.ReadImage(sys.argv[1], sitk.sitkFloat32)
moving_image = sitk.ReadImage(sys.argv[2], sitk.sitkFloat32)

# initialization
transform = sitk.CenteredTransformInitializer(fixed_image,
                                              moving_image,
                                              sitk.Euler3DTransform(),
                                              sitk.CenteredTransformInitializerFilter.GEOMETRY)
# registration
registration_method = sitk.ImageRegistrationMethod()
registration_method.SetMetricAsCorrelation()
registration_method.SetMetricSamplingStrategy(registration_method.NONE)
registration_method.SetInterpolator(sitk.sitkLinear)
registration_method.SetOptimizerAsGradientDescent(learningRate=1.0,
                                                  numberOfIterations=300,
                                                  convergenceMinimumValue=1e-6,
                                                  convergenceWindowSize=10)
registration_method.SetOptimizerScalesFromPhysicalShift()
registration_method.SetInitialTransform(transform, inPlace=True)
registration_method.SetOptimizerWeights([0,0,1,1,1,1])
registration_method.Execute(fixed_image, moving_image)

print("-------")
print(f"Final transform parameters: {transform.GetParameters()}")
print(f"Optimizer stop condition: {registration_method.GetOptimizerStopConditionDescription()}")
print(f"Iteration: {registration_method.GetOptimizerIteration()}")
print(f"Metric value: {registration_method.GetMetricValue()}")

sitk.WriteTransform(transform, sys.argv[3])
