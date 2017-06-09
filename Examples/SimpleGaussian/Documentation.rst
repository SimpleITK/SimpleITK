Simple Gaussian
===============


Overview
--------

Introductory example which demotrates the basics of reading, filtering,
and writing an image. This examples works for any scalar or vector
image type. It processes the image with a Gaussian blurring filter,
which produces an image with floating point pixel type, then cast the
output back to the input before writing the image to a file.

This example uses the object oriented (OO) interface to SimpleITK
classes. The OO style produces more verbose code which clearly labels the
parameters set by class member functions.


Code
----

C++
...

.. literalinclude:: SimpleGaussian.cxx
   :language: c++
   :lines: 18-

Python
......

.. literalinclude:: SimpleGaussian.py
   :language: python
   :lines: 1,19-

CSharp
......

.. literalinclude:: SimpleGaussian.cs
   :language: c#
   :lines: 18-

Java
....

.. literalinclude:: SimpleGaussian.java
   :language: java
   :lines: 18-

Lua
...

.. literalinclude:: SimpleGaussian.lua
   :language: lua
   :lines:  18-

R
.

.. literalinclude:: SimpleGaussian.R
   :language: r
   :lines:  18-

Ruby
....

.. literalinclude:: SimpleGaussian.rb
   :language: ruby
   :lines:  18-

Tcl
...

.. literalinclude:: SimpleGaussian.tcl
   :language: tcl
   :lines: 18-
