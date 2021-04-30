A Simple C++/CMake Example
==========================

Building a C++ SimpleITK application is supported by using
`CMake <https://cmake.org>`_ to configure the build process.  CMake can
generate project buildsystems for Unix Makefiles,
`Ninja <https://ninja-build.org>`_, Microsoft Visual Studio, or Mac OS Xcode.

Here is a basic **CMakeLists.txt** configuration file for building a SimpleITK
C++ example program.

.. literalinclude:: ../../Examples/CppCMake/Source/CMakeLists.txt


Here is our SimpleITK C++ example file **sitk_example.cxx**.

.. literalinclude:: ../../Examples/CppCMake/Source/sitk_example.cxx
   :language: c++
   :lines: 18-


Invoking **cmake** as below in the same directory as these files will create
the project buildsystem::

    cmake .

Required CMake Variables
########################

Running CMake will produce a **CMakeCache.txt** file that is the CMake
configuration.  Within that text file there are two variables needed to build
a SimpleITK program, **SimpleITK_DIR** and **ITK_DIR**.  SimpleITK_DIR needs to
be set to the directory that contains the file :code:`SimpleITKConfig.cmake`,
and ITK_DIR needs to be the directory containing the file
:code:`ITKConfig.cmake`.

CMake attempts to find these files automatically, but it is unlikely to find
them unless SimpleITK and ITK are installed into the system.

If SimpleITK has been built using the SuperBuild process, as described in
:doc:`building`, then these required directories can be found in the SuperBuild
location.  The SimpleITK_DIR variable should refer to the directory
SimpleITK-build within the SuperBuild location, and the ITK_DIR variable should
refer to the directory ITK-build in the SuperBuild location.

Here are what the settings in a CMakeCache.txt file should look like::

    //The directory containing a CMake configuration file for ITK.
    ITK_DIR:PATH=path_to_simpleitk_build_dir/ITK-build

    //The directory containing a CMake configuration file for SimpleITK.
    SimpleITK_DIR:PATH=path_to_simpleitk_build_dir/SimpleITK-build

Compiling using CMake
#####################
A SimpleITK program can also be compiled by running CMake.  Here is the command
to perform the build in the current directory::

    cmake --build . --config Release

The 'config' parameter could also be set to Debug, RelWithDebInfo or
MinSizeRel.  On Unix-type systems Release is the default.  On Windows the
config must be specified explicitly.  We recommend Release or MinSizeRel,
since SimpleITK compiled in Debug mode is several orders of magnitude slower.

Of course traditional methods can be used to build a SimpleITK program (e.g.
make on Unix, or Visual Studio on Windows), but it is often convenient to be
able to use the same build command on all system types.


Using CMake-gui on Windows
##########################

In addition to the standard command-line CMake, a graphical-user-interface
(GUI) version of CMake is also available.  Here is what the CMake GUI looks
like building our same example:

.. image:: ../images/windows-build1.png
  :width: 400
  :alt: Windows CMake GUI

We have placed the files sitk_example.cxx and CMakeLists.txt in
the folder :code:`C:\sitkExample`, and in CMake we have set the **source**
directory to point there.  Also, in CMake, we have set the **build**
directory to point to :code:`C:\sitkExample-Build`.

After the user specifies the source and build directories, CMake will ask to
select which compiler generator to use.  The options are determined by what
versions of Visual Studio are installed on the system, in this example Visual
Studio 16 2019.  The user must specify **x64** for the platform generator,
as the default option (x86) is not supported by SimpleITK.

.. image:: ../images/windows-build2.png
  :width: 45%
  :alt: Setting SimpleITK_DIR
.. image:: ../images/windows-build3.png
  :width: 45%
  :alt: Setting ITK_DIR

After clicking **Configure**, CMake will attempt to find the SimpleITK library.
That can be set in the :code:`SimpleITK_DIR` variable, as seen in the above
left image.  CMake is looking for the directory containing the
:code:`SimpleITKConfig.cmake` file, in our example
:code:`C:\SimpleITK-build\SimpleITK-build`.

Clicking Configure again, CMake will then try to find the ITK library for the
:code:`ITK_DIR` variable (see above right).  CMake is looking for the directory
containing :code:`ITKConfig.cmake`.  For a SimpleITK SuperBuild, as we have done,
:code:`ITK_DIR` will be the :code:`ITK-build` directory within the SuperBuild,
in our case :code:`C:\SimpleITK-build\ITK-build`.

Once the :code:`SimpleITK_DIR` and :code:`ITK_DIR` variables have been set, we can click
**Generate** to create the Visual Studio project file, :code:`ALL_BUILD.vcxproj`.

.. image:: ../images/windows-build4.png
  :width: 90%
  :alt: Visual Studio

After opening :code:`ALL_BUILD.vcvproj` in Visual Studio, the user should
select a build type in Visual Studio.  We recommend choosing **Release** for
performance reasons.  Then the user should select the **x64** build platform,
not the unsupported default, x86.  Many man-hours and cpu cycles have been
wasted building SimpleITK without setting the proper platform.
