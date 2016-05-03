SimpleITK
=========

The goal of SimpleITK is to provide an abstraction layer to [ITK](https://www.itk.org) that enables developers and users to access the powerful features of the Insight Toolkit in a more simplified manner.  SimpleITK's goal is to provide a simple layer to ITK's complicated C++ templeted API to be easily wrap-able in several languages including:

* [Python](http://www.python.org)
* [Java](http://www.java.com)
* [C#](http://msdn.microsoft.com/en-us/vcsharp/default.aspx)
* [Lua](http://www.lua.org)

Wrapping is accomplished through [SWIG](http://www.swig.org), in principle, any language wrapped by SWIG should be applicable to SimpleITK.

SimpleITK is licensed under the [Apache License](http://www.opensource.org/licenses/apache2.0.php) in the [same way as ITK](https://www.itk.org/Wiki/ITK_Release_4/Licensing).

Development
===========

SimpleITK uses the [Git](http://git-scm.com/) distributed version control system.  The main repository is hosted on [itk.org](https://itk.org/SimpleITK.git) and mirrored to [Github](https://blowekamp@github.com/SimpleITK/SimpleITK.git).  There are two main branches, master and next. The "master" is a stable branch of the code, and suitable for most users, while "next" contains future features that are unlikely to be stable.

Documentation in maintained in [Doxygen](https://www.itk.org/SimpleITKDoxygen/html/annotated.html).  [Development instructions](https://www.itk.org/SimpleITKDoxygen/html/pages.html) are also on this site.  There is also the [Wiki](https://www.itk.org/Wiki/ITK_Release_4/SimpleITK) with additional information. SimpleITK requires a recent build of [ITK v4](https://itk.org/), but this can be automatically build along side SimpleITK with the SuperBuild cmake build.
