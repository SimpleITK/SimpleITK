SimpleITK
=========

[![CircleCI](https://img.shields.io/circleci/project/SimpleITK/SimpleITK/master.svg?maxAge=2592000?style=flat-square)](https://circleci.com/gh/SimpleITK/SimpleITK/tree/master)

SimpleITK is an image analysis toolkit with a large number of components supporting general filtering operations, image segmentation and registration. It is built on top of the Insight Segmentation and Registration Toolkit [ITK](https://www.itk.org) with the intent of providing a simplified interface to ITK. SimpleITK itself is written in C++ but is available for a large number of programming languages. Currently these include:

* [Python](http://www.python.org)
* [R](https://www.r-project.org)
* [Java](http://www.java.com)
* [C#](http://msdn.microsoft.com/en-us/vcsharp/default.aspx)
* [Lua](http://www.lua.org)
* [TCL](https://www.tcl.tk/)
* [Ruby](https://www.ruby-lang.org/en/)


Wrapping of the C++ code is accomplished through [SWIG](http://www.swig.org), in principle, any language wrapped by SWIG should be applicable to SimpleITK.

Unlike ITK's support of n-dimensional spatio-temporal images, SimpleITK supports 2D, 3D and optionally 3D+time. The dimensionality refers to spatio-temporal dimensions, the voxels can be n-dimensional vectors.

SimpleITK is licensed under the [Apache License](http://www.opensource.org/licenses/apache2.0.php) in the [same way as ITK](https://www.itk.org/Wiki/ITK_Release_4/Licensing).

Development
===========

SimpleITK uses the [Git](http://git-scm.com/) distributed version control system.  The main repository is hosted on [itk.org](https://itk.org/SimpleITK.git) and mirrored to [Github](https://blowekamp@github.com/SimpleITK/SimpleITK.git).  There are two main branches, master and next. The "master" is a stable branch of the code, and suitable for most users, while "next" contains future features that are unlikely to be stable.

The SimpleITK [Wiki](https://itk.org/Wiki/SimpleITK) is the main site for all things SimpleITK. The site includes information on installing the toolkit's binary distributions, building the toolkit, user support documentation and much more. The API documentation is maintained using [Doxygen](https://www.itk.org/SimpleITKDoxygen/html/annotated.html).

SimpleITK provides access to most of the ITK components, but not all. If you are looking for something specific and can't find it, ask for support on the [mailing list](https://itk.org/mailman/listinfo/community) (you will need to subscribe to the mailing list before you post).
