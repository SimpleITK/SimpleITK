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
require 'simpleitk'

if ARGV.length != 1 then
  puts "Usage: SimpleGaussian image_input_file";
  exit( 1 )
end

# Find out which image IOs are supported
reader = Simpleitk::ImageFileReader.new
reader.set_file_name( ARGV[0] )
image_ios = reader.get_registered_image_ios()

print "The supported image IOs are: "
for i in image_ios do
  print i, " "
end
puts "\n--------------------"

# Another option is to just print the reader and see which
# IOs are supported
puts reader.to_string()
puts "\n--------------------"

# Force the use of a specific IO. If the IO doesn't support
# reading the image type it will throw an exception.
reader.set_image_io("PNGImageIO")

begin
  image = reader.execute
  puts "Read image: " + ARGV[0]
rescue StandardError => e
  puts "Read failed: " + e.message
end
