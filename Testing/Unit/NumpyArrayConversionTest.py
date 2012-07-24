#==========================================================================
#
#   Copyright Insight Software Consortium
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#          http://www.apache.org/licenses/LICENSE-2.0.txt
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#
#==========================================================================*/

import sys
import unittest


import SimpleITK as sitk
import numpy as np

def die(message):
    print(message)
    sys.exit(1)

sizeX = 4
sizeY = 5
sizeZ = 3


class TestNumpySimpleITKInterface(unittest.TestCase):
    """ This tests numpy array <-> SimpleITK Image conversion. """


    def setUp(self):
        pass

    def test_legacy(self):
      #------------------------------------
      # Test SimpleITK Image to numpy array.

      # Test passing in the wrong type
      detectedWrongType = False
      try:
          sitk.GetArrayFromImage( 3 )
      except TypeError:
          detectedWrongType = True
      if not detectedWrongType:
          die("Did not correctly detect the TypeError in argument passing to GetArrayFromImage.")

      # 2D image
      image = sitk.Image(sizeX, sizeY, sitk.sitkInt32)
      for j in range(sizeY):
          for i in range(sizeX):
              image[i, j] = j*sizeX + i
      print('array from sitk.Image(' + str(sizeX) +', ' + str(sizeY) + ', sitk.sitkInt32):')
      print(sitk.GetArrayFromImage(image))
      if not type (sitk.GetArrayFromImage(image)) == np.ndarray:
          die( "GetArrayFromImage did not return numpy array" )
      print('')

      # 3D image
      image = sitk.Image(sizeX, sizeY, sizeZ, sitk.sitkFloat32)
      for k in range(sizeZ):
          for j in range(sizeY):
              for i in range(sizeX):
                  image[i, j, k] = (sizeY*k +j)*sizeX + i

      print('array from sitk.Image(' + str(sizeX) +', ' + str(sizeY) + ', ' + \
                 str(sizeZ) + ', sitk.sitkFloat32):')
      print(sitk.GetArrayFromImage(image))

      if not type (sitk.GetArrayFromImage(image) )== np.ndarray:
          die( "GetArrayFromImage did not return numpy array" )
          print('')


      #------------------------------------
      # Test numpy array to SimpleITK Image

      arr = np.arange(20, dtype=np.float64)
      arr.shape = (sizeY, sizeX)
      print('image from np.arange(20, dtype=np.float64); arr.shape= (' \
                + str(sizeY) + ', ' + str(sizeX) + '):')
      image = sitk.GetImageFromArray(arr)
      print(image)
      print('image[0,0]: ' + str(image[0,0]))
      if image[0,0] != 0.0:
          die('Expected 0.0')
      print('image[1,1]: ' + str(image[1,1]))
      if image[1,1] != 5.0:
          die('Expected 5.0')
      print('image[2,2]: ' + str(image[2,2]))
      if image[2,2] != 10.0:
          die('Expected 10.0')
      print('')


      arr = np.arange(60, dtype=np.int16)
      arr.shape = (sizeZ, sizeY, sizeX)
      print('image from np.arange(20, dtype=np.int16); arr.shape= (' \
                + str(sizeZ) + ', ' + str(sizeY) + ', ' + str(sizeX) + '):')
      image = sitk.GetImageFromArray(arr)
      print(image)
      print('image[0,0,0]: ' + str(image[0,0,0]))
      if image[0,0,0] != 0:
          die('Expected 0')
          print('image[1,1,1]: ' + str(image[1,1,1]))
      if image[1,1,1] != 25:
          die('Expected 25')
      print('image[2,2,2]: ' + str(image[2,2,2]))
      if image[2,2,2] != 50:
          die('Expected 50')
      print('')


if __name__ == '__main__':
    unittest.main()
