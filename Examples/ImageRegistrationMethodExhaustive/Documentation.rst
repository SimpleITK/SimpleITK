Image Registration Method Exhaustive
====================================


Overview
--------

This script demonstrates the use of the Exhaustive optimizer in the
ImageRegistrationMethod to estimate a good initial rotation position.

Because gradient descent base optimization can get stuck in local
minima, a good initial transform is critical for reasonable
results. Search a reasonable space on a grid with brute force may be a
reliable way to get a starting location for further optimization.

The initial translation and center of rotation for the transform is
initialized based on the first principle moments of the intensities of
the image. Then in either 2D or 3D a Euler transform is used to
exhaustively search a grid of the rotation space at a certain step
size. The resulting transform is a reasonable guess where to start
further registration.

Code
----

.. tabs::

  .. tab:: Python

    .. literalinclude:: ../../Examples/ImageRegistrationMethodExhaustive/ImageRegistrationMethodExhaustive.py
       :language: python
       :lines: 1,19-

  .. tab:: R

    .. literalinclude:: ../../Examples/ImageRegistrationMethodExhaustive/ImageRegistrationMethodExhaustive.R
       :language: R
       :lines: 18-
