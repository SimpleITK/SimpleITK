import sys

import SimpleITK as sitk
import numpy as np

# This tests numpy array <-> SimpleITK Image conversion.

def die(message):
    print(message)
    sys.exit(1)

sizeX = 4
sizeY = 5
sizeZ = 3

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

print(sitk.GetArrayFromImage(image))

# 3D image
image = sitk.Image(sizeX, sizeY, sizeZ, sitk.sitkFloat32)
for k in range(sizeZ):
    for j in range(sizeY):
        for i in range(sizeX):
            image[i, j, k] = (sizeY*k +j)*sizeX + i

print(sitk.GetArrayFromImage(image))


#------------------------------------
# Test numpy array to SimpleITK Image

arr = np.arange(20)
arr.shape = (sizeX, sizeY)
image = sitk.GetImageFromArray(arr)
print(image)
print('image[0,0]: ' + str(image[0,0]))
print('image[1,1]: ' + str(image[1,1]))
print('image[2,2]: ' + str(image[2,2]))


