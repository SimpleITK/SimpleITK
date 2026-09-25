.. _lbl_apply_to_image_metadata_and_warp:

Apply To Image Metadata And Warp
================================

Overview
--------

This example demonstrates how to apply a linear transform (e.g., an affine
transform) followed by a floating point displacement field to an image with
only a single resampling pass.

A ``DisplacementFieldTransform`` requires a double precision displacement
field. Conventionally, a composite transform containing both a linear and a
displacement field component is used to perform the resampling in a single
step. However, the displacement field itself may be a single precision image,
which the transform cannot use directly. This example shows a two step
alternative: first apply the linear transform to the image metadata, and then
apply the non-linear displacement field via resampling.

Since ``Transform.ApplyToImageMetadata`` only changes an image's origin,
spacing, and direction, it has no cost -- no pixel data is touched. The
linear part of the deformation is therefore applied "for free" this way,
and only the non-linear, residual deformation, represented here as a
displacement field loaded from a file, is applied by resampling, via
``WarpImageFilter`` (``sitk.Warp``). This avoids compounding two separate
interpolations for what is ultimately one resampling operation.

Note that ``ApplyToImageMetadata`` is only valid for linear transforms
that have an inverse.

Since ``ApplyToImageMetadata`` changes where the moving image's content
sits in physical space, and ``Warp`` otherwise defaults to the
displacement field's own grid, the example records the moving image's
original size, origin, spacing, and direction before applying the linear
transform, and passes them explicitly to ``Warp`` as the output grid, so
the result is defined on the original image's grid.

Code
----

.. tabs::

  .. tab:: Python

    .. literalinclude:: ../../Examples/ApplyToImageMetadataAndWarp/ApplyToImageMetadataAndWarp.py
       :language: python
       :lines: 19-
