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
Windows. **R** binaries are not available but a convenient
`remotes based installer <https://github.com/SimpleITK/SimpleITKRInstaller>`__  for Linux and Mac is.

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

 pip install simpleitk

This installation requires a recent version of pip, to properly detect
compatibility with the filename tags`PEP 427
<https://www.python.org/dev/peps/pep-0427/>`__ , stable API
`PEP 425 <https://peps.python.org/pep-0425/>`__ , and package
name normalization. Pip can be updated using ``pip install -U pip``.
Also the Python environment must be compatible with one of
the pre-compiled binary wheels.

Alternatively, the wheels can be manually downloaded from `GitHub releases
<https://github.com/SimpleITK/SimpleITK/releases>`__ or
`PyPI <https://pypi.python.org/pypi/SimpleITK>`__, and then installed with pip.


Conda-based distributions (Anaconda, Miniconda)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

SimpleITK Conda binaries are available for the conda-forge ecosystem. To get started run the following command:

.. code-block :: bash

 conda create --name sitk python=3.11 simpleitk --channel conda-forge --override-channels
 conda activate sitk

This will create and activate a new conda environment named ``sitk`` with Python 3.11 and SimpleITK installed from the `Anaconda
conda-forge channel <https://anaconda.org/conda-forge/simpleitk>`__. The version of python can be changed to any
supported version.

The above ``create`` command creates an environment which only used the conda-forge channel. This follows Conda-forge's
recommendation to not mix the ``defaults`` channel with the conda-forge channel. Mixing the channels can cause package
dependency issues, missing libraries, and a non-functional virtual environment. Alternatively, the
`miniforge <https://github.com/conda-forge/miniforge>`__ installer can be used to create dedicated conda-forge
environments.


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

R binaries are not available.

For Linux and Mac one can easily build and install SimpleITK from source using a `remotes <https://cran.r-project.org/web/packages/remotes/readme/README.html>`__ based installer
referencing this `GitHub Repository <https://github.com/SimpleITK/SimpleITKRInstaller>`__.

This installation requires `R remotes <https://github.com/r-lib/remotes>`__,
`CMake <https://cmake.org/>`__, `git <https://git-scm.com/>`__, and a compiler
in the path.

One line commands to build and install the package:

.. code-block :: bash

  remotes::install_github("SimpleITK/SimpleITKRInstaller")

or using six cores for compilation (change this number based on your hardware):

.. code-block :: bash

  remotes::install_github("SimpleITK/SimpleITKRInstaller", configure.vars=c("MAKEJ=6"))


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

 pip install --upgrade --pre simpleitk --find-links https://github.com/SimpleITK/SimpleITK/releases/tag/latest


Recommended Software
====================

Fiji (Fiji is Just ImageJ)
--------------------------

SimpleITK has a built in function,
`itk::simple::Show() <https://simpleitk.org/doxygen/latest/html/namespaceitk_1_1simple.html#a86cb9e226d455efca3ba034dc2154605>`__,
which can be used for viewing images in an interactive session.
By default this Show function searches for an installed
`Fiji <https://fiji.sc>`__ to display images.  If Fiji is not found,
then it searches for `ImageJ <https://imagej.net/ij/>`__. Fiji/ImageJ were
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
