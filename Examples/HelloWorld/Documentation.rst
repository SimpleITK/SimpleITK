Hello World
===========


Overview
--------

A "Hello World" example for SimpleITK. The example constructs a 128x128 greyscale
image, draws a smiley face made of Gaussian blobs, and calls the Show function to
display the image with Fiji.


Sample Output
-------------

Running the python code produces this image:


.. exec_code::
    :hide_output:

    # --- hide: start ---
    from example_utils import run_example, save_image
    args = []
    return_dict = run_example('HelloWorld', 'main', args)
    save_image(return_dict["output_image"], f"HelloWorld_output_image")
    # --- hide: stop ---


.. figure:: ../images/HelloWorld_output_image.png
   :scale: 100%

   **Input Image**

Code
----

.. tabs::
  .. tab:: C#

    .. literalinclude:: ../../Examples/HelloWorld/HelloWorld.cs
       :language: c#
       :lines: 18-

  .. tab:: C++

    .. literalinclude:: ../../Examples/HelloWorld/HelloWorld.cxx
       :language: c++
       :lines: 18-

  .. tab:: Java

    .. literalinclude:: ../../Examples/HelloWorld/HelloWorld.java
       :language: java
       :lines: 18-

  .. tab:: Lua

    .. literalinclude:: ../../Examples/HelloWorld/HelloWorld.lua
       :language: lua
       :lines:  18-

  .. tab:: Python

    .. literalinclude:: ../../Examples/HelloWorld/HelloWorld.py
       :language: python
       :lines: 20-64

  .. tab:: R

    .. literalinclude:: ../../Examples/HelloWorld/HelloWorld.R
       :language: r
       :lines:  19-

  .. tab:: Ruby

    .. literalinclude:: ../../Examples/HelloWorld/HelloWorld.rb
       :language: ruby
       :lines:  18-

  .. tab:: Tcl

    .. literalinclude:: ../../Examples/HelloWorld/HelloWorld.tcl
       :language: tcl
       :lines: 18-
