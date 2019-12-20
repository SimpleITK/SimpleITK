.. _lbl_advanced_image_reading:

Advanced Image Reading
==============================

Overview
--------

This example illustrates advanced image reading options:

  1. Querying an image for its meta-data without reading the bulk intensity data.
  2. Reading a sub-region of an image.

Querying an image for its meta-data
++++++++++++++++++++++++++++++++++++

In some cases you may only want to read an image's meta-data without reading the
bulk intensity data into memory. For instance, if you want to read subregions of
an image and not the whole image or if you want to display image
information (e.g. patient name) to a user in a GUI which then allows them to
select a specific image.

Reading an image sub-region
+++++++++++++++++++++++++++
In some cases you are only interested in reading a sub-region of an image. This
may be due to memory constraints or if it is known that the relevant content is
always in a sub region of the image. If the specific image IO used for this operation
supports streaming then this will indeed only read the sub-region, otherwise the whole
image is read into memory and the sub-region is returned. The IOs that support
streaming are:
1. TIFFImageIO (supports a subset of encodings)
2. MetaImageIO
3. NrrdImageIO
4. HDF5ImageIO (supports a subset of encodings)
5. MRCImageIO
6. VTKImageIO (supports a subset of encodings)



Code
----

.. tabs::

  .. tab:: Python

    .. literalinclude:: ../../Examples/AdvancedImageReading/AdvancedImageReading.py
       :language: python
       :lines: 19-

  .. tab:: R

    .. literalinclude:: ../../Examples/AdvancedImageReading/AdvancedImageReading.R
       :language: R
       :lines: 22-
