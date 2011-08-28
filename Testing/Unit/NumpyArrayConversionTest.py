import sys

import SimpleITK as sitk
import numpy as np

# This tests numpy array <-> SimpleITK Image conversion.

def die(message):
    print(message)
    sys.exit(1)

sizeX = 4
sizeY = 5

#------------------------------------
# Test numpy array to SimpleITK Image

arr = np.arange(20)
arr.shape = (sizeX, sizeY)
print(sitk.GetImageFromArray(arr))


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

image = sitk.Image(sizeX, sizeY, sitk.sitkInt32)
for i in range(sizeX):
    for j in range(sizeY):
        image[i, j] = i*sizeY + j

print(sitk.GetArrayFromImage(image))
