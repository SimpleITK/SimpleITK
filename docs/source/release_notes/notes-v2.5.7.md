# SimpleITK Release v2.5.7


To upgrade to this Python binary package run:
```pip install --upgrade --pre simpleitk --find-links https://github.com/SimpleITK/SimpleITK/releases/tag/v2.5.7```

## ITK 5.4.8
This distribution is based on the Insight Toolkit 5.4.8 release. Please see the [ITK release notes](https://docs.itk.org/en/release/releases/5.4.8.html) for details.

## Free-Threaded Python 3.15 Support
SimpleITK now packages wheels for free-threaded CPython 3.15 (`cp315t`) as a regular release, now that 3.15 is no longer a pre-release. CPython 3.15 changed how the GIL-free declaration must be made, from a runtime-only call to a static `Py_mod_gil` module slot, so building against it requires SWIG 4.5.1 or later, which this release updates to. Read more about [free-threaded Python on python.org](https://docs.python.org/3/howto/free-threading-python.html).

**New Features**
- Added `ImageFileReader::CanStreamRead()` to query whether the configured ImageIO supports streamed, region-by-region reading before attempting it.
- Added `Transform::ApplyToImageMetadata()`, updating an image's origin, spacing, and direction in place through the inverse of a transform, without resampling pixel data.

**Bug Fixes**
- Improved the numerical accuracy of `MultiLabelSTAPLEImageFilter` by computing weights in double instead of float precision.



**What's Changed**
* Bump pypa/gh-action-pypi-publish from 1.12.4 to 1.14.2 by @dependabot[bot] in https://github.com/SimpleITK/SimpleITK/pull/2668
* Bump actions/checkout from 4 to 7 by @dependabot[bot] in https://github.com/SimpleITK/SimpleITK/pull/2664
* Bump actions/upload-artifact from 4 to 7 by @dependabot[bot] in https://github.com/SimpleITK/SimpleITK/pull/2667
* Bump actions/download-artifact from 4 to 8 by @dependabot[bot] in https://github.com/SimpleITK/SimpleITK/pull/2666
* Bump actions/setup-python from 5 to 7 by @dependabot[bot] in https://github.com/SimpleITK/SimpleITK/pull/2665
* Bump actions/cache from 4 to 6 by @dependabot[bot] in https://github.com/SimpleITK/SimpleITK/pull/2669
* BUG: Fix free-threaded GIL declaration for CPython 3.15 (backport #2693) by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2695
* Backport #2691: Add packaging for Python 3.15t free-threaded pre-release by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2692
* CI: Use release-5.4 for ITK in batch build by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2674
* Update swig to 4.5.1 for release branch by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2675
* CI: Backport Package workflow hardening to release by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2724
* CI: Verify abi3 wheels with abi3audit (backport to release) by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2725
* BUG: Backport fix for broken commit-msg hook to release by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2733
* ENH: Add ImageFileReader::CanStreamRead to query streamed read support by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2730
* COMP: Update ITK to release-5.4 branch hash 2026-10-01 by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2734
* Backport PR #2670: Change TWeights in MultiLabelSTAPLE to double by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2673
* ENH: Add Transform::ApplyToImageMetadata by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2731
* COMP: Update ITK to release-5.4 branch hash 2026-10-12 by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2747
* CI: Package Python 3.15t as a regular release by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2753
* Build(deps): Bump pypa/gh-action-pypi-publish from 1.14.2 to 1.14.3 in the github-actions group by @dependabot[bot] in https://github.com/SimpleITK/SimpleITK/pull/2768
* ENH: Update ITK superbuild to v5.4.8 tag by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2776


**Full Changelog**: https://github.com/SimpleITK/SimpleITK/compare/v2.5.6...v2.5.7
