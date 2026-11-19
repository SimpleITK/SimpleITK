

To upgrade to this Python binary package run:
```pip install --upgrade --pre simpleitk --find-links https://github.com/SimpleITK/SimpleITK/releases/tag/v2.5.8```


# Release Highlights

## Elastix Updated to 5.3.1
The optional Elastix SuperBuild dependency (`SimpleITK_USE_ELASTIX=ON`) is updated from 5.2.0 to 5.3.1, the latest release, which requires ITK >= 5.4.1 and is compatible with the ITK 5.4.8 used in this release. Elastix 5.3 renamed the "nonrigid" transform to "bspline"; SimpleITK's default parameter maps and documentation have been updated to match.

## New ProcessObject Thread Control API
Added `ProcessObject::SetMaximumNumberOfThreads` / `GetMaximumNumberOfThreads`, clarifying the existing `SetNumberOfThreads` / `GetNumberOfThreads` as equivalent aliases and documenting how the setting is interpreted by each ITK multi-threader backend (TBB, POOL, PLATFORM).

## Python 3.9 Support Removed
Python 3.9 has reached end-of-life and is no longer packaged in SimpleITK binary wheels.

## Packaging and Release Provenance
Release assets now include an attested `SHA256SUMS` manifest — see [Checking the SHA-256 Checksum](https://simpleitk.readthedocs.io/en/latest/gettingStarted.html#checking-the-sha-256-checksum) for how to verify a download. Final release tags now publish to PyPI via trusted publishing (OIDC) rather than a long-lived API token.

**Bug Fixes**
- Fixed setuptools deprecation warning by removing the license trove classifier in `setup.py` packaging template.

## What's Changed
* CI: Backport PyPI trusted publishing to release by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2780
* BUG: Remove deprecated license classifier from setup.py by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2791
* Backport #2777: Publish and attest release SHA-256 manifest by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2790
* CI: Remove packaging of EOL Python 3.9 by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2795
* Updated documentaiton to reflect new R distro. by @zivy in https://github.com/SimpleITK/SimpleITK/pull/2797
* ENH: Update Elastix to 5.3.1 by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2796
* ENH: Add ProcessObject Set/GetMaximumNumberOfThreads by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2800
* BUG: Ignore qualifiedname in doxy2swig Doxygen XML parsing by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2811
* DOC: Update Java docs from SimpleITK Doxygen by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2808
* DOC: Update R Rd documentation archive from SimpleITK Doxygen by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2809
* DOC: Update Python docstrings from SimpleITK Doxygen by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2807


**Full Changelog**: https://github.com/SimpleITK/SimpleITK/compare/v2.5.7...v2.5.8
