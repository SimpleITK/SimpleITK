# PEP 803 abi3t Wheel Packaging Strategy

## Overview

SimpleITK now supports building Python wheels that are compatible with both GIL-enabled and free-threaded CPython 3.15+ using the **abi3.abi3t** combined tag (PEP 803 / PEP 793).

The full target wheel matrix consists of four builds:

1. **cp310-cp310** — legacy, version-pinned build for the oldest supported Python (3.10, predates the Stable ABI floor used here)
2. **cp311-abi3** — classic Stable ABI wheel, built once with the minimum supported abi3 version (Python 3.11)
3. **cp314-cp314t** — interim, version-pinned free-threaded build for Python 3.14 (abi3t does not exist before 3.15)
4. **cp315-abi3.abi3t** — combined Stable ABI wheel, built once with the free-threaded Python 3.15t interpreter

## Wheel Tags

### abi3 Wheel (GIL-enabled Python 3.11+)
- **Tag Format**: `cp311-abi3-<platform>`
- **Built From**: GIL-enabled CPython 3.11.x (the minimum supported Stable ABI version)
- **Usage**: Works on any CPython 3.11, 3.12, 3.13, 3.14, 3.15 (and all future versions with stable ABI)
- **Build Count**: **ONE** per platform (not per Python version)

### abi3t Wheel (Free-threaded Python 3.15+)
- **Tag Format**: `cp315-abi3t-<platform>` (reported as the combined `abi3.abi3t` tag by scikit-build-core)
- **Built From**: Free-threaded CPython 3.15t.x (Py_GIL_DISABLED)
- **Usage**: Works on both free-threaded *and* GIL-enabled CPython 3.15+ builds
- **Build Count**: **ONE** per platform (only needed for 3.15t and future free-threaded versions)

### Combined Wheels (abi3.abi3t)
- **Tag Format**: `cp315-abi3.abi3t-<platform>`
- **Created**: By building once with the free-threaded 3.15t interpreter while targeting both `Py_LIMITED_API` and `Py_TARGET_ABI3T`
- **Usage**: Single wheel works on both GIL-enabled and free-threaded Python 3.15+
- **Benefit**: No separate "abi3 at 3.15" build is needed — the classic `cp311-abi3` wheel already covers GIL-enabled 3.15, and the abi3t wheel additionally covers free-threaded 3.15+

## Build Infrastructure

### Docker Builds (Linux manylinux)

The manylinux CI/CD pipeline now:

1. **BUILD_PYTHON_LIMITED_API section**:
   - Builds the classic abi3 wheel using **Python 3.11** (the minimum supported Stable ABI version — matches the mac/Windows packaging path)
   - Builds the abi3t wheel using **Python 3.15t** (free-threaded), with both `SimpleITK_PYTHON_USE_LIMITED_API` and `SimpleITK_PYTHON_USE_ABI3T` set
   - Both are produced from a single CI run

2. **PYTHON_VERSIONS loop**:
   - Builds version-specific wheels for Python 3.10, 3.14t (for tier 1 support)
   - Skips `cp311-cp311` and `cp315-cp315t` (already handled in the abi3/abi3t section above)

Environment variables:
- `PYTHON_VERSIONS: "cp310-cp310 cp314-cp314t cp315-cp315t"`
- `BUILD_PYTHON_LIMITED_API: 1`

### macOS & Windows Individual Builds

The GitHub Actions workflow (`Package.yml`) packages:

1. **Package Python 3.11** with `use_limited_api: true` → `cp311-abi3` wheel
2. **Package Python 3.10** (legacy, version-specific)
3. **Package Python 3.14t** (interim free-threaded, version-specific, continue-on-error)
4. **Package Python 3.15t** with `use_limited_api: true` → `cp315-abi3.abi3t` wheel (continue-on-error, currently blocked — see below)

## Why This Works

Per PEP 384 (Stable ABI), when you compile with the limited API using the *minimum* supported Python version (3.11), you generate a wheel tagged `cp311-abi3-<platform>` that:

- Works identically on Python 3.11, 3.12, 3.13, 3.14, 3.15, and later
- Avoids opaque type definitions and unstable internals
- Is compatible with all future Python versions

There is no need to also build a plain "abi3" wheel at 3.15 — the `cp311-abi3` wheel already covers GIL-enabled 3.15 (and beyond).

Separately, when you compile with `Py_TARGET_ABI3T` using the free-threaded Python 3.15t interpreter, you generate a wheel with the combined `abi3.abi3t` tag that works on:

- GIL-enabled: Python 3.15, 3.16, ... (redundant with, but not conflicting with, the `cp311-abi3` wheel)
- Free-threaded: Python 3.15t, 3.16t, ...

So the two builds (`cp311-abi3` and `cp315-abi3.abi3t`) are complementary, not overlapping in purpose: the first extends compatibility as far back as possible, the second extends it to free-threaded interpreters.

## scikit-build-core Integration

The build system uses **scikit-build-core 1.0+** which provides:

- **py-api overrides** in `pyproject.toml`:
  - Python ≥3.15: `py-api = "cp315.cp315t"` → when built with the free-threaded 3.15t interpreter, produces the combined `abi3.abi3t` tag
  - Python ≥3.11, <3.15: `py-api = "cp311"` → produces the classic `abi3` tag

- **Automatic detection**:
  - On free-threaded 3.15t: scikit-build-core sets `Py_TARGET_ABI3T` → produces the combined `abi3.abi3t` tag
  - Otherwise (GIL-enabled ≥3.11): produces the classic `abi3` tag

The non-scikit-build-core packaging paths (`mac_build_python.sh`, `win_build_python.sh`, and the manylinux `cmd.sh`) configure Wrapping/Python directly via CMake first; that outer configure must be told explicitly which mode to use via `-DSimpleITK_PYTHON_USE_LIMITED_API` and `-DSimpleITK_PYTHON_USE_ABI3T`, since those CMake options default to `OFF` outside of scikit-build-core. The outer build then generates a `pyproject.toml` with the matching `wheel.py-api` value and invokes `pip wheel` on it, which drives a nested scikit-build-core build to actually produce the wheel.

## Configuration Files Modified

1. **.github/workflows/Package.yml**:
   - `PYTHON_VERSIONS` (Docker/manylinux path): `"cp310-cp310 cp314-cp314t cp315-cp315t"`
   - Individual macOS/Windows steps: Python 3.11 (abi3), 3.10 (legacy), 3.14t (interim), 3.15t (abi3.abi3t)

2. **.github/actions/package_python/action.yml** and its `mac_build_python.sh` / `win_build_python.sh` scripts:
   - Propagate `SimpleITK_PYTHON_USE_ABI3T=ON` to CMake whenever `use_limited_api` is requested with a free-threaded interpreter

3. **Utilities/Distribution/manylinux/imagefiles/cmd.sh**:
   - `BUILD_PYTHON_LIMITED_API` block builds `cp311-cp311` (classic abi3) and `cp315-cp315t` (abi3t), each with an explicit `ABI_SUFFIX` and the correct `SimpleITK_PYTHON_USE_ABI3T` flag
   - Main `PYTHON_VERSIONS` loop skips `cp311-cp311` and `cp315-cp315t` to avoid duplicate builds

4. **Wrapping/Python/CMakeLists.txt**:
   - `SITK_PYTHON_ABI_VER_HEX` computed arithmetically (not by string concatenation) so it is correct for every minor version
   - `wheel.py-api` in the generated `pyproject.toml` computed dynamically from the actual interpreter's minor version (and abi3t-aware), instead of a hardcoded `"cp311"`

5. **pyproject.toml** (top level, in prior commits):
   - Updated to scikit-build-core `~=1.0.0`
   - Added py-api overrides for abi3 and abi3t support
   - Requires CMake ≥3.30

## Known Limitations

⚠️ **SWIG Support Blocker**:
- Full abi3t compilation is currently blocked by SWIG 4.5.0's lack of `PyModExport` support (PEP 793)
- See [PR #2681](https://github.com/SimpleITK/SimpleITK/pull/2681) for blocker details
- A `sitkPyModExport.cxx` shim is available but wrapper code (SWIG-generated code and `sitkImageBuffer.cxx`) needs porting away from opaque CPython internals first
- CI's `cp315-abi3.abi3t` build step is marked `continue-on-error` until this is resolved

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

The resulting `.whl` file will have the combined `abi3.abi3t` tag when the build succeeds.

## Wheel Distribution

Once abi3t support is complete, users can:

```bash
# Install SimpleITK on Python 3.15 (GIL-enabled)
pip install simpleitk

# Install SimpleITK on Python 3.15t (free-threaded)
pip install simpleitk  # Same wheel works!
```

A single `cp315-abi3.abi3t-<platform>.whl` works on both Python 3.15 (GIL) and 3.15t (free-threaded) interpreters. Earlier GIL-enabled versions (3.11-3.14) are served by the separate `cp311-abi3` wheel.

## References

- [PEP 793 - PyModExport](https://peps.python.org/pep-0793/)
- [PEP 803 - Free-Threaded Stable ABI](https://peps.python.org/pep-0803/)
- [PEP 384 - Stable ABI](https://peps.python.org/pep-0384/)
- [Python abi3t Migration Guide](https://docs.python.org/3.15/howto/abi3t-migration.html)
