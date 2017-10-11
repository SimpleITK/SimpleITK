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

.. _installation-binaries:

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
recommend the use of a :ref:`virtual environment <FAQ-virtualenv>`
for installation of SimpleITK.


.. _installation-generic-python:

Wheels for Generic Python Distribution
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

From the command line use the `pip
program <https://pip.pypa.io/en/latest/index.html>`__ to install a
binary wheel:

.. code-block :: bash

 pip install SimpleITK

This requires a recent version of  pip (>=9.0), to properly detect
compatibility with the `PEP 427
<https://www.python.org/dev/peps/pep-0427/>`__ tags in the wheel
filenames. You can update your pip using ``pip install -U pip``. It
also requires that your Python environment is compatible with one of
the pre-compiled binary wheels.

Alternatively, the wheels can be manually downloaded from `sourceforge
<http://sourceforge.net/projects/simpleitk/files/SimpleITK/>`__ or
`PyPI <https://pypi.python.org/pypi/SimpleITK>`__, then installed with pip.


Conda-based distributions (Anaconda, Miniconda)
-----------------------------------------------

From the command line prompt, execute:

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
the `CDash dashboard <https://open.cdash.org/index.php?project=SimpleITK>`__
in the "Nightly Packages" section.

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
`"itk::simple::Show()" <https://itk.org/SimpleITKDoxygen/html/namespaceitk_1_1simple.html#ac8416e6e7f02dedfe8373b83dbea411d>`__,
which can be used for viewing images in an interactive session.
Currently, this function by default Show invokes
`Fiji <https://fiji.sc>`__ then
`ImageJ <http://rsbweb.nih.gov/ij/>`__ to display images. ImageJ was
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

IPython and Jupyter
-------------------

If you are using python, `IPython <http://ipython.org/>`__ with
`Jupyter <http://jupyter.org>`__ is terrific environment to perform
interactive computing for image processing. With the addition of numpy
and scipy, you'll have a powerful interactive environment.

We have instructional `SimpleITK Jupyter
Notebooks <http://insightsoftwareconsortium.github.io/SimpleITK-Notebooks/>`__
which can help you get started.
