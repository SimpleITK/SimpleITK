Frequently Asked Questions
**************************

This page hosts frequently asked questions about SimpleITK, and their
answers.

.. contents:: On this page
    :local:
    :backlinks: none


Installation
============

Why do I get an error about a missing Dynamic Library when running SimpleITK with Python on windows?
----------------------------------------------------------------------------------------------------

This error has been resolved with SimpleITK version 0.5.1 and should no
longer occur. Upgrading to the latest SimpleITK is encouraged.

This error occurs after you have downloaded the Windows SimpleITK
binaries when you are running python and try to import SimpleITK. There
is an error about a missing DLL on Windows when you don't have Visual
Studio 10 and no other application has installed certain libraries
before. You will need to download the Visual Studio 10 redistribution
libraries. The libraries are available for download
`here <http://www.microsoft.com/download/en/details.aspx?id=5555>`__.

I am using the binary distribution of SimpleITK for Anaconda, why do I get an error about libpng?
-------------------------------------------------------------------------------------------------

::

        ImportError: dlopen(./_SimpleITK.so, 2): Library not loaded: @rpath/libpng15.15.dylib
          Referenced from: .../lib/python2.7/site-packages/SimpleITK/_SimpleITK.so
          Reason: image not found

This can be resolved by installing the version of libpng that SimpleITK
0.9 was built against:

.. code-block :: bash

        conda create -n sitkpy anaconda libpng=1.5
        source activate sitkpy #unix/mac
        # for win: activate sitkpy
        conda install -c https://conda.binstar.org/simpleitk/channel/main SimpleITK
        conda install libpng=1.5

This set of commands:

-  creates the virtual environment with our choice of libpng version,
   all other anaconda packages will be compatible with this version.
-  activate the virtual environment.
-  installs SimpleITK into the virtual environment (unfortunately this
   will automatically upgrade you to libpng 1.6).
-  downgrades to libpng 1.5 so that library versions are compatible.

We are currently investigating why the anaconda build system is not
expressing version dependency for shared libraries. We how this will not
be an issue with the next binary package.

How to Use
==========

What filters are currently available in SimpleITK?
--------------------------------------------------

As of March 2014 we have approximately **260 ITK image filters** wrapped
for SimpleITK. The `**filter coverage
table** <http://www.itk.org/SimpleITKDoxygen/html/Filter_Coverage.html>`__
shows the current set of ITK filters in SimpleITK. Additionally the
`Doxygen <http://www.itk.org/SimpleITKDoxygen/html/classes.html>`__ can
be looked at to determine if a filter is available.

What image file formats can SimpleITK read?
-------------------------------------------

How do I read a RAW image into SimpleITK?
-----------------------------------------

In general raw image files are missing information. They do not contain
the nessesary header information to describe the basic size and type for
the data, so this format is intrinsically deficient. The
`RawImageIO <http://www.itk.org/Doxygen/html/classitk_1_1RawImageIO.html>`__
class is not available in SimpleITK so there is no direct way to
programmatically hard code this header information. The suggested way is
to create a Meta image header file (\*.mhd) which references the raw
data file and describes the size and type of the data. The documentation
on how to write a Meta image header can be found
`here <http://www.itk.org/Wiki/MetaIO/Documentation#Reading_a_Brick-of-Bytes_.28an_N-Dimensional_volume_in_a_single_file.29>`__.

The following is a sample Meta image header file, perhaps of name
sample.mhd:

.. code-block :: bash

        ObjectType = Image
        NDims = 3
        DimSize = 256 256 64
        ElementType = MET_USHORT
        ElementDataFile = image.raw    (this tag must be last in a MetaImageHeader)

Can I use another image file viewer beside ImageJ?
--------------------------------------------------

By default when the `Show
function <http://www.itk.org/SimpleITKDoxygen/html/namespaceitk_1_1simple.html#a7bacfc4685cff93e46d7401865f9579e>`__
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
Filters <http://www.itk.org/Doxygen/html/group__IOFilters.html>`__.

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
page <http://www.itk.org/SimpleITKDoxygen/html/namespaceitk_1_1simple.html#a7bacfc4685cff93e46d7401865f9579e>`__.

How can I use 3D Slicer to view my images?
------------------------------------------

`3D Slicer <http://slicer.org>`__ is a very powerful and popular
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
Python! <http://docs.python-guide.org/en/latest/>`__:

    A Virtual Environment is a tool to keep the dependencies required by
    different projects in separate places, by creating virtual Python
    environments for them. It solves the “Project X depends on version
    1.x but, Project Y needs 4.x” dilemma, and keeps your global
    site-packages directory clean and manageable.

Programs for creating virtual environments include `virtualenv and
pyvenv <https://packaging.python.org/en/latest/installing/#creating-virtual-environments>`__
for generic Python distributions,
`conda <http://conda.pydata.org/docs/using/envs.html>`__ for the
anaconda distribution, and
`canopy\_cli <http://docs.enthought.com/canopy/configure/canopy-cli.html>`__
for the canopy distribution.

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

.. _compiler-supported:

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
dashboard <http://open.cdash.org/index.php?project=SimpleITK>`__. We
welcome user contributions to the nightly dashboard to expand the list
of supported compilers.

Committed to Support
~~~~~~~~~~~~~~~~~~~~

-  GCC 4.2-4.7
-  Visual Studio 2008 with Service Pack 1 (VS9)
-  Visual Studio 2012 (VS10) ( including Express )
-  Visual Studio 2012 (VS11)

Noted Problems
~~~~~~~~~~~~~~

-  Compiling on a MS Windows 32-bit OS with static libraries is not
   supported due to lack of memory.
-  With SimpleITK release 0.4.0, Visual Studio 2008 was not compiling.
   This problem has since been remedied in the development branch on
   April 18th, 2012.
-  With SimpleITK release 0.7.0, Visual Studio 2008 is not able to
   compile all wrapped languages at the same time, it's recommenced to
   choose one at a time.

Why am I getting a compilation error on OSX Mavericks?
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
libstdc++ <http://gcc.gnu.org/libstdc++/>`__ , while clang 5.0 now uses
`LLVM's libc++ <http://libcxx.llvm.org>`__. SimpleITK 0.7 and earlier
require certain features from `C++
tr1 <http://en.wikipedia.org/wiki/C%2B%2B_Technical_Report_1>`__ which
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
'''xcode-select --install

To reset the default command line tools path: '''xcode-select --reset

Do I need to download an option package for TR1 support?
--------------------------------------------------------

Visual Studio 2008 requires an additional download for TR1 support. This
support is best provided with the Service Pack 1. There is a separate
TR1 feature pack which can be downloaded, but it is no longer
recommended since Service Pack 1 includes TR1 and numerous bug and
performance improvements.

Do I need to download an optional package for C99?
--------------------------------------------------

SimpleITK will proved a "stdint.h" header if missing on the system.

How do I build with Visual Studio 2008?
---------------------------------------

Visual Studio 2008 is the oldest supported Microsoft development
environment that SimpleITK supports. To build SimpleITK, certain
features of C++TR1 are required. These features are best provided by the
`"Microsoft Visual Studio 2008 Service Pack
1" <http://www.microsoft.com/download/en/details.aspx?id=23691>`__ (or
try this link
`1 <http://www.microsoft.com/en-us/download/confirmation.aspx?id=10986>`__).
Alternatively just the `Visual C++ 2008 Feature Pack
Release <http://www.microsoft.com/downloads/en/details.aspx?FamilyId=D466226B-8DAB-445F-A7B4-448B326C48E7&displaylang=en>`__
can be installed. Please note that all our dashboard machines now use
SP1.

Older versions of SimpleITK (<0.7.0) requires a also required a
separately downloaded stdint.h for this compiler. This is not
automatically provided if needed. If it's still needed the file can be
downloaded
`here <http://msinttypes.googlecode.com/svn/trunk/stdint.h>`__. For
64-bit Microsoft Windows it should be dragged with the GUI into the
appropriate include path for the architecture.

What Configurations on Windows are Supported For Building?
----------------------------------------------------------

There are quite a large number of configuration options available for
the Windows platform. The following table is a guide line of what is
regularly tested and confirmed to work or fail.

+--------------------+---------------------+----------------+---------------------------------+-------------------------------+-------------------------------+-------------------------------+-----------+---------+-----------+---------+
|                    | Architecture        | Library Type   | Visual Studio 2008 SP1 (VS9 )   | Visual Studio 2010 ( VS10 )   | Visual Studio 2012 ( VS11 )   | Visual Studio 2013 ( VS13 )   |           |         |           |         |
+====================+=====================+================+=================================+===============================+===============================+===============================+===========+=========+===========+=========+
|                    |                     |                | Release                         | Debug                         | Release                       | Debug                         | Release   | Debug   | Release   | Debug   |
+--------------------+---------------------+----------------+---------------------------------+-------------------------------+-------------------------------+-------------------------------+-----------+---------+-----------+---------+
| 32-bit Window OS   | Only Intel 32-bit   | Static         | FAIL                            | FAIL                          | FAIL                          | FAIL                          |           |         |           |         |
+--------------------+---------------------+----------------+---------------------------------+-------------------------------+-------------------------------+-------------------------------+-----------+---------+-----------+---------+
| Shared             | FAIL                | FAIL           | Nightly                         | Nightly                       |                               |                               |           |         |           |         |
+--------------------+---------------------+----------------+---------------------------------+-------------------------------+-------------------------------+-------------------------------+-----------+---------+-----------+---------+
| 64-bit Window OS   | Intel 32-bit        | Static         | Nightly                         |                               | Nightly                       |                               | Nightly   |         | Nightly   |         |
+--------------------+---------------------+----------------+---------------------------------+-------------------------------+-------------------------------+-------------------------------+-----------+---------+-----------+---------+
| Shared             |                     |                |                                 |                               |                               |                               |           |         |           |         |
+--------------------+---------------------+----------------+---------------------------------+-------------------------------+-------------------------------+-------------------------------+-----------+---------+-----------+---------+
| Intel 64-bit       | Static              | Nightly        |                                 | Nightly                       | Nightly                       |                               |           |         |           |         |
+--------------------+---------------------+----------------+---------------------------------+-------------------------------+-------------------------------+-------------------------------+-----------+---------+-----------+---------+
| Shared             |                     |                |                                 |                               | Nightly                       |                               | Nightly   |         |           |         |
+--------------------+---------------------+----------------+---------------------------------+-------------------------------+-------------------------------+-------------------------------+-----------+---------+-----------+---------+



+-----------+------------------------------------------------------------------------+
|           | Legend                                                                 |
+-----------+------------------------------------------------------------------------+
| Nightly   | This combination of options is nightly tested, and known to work.      |
+-----------+------------------------------------------------------------------------+
|           | This combinations has been manually tested, and is expected to work.   |
+-----------+------------------------------------------------------------------------+
|           | It is not known if this combinations of options will work.             |
+-----------+------------------------------------------------------------------------+
|           | This combination likely has problems, and is not recommended.          |
+-----------+------------------------------------------------------------------------+
| FAIL      | These options are known not to work.                                   |
+-----------+------------------------------------------------------------------------+


This table has been updated for the release branch, master, as of
February 15th 2013.

Why are all of the configurations not supported on Windows?
-----------------------------------------------------------

One of the following errors frequently occur when the set of
configuration options fail:

``LINK : fatal error LNK1102: out of memory``

``LINK : fatal error LNK1248: image size (80000010) exceeds maximum allowable size (80000000)``

These errors occur because of limitations in the compiler's linker or
the operating system. For 64-bit architectures the linker is still only
32-bits on some Visual Studios. In certain configurations the linker can
run out of memory. Also the Windows operating systems have a hard limit
of 2GB for the size of libraries. For Debug mode configurations this
limit can be encounted.

In general building in Debug mode should not be necessary, unless you
are trying to debug SimpleITK or ITK. This configuration produces
libraries that are very large because the compiler must maintain symbols
for all instantiated ITK classes and member functions for each template
parameters that a class is instantiating.

Where is the Test Data?
-----------------------

The testing data is not stored in the SimpleITK repository or as part of
the source code. It is mirrored on several data repositories on the web.

If you have obtained the source code from the git repository, it should
be downloaded as part of the build process via the CMake ExternalData
module.

If you have downloaded a tar-ball of the source code there should be an
accompanying "SimpleITKData" tar-ball available, which contains the
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
