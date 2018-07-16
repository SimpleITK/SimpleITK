.. _lbl_dicom_series_from_array:

Dicom Series From Array
==============================

Overview
--------
This example illustrates how to write a DICOM series from a numeric array and create appropriate meta-data so it can be read by DICOM viewers.

Generating an array is done using a simple random number generator for this case but can come from other sources.

Writing the 3D image as a DICOM series is done by configuring the meta-data dictionary for each of the slices and then writing it in DICOM format. In our case we generate all of the meta-data to indicate that this series is derived. Note that we write the intensity values as is and thus do not set the rescale slope (0028|1053), rescale intercept (0028|1052) meta-data dictionary values.

See also :ref:`lbl_print_image_meta_data_dictionary`, :ref:`lbl_dicom_series_reader`.


Code
----

.. tabs::

  .. tab:: Python

    .. literalinclude:: DicomSeriesFromArray.py
       :language: python
       :lines: 19-

  .. tab:: R

    .. literalinclude:: DicomSeriesFromArray.R
       :language: R
       :lines: 18-
