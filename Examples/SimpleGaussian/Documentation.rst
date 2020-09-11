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
       :lines: 1,19-

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
