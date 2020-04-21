Fast Marching Segmentation
==========================


Overview
--------

The fast marching method is a simple form of level-set evolution where
only a positive speed term is used to govern the differential
equation. The resulting level-set contour only grows over
time. Practically, this algorithm can be used as an advanced region
growing segmentation which is controlled by a speed image.

A good propagation speed image for segmentation is close to zero
near object boundaries and relatively high in between. In this example,
an input feature image is smoothed with an `anisotropic
diffusion <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1CurvatureAnisotropicDiffusionImageFilter.html>`_
method, then the gradient magnitude is used to produce an edge
image. A Gaussian with a parameterized *sigma* is used during the
gradient computation to enable the level-set to slow down near
edges. The `Sigmoid filter
<https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1SigmoidImageFilter.html>`_
performs a linear transform on the gradient magnitude so that
boundaries are near zero and homogeneous regions are close to one. The
values for *alpha* and *beta* are provided in the testing code. The heuristics used to
estimate good values are dependent on the minimum value along a boundary
and the mean value of the gradient in the object's region.

Lastly the `fast marching filter
<https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1FastMarchingImageFilter.html>`_
is configured with an initial trial point and starting value. Each
trial point consists of a tuple for an image index including an optional
unsigned starting seed value at the trial point. The trial points are
the starting location of the level-set. The output of the fast
marching filter is a *time-crossing map* that indicate the time of
arrival of the propagated level-set front. We threshold the result to
the region the level-set front propagated through to form the
segmented object. A graphical interface can be constructed to show the
contour propagation over time, enabling a user to select a the desired
segmentation.

Code
----

.. tabs::

  .. tab:: C#

    .. literalinclude:: ../../Examples/FastMarchingSegmentation/FastMarchingSegmentation.cs
       :language: c#
       :lines: 18-

  .. tab:: C++

    .. literalinclude:: ../../Examples/FastMarchingSegmentation/FastMarchingSegmentation.cxx
       :language: C++
       :lines: 1,19-

  .. tab:: Python

    .. literalinclude:: ../../Examples/FastMarchingSegmentation/FastMarchingSegmentation.py
       :language: python
       :lines: 1,19-
