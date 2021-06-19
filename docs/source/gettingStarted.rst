Getting Started
++++++++++++++++

Welcome to SimpleITK!

SimpleITK provides a simplified interface to ITK in a variety of
languages. A user can either download pre-built binaries, if they
are available for the desired platform and language, or SimpleITK can be
:ref:`built from the source code<building_simpleitk>`.

In the following sections we describe how to install SimpleITK and
auxiliary software tools.

After installing SimpleITK, we recommend going over the
:ref:`latest tutorial <lbl_tutorials_courses>` and skimming
the `Doxygen <http://www.simpleitk.org/doxygen/latest/html/>`__ pages for
more information.

..
	.. contents:: On this page
	    :depth: 2
	    :local:
	    :backlinks: none

.. _installation-binaries:

Downloading the binaries
========================

One of the great advantages of SimpleITK is that (typically) the user does not
have to build it — he or she can simply download the binaries and get started
right away!

Currently, **Python** binaries are available on Microsoft Windows, GNU
Linux and Mac OS X. **C# and Java** binaries are available for
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

This installation requires a recent version of  pip (>=9.0), to properly detect
compatibility with the `PEP 427
<https://www.python.org/dev/peps/pep-0427/>`__ tags in the wheel
filenames. Pip can be updated using ``pip install -U pip``.
Also the Python environment must be compatible with one of
the pre-compiled binary wheels.

Alternatively, the wheels can be manually downloaded from `GitHub releases
<https://github.com/SimpleITK/SimpleITK/releases>`__ or
`PyPI <https://pypi.python.org/pypi/SimpleITK>`__, and then installed with pip.


Conda-based distributions (Anaconda, Miniconda)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

From the command line prompt, execute:

.. code-block :: bash

 conda install -c simpleitk simpleitk

Beta and release candidate packages are also available on Anaconda cloud
under the dev label:

.. code-block :: bash

 conda install -c simpleitk/label/dev simpleitk


C# binary files
---------------

**Binaries for select C# platforms** can be found on SimpleITK's
`GitHub releases
<https://github.com/SimpleITK/SimpleITK/releases>`__
under the appropriate version. Installing the library should only
involve importing the unzipped files into the C# environment. The
files have the following naming convention:

``SimpleITK-version-CSharp-buildplatform-targetplatform.zip``

e.g.

| ``SimpleITK-1.2.4-CSharp-win64-x64.zip``


Details about how to set up a C# Visual Studio project with SimpleITK
can be found in the :ref:`setup SimpleITK with CSharp <setup-csharp>` page.


Java binary files
-----------------

**Binaries for select Java platforms** can be found on SimpleITK's
`GitHub releases page
<https://github.com/SimpleITK/SimpleITK/releases>`__
under the appropriate version. Installation instructions are available
at :ref:`setup SimpleITK with Java <setup-java>`.


R binary files
--------------

R binaries are currently only available for Linux and Mac.

SimpleITK/R is installed using a devtools based installer
(`GitHub Repository <https://github.com/SimpleITK/SimpleITKRInstaller>`__).
Strictly speaking, this is not a binary distribution, but it is a convenient
way of automatically compiling and installing on a system.

This installation requires `R devtools <https://github.com/r-lib/devtools>`__,
`CMake <https://cmake.org/>`__, `git <https://git-scm.com/>`__, and a compiler
in the path.

.. code-block :: bash

  devtools::install_github("SimpleITK/SimpleITKRInstaller")


Latest binaries
----------------

If the latest SimpleITK bug fixes and features are required then
pre-release binaries are available. The pre-release binaries are built
from the actively developed master branch. The SimpleITK packages are
available on `Github releases
<https://github.com/SimpleITK/SimpleITK/releases/tag/latest>`__ under
the "latest" tag. The packages include Python, CSharp and Java. To
upgrade to the latest pre-release Python binary package run:


.. code-block :: bash

 pip install --upgrade --pre SimpleITK --find-links https://github.com/SimpleITK/SimpleITK/releases/tag/latest


Recommended Software
====================

Fiji (Fiji is Just ImageJ)
--------------------------

SimpleITK has a built in function,
`itk::simple::Show() <https://simpleitk.org/doxygen/latest/html/namespaceitk_1_1simple.html#a86cb9e226d455efca3ba034dc2154605>`__,
which can be used for viewing images in an interactive session.
By default this Show function searches for an installed
`Fiji <https://fiji.sc>`__ to display images.  If Fiji is not found,
then it searches for `ImageJ <http://rsbweb.nih.gov/ij/>`__. Fiji/ImageJ were
chosen because they can handle all the image types that SimpleITK
supports, including 3D vector images with n components per pixel.

The Show function searches for Fiji/ImageJ in a number of standard locations.
The exact locations depend on the system type (Linux, Mac or Windows).
Enabling the **"debugOn**" option to **"Show**", allows the user to see
where SimpleITK is searching for Fiji (or other viewing application)
and the actual command used to launch the viewing application.

Show is a functional interface to the `ImageViewer class <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ImageViewer.html>`__.
Other viewing applications can be configured using an ImageViewer object,
see the following section of the :ref:`FAQ`:

    :ref:`alt_viewer`.


IPython and Jupyter
-------------------

For python users, `IPython <http://ipython.org/>`__ with
`Jupyter <http://jupyter.org>`__ is a terrific environment to perform
interactive computing for image processing.  The addition of the
`numpy <https://numpy.org>`__ and `scipy <https://www.scipy.org>`__ packages
creates a powerful interactive development environment.

We have instructional `SimpleITK Jupyter
Notebooks <http://insightsoftwareconsortium.github.io/SimpleITK-Notebooks/>`__
which can help a user get started.
