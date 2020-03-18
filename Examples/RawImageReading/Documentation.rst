.. _lbl_raw_image_reading:

Raw Image Reading
=================

Overview
--------
In some, hopefully rare, cases you may only have the image information in raw pixel format, a binary blob file. For example the `chest x-ray dataset <http://db.jsrt.or.jp/eng.php>`__ from the Japanese Society of Radiological Technology (JSRT).

To read such an image you are required to know three things:

  1. Image size (number of pixels per dimenssion).
  2. Pixel type (e.g. sitkUInt16).
  3. The byte order ( or `endianness <https://en.wikipedia.org/wiki/Endianness>`__) where little endian is most common.

If the byte order in unknown since it only has two options and we can try both. The one resulting in a visually correct image is the correct byte order.

As a SimpleITK image is a spatial object, we may also need to provide its origin, spacing, and directon cosine matrix. Without explicit information we can make reasonable assumptions that often work, as shown in the code below.


Code
----

.. tabs::

  .. tab:: Python

    .. literalinclude:: ../../Examples/RawImageReading/RawImageReading.py
       :language: python
       :lines: 19-

  .. tab:: R

    .. literalinclude:: ../../Examples/RawImageReading/RawImageReading.R
       :language: r
       :lines:  25-
