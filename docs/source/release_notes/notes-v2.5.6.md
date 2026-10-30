# SimpleITK Release v2.5.6


To upgrade to this Python binary package run:
```pip install --upgrade --pre simpleitk --find-links https://github.com/SimpleITK/SimpleITK/releases/tag/v2.5.6```



**What's Changed**
* Use reshape over setting ndarray shape by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2611
* Update ITK version to 5.4.7 by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2649
* BUG: Remove copy=False kwarg from reshape in GetArrayViewFromImage by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2654
* CI: Migrate BatchBuild macOS jobs off deprecated macos-13 runner by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2653
* CI: Fix always-truthy if expression in BatchBuild.yml by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2658
* BUG: Pin numpy <2.5 for manylinux2014 python test venv by @blowekamp in https://github.com/SimpleITK/SimpleITK/pull/2659


**Full Changelog**: https://github.com/SimpleITK/SimpleITK/compare/v2.5.5...v2.5.6
