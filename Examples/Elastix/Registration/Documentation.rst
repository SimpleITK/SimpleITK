Registration and Transformation
================================

Overview
--------

This example demonstrates image registration and transformation using SimpleElastix. SimpleElastix provides access to the powerful `elastix <https://elastix.lumc.nl/>`_ registration toolbox through SimpleITK's `ElastixImageFilter <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ElastixImageFilter.html>`_ and `TransformixImageFilter <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1TransformixImageFilter.html>`_ classes.

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

    .. literalinclude:: ../../Examples/Elastix/Registration/elx.cs
       :language: c#
       :lines: 18-

  .. tab:: C++

    .. literalinclude:: ../../Examples/Elastix/Registration/elx.cxx
       :language: c++
       :lines: 1-

  .. tab:: Java

    .. literalinclude:: ../../Examples/Elastix/Registration/elx.java
       :language: java
       :lines: 18-

  .. tab:: Lua

    .. literalinclude:: ../../Examples/Elastix/Registration/elx.lua
       :language: lua
       :lines: 18-

  .. tab:: Python

    .. literalinclude:: ../../Examples/Elastix/Registration/elx.py
       :language: python
       :lines: 1-

  .. tab:: R

    .. literalinclude:: ../../Examples/Elastix/Registration/elx.R
       :language: r
       :lines: 18-

Transformation (tfx)
^^^^^^^^^^^^^^^^^^^^

.. tabs::

  .. tab:: C#

    .. literalinclude:: ../../Examples/Elastix/Registration/tfx.cs
       :language: c#
       :lines: 18-

  .. tab:: C++

    .. literalinclude:: ../../Examples/Elastix/Registration/tfx.cxx
       :language: c++
       :lines: 1-

  .. tab:: Java

    .. literalinclude:: ../../Examples/Elastix/Registration/tfx.java
       :language: java
       :lines: 18-

  .. tab:: Lua

    .. literalinclude:: ../../Examples/Elastix/Registration/tfx.lua
       :language: lua
       :lines: 18-

  .. tab:: Python

    .. literalinclude:: ../../Examples/Elastix/Registration/tfx.py
       :language: python
       :lines: 1-

  .. tab:: R

    .. literalinclude:: ../../Examples/Elastix/Registration/tfx.R
       :language: r
       :lines: 18-
