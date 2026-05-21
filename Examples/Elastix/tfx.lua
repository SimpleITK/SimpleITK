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

if #arg < 3 then
    print("Usage: tfx <inputImage> <parameterFile> <outputImage>")
    os.exit(1)
end

-- Instantiate transformix
transformixImageFilter = SimpleITK.TransformixImageFilter()
transformixImageFilter:LogToConsoleOn()

-- Read input
transformixImageFilter:SetMovingImage(SimpleITK.ReadImage(arg[1]))
transformixImageFilter:SetTransformParameterMap(SimpleITK.ReadParameterFile(arg[2]))

-- Run warp
transformixImageFilter:Execute()

-- Write result image
SimpleITK.WriteImage(transformixImageFilter:GetResultImage(), arg[3])
