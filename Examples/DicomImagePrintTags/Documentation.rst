.. _lbl_print_image_meta_data_dictionary:

Print Image Meta-Data Dictionary
================================

Overview
--------

This example illustrates how to read an image and access its meta-data dictionary. Most image types do not have a meta-data dictionary. The most common case for images with a dictionary is DICOM. For efficiency, the default reader settings will only load public DICOM tags (even group numbers). In the example we explicitly set the reader to load private tags (odd group numbers).

For further information on DICOM data elements see the standard part 5, `Data Structures and Encoding <http://dicom.nema.org/medical/dicom/current/output/pdf/part05.pdf>`_.

See also :ref:`lbl_dicom_series_read_modify_write`, :ref:`lbl_dicom_series_reader`.

Code
----

Python
......

.. literalinclude:: DicomImagePrintTags.py
   :language: python
   :lines: 1,19-

R
.

.. literalinclude:: DicomImagePrintTags.R
   :language: r
   :lines: 18-
