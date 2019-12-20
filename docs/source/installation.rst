Installation
************

SimpleITK provides a simplified interface to ITK in a variety of
languages. You can either download binaries, if they are available for
your platform and preferred language, or you can :ref:`build SimpleITK <building_simpleitk>`
yourself from the source code.

Additionally, there are several recommended third-party software
packages.

After you have installed SimpleITK, please look to the
`Tutorial <http://simpleitk.github.io/ISBI2018_TUTORIAL/>`__
or the `Doxygen <http://www.itk.org/SimpleITKDoxygen/html/>`__ pages for
more information.

..
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

This installation requires a recent version of  pip (>=9.0), to properly detect
compatibility with the `PEP 427
<https://www.python.org/dev/peps/pep-0427/>`__ tags in the wheel
filenames. You can update your version of pip using ``pip install -U pip``.
Also your Python environment must be compatible with one of
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
involve importing the unzipped files into you C# environment. The
files have the following naming convention:

``SimpleITK-version-CSharp-buildplatform-targetplatform.zip``

eg.

| ``SimpleITK-1.2.0-CSharp-win64-x64.zip``

Details about how to set up a C# Visual Studio project with SimpleITK
can be found in the :ref:`setup SimpleITK with CSharp <setup-csharp>`.


Java binary files
-----------------

**Binaries for select Java platforms** can be found on SimpleITK's
`GitHub releases page
<https://github.com/SimpleITK/SimpleITK/releases>`__
under the appropriate version. Installation instructions are available
at :ref:`setup SimpleITK with Java <setup-java>`.

Latest binaries
----------------

If the latest SimpleITK bug fixes or features are required then
pre-release binaries are needed. The pre-release binaries are built
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

SimpleITK has a built in function
`itk::simple::Show() <https://itk.org/SimpleITKDoxygen/html/namespaceitk_1_1simple.html#a86cb9e226d455efca3ba034dc2154605>`__
which can be used for viewing images in an interactive session.
By default this Show function searches for an installed
`Fiji <https://fiji.sc>`__ to display images.  If Fiji is not found,
then it searches for `ImageJ <http://rsbweb.nih.gov/ij/>`__. Fiji/ImageJ were
chosen because they can handle all the image types that SimpleITK
supports, including 3D vector images with n components.

The Show function first searches the "PATH" environment variable, then
additional standard locations are examined, if problems are encountered
the correct path can be added to this environment variable and the
**"debugOn**" option to **"Show**" flag set.

The Show function can also be configured to invoke some other viewing application
using the SITK_SHOW_COMMAND environment variable.

IPython and Jupyter
-------------------

If you are using python, `IPython <http://ipython.org/>`__ with
`Jupyter <http://jupyter.org>`__ is terrific environment to perform
interactive computing for image processing. With the addition of numpy
and scipy, you will have a powerful interactive environment.

We have instructional `SimpleITK Jupyter
Notebooks <http://insightsoftwareconsortium.github.io/SimpleITK-Notebooks/>`__
which can help you get started.
