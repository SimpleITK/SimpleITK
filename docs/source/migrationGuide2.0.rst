.. _lbl_migration_guide2.0:

Migration Guide 2.0
===================

With the release of SimpleITK 2.0 there are changes to the interface and to the behaviour of some methods and classes. The intent of this document is to provide guidance on how to modify code so that it is compatible with SimpleITK 2.0.

This document will continue to evolve after the SimpleITK 2.0 release, consider reading the `latest <https://simpleitk.readthedocs.io/en/master/migrationGuide2.0.html>`__ version. Contributions to update this document that share problems and solutions when updating to SimpleITK 2.0 are welcomed.


Interface Compatibility
-----------------------

These changes list API changes that cause compilation or runtime errors.


Composite Transforms
++++++++++++++++++++

The `Transform::AddTransform` method was removed.

Composite transformations were previously represented using the generic `Transform class <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1Transform.html>`__. This class served both as a base class for all transformations and as a composite transformation. This dual purpose
has been separated. Composite transformations are now represented by a dedicated class `CompositeTransform <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1CompositeTransform.html>`__ and the associated functionality was removed from the `Transform` class.

+---------------------------------------------------+------------------------------------------------+
| 1.x                                               | 2.x                                            |
+---------------------------------------------------+------------------------------------------------+
| .. code-block:: python                            | .. code-block:: python                         |
|                                                   |                                                |
|  tx = sitk.Transform()                            |  tx1 = sitk.TranslationTransform(3,(1,7,76))   |
|  tx1 = sitk.TranslationTransform(3,(1,7,76))      |  tx2 = sitk.Euler3DTransform()                 |
|  tx2 = sitk.Euler3DTransform()                    |  tx = sitk.CompositeTransform([tx1, tx2])      |
|  tx.AddTransform(tx1)                             |                                                |
|  tx.AddTransform(tx2)                             |                                                |
+---------------------------------------------------+------------------------------------------------+

This change does effect compatibility when reading or writing `CompositeTransforms` between versions.


Filter's Execute Method
+++++++++++++++++++++++

The Filters' `Execute` methods with filter parameters as arguments was removed. A filter object's parameters are only set via the SetXYZ methods. For example the `STAPLEImageFilter class <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1STAPLEImageFilter.html>`__:

+-----------------------------------------------------------+----------------------------------------------------------------+
| 1.x                                                       | 2.x                                                            |
+-----------------------------------------------------------+----------------------------------------------------------------+
| .. code-block:: python                                    | .. code-block:: python                                         |
|                                                           |                                                                |
|  staple_filter = sitk.STAPLEImageFilter()                 |  staple_filter = sitk.STAPLEImageFilter()                      |
|                                                           |  staple_filter.ConfidenceWeight(confidenceWeight)              |
|  staple_image = staple_filter.Execute(image1,             |  staple_filter.SetForegroundValue(foregroundValue)             |
|                                       image2, image3,     |  staple_filter.SetMaximumIterations(maximumIterations)         |
|                                       confidenceWeight,   |  staple_image = staple_filter.Execute([image1, image2, image3])|
|                                       foregroundValue,    |                                                                |
|                                       maximumIterations)  |  staple_specificity = staple_filter.GetSpecificity()           |
|  staple_specificity = staple_filter.GetSpecificity()      |                                                                |
|                                                           |                                                                |
+-----------------------------------------------------------+----------------------------------------------------------------+

Alternatively, the procedural method could be used if no measurements or side effects on the object are needed.

Morphology Radius
+++++++++++++++++

The procedural interfaces for morphology filters only accept vector values for the radius parameter. Previously the procedures accepted a scalar for the radius parameter. For example, a structuring element of radius 5 used on a 3D image is specified as [5, 5, 5]:

+----------------------------------------------------------+-------------------------------------------------------+
| 1.x                                                      | 2.x                                                   |
+----------------------------------------------------------+-------------------------------------------------------+
| .. code-block:: python                                   | .. code-block:: python                                |
|                                                          |                                                       |
|  seg = sitk.BinaryDilate(seg, 5)                         |  seg = sitk.BinaryDilate(seg, [5]*seg.GetDimension()) |
+----------------------------------------------------------+-------------------------------------------------------+

The following is a list of procedures affected by this change:

* `BinaryClosingByReconstruction`
* `BinaryDilate`
* `BinaryErode`
* `BinaryMorphologicalClosing`
* `BinaryMorphologicalOpening`
* `BinaryOpeningByReconstruction`
* `BlackTopHat`
* `ClosingByReconstruction`
* `DilateObjectMorphology`
* `ErodeObjectMorphology`
* `GrayscaleDilate`
* `GrayscaleErode`
* `GrayscaleMorphologicalClosing`
* `GrayscaleMorphologicalOpening`
* `MorphologicalGradient`
* `OpeningByReconstruction`
* `WhiteTopHat`


FastMarchingImageFilter
+++++++++++++++++++++++

The `FastMarchingImageFilter::AddTrialPoints` and `FastMarchingImageFilter::ClearTrialPoints` methods were removed. The `SetTrialPoints` method can be used instead to set the whole list of trial points.


Behavior Changes
----------------

ITKv5
+++++

SimpelITK 2.0 uses ITK version 5.0. This major version change to ITK includes numerous changes to the usage and behavior of ITK. The `ITK v5 Migration Guide <https://github.com/InsightSoftwareConsortium/ITK/blob/master/Documentation/ITK5MigrationGuide.md>`_ contains valuable information documenting changes.


Show Environment Variables
++++++++++++++++++++++++++

The environment variables related to the `Show` method are only checked once. The `Show` method is a wrapper for the `ImageViewer <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ImageViewer.html>`__ class, changing the behavior from SimpleITK 1.0. The SITK_SHOW_EXTENSION and SITK_SHOW_COMMAND environment variables if defined initialize the corresponding global defaults only the first time accessed. The environment variables SITK_COLOR_COMMAND and SITK_SHOW_3D_COMMAND were removed as the ImageViewer class allows for direct configuration of the command.


Images
++++++

Images support sub-image left assignment of constants and matching image regions.

.. code-block:: python

 img[0:10,5:15] = 128
 img[5:10,10:15] = img2[0:5,5:10]


DICOM MOCHOROME1
++++++++++++++++

Changes to DICOM reading, due to SimpleITK's move from ITK 4.x to 5.x. Photomertic interpretation, tag 0028|0004, is now taken into account when reading the image.

   1. MOCHOROME1: previously intensity values loaded as is, now they are inverted. Code that previously inverted the intensities explicitly needs to be removed.
   2. Color images (e.g. YBR_FULL_422): Previously channels loaded as is, now they are converted to RGB. If previous code used the photometric interpretation tag value to perform color space conversions outside of SimpleITK it will need to be  modified. For example, previously the first channel for an image with photometric interpretation of YBR_FULL was luminance and could be used as the grayscale version of the image. Now all three channels are used to compute the image luminance:

+----------------------------------------------------------+------------------------------------------------------------------------------------+
| 1.x                                                      | 2.x                                                                                |
+----------------------------------------------------------+------------------------------------------------------------------------------------+
| .. code-block:: python                                   | .. code-block:: python                                                             |
|                                                          |                                                                                    |
|                                                          |  image = sitk.ReadImage(file_name)                                                 |
|                                                          |  grayscale_image = 0.299*sitk.VectorIndexSelectionCast(image,0,sitk.sitkFloat32) + |
|  image = sitk.ReadImage(file_name)                       |                    0.587*sitk.VectorIndexSelectionCast(image,1,sitk.sitkFloat32) + |
|  grayscale_image = sitk.VectorIndexSelectionCast(image,0)|                    0.114*sitk.VectorIndexSelectionCast(image,2,sitk.sitkFloat32)   |
|                                                          |  grayscale_image = sitk.Cast(sitk.RescaleIntensity(grayscale_image))               |
+----------------------------------------------------------+------------------------------------------------------------------------------------+



Python Installation
+++++++++++++++++++

The Python installation procedure to use `setup.py` changed. To install see the updated `Python Installation <python_installation>`_ documentation.

Multi-threading
+++++++++++++++

The upgrade to ITKv5 contains a major refactoring of ITK's threading model. Details on the behavior of the new default PoolMultiThreader can be found in the `ITK v5 Multi-Threading Section <https://github.com/InsightSoftwareConsortium/ITK/blob/master/Documentation/ITK5MigrationGuide.md#multithreading-refactored>`_.

The SimpelITK `ProcessObject class <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ProcessObject.html>`_ contains the methods to configure the ITK Threader used and the number of threads and number of work units used for an algorithm.


Registration Smoothing
++++++++++++++++++++++

Results from the registration framework may change due to the the Gaussian smoothing algorithm changing from the `DiscreteGaussianImageFilter` to the `SmoothingRecursiveGaussianImageFilter`.
