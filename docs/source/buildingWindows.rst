
Building SimpleITK on Windows
###########################################

This page describes how to build a SimpleITK Superbuild on
Windows.  To build SimpleITK we use CMake to generate a Visual Studio project,
and Visual Studio to compile the C/C++ code.  To obtain the SimpleITK source
code see :ref:`source_code`.

The Windows version of CMake includes a graphical-user-interface (GUI) version
of the program, in addition to the standard command-line CMake.  Here is what
the CMake GUI looks like:

.. image:: ../images/cmake-win-1.png
  :width: 400
  :alt: Windows CMake GUI

In the above example, the source directory is :code:`C:/SimpleITK`, and the
build directory is :code:`C:/SimpleITK-build`.  It is best to place the source
and build directories at the root of a volume to minimize path name lengths.
Windows has a `default max path length <https://docs.microsoft.com/en-us/windows/win32/fileio/maximum-file-path-limitation?tabs=cmd>`_
of 260 characters, and ITK has long paths which can cause build issues.

.. image:: ../images/cmake-win-2.png
  :width: 400
  :alt: Visual Studio Selection

After the user specifies the **source** and **build** directories, CMake will
ask to select which compiler generator to use.  The options are determined by
what versions of Visual Studio are installed on the system.  The user must
specify **x64** for the platform version, since the default option (x86) is
not supported by SimpleITK.

.. image:: ../images/cmake-win-3.png
  :width: 45%
  :alt: CMake Configure
.. image:: ../images/cmake-win-4.png
  :width: 45%
  :alt: CMake Generate

The next steps are the configuration and generation processes.  By clicking
the **Configure** button, cmake reads the :code:`CMakeLists.txt` file and sets up all
the variables in the CMake cache (:code:`CMakeCache.txt`).  Then when the **Generate**
button is clicked, CMake creates the Visual Studio build system.

The left image of the above figure is the result of the configure process, and
on the right is the result of the generation process.

Note for the **CMAKE_CXX_FLAGS** and **CMAKE_C_FLAGS** variables, we have
appended the **'/MP'** flag, enabling multiple processor when building with Visual
Studio.  This flag is *not* enabled by default.

After CMake has completed the generation process, the user can actually build
SimpleITK with Visual Studio.  The user should select a build type in Visual
Studio.  We recommend choosing **Release** or **MinSizeRel** (release with
minimum size), since the performance of SimpleITK with the Debug option is
several orders of magnitude slower.  Also the user must select the **x64**
build platform, since the default platform (x86) is not supported by SimpleITK.

Many man hours and cpu cycles have been wasted building SimpleITK without
setting the proper platform.

.. image:: ../images/cmake-win-5.png
  :width: 90%
  :alt: CMake Build Version

To begin the build process in Visual Studio, select **Build ALL_BUILD** in the
**Build** menu.

Once the build has completed with no failures, the build can be verified with
the following commands entered in a PowerShell::

    cd C:\SimpleITK-build\SimpleITK-build
    ctest -R Release

These commands assume that the SimpleITK build directory is
:code:`C:\\SimpleITK-build` and that the build is a Release build.
