.. _lbl_advanced_image_reading:

Advanced Image Reading
==============================

Overview
--------

This example illustrates advanced image reading options:
  1. Explicitly selecting a specific IO for reading.
  2. Querying an image for its meta-data without reading the bulk intensity data.
  3. Reading a sub-region of an image.

Selecting a Specific IO
++++++++++++++++++++++++
When using the default settings for the `ImageFileReader class <https://itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ImageFileReader.html>`_ or
the `ReadImage <https://itk.org/SimpleITKDoxygen/html/namespaceitk_1_1simple.html#ae3b678b5b043c5a8c93aa616d5ee574c>`_ function
you have minimal control over the reading. That is, the specific IO mechanism is
determined automatically based on the file type and the whole file is read into
memory.

In some cases there are multiple IO classes that support reading the same image
format and you do not know which one was used. For example the 'SCIFIOImageIO'
and 'JPEGImageIO' both support reading JPEG images. The SCIFIOImageIO reading
is much slower than the JPEGImageIO. With the advanced reading approach you can
find out which IO classes are supported by the ImageFileReader and indicate which
one you want to use.

Querying an image for its meta-data
++++++++++++++++++++++++++++++++++++

In some cases you may only want to read an image's meta-data without reading the
bulk intensity data into memory. For instance, if you want to display image
information (e.g. patient name) to a user in a GUI which then allows them to
select a specific image.

Reading an image sub-region
+++++++++++++++++++++++++++
In some cases you are only interested in reading a sub-region of an image. This
may be due to memory constraints or if it is known that the relevant content is
always in a sub region of the image.



Code
----

.. tabs::

  .. tab:: Python

    .. literalinclude:: AdvancedImageReading.py
       :language: python
       :lines: 19-

  .. tab:: R

    .. literalinclude:: AdvancedImageReading.R
       :language: R
       :lines: 22-
