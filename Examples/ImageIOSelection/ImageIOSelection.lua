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

local write = io.write

require "SimpleITK"

if #arg < 1 then
  print ( "Usage: ImageIOSelection image_file_name" )
  os.exit ( 1 )
end

-- Find out which image IOs are supported
reader = SimpleITK.ImageFileReader()
image_ios = reader:GetRegisteredImageIOs()
write("The supported image IOs are: ")
for i=0,image_ios:size()-1 do
  write(image_ios[i], " ")
end
write("\n")
print("--------------------")

-- Another option is to just print the reader and see which
-- IOs are supported
print(reader:ToString())
print("--------------------")

-- Force the use of a specific IO.
reader:SetImageIO("PNGImageIO")

-- Remember that Lua arrays are 1-based, and that arg does not contain the application name!
reader:SetFileName ( arg[1] )

-- We need a function to pass to pcall, the Lua error handler.
-- So we embed the reader's Execute method in this function.
function read_execute( reader )
  reader:Execute()
end

-- Call the reader's execute method through Lua's pcall error handler
--
local status, err = pcall(read_execute, reader)
if status then
  -- The reader succeeded
  write("Read image: ")
  write(arg[1])
  write("\n")
else
  -- The reader failed
  write("Read failed: ")
  write(err)
  write("\n")
end
