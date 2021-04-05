.. _FAQ:

Frequently Asked Questions
**************************

This page hosts frequently asked questions about SimpleITK, and their
answers.

..
    .. contents:: On this page
        :local:
        :backlinks: none

General
=======

Does SimpleITK offer all the functionality as the C++ ITK?
----------------------------------------------------------

SimpleITK supports most ITK image filters (:ref:`see list <lbl_filter>`) and the
IO and registration frameworks. It exposes fewer settings than ITK, hence the
Simple in the name. The main ITK
elements omitted from SimpleITK are the pipeline architecture,
spatial objects framework, point sets, and the mesh framework.


Installation
============

I am using the binary distribution of SimpleITK for Anaconda, why do I get an error about libpng?
-------------------------------------------------------------------------------------------------

        ImportError: dlopen(./_SimpleITK.so, 2): Library not loaded: @rpath/libpng15.15.dylib
          Referenced from: .../lib/python2.7/site-packages/SimpleITK/_SimpleITK.so
          Reason: image not found

This type of error can occur if a library SimpleITK depends on can
not be found. It may be that the version of the dependent library has
changed in the Python environment and is no longer compatible. One
solution is to create a `environment.yml` file with all the packages
required for a project, then create a new environment:

.. code-block :: bash

  conda env create -f environment.yml

Why am I getting "ModuleNotFoundError: No module named '_SimpleITK'" when importing SimpleITK on Windows?
---------------------------------------------------------------------------------------------------------

        Traceback (most recent call last):
          File "C:\Python37\lib\site-packages\SimpleITK\SimpleITK.py", line 14, in swig_import_helper
            return importlib.import_module(mname)
            ...
            File "<frozen importlib._bootstrap>", line 219, in _call_with_frames_removed
            ImportError: DLL load failed: The specified module could not be found.

The above error occurs on Microsoft windows when system libraries SimpleITK depends on are not available on the system.
This issue can be resolved by installing the appropriate
`Redistributable for Visual Studio <https://www.microsoft.com/en-us/download/details.aspx?id=48145>`__ package.


How to Use
==========

What filters are currently available in SimpleITK?
--------------------------------------------------

There are nearly **300 ITK image filters** wrapped
in SimpleITK. We have a
:ref:`list of filters <lbl_filter>` accompanied by a brief
description. Additionally the
`Doxygen <https://simpleitk.org/doxygen/latest/html/classes.html>`__ can
be examined to determine the availability of a filter.

What image file formats can SimpleITK read?
-------------------------------------------

See :ref:`here <image-io>`.


How do I read a RAW image into SimpleITK?
-----------------------------------------

In general raw image files are missing information. They do not contain
the necessary header information to describe the basic size and type for
the data, so this format is intrinsically deficient. The
`RawImageIO <https://www.itk.org/Doxygen/html/classitk_1_1RawImageIO.html>`__
class is not available in SimpleITK so there is no direct way to
programmatically hard code this header information. The suggested way is
to create a Meta image header file (\*.mhd) which references the raw
data file and describes the size and type of the data. The documentation
on how to write a Meta image header can be found
`here <https://www.itk.org/Wiki/MetaIO/Documentation#Reading_a_Brick-of-Bytes_.28an_N-Dimensional_volume_in_a_single_file.29>`__.

The following is a sample Meta image header file, perhaps of name
sample.mhd:

.. code-block :: bash

        ObjectType = Image
        NDims = 3
        DimSize = 256 256 64
        ElementType = MET_USHORT
        ElementDataFile = image.raw    (this tag must be last in a MetaImageHeader)

An example implementing this approach is available here :ref:`here <lbl_raw_image_reading>`.

.. _lbl_imageJ_not_found:

Why isn't Fiji or ImageJ found by the Show function (RuntimeError: Exception thrown...)?
----------------------------------------------------------------------------------------

The SimpleITK ``Show`` function expects the Fiji or ImageJ application to be
installed in specific locations. The recommended installation locations are:

- On Windows: in your user directory (e.g. C:\\Users\\your_user_name\\Fiji.app).
- On Linux: in ~/bin.
- On Mac: in /Applications or ~/Applications.

To see the locations where the function is searching set Show's debugOn flag.

In Python:

.. code-block :: python

  sitk.Show(image, debugOn=True)

In R:

.. code-block :: r

  Show(image, "file_name", TRUE)


Show is a functional interface to the `ImageViewer class <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ImageViewer.html>`__.
Other viewing applications can be configured using an ImageViewer object, as
described in the next section.

.. _alt_viewer:

Can I use another image file viewer beside Fiji?
--------------------------------------------------

The
`ImageViewer class <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ImageViewer.html>`__ allows a user to configure what application
SimpleITK uses to display images.
An ImageViewer object displays an image via the Execute method.

The default display application for all image types is `Fiji <https://fiji.sc>`__.
To override Fiji with some other application, use the
``ImageViewer::SetCommand`` method.  For example in Python on Linux
systems, using ImageMagick's display program would look like this:

.. code-block :: python

        import SimpleITK as sitk

        viewer = sitk.ImageViewer()
        viewer.SetFileExtension('.png')
        viewer.SetCommand('/usr/bin/display')

By default when ``ImageViewer::Execute`` is called, it writes out a temporary
image in `Nifti <https://nifti.nimh.nih.gov>`__ format then launches Fiji. If
the viewing application has been changed to one that does not support Nifti,
the file format of the temporary file can be overridden using the
``ImageViewer::SetFileExtension`` method. In the above example, we use PNG, a
format ImageMagick does support, unlike Nifti.

Use of an file extension unsupported by ITK results in an error message. For
the supported image formats, see the `ITK Image IO
Filters <https://www.itk.org/Doxygen/html/group__IOFilters.html>`__.

More details into ImageViewer configuration can be found in the
`ImageViewer class documentation <https://simpleitk.org/doxygen/latest/html/classitk_1_1simple_1_1ImageViewer.html>`__.

How can I use 3D Slicer to view my images?
------------------------------------------

`3D Slicer <https://slicer.org>`__ is a very powerful and popular
application for visualization and medical image computing. An
ImageViewer object can be configured to use
Slicer instead of SimpleITK's default viewer, Fiji. The following
are examples of how to configure an ImageViewer object in Python
for Mac OS X, Linux and Windows to use Slicer.

Mac OS X

.. code-block :: python

        import SimpleITK as sitk

        viewer = sitk.ImageViewer()
        viewer.SetCommand('/Applications/Slicer.app/Contents/MacOS/Slicer')

Linux

.. code-block :: python

        import SimpleITK as sitk

        viewer = sitk.ImageViewer()
        viewer.SetCommand('Slicer')

Windows

.. code-block :: python

        import SimpleITK as sitk

        viewer = sitk.ImageViewer()
        viewer.SetCommand( 'c:\Program Files\Slicer 4.10.2\Slicer' )

The call to SetCommand should be modified to point to wherever
the Slicer executable is installed.

Wrapping
========

Python
------

.. _FAQ-virtualenv:

Why should I use a virtual environment?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Before installing SimpleITK we highly recommend creating a
virtual environment into which the package can be installed. Note that
different Python versions and distributions have different programs for
creating and managing virtual environments.

The use of a virtual environment allows a user to elegantly deal with
package compatibility issues, to quote `The Hitchhiker’s Guide to
Python! <https://docs.python-guide.org/en/latest/>`__:

    A Virtual Environment is a tool to keep the dependencies required by
    different projects in separate places, by creating virtual Python
    environments for them. It solves the “Project X depends on version
    1.x but, Project Y needs 4.x” dilemma, and keeps your global
    site-packages directory clean and manageable.

Programs for creating virtual environments include `virtualenv and
pyvenv <https://packaging.python.org/en/latest/installing/#creating-virtual-environments>`__
for generic Python distributions,
`conda <https://conda.pydata.org/docs/using/envs.html>`__ for the
anaconda distribution, and
`canopy\_cli <https://docs.enthought.com/canopy/configure/canopy-cli.html>`__
for the canopy distribution.

Are the Python Wheels compatible with Enthought Canopy Distribution?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The :ref:`Generic Python Wheels <installation-generic-python>`
frequently seem to work with the Enthought Canopy Python
distribution. However, we recommend compiling SimpleITK
explicitly against this Python distribution to ensure compatibility.

Tcl
---

Java
----

C#
--

R
-

Compilation
===========

.. _FAQ-compiler-supported:

Is my compiler supported?
-------------------------

SimpleITK uses advanced C++ meta-programming to instantiate ITK's Images
and Filters. SimpleITK is developed to require the C++11 standard.

In practice the list of compilers actively supported are those that are used for continuous
testing and integration. These can be seen on the `SimpleITK
dashboard <https://open.cdash.org/index.php?project=SimpleITK>`__. We
welcome user contributions to the nightly dashboard to expand the list
of these compilers and contributions to fix additional compilation problems.

Noted Problems
~~~~~~~~~~~~~~

-  Microsoft compilers before Visual Studio 14 (2015) have had memory
   limitation issues.


Are 32-bits architectures supported?
------------------------------------

While 32-bit binaries are no longer pre-compiled, the intel 32-architecture are still
tested to help ensure robustness of the toolkit. Contributions and bug reports to support
additional architectures are welcomed.


Why does the Superbuild fail compiling PCRE on Mac OS X?
--------------------------------------------------------

If the Xcode command line tools are not properly set up on OS X, PCRE
could fail to build in the Superbuild process with messages such as:

::

 checking whether we are cross compiling... configure: error: in `/your/build/path/SimpleITK/PCRE-prefix/src/PCRE-build':
 configure: error: cannot run C compiled programs.
 If you meant to cross compile, use `--host'.
 See `config.log' for more details
 [10/13] Performing build step for 'PCRE'

To install the command line developer tools enter the following:


.. code-block :: bash

   xcode-select --install

To reset the default command line tools path:

.. code-block :: bash

   xcode-select --reset


What Configurations on Windows are Supported For Building?
----------------------------------------------------------

We recommend using at least Microsoft Visual Studio 15 (2017) with MSVC v140 toolset.


Where is the Test Data?
-----------------------

The testing data is not stored in the SimpleITK repository or as part of
the source code. It is mirrored on several data repositories on the web.

If the source code was obtained from the git repository, the test data should
be downloaded as part of the build process via the CMake `ExternalData
<https://cmake.org/cmake/help/v3.10/module/ExternalData.html>`__ module.

A tar-ball of the "SimpleITKData" can be downloaded for
a release from the `GitHub Assets
<https://github.com/SimpleITK/SimpleITK/releases>`__, which contains the
external data. It should populate the .ExternalData subdirectory of the
SimpleITK source code directory when extracted.

Why is CMake unable to download ExternalData?
---------------------------------------------

When compiling SimpleITK an error like the following may occur:

::

 Object MD5=2e115fe26e435e33b0d5c022e4490567 not found at:
  https://placid.nlm.nih.gov/api/rest?method=midas.bitstream.download&checksum=2e115fe26e435e33b0d5c022e4490567&algorithm=MD5 ("Unsupported protocol")
  https://simpleitk.org/SimpleITKExternalData/MD5/2e115fe26e435e33b0d5c022e4490567 ("Unsupported protocol")
  https://midas3.kitware.com/midas/api/rest?method=midas.bitstream.download&checksum=2e115fe26e435e33b0d5c022e4490567&algorithm=MD5 ("Unsupported protocol")
  https://insightsoftwareconsortium.github.io/ITKTestingData/MD5/2e115fe26e435e33b0d5c022e4490567 ("Unsupported protocol")
  https://itk.org/files/ExternalData/MD5/2e115fe26e435e33b0d5c022e4490567 ("Unsupported protocol")

This indicates that CMake was not compiles with SSL support. The
"Unsupported protocol" message indicate that CMake can not communicate
via "https".

The solution is to use a compiled version of CMake which supports SSL.
To re-build CMake with OpenSSL support, simply reconfigure CMake with the
"CMAKE\_USE\_OPENSSL" option enabled.
