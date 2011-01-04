--[[=========================================================================
 -
 -  Copyright Insight Software Consortium
 -
 -  Licensed under the Apache License, Version 2.0 (the "License");
 -  you may not use this file except in compliance with the License.
 -  You may obtain a copy of the License at
 -
 -         http://www.apache.org/licenses/LICENSE-2.0.txt
 -
 -  Unless required by applicable law or agreed to in writing, software
 -  distributed under the License is distributed on an "AS IS" BASIS,
 -  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 -  See the License for the specific language governing permissions and
 -  limitations under the License.
 -
 -=========================================================================]]

--[[ Check Command Line ]]
if #arg < 7 then
  print ( "Usage: ConnectedThresholdImageFilter inputImage outputImage lowerThreshold upperThreshold seedX seedY [seed2X seed2Y ... ]" )
  os.exit ( 1 )
end

--[[ Read the image ]]
reader = SimpleITK.ImageFileReader()
reader:SetFilename( arg[1] )
image = reader:Execute()

--[[ Set up the writer ]]
writer = SimpleITK.ImageFileWriter()
writer:SetFilename( arg[2] )

--[[ Blur using CurvatureFlowImageFilter ]]
blurFilter = SimpleITK.CurvatureFlowImageFilter()
blurFilter:SetNumberOfIterations( 5 )
blurFilter:SetTimeStep( 0.125 )
image = blurFilter:Execute( image )

--[[ Set up and run the setmentation filter ]]
segmentationFilter = SimpleITK.ConnectedThresholdImageFilter()
segmentationFilter:SetLower( arg[3] )
segmentationFilter:SetUpper( arg[4] )
segmentationFilter:SetReplaceValue( 255 )

for i=5,(#arg)-1,2 do
  seed = SimpleITK.Index( arg[i], arg[i+1] )
  segmentationFilter:AddSeed( seed )
  print( "Adding seed at " .. seed:ToString() )
end

image = segmentationFilter:Execute( image )

--[[ Write out the result ]]
writer:Execute( image )

