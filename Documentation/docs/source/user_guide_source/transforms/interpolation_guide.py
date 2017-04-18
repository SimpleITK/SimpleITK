"""
Image Interpolation
===================

We demonstrate the different interpolators available in SimpleITK available for
image resampling.  Their effect is demonstrated on the
`Marschner-Lobb <http://www.cs.cornell.edu/~srm/publications/Vis94-filters-abstract.html>`_ 
image.
"""

import SimpleITK as sitk
import math
from myshow import myshow

##############################################################################
# Marschner-Lobb image
# --------------------
#
# Add formula for it here.


def marschner_lobb(size=40, alpha=0.25, f_M=6.0):
    img = sitk.PhysicalPointSource(sitk.sitkVectorFloat32, [size] * 3,
                                   [-1] * 3, [2.0 / size] * 3)
    imgx = sitk.VectorIndexSelectionCast(img, 0)
    imgy = sitk.VectorIndexSelectionCast(img, 1)
    imgz = sitk.VectorIndexSelectionCast(img, 2)
    r = sitk.Sqrt(imgx**2 + imgy**2)
    pr = sitk.Cos((2.0 * math.pi * f_M) * sitk.Cos((math.pi / 2.0) * r))
    return (1.0 - sitk.Sin((math.pi / 2.0) * imgz) + alpha * (1.0 + pr)) / \
        (2.0 * (1.0 + alpha))

myshow(marschner_lobb(200), title='Marschner-Lobb Image')

##############################################################################
# Interpolations
# --------------
# Let's use ``Expand`` to rescale image by a factor of 5 in all dimensions.
#
# Compare these interpolations with the image above. 

ml = marschner_lobb(40)
ml = ml[:, :, ml.GetSize()[-1] // 2]

myshow(sitk.Expand(ml, [5] * 3, sitk.sitkNearestNeighbor),
       title="nearest neighbor")
myshow(sitk.Expand(ml, [5] * 3, sitk.sitkLinear),
       title="linear")
myshow(sitk.Expand(ml, [5] * 3, sitk.sitkBSpline),
       title="b-spline")
myshow(sitk.Expand(ml, [5] * 3, sitk.sitkGaussian),
       title="Gaussian")
myshow(sitk.Expand(ml, [5] * 3, sitk.sitkHammingWindowedSinc),
       title="Hamming windowed sinc")
myshow(sitk.Expand(ml, [5] * 3, sitk.sitkBlackmanWindowedSinc),
       title="Blackman windowed sinc")
myshow(sitk.Expand(ml, [5] * 3, sitk.sitkCosineWindowedSinc),
       title="Cosine windowed sinc")
myshow(sitk.Expand(ml, [5] * 3, sitk.sitkWelchWindowedSinc),
       title="Welch windowed sinc")
myshow(sitk.Expand(ml, [5] * 3, sitk.sitkLanczosWindowedSinc),
       title="Lanczos windowed sinc")
