.. _lbl_fundamental_concepts:

Fundamental Concepts
--------------------

The two basic elements which are at the heart of SimpleITK are images and
spatial transformations. These follow the same conventions as the ITK components
which they represent. The fundamental underlying concepts are described below.


Images
++++++

The fundamental tenet of an image in ITK and consequentially in SimpleITK is
that an image is defined by a set of points on a grid occupying a **physical region
in space**. This significantly differs from many other image analysis libraries
that treat an image as an array which has two implications: (1) pixel/voxel spacing
is assumed to be isotropic and (2) there is no notion of an image's location in
physical space.

SimpleITK images are multi-dimensional ( the default configuration
includes images from 2D upto 5D ) and can be a scalar, labelmap
(scalar with run length encoding), complex value or have an arbitrary
number of  scalar channels ( also known as a vector image). The region
in physical space which an image occupies is defined by the image's:

1. Origin (vector like type) - location in the world coordinate system of
   the voxel with all zero indexes.
2. Spacing (vector like type) - distance between pixels along each of the
   dimensions.
3. Size (vector like type) - number of pixels in each dimension.
4. Direction cosine matrix (vector like type representing matrix in row major order) -
   direction of each of the axes corresponding to the matrix columns.

The meaning of each of these meta-data elements
is visually illustrated in :ref:`this figure <lbl_image_metadata>`.

.. _lbl_image_metadata:
.. figure:: ../images/ImageOriginAndSpacing.svg
   :alt: Image meta-data.

   An image in SimpleITK occupies a region in physical space which is defined by
   its meta-data (origin, size, spacing, and direction cosine matrix). Note that
   the image's physical extent starts half a voxel before the origin and ends half
   a voxel beyond the last voxel.

In SimpleITK, when we construct an image we specify its dimensionality, size and pixel
type, all other components are set to **reasonable default values**:

1. origin - all zeros.
2. spacing - all ones.
3. direction - identity.
4. intensities in all channels - all zero.

In the following Python code snippet we illustrate how to create a 2D image with five
float valued channels per pixel, origin set to (3, 14) and a spacing of (0.5, 2).
Note that the metric units associated with the location of the image origin
in the world coordinate system and the spacing between pixels are unknown
(km, m, cm, mm,...). It is up to you the developer to be consistent. More about
that :ref:`below <lbl_metric_units>`.

.. code-block:: python

 image = sitk.Image([10,10], sitk.sitkVectorFloat32, 5)
 image.SetOrigin((3.0, 14.0))
 image.SetSpacing((0.5, 2))


The tenet that images occupy a spatial location in the physical world has to do with
the original application domain of ITK and SimpleITK, medical imaging. In that domain
images represent anatomical structures with metric sizes and spatial locations.
Additionally, the spacing between voxels is often non-isotropic (most commonly the
spacing along the inferior-superior/foot-to-head direction is larger). Viewers that
treat images as an array will display a distorted image as shown in
:ref:`this figure <lbl_isotropy>`.

.. _lbl_isotropy:
.. figure:: ../images/nonisotropicVsIsotropic.svg
   :alt: nonisotropic vs. isotropic pixels.

   The same image displayed with a viewer that is not aware of spatial meta-data
   (left image) and one that is aware (right image). The image's pixel spacing is (0.97656, 2.0)mm.

As an image is also defined by its spatial location, two images with the same pixel data
and spacing may not be considered equivalent. Think of two CT scans of the same patient
acquired at different sites. :ref:`This figure <lbl_spatial_location>`
illustrates the notion of spatial location in
the physical world, the two images are considered different even though
the intensity values and pixel spacing are the same.

.. _lbl_spatial_location:
.. figure:: ../images/spatialRelationship.svg
   :alt: images are spatial objects

   Two images with exactly the same pixel data, positioned in the world coordinate
   system. In SimpleITK these are not considered the same image, because they occupy
   different spatial locations. The image on the left
   has its origin at (-136.3, -20.5) with a direction cosine matrix, in row
   major order, of (0.7, -0.7, 0.7, 0.7). The image on the right's origin is
   (16.9, 21.4) with a direction cosine matrix of (1,0,0,1).

.. _lbl_metric_units:

As SimpleITK images occupy a physical region in space, the quantities defining
this region have metric units (cm, mm, etc.). In general SimpleITK assume units are in
millimeters (historical reasons, due to DICOM standard). In practice SimpleITK is not aware
of the specific units associated with each image, it just assumes that they are consistent.
Thus, it is up to you the developer to ensure that all of the images you read and created
are using the same units. Mixing units and using wrong
units has `not ended well in the past <https://en.wikipedia.org/wiki/Mars_Climate_Orbiter>`_.

Finally, having convinced you to think of images as objects occupying a physical region
in space, we need to answer two questions:

1. How do you access the pixel values in an image?

   a. In dynamically typed typed languages such as Python and R use a type agnostic function:

      .. code-block:: python

        image.GetPixel((0,0))

   b. In statically typed languages such as C# and C++ use type specific functions:

      .. code-block:: C++

        image.GetPixelAsUInt8( {0, 0} )

   SimpleITK functions use a zero based indexing scheme. The toolkit also includes
   syntactic sugar that allows one to use the bracket operator in combination with
   the native zero/one based indexing scheme (e.g. a one
   based indexing in R vs. the zero based indexing in Python).
2. How do you determine the physical location of a pixel:

   .. code-block:: python

     image.TransformIndexToPhysicalPoint((0,0))

   This computation can also be done manually using the meta-data defining the
   image's spatial location, but we highly recommend that you do not do so as it
   is error prone.

Channels
========

As stated above, a SimpleITK image can have an arbitrary number of
channels with the content of the channels being a scalar or complex value. This
is determined when an image is created.

In the medical domain, many image types have a single scalar channel (e.g. CT, US).
Another common image type is a three channel image where each channel has scalar
values in [0,255], often people refer to such an image as an RGB image. This terminology
implies that the three channels should be interpreted using the
`RGB color space <https://en.wikipedia.org/wiki/RGB_color_space>`_. In some cases you
can have the same image type, but the channel values represent another color space, such as `HSV
<https://en.wikipedia.org/wiki/HSL_and_HSV>`_ (it decouples the color and intensity
information and is a bit more invariant to illumination changes).
SimpleITK has no concept of color space, thus in both cases it will simply view a pixel value as a
3-tuple.

Word of caution: In some cases looks may be deceiving. Gray scale images are not always
stored as a single channel image. In some cases an image that looks like a gray scale
image is actually a three channel image with the intensity values repeated in each of
the channels. Even worse, some gray scale images can be four
channel images with the channels representing RGBA and the alpha channel set to all 255. This can
result in a significant waste of memory and computation time. Always become familiar with your data.


Additional Resources
=====================
1. The API for the SimpleITK
   `Image class <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1Image.html>`_
   in Doxygen format.
2. To really understand the structure of SimpleITK images and how to work with them,
   we recommend some hands-on interaction using the
   `SimpleITK Jupyter notebooks <https://github.com/InsightSoftwareConsortium/SimpleITK-Notebooks>`_
   (Python and R only).

.. _lbl_transforms:

Transforms
++++++++++

SimpleITK supports two types of spatial transforms, ones with a global (unbounded)
spatial domain and ones with a bounded spatial domain. Points in SimpleITK are
mapped by the transform using the `TransformPoint` method.


All **global domain transforms** are of the form:

.. math::

  T(\mathbf{x}) = A(\mathbf{x}-\mathbf{c}) + \mathbf{t} + \mathbf{c}

The nomenclature used in the documentation refers to the components of the transformations
as follows:

* Matrix - the matrix :math:`A`.
* Center - the point :math:`\mathbf{c}`.
* Translation - the vector :math:`\mathbf{t}`.
* Offset - the expression :math:`\mathbf{t} + \mathbf{c} - A\mathbf{c}`.

A variety of global 2D and 3D transformations are available
(translation, rotation, rigid, similarity, affine...). Some of these
transformations are available with various
parameterizations which are useful for registration purposes.

The second type of spatial transformation, **bounded domain transformations**, are
defined to be identity outside their domain. These include the B-spline deformable
transformation, often referred to as Free-Form Deformation, and the displacement
field transformation.

The B-spline transform uses a grid of control points to represent a
spline based transformation. To specify the transformation the user defines the
number of control points and the spatial region which they overlap. The spline
order can also be set, though the default of cubic is appropriate in most cases.
The displacement field transformation uses a dense set of vectors representing
displacement in a bounded spatial domain. It has no implicit constraints on
transformation continuity or smoothness.

Finally, SimpleITK supports a **composite transformation** with either a bounded or
global domain. This transformation represents multiple transformations applied
one after the other :math:`T_0(T_1(T_2(...T_n(p)...)))`. The semantics are
stack based, that is, first in last applied:

.. code-block:: python

 composite_transform = CompositeTransform([T0, T1])
 composite_transform.AddTransform(T2)

In the context of registration, if you use a composite transform as the transformation
that is optimized, only the parameters of the last transformation :math:`T_n` will
be optimized over.

Additional Resources
=====================

1. The API for the SimpleITK transformation classes is available in Doxygen format:

   * `2D or 3D translation <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1TranslationTransform.html>`_.
   * `VersorTransform <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1VersorTransform.html>`_.
   * `Euler2DTransform <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1Euler2DTransform.html>`_
     and `Euler3DTransform <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1Euler3DTransform.html>`_.
   * `Similarity2DTransform <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1Similarity2DTransform.html>`_
     and `Similarity3DTransform <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1Similarity3DTransform.html>`_.
   * `2D or 3D ScaleTransform <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ScaleTransform.html>`_.
   * `ScaleVersor3DTransform <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ScaleVersor3DTransform.html>`_.
   * `ScaleSkewVersor3DTransform <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ScaleSkewVersor3DTransform.html>`_.
   * `ComposeScaleSkewVersor3DTransform <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ComposeScaleSkewVersor3DTransform.html>`_.
   * `2D or 3D AffineTransform <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1AffineTransform.html>`_.
   * `2D or 3D BSplineTransform <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1BSplineTransform.html>`_.
   * `2D or 3D DisplacementFieldTransform <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1DisplacementFieldTransform.html>`_.
   * `CompositeTransform <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1CompositeTransform.html>`_.
   * `Transform <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1Transform.html>`_.

2. To really understand the structure of SimpleITK transforms and how to work with them,
   we recommend some hands-on interaction using the
   `SimpleITK Jupyter notebooks <https://github.com/InsightSoftwareConsortium/SimpleITK-Notebooks>`_
   (Python and R only).

Resampling
++++++++++

Resampling, as the verb implies, is the action of sampling an image, which itself
is a sampling of an original continuous signal.

Generally speaking, resampling in SimpleITK involves four components:

1. Image - the image we resample, given in coordinate system :math:`m`.
2. Resampling grid - a regular grid of points given in coordinate system :math:`f`
   which will be mapped to coordinate system :math:`m`.
3. Transformation :math:`T_f^m` - maps points from coordinate system :math:`f`
   to coordinate system :math:`m`, :math:`^mp = T_f^m(^fp)`.
4. Interpolator - method for obtaining the intensity values at arbitrary points
   in coordinate system :math:`m` from the values of the points defined by the Image.

While SimpleITK provides a large number of interpolation methods, the two most
commonly used are sitkLinear and sitkNearestNeighbor. The former is used for
most interpolation tasks and is a compromise between accuracy and computational
efficiency. The later is used to interpolate labeled images representing a
segmentation. It is the only interpolation approach which will not introduce
new labels into the result.

The SimpleITK interface includes three variants for specifying the resampling grid:

1. Use the same grid as defined by the resampled image.
2. Provide a second, reference, image which defines the grid.
3. Specify the grid using: size, origin, spacing, and direction cosine matrix.

Points that are mapped outside of the resampled image's spatial extent in physical
space are set to a constant pixel value which you provide (default is zero).

Common Errors
=============

It is not uncommon to end up with an empty (all black) image after resampling.
This is due to:

1. Using wrong settings for the resampling grid (not too common, but does happen).
2. Using the inverse of the transformation :math:`T_f^m`. This is a relatively
   common error, which is readily addressed by invoking the transformation's
   `GetInverse` method.


Additional Resources
=====================

1. The API for the SimpleITK
   `ResampleImageFilter class <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ResampleImageFilter.html>`_
   in Doxygen format. The procedural interface for this class supports the three variations for specifying the
   resampling grid described above.
2. To really understand the structure of SimpleITK images and how to work with them
   we recommend some hands-on interaction using the
   `SimpleITK Jupyter notebooks <https://github.com/InsightSoftwareConsortium/SimpleITK-Notebooks>`_
   (Python and R only).
