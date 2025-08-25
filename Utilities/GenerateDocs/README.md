# SimpleITK Documentation Generation

This directory contains scripts used to process and generate documentation for SimpleITK.

## Overview

- Much of the SimpleITK documentation (Doxygen strings and API language docs) is derived from ITK's Doxygen.
- The process begins by running Doxygen on ITK to produce ITK Doxygen XML files. These can be generated locally or downloaded as nightly builds.
- Use the `GenerateDoc.py` script to extract documentation from the ITK Doxygen XML and update the SimpleITK YAML filter description files.
- When SimpleITK is built, the YAML files serve as the source for generating C++ code with embedded documentation.
- Building the SimpleITK Documentation target generates SimpleITK's own Doxygen XML files.
- The `SwigDocUpdate.sh` script can then be run to convert the SimpleITK Doxygen XML into Swig `.i` files, enabling inline documentation for some wrapped languages when SimpleITK is built.

## Building Documentation with Docker

A docker configuration is available in the `docker` subdirectory. It contains a Dockerfile and run scripts to build the documentation. Results are saved in the docker folder. The process is executed from the docker folder using a command like:

```bash
SIMPLEITK_GIT_TAG=v2.4.0 ./run.sh
```

Or to use another git repo:

```bash
SIMPLEITK_GIT_TAG=MyTestBranch SIMPLEITK_GIT_REPO=https://github.com/username/SimpleITK.git ./run.sh
```

### Testing Changes to Documentation Scripts

Testing changes to the documentation scripts can use the docker framework as follows:

1. Execute `run.sh` to create the appropriate container.
2. Enter the docker via the bash entry point, with environment variables specifying the appropriate repo and branch:

```bash
docker run -e _USER=$(id -un) -e _USERID=$(id -u) -e _GROUPID=$(id -g) \
  -e SIMPLEITK_GIT_TAG=v1.2.0 -e SIMPLEITK_GIT_REPO=https://github.com/username/SimpleITK.git \
  -v $(pwd):/work/io -ti --entrypoint /bin/bash simpleitk_doxygen
```

The bash entrypoint will place you in the `/tmp` directory. Run the documentation process using:

```bash
/work/bin/cmd.sh
```

This will check out SimpleITK and build the documents. You can change the documentation scripts for testing within the checked out copies.

## Building Documentation from SuperBuild

Building the documentation target from the SuperBuild framework requires:

- The correct cmake flags: `-DBUILD_DOXYGEN:BOOL=ON`
- Run `make SimpleITK-doc` after a SuperBuild config, or `make Documentation` in the SimpleITK-build directory.
- This will create the `SimpleITK-build/Documentation/xml` content.

## Important Scripts

- **`GenerateDoc.py`** - Updates the documentation of a SimpleITK class in its YAML file. Documentation is pulled from the corresponding ITK class XML file. This script replaces the old `JSONDocUpdate.sh` and now works with YAML only.
- **`SwigDocUpdate.sh`** - Copies SimpleITK Doxygen into Swig .i files and R .Rd files.

### Requirements

- `GenerateDoc.py` requires Python 3 and the `pyyaml` package.
- `SwigDocUpdate.sh` requires Python and the `regex` library. The regex library is required for a recursive regular expression used to match bracket pairs of mbox in LaTeX math. R documentation doesn't implement all LaTeX, and leaving the `\mbox` and `\text` fields causes problems when creating PDF versions of documentation in the package build process.

## Usage: GenerateDoc.py

Update one or more YAML filter description files with documentation from ITK Doxygen XML:

```bash
python3 GenerateDoc.py [options] <SimpleITKClass.yaml> [<SimpleITKClass2.yaml> ...]
```

- To specify the ITK Doxygen XML path, use:

```bash
python3 GenerateDoc.py --xml-path /path/to/itk-build/Documentation/xml MyFilter.yaml
```

- If `--xml-path` is not provided, the script will automatically download the latest ITK Doxygen XML from GitHub.

For more options, run:

```bash
python3 GenerateDoc.py --help
```

## Configuration

The `config_vars.sh` file needs to be manually modified for the system and build configuration.

These scripts are manually run to modify and create files in the source tree with the derived documentation.
