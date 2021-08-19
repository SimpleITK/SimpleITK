.. _windows_path_length:

Path Length Issues on Windows
#############################


.. toctree::
  :maxdepth: 1

The Windows API, by default, has a `Maximum Path Length Limitation <https://docs.microsoft.com/en-us/windows/win32/fileio/maximum-file-path-limitation>`__ of 260 characters.
This limitation can cause problems when building SimpleITK using the Superbuild process.

For this reason we recommend placing SimpleITK's source and build directories at the
top of the file system.  For example, place the source code in :code:`C:\SimpleITK`
and set the build directory to be :code:`C:\SimpleITK-build`.


Trying to build SimpleITK with too long a path length will result in an error like so:

.. code-block::
   :emphasize-lines: 4-5

    CMake Error at CMakeLists.txt:109 (message):
      -- Configuring incomplete, errors occurred!
      See also "C:/Users/dchen/VeryVeryLongPathName/SimpleITK-build/ITK-build/CMakeFiles/CMakeOutput.log".
        ITK source code directory path length is too long (55 > 50).Please move the
        ITK source code directory to a directory with a shorter path.


    C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Microsoft\VC\v160\Microsoft.CppCommon.targets(238,5): error MSB8066: C
    ustom build for 'C:\Users\dchen\VeryVeryLongPathName\SimpleITK-build\CMakeFiles\49f9d16effa529c310c9be3182f62407\ITK-mkdir.rule;C:\Users\dch
    en\VeryVeryLongPathName\SimpleITK-build\CMakeFiles\49f9d16effa529c310c9be3182f62407\ITK-download.rule;C:\Users\dchen\VeryVeryLongPathName\Si
    mpleITK-build\CMakeFiles\49f9d16effa529c310c9be3182f62407\ITK-update.rule;C:\Users\dchen\VeryVeryLongPathName\SimpleITK-build\CMakeFiles\49f
    9d16effa529c310c9be3182f62407\ITK-patch.rule;C:\Users\dchen\VeryVeryLongPathName\SimpleITK-build\CMakeFiles\49f9d16effa529c310c9be3182f62407
    \ITK-configure.rule;C:\Users\dchen\VeryVeryLongPathName\SimpleITK-build\CMakeFiles\49f9d16effa529c310c9be3182f62407\ITK-build.rule;C:\Users\
    dchen\VeryVeryLongPathName\SimpleITK-build\CMakeFiles\49f9d16effa529c310c9be3182f62407\ITK-install.rule;C:\Users\dchen\VeryVeryLongPathName\
    SimpleITK-build\CMakeFiles\0cd4fd1b047c29b91c2ff7b21fd713a6\ITK-complete.rule;C:\Users\dchen\VeryVeryLongPathName\SimpleITK-build\CMakeFiles
    \ff9535a930f370e2434114c6e547ebba\ITK.rule' exited with code 1. [C:\Users\dchen\VeryVeryLongPathName\SimpleITK-build\ITK.vcxproj]


Building SimpleITK with long path names
---------------------------------------
If SimpleITK must be built with long path names, two things need to be done:

    1. `Enable Long Paths in Windows 10, Version 1607, and Layer <https://docs.microsoft.com/en-us/windows/win32/fileio/maximum-file-path-limitation?tabs=cmd#enable-long-paths-in-windows-10-version-1607-and-later>`__
    2.  Set the ITK_SKIP_PATH_LENGTH_CHECKS cmake variable to ON in the External_ITK.cmake


Enabling Long Paths in Windows
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
As described in `Microsoft's documentation <https://docs.microsoft.com/en-us/windows/win32/fileio/maximum-file-path-limitation?tabs=cmd#enable-long-paths-in-windows-10-version-1607-and-later>`__, Long path names are enabled in Windows by editing the registry with the following PowerShell command::

    New-ItemProperty -Path "HKLM:\SYSTEM\CurrentControlSet\Control\FileSystem" `-Name "LongPathsEnabled" -Value 1 -PropertyType DWORD -Force

The LongPathsEnabled property can also be edited using the Registry Editor app.

Setting ITK_SKIP_PATH_LENGTH_CHECKS
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Next ITK needs to be configured so that it does **NOT** check path lengths in the build
process.  To disable the path length check, we simply need to add the entry
ITK_SKIP_PATH_LENGTH_CHECKS to the CMake configuration, and set its value to ON.
We can do this in the CMake GUI when we configure our
:ref:`SimpleITK SuperBuild <building_windows>`.

After the initial configuration of the build, click on the "Add Entry" button, enter
ITK_SKIP_PATH_LENGTH_CHECKS for the name, and click the Value checkbox to turn set
the entry to ON.

.. image:: ../images/windowsPathLength.png
  :width: 400
  :alt: Setting ITK_SKIP_PATH_LENGTH_CHECKS in CMake

Now we can build ITK within the SimpleITK SuperBuild with long path names.
