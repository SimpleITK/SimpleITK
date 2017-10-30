.. _lbl_dicom_series_from_array:

Dicom Series From Array
==============================

Overview
--------
This example illustrates how to write a DICOM series from an array in Python

Generating an array is done using a simple random number generator for this case but can come from other sources.

Writing the 3D image as a DICOM series is done by configuring the meta-data dictionary for each of the slices and then writing it in DICOM format. In our case we generate all of the meta-data to indicate that this series is derived. Note that we write the intensity values as is and thus do not set the rescale slope (0028|1053), rescale intercept (0028|1052) meta-data dictionary values.

See also :ref:`lbl_print_image_meta_data_dictionary`, :ref:`lbl_dicom_series_reader`.


Code
----

Python
......

.. literalinclude:: DicomSeriesFromArray.py
   :language: python
   :lines: 1,19-

