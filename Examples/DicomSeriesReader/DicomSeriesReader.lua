--=========================================================================
--
--  Copyright Insight Software Consortium
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

if #arg < 2 then
  print ( "Usage: DicomSeriesReader <input_directory> <output_file>" )
  os.exit ( 1 )
end

print( "Reading Dicom directory:", arg[1] )
reader = SimpleITK.ImageSeriesReader()

dicom_names = SimpleITK.ImageSeriesReader.GetGDCMSeriesFileNames( arg[1] )
reader:SetFileNames ( dicom_names )

image = reader:Execute();

size = image:GetSize();
print("Image size:", size[0], size[1], size[2]);

print( "Writing image:", arg[2] )
SimpleITK.WriteImage( image, arg[2] )
