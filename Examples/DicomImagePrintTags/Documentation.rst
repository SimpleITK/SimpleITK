.. _lbl_print_image_meta_data_dictionary:

Read Image Meta-Data Dictionary and Print
=========================================

Overview
--------

This example illustrates how to read only an image's information and meta-data dictionary then access the meta-data dictionary via the `ImageFileReader <https://itk.org/SimpleITKDoxygen/html/classitk_1_1simple_1_1ImageFileReader.html>`_.

Reading an entire image can be a memory and time intensive operation if the image is large or there are many files to read. The image information and meta-data dictionary can be read without the bulk data by using the ImageFilerReader's object oriented interface, and use the ImageFileReader::ReadImageInformation method.

Most image types do not have a meta-data dictionary. The most common case for images with a dictionary is DICOM, but also the fields from a TIFF, NIFTI, MetaIO and other file formats load some of their information into the meta-data dictionary. When reading a whole image the meta-data dictionary is loaded into an image, but is not propagated through filters.

 For efficiency, the default DICOM reader settings will only load public tags (even group numbers). In the example we explicitly set the reader to load private tags (odd group numbers). For further information on DICOM data elements see the standard part 5, `Data Structures and Encoding <http://dicom.nema.org/medical/dicom/current/output/pdf/part05.pdf>`_.

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
