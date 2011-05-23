SimpleITK
=========

The goal of SimpleITK is to provide an abstraction layer to [ITK](http://www.itk.org) that enables developers and users to access the powerful features of the Insight Toolkit in a more simplified manner.  SimpleITK also is easily wrap-able in several languages including:

* [Python](http://www.python.org)
* [Java](http://www.java.com)
* [C#](http://msdn.microsoft.com/en-us/vcsharp/default.aspx)
* [Lua](http://www.lua.org)

Wrapping is accomplished through [SWIG](http://www.swig.org), in principle, any language wrapped by SWIG should be applicable to SimpleITK.

SimpleITK is licensed under the [Apache License](http://www.opensource.org/licenses/apache2.0.php) in the [same way as ITK](http://www.itk.org/Wiki/ITK_Release_4/Licensing).

Development
===========

SimpleITK uses the [Git](http://git-scm.com/) distributed version control system.  The main repository is hosted on [GitHub](https://github.com/SimpleITK/SimpleITK).  There are two main branches, master and next.  "master" is a stable branch of the code, and suitable for most users, while "next" contains future features that are unlikely to be stable.

Documentation in maintained in [Doxygen](http://erie.nlm.nih.gov/~blowek1/SimpleITK/annotated.html).  [Development instructions](http://erie.nlm.nih.gov/~blowek1/SimpleITK/pages.html) are also on this site.  SimpleITK requires a recent build of [ITK v4](http://itk.org/), which may be found on [GitHub](https://github.com/Kitware/ITK).

ToDo:

+ Registration
+ CastImageFilter
+ Multiple input filters
+ Simple arithmetic filters
