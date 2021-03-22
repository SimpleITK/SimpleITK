#=========================================================================
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
#=========================================================================

# These examples are used in the I/O documentation page. The IO.rst file
# pulls the code examples based their line numbers in this file. So any
# change in the line numbers of the code below will break the I/O page.

def example1(inputImageFileName, outputImageFileName)
  require 'simpleitk'

  reader = Simpleitk::ImageFileReader.new
  reader.set_image_io("PNGImageIO")
  reader.set_file_name(inputImageFileName)
  image = reader.execute

  writer = Simpleitk::ImageFileWriter.new
  writer.set_file_name outputImageFileName
  writer.execute image
end

def example2(inputImageFileName, outputImageFileName)
  require 'simpleitk'

  image = Simpleitk::read_image(inputImageFileName, Simpleitk::SitkUnknown, "PNGImageIO")
  Simpleitk::write_image(image, outputImageFileName)
end

def example3()
  require 'simpleitk'

  basic_transform = Simpleitk::Euler2DTransform.new
  trans = Simpleitk::VectorDouble.new
  trans << 2.0
  trans << 3.0
  basic_transform.set_translation(trans)

  Simpleitk::write_transform(basic_transform, 'euler2D.tfm')
  read_result = Simpleitk::read_transform('euler2D.tfm')

  raise "This shouldn't happen." unless basic_transform.class != read_result.class
end

if ARGV.length != 2 then
  puts "Usage: SimpleIO <input> <output>";
  exit( 1 )
end

example1(ARGV[0], ARGV[1])
example2(ARGV[0], ARGV[1])
example3()
