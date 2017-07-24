Building SimpleITK
******************


In many cases a user does not need to build SimpleITK because of the
pre-built binaries available (see :ref:`Downloading the binaries
<installation-binaries>`). However there are several reasons a user
might prefer to **build SimpleITK from source**:

-  The binary files for your programming language of choice are not
   (yet) distributed
-  You want the live on the bleeding edge by using the
   latest-and-greatest version of SimpleITK
-  You want to wrap your own filters using the SimpleITK infrastructure
-  You want to contribute to the development of SimpleITK
-  To use the SimpleITK's C++ interface and/or use ITK directly

.. contents:: On this page
    :local:
    :backlinks: none


Prerequisites
=============

To build SimpleITK you need:

-  A recent version of `CMake <http://www.cmake.org/>`__ >= 3.3 with SSL
   support for https.
-  A supported :ref:`compiler <FAQ-compiler-supported>`.
-  To use the latest developmental version, source code can be
   downloaded with `git <http://git-scm.com/>`__ >= 1.65

   -  Git is required if building SimpleITK using "SuperBuild" (see
      below) to automatically download the matching version of ITK,
      SWIG, etc...
   -  Windows users may prefer `msysGit <http://msysgit.github.com/>`__

-  It is recommended to have numpy installed when testing Python
   bindings


Recipes / Formulas / Short Cuts
===============================

For some environments we have short cuts, scripts, for automated
building of SimpleITK (see their repository for more details):

-  For **Python**: The
   `scikit-build <https://github.com/scikit-build/scikit-build>`__ based
   distutils based `setup.py
   frontend <https://github.com/SimpleITK/SimpleITKPythonPackage>`__ can be
   used to build, install, and package SimpleITK for Python.

-  For the **Anaconda Python** distribution: The recipe and instructions
   for the SimpleITK build are in `this GitHub
   repository <https://github.com/SimpleITK/SimpleITKCondaRecipe>`__.

-  For the **R language**: A devtools installer and instructions are
   available from `this GitHub
   repository <https://github.com/SimpleITK/SimpleITKRInstaller>`__.

-  **On the Mac**, with the `Homebrew package
   manager <http://brew.sh/>`__, a SimpleITK formula is available:
   https://github.com/Homebrew/homebrew-science/blob/master/simpleitk.rb
   for multiple language wrappings.

-  For the **Lua language** with the Luarocks module deployment system,
   a SimpleITK rockspec is available form `this GitHub
   repository <https://github.com/SimpleITK/SimpleITKLuaRock>`__.


Source code
===========

If one of the above language specific front-ends are not used then
SimpleITK must be build directly.

There are two options to obtain the SimpleITK source code:

#. Download a released version from the SimpleITK
   `SourceForge <https://sourceforge.net/projects/simpleitk/>`__ page
#. Download the latest development version using git

.. code-block :: bash

 git clone  https://itk.org/SimpleITK.git


Building using SuperBuild
-------------------------

After downloading SimpleITK's source code we **STRONGLY** recommend to
run cmake on the SuperBuild subdirectory of SimpleITK. Execute the
following commands in the parent of the SimpleITK source directory to
configure the SuperBuild:

.. code-block :: bash

 mkdir SimpleITK-build
 cd SimpleITK-build
 cmake ../SimpleITK/SuperBuild

The SuperBuild will automatically download and build the matching
version of ITK and SWIG needed to compile SimpleITK. Additionally, it
will set recommended compilation flags to minimize the size of the
library and enable support for large libraries. This is the recommended
way to build SimpleITK and is easiest.

If you get an error message saying that ITK\_DIR is not set then, you
did not correctly point cmake to the SuperBuild sub-directory. Please
erase your binary directory, and point cmake to the SimpleITK/SuperBuild
sub-directory.

The cmake configuration process should automatically find supported
languages and enable SimpleITK wrapping for them. To manually enable a
language toggle the appropriate WRAP\_LANGUAGE cmake variable to ON.
Verify and/or correct the advanced cmake variables to the language
specific executable, libraries and include directories. For example if
you have multiple Python installations ensure that all related Python
variable refer to the same versions.

Then use your make utility or your cmake chosen build utility to build
SimpleITK.

SimpleITK takes a while to build. Some tips and tricks to speed up
development time are listed
`here <http://www.itk.org/SimpleITKDoxygen/html/Developer.html#TandT>`__.


Building Manually
-----------------

This is **not** the recommended way of building SimpleITK, but it can be
useful if you want to use a system version of ITK, etc. , or if you do
not want to (or can not) use git.

#. Setup the prerequisites as described above (i.e. CMake and supported
   compiler)
#. Install the matching version of `SWIG <http://www.swig.org/>`__ >=
   3.0.11

   -  e.g. Windows users may install
      `swigwin-3.0.11 <http://prdownloads.sourceforge.net/swig/swigwin-3.0.11.zip>`__

#. Download the SimpleITK source code from the
   `SourceForge <https://sourceforge.net/projects/simpleitk/files/SimpleITK/>`__
   page
#. Download the matching version of ITK, found by examining the
   \`SuperBuild/External\_ITK.cmake\` file.
#. Configure ITK using CMake

   -  e.g. BUILD\_EXAMPLES=OFF, BUILD\_TESTING=OFF,
      BUILD\_SHARED\_LIBS=OFF, **ITK\_USE\_REVIEW=ON**

#. Build ITK

   -  Be sure to note the build settings e.g. Release x64

#. Configure SimpleITK using CMake

   -  Set ITK\_DIR to the location of the ITK build location from the
      previous steps

#. Build SimpleITK

   -  Be sure to configure the build settings exactly the same as ITK
      e.g. Release x64 and CXX\_FLAGS


Advanced Build Options
----------------------

SimpleITK is aware of the enabled and disabled ITK Modules. It is
possible to customize SimpleITK by disabling unneeded ITK modules or to
extend SimpleITK by writing custom json file dependent an ITK Remote
Modules being enabled.

Additionally, each of the Examples directory, and each of the Wrapping
subdirectories can be configured as independent CMake project dependent
on an installed SimpleITK.


Testing
-------

After compilation the prudent thing to due is to test SimpleITK to
ensure your build is stable and suitable for installation and use. The
following commands execute the SimpleITK tests.

.. code-block :: bash

 cd SimpleITK-build/SimpleITK-build
 ctest .

On Windows you will need to specify configuration. Typically that would
be the Release configuration, as such:

.. code-block :: bash

 cd SimpleITK-build/SimpleITK-build
 ctest -C Release


Installation from Build Tree
----------------------------


Python Installation
^^^^^^^^^^^^^^^^^^^

To install a built python package into the system Python, as root run:

.. code-block :: bash

 cd SimpleITK-build/Wrapping/Python
 python Packaging/setup.py install

Alternatively, a Python virtual environment can be created and the
distribution installed there.

A Python Wheel file (.whl) can be created in the "Wrapping/Python/dist"
directory, by building the "dist" target. If you have used the
Superbuild with the "make" generator then issue the following command:

.. code-block :: bash

 make -C SimpleITK-build dist


R Installation
^^^^^^^^^^^^^^

To install a built R package:

.. code-block :: bash

 cd SimpleITK-build/Wrapping/R/Packaging
 R CMD INSTALL SimpleITK

This will install the R package "SimpleITK" in /usr/local as root or
your local R installation directory.

If you are working in a multi-user environment, and are considerate of
your fellow users you can install the package in a local directory:

#. Create a local directory where you will install your R packages

.. code-block :: bash

 mkdir my_R_libs

2. Add an environment variable to your .bashrc

.. code-block :: bash

 export R_LIBS="/path_to/my_R_libs"

3. source your .bashrc and check the R library path, in an R shell

.. code-block :: R

   .libPaths()

4. install

.. code-block :: bash

 cd SimpleITK-build/Wrapping/R/Packaging
 R CMD INSTALL -l /path_to/my_R_libs SimpleITK
