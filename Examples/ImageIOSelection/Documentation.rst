.. _lbl_image_io_selection:

IO Selection for Image Reading
==============================

Overview
--------

This example illustrates how to explicitly select a specific IO for image reading.

When using the default settings for the `ImageFileReader class <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ImageFileReader.html>`_ or
the `ReadImage <https://simpleitk.org/doxygen/latest/html/namespaceitk_1_1simple.html#ae3b678b5b043c5a8c93aa616d5ee574c>`_ function
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

  .. tab:: C#

    .. literalinclude:: ../../Examples/ImageIOSelection/ImageIOSelection.cs
       :language: csharp
       :lines: 18-

  .. tab:: C++

    .. literalinclude:: ../../Examples/ImageIOSelection/ImageIOSelection.cxx
       :language: cpp
       :lines: 19-

  .. tab:: Java

    .. literalinclude:: ../../Examples/ImageIOSelection/ImageIOSelection.java
       :language: java
       :lines: 23-

  .. tab:: Lua

    .. literalinclude:: ../../Examples/ImageIOSelection/ImageIOSelection.lua
       :language: lua
       :lines: 19-

  .. tab:: Python

    .. literalinclude:: ../../Examples/ImageIOSelection/ImageIOSelection.py
       :language: python
       :lines: 19-

  .. tab:: R

    .. literalinclude:: ../../Examples/ImageIOSelection/ImageIOSelection.R
       :language: R
       :lines: 22-

  .. tab:: Ruby

    .. literalinclude:: ../../Examples/ImageIOSelection/ImageIOSelection.rb
       :language: ruby
       :lines: 18-

  .. tab:: Tcl

    .. literalinclude:: ../../Examples/ImageIOSelection/ImageIOSelection.tcl
       :language: tcl
       :lines: 19-
