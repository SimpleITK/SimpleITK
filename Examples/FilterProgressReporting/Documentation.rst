Filter Progress Reporting
=========================


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

.. literalinclude:: FilterProgressReporting.cxx
   :language: c++
   :lines: 18-

Python
......

.. literalinclude:: FilterProgressReporting.py
   :language: python
   :lines: 1,19-

CSharp
......

.. literalinclude:: FilterProgressReporting.cs
   :language: c#
   :lines: 18-

Java
....

.. literalinclude:: FilterProgressReporting.java
   :language: java
   :lines: 18-

R
.

.. literalinclude:: FilterProgressReporting.R
   :language: r
   :lines:  18-

Ruby
....

.. literalinclude:: FilterProgressReporting.rb
   :language: ruby
   :lines:  18-
