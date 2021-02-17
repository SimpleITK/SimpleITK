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

if { $argc < 1 } {
    puts "Usage: ImageIOSelection image_input_file"
    exit 1
}

# Find out which image IOs are supported
ImageFileReader reader
set image_ios [ reader GetRegisteredImageIOs]
puts "The supported image IOs are: $image_ios"
puts "--------------------"

# Another option is to just print the reader and see which
# IOs are supported
puts [reader ToString]
puts "--------------------"

reader SetFileName [ lindex $argv 0 ]
reader SetImageIO "PNGImageIO"
if {[catch {set image [ reader Execute ]} errmsg]} {
  puts "Read failed: $errmsg"
}

# Tcl requires explicit cleanup Cleanup
reader -delete
if {[info exists image]} {
  $image -delete
}
