# PEP 803 abi3t Wheel Packaging Strategy

## Overview

SimpleITK now supports building Python wheels that are compatible with both GIL-enabled and free-threaded CPython 3.15+ using the **abi3.abi3t** combined tag (PEP 803 / PEP 793).

Per the [Python abi3t migration guide](https://docs.python.org/3.15/howto/abi3t-migration.html), a **single abi3 wheel** built from Python 3.15 works on all supported Python versions (3.11+), dramatically reducing build and distribution burden.

## Wheel Tags

### abi3 Wheel (GIL-enabled Python 3.11+)
- **Tag Format**: `cp315-abi3-<platform>`
- **Built From**: GIL-enabled CPython 3.15.x
- **Usage**: Works on any CPython 3.11, 3.12, 3.13, 3.14, 3.15 (and all future versions with stable ABI)
- **Build Count**: **ONE** per platform (not per Python version)

### abi3t Wheel (Free-threaded Python 3.15+)
- **Tag Format**: `cp315-abi3t-<platform>`
- **Built From**: Free-threaded CPython 3.15t.x (Py_GIL_DISABLED)
- **Usage**: Works on free-threaded CPython 3.15+ builds only
- **Build Count**: **ONE** per platform (only needed for 3.15t and future free-threaded versions)

### Combined Wheels (abi3.abi3t)
- **Tag Format**: `cp315-abi3.abi3t-<platform>`
- **Created**: By combining a single abi3 wheel with a single abi3t wheel
- **Usage**: Single wheel works on both GIL-enabled (3.11+) and free-threaded (3.15+) CPython
- **Benefit**: Maximum compatibility with minimal build overhead

## Build Infrastructure

### Docker Builds (Linux manylinux)

The manylinux CI/CD pipeline now:

1. **BUILD_PYTHON_LIMITED_API section**:
   - Builds abi3 wheel using **single version** Python 3.15 (GIL-enabled)
   - Builds abi3t wheel using **single version** Python 3.15t (free-threaded)
   - Both are produced from a single CI run

2. **PYTHON_VERSIONS loop**:
   - Builds version-specific wheels for Python 3.10, 3.14t (for tier 1 support)
   - Skips 3.15 and 3.15t (already handled in abi3/abi3t section)

Environment variables:
- `PYTHON_VERSIONS: "cp310-cp310 cp314-cp314t cp315-cp315 cp315t-cp315t"`
- `BUILD_PYTHON_LIMITED_API: 1`

### macOS & Windows Individual Builds

The GitHub Actions workflow (`Package.yml`) now:

1. **Tier 1 individual builds**:
   - Package Python 3.11 with `use_limited_api: true` → abi3 wheel
   - Package Python 3.10 (version-specific)
   - Package Python 3.14t (free-threaded, version-specific)

2. **abi3t test build**:
   - Package Python 3.15t with `use_limited_api: true` → validates abi3t support (continue-on-error due to SWIG blocker)

## Why This Works

Per PEP 384 (Stable ABI), when you compile with the limited API, you generate a wheel tagged `cp315-abi3-<platform>` that:

- Works identically on Python 3.11, 3.12, 3.13, 3.14, 3.15
- Avoids opaque type definitions and unstable internals
- Is compatible with all future Python versions

Similarly, when you compile with `Py_TARGET_ABI3T=1` on free-threaded Python 3.15t, you generate `cp315-abi3t-<platform>` that works on all future free-threaded builds.

Combined, a single `cp315-abi3.abi3t-<platform>.whl` covers:
- GIL-enabled: Python 3.11, 3.12, 3.13, 3.14, 3.15, 3.16, ...
- Free-threaded: Python 3.15t, 3.16t, ...

## scikit-build-core Integration

The build system uses **scikit-build-core 1.0+** which provides:

- **py-api overrides** in `pyproject.toml`:
  - Python ≥3.15: `py-api = "cp315.cp315t"` → when built with 3.15t, produces abi3t tag; when built with 3.15, produces abi3 tag
  - Python ≥3.11, <3.15: `py-api = "cp311"` → produces abi3 tag

- **Automatic detection**:
  - On GIL-enabled 3.15: scikit-build-core sets `Py_LIMITED_API` → produces `abi3` tag
  - On free-threaded 3.15t: scikit-build-core sets `Py_TARGET_ABI3T` → produces `abi3t` tag

## Configuration Files Modified

1. **.github/workflows/Package.yml**:
   - Updated `PYTHON_VERSIONS` to: `"cp310-cp310 cp314-cp314t cp315-cp315 cp315t-cp315t"`
   - Removed redundant 3.11, 3.12, 3.13 individual builds (covered by single abi3 build)
   - Added single Python 3.15t package step for abi3t testing

2. **Utilities/Distribution/manylinux/imagefiles/cmd.sh**:
   - Updated abi3 build section to build **only 3.15 and 3.15t** (not per-version)
   - Added conditional skipping of 3.15/3.15t in main loop to prevent duplication
   - Reduced total builds from 8+ per platform to 4 per platform

3. **pyproject.toml** (in prior commits):
   - Updated to scikit-build-core `~=1.0.0`
   - Added py-api overrides for abi3 and abi3t support
   - Requires CMake ≥3.30

## Known Limitations

⚠️ **SWIG Support Blocker**:
- Full abi3t compilation is currently blocked by SWIG 4.5.0's lack of `PyModExport` support (PEP 793)
- See [PR #2681](https://github.com/SimpleITK/SimpleITK/pull/2681) for blocker details
- A `sitkPyModExport.cxx` shim is available but wrapper code needs porting to opaque types

## Local Testing

To build abi3t wheels locally:

```bash
# Create a Python 3.15t venv using uv
uv venv -p 3.15t .venv-3.15t
source .venv-3.15t/bin/activate

# Install build dependencies
uv pip install scikit-build-core>=1.0.0 cmake

# Build wheels (will hit SWIG blocker currently)
uv build --wheel
```

The resulting `.whl` file will have the `abi3t` tag when the build succeeds.

## Wheel Distribution

Once abi3t support is complete, users can:

```bash
# Install SimpleITK on Python 3.15 (GIL-enabled)
pip install simpleitk

# Install SimpleITK on Python 3.15t (free-threaded)
pip install simpleitk  # Same wheel works!
```

A single `cp315-abi3.abi3t-<platform>.whl` works on both Python 3.15 (GIL) and 3.15t (free-threaded) interpreters, plus all earlier versions via the abi3 tag.

## References

- [PEP 793 - PyModExport](https://peps.python.org/pep-0793/)
- [PEP 803 - Free-Threaded Stable ABI](https://peps.python.org/pep-0803/)
- [PEP 384 - Stable ABI](https://peps.python.org/pep-0384/)
- [Python abi3t Migration Guide](https://docs.python.org/3.15/howto/abi3t-migration.html)
