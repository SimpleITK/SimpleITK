Installing SimpleITK
********************

Typically, you don't need to build SimpleITK to use it. 
You can simply download the binaries and get started right away!

Currently, Python binaries are available on Windows, Linux and Mac OS X. C# and Java binaries are available for Windows. We are also working towards supporting R packaging.

Python
======
`Virtual environments <http://docs.python-guide.org/en/latest/dev/virtualenvs/>`_ are highly recommended. They allow you to elegantly deal with package compatibility issues.

Standard Python installation
-----------------------------
From the shell, execute

.. code-block:: bash
	
	pip install simpleitk

You can always manually download the wheels for your operating system and Python version directly from `sourceforge <http://sourceforge.net/projects/simpleitk/files/SimpleITK/>`_. You might need to update your pip using ``pip install -U pip``.

The pip package manager should automatically find the correct package for MS Windows and GNU Linux if your version is supported. For Apple OS X you need to manually specify:

.. code-block:: bash

	pip install https://sourceforge.net/projects/simpleitk/files/SimpleITK/0.10.0/Python/SimpleITK-0.10.0-cp27-cp27m-macosx_10_6_intel.whl

Conda-based distributions (Anaconda, Miniconda)
-----------------------------------------------
From the shell/command prompt, execute

.. code-block:: bash
	
	conda install -c https://conda.anaconda.org/simpleitk SimpleITK

Beta and release candidate packages are also available on Anaconda cloud under the dev label

.. code-block:: bash
	
	conda install -c https://conda.anaconda.org/simpleitk/label/dev SimpleITK


C Sharp (C#)
============
Binaries for select C# platform can be found on `SimpleITK's SourceForge page <https://sourceforge.net/projects/simpleitk/files/SimpleITK/0.10.0/CSharp/>`_. 
Installing the library should only involve importing the unzipped files into you C# environment. 

The files have the following naming convention::

	SimpleITK-version-CSharp-buildplatform-targetplatform.zip

Following files are currently available::
	
	SimpleITK-0.10.0-CSharp-win32-x86.zip
	SimpleITK-0.10.0-CSharp-win64-x64.zip

A guide describing how to set up a C# Visual Studio project with SimpleITK can be found :doc:`here <building/csharp>`. 
For platforms other than Windows, you might have to build manually as described in :doc:`building/unix`.

Java
====
Binaries for select Java platforms can be found on `SimpleITK's SourceForge page <https://sourceforge.net/projects/simpleitk/files/SimpleITK/0.10.0/Java/>`_. 

Following files are currently available::
	
	SimpleITK-0.10.0-Java-win64.zip	
	SimpleITK-0.10.0-Java-win32.zip	

Detailed instructions are available at :doc:`building/java`.
For platforms other than Windows, you might have to build manually as described in :doc:`building/unix`.


Nightly binaries
================

The latest binaries for the current development version of SimpleITK are also generally available. Binary packages are built as part of the nightly regression testing system. The download links are available from the `CDash	<https://open.cdash.org/index.php?project=SimpleITK>`_ dashboard in the "Nightly Packages" section.

Each row on the dashboard is a SimpleITK build on a particular system, and if the build was successful there will be a package icon: package.png which links to the packages build by the system. A user may directly download the built package from such a link.