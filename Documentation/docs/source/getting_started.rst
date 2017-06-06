Getting Started
***************

SimpleITK provides a simplified interface to ITK in a variety of
languages. You can either download binaries, if they are available for
your platform and prefered language, or you can build SimpleITK
yourself.

Additionally, there are several recommended third-party software
packages.

After you have installed SimpleITK, please look to the
`Tutorial <ITK_Release_4/Outreach/Conferences/MICCAI 2011/SimpleITK>`__
or the `Doxygen <http://www.itk.org/SimpleITKDoxygen/html/>`__ pages for
more information.

.. contents:: On this page
    :local:
    :backlinks: none

Downloading the binaries
========================

One of the great advantages of SimpleITK is that (typically) you do not
have to build it — you can simply download the binaries and get started
right away!

Currently, **Python** binaries are available on Microsoft Windows, GNU
Linux and Apple OS X. **C# and Java** binaries are available for
Windows. We are also working towards supporting **R** packaging.

Python binary files
-------------------

There are currently two Python binary package choices: Python Wheels,
and Anaconda packages for the Anaconda Python distribution.

Use a Virtual Environment
^^^^^^^^^^^^^^^^^^^^^^^^^

Before you install SimpleITK we highly recommend that you create a
virtual environment into which you install the package. Note that
different Python versions and distributions have different programs for
creating and managing virtual environments.

The use of a virtual environment allows you to elegantly deal with
package compatability issues, to quote `The Hitchhiker’s Guide to
Python! <http://docs.python-guide.org/en/latest/>`__:

    A Virtual Environment is a tool to keep the dependencies required by
    different projects in separate places, by creating virtual Python
    environments for them. It solves the “Project X depends on version
    1.x but, Project Y needs 4.x” dilemma, and keeps your global
    site-packages directory clean and manageable.

Programs for creating virtual environments include `virtualenv and
pyvenv <https://packaging.python.org/en/latest/installing/#creating-virtual-environments>`__
for generic Python distributions,
`conda <http://conda.pydata.org/docs/using/envs.html>`__ for the
anaconda distribution, and
`canopy\_cli <http://docs.enthought.com/canopy/configure/canopy-cli.html>`__
for the canopy distribution.

Wheels for Generic Python Distribution
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If you are working with the `generic Python
distribution <https://www.python.org/>`__ you can install a Wheel with
the lasted version of pip (>=9.0).

First thing you should do is create a virtual environment (virtualenv or
pyvenv tools) and activate it.

Note: you can always manually download the wheels for your operating
system and Python version directly from
`sourceforge <http://sourceforge.net/projects/simpleitk/files/SimpleITK/>`__.

From the command line use the `pip
program <https://pip.pypa.io/en/latest/index.html>`__ to install:

``$ pip install SimpleITK``

The pip package manager should automatically find the correct package
for Microsoft Windows, Apple OS X and GNU Linux if your version and
architecture are supported. If no binary package is found, then a source
distribution will be downloaded and attempted to be compiled and you
should look into `#Build\_It\_Yourself <#Build_It_Yourself>`__.

        If your pip version in the virtual environment is stale (<9.0)
        you need to update it (pip install -U pip).

Anaconda Distribution
~~~~~~~~~~~~~~~~~~~~~

First thing you should do is create a virtual environment
(`conda <https://conda.pydata.org/docs/using/envs.html>`__ tool) and
activate it.

Currently there are compiled binaries on `Anaconda
Cloud <https://conda.anaconda.org/simpleitk>`__, easily installed with:

``$ conda install -c https://conda.anaconda.org/simpleitk SimpleITK``

Beta and release candidate packages are also available on Anaconda cloud
under the dev label:

``$conda install -c https://conda.anaconda.org/simpleitk/label/dev SimpleITK``

Enthought Canopy Distribution
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

First thing you should do is create a virtual environment (canopy\_cli
tool) and activate it.

Currently there are no binaries supported with this distribution. You
will need to compile SimpleITK yourself. (Using pip installation may
work.)

C# binary files
---------------

**Binaries for select C# platform** can be found on `SimpleITK's
SourceForge
page <https://sourceforge.net/projects/simpleitk/files/SimpleITK/1.0.0/CSharp/>`__.
Installing the library should only involve importing the unzipped files
into you C# environment. The files have the following naming convention:

``SimpleITK-version-CSharp-buildplatform-targetplatform.zip``

eg.

| ``SimpleITK-1.0.0-CSharp-win32-x86.zip``
| ``SimpleITK-1.0.0-CSharp-win64-x64.zip``

Details about how to set up a C# Visual Studio project with SimpleITK
can be found in the `Visual Guide to SimpleITK with
CSharp <SimpleITK/GettingStarted/A_visual_guide_to_SimpleITK_with_CSharp>`__.

More information about getting started with a sample C# program can be
found in `A visual guide to building SimpleITK on
Linux <SimpleITK/GettingStarted/Visual_guide_to_building_on_Linux#A_simple_C.23_program>`__

Java binary files
-----------------

**Binaries for select Java platforms** can be found on `SimpleITK's
SourceForge
page <https://sourceforge.net/projects/simpleitk/files/SimpleITK/1.0.0/Java/>`__.
Installation instructions are available at `a visual guide to SimpleITK
in
Java <SimpleITK/GettingStarted/A visual guide to SimpleITK in Java>`__.

Nightly binaries
----------------

The **latest binaries** for the current development version of SimpleITK
are also generally available. Binary packages are built as part of the
nightly regression testing system. The download links are available from
the `**CDash** <https://open.cdash.org/index.php?project=SimpleITK>`__
**dashboard** in the "Nightly Packages" section.

Each row on the dashboard is a SimpleITK build on a particular system,
and if the build was successful there will be a **package icon**:
https://open.cdash.org/img/package.png which links to the packages build
by the system. A user may directly download the built package from such
a link.

Build It Yourself
=================

In many cases a user does not need to build SimpleITK because of the
pre-built binaries available (see
`above <SimpleITK/GettingStarted#Binaries>`__). However there are
several reasons a user might prefer to **build SimpleITK from source**:

-  The binary files for your programming language of choice are not
   (yet) distributed
-  You want the live on the bleeding edge by using the
   latest-and-greatest version of SimpleITK
-  You want to wrap your own filters using the SimpleITK infrastructure
-  You want to contribute to the development of SimpleITK
-  To use the SimpleITK's C++ interface and/or use ITK directly

Prerequisites
~~~~~~~~~~~~~

To build SimpleITK you need:

-  A recent version of `CMake <http://www.cmake.org/>`__ >= 3.3 with SSL
   support for https.
-  A supported `compiler <SimpleITK/FAQ#Is_my_compiler_supported.3F>`__
-  To use the latest developmental version, source code can be
   downloaded with `git <http://git-scm.com/>`__ >= 1.65

   -  Git is required if building SimpleITK using "SuperBuild" (see
      below) to automatically download the matching version of ITK,
      SWIG, etc...
   -  Windows users may prefer `msysGit <http://msysgit.github.com/>`__

-  It is recommended to have numpy installed when testing Python
   bindings

Recipes / Formulas / Short Cuts
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

For some environments we have short cuts, scripts, for automated
building of SimpleITK (see their repository for more details):

-  For **Python**: The
   `scikit-build <https://github.com/scikit-build/scikit-build>`__ based
   distutils based `setup.py
   frontend <https://github.com/scikit-build/scikit-build>`__ can be
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
~~~~~~~~~~~

If one of the above language specific front-ends are not used then
SimpleITK must be build directly.

There are two options to obtain the SimpleITK source code:

#. Download a released version from the SimpleITK
   `SourceForge <https://sourceforge.net/projects/simpleitk/>`__ page
#. Download the latest development version using git

``git clone ``\ ```http://itk.org/SimpleITK.git`` <http://itk.org/SimpleITK.git>`__

Building using SuperBuild
~~~~~~~~~~~~~~~~~~~~~~~~~

After downloading SimpleITK's source code we **STRONGLY** recommend to
run cmake on the SuperBuild subdirectory of SimpleITK. Execute the
following commands in the parent of the SimpleITK source directory to
configure the SuperBuild:

| ``mkdir SimpleITK-build``
| ``cd SimpleITK-build``
| ``cmake ../SimpleITK/SuperBuild``

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
~~~~~~~~~~~~~~~~~

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
~~~~~~~~~~~~~~~~~~~~~~

SimpleITK is aware of the enabled and disabled ITK Modules. It is
possible to customize SimpleITK by disabling unneeded ITK modules or to
extend SimpleITK by writing custom json file dependent an ITK Remote
Modules being enabled.

Additionally, each of the Examples directory, and each of the Wrapping
subdirectories can be configured as independent CMake project dependent
on an installed SimpleITK.

`A visual guide to building SimpleITK on Linux <SimpleITK/GettingStarted/Visual_guide_to_building_on_Linux>`__
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Testing
-------

After compilation the prudent thing to due is to test SimpleITK to
ensure your build is stable and suitable for installation and use. The
following commands execute the SimpleITK tests.

| ``cd SimpleITK-build/SimpleITK-build``
| ``ctest``

On Windows you will need to specify configuration. Typically that would
be the Release configuration, as such:

| ``cd SimpleITK-build/SimpleITK-build``
| ``ctest -C Release``

Python installation
-------------------

To install a built python package into the system Python, as root run:

| `` cd SimpleITK-build/Wrapping/Python``
| `` python Packaging/setup.py install``

Alternatively, a Python virtual environment can be created and the
distribution installed there.

A Python Wheel file (.whl) can be created in the "Wrapping/Python/dist"
directory, by building the "dist" target. If you have used the
Superbuild with the "make" generator then issue the following command:

`` make -C SimpleITK-build dist``

R installation
--------------

To install a built R package:

| `` cd SimpleITK-build/Wrapping/R/Packaging``
| `` R CMD INSTALL SimpleITK``

This will install the R package "SimpleITK" in /usr/local as root or
your local R installation directory.

If you are working in a multi-user environment, and are considerate of
your fellow users you can install the package in a local directory:

#. Create a local directory where you will install your R packages

`` mkdir my_R_libs``

2. Add an environment variable to your .bashrc

`` export R_LIBS="/path_to/my_R_libs"``

3. source your .bashrc and check the R library path, in an R shell
   >.libPaths()

4. install

| `` cd SimpleITK-build/Wrapping/R/Packaging``
| `` R CMD INSTALL -l /path_to/my_R_libs  SimpleITK``

Recommended Software
====================

Fiji (Fiji is Just ImageJ)
--------------------------

SimpleITK has a built in function,
`**"itk::simple::Show()"** <https://itk.org/SimpleITKDoxygen/html/namespaceitk_1_1simple.html#ac8416e6e7f02dedfe8373b83dbea411d>`__,
which can be used for viewing images in an interactive session.
Currently, this function by default Show invokes
`**Fiji** <https://fiji.sc>`__ then
`**ImageJ** <http://rsbweb.nih.gov/ij/>`__ to display images. ImageJ was
chosen because it can handle all the image types that SimpleITK
supports, even 3D vector images with n components.

The Show function first searches the "PATH" environment variable, then
additional standard locations are examined, if problems are encountered
the correct path can be added to this environment variable and the
**"debugOn**" option to **"Show**" flag set.

ImageJ
^^^^^^

If ImageJ is used then we recommend downloading a recent version of
`ImageJ <http://rsbweb.nih.gov/ij/download.html>`__ from the official
home page. Recent versions come with support for the
`Nifti <http://nifti.nimh.nih.gov/nifti-1/>`__ ( \*.nii ) file format,
which SimpleITK uses to export to ImageJ.

**Note:** **Linux installation** requires an additional step. The
**"Show**" function searches for an executable named ImageJ or imagej,
however the default tarball does not come with this file. Instead it
comes with a file names
`script <http://imagej.nih.gov/ij/download/linux/unix-script.txt>`__.
This file contains the installation instructions. In short the file
should be renamed to "imagej" and the site specific variables for the
installation location, and java must be set. Also consider the
"newwindow" variable... Do you really want a new instance of ImageJ
launched each time you use Show? Lastly, as the installation
instructions indicate, the imagej wrapper should be in your path.

iPython and Jupyter
-------------------

If you are using python, `**ipython** <http://ipython.org/>`__ with
`Jupyter <http://jupyter.org>`__ is terrific environment to perform
interactive computing for image processing. With the addition of numpy
and scipy, you'll have a powerful interactive environment.

We have instructional `SimpleITK Jupyter
Notebooks <http://insightsoftwareconsortium.github.io/SimpleITK-Notebooks/>`__
which can help you get started.
