.. _lbl_sub_dimension_process:

Slice by Slice Adaptive Histogram Equalization
==============================================


Overview
--------

Most SimpleITK filters can only operate on 2 or 3 dimensional images, with the exception of filters such as
`ExtractImageFilter`, `PasteImageFilter`, `SliceImageFilter` and `JoinSeriesImageFilter`. However, SimpleITK
(by default) supports upto 5 dimensional images. A high dimensional image can be processed by extracting 2 or 3
dimensional images, then either using the `JoinSeriesImageFilter` to join the sub-volumes together or the
`PasteImageFilter` to copy the results back to the original image. Possible reasons include when the z direction
spacing is too great, or for computation or memory efficient reasons. Additionally, it may be desired to process a
volume (3d or higher) as a sequence of 2 dimensional images.

In this example, the `AdaptiveHistogramEqualizationImageFilter` is used to processes a higher dimensional image as a
sequence of two dimensional images.. When the filter is run only a single X, Y cross-section of the volume.

Both the Python and the C++ examples demonstrate a reusable "decorator" to wrap the SimpleITK
`AdaptiveHistogramEqualization` procedure to process the input image by 2d slices. A function decorator is a function
which takes a function as an argument and returns a modified or wrapped function. The decorators are written
generically, so they can work with other SimpleITK procedures or a custom procedure. The decorators wrap the procedure
to accept a 2, 3, 4 or 5 dimensional image as input. The pasting approach is used to provide a memory efficient approach.

The process of extracting a slice, processing, and then pasting back to the original image is straight forward. However,
to create a reusable decorator requires advanced language specific features. Additionally, to efficiently do pasting
:ref:`in place execution<lbl_cpp_inplace>`  is done in C++, and sliced indexed assignment is used in Python.



Code
----

.. tabs::

  .. tab:: Python

    .. literalinclude:: ../../Examples/SliceBySliceDecorator/SliceBySliceDecorator.py
       :language: python
       :lines: 1,19-

  .. tab:: C++

    .. literalinclude:: ../../Examples/SliceBySliceDecorator/SliceBySliceDecorator.cxx
       :language: c++
       :lines: 18-
