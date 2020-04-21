N4 Bias Field Correction
========================


Overview
--------

The N4 bias field correction algorithm is a popular method for
correcting low frequency intensity non-uniformity present in MRI image
data known as a bias or gain field. The method has also been
successfully applied as flat-field correction in microscopy data. This
method assumes a simple parametric model and does not require tissue
classification.

This example demonstrates how to use the SimpleITK
`N4BiasFieldCorrectionImageFilter
<https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1N4BiasFieldCorrectionImageFilter.html>`_
class. This filter has one required input image which is affected by a
bias field we wish to correct. The primary input is required to have a
"real" pixel type of either `sitkFloat32` or
`sitkFloat64`. Additionally, there is an  optional "MaskImage" input
which specifies which pixels are used to estimate the bias-field and
suppress pixels close to zero. It is recommended that the mask image
follows the common conventions for :ref:`masked images
<lbl_conventions_mask_image>`, which is being of pixel type
`sitkUint8` and having values of 0 and 1 representing the
mask. Additionally, the mask image and the main input image must
occupy the same physical space to ensure pixel to pixel
correspondence.

Some basic parameters for using this algorithm are parsed from the
command line in this example. The shrink factor is used to reduce the
size and complexity of the image. The N4 algorithm uses a multi-scale
optimization approach to compute the bias field. The
**SetMaximumNumberOfIterations** method takes an array used to set
the limit of iterations per resolution level, thereby setting both the
iterations and the number of scales ( from the length of the array
). The output of the filter is the bias corrected input image.

Code
----

.. tabs::

  .. tab:: Python

    .. literalinclude:: ../../Examples/N4BiasFieldCorrection/N4BiasFieldCorrection.py
       :language: python
       :lines: 1,19-

  .. tab:: R

    .. literalinclude:: ../../Examples/N4BiasFieldCorrection/N4BiasFieldCorrection.R
       :language: R
       :lines: 18-
