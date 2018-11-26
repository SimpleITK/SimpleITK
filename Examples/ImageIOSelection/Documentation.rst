.. _lbl_image_io_selection:

IO Selection for Image Reading
==============================

Overview
--------

This example illustrates how to explicitly select a specific IO for image reading.

When using the default settings for the `ImageFileReader class <https://itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ImageFileReader.html>`_ or
the `ReadImage <https://itk.org/SimpleITKDoxygen/html/namespaceitk_1_1simple.html#ae3b678b5b043c5a8c93aa616d5ee574c>`_ function
you have minimal control over the reading. That is, the specific IO mechanism is
determined automatically based on the file type and the file is read into
memory.

In some cases there are multiple IO classes that support reading the same image
format and you do not know which one was used. For example the 'SCIFIOImageIO'
and 'JPEGImageIO' both support reading JPEG images. As these are different implementations
they may vary in performance and in the support of the features associated with the specific
format. As a consequence, you may want or need to select one implementation over the other.
Explicitly selecting the IO allows you to do so.

Code
----

.. tabs::

  .. tab:: Python

    .. literalinclude:: ImageIOSelection.py
       :language: python
       :lines: 19-

  .. tab:: R

    .. literalinclude:: ImageIOSelection.R
       :language: R
       :lines: 22-
