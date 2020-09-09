.. _lbl_migration_guide2.0:

Migration Guide 2.0
-------------------

With the release of SimpleITK 2.0 there are changes to the interface and to the behaviour of some methods and classes. The intent of this document is to provide guidance on how to modify code so that it is compatible with SimpleITK 2.0.

DICOM reading
+++++++++++++

Changes to DICOM reading, due to SimpleITK's move from ITK 4.x to 5.x. Photomertic interpretation, tag 0028|0004, is now taken into account when reading the image.

   1. MOCHOROME1: previously intensity values loaded as is, now they are inverted. Code that previously inverted the intensities explicitly needs to be removed.
   2. Color images (e.g. YBR_FULL_422): Previously channels loaded as is, now they are converted to RGB. If previous code used the photometric interpretation tag value to perform color space conversions outside of SimpleITK it will need to be  modified. For example, previously the first channel for an image with photometric interpretation of YBR_FULL was luminance and could be used as the grayscale version of the image. Now all three channels are used to compute the image luminance:

+----------------------------------------------------------+-----------------------------------------------------------------------------------------------------------------------------------+
| 1.x                                                      | 2.x                                                                                                                               |
+----------------------------------------------------------+-----------------------------------------------------------------------------------------------------------------------------------+
| .. code-block:: python                                   | .. code-block:: python                                                                                                            |
|                                                          |                                                                                                                                   |
|                                                          |  image = sitk.ReadImage(file_name)                                                                                                |
|                                                          |  grayscale_image = sitk.Cast(sitk.RescaleIntensity(0.299*sitk.VectorIndexSelectionCast(image,0,sitk.sitkFloat32) +                |
|  image = sitk.ReadImage(file_name)                       |                                                    0.587*sitk.VectorIndexSelectionCast(image,1,sitk.sitkFloat32) +                |
|  grayscale_image = sitk.VectorIndexSelectionCast(image,0)|                                                    0.114*sitk.VectorIndexSelectionCast(image,0,sitk.sitkFloat32)), sitk.sitkUInt8)|
+----------------------------------------------------------+-----------------------------------------------------------------------------------------------------------------------------------+


Binary Morphology
+++++++++++++++++

The procedural interfaces for BinaryErode, BinaryDilate and BinaryClosingByReconstruction previously expected a scalar value and now expect a vector structuring element with the same length as image dimension. This enables more flexible structuring elements. For example, previously a structuring element of size 5 used on a 3D image will now be specified as [5, 5, 5]:

+----------------------------------------------------------+-------------------------------------------------------+
| 1.x                                                      | 2.x                                                   |
+----------------------------------------------------------+-------------------------------------------------------+
| .. code-block:: python                                   | .. code-block:: python                                |
|                                                          |                                                       |
|  seg = sitk.BinaryDilate(seg, 5)                         |  seg = sitk.BinaryDilate(seg, [5]*seg.GetDimension()) |
+----------------------------------------------------------+-------------------------------------------------------+

Transformations
+++++++++++++++

Composite transformations were previously represented using the generic `Transform class  <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1Transform.html>`__. This class served both as a base class for all transformations and as a composite transformation. This dual purpose
has been separated. Composite transformations are now represented by a dedicated class `CompositeTransform <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1CompositeTransform.html>`__ and the associated functionality has been removed from the Transform.

+----------------------------------------------------------+-------------------------------------------------------------------------------------------------+
| 1.x                                                      | 2.x                                                                                             |
+----------------------------------------------------------+-------------------------------------------------------------------------------------------------+
| .. code-block:: python                                   | .. code-block:: python                                                                          |
|                                                          |                                                                                                 |
|  tx = sitk.Transform()                                   |  tx = sitk.CompositeTransform([sitk.TranslationTransform(3,(1,7,76)), sitk.Euler3DTransform()]) |
|  tx.AddTransform(sitk.TranslationTransform(3,(1,7,76)))  |                                                                                                 |
|  tx.AddTransform(sitk.Euler3DTransform())                |                                                                                                 |
+----------------------------------------------------------+-------------------------------------------------------------------------------------------------+

Images
++++++

Images previously did not support sub-image left assignment, they now do:

.. code-block:: python

 img[0:10,5:15] = 128

Image Filters
+++++++++++++

Previously, the Execute method for some filters received filter parameter arguments. Now these methods have been removed, and filter parameters are only set via the SetXYZ methods. For example the `ResampleImageFilter class <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ResampleImageFilter.html>`__:

+----------------------------------------------------------------+----------------------------------------------------------+
| 1.x                                                            | 2.x                                                      |
+----------------------------------------------------------------+----------------------------------------------------------+
| .. code-block:: python                                         | .. code-block:: python                                   |
|                                                                |                                                          |
|                                                                |  resample_filter = sitk.ResampleImageFilter()            |
|  resample_filter = sitk.ResampleImageFilter()                  |  resample_filter.SetOutputOrigin(new_origin)             |
|  resample_filter.Execute(image, new_size, tx, sitk.sitkLinear, |  resample_filter.SetSize(new_size)                       |
|                          new_origin, new_spacing,              |  resample_filter.SetSpacing(new_spacing)                 |
|                          [1,0,0,0,1,0,0,0,1], -1000)           |  resample_filter.SetTransform(tx)                        |
|                                                                |  resample_filter.SetInterpolator(sitk.sitkLinear)        |
|                                                                |  resample_filter.SetOutputDirection([1,0,0,0,1,0,0,0,1]) |
|                                                                |  resample_filter.SetDefaultPixelValue(-1000)             |
|                                                                |  resampled_image = resample_filter.Execute(image)        |
+----------------------------------------------------------------+----------------------------------------------------------+
