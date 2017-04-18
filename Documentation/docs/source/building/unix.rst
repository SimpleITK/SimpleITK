Building SimpleITK
******************

In many cases, you do not need to build SimpleITK because of the pre-built binaries available (see :doc:`../installation`). However there are several reasons you might prefer to build SimpleITK from source:

* The binary files for your programming language of choice are not (yet) distributed
* You want the live on the bleeding edge by using the latest-and-greatest version of SimpleITK
* You want to wrap your own filters using the SimpleITK infrastructure
* You want to contribute to the development of SimpleITK
* To use the SimpleITK's C++ interface and/or use ITK directly

.. contents:: On this page
    :local:
    :backlinks: none

Prerequisites
=============

To build SimpleITK you need:

* A recent version of CMake >= 3.3 with SSL support for https.
* A supported :doc:`compiler <../faq>`.
* To use the latest developmental version, source code can be downloaded with git >= 1.65
	
	* Git is required if building SimpleITK using "SuperBuild" (see below) to automatically download the matching version of ITK and SWIG
	* Windows users may prefer msysGit

It is recommended to have numpy installed when testing Python bindings.


Recipes/ Formulas/ Short Cuts
=============================

For some environments we have short cuts, scripts, for automated building of SimpleITK.


Mac
---
On the Mac, with the `Homebrew <http://brew.sh/>`_ package manager, a SimpleITK formula is available: https://github.com/Homebrew/homebrew-science/blob/master/simpleitk.rb for multiple language wrappings.

.. code-block:: bash
	
	# available install options can be listed using 
	brew options homebrew/science/simpleitk
	# for example, you can install with java and lua support as follows
	brew install homebrew/science/simpleitk --with-java --with-lua


Anaconda Python
---------------
For the Anaconda Python distribution: The `recipe <http://conda.pydata.org/docs/building/recipe.html>`_ for the SimpleITK build is in the official `conda-recipe <https://github.com/conda/conda-recipes>`_ repository.

.. code-block:: bash
	
	# get the recipe
	git clone https://github.com/conda/conda-recipes.git
	cd conda-recipes/python
	# build with your default Python (likely 2.7)
	conda build simpleitk
	# or build with 3.x
	CONDA_PY=34 conda build simpleitk

R
-
For the R language you can use the devtools installer (currently only for Linux/OS X): This script will download, build and install SimpleITK into your R environment. Please modify the number of processors to use based on your system (in our example below we set it to six)

.. code-block:: R

 	devtools::install_github("SimpleITK/SimpleITKRInstaller", args=c('--configure-vars="MAKEJ=6"'))

Lua
---
For the Lua language with the Luarocks module deployment system, a `SimpleITK rockspec <https://github.com/SimpleITK/SimpleITKLuaRock>`_ is available on github.

.. code-block:: bash

	# get the rock spec
	git clone https://github.com/SimpleITK/SimpleITKLuaRock.git
	cd SimpleITKLuaRock
	# build and install the SimpleITK Lua module
	luarocks install simpleitk-1.0-0.rockspec

Building
========

Obtaining Source Code
---------------------
There are two options to obtain the SimpleITK source code:

1. Download a released version from the `SimpleITK SourceForge page <https://sourceforge.net/projects/simpleitk/>`_
2. Download the latest development version using git:
   ``git clone http://itk.org/SimpleITK.git``

Building using SuperBuild
-------------------------
After downloading SimpleITK's source code we STRONGLY recommend to run cmake on the SuperBuild subdirectory of SimpleITK. Execute the following commands in the parent of the SimpleITK source directory to configure the SuperBuild:

.. code-block:: bash

	mkdir SimpleITK-build
	cd SimpleITK-build
	cmake ../SimpleITK/SuperBuild

The SuperBuild will automatically download and build the matching version of ITK and SWIG needed to compile SimpleITK. Additionally, it will set recommended compilation flags to minimize the size of the library and enable support for large libraries. This is the recommended way to build SimpleITK and is easiest.

.. note ::
	If you get an error message saying that ITK_DIR is not set then, you did not correctly point cmake to the SuperBuild sub-directory. Please erase your binary directory, and point cmake to the SimpleITK/SuperBuild sub-directory.

The cmake configuration process should automatically find supported languages and enable SimpleITK wrapping for them. To manually enable a language toggle the appropriate WRAP_LANGUAGE cmake variable to ON. Verify and/or correct the advanced cmake variables to the language specific executable, libraries and include directories. For example if you have multiple Python installations ensure that all related Python variable refer to the same versions.

Then use your make utility or your cmake chosen build utility to build SimpleITK.
SimpleITK takes a while to build.

Building manually
-----------------
This is **not** the recommended way of building SimpleITK, but it can be useful if you want to use a system version of ITK and/or SWIG, or if you do not want to (or can not) use git (due to firewall, etc).

1. Setup the prerequisites as described above (i.e. CMake and supported compiler)
2. Install the matching version of `SWIG <http://www.swig.org/>`_ >= 3.0.5
	e.g. Windows users may install `swigwin-3.0.5 <http://prdownloads.sourceforge.net/swig/swigwin-3.0.5.zip>`_
3. Download the SimpleITK source code from the SourceForge page
4. Download the matching version of ITK
	e.g. SimpleITK 0.10.0 uses `ITK 4.10.0 (tag v4.10.0) <http://sourceforge.net/projects/itk/files/itk/4.10/InsightToolkit-4.10.0.tar.gz/download>`_
5. Configure ITK using CMake
	BUILD_EXAMPLES=OFF, BUILD_TESTING=OFF, BUILD_SHARED_LIBS=OFF, **ITK_USE_REVIEW=ON**
6. Build ITK
	Be sure to note the build settings e.g. Release x64
7. Configure SimpleITK using CMake
	Set ITK_DIR to the location of the ITK build location from the previous steps
8. Build SimpleITK
	Be sure to configure the build settings exactly the same as ITK e.g. Release x64 and CXX_FLAGS

Testing
-------
After compilation the prudent thing to due is to test SimpleITK to ensure your build is stable and suitable for use and installation. The following commands execute the SimpleITK tests.

.. code-block:: bash

	cd SimpleITK-build/SimpleITK-build
	ctest

On Windows you will need to specify configuration. Typically that would be the Release configuration, as such:

.. code-block:: bash

	cd SimpleITK-build/SimpleITK-build
	ctest -C Release

If all tests fail, verify that you have the testing data in your source tree (the reason for the "--recursive" flag in the git command) AND that you have added the correct path to your *_LIBRARY_PATH.

Python installation
-------------------
To install a built python package into the system Python, as root run:

.. code-block:: bash

	cd SimpleITK-build/Wrapping/Python
	python Packaging/setup.py install

Alternatively, a Python virtual environment can be created and the distribution installed there. If you build the "dist" target a Python Wheel file (.whl) will be created in the "Wrapping/Python/dist" directory.

R installation
--------------
To install a built R package:

.. code-block:: bash

	cd SimpleITK-build/Wrapping/R/Packaging
	R CMD INSTALL SimpleITK

This will install the R package "SimpleITK" in /usr/local as root or your local R installation directory.

If you are working in a multi-user environment, and are considerate of your fellow users you can install the package in a local directory:

1. Create a local directory where you will install your R packages
 	``mkdir my_R_libs``
2. Add an environment variable to your .bashrc
 	``export R_LIBS="/path_to/my_R_libs"``
3. source your .bashrc and check the R library path, in an R shell >.libPaths()
4. install

	.. code-block:: bash

		cd SimpleITK-build/Wrapping/R/Packaging
		R CMD INSTALL -l /path_to/my_R_libs  SimpleITK


Recommended Software
====================

Fiji (Fiji is Just ImageJ)
--------------------------

SimpleITK has a built in function, `itk::simple::Show() <https://itk.org/SimpleITKDoxygen/html/namespaceitk_1_1simple.html#ac8416e6e7f02dedfe8373b83dbea411d>`_, which can be used for viewing images in an interactive session. 
Currently, this function by default ``Show`` invokes `Fiji <https://fiji.sc/>`_ then `ImageJ <http://rsbweb.nih.gov/ij/>`_ to display images. ImageJ was chosen because it can handle all the image types that SimpleITK supports, even 3D vector images with n components.

The Show function first searches the "PATH" environment variable, then additional standard locations are examined, if problems are encountered the correct path can be added to this environment variable and the **"debugOn"** option to **"Show"** flag set.

ImageJ
^^^^^^

If ImageJ is used then we recommend downloading a recent version of ImageJ from the `official home page <http://rsbweb.nih.gov/ij/download.html>`_. Recent versions come with support for the `Nifti <http://nifti.nimh.nih.gov/nifti-1/>`_ ( *.nii ) file format, which SimpleITK uses to export to ImageJ.

.. note :: 
	Linux installation requires an additional step. The ``Show`` function searches for an executable named ImageJ or imagej, however the default tarball does not come with this file. Instead it comes with a file names `script <http://imagej.nih.gov/ij/download/linux/unix-script.txt>`_. This file contains the installation instructions. In short the file should be renamed to "imagej" and the site specific variables for the installation location, and java must be set. Also consider the "newwindow" variable... Do you really want a new instance of ImageJ launched each time you use Show? Lastly, as the installation instructions indicate, the imagej wrapper should be in your path.

iPython and Jupyter
-------------------
If you are using python, `ipython <http://ipython.org/>`_ with `Jupyter <http://jupyter.org/>`_ is terrific environment to perform interactive computing for image processing. With the addition of numpy and scipy, you'll have a powerful interactive environment.

We have instructional SimpleITK Jupyter Notebooks which can help you get started.
