#
# A CMake Module for finding C# .NET.
#
# The following variables are set:
#   CSHARP_DOTNET_FOUND
#   CSHARP_DOTNET_COMPILER_${version} eg. "CSHARP_DOTNET_COMPILER_v4.0.30319"
#   CSHARP_DOTNET_VERSION eg. "v4.0.30319"
#   CSHARP_DOTNET_VERSIONS eg. "v3.5, v4.0.30319"
#   DotNetFrameworkSdk_USE_FILE
#
# Additional references can be found here:
#   .NET SDK 1.1: http://www.microsoft.com/downloads/details.aspx?FamilyID=9b3a2ca6-3647-4070-9f41-a333c6b9181d&displaylang=en
#   .NET SDK 2.0: http://www.microsoft.com/downloads/details.aspx?FamilyID=fe6f2099-b7b4-4f47-a244-c96d69c35dec&displaylang=en
#   .NET SDK 3.5: http://www.microsoft.com/downloads/details.aspx?familyid=333325fd-ae52-4e35-b531-508d977d32a6&displaylang=en
#   C# Compiler options: http://msdn.microsoft.com/en-us/library/2fdbz5xd(v=VS.71).aspx
#
# This file is based on the work of GDCM:
#   http://gdcm.svn.sf.net/viewvc/gdcm/trunk/CMake/FindDotNETFrameworkSDK.cmake
# Copyright (c) 2006-2010 Mathieu Malaterre <mathieu.malaterre@gmail.com>
#

set( csharp_dotnet_valid 1 )
if( DEFINED CSHARP_DOTNET_FOUND )
  # The .NET compiler has already been found
  # It may have been reset by the user, verify it is correct
  if( NOT DEFINED CSHARP_DOTNET_COMPILER_${CSHARP_DOTNET_VERSION} )
    set( csharp_dotnet_version_user ${CSHARP_DOTNET_VERSION} )
    set( csharp_dotnet_valid 0 )
    set( CSHARP_DOTNET_FOUND 0 )
    set( CSHARP_DOTNET_VERSION "CSHARP_DOTNET_VERSION-NOTVALID" CACHE STRING "C# .NET compiler version, choices: ${CSHARP_DOTNET_VERSIONS}" FORCE )
    message( FATAL_ERROR "The C# .NET version '${csharp_dotnet_version_user}' is not valid. Please enter one of the following: ${CSHARP_DOTNET_VERSIONS}" )
  endif( NOT DEFINED CSHARP_DOTNET_COMPILER_${CSHARP_DOTNET_VERSION} )
endif( DEFINED CSHARP_DOTNET_FOUND )

unset( CSHARP_DOTNET_VERSIONS CACHE ) # Clear versions
set( csharp_dotnet_framework_dir "$ENV{windir}/Microsoft.NET/Framework" )
string( REPLACE "\\" "/" csharp_dotnet_framework_dir ${csharp_dotnet_framework_dir} )
file( GLOB_RECURSE csharp_dotnet_executables "${csharp_dotnet_framework_dir}/csc.exe" )
list( SORT csharp_dotnet_executables )
list( REVERSE csharp_dotnet_executables )
foreach ( csharp_dotnet_executable ${csharp_dotnet_executables} )
  if( csharp_dotnet_valid )
    # Extract version number (eg. v4.0.30319)
    # TODO: Consider using REGEX
    string( REPLACE "${csharp_dotnet_framework_dir}/" "" csharp_dotnet_version_temp ${csharp_dotnet_executable} )
    string( REPLACE "/csc.exe" "" csharp_dotnet_version_temp ${csharp_dotnet_version_temp} )
    set( CSHARP_DOTNET_VERSION ${csharp_dotnet_version_temp} CACHE STRING ".NET C# compiler version" )
    mark_as_advanced( CSHARP_DOTNET_VERSION )

    # Add variable holding executable
    set( CSHARP_DOTNET_COMPILER_${csharp_dotnet_version_temp} ${csharp_dotnet_executable} CACHE STRING ".NET C# compiler ${csharp_dotnet_version}" FORCE )
    mark_as_advanced( CSHARP_DOTNET_COMPILER_${csharp_dotnet_version_temp} )
  endif( csharp_dotnet_valid )
  
  # Create a list of supported compiler versions
  if( NOT DEFINED CSHARP_DOTNET_VERSIONS )
    set( CSHARP_DOTNET_VERSIONS "${csharp_dotnet_version_temp}" CACHE STRING "Available C# .NET compiler versions" FORCE )
  else( NOT DEFINED CSHARP_DOTNET_VERSIONS )
    set( CSHARP_DOTNET_VERSIONS "${CSHARP_DOTNET_VERSIONS}, ${csharp_dotnet_version_temp}"  CACHE STRING "Available C# .NET compiler versions" FORCE )
  endif( NOT DEFINED CSHARP_DOTNET_VERSIONS )
  mark_as_advanced( CSHARP_DOTNET_VERSIONS )

  # We found at least one .NET compiler version
  set( CSHARP_DOTNET_FOUND 1 CACHE INTERNAL "Boolean indicating if C# .NET was found" )
endforeach( csharp_dotnet_executable )

if( CSHARP_DOTNET_FOUND )
  # Report the found versions
  message( STATUS "Found the following C# .NET compiler versions: ${CSHARP_DOTNET_VERSIONS}" )
endif( CSHARP_DOTNET_FOUND )

# Set USE_FILE
get_filename_component( current_list_path ${CMAKE_CURRENT_LIST_FILE} PATH )
set( DotNetFrameworkSdk_USE_FILE ${current_list_path}/UseDotNetFrameworkSdk.cmake )
