# SimpleITK Release v3.0.0b1

**Announcing the SimpleITK 3.0.0b1 Beta Release!**

This beta release is a major milestone for SimpleITK 3.0, featuring new functionality and improvements including experimental integration of SimpleElastix into the binary distributions.

## Installing SimpleITK

Complete instructions on getting started with SimpleITK including downloading binaries or building SimpleITK can be found on the SimpleITK [Read the Docs web page](https://simpleitk.readthedocs.io/en/master/index.html).

### Python Binary Downloads

Python binary wheels are available for download. To install this beta release from Test PyPI or the GitHub release page:

**From Test PyPI:**
```
python -m pip install --upgrade pip
python -m pip install --pre --index-url https://test.pypi.org/simple/ --extra-index-url https://pypi.org/simple/ SimpleITK
```

Note: Due to space limitation on Test PyPI, published releases are not kept long term on the test distribution hub.

**From GitHub release page:**
```pip install --upgrade --pre simpleitk --find-links https://github.com/SimpleITK/SimpleITK/releases/tag/v3.0.0b1```

The binary distribution contains wheels built on the Python 3.11 stable API (see [PEP 384](https://peps.python.org/pep-0384/)) and should work with Python versions 3.11 and later. Additionally, this release provides wheels specifically for Python 3.10 and free-threaded Python 3.14t.

### Getting Started

To get started with pre-compiled Java or C# bindings, building the R binding, or building SimpleITK from source code, see the [Getting Started Guide](https://simpleitk.readthedocs.io/en/main/gettingStarted.html).

# Release Highlights

## 🎉 SimpleElastix Now Included in Binary Distributions!

As an experiment, **SimpleElastix is included in SimpleITK binary distributions**! Previously, SimpleElastix required building SimpleITK from source with special flags. This major enhancement brings powerful image registration capabilities to all users without needing custom builds.

SimpleElastix provides access to the elastix registration framework, enabling advanced deformable image registration directly through SimpleITK's `ElastixImageFilter` and `TransformixImageFilter` classes. A key advantage of elastix is its [parameter zoo](https://lkeb.ml/modelzoo/) - a curated collection of turnkey parameter settings for various registration scenarios, from simple rigid alignment to complex multi-modal deformable registration. This makes SimpleElastix particularly valuable for medical image analysis, image alignment, and multi-modal registration tasks without requiring extensive parameter tuning expertise.

## SimpleITK in R for Windows!

SimpleITK 3.0.0b1 continues support for building SimpleITK with R wrapping for all major operating systems, including Windows. It is recommended to use the [SimpleITKRInstaller](https://github.com/SimpleITK/SimpleITKRInstaller) to configure standard or custom builds. This release adds support for the new R 4.6.0.

## Free-Threaded Python 3.14 Support

This release includes **Python wheels for free-threaded CPython 3.14** (`cp314t` in wheel filenames). The Global Interpreter Lock (GIL) is now optional in CPython ([PEP 703](https://peps.python.org/pep-0703/)), enabling true parallel multithreading on multi-core systems. SimpleITK has been updated to declare the Python module as GIL-free for compatibility with free-threaded CPython.

While this change affects native Python code and requires compatible wheels, standard Python wheels continue to unlock the GIL during ITK code execution for parallel processing. Read more about [free-threaded Python on python.org](https://docs.python.org/3/howto/free-threading-python.html).

## ITK 5.4.6

This distribution is based on the Insight Toolkit 5.4.6 release. Please see the ITK release notes for details.


## Migration Guide for Version 3.0

A comprehensive [migration guide](https://simpleitk.readthedocs.io/en/main/migration_guides/migrationGuide3.0.html) is now available to help users transition from SimpleITK 2.x to 3.0.

## What's Changed
* Align Elastix/Transformix API with elastix PR #417 by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2526
* Remove outdated cdash exceptions for warnings and errors by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2528
* Use additional PR branch name in ccache key by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2529
* DOC: Update Sphinx docs for v3.0.0a3 changes by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2530
* Add migration guide for version 3.0 by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2533
* DOC: Add release notes and update documentation infrastructure by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2534
* COMP: Update ITK to release-5.4 branch hash 2026-02-26 by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2535
* Add myst_parser to Sphinx Docs requirements by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2537
* DOC: Update requirements and ReadTheDocs config by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2538
* Separately backport gersemi CMake formatting for FindR.cmake by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2541
* Update FindR to detect R.dll on windows. by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2542
* Update Elastix to Superbuild 5.3.1 by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2540
* Coverage image by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2532
* Update FindR to detect R.dll on windows. - for release by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2546
* DOC: Update phrasing in documentation. by @zivy in https://github.com/SimpleITK/SimpleITK/pull/2548
* Merge ElastixImageFilter and TransformixImageFilter into SimpleElastix by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2547
* Add GHA batch builds which use fetch content by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2545
* DOC: Add FAQ entry for Windows pip build path length error by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2551
* BUG: Replace deprecated macos-13 runner with macos-15-intel by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2553
* Create an Elastix FetchContent build option by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2543
* Release into main by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2554
* Remove manylinux 2014. by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2559
* Update elastix to af47e22, and use target based properties by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2558
* Fix continue-on-error in composite actions to use boolean expression by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2557
* Bump pypa/gh-action-pypi-publish from 1.13.0 to 1.14.0 by @dependabot[bot] in https://github.com/SimpleITK/SimpleITK/pull/2560
* ENH: Add free-threaded Python 3.14t package builds by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2552
* Enable SimpleElastix in doxygen build by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2562
* Package with elastix by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2555
* Declare Python module as GIL-free for free-threaded CPython by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2565
* Update actions/setup-python from v5 to v6 by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2567
* SWIG use doxygen flag for automatic docs by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2566
* Update ITK Superbuild version to 5.4.6 by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2570
* COMP: Link ITKRegistrationCommonModule for elastix pyramid headers by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2569
* DOC: Add release notes for v2.5.4 by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2571
* ENH: Use file glob for external data cache key in GHA workflows by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2572
* ENH: Simplify ccache key in Build.yml GHA workflow by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2573
* GHA: Pin R version to 4.5 by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2575
* Update Superbuild SWIG to 4.4.1 by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2577
* COMP: Remove KWStyle style checking by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2578
* ENH: Fix free-threaded Python linking with CMake >= 3.30 by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2581
* ENH: Add free-threaded Python (3.14t) packaging support - for release by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2580
* BUG: Remove duplicate Python packaging steps in Package workflow by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2582
* ENH: Update macOS CI runner from macos-13 to macos-14 by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2584
* Fix R CLOENV - for release and master by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2585
* BUG: Patch SWIG superbuild for R 4.6.0 API removals by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2587
* BUG: Patch SWIG superbuild for R 4.6.0 API removals - for main by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2589
* ENH: Add R wrapping CI coverage to Build and BatchBuild workflows by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2586
* BUG: Fix DicomSeriesReader test for ITK PR#5357 direction fix by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2591
* DOC: Add release notes for v2.5.5 by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2592
* DOC: Expand v2.5.5 release notes with highlights and installation ins… by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2594
* GHA packaging use mac-15 ARM by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2595
* ci: harden Package workflow against supply-chain and injection risks by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2596


**Full Changelog**: https://github.com/SimpleITK/SimpleITK/compare/v3.0.0a3...v3.0.0b1
