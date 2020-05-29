.. _lbl_dcm_convert:

Resample and Convert DICOM to Common Image Formats
==================================================

Overview
--------
This example illustrates the use of SimpleITK for converting a set of DICOM images to other file formats (tif, jpg, png,...). The output file format is specified by the user, and the output image width can also be specified by the user (height is determined from the width as resulting pixel sizes are required to be isotropic). Grayscale images with high dynamic range are rescaled to [0,255] before conversion to the new format. Output is written in the same location as the input image, or to a user specified output directory. An additional csv file mapping between original and converted file names is also written, either to the specified output directory or to the current working directory.


Code
----

.. tabs::

  .. tab:: Python

    .. literalinclude:: ../../Examples/DicomConvert/DicomConvert.py
       :language: python
       :lines: 19-

  .. tab:: R

    .. literalinclude:: ../../Examples/DicomConvert/DicomConvert.R
       :language: r
       :lines:  22-
