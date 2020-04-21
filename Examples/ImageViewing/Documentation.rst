.. _lbl_image_viewing:

Image Viewing
==============================

Overview
--------

This example illustrates the basic image viewing capabilities provided by SimpleITK.

The focus of SimpleITK is on image analysis and not display. We therefor use
an ad-hoc image viewing approach, relying on an external program. By default
this is the Fiji/ImageJ program.

When using this functionality, SimpleITK writes the image to disc in a temporary
location and then launches the viewer. Potential issues with this approach:

  1. The external viewer program is not found. Either it is not installed, or not
     installed in the expected location, for details see :ref:`lbl_imageJ_not_found`)
  2. Writing the image to disc fails when there isn't enough disc space.
  3. The external program cannot read the image file because it was saved in a format
     not supported by the program.


To control viewing you have two options:

  1. Procedural approach. Use the `Show <https://simpleitk.org/doxygen/latest/html/namespaceitk_1_1simple.html#a86cb9e226d455efca3ba034dc2154605>`_
     function, with control primarily done via environment variable settings.
  2. Object oriented approach. Use the `ImageViewer <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ImageViewer.html>`_
     class, with control via the object's interface.

One can either set the viewing application, if you just want to change the
specific viewer, or set the viewing command. The latter allows you to specify
viewer specific arguments such as -z for ITK-SNAP, see below, to open in a
zoomed view.

Code
----

.. tabs::

  .. tab:: Python

    .. literalinclude:: ../../Examples/ImageViewing/ImageViewing.py
       :language: python
       :lines: 19-

  .. tab:: R

    .. literalinclude:: ../../Examples/ImageViewing/ImageViewing.R
       :language: R
       :lines: 18-
