import SimpleITK as sitk
import numpy as np

arr = np.arange(20)
arr.shape = (4,5)
print( sitk.GetImageFromArray(arr) )
