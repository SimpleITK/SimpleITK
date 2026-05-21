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

if #arg < 5 then
    print("Usage: elx <fixedImage> <movingImage> <parameterFile> <outputImage> <outputParameterFile>")
    os.exit(1)
end

-- Instantiate SimpleElastix
elastixImageFilter = SimpleITK.ElastixImageFilter()

-- Read input
elastixImageFilter:SetFixedImage(SimpleITK.ReadImage(arg[1]))
elastixImageFilter:SetMovingImage(SimpleITK.ReadImage(arg[2]))
elastixImageFilter:SetParameterMap(SimpleITK.ReadParameterFile(arg[3]))
elastixImageFilter:LogToConsoleOn()

-- Run registration
elastixImageFilter:Execute()

-- Write result image
SimpleITK.WriteImage(elastixImageFilter:GetResultImage(), arg[4])

-- Write parameter file. This example only supports one parameter map and one transform parameter map.
parameterMaps = elastixImageFilter:GetTransformParameterMaps()
SimpleITK.WriteParameterFile(parameterMaps[0], arg[5])
