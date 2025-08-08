Landmark Registration
=====================

This example demonstrates the use of point based registration. This form of registration is often used to initialize an intensity based registration that refines the results of the point base method, hence the "initializer" in the class name. The example uses a 2D rigid transformation, though the `LandmarkBasedTransformInitializerFilter <https://simpleitk.org/doxygen/v2_2/html/classitk_1_1simple_1_1LandmarkBasedTransformInitializerFilter.html>`_ class supports other transformation types including VersorRigid3DTransform, AffineTransform
and BSplineTransform.

.. include:: registrationExamplePrefix.rst

Overview
--------



Code
----

.. tabs::

  .. tab:: C++

    .. literalinclude:: ../../Examples/LandmarkRegistration/LandmarkRegistration.cxx
       :language: c++
       :lines: 21-

  .. tab:: C#

    .. literalinclude:: ../../Examples/LandmarkRegistration/LandmarkRegistration.cs
       :language: csharp
       :lines: 23-

  .. tab:: Java

    .. literalinclude:: ../../Examples/LandmarkRegistration/LandmarkRegistration.java
       :language: java
       :lines: 23-

  .. tab:: Python

    .. literalinclude:: ../../Examples/LandmarkRegistration/LandmarkRegistration.py
       :language: python
       :lines: 1,21-

  .. tab:: R

    .. literalinclude:: ../../Examples/LandmarkRegistration/LandmarkRegistration.R
       :language: r
       :lines: 21-
