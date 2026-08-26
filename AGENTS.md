# SimpleITK Development Instructions

## Project Overview

SimpleITK is a layer for the Insight Toolkit (ITK) providing an accessible interface for medical image analysis. It has a core C++ library, and uses SWIG to provide language bindings for Python, Java, R, C# and others.


## Directory Structure

The SimpleITK repository is organized as follows:

- `Code/` — Library C++ source code and templates for filter and class generation.
  - `BasicFilters/yaml/` — YAML configuration files for filter code generation. For additional filter/API details, see the YAML file matching the filter name, e.g. `ResampleImageFilter.yaml`
  - `BasicFilters/templates/` — Jinja2 templates for code generation.
  - `Common/` - Core classes such as `Image` and transforms, template code, pixel types and typelists, with build target SimpleITKCommon
  - `ElastixTransformixWrappers/` - An optional feature for SimpleElastix.
  - `IO/` - Input/Output functionality for reading and writing images, with build target SimpleITKIO
  - `Registration/` - Image registration framework, with build target SimpleITKRegistration
- `Wrapping/` — SWIG-generated language binding code (Python, Java, R, C#, Lua, Ruby, Tcl).
- `ExpandTemplateGenerator/` — Python scripts for expanding templates and generating C++ code.
- `Utilities/` — Helper scripts and utilities for documentation and code maintenance.
- `Testing/` — CMake and test driver files for running unit and integration tests.
- `SuperBuild/` — An optional build root directory which incorporates all dependencies as CMake subprojects.
- `docs/` and `Documentation/` — Project documentation and guides.
- `CMake/` — CMake modules and helper scripts for the build system.
- `Examples/` — Example scripts and sample code for using SimpleITK.

The Schema for the YAML filter configuration is `ExpandTemplateGenerator/simpleitk_filter_description.schema.json`

This structure supports a code generation workflow, where YAML configuration files and Jinja2 templates are used to generate much of the C++ codebase and documentation.

## Development Workflow

### Git Workflow - Topic Branch Model
- DO NOT commit to the main branch.
- Branch names should be concise but descriptive (like function names)
- DO NOT push to the official repository.

### Steps to Create a PR
- Target branch `upstream/main` for features or `upstream/release` for backports.
- Create new topic branch based on targeted branch.
- Make concise commits, following the commit message standards.
- Push branches to the developer's forked remote.
- Create a pull request against the target branch.

### Commit Message Standards
Use these prefixes as needed:

BUG:    - fix for runtime crash or incorrect result
COMP:   - compiler error or warning fix
DOC:    - documentation change
ENH:    - new functionality
PERF:   - performance improvement
STYLE:  - no logic impact (indentation, comments)
CI:     - Changes in continuous integration, packaging and GitHubActions
WIP:    - Work In Progress not ready for merge

The first line should be <= 78 characters, followed by a blank line then a descriptive but concise summary of the changes.


## Build and Testing

The full compilation of SimpleITK and ITK is time consuming. Building specific targets can speed development.

### CMake Configuration and Build

Execute cmake from the source directory.
**Configure and build:**
```sh
cmake --preset PRESET_NAME && cmake --build --preset PRESET_NAME
```

**Build specific targets:**
```sh
cmake --build --preset PRESET_NAME --target TARGET_NAME
```

**Run tests:**
```sh
ctest --preset PRESET_NAME --output-on-failure
```

Use `default` as the default preset; inspect `CMakePresets.json` for other available presets.
