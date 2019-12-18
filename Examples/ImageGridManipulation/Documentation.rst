Image Grid Manipulation
=======================


Overview
--------

There are numerous SimpleITK filters that have similar functions, but very
important differences. The filters that will be compared are:

 - ``JoinSeriesImageFilter()`` - Joins multiple N-D images into an (N+1)-D image
 - ``ComposeImageFilter()`` - Combines several scalar images into a multicomponent vector image
 - ``VectorIndexSelectionCastImageFilter()`` - Extracts the selected index of the input pixel
   type vector (the input image pixel type must be a vector and the output a scalar). Additionally,
   this filter can cast the output pixel type (SetOutputPixelType method).
 - ``ExtractImageFilter()`` - Crops an image to the selected region bounds using vectors;
   Collapses dimensions unless dimension is two
 - ``CropImageFilter()`` - Similar to ``ExtractImageFilter()``, but crops an image by an
   ``itk::Size`` at upper and lower bounds
 - Image Slicing Operator - Uses slicing (``img[i:j, k:l]``) to extract a subregion of an image

All of these operations will maintain the physical location of the pixels,
instead modifying the image's metadata.

Comparisons
-----------

Composition Filters
+++++++++++++++++++
While ``JoinSeriesImageFilter()`` merges multiple images of the same pixel
type in N dimensions into an image in N+1 dimensions, ``ComposeImageFilter()``
will combine scalar images into a vector image of the same dimension. The
former is useful for connecting a series of contiguous images while the latter
is more useful for merging multiple channels of the same object into one image
(such as RGB).

Extraction Filters
++++++++++++++++++
``VectorIndexSelectionCastImageFilter()`` will isolate a single channel in a
vector image and return a scalar image. On the other hand,
``ExtractImageFilter()`` and ``CropImageFilter()`` will extract and return a
subregion of an image, using an ExtractionRegion size and index and
``itk::Size``'s respectively. However, note that only the
``ExtractImageFilter()`` collapses dimensions. The image slicing operator
can also serve the same purpose.


Code
----

.. tabs::

  .. tab:: Python

    .. literalinclude:: ../../Examples/ImageGridManipulation/ImageGridManipulation.py
       :language: python
       :lines: 1,19-

  .. tab:: R

    .. literalinclude:: ../../Examples/ImageGridManipulation/ImageGridManipulation.R
       :language: R
       :lines: 18-
