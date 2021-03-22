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

proc example1 {inputImageFileName outputImageFileName} {
  ImageFileReader reader
  reader SetImageIO "PNGImageIO"
  reader SetFileName $inputImageFileName
  set image [ reader Execute ]

  ImageFileWriter writer
  writer SetFileName $outputImageFileName
  writer Execute $image

  reader -delete
  writer -delete
  $image -delete
}

proc example2 {inputImageFileName outputImageFileName} {
  global sitkUnknown
  set image [ ReadImage $inputImageFileName $sitkUnknown "PNGImageIO" ]
  WriteImage $image $outputImageFileName

  $image -delete
}

proc example3 {} {
  Euler2DTransform basic_transform
  set trans { 2.0 3.0 }
  basic_transform SetTranslation $trans

  WriteTransform basic_transform "euler2D.tfm"
  set read_result [ ReadTransform "euler2D.tfm" ]

  if { [basic_transform GetName] == [$read_result GetName] } {
    error "This should not happen" 1
  }

  basic_transform -delete
  $read_result -delete
}

if { $argc < 2 } {
    puts "Usage: SimpleIO <input> <output>"
    exit 1
}

example1 [ lindex $argv 0] [ lindex $argv 1]
example2 [ lindex $argv 0] [ lindex $argv 1]
example3
