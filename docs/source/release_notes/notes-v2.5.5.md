# SimpleITK Release v2.5.5

Announcing the SimpleITK 2.5.5 Release!

## Installing SimpleITK

Complete instructions on getting started with SimpleITK including downloading binaries or building SimpleITK can be found on the SimpleITK [Read the Docs web page](https://simpleitk.readthedocs.io/en/master/index.html).

# Release Highlights

## SimpleITK in R on the Windows operating system is finally available!
SimpleITK 2.5.5 is the first official release to support building SimpleITK with R wrapping for all major operating systems. It is recommended to use the [SimpleITKRInstaller](https://github.com/SimpleITK/SimpleITKRInstaller) to configure standard or custom builds without explicitly cloning the source code repository. Alternatively, R packages can be [built from the SimpleITK source code directly](https://simpleitk.readthedocs.io/en/latest/building.html) by turning the WRAP_R flag on in the CMake configuration and following the [R-specific installation instructions](https://simpleitk.readthedocs.io/en/latest/building.html#r-installation).

### Added Support for R 4.6.0

## Added Python Wheels for Free-Threaded CPython 3.14
In the ABI section of the wheel filename, the `t` in `cp314t` indicates support for free-threading.
The small `t` in the wheel filename is a significant change. The Global Interpreter Lock (GIL) is now optional in CPython ([PEP 703](https://peps.python.org/pep-0703/)). With this change, Python natively supports true multithreading, running threads in parallel on multi-core systems and not in a serial fashion managed by the GIL. Read more about [free-threaded Python on python.org](https://docs.python.org/3/howto/free-threading-python.html). While this change may affect your native Python code, and requires a compatible SimpleITK built wheel, the other wheels continue to unlock the GIL during ITK code execution for parallel processing.

## ITK 5.4.6
This distribution is based on the Insight Toolkit 5.4.6 release. Please see the [ITK release notes](https://docs.itk.org/en/release/releases/5.4.6.html) for details.



**What's Changed**
* ENH: Add free-threaded Python (3.14t) packaging support - for release by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2580
* ENH: Update macOS CI runner from macos-13 to macos-14 by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2584
* Fix R CLOENV - for release and master by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2585
* BUG: Patch SWIG superbuild for R 4.6.0 API removals by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2587


**Full Changelog**: https://github.com/SimpleITK/SimpleITK/compare/v2.5.4...v2.5.5
