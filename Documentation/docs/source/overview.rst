Overview
========

SimpleITK is an image analysis toolkit with a large number of components
supporting general filtering operations, image segmentation and
registration. It is built on top of the Insight Segmentation and
Registration Toolkit `ITK`_ with the intent of providing a simplified
interface to ITK. SimpleITK itself is written in C++ but is available
for a large number of programming languages. Currently these include:

-  `Python`_
-  `R`_
-  `Java`_
-  `C#`_
-  `Lua`_
-  `TCL`_
-  `Ruby`_

Wrapping of the C++ code is accomplished through `SWIG`_, in principle,
any language wrapped by SWIG should be applicable to SimpleITK.

Unlike ITK’s support of n-dimensional spatio-temporal images, SimpleITK
supports 2D, 3D and optionally 3D+time. The dimensionality refers to
spatio-temporal dimensions, the voxels can be n-dimensional vectors.

SimpleITK is licensed under the `Apache License`_ in the `same way as
ITK`_.

.. _ITK: https://www.itk.org
.. _Python: http://www.python.org
.. _R: https://www.r-project.org
.. _Java: http://www.java.com
.. _C#: http://msdn.microsoft.com/en-us/vcsharp/default.aspx
.. _Lua: http://www.lua.org
.. _TCL: https://www.tcl.tk/
.. _Ruby: https://www.ruby-lang.org/en/
.. _SWIG: http://www.swig.org
.. _Apache License: http://www.opensource.org/licenses/apache2.0.php
.. _same way as ITK: https://www.itk.org/Wiki/ITK_Release_4/Licensing