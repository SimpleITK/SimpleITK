#
# A CMake Module for finding and using C# (.NET and Mono).
#
# The following variables are set:
#   CSHARP_FOUND - set to true if C# is found
#   CSHARP_USE_FILE - the path to the C# use file
#   CSHARP_TYPE - the type of the C# compiler (eg. ".NET" or "Mono")
#   CSHARP_COMPILER - the path to the C# compiler executable (eg. "C:/Windows/Microsoft.NET/Framework/v4.0.30319/csc.exe")
#
# This file is based on the work of GDCM:
#   http://gdcm.svn.sf.net/viewvc/gdcm/trunk/CMake/FindCSharp.cmake
# Copyright (c) 2006-2010 Mathieu Malaterre <mathieu.malaterre@gmail.com>
#

# TODO: ADD ABILITY TO SELECT WHICH C# COMPILER eg. .NET or Mono (if both exist)

unset( CSHARP_COMPILER CACHE )
unset( CSHARP_TYPE CACHE )
unset( CSHARP_VERSION CACHE )

if( WIN32 )
  find_package( DotNetFrameworkSdk )
  # TODO Support Mono for Win32 systems
else( WIN32 )
  #TODO Support Mono for non-Win32 systems
  message( ERROR "C# wrapping for Mono is not supported (yet)" )
endif( WIN32 )

if( CSHARP_DOTNET_FOUND )
  set( CSHARP_TYPE ".NET" CACHE STRING "Using the .NET compiler" )
  set( CSHARP_COMPILER ${CSHARP_DOTNET_COMPILER_${CSHARP_DOTNET_VERSION}} CACHE STRING "Full path to .NET compiler" FORCE )
elseif( CSHARP_MONO_FOUND )
  set( CSHARP_TYPE "Mono" CACHE STRING "Using the Mono compiler" )
  set( CSHARP_COMPILER ${CSHARP_MONO_COMPILER_${CSHARP_MONO_VERSION}} CACHE STRING "Full path to Mono compiler" FORCE )
  #set( CSHARP_INTERPRETER ${CSHARP_MONO_INTERPRETOR_${CSHARP_MONO_VERSION}} CACHE STRING "Full path to Mono interpretor" )
endif( CSHARP_DOTNET_FOUND )

# Set the USE_FILE path
# http://public.kitware.com/Bug/view.php?id=7757
get_filename_component( current_list_path ${CMAKE_CURRENT_LIST_FILE} PATH )
set( CSHARP_USE_FILE ${current_list_path}/UseCSharp.cmake )
