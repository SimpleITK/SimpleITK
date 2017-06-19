Installation
************

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
    :depth: 2
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
and Anaconda packages for the Anaconda Python distribution. We
reccommend the use of a :ref:`virual environment <FAQ-virtualenv>`
for installation of SimpleITK.


.. _installation-generic-python:

Wheels for Generic Python Distribution
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

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

.. code-block :: bash

 pip installSimpleITK

The pip package manager should automatically find the correct package
for Microsoft Windows, Apple OS X and GNU Linux if your version and
architecture are supported. If no binary package is found, then a source
distribution will be downloaded and attempted to be compiled and you
should look into `Build It Yourself`_.

        If your pip version in the virtual environment is stale (<9.0)
        you need to update it (pip install -U pip).

Anaconda Distribution
^^^^^^^^^^^^^^^^^^^^^

First thing you should do is create a virtual environment
(`conda <https://conda.pydata.org/docs/using/envs.html>`__ tool) and
activate it.

Currently there are compiled binaries on `Anaconda
Cloud <https://conda.anaconda.org/simpleitk>`__, easily installed with:

.. code-block :: bash

 conda install -c https://conda.anaconda.org/simpleitk SimpleITK

Beta and release candidate packages are also available on Anaconda cloud
under the dev label:

.. code-block :: bash

 conda install -c https://conda.anaconda.org/simpleitk/label/dev SimpleITK


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
CSharp <https://itk.org/Wiki/SimpleITK/GettingStarted/A_visual_guide_to_SimpleITK_with_CSharp>`__.

More information about getting started with a sample C# program can be
found in `A visual guide to building SimpleITK on
Linux <https://itk.org/Wiki/SimpleITK/GettingStarted/Visual_guide_to_building_on_Linux#A_simple_C.23_program>`__

Java binary files
-----------------

**Binaries for select Java platforms** can be found on `SimpleITK's
SourceForge
page <https://sourceforge.net/projects/simpleitk/files/SimpleITK/1.0.0/Java/>`__.
Installation instructions are available at `a visual guide to SimpleITK
in
Java <https://itk.org/Wiki/SimpleITK/GettingStarted/A visual guide to SimpleITK in Java>`__.

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
