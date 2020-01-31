A Simple C++/CMake Example
==========================

Building a C++ SimpleITK application is normally done using `CMake <https://cmake.org>` to
configure the build process.  CMake can generate project buildsystem for Unix Makefiles,
Microsoft Visual Studio, or Mac OS Xcode.

Here is a basic **CMakeLists.txt** configuration file for building a SimpleITK C++ example program.

.. literalinclude:: CMakeLists.txt


Here is our SimpleITK C++ example file **sitk_example.cxx**.

.. literalinclude:: sitk_example.cxx


To create the project buildsystem, run **cmake** in the same directory as these files like so::

    cmake .

Running cmake will produce a **CMakeCache.txt** file that is the cmake configuration.  Within that
text file there are several variables that will most likely need to be set, SimpleITK_DIR and ITK_DIR.
SimpleITK_DIR needs to be set to the directory that contains the file SimpleITKConfig.cmake, and ITK_DIR needs
to be the directory containing the ITKConfig.cmake file.

CMake attempts to find these files automatically, but it is unlikely to find them unless SimpleITK and ITK are
installed into the system.

If you have built SimpleITK using the SuperBuild process, as described in :doc:`building`, then required directories
can be found in the SuperBuild location.  The SimpleITK_DIR variable should refer
to SimpleITK-build within the SuperBuild location, and ITK_DIR variable should refer
to ITK-build in the SuperBuild location.

Here are what the settings in a generate CMakeCache.txt file look like::

    //The directory containing a CMake configuration file for ITK.
    ITK_DIR:PATH=/home/dchen/SuperBuild/ITK-build

    //The directory containing a CMake configuration file for SimpleITK.
    SimpleITK_DIR:PATH=/home/dchen/SuperBuild/SimpleITK-build
