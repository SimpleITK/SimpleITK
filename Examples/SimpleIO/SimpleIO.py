#!/usr/bin/env python
# =========================================================================
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
# =========================================================================

# These examples are used in the I/O documentation page. The IO.rst file
# pulls the code examples based their line numbers in this file. So any
# change in the line numbers of the code below will break the I/O page.

# A simple image input/output example
#
def example1(inputImageFileName, outputImageFileName):

  import SimpleITK as sitk

  reader = sitk.ImageFileReader()
  reader.SetImageIO("PNGImageIO")
  reader.SetFileName(inputImageFileName)
  image = reader.Execute();

  writer = sitk.ImageFileWriter()
  writer.SetFileName(outputImageFileName)
  writer.Execute(image)


# A simple procedural image input/output example
#
def example2(inputImageFileName, outputImageFileName):

  import SimpleITK as sitk

  image = sitk.ReadImage(inputImageFileName, imageIO="PNGImageIO")
  sitk.WriteImage(image, outputImageFileName)


# A simple transform input/output example
#
def example3():

  import SimpleITK as sitk

  basic_transform = sitk.Euler2DTransform()
  basic_transform.SetTranslation((2,3))

  sitk.WriteTransform(basic_transform, 'euler2D.tfm')
  read_result = sitk.ReadTransform('euler2D.tfm')

  assert(str(type(read_result) != type(basic_transform)))


import sys

if __name__ == "__main__":

    if len(sys.argv) < 3:
        print("Usage: SimpleIO <input> <output>")
        sys.exit(1)

    example1(sys.argv[1], sys.argv[2])
    example2(sys.argv[1], sys.argv[2])
    example3()
    sys.exit(0)
