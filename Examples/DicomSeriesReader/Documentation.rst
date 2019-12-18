.. _lbl_dicom_series_reader:

Dicom Series Reader
==========================


Overview
--------

This example illustrates how to read a DICOM series into a 3D volume. Additional actions include printing some information, writing the image and possibly displaying it using the default display program via the SimpleITK `Show` function. The program makes several assumptions: the given directory contains at least one DICOM series, if there is more than one series the first series is read, and the default SimpleITK external viewer is installed.


See also :ref:`lbl_dicom_series_read_modify_write`, :ref:`lbl_print_image_meta_data_dictionary`.

Code
----

.. tabs::

  .. tab:: C++

    .. literalinclude:: ../../Examples/DicomSeriesReader/DicomSeriesReader.cxx
       :language: c++
       :lines: 18-

  .. tab:: Java

    .. literalinclude:: ../../Examples/DicomSeriesReader/DicomSeriesReader.java
       :language: java
       :lines: 18-

  .. tab:: Lua

    .. literalinclude:: ../../Examples/DicomSeriesReader/DicomSeriesReader.lua
       :language: lua
       :lines:  18-

  .. tab:: Python

    .. literalinclude:: ../../Examples/DicomSeriesReader/DicomSeriesReader.py
       :language: python
       :lines: 1,19-

  .. tab:: R

    .. literalinclude:: ../../Examples/DicomSeriesReader/DicomSeriesReader.R
       :language: R
       :lines:  23-
