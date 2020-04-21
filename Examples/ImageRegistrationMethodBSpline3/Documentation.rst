.. _lbl_image_registration_method_bspline3:

Image Registration Method BSpline 3
===================================

.. include:: registrationExamplePrefix.rst

Overview
--------

This example performs registration of multi-modality images with a multi-resolution BSpline approach.

A `BSplineTransform
<https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1BSplineTransform.html>`_
usually has a large number of parameters which increases the
complexity and duration of optimizing the deformation. The
multi-resolution BSpline approach initially performs the registration
at a lower resolution with fewer parameters at the first level and
then adapts or resamples the BSpline control points to a higher
resolution at subsequent levels. This transformation adaption is done
concurrently with the `ImageRegistrationMethod's
<https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ImageRegistrationMethod.html>`_
multi-level feature. This enables the setting of the shrink factor,
smoothing sigmas, sampling percentage and BSpline resolution to vary
per level to efficiently solve a diverse set of registration
problems.

The initial transform is the low resolution BSpline. The scaling
factor of each BSpline used per level is specified with the
``ImageRegistration::SetInitialBSpline`` method's third argument as an
integer array. The first value is usually 1 and it is reasonable to
double the resolution at each registration level. For this example the
last resolution is 5, so that the result is comparable to the
transformation from the :ref:`previous
<lbl_image_registration_method_bspline2>` example.

It can be important to monitor and observe the transform at each level
or iteration. When the "inplace" option is enabled, the transform
passed as the initial transform will be up to date during the
registration process which enables it to be used in :ref:`event
commands <lbl_filter_progress_reporting>`.

See also: :ref:`lbl_image_registration_method_bspline1`, :ref:`lbl_image_registration_method_bspline2`.

Code
----

.. tabs::

  .. tab:: C++

    .. literalinclude:: ../../Examples/ImageRegistrationMethodBSpline3/ImageRegistrationMethodBSpline3.cxx
       :language: c++
       :lines: 18-

  .. tab:: Python

    .. literalinclude:: ../../Examples/ImageRegistrationMethodBSpline3/ImageRegistrationMethodBSpline3.py
       :language: python
       :lines: 1,19-
