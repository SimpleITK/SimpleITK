"""
Visualizing Segmentations
=========================

In previous guides, we've seen how to visualize 2d and 3d images. 
We've written functions ``myshow`` and ``myshow3d`` which we will be using in 
this guide.

We will also look at the subtleties of working with image filters that require
the input images' to be overlapping.

"""

import matplotlib.pyplot as plt
import SimpleITK as sitk
from downloaddata import fetch_data as fdata
from myshow import myshow, myshow3d

##############################################################################
# LabelOverlay In 2D
# ------------------
# We start by loading a segmented image. As the segmentation is just an image
# with integral data, we can display the labels as we would any other image.

img1 = sitk.ReadImage(fdata("cthead1.png"))
img1_seg = sitk.ReadImage(fdata("2th_cthead1.png"))

myshow(img1, title="cthead1")
myshow(img1_seg, title="Label Image as Grayscale")

##############################################################################
# We can also map the scalar label image to a color image as shown below.

myshow(sitk.LabelToRGB(img1_seg), title="Label Image as RGB")

##############################################################################
# Most filters which take multiple images as arguments require that the images
# occupy the same physical space. That is the pixel you are operating must
# refer to the same location. Luckily for us our image and labels do occupy the
# same physical space, allowing us to overlay the segmentation onto the
# original image.

myshow(sitk.LabelOverlay(img1, img1_seg), title="Label Overlayed")

##############################################################################
# We can also overlay the labels as contours.

myshow(sitk.LabelOverlay(img1, sitk.LabelContour(img1_seg), 1.0))

##############################################################################
# LabelOverlay In 3D
# ------------------
#
# The Surgical Planning Laboratory at Brigham and Women's Hospital has a wonderful
# `Multi-modality MRI-based Atlas of the Brain <http://www.spl.harvard.edu/publications/item/view/2037>`_ that we can use.

img_T1 = sitk.ReadImage(
    fdata("nac-hncma-atlas2013-Slicer4Version/Data/A1_grayT1.nrrd"))
img_T2 = sitk.ReadImage(
    fdata("nac-hncma-atlas2013-Slicer4Version/Data/A1_grayT2.nrrd"))
img_labels = sitk.ReadImage(
    fdata("nac-hncma-atlas2013-Slicer4Version/Data/hncma-atlas.nrrd"))

myshow(img_T1, title='T1')
myshow(img_T2, title='T2')
myshow(sitk.LabelToRGB(img_labels), title='lables')

##############################################################################
# Physical Space Issues
# ---------------------
# Why doesn't this work? The images do not overlap in physical space.
#
# All the functions in SimpleITK work on underlying physical space. Thefore,
# mismatch in physical space like image origin etc. will raise errors.
try:
    size = img_T1.GetSize()
    myshow3d(sitk.LabelOverlay(img_T1, img_labels),
             yslices=range(50, size[1] - 50, 20),
             zslices=range(50, size[2] - 50, 20), dpi=30)
except Exception as e:
    print(e)

##############################################################################
# Two ways to solve our problem:
#
# 1. resample the labels onto the image grid
# 2. resample the image onto the label grid.
#
# The difference between the two from a computation standpoint depends on the
# grid sizes and on the interpolator used to estimate values at non-grid
# locations.
#
# Note interpolating a label image with an interpolator that can generate
# non-label values is problematic as you may end up with an image that has more
# classes/labels than your original. This is why we only use the nearest
# neighbor interpolator when working with label images.
#
# **Option 1**: Resample the label image using the identity transformation
resampled_img_labels = sitk.Resample(img_labels, img_T1, sitk.Transform(),
                                     sitk.sitkNearestNeighbor, 0.0,
                                     img_labels.GetPixelID())
##############################################################################
# Overlay onto the T1 image, requires us to rescale the intensity of the T1
# image to [0,255] and cast it so that it can be combined with the color
# overlay (we use an alpha blending of 0.5).
rescaled_T1 = sitk.Cast(sitk.RescaleIntensity(img_T1), sitk.sitkUInt8)
myshow3d(sitk.LabelOverlay(rescaled_T1, resampled_img_labels, 0.5),
         yslices=range(50, size[1] - 50, 20),
         zslices=range(50, size[2] - 50, 20),
         dpi=100)

##############################################################################
# **Option 2**: Resample the T1 image using the identity transformation.
resampled_T1 = sitk.Resample(img_T1, img_labels, sitk.Transform(),
                             sitk.sitkLinear, 0.0, img_T1.GetPixelID())

##############################################################################
# As above, we need to use rescale the intensity of resampled T1
rescaled_T1 = sitk.Cast(sitk.RescaleIntensity(resampled_T1), sitk.sitkUInt8)
myshow3d(sitk.LabelOverlay(rescaled_T1, img_labels, 0.5),
         yslices=range(50, size[1] - 50, 20),
         zslices=range(50, size[2] - 50, 20),
         dpi=100)

##############################################################################
# Why are the two displays above different?
# (hint: in the calls to the "myshow3d" function the indexes of the y and z
# slices are the same).
#

