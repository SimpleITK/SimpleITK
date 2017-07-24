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
SimpleITK must be built directly.

There are two options to obtain the SimpleITK source code:

#. Download a released version from the SimpleITK
   `SourceForge <https://sourceforge.net/projects/simpleitk/>`__ page
#. Download the latest development version using git

.. code-block :: bash

 git clone  https://itk.org/SimpleITK.git

The tar-balls provided by GitHub will result in a configuration
warning, because SimpleITK examines the repository to determine a
descriptive version.

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
versions of ITK, SWIG, Lua, and GTest (if testing is enabled) needed to
compile SimpleITK.

If you get an error message saying that ITK\_DIR is not set then, you
did not correctly point cmake to the SuperBuild sub-directory. Please
erase your binary directory, and point cmake to the SimpleITK/SuperBuild
sub-directory.

The CMake configuration process should automatically find supported
languages and enable SimpleITK wrapping for them. To manually enable a
language toggle the appropriate WRAP\_LANGUAGE cmake variable to ON.
Verify and correct the advanced cmake variables for the language
specific executable, libraries and include directories. For example if
you have multiple Python installations ensure that all related Python
variables refer to the same versions.

Then use your make utility or your cmake chosen build utility to build
SimpleITK. As the SimpleITK build process may take a while, it is
important to use the appropriate flags to enable multi-process
compilation i.e. "-j" for make, "/MP" for Visual Studio, or use the
CMake `Ninja <https://ninja-build.org>`__ generator.


Building Manually
-----------------


By not using the superbuild, you must manually specify all dependencies
used during the building of SimpleITK instead of using the known
working versions provided by the superbuild as external projects. This
may be useful if you are providing a system package of SimpleITK or tightly
integrating it into another build system. The versions of external
project used and tested by SimpleITK can be found by examining the
External CMake files in the Superbuild sub-directory.


Additional Prerequisites
^^^^^^^^^^^^^^^^^^^^^^^^

The following are dependencies when not using the SuperBuild:

#. Setup the prerequisites as described above (i.e. CMake and supported
   compiler)

#. `Insight Toolkit (ITK) <https://itk.org/>`__ the version specified in
   the External_ITK.cmake file is the version of ITK used for binary
   release. This can be seen as the minimum version of ITK to be used
   with SimpleITK, as future ITK versions are generally backwards
   compatible.

#. `Lua <https://www.lua.org/>`__ 5.1

#. `SWIG <http://www.swig.org/>`__ >= 3.0.11

#. GTest or `Google <https://github.com/google/googletest>` >= 1.0.8
   is needed if testing is enabled.


Configuration and Building
^^^^^^^^^^^^^^^^^^^^^^^^^^

After the source code is obtained, SimpleITK can be configured:

.. code-block :: bash

 mkdir SimpleITK-build
 cd SimpleITK-build
 cmake ../SimpleITK

If all the dependencies are installed in standard places, then the CMake
configuration should detect them properly. Otherwise, if there are
configuration errors, the proper CMake variable should be set.

Then SimpleITK can be built:

.. code-block :: bash

 make -j$(nproc)


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
