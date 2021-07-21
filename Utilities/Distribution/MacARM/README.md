# SimpleITKMacARM

Scripts to build Python wheels for SimpleITK on Apple's ARM processor.

**build_all.sh** is the main script that does all the building.  It calls **mac_build_core.sh** to build the SimpleITK
C++ libraries.  Then it calls **mac_build_py.sh** twice, with the 3.8 and 3.9 arguments to build for the two
Python versions.  Those are the only versions of Python with installers available for Apple Silicon.

**mac_build_py.sh** is hard coded to use the Python installed by the Python.org installer.  So it's looking
for python in /Library/Frameworks/Python.Framework/Versions.
