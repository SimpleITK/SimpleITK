SimpleElastix Registration
==========================

Overview
--------

This example demonstrates the usage of the SimpleElastix framework for image registration and transformation. SimpleElastix provides access to the powerful `elastix <https://elastix.lumc.nl/>`_ registration toolbox through SimpleITK's `ElastixImageFilter <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ElastixImageFilter.html>`_ and `TransformixImageFilter <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1TransformixImageFilter.html>`_ classes.

The elastix framework is widely used for medical image registration and offers:

* A comprehensive collection of registration algorithms
* Multi-resolution strategies
* A variety of transformation models (rigid, affine, B-spline, etc.)
* Multiple similarity metrics for different imaging modalities
* A `parameter zoo <https://lkeb.ml/modelzoo/>`_ with pre-configured settings for common registration scenarios

This example includes two programs:

1. **elx** - Performs image registration using ElastixImageFilter
2. **tfx** - Applies transformations using TransformixImageFilter

The registration workflow typically consists of:

1. Reading fixed and moving images
2. Loading or creating a parameter map that defines the registration strategy
3. Executing the registration to obtain a registered image and transform parameters
4. Optionally applying the transform to other images using Transformix

Parameter maps can be loaded from text files, created using default presets, or customized programmatically. The elastix parameter files use a simple text format that allows fine-grained control over the registration process.

Code
----

Registration (elx)
^^^^^^^^^^^^^^^^^^

.. tabs::

  .. tab:: C#

    .. literalinclude:: ../../Examples/Elastix/elx.cs
       :language: c#
       :lines: 18-

  .. tab:: C++

    .. literalinclude:: ../../Examples/Elastix/elx.cxx
       :language: c++
       :lines: 1-

  .. tab:: Java

    .. literalinclude:: ../../Examples/Elastix/elx.java
       :language: java
       :lines: 18-

  .. tab:: Lua

    .. literalinclude:: ../../Examples/Elastix/elx.lua
       :language: lua
       :lines: 18-

  .. tab:: Python

    .. literalinclude:: ../../Examples/Elastix/elx.py
       :language: python
       :lines: 1-

  .. tab:: R

    .. literalinclude:: ../../Examples/Elastix/elx.R
       :language: r
       :lines: 18-

Transformation (tfx)
^^^^^^^^^^^^^^^^^^^^

.. tabs::

  .. tab:: C#

    .. literalinclude:: ../../Examples/Elastix/tfx.cs
       :language: c#
       :lines: 18-

  .. tab:: C++

    .. literalinclude:: ../../Examples/Elastix/tfx.cxx
       :language: c++
       :lines: 1-

  .. tab:: Java

    .. literalinclude:: ../../Examples/Elastix/tfx.java
       :language: java
       :lines: 18-

  .. tab:: Lua

    .. literalinclude:: ../../Examples/Elastix/tfx.lua
       :language: lua
       :lines: 18-

  .. tab:: Python

    .. literalinclude:: ../../Examples/Elastix/tfx.py
       :language: python
       :lines: 1-

  .. tab:: R

    .. literalinclude:: ../../Examples/Elastix/tfx.R
       :language: r
       :lines: 18-

See Also
--------

* `elastix documentation <https://elastix.lumc.nl/>`_
* `elastix parameter zoo <https://lkeb.ml/modelzoo/>`_ - Pre-configured parameter files for various registration tasks
* `SimpleITK ElastixImageFilter <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ElastixImageFilter.html>`_
* `SimpleITK TransformixImageFilter <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1TransformixImageFilter.html>`_
