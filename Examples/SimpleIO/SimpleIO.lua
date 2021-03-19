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

-- These examples are used in the I/O documentation page. The IO.rst file
-- pulls the code examples based their line numbers in this file. So any
-- change in the line numbers of the code below will break the I/O page.


function example1(inputImageFileName, outputImageFileName)
  require "SimpleITK"

  reader = SimpleITK.ImageFileReader()
  reader:SetImageIO("PNGImageIO")
  reader:SetFileName(inputImageFileName)
  image = reader:Execute();

  writer = SimpleITK.ImageFileWriter()
  writer:SetFileName(outputImageFileName)
  writer:Execute(image);
end

function example2(inputImageFileName, outputImageFileName)
  require "SimpleITK"

  image = SimpleITK.ReadImage(inputImageFileName, SimpleITK.sitkUnknown, "PNGImageIO")
  SimpleITK.WriteImage(image, outputImageFileName)
end

function example3()
  require "SimpleITK"

  basic_transform = SimpleITK.Euler2DTransform()
  trans = SimpleITK.VectorDouble()
  trans:push_back(2.0)
  trans:push_back(3.0)
  basic_transform:SetTranslation(trans)

  SimpleITK.WriteTransform(basic_transform, 'euler2D.tfm')
  read_result = SimpleITK.ReadTransform('euler2D.tfm')

  assert(read_result:GetName() ~= basic_transform:GetName(), "type error")
end

if #arg < 2 then
  print ( "Usage: SimpleIO <input> <output>" )
  os.exit ( 1 )
end

example1(arg[1], arg[2])
example2(arg[1], arg[2])
example3()
