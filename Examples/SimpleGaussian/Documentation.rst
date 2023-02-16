Reading-Gaussian Blurring-Writing
=================================


Overview
--------

Introductory example which demonstrates the basics of reading, filtering,
and writing an image. This examples works for any scalar or vector
image type. It processes the image with a Gaussian blurring filter,
which produces an image with floating point pixel type, then cast the
output back to the input before writing the image to a file.

This example uses the object oriented (OO) interface to SimpleITK
classes. The OO style produces more verbose code which clearly labels the
parameters set by class member functions.


Example Run
-----------

Running the Python code as follows:

``main('docs/images/BrainProtonDensitySlice.png', 2.0, 'output.png')``

modifies the input image to the output image below.

.. exec_code::
    :hide_output:

    # --- hide: start ---
    from example_utils import run_example, save_image
    args = ['../../docs/images/BrainProtonDensitySlice.png',
            2.0,
            '/tmp/gaussian_out.png',
            ]
    return_dict = run_example('SimpleGaussian', 'main', args)
    for key, value in return_dict.items():
        save_image(value, f"SimpleGaussian_{key}")

    # --- hide: stop ---

Input/Output Images
^^^^^^^^^^^^^^^^^^^

.. figure:: ../images/SimpleGaussian_input_image.png
   :scale: 100%

   **Input Image**

.. figure:: ../images/SimpleGaussian_blur_image.png
   :scale: 100%

   **Output Image**



Code
----

.. tabs::

  .. tab:: C#

    .. literalinclude:: ../../Examples/SimpleGaussian/SimpleGaussian.cs
       :language: c#
       :lines: 18-

  .. tab:: C++

    .. literalinclude:: ../../Examples/SimpleGaussian/SimpleGaussian.cxx
       :language: c++
       :lines: 18-

  .. tab:: Java

    .. literalinclude:: ../../Examples/SimpleGaussian/SimpleGaussian.java
       :language: java
       :lines: 18-

  .. tab:: Lua

    .. literalinclude:: ../../Examples/SimpleGaussian/SimpleGaussian.lua
       :language: lua
       :lines:  18-

  .. tab:: Python

    .. literalinclude:: ../../Examples/SimpleGaussian/SimpleGaussian.py
       :language: python
       :lines: 1,22-53

  .. tab:: R

    .. literalinclude:: ../../Examples/SimpleGaussian/SimpleGaussian.R
       :language: r
       :lines:  18-

  .. tab:: Ruby

    .. literalinclude:: ../../Examples/SimpleGaussian/SimpleGaussian.rb
       :language: ruby
       :lines:  18-

  .. tab:: Tcl

    .. literalinclude:: ../../Examples/SimpleGaussian/SimpleGaussian.tcl
       :language: tcl
       :lines: 18-
