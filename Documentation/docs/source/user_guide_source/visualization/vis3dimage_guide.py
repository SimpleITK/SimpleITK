"""
Visualizing 3D images
======================

In previous guide, we've seen how to visualize 2d images. We've written a
function ``myshow`` which we will be using in this guide.

Now lets move on to visualizing real MRI images. The Surgical Planning
Laboratory at Brigham and Women's Hospital has a wonderful
`Multi-modality MRI-based Atlas of the Brain <http://www.spl.harvard.edu/publications/item/view/2037>`_ that we can use.

Please note, what is done here is for convenience and is not the common way
images are displayed for radiological work.

Get Images
----------
"""
import matplotlib.pyplot as plt
import SimpleITK as sitk
from downloaddata import fetch_data as fdata
from myshow import myshow

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
# Visualize another axis.

size = img_T1.GetSize()
myshow(img_T1[:, size[1] // 2, :])

##############################################################################
# Let's visualize all three orthogonal views. You can use ``sitk.Tile`` for
# tiling images.

slices = [img_T1[size[0] // 2, :, :], img_T1[:, size[1] // 2, :],
          img_T1[:, :, size[2] // 2]]
myshow(sitk.Tile(slices, [3, 1]), dpi=20)

##############################################################################
# Visualize 5 slices in one axis.

nslices = 5
slices = [img_T1[:, :, s] for s in range(0, size[2], size[0] // (nslices + 1))]
myshow(sitk.Tile(slices, [1, 0]), dpi=100)

##############################################################################
# Let's create a version of the show methods which allows the selection of
# slices to be displayed.


def myshow3d(img, xslices=[], yslices=[], zslices=[], title=None, margin=0.05,
             dpi=80):
    img_xslices = [img[s, :, :] for s in xslices]
    img_yslices = [img[:, s, :] for s in yslices]
    img_zslices = [img[:, :, s] for s in zslices]

    maxlen = max(len(img_xslices), len(img_yslices), len(img_zslices))

    img_null = sitk.Image([0, 0], img.GetPixelID(),
                          img.GetNumberOfComponentsPerPixel())

    img_slices = []
    d = 0

    if len(img_xslices):
        img_slices += img_xslices + [img_null] * (maxlen - len(img_xslices))
        d += 1

    if len(img_yslices):
        img_slices += img_yslices + [img_null] * (maxlen - len(img_yslices))
        d += 1

    if len(img_zslices):
        img_slices += img_zslices + [img_null] * (maxlen - len(img_zslices))
        d += 1

    if maxlen != 0:
        if img.GetNumberOfComponentsPerPixel() == 1:
            img = sitk.Tile(img_slices, [maxlen, d])
        # TO DO check in code to get Tile Filter working with vector images
        else:
            img_comps = []
            for i in range(0, img.GetNumberOfComponentsPerPixel()):
                img_slices_c = [sitk.VectorIndexSelectionCast(s, i)
                                for s in img_slices]
                img_comps.append(sitk.Tile(img_slices_c, [maxlen, d]))
            img = sitk.Compose(img_comps)

    myshow(img, title, margin, dpi)

myshow3d(img_T1, yslices=range(50, size[1] - 50, 20),
         zslices=range(50, size[2] - 50, 20), dpi=100)

##############################################################################

myshow3d(img_T2, yslices=range(50, size[1] - 50, 30),
         zslices=range(50, size[2] - 50, 20), dpi=100)

##############################################################################

myshow3d(sitk.LabelToRGB(img_labels), yslices=range(50, size[1] - 50, 20),
         zslices=range(50, size[2] - 50, 20), dpi=100)
