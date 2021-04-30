.. _building_simpleitk:

Building SimpleITK
******************

Pre-built binaries (see :ref:`Downloading the binaries
<installation-binaries>`) are available in many cases so
users do not need to build SimpleITK. However, there are
several reasons a user might prefer to **build SimpleITK from source code**:

-  The binary files for your programming language of choice are not
   (yet) distributed
-  You want the live on the bleeding edge by using the
   latest-and-greatest version of SimpleITK
-  You want to wrap your own filters using the SimpleITK infrastructure
-  You want to contribute to the development of SimpleITK
-  To use the SimpleITK's C++ interface and/or use ITK directly

..
  .. contents:: On this page
      :local:
      :backlinks: none

Prerequisites
=============

To build SimpleITK you need:

-  A recent version of `CMake <http://www.cmake.org/>`__ >= 3.10 with SSL
   support for https.
-  A supported :ref:`compiler <FAQ-compiler-supported>`.
-  To use the latest developmental version, source code can be
   downloaded with `git <http://git-scm.com/>`__ >= 1.65

   -  Git is required if building SimpleITK using :ref:`SuperBuild <building_superbuild>`
      to automatically download the matching version of ITK,
      SWIG, etc...
   -  Windows users may prefer `msysGit <http://msysgit.github.com/>`__

-  The Python interface requires Python version 3.5 or greater.

-  It is recommended to have numpy installed when testing Python
   bindings.

-  The R interface requires R version 3.3 or greater.

Recipes / Formulas / Short cuts
===============================

Before you start please make sure you have the required `Prerequisites`_ installed.

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

-  For the **R language** (version 3.3 or greater): A devtools installer and instructions are
   available from `this GitHub
   repository <https://github.com/SimpleITK/SimpleITKRInstaller>`__.

-  For the **Lua language** with the Luarocks module deployment system,
   a SimpleITK rockspec is available at the `Luarocks repository <https://luarocks.org/modules/dave3d/simpleitk>`__
   or from `this GitHub repository <https://github.com/SimpleITK/SimpleITKLuaRock>`__.

.. _source_code:

Source code
===========

If one of the above language specific front-ends are not used then
SimpleITK must be built directly.

Before you start please make sure you have the required `Prerequisites`_ installed.

All of the instructions assume you are working on the command line.

Words of caution for building on the Windows operating system:

* Windows has issues with long directory paths. We recommend cloning the
  source code near the root (e.g. C:\\src).
* To avoid potential issues do not clone the source into a path which has spaces
  in the directory name (e.g. C:\\Users\\SimpleITK Source).

First obtain the SimpleITK source code:

#. Download the latest development version using git

.. code-block :: bash

 git clone https://github.com/SimpleITK/SimpleITK.git


.. _building_superbuild:

Building using SuperBuild
-------------------------

After downloading SimpleITK's source code we **STRONGLY** recommend
running cmake on the SuperBuild subdirectory of SimpleITK. Execute the
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

For **building SimpleITK on Windows** using the CMake GUI see:

.. toctree::
  buildingWindows.rst

Building Manually
-----------------

By not using the superbuild, you must manually specify all dependencies
used during the building of SimpleITK instead of using the known
working versions provided by the superbuild as external projects. This
may be useful if you are providing a system package of SimpleITK or tightly
integrating it into another build system. The versions of external
projects used and tested by SimpleITK can be found by examining the
External CMake files in the Superbuild sub-directory.


Additional Prerequisites
^^^^^^^^^^^^^^^^^^^^^^^^

The following are dependencies you will need when not using the SuperBuild:

#. Setup the prerequisites as described above (i.e. CMake and supported
   compiler)

#. `Insight Toolkit (ITK) <https://itk.org/>`__ the version specified in
   the External_ITK.cmake file is the version of ITK used for the binary
   release. This can be seen as the minimum version of ITK to be used
   with SimpleITK, as future ITK versions are generally backwards
   compatible.

#. `Lua <https://www.lua.org/>`__ 5.3.5

#. `SWIG <http://www.swig.org/>`__ >= 4.0

#. GTest or `Google Test <https://github.com/google/googletest>`__ >= 1.10
   is needed if testing is enabled.


Configuration and Building
^^^^^^^^^^^^^^^^^^^^^^^^^^

After the source code is obtained, SimpleITK can be configured on
Unix-like systems like so:

.. code-block :: bash

 mkdir SimpleITK-build
 cd SimpleITK-build
 cmake ../SimpleITK

If all the dependencies are installed in standard places, then the CMake
configuration should detect them properly. Otherwise, if there are
configuration errors, the proper CMake variable should be set. CMake
variables can be either set with a CMake interactive GUI such as
`ccmake` or `cmake-qt`, as arguments on the command line by using
the following format: `-D<var>=<value>`, or by editing the CMakeCache.txt
file.

After proper configuration, SimpleITK can be built:

.. code-block :: bash

 make -j$(nproc)


Advanced Build Options
----------------------

SimpleITK is aware of the modularity of ITK and automatically enables
and disables filters based on which modules are available from the ITK
build which SimpleITK is compiled against. This makes it possible to
customize SimpleITK to be a small library or to wrap additional ITK
remote modules simply by configuring ITK with the desired modules
enabled.

For example, the CoherenceEnhancingDiffusionImageFilter is an optional
filter in SimpleITK as it's part of the ITK remote module
AnisotropicDiffusionLBR. This remote module is not enabled by default
when building ITK and SimpleITK. To enable it when using SimpleITK's
Superbuild add `-DModule_AnisotropicDiffusionLBR:BOOL=ON` to the
command line or in the CMake GUI press the "Add Entry" button to
define the variable as above.

SimpleITK has a very flexible and robust build system utilizing
CMake. It enables packagers to build SimpleITK in a variety of ways to
suit their requirements and minimize recompilation of SimpleITK so
that it can be wrapped for many different languages. Each of the
language wrapping sub-directories e.g. "Wrapping/Python" can be
configured and built as an independent project which is dependent on
SimpleITK as an installed package of its libraries and header filers.


Testing
-------

After compilation the prudent thing to do is to test SimpleITK to
ensure that the build is stable and suitable for installation and use. To enable
testing the cmake `BUILD_TESTING` variable must be enabled during the build process.
Then the following commands execute the SimpleITK tests.

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

.. _python_installation:

Python Installation
^^^^^^^^^^^^^^^^^^^

To install a built python package into the system Python, as root run:

.. code-block :: bash

 cd SimpleITK-build/Wrapping/Python
 python setup.py install

Preferably, a Python virtual environment is created and the
distribution installed there.

A Python Wheel file (.whl) is built by the "dist" target and produced in the
"Wrapping/Python/dist" directory. If you use the
Superbuild with the "make" generator then issue the following command:

.. code-block :: bash

 make -C SimpleITK-build dist


R Installation
^^^^^^^^^^^^^^

To install a built R package:

.. code-block :: bash

 cd SimpleITK-build/Wrapping/R/Packaging
 R CMD INSTALL SimpleITK

This installs the R package "SimpleITK" in /usr/local as root or
your local R installation directory.

If you work in a multi-user environment, and are considerate of
your fellow users you can install the package in a local directory:

#. Create a local directory to install your R packages

.. code-block :: bash

 mkdir my_R_libs

2. In your home directory create a file named .Renviron with the following line

.. code-block :: bash

  R_LIBS_USER="/path_to/my_R_libs"

3. Check that the R library paths include this directory, in an R shell or from RStudio:

.. code-block :: R

   .libPaths()

4. install

.. code-block :: bash

 cd SimpleITK-build/Wrapping/R/Packaging
 R CMD INSTALL -l /path_to/my_R_libs SimpleITK
