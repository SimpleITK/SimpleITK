Common Conventions
------------------

This document contains common conventions that SimpleITK filters, and objects follow. It is intended to describe the interfaces that users should use and developers should implement. If a method or class does not specify different behavior or default values then those described here, it should be assumed that it follows the following conventions.

Naming
......

The object oriented interface of process objects are named based on the specific operation they perform on their input image(s)
with a suffix of **ImageFilter**, the ITK convention. For example, `AbsImageFilter <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1AbsImageFilter.html>`_, `BinaryMinMaxCurvatureFlowImageFilter <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1BinaryMinMaxCurvatureFlowImageFilter.html>`_ etc. For almost all process objects there is also a procedural interface. This interface provides one or more functions which
allow setting parameter values and invoking the operation in one call. This results in concise code and is useful if the filter is only applied once.
These functions use the same naming as the object oriented interface only without the suffix. That is,
the corresponding procedural methods to the object oriented interface examples above are `Abs <https://simpleitk.org/doxygen/latest/html/namespaceitk_1_1simple.html#a54161a47394e60c5758193cd0ab6930e>`_ and `BinaryMinMaxCurvatureFlow <https://simpleitk.org/doxygen/latest/html/namespaceitk_1_1simple.html#ab0cd996e578cd566b0e7318978bd0420>`_.

Note that the complete/detailed documentation appears in the doxygen of the object oriented interface.

Dimensional Vectors
...................

Dimensional Vectors must contain at least the number of elements as the dimensions of the image, elements beyond the image's dimension will be truncated.

The SimpleITK image class can contain 2 or 3 dimensional images. In ITK proper, certain types such as indexes, points, and sizes are templated over the image dimensions. In SimpleITK we utilize the variable length ``std::vector`` for these types, so that non-templated calls can wrap ITK's templated image class. These types are called Dimensional Vectors. If a dimensional vector's length is less that the dimension of the image, an exception will be generated when converted to the ITK type. If there are extra elements in the dimensional vector these values will be ignored.


Image Access
............

`Image <http://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1Image.html>`_ access is in x,y,z order, ``GetPixel(x,y,z)`` or ``image[x,y,z]``, with zero based indexing.

.. _lbl_conventions_mask_image:

Mask Image Types and Default Values
...................................

The default mask image type is a scalar image of ``sitkUInt8`` or ``uint8_t`` pixels. The default values are 0 and 1, with 1s representing the mask.

These defaults are for filter which create masks such as thresholding, and certain other segmentation filters. Additionally, these are the defaults for the binary morphology filters, so that they can easily be applied after segmentation. This choice makes many mask manipulations easier. For example, "masking" an image (scalar or vector) is simply a matter of multiplying by a mask an image. Additionally, the set of {0, 1} pixels is closed under the logical Boolean operators.


Order of Procedural Parameters
..............................

The order of the procedural parameters should be with the most frequently modified parameters at the beginning of the parameter list. While the last parameter, may be ones that the user does not need to set or are infrequently used.


Matrices as Parameters
......................

Matrices are represented as a single dimensional vector with the entries in row major order. The vector :math:`[1, 2, 3, 4, 5, 6]` represents the matrix

.. math::

	\begin{bmatrix} 1 & 2 & 3 \\
		4 & 5 & 6
	\end{bmatrix}


Image Regions as Index and Size
...............................

The `itk::ImageRegion <http://itk.org/Doxygen/html/classitk_1_1ImageRegion.html>`_ is a frequently used class in ITK to define a sub-image area. It is defined by `itk::Index <http://itk.org/Doxygen/html/classitk_1_1Index.html>`_ and `itk::Size <http://itk.org/Doxygen/html/classitk_1_1Size.html>`_ of signed and unsigned integer types respectfully. In SimpleITK, the index and size elements are usually separated into two arguments with separate Set and Get methods.

When specified as a single argument value, it is a 1 dimensional array with the index values followed by the size values i.e. :math:`[idx_x, idx_y, idx_z, size_x, size_y, size_z]`.


Images As Parameters
....................

The dimensionality (2D or 3D) and pixel type (``sitkUInt8``, ``sitkFloat64``...) of images is required to be the same for most methods that receive multiple images as input.

The `ImageRegistrationMethod <http://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ImageRegistrationMethod.html>`_ only supports images with ``sitkFloat32`` and ``sitkFloat64`` pixel types.

Casting an image's pixel type into another is done with the SimpleITK `Cast() <http://simpleitk.org/doxygen/latest/html/namespaceitk_1_1simple.html#af8c9d7cc96a299a05890e9c3db911885>`_ function.
