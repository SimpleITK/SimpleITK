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

What is the toolkit's Python version support policy?
----------------------------------------------------

For the Python programming language, SimpleITK stops providing binary packages when
the Python version has reached end-of-life status. Extensions may be made such as
when the EOL Python version is included as part of a long-term support
operating system version. If you need a newer SimpleITK binary than the one available
for your Python version you can :ref:`build it on your own<building_simpleitk>`.

How do I use the SimpleElastix framework in SimpleITK?
------------------------------------------------------

SimpleITK binary distributions do not include the SimpleElastix framework. To use
the version of SimpleElastix included in SimpleITK, you will need to
:ref:`build it on your local machine <building_simpleitk>`
using the SuperBuild configuration and turn on the SimpleITK_USE_ELASTIX flag in
addition to the relevant WRAP_LANGUAGE flags for the desired programming languages.


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


Why am I getting "DllNotFoundException: Unable to load DLL 'SimpleITKCSharpNative'" when running a CSharp application on Windows?
---------------------------------------------------------------------------------------------------------------------------------
This error message can be the result of an incomplete installation of SimpleITK
in the CSharp application.  Below is the complete error message that can result:

.. code-block :: bash

  System.TypeInitializationException: 'The type initializer for 'itk.simple.SimpleITKPINVOKE' threw an exception.'

  TypeInitializationException: The type initializer for 'SWIGExceptionHelper' threw an exception.

  DllNotFoundException: Unable to load DLL 'SimpleITKCSharpNative': The specified module could not be found. (Exception from HRESULT: 0x8007007E)


The application is missing the SimpleITK dynamically loaded library (DLL).  To
fix this problem, follow the instructions in the
`Add Native Library <https://simpleitk.readthedocs.io/en/master/setUp.html#add-native-library>`__
section of the SimpleITK Visual Studio/C# build instructions.

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
`here <https://docs.itk.org/en/latest/learn/metaio.html#reading-a-brick-of-bytes-an-n-dimensional-volume-in-a-single-file>`__.

The following is a sample Meta image header file, perhaps of name
sample.mhd:

.. code-block :: bash

        ObjectType = Image
        NDims = 3
        DimSize = 256 256 64
        ElementType = MET_USHORT
        ElementDataFile = image.raw    (this tag must be last in a MetaImageHeader)

An example implementing this approach is available here :ref:`here <lbl_raw_image_reading>`.


Why does my image appear to be empty / all black / blank when visualized?
-------------------------------------------------------------------------

There are two possible reasons for this:

#. The image is indeed empty. This is rarely the case, and indicates that there is something incorrect with the code, will require debugging.
#. The image contains very low values (1, 2, 3...). This is very common with segmentation and :ref:`binary mask <lbl_conventions_mask_image>` images. What you are experiencing is an issue with data visualization, not with the data itself. The code below illustrates the difference, and shows how to quickly visualize such images using the existing SimpleITK functionality.

.. code-block :: python

  import SimpleITK as sitk

  # Create segmentation image
  segmentation_image = sitk.Image([128,128], sitk.sitkUInt8)
  segmentation_image[40:50,20:120] = 1
  segmentation_image[50:60,20:120] = 2
  segmentation_image[60:70,20:120] = 3

  # When visualized with Fiji, image looks all black. To see the data
  # change the display settings Image->Adjust->Brightness/Contrast.
  sitk.Show(segmentation_image)

  # For quick visualization, convert to float and add
  # 255 so that the data is immediately visible in Fiji.
  sitk.Show(sitk.Cast(segmentation_image,sitk.sitkFloat32) + 255)


.. _lbl_imageJ_not_found:

Why isn't Fiji or ImageJ found by the Show function (RuntimeError: Exception thrown...)?
----------------------------------------------------------------------------------------

The SimpleITK ``Show`` function expects the Fiji or ImageJ application to be
installed in specific locations. The recommended installation locations are:

- On Windows: in your user directory (e.g. C:\\Users\\your_user_name\\Fiji.app or C:\\Users\\your_user_name\\Fiji).
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

Programs for creating virtual environments include `venv <https://packaging.python.org/en/latest/guides/installing-using-pip-and-virtual-environments/#creating-a-virtual-environment>`__
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

How do I read an image with a special character in the filename?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Special characters are non-ANSI characters, which require a non-ASCII encoding for representation. Unicode is the
modern standard with UTF-8 being the most common. The underlying ITK API calls uses bytes to represent the filename which
is compatible with UTF-8. This works on modern POSIX and MacOS systems. However, on Windows, the default encoding is
an alternative 8-bit encoding and wide UTF-16 is used to represent Unicode code points.

The Windows Operating Systems since about 2020 can be configured to use UTF-8 as the default encoding. This setting
can be found under "All Settings -> Time & Language -> Language -> "Administrative Language Settings" and the option
"Beta: Use Unicode UTF-8 for worldwide language support". However, this may change in the future and may have unintended
consequences for other languages.

An alternative, is to set the character locale to UTF-8 in the Python script. This can be done with the following
command:

.. code-block :: python

    import locale
    locale.setlocale( locale.LC_ALL, "en_US.UTF-8" )


There are related Python Enhancement Proposals (PEP) related to encodings:
 * `PEP 528 <https://www.python.org/dev/peps/pep-0528/>`_
 * `PEP 529 <https://www.python.org/dev/peps/pep-0529/>`_.
 * `PEP 540 <https://www.python.org/dev/peps/pep-0540/>`_.
 * `PEP 686 <https://www.python.org/dev/peps/pep-0686/>`_.


https://docs.python.org/3/using/windows.html#utf-8-mode

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

Path Length Issues on Windows
-----------------------------
The location of the build and source directories on Windows can cause the build
to fail.  By default, Windows does not allow path lengths longer than 260 characters.

See `Windows Path Length <windowsPathLength.html>`__ for more information.


Where is the Test Data?
-----------------------

The testing data is not stored in the SimpleITK repository or as part of
the source code. It is mirrored on several data repositories on the web.

If the source code was obtained from the git repository, the test data should
be downloaded as part of the build process via the CMake `ExternalData
<https://cmake.org/cmake/help/latest/module/ExternalData.html>`__ module.

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
