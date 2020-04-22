A Simple C++/CMake Example
==========================

Building a C++ SimpleITK application is supported by using `CMake <https://cmake.org>`_ to
configure the build process.  CMake can generate project buildsystems for Unix Makefiles,
`Ninja <https://ninja-build.org>`_, Microsoft Visual Studio, or Mac OS Xcode.

Here is a basic **CMakeLists.txt** configuration file for building a SimpleITK C++ example program.

.. literalinclude:: ../../Examples/CppCMake/Source/CMakeLists.txt


Here is our SimpleITK C++ example file **sitk_example.cxx**.

.. literalinclude:: ../../Examples/CppCMake/Source/sitk_example.cxx
   :language: c++
   :lines: 18-


Invoking **cmake** as below in the same directory as these files will create the project buildsystem::

    cmake .

Required CMake Variables
########################

Running CMake will produce a **CMakeCache.txt** file that is the CMake configuration.  Within that
text file there are two variables needed to build a SimpleITK program, *SimpleITK_DIR* and *ITK_DIR*.
SimpleITK_DIR needs to be set to the directory that contains the file SimpleITKConfig.cmake, and
ITK_DIR needs to be the directory containing the file ITKConfig.cmake.

CMake attempts to find these files automatically, but it is unlikely to find them unless SimpleITK
and ITK are installed into the system.

If SimpleITK has been built using the SuperBuild process, as described in :doc:`building`, then
these required directories can be found in the SuperBuild location.  The SimpleITK_DIR variable
should refer to the directory SimpleITK-build within the SuperBuild location, and the ITK_DIR
variable should refer to the directory ITK-build in the SuperBuild location.

Here are what the settings in a CMakeCache.txt file should look like::

    //The directory containing a CMake configuration file for ITK.
    ITK_DIR:PATH=/home/dchen/SuperBuild/ITK-build

    //The directory containing a CMake configuration file for SimpleITK.
    SimpleITK_DIR:PATH=/home/dchen/SuperBuild/SimpleITK-build

Compiling using CMake
#####################
A SimpleITK program can also be compiled by running CMake.  Here is the command to perform the
build in the current directory::

    cmake --build . --config Release

The 'config' parameter could also be set to Debug, RelWithDebInfo or MinSizeRel.  On
Unix-type systems Release is the default.  On Windows the config must be specified explicitly.

Of course traditional methods can be used to build a SimpleITK program (e.g. make on Unix, or
Visual Studio on Windows), but it is often convenient to be able to use the same build command on
all system types.


Using CMake on Windows
######################

The Windows version of CMake includes a graphical-user-interface (GUI) version of the program,
in addition to the standard command-line CMake.  Here is what the CMake GUI looks like:

.. image:: ../images/cmake-win-1.png
  :width: 400
  :alt: Windows CMake GUI

After the user specifies the **source** and **build** directories, CMake will ask to select
which compiler generator to use.  The options are determined by what versions of Visual Studio
are installed on the system.  The user must specify **x64** for the platform version, as the
default option (x86) is not supported by SimpleITK.

.. image:: ../images/cmake-win-2.png
  :width: 400
  :alt: Visual Studio Selection

Next are the configuration and generation process.  By clicking the **Configure** button,
cmake reads the CMakeLists.txt and sets up all the variables in the CMake cache (CMakeCache.txt).
Then when the **Generate** button is clicked, CMake creates the Visual Studio build system.

.. image:: ../images/cmake-win-3.png
  :width: 45%
  :alt: CMake Configure
.. image:: ../images/cmake-win-4.png
  :width: 45%
  :alt: CMake Generate

After CMake is completed the generation process the user can actually build SimpleITK in Visual
Studio.  The user should select a build type in Visual Studio.  We recommend choosing **Release**,
since the performance of SimpleITK with the Debug option is several orders of magnitude slower.
Also the user must select the **x64** build platform, as the default one, x86, is not supported by
SimpleITK.  Many man hours and cpu cycles have been wasted building SimpleITK without setting
the proper platform.

.. image:: ../images/cmake-win-5.png
  :width: 500
  :alt: CMake Build Version
