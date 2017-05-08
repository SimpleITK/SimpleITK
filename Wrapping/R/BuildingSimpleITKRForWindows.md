# Building SimpleITK/R for Windows

The _RTools_ package supplies unix utilities and compilers that are
usually used to build R and packages. However these compilers are relatively
old and SimpleITK appears to break them. The symptoms are that linking
of test drivers and libraries tends to run for days without progress.

We've had success using the MSYS2 suite as an alternative.

The instructions below only build a 64bit version. Given the issues with
the code size and linking issues it appears likely that a 32bit version will
be more trouble than it is worth.

## Prerequisites

1. R
1. MSYS2

## Install R

[R](https://www.r-project.org/mirrors.html).

## Install MSYS2 64 bit

Fetch and run the [64 bit installer](http://www.msys2.org/).

Update the base system from the MSYS2 prompt:

``` bash
pacman -Syu
```

Close terminal, then reopen:

``` bash
pacman -Su
```

repeat a few times until everything appears stable.

## MSYS2 components

Select the "all" option (default).

``` bash
pacman -S zip git  base-devel mingw-w64-x86_64-ninja \
              mingw-w64-x86_64-toolchain \
              mingw-w64-x86_64-cmake \
              mingw-w64-x86_64-extra-cmake-modules \
              automake gcc-fortran


```

Add c:\\msys64\\mingw64\\bin to the user path (windows system settings) and restart terminal.

## Fetch SimpleITK

Note that sometimes there are errors resulting from long path names. This
may only relate to attempts to get things working with the R tools, but
safest not to tempt fate. Minimise the length of folder names:

``` bash
mkdir /c/S
cd /c/S
git clone https://github.com/SimpleITK/SimpleITK.git
## Create the build folder
mkdir B
cd B
```

Now configure with cmake

```bash
## some hacks to set up paths to R

RR=$(which R)
R64=$(dirname $RR)/x64/R.exe
R64DLL=$(dirname $R64)/R.dll

cmake -G Ninja ../SimpleITK/SuperBuild \
-DCMAKE_CXX_FLAGS="--param ggc-min-expand=0 --param ggc-min-heapsize=2648000" \
-DR_COMMAND=${R64} -DR_LIBRARY_BASE=${R64DLL} -DWRAP_R=ON

```
