"""
Thresholding
============

Thresholding is the most basic form of segmentation. It simply labels the
pixels of an image based on the intensity range without respect to geometry
or connectivity.
"""
# License: CC-BY
# sphinx_gallery_thumbnail_number = 4

import SimpleITK as sitk
from myshow import myshow, myshow3d
from downloaddata import fetch_data as fdata

##############################################################################
# Load Image
# ----------

img_T1 = sitk.ReadImage(
    fdata("nac-hncma-atlas2013-Slicer4Version/Data/A1_grayT1.nrrd"))

# To visualize the labels image in RGB needs a image with 0-255 range
img_T1_255 = sitk.Cast(sitk.RescaleIntensity(img_T1), sitk.sitkUInt8)

size = img_T1.GetSize()
myshow3d(img_T1_255, zslices=range(50, size[2] - 50, 20))

##############################################################################
# Threshold
# ---------
# Let's pick a threshold 200 for thresholding.

seg = img_T1 > 200
myshow(sitk.LabelOverlay(img_T1_255, seg), "Basic Thresholding")

##############################################################################
# You can also use a upper and lower threshold. 

seg = sitk.BinaryThreshold(img_T1,
                           lowerThreshold=100, upperThreshold=400, 
                           insideValue=1, outsideValue=0)
myshow(sitk.LabelOverlay(img_T1_255, seg), "Binary Thresholding")

##############################################################################
# Otsu Thresholding
# -----------------
# 
# ITK has a number of histogram based automatic thresholding filters including 
# Huang, MaximumEntropy, Triangle, and the popular Otsu's method. These methods 
# create a histogram then use a heuristic to determine a threshold value.
# 
# Otsu Thresholding for example, assumes that the image contains two classes 
# of pixels following bi-modal histogram and calculates the optimum threshold 
# separating these two classes.

otsu_filter = sitk.OtsuThresholdImageFilter()
otsu_filter.SetInsideValue(0)
otsu_filter.SetOutsideValue(1)
seg = otsu_filter.Execute(img_T1)
myshow(sitk.LabelOverlay(img_T1_255, seg), "Otsu Thresholding")

print("Computed Threshold: {}".format(otsu_filter.GetThreshold()))
