"""
Visualizing 2D images
=====================

In this example, we will explore using matplotlib to display images in our
notebooks, and work towards developing a reusable function to display 2D,3D,
color for SimpleITK images.

"""

import matplotlib.pyplot as plt
import SimpleITK as sitk
from downloaddata import fetch_data as fdata

##############################################################################
# Fetch and read image
img1 = sitk.ReadImage(fdata("cthead1.png"))
img2 = sitk.ReadImage(fdata("VM1111Shrink-RGB.png"))


##############################################################################
# SimpleITK has a built in `Show` method which saves the image to disk and
# launches a user configurable program ( defaults to ImageJ ), to display the
# image.
#
# .. code-block:: python
#
#     sitk.Show(img1, title="cthead1")
#     sitk.Show(img2, title="Visible Human Head")
#
# Plotting with ``matplotlib``
# ----------------------------
# You can also use matplotlib to show images.

nda = sitk.GetArrayFromImage(img1)
plt.imshow(nda)

##############################################################################

nda = sitk.GetArrayFromImage(img2)
plt.imshow(nda)

##############################################################################
# Let's write a function which directly takes Image object and shows it.


def myshow(img):
    nda = sitk.GetArrayFromImage(img)
    plt.imshow(nda)
    plt.show()

myshow(sitk.Expand(img2, [10] * 5))


##############################################################################
# This image does not appear bigger.
#
# There are numerous improvements that we can make:
#
#  - support 3d images
#  - include a title
#  - use physical pixel size for axis labels
#  - show the image as gray values


def myshow(img, title=None, margin=0.05, dpi=80):
    nda = sitk.GetArrayFromImage(img)
    spacing = img.GetSpacing()

    if nda.ndim == 3:
        # fastest dim, either component or x
        c = nda.shape[-1]

        # the the number of components is 3 or 4 consider it an RGB image
        if c not in (3, 4):
            nda = nda[nda.shape[0] // 2, :, :]

    elif nda.ndim == 4:
        c = nda.shape[-1]

        if c not in (3, 4):
            raise RuntimeError("Unable to show 3D-vector Image")

        # take a z-slice
        nda = nda[nda.shape[0] // 2, :, :, :]

    xsize = nda.shape[1]
    ysize = nda.shape[0]

    # Make a figure big enough to accommodate an axis of xpixels by ypixels
    # as well as the ticklabels, etc...
    figsize = (1 + margin) * xsize / dpi, (1 + margin) * ysize / dpi

    plt.figure(figsize=figsize, dpi=dpi, tight_layout=True)
    ax = plt.gca()

    extent = (0, xsize * spacing[0], ysize * spacing[1], 0)

    t = ax.imshow(nda, extent=extent, interpolation=None)

    if nda.ndim == 2:
        t.set_cmap("gray")

    if(title):
        plt.title(title)

    plt.show()

myshow(sitk.Expand(img2, [2, 2]), title="Big Visibile Human Head")

##############################################################################
# The ``myshow`` function is really useful. We will build up on it for 3d
# images( ``myshow3d`` ) in the next guide.
# They have been copied into a "myshow.py" file so that they can be
# imported into other guides.
