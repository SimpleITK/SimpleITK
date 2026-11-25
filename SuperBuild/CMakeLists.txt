
#-----------------------------------------------------------------------------
# Override defaults set in initial "project" call, allow user to
# override from command line
#-----------------------------------------------------------------------------


# SimpleITK Addition: install to the common library
# directory, so that all libs/include etc ends up
# in one common tree
if( NOT DEFINED CMAKE_INSTALL_PREFIX )
  set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR} CACHE PATH "Where all the prerequisite libraries go")
endif()


include("${CMAKE_CURRENT_SOURCE_DIR}/../CMake/sitkCMakeInit.cmake")
cmake_minimum_required(VERSION ${SITK_CMAKE_MINIMUM_REQUIRED_VERSION}...${SITK_CMAKE_POLICY_VERSION})
project ( SuperBuildSimpleITK )


foreach(p "CMP0135"
    )
  if(POLICY ${p})
    cmake_policy(SET ${p} NEW)
  endif()
endforeach()

#-----------------------------------------------------------------------------
# CMAKE_CXX_COMPILER_ARG1 is a CMake internal variable. It should not be
# used in SimpleITK Superbuild's configuration as it will not get
# correctly propagated to external projects. If it is set, it most
# likely means that SimpleITK is to be built with a launcher such as
# ccache or distcc. This should be done with the CMake variable
# CMAKE_CXX_COMPILER_LAUNCHER_FLAG available in CMake > 3.4.0 .
if(CMAKE_CXX_COMPILER_ARG1)
  message(WARNING "The CMake variable CMAKE_CXX_COMPILER_ARG1 is\
set. The CMake variable CMAKE_CXX_COMPILER_LAUNCHER_FLAG should be used
instead (CMake>=3.4 required).")
endif()

#-----------------------------------------------------------------------------
# Superbuild script
#-----------------------------------------------------------------------------

# Actually run the super build script
set(${CMAKE_PROJECT_NAME}_DEPENDENCIES "") #Dependencies will be determined during superbuild stage.
include("${CMAKE_CURRENT_SOURCE_DIR}/SuperBuild.cmake")

# A plain `cmake --install <this-build-dir> --component Python` (what
# scikit-build-core does) would otherwise be a no-op: the inner SimpleITK
# ExternalProject's own install step runs as part of the outer `cmake
# --build`, not this outer project's own install(), and its Python
# install() rules are COMPONENT Python / EXCLUDE_FROM_ALL so its default
# (no-component) install step skips them anyway. Re-run `cmake --install`
# against the inner EP's build tree directly at outer-install time,
# targeting whatever prefix/config the outer install invocation uses.
# EXCLUDE_FROM_ALL keeps this out of a plain `cmake --install` with no
# --component, matching the inner install() rules it re-runs.
ExternalProject_Get_Property(SimpleITK BINARY_DIR)
install(
  CODE
    "execute_process(
  COMMAND \"${CMAKE_COMMAND}\" --install \"${BINARY_DIR}\"
          --config \"\${CMAKE_INSTALL_CONFIG_NAME}\"
          --prefix \"\${CMAKE_INSTALL_PREFIX}\"
          --component Python
)
"
  COMPONENT Python
  EXCLUDE_FROM_ALL
)


