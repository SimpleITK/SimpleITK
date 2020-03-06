--=========================================================================
--
--  Copyright NumFOCUS
--
--  Licensed under the Apache License, Version 2.0 (the "License");
--  you may not use this file except in compliance with the License.
--  You may obtain a copy of the License at
--
--         http://www.apache.org/licenses/LICENSE-2.0.txt
--
--  Unless required by applicable law or agreed to in writing, software
--  distributed under the License is distributed on an "AS IS" BASIS,
--  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
--  See the License for the specific language governing permissions and
--  limitations under the License.
--
--=========================================================================

require "SimpleITK"

function command_iteration(method)
    print(method)
    pos = method:GetOptimizedPosition()
    print( string.format("%3d = %f : (%f, %f)", method:GetOptimizerIteration(),
        method:GetMetricValue(), pos[1], pos[2] ) )
end

if #arg < 3 then
    print( string.format("Usage: %s <fixedImageFilter> <movingImageFile> <outputTransformFile>", arg[0]) )
    os.exit ( 1 )
end

fixed = SimpleITK.ReadImage( arg[1], SimpleITK.sitkFloat32 )

moving = SimpleITK.ReadImage( arg[2], SimpleITK.sitkFloat32 )


R = SimpleITK.ImageRegistrationMethod()
R:SetMetricAsMeanSquares()
R:SetOptimizerAsRegularStepGradientDescent( 4.0, .01, 200 )
R:SetInitialTransform( SimpleITK.Transform( fixed:GetDimension(), SimpleITK.sitkTranslation ) )
R:SetInterpolator( SimpleITK.sitkLinear )

-- callback for progress reporting doesn't work yet in Lua
-- R:AddCommand( SimpleITK.sitkIterationEvent, command_iteration(R) )

outTx = R:Execute(fixed, moving)

print("-------")
print(outTx)
print(string.format("Optimizer stop condition: %s", R:GetOptimizerStopConditionDescription()) )
print(" Iteration: ", R:GetOptimizerIteration() )
print(" Metric value: ", R:GetMetricValue() )

SimpleITK.WriteTransform(outTx,  arg[3])
