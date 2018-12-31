Frequently Asked Questions
**************************

This page hosts frequently asked questions about SimpleITK, and their
answers.

..
    .. contents:: On this page
        :local:
        :backlinks: none


Installation
============

I am using the binary distribution of SimpleITK for Anaconda, why do I get an error about libpng?
-------------------------------------------------------------------------------------------------

        ImportError: dlopen(./_SimpleITK.so, 2): Library not loaded: @rpath/libpng15.15.dylib
          Referenced from: .../lib/python2.7/site-packages/SimpleITK/_SimpleITK.so
          Reason: image not found

This type of error can occour if a library SimpleITK depends on can
not be found. It may be that the version of the dependent library has
changed in the Python environment and is no longer compatible. One
solution is to create a `environment.yml` file with all the packages
required for your project, then create a new environment:

.. code-block :: bash

  conda env create -f environment.yml


How to Use
==========

What filters are currently available in SimpleITK?
--------------------------------------------------

There are nearly **300 ITK image filters** wrapped
in SimpleITK. We have a
:ref:`list of filters <lbl_filter>` accompanied by a brief
description. Additionally the
`Doxygen <https://www.itk.org/SimpleITKDoxygen/html/classes.html>`__ can
be examined to determine the availability of a filter.

What image file formats can SimpleITK read?
-------------------------------------------

See :ref:`here <image-io>`.


How do I read a RAW image into SimpleITK?
-----------------------------------------

In general raw image files are missing information. They do not contain
the nessesary header information to describe the basic size and type for
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

.. _lbl_imageJ_not_found:

Why isn't ImageJ found by the Show function (RuntimeError: Exception thrown...)?
---------------------------------------------------------------------------------

The SimpleITK ``Show`` function expects the ImageJ program to be installed in
specific locations. The recommended installation locations are:

- On Windows: in your user directory (e.g. C:\\Users\\your_user_name\\Fiji.app).
- On Linux: in ~/bin .
- On Mac: in /Applications .

To see the locations where the function is searching set its debugOn flag.

In Python:

.. code-block :: python

  sitk.Show(image, debugOn=True)

In R:

.. code-block :: r

  Show(image, "file_name", TRUE)


You can also indicate where a viewer (not necessarily ImageJ) is found by setting
the path to the viewer in an environment variable SITK_SHOW_COMMAND.

Can I use another image file viewer beside ImageJ?
--------------------------------------------------

By default when the `Show
function <https://www.itk.org/SimpleITKDoxygen/html/namespaceitk_1_1simple.html#a7bacfc4685cff93e46d7401865f9579e>`__
is called, SimpleITK writes out a temporary image in Nifti format then
launches `ImageJ <http://rsbweb.nih.gov/ij/index.html>`__. The user can
override the file format of the temporary file and/or the application
used to handle that file.

The temporary file format can be specified via the
**SITK\_SHOW\_EXTENSION** environment variable. For example, if the user
wanted to export a PNG file, on Linux it might look like this:

.. code-block :: bash

        SITK_SHOW_EXTENSION=".png"
        export SITK_SHOW_EXTENSION

Use of an extension unsupported by ITK results in an error message. For
the supported image formats, here is the `ITK Image IO
Filters <https://www.itk.org/Doxygen/html/group__IOFilters.html>`__.

The default display application for all image types is ImageJ. To
override ImageJ with some other application, use the
**SITK\_SHOW\_COMMAND** environment variable. For instance, on Unix
systems, using GNOME's image viewer eog would be:

.. code-block :: bash

        SITK_SHOW_EXTENSION=".png"
        export SITK_SHOW_EXTENSION
        SITK_SHOW_COMMAND="eog"
        export SITK_SHOW_COMMAND

To override the default display applications for only color or 3d
images, there are the **SITK\_SHOW\_COLOR\_COMMAND** and
**SITK\_SHOW\_3D\_COMMAND** environment variables.

More details on the Show function, including use of the "%a" and "%f"
tokens, is at the `Show function Doxygen
page <https://www.itk.org/SimpleITKDoxygen/html/namespaceitk_1_1simple.html#a7bacfc4685cff93e46d7401865f9579e>`__.

How can I use 3D Slicer to view my images?
------------------------------------------

`3D Slicer <https://slicer.org>`__ is a very powerful and popular
application for visualization and medical image computing. The
SITK\_SHOW\_COMMAND environment variable may be used to display images
in Slicer instead of SimpleITK's default viewer, ImageJ. The following
are examples of what settings for SITK\_SHOW\_COMMAND might look like
for Mac OS X, Linux and Windows to use Slicer.

Mac OS X

.. code-block :: bash

        export SITK_SHOW_COMMAND=/Applications/Slicer.app/Contents/MacOS/Slicer

Linux

.. code-block :: bash

        export SITK_SHOW_COMMAND=Slicer

Windows

.. code-block :: bash

        set SITK_SHOW_COMMAND=:"c:\Program Files\Slicer 4.2.2-1\Slicer"

The value of SITK\_SHOW\_COMMAND should be modified to point to wherever
Slicer is installed. If you only want to use Slicer for volumetric 3D
images, use the SITK\_SHOW\_3D\_COMMAND environment variable instead of
SITK\_SHOW\_COMMAND.

How can I use a newer Java with ImageJ on Mac OS X?
---------------------------------------------------

By default on Mac OS X, the ImageJ application expects Java 6, which is
old and unsupported. The latest supported version of Java (currently
version 8u25) can be downloaded from `Oracle's Java Development kit
page <http://www.oracle.com/technetwork/java/javase/downloads/jdk8-downloads-2133151.html>`__.
The following bash commands will set up the SITK\_SHOW\_COMMAND and
SITK\_SHOW\_COLOR\_COMMAND to invoke ImageJ's jar file using the Java
compiler.

.. code-block :: bash

        ij="/Applications/ImageJ/"
        ijcmd="java -Dplugins.dir=$ij/plugins -jar $ij/ImageJ.app/Contents/Resources/Java/ij.jar"
        export SITK_SHOW_COMMAND="$ijcmd -eval 'open( \"%f\" );'"
        export SITK_SHOW_COLOR_COMMAND="$ijcmd -eval 'open( \"%f\" ); run(\"Make Composite\", \"display=Composite\");'"

The first lines set a variable pointing to the standard location for the
ImageJ directory. If ImageJ is installed somewhere else, the line should
be modified. The second line provides the command to launch ImageJ using
the Java compiler. It includes flags that point to ImageJ's plugiin
directory and ImageJ's ij.jar file.

The SITK\_SHOW\_COMMAND tells SimpleITK.Show() to launch Java with
ij.jar and then execute the open macro with an image file. The
SITK\_SHOW\_COLOR\_COMMAND does these same things and then executes the
ImageJ "Make Composite" command to treat a multichannel image as a
composite color image.

Wrapping
========

Python
------

.. _FAQ-virtualenv:

Why should I use a virtual environment?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Before you install SimpleITK we highly recommend that you create a
virtual environment into which you install the package. Note that
different Python versions and distributions have different programs for
creating and managing virtual environments.

The use of a virtual environment allows you to elegantly deal with
package compatability issues, to quote `The Hitchhiker’s Guide to
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
distribution. However, it is recommended that you compile SimpleITK
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
and Filters. Addtionally, we use some headers which are included in the
C99 and C++ TR1 extension. Therefore SimpleITK places additional
requirements on the compiler beyond what is required for ITK. In
principle we require C++x03 with C99's "stdint.h" and TR1's
"functional". If your compiler has those features it is likely able to
be supported.

The additional requirement for a supported compiler is that it is on the
nightly dashboard. With this regard, the list of supported compilers is
on the SimpleITK `SimpleITK
dashboard <https://open.cdash.org/index.php?project=SimpleITK>`__. We
welcome user contributions to the nightly dashboard to expand the list
of supported compilers.

Noted Problems
~~~~~~~~~~~~~~

-  Microsoft compilers before Visual Studio 14 (2015) have had memory
   limitation issues.

Why am I getting a compilation error on OSX?
------------------------------------------------------

With SimpleITK <=0.7 the following error occurred during compilation on
Apple OSX 10.9 Mavericks with **clang 5.0**:

::

         SimpleITK/Code/Common/include/sitkMemberFunctionFactoryBase.h:106:16:  error: no member named 'tr1' in namespace 'std'
         typedef std::tr1::function< MemberFunctionResultType ( ) > FunctionObjectType;
         ~~~~~^

With Xcode 5.0, Apple's distributed version of clang (5.0) changed which
implementation of the C++ Standard Library it uses by default. Previous
versions of clang (4.2 and earlier) used `GNU's
libstdc++ <https://gcc.gnu.org/libstdc++/>`__ , while clang 5.0 now uses
`LLVM's libc++ <https://libcxx.llvm.org>`__. SimpleITK 0.7 and earlier
require certain features from `C++
tr1 <https://en.wikipedia.org/wiki/C%2B%2B_Technical_Report_1>`__ which
are not implemented in LLVM's libc++ but are available in GNU's
libstdc++.

To build SimpleITK <=0.7 with clang 5.0, you can configure the compiler
to use GNU's stdlibc++. This change must be done at the initial
configuration:

.. code-block :: bash

        cmake "-DCMAKE_CXX_FLAGS:STRING=-stdlib=libstdc++" ../SimpleITK/SuperBuild

NOTE: If you already have a build directory which has been partially
configured the contents must be deleted. The above line needs to be done
for an initial configuration in an empty build directory. NOTE: This
work around does not work when with the CMake "Xcode" generator. It is
recommended to just use the default "Unix Makefiles" generator, to build
SimpleITK, and get using SimpleITK, not building it.

The following is a **compatibility table for clang 5.0**. It shows that
the default of libc++ does not work with SimpleITK, while the other
options do. The choice of which standard library to use and which C++
language standard to use are independent.

+---------------------------+------------------+---------------------+
| Clang 5.0 compatibility   | -stdlib=libc++   | -stdlib=libstdc++   |
+===========================+==================+=====================+
| (c++03)                   | FAIL             | OK                  |
+---------------------------+------------------+---------------------+
| -std=c++11                | OK (>=0.8)       | OK                  |
+---------------------------+------------------+---------------------+

For SimpleITK >=0.8, support for the tr1 features migrated to C++11 has
been improved with better feature detection, and the necessary flags are
now automatically added. LLVM's libc++ will now work if compiling with
the C++11 standard by adding the flag "-std=c++11" in the initial
configuration.

To further complicate dependencies and interactions, some downloadable
languages such as Java, or R, may be compiled against GNU's libstdc++.
This may cause a conflict in the types used in the interface resulting
in compilation errors while wrapping the language.

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

Do I need to download an option package for TR1 support?
--------------------------------------------------------

Visual Studio 2008 requires an additional download for TR1 support. This
support is best provided with the Service Pack 1. There is a separate
TR1 feature pack which can be downloaded, but it is no longer
recommended since Service Pack 1 includes TR1 and numerous bug and
performance improvements.


What Configurations on Windows are Supported For Building?
----------------------------------------------------------

We recommend to use Microsoft Visual Studio 14 (2015) or newer to
compile SimpleITK.


Where is the Test Data?
-----------------------

The testing data is not stored in the SimpleITK repository or as part of
the source code. It is mirrored on several data repositories on the web.

If you have obtained the source code from the git repository, it should
be downloaded as part of the build process via the CMake `ExternalData
<https://cmake.org/cmake/help/v3.10/module/ExternalData.html>`__ module.

You can download a tar-ball of the "SimpleITKData" for
a release from the `GitHub Assets
<https://github.com/SimpleITK/SimpleITK/releases>`__, which contains the
external data. It should populate the .ExternalData subdirectory of the
SimpleITK source code directory when extracted.

Why is CMake unable to download ExternalData?
---------------------------------------------

When compiling SimpleITK you may get and error like the following:

::

 Object MD5=2e115fe26e435e33b0d5c022e4490567 not found at:
  https://placid.nlm.nih.gov/api/rest?method=midas.bitstream.download&checksum=2e115fe26e435e33b0d5c022e4490567&algorithm=MD5 ("Unsupported protocol")
  https://simpleitk.github.io/SimpleITKExternalData/MD5/2e115fe26e435e33b0d5c022e4490567 ("Unsupported protocol")
  https://midas3.kitware.com/midas/api/rest?method=midas.bitstream.download&checksum=2e115fe26e435e33b0d5c022e4490567&algorithm=MD5 ("Unsupported protocol")
  https://insightsoftwareconsortium.github.io/ITKTestingData/MD5/2e115fe26e435e33b0d5c022e4490567 ("Unsupported protocol")
  https://itk.org/files/ExternalData/MD5/2e115fe26e435e33b0d5c022e4490567 ("Unsupported protocol")

This indicates that CMake was not compiles with SSL support. The
"Unsupported protocol" message indicate that CMake can not communicate
via "https".

The solution is to use a compiled version of CMake which supports SSL.
If you compile CMake yourself, simply reconfigure CMake with the
"CMAKE\_USE\_OPENSSL" option enabled.
