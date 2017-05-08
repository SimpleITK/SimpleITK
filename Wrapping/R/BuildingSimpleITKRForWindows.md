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
1. ninja

## Install MSYS2 64 bit

Fetch and run the [64 bit installer](http://www.msys2.org/)

## MSYS2 components

``` bash
pacman -S zip cmake git

```