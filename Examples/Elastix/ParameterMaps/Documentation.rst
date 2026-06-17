Parameter Maps
==============

Overview
--------

Parameter maps are the primary mechanism for configuring image registration in elastix. A parameter map is a collection of key-value pairs that specifies the components and settings of a registration procedure — including the transform type, optimizer, metric, and multi-resolution strategy. SimpleITK provides a programmatic interface for creating, modifying, reading, and writing these maps.

File Format
-----------

Elastix parameter files are plain text files where each line contains a key and one or more values enclosed in parentheses. Comments begin with ``//``. String values are quoted; numeric values are not. When multiple values are provided, they typically correspond to per-resolution settings.

.. code-block:: text

   // An affine registration parameter file
   (FixedInternalImagePixelType "float")
   (MovingInternalImagePixelType "float")

   (Registration "MultiResolutionRegistration")
   (Interpolator "BSplineInterpolator")
   (Metric "AdvancedMattesMutualInformation")
   (Optimizer "AdaptiveStochasticGradientDescent")
   (ResampleInterpolator "FinalBSplineInterpolator")
   (Resampler "DefaultResampler")
   (Transform "AffineTransform")

   (NumberOfResolutions 4)
   (MaximumNumberOfIterations 500)
   (AutomaticParameterEstimation "true")
   (AutomaticTransformInitialization "true")

For a comprehensive reference of all available parameters, see the `elastix 5.2.0 manual <https://github.com/SuperElastix/elastix/releases/download/5.2.0/elastix-5.2.0-manual.pdf>`_.

Getting Default Parameter Maps
------------------------------

SimpleITK provides pre-configured default parameter maps for common registration scenarios:

* **translation** — Translation only
* **rigid** — Rotation and translation (6 DOF in 3D)
* **affine** — Affine transformation (12 DOF in 3D)
* **bspline** — Non-rigid B-spline deformation
* **groupwise** — Simultaneous registration of multiple images

.. tabs::

  .. tab:: C#

    .. literalinclude:: ../../Examples/Elastix/ParameterMaps/ParameterMaps.cs
       :language: csharp
       :start-after: //START_DEFAULT_PARAMETER_MAP
       :end-before: //END_DEFAULT_PARAMETER_MAP
       :dedent: 12

  .. tab:: C++

    .. literalinclude:: ../../Examples/Elastix/ParameterMaps/ParameterMaps.cxx
       :language: cpp
       :start-after: //START_DEFAULT_PARAMETER_MAP
       :end-before: //END_DEFAULT_PARAMETER_MAP
       :dedent: 2

  .. tab:: Java

    .. literalinclude:: ../../Examples/Elastix/ParameterMaps/ParameterMaps.java
       :language: java
       :start-after: //START_DEFAULT_PARAMETER_MAP
       :end-before: //END_DEFAULT_PARAMETER_MAP
       :dedent: 8

  .. tab:: Lua

    .. literalinclude:: ../../Examples/Elastix/ParameterMaps/ParameterMaps.lua
       :language: lua
       :start-after: --START_DEFAULT_PARAMETER_MAP
       :end-before: --END_DEFAULT_PARAMETER_MAP

  .. tab:: Python

    .. literalinclude:: ../../Examples/Elastix/ParameterMaps/ParameterMaps.py
       :language: python
       :start-after: #START_DEFAULT_PARAMETER_MAP
       :end-before: #END_DEFAULT_PARAMETER_MAP

  .. tab:: R

    .. literalinclude:: ../../Examples/Elastix/ParameterMaps/ParameterMaps.R
       :language: r
       :start-after: #START_DEFAULT_PARAMETER_MAP
       :end-before: #END_DEFAULT_PARAMETER_MAP

Modifying Parameter Maps
------------------------

Parameter maps behave like dictionaries mapping string keys to vectors of string values. You can override any default setting by assigning new values to specific keys:

.. tabs::

  .. tab:: C#

    .. literalinclude:: ../../Examples/Elastix/ParameterMaps/ParameterMaps.cs
       :language: csharp
       :start-after: //START_MODIFY_PARAMETER_MAP
       :end-before: //END_MODIFY_PARAMETER_MAP
       :dedent: 12

  .. tab:: C++

    .. literalinclude:: ../../Examples/Elastix/ParameterMaps/ParameterMaps.cxx
       :language: cpp
       :start-after: //START_MODIFY_PARAMETER_MAP
       :end-before: //END_MODIFY_PARAMETER_MAP
       :dedent: 2

  .. tab:: Java

    .. literalinclude:: ../../Examples/Elastix/ParameterMaps/ParameterMaps.java
       :language: java
       :start-after: //START_MODIFY_PARAMETER_MAP
       :end-before: //END_MODIFY_PARAMETER_MAP
       :dedent: 8

  .. tab:: Lua

    .. literalinclude:: ../../Examples/Elastix/ParameterMaps/ParameterMaps.lua
       :language: lua
       :start-after: --START_MODIFY_PARAMETER_MAP
       :end-before: --END_MODIFY_PARAMETER_MAP

  .. tab:: Python

    .. literalinclude:: ../../Examples/Elastix/ParameterMaps/ParameterMaps.py
       :language: python
       :start-after: #START_MODIFY_PARAMETER_MAP
       :end-before: #END_MODIFY_PARAMETER_MAP

  .. tab:: R

    .. literalinclude:: ../../Examples/Elastix/ParameterMaps/ParameterMaps.R
       :language: r
       :start-after: #START_MODIFY_PARAMETER_MAP
       :end-before: #END_MODIFY_PARAMETER_MAP

Multi-Stage Registration
------------------------

Complex registration problems benefit from a coarse-to-fine approach. Use ``SetParameterMap`` for the first stage, then ``AddParameterMap`` for subsequent stages. Each stage uses the result of the previous stage as initialization. A common progression is translation → affine → B-spline:

.. tabs::

  .. tab:: C#

    .. literalinclude:: ../../Examples/Elastix/ParameterMaps/ParameterMaps.cs
       :language: csharp
       :start-after: //START_MULTI_STAGE_REGISTRATION
       :end-before: //END_MULTI_STAGE_REGISTRATION
       :dedent: 12

  .. tab:: C++

    .. literalinclude:: ../../Examples/Elastix/ParameterMaps/ParameterMaps.cxx
       :language: cpp
       :start-after: //START_MULTI_STAGE_REGISTRATION
       :end-before: //END_MULTI_STAGE_REGISTRATION
       :dedent: 2

  .. tab:: Java

    .. literalinclude:: ../../Examples/Elastix/ParameterMaps/ParameterMaps.java
       :language: java
       :start-after: //START_MULTI_STAGE_REGISTRATION
       :end-before: //END_MULTI_STAGE_REGISTRATION
       :dedent: 8

  .. tab:: Lua

    .. literalinclude:: ../../Examples/Elastix/ParameterMaps/ParameterMaps.lua
       :language: lua
       :start-after: --START_MULTI_STAGE_REGISTRATION
       :end-before: --END_MULTI_STAGE_REGISTRATION

  .. tab:: Python

    .. literalinclude:: ../../Examples/Elastix/ParameterMaps/ParameterMaps.py
       :language: python
       :start-after: #START_MULTI_STAGE_REGISTRATION
       :end-before: #END_MULTI_STAGE_REGISTRATION

  .. tab:: R

    .. literalinclude:: ../../Examples/Elastix/ParameterMaps/ParameterMaps.R
       :language: r
       :start-after: #START_MULTI_STAGE_REGISTRATION
       :end-before: #END_MULTI_STAGE_REGISTRATION

Reading and Writing Parameter Maps
-----------------------------------

Parameter maps can be saved to and loaded from elastix-format text files. This enables sharing registration configurations, reproducing results, and applying the same strategy to multiple datasets:

.. tabs::

  .. tab:: C#

    .. literalinclude:: ../../Examples/Elastix/ParameterMaps/ParameterMaps.cs
       :language: csharp
       :start-after: //START_READ_WRITE_PARAMETER_MAP
       :end-before: //END_READ_WRITE_PARAMETER_MAP
       :dedent: 12

  .. tab:: C++

    .. literalinclude:: ../../Examples/Elastix/ParameterMaps/ParameterMaps.cxx
       :language: cpp
       :start-after: //START_READ_WRITE_PARAMETER_MAP
       :end-before: //END_READ_WRITE_PARAMETER_MAP
       :dedent: 2

  .. tab:: Java

    .. literalinclude:: ../../Examples/Elastix/ParameterMaps/ParameterMaps.java
       :language: java
       :start-after: //START_READ_WRITE_PARAMETER_MAP
       :end-before: //END_READ_WRITE_PARAMETER_MAP
       :dedent: 8

  .. tab:: Lua

    .. literalinclude:: ../../Examples/Elastix/ParameterMaps/ParameterMaps.lua
       :language: lua
       :start-after: --START_READ_WRITE_PARAMETER_MAP
       :end-before: --END_READ_WRITE_PARAMETER_MAP

  .. tab:: Python

    .. literalinclude:: ../../Examples/Elastix/ParameterMaps/ParameterMaps.py
       :language: python
       :start-after: #START_READ_WRITE_PARAMETER_MAP
       :end-before: #END_READ_WRITE_PARAMETER_MAP

  .. tab:: R

    .. literalinclude:: ../../Examples/Elastix/ParameterMaps/ParameterMaps.R
       :language: r
       :start-after: #START_READ_WRITE_PARAMETER_MAP
       :end-before: #END_READ_WRITE_PARAMETER_MAP

See Also
--------

* `elastix 5.2.0 manual <https://github.com/SuperElastix/elastix/releases/download/5.2.0/elastix-5.2.0-manual.pdf>`_ — Comprehensive documentation of all elastix parameters
* `elastix model zoo <https://elastix.lumc.nl/modelzoo/>`_ — Pre-configured parameter files for various registration tasks
* :doc:`link_ElastixRegistration_docs` — Basic registration example
* `SimpleITK ElastixImageFilter API <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ElastixImageFilter.html>`_
