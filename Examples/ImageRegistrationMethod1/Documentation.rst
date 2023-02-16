Image Registration Method 1
===========================

Overview
--------

.. include:: registrationExamplePrefix.rst

Example Run
-----------

Running the Python code with the following inputs:

``main('BrainProtonDensitySliceBorder20.png', 'BrainProtonDensitySliceShifted13x17y.png', 'displaceMeth1.hdf5')``

produces the text and images below.

Output Text
^^^^^^^^^^^

.. collapse:: Text Output (click triangle to collapse)
    :open:

    .. exec_code::

        # --- hide: start ---
        from example_utils import run_example, save_image
        args = ['../images/BrainProtonDensitySliceBorder20.png',
                '../images/BrainProtonDensitySliceShifted13x17y.png',
                'displaceMeth1.hdf5',
               ]
        return_dict = run_example('ImageRegistrationMethod1', 'main', args)
        for key, value in return_dict.items():
            save_image(value, f"ImageRegistrationMethod1_{key}")
        # --- hide: stop ---


Input Images
^^^^^^^^^^^^

.. list-table::

    * - .. figure:: ../images/ImageRegistrationMethod1_fixed.png
           :scale: 100%

        **Fixed Image**

      - .. figure:: ../images/ImageRegistrationMethod1_moving.png
           :scale: 100%

        **Moving Image**

Output Image
^^^^^^^^^^^^

.. figure:: ../images/ImageRegistrationMethod1_composition.png
   :scale: 100%

   **Composition Image**

Code
----

.. tabs::

  .. tab:: C#

    .. literalinclude:: ../../Examples/ImageRegistrationMethod1/ImageRegistrationMethod1.cs
       :language: c#
       :lines: 18-

  .. tab:: C++

    .. literalinclude:: ../../Examples/ImageRegistrationMethod1/ImageRegistrationMethod1.cxx
       :language: c++
       :lines: 18-

  .. tab:: Java

    .. literalinclude:: ../../Examples/ImageRegistrationMethod1/ImageRegistrationMethod1.java
       :language: java
       :lines: 18-

  .. tab:: Lua

    .. literalinclude:: ../../Examples/ImageRegistrationMethod1/ImageRegistrationMethod1.lua
       :language: lua
       :lines:  18-

  .. tab:: Python

    .. literalinclude:: ../../Examples/ImageRegistrationMethod1/ImageRegistrationMethod1.py
       :language: python
       :lines: 1,19-80

  .. tab:: R

    .. literalinclude:: ../../Examples/ImageRegistrationMethod1/ImageRegistrationMethod1.R
       :language: r
       :lines:  18-
