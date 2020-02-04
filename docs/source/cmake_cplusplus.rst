A Simple C++/CMake Example
==========================

Building a C++ SimpleITK application is supported by using `CMake <https://cmake.org>`_ to
configure the build process.  CMake can generate project buildsystems for Unix Makefiles,
`Ninja <https://ninja-build.org>`_, Microsoft Visual Studio, or Mac OS Xcode.

Here is a basic **CMakeLists.txt** configuration file for building a SimpleITK C++ example program.

.. literalinclude:: CMakeLists.txt


Here is our SimpleITK C++ example file **sitk_example.cxx**.

.. literalinclude:: sitk_example.cxx


Invoking **cmake** as below in the same directory as these files will create the project buildsystem::

    cmake .

Required CMake Variables
########################

Running cmake will produce a **CMakeCache.txt** file that is the cmake configuration.  Within that
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
A SimpleITK program can also be compiled by running cmake.  Here is the command to perform the
build in the current directory::

    cmake --build . --config Release

The 'config' parameter could also be set to Debug, RelWithDebInfo or MinSizeRel.  On
Unix-type systems Release is the default.  On Windows the config must be specified explicitly.

Of course traditional methods can be used to build a SimpleITK program (e.g. make on Unix, or
Visual Studio on Windows), but it is often convenient to be able to use the same build command on
all system types.
