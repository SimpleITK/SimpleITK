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


Scalar Constants in Binary Operations Use Double Precision
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Binary filters that take an image and a scalar constant (e.g. ``Multiply(image, 0.5)``) previously cast the constant to the pixel type of the image before the operation ran. For integer images, a fractional or out-of-range constant was silently truncated, so ``Multiply(uint8_image, 0.5)`` was computed as ``Multiply(uint8_image, 0)``.

In SimpleITK 3.0 the constant is kept as a ``double`` and the operation is computed at ``double`` precision. Only the final result is cast to the output pixel type. Constants are only promoted for integer pixel types (and integer vector/complex components). Images with floating point pixels, such as ``float``, are computed as before.

**Affected filters:**

The following filters, and only these, now use a ``double`` constant in the image/constant overloads:

* ``MultiplyImageFilter`` (``Multiply``)
* ``DivideImageFilter`` (``Divide``)
* ``DivideRealImageFilter`` (``DivideReal``)
* ``DivideFloorImageFilter`` (``DivideFloor``)
* ``PowImageFilter`` (``Pow``)

Other binary filters with a constant overload, such as ``Add``, ``Subtract``, ``Modulus``, ``Equal``, ``NotEqual``, ``Greater``, ``GreaterEqual``, ``Less`` and ``LessEqual``, are unchanged and still cast the constant to the image's pixel type.

**Implication for Overloaded Operators:**

The overloaded operators call these filters, so their behavior changes when one operand is a scalar and the image has an integer pixel type:

.. list-table::
   :header-rows: 1
   :widths: 30 35 35

   * - Operator
     - Filter
     - Languages
   * - ``*``, ``*=``
     - ``Multiply``
     - C++, Python, C#, R
   * - ``/``
     - ``Divide``
     - C++, C#, R
   * - ``/``, ``/=``
     - ``DivideReal`` (Python true division)
     - Python
   * - ``//``, ``//=``
     - ``DivideFloor`` (Python floor division)
     - Python
   * - ``**``, ``**=``
     - ``Pow``
     - Python, R

This includes the reflected forms where the scalar is on the left, e.g. ``0.5 * image`` and ``2 ** image``. Operators for the filters that were not changed (``+``, ``-``, ``%``, ``==``, ``!=``, ``<``, ``<=``, ``>`` and ``>=``) are unaffected.

The results change in these cases for integer pixel types:

* ``image * 0.5`` was previously ``image * 0`` (all zeros). The product is now computed at ``double`` precision.
* ``image / 0.5`` previously truncated the divisor to ``0``, which triggered the divide-by-zero guard and saturated the result to the pixel type's maximum value. It now computes ``image * 2``.
* ``image // 0.5`` previously saturated in the same way, and now computes ``floor(image / 0.5)``. ``-0.5 // image`` now yields ``-1`` for a positive pixel value of 1, rather than ``0`` from the truncated constant.
* ``image ** 0.5`` previously used an exponent of ``0`` (all ones). It now computes the square root.

The final cast of a result to the output pixel type uses the C++ default numeric conversion (truncation toward zero, not rounding).

**64-bit Integer Precision:**

``DivideReal``, ``DivideFloor`` and ``Pow`` already converted the pixel values to ``double`` in 2.x. For ``Multiply`` and ``Divide``, however, the pixel values are now converted to ``double`` along with the constant. ``int64`` and ``uint64`` pixel values with a magnitude above 2\ :sup:`53` are rounded to the nearest representable ``double`` before these two filters operate on them. In SimpleITK 2.x these operations were exact for such values, because the constant was cast to the integer pixel type. For example, a pixel of 9007199254740993 multiplied by ``1.0`` yields 9007199254740992. The constant has always been a ``double`` in the interface, so a constant above 2\ :sup:`53` was never exactly representable. Images with values below 2\ :sup:`53`, which includes all 8, 16 and 32-bit integer types, are not affected. If exact 64-bit integer arithmetic is required, use the image/image overloads with a constant image of the same pixel type, which do not convert the pixels to ``double``.

**Migration:**

Code that relied on the previous truncation, which is unlikely to be intentional, should truncate the constant explicitly, for example ``image * int(0.5)``. To keep fractional results, cast the image to a floating point type before the operation:

.. code-block:: python

   img = sitk.Image([2, 2], sitk.sitkUInt8) + 10

   # 2.x: all zeros, 3.x: 5 (computed at double precision)
   result = img * 0.5

   # Compute in floating point and keep fractional results
   result = sitk.Cast(img, sitk.sitkFloat32) * 0.5
