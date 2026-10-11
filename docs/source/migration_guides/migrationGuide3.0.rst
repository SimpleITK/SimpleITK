.. _lbl_migration_guide3.0:

Migration Guide 3.0
===================

With the release of SimpleITK 3.0 there are changes to the interface and to the behaviour of some methods and classes. The intent of this document is to provide guidance on how to modify code so that it is compatible with SimpleITK 3.0.

This document will continue to evolve after the SimpleITK 3.0 release, consider reading the `latest <https://simpleitk.readthedocs.io/en/main/migrationGuide3.0.html>`__ version. Contributions to update this document that share problems and solutions when updating to SimpleITK 3.0 are welcomed.



Build System Requirements
-------------------------

The following minimum version requirements have changed:

* CMake minimum version: 3.16.3 → **3.23.0**
* Python minimum version: 3.9 → **3.10**
* SWIG minimum version: 4.3.0 (now explicitly required)


SimpleITK_USE_FILE Deprecated
+++++++++++++++++++++++++++++

``SimpleITK_USE_FILE`` and the ``UseSimpleITK.cmake`` file it points to are deprecated. This legacy mechanism only set up global include/link directories (``include_directories()``/``link_directories()``), which predates CMake's modern, target-based usage requirements. SimpleITK now exports proper imported CMake targets, so consumers should link against them directly instead.

The variable and file will continue to work, but including them now emits a CMake deprecation warning. And will be removed in a future release.

**2.x (deprecated, still works but warns in 3.x):**

.. code-block:: cmake

   find_package(SimpleITK REQUIRED)
   include(${SimpleITK_USE_FILE})

   add_executable(MyExample MyExample.cxx)
   target_link_libraries(MyExample ${SimpleITK_LIBRARIES})

**3.x (updated approach):**

.. code-block:: cmake

   find_package(SimpleITK REQUIRED)

   add_executable(MyExample MyExample.cxx)
   target_link_libraries(MyExample ${SimpleITK_LIBRARIES})

Simply drop the ``include(${SimpleITK_USE_FILE})`` line. ``SimpleITK_LIBRARIES`` already refers to SimpleITK's imported targets, which carry their own include directories and dependencies, so no separate include/link directory setup is needed.


Interface Compatibility
-----------------------

These changes list API changes that cause compilation or runtime errors.


LabelIntensityStatisticsImageFilter
++++++++++++++++++++++++++++++++++++

The `LabelIntensityStatisticsImageFilter` now only supports unsigned integer pixel types for label images.

Previously, this filter accepted both signed and unsigned integer pixel types for label images. To reduce compilation time and object file size, support for signed integer label images has been removed. This change reduces the compiled object file size from 27MB to 14MB on Mac ARM systems.

**Error Message:**
Code using signed integer label images will now produce a runtime error indicating the pixel type is not supported.

**Migration:**
Convert signed label images to unsigned types before using this filter.

**2.x (No longer works in 3.x):**

.. code-block:: python

   # This worked in 2.x but fails in 3.x
   label_image = sitk.ReadImage("labels.nii")
   # label_image has signed integer pixels
   intensity_image = sitk.ReadImage("intensity.nii")
   filter_result = sitk.LabelIntensityStatistics(
       label_image, intensity_image)

**3.x (Updated approach):**

.. code-block:: python

   # Convert signed labels to unsigned
   label_image = sitk.ReadImage("labels.nii")
   # Convert to unsigned if needed
   if label_image.GetPixelID() in [
       sitk.sitkInt8, sitk.sitkInt16,
       sitk.sitkInt32, sitk.sitkInt64]:
       label_image = sitk.Cast(label_image,
           sitk.sitkUInt32)
   intensity_image = sitk.ReadImage(
       "intensity.nii")
   filter_result = sitk.LabelIntensityStatistics(
       label_image, intensity_image)

**Supported Label Image Pixel Types:**

* sitkUInt8
* sitkUInt16
* sitkUInt32
* sitkUInt64

**Unsupported Label Image Pixel Types (will cause runtime error):**

* sitkInt8
* sitkInt16
* sitkInt32
* sitkInt64


_GetMemoryViewFromImage Removed
+++++++++++++++++++++++++++++++

The private ``_GetMemoryViewFromImage`` function has been removed from the Python wrapping. The ``Image`` class now directly supports the Python buffer protocol (PEP 688) via ``__buffer__`` and the NumPy array interface via ``__array_interface__``.

**2.x (No longer works in 3.x):**

.. code-block:: python

   # Internal usage in 2.x
   mv = sitk._GetMemoryViewFromImage(image)

**3.x (Updated approach):**

.. code-block:: python

   import numpy as np

   # Use numpy's asarray for zero-copy read-only view
   arr = np.asarray(image)

   # Or use the buffer protocol directly
   mv = memoryview(image)


Behavioral Changes
------------------

SobelEdgeDetectionImageFilter
+++++++++++++++++++++++++++++

The default 3D Sobel operator coefficients have changed to be consistent with the 2D operator. This is a breaking change that may produce different results for 3D images compared to SimpleITK 2.x.

**Motivation for the Change:**

The new coefficients are:

* Generated using a consistent algorithm across all dimensions (2D, 3D, 4D, and arbitrary ND)
* More commonly used by other toolkits, including `SciPy's <https://docs.scipy.org/doc/scipy/reference/generated/scipy.ndimage.sobel.html>`__ ``scipy.ndimage.sobel``
* Consistent with the `Wikipedia definition of the Sobel operator <https://en.wikipedia.org/wiki/Sobel_operator>`__
* Verified against established implementations for accuracy across multiple dimensions

Note unlike SimpleITK's defaults, ITK 6.0 will default to the legacy coefficients unless compiled with ITK_FUTURE_LEGACY_REMOVE is defined, unlike SimpleITK 3.0 which defaults to the new coefficients.

**Background:**

The update was proposed in `ITK issue #5702 <https://github.com/InsightSoftwareConsortium/ITK/issues/5702>`__ and implemented in `ITK pull request #5718 <https://github.com/InsightSoftwareConsortium/ITK/pull/5718>`__ (merged Jan 20, 2026).

**Migration:**

If your code requires the exact behavior from SimpleITK 2.x for 3D images, use the legacy coefficients:

.. code-block:: python

   # To restore 2.x behavior for 3D images:
   f = sitk.SobelEdgeDetectionImageFilter()
   f.UseLegacyOperatorCoefficientsOn()
   result = f.Execute(image)
