#
# A CMake Module for finding Mono.
#
# The following variables are set:
#   CSHARP_MONO_FOUND
#   CSHARP_MONO_COMPILER_${version} eg. "CSHARP_MONO_COMPILER_v1.1"
#   CSHARP_MONO_INTERPRETOR_${version} eg. "CSHARP_MONO_INTERPRETOR_v1.1"
#   CSHARP_MONO_VERSION eg. "v4.0.30319"
#   CSHARP_MONO_VERSIONS eg. "v3.5, v4.0.30319"
#
# Additional references can be found here:
#   http://www.mono-project.com/Main_Page
#   http://www.mono-project.com/CSharp_Compiler
#
# This file is based on the work of GDCM:
#   http://gdcm.svn.sf.net/viewvc/gdcm/trunk/CMake/FindMono.cmake
# Copyright (c) 2006-2010 Mathieu Malaterre <mathieu.malaterre@gmail.com>
#

# TODO