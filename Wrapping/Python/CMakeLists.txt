include("${CMAKE_CURRENT_SOURCE_DIR}/../../CMake/sitkCMakeInit.cmake")
cmake_minimum_required(
  VERSION ${SITK_CMAKE_MINIMUM_REQUIRED_VERSION}...${SITK_CMAKE_POLICY_VERSION}
)

project(SimpleITK_Python)

include(../../CMake/sitkProjectLanguageCommon.cmake NO_POLICY_SCOPE)

find_package(
  Python
  REQUIRED
  COMPONENTS
    Interpreter
    Development.Module
  OPTIONAL_COMPONENTS
    Development.SABIModule
)

include_directories(
  ${SimpleITK_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}
)

#
# Options
#
option(
  SimpleITK_PYTHON_FLATSTATICMETHOD
  "Enable object_method functions for static class members. \
This feature will be removed in the future. To disable requires SWIG>=4.1.0"
  ON
)
option(
  SimpleITK_PYTHON_THREADS
  "Enable threaded python usage by unlocking the GIL."
  ON
)
mark_as_advanced(SimpleITK_PYTHON_THREADS)
if(SimpleITK_PYTHON_EGG)
  message(
    WARNING
    "SimpleITK_PYTHON_EGG option is deprecated and no longer used."
  )
endif()
option(
  SimpleITK_PYTHON_WHEEL
  "Add building of python wheels to the dist target."
  ON
)
mark_as_advanced(SimpleITK_PYTHON_WHEEL)

if(
  CMAKE_VERSION
    VERSION_GREATER_EQUAL
    "3.26"
  AND
    SWIG_VERSION
      VERSION_GREATER_EQUAL
      "4.2.0"
  AND
    Python_VERSION
      VERSION_GREATER_EQUAL
      "3.11.0"
)
  set(_SimpleITK_PYTHON_USE_LIMITED_API_DEFAULT ON)
else()
  set(_SimpleITK_PYTHON_USE_LIMITED_API_DEFAULT OFF)
endif()
option(
  SimpleITK_PYTHON_USE_LIMITED_API
  "Use Python limited API, for minor version compatibility."
  ${_SimpleITK_PYTHON_USE_LIMITED_API_DEFAULT}
)
mark_as_advanced(SimpleITK_PYTHON_USE_LIMITED_API)

if(SimpleITK_PYTHON_USE_LIMITED_API)
  find_package(
    Python
    REQUIRED
    COMPONENTS
      Interpreter
      Development.SABIModule
  )
endif()

if(
  SimpleITK_PYTHON_USE_LIMITED_API
  AND
    NOT
      _SimpleITK_PYTHON_USE_LIMITED_API_DEFAULT
)
  message(WARNING "SWIG_VERSION (>=4.2.0): ${SWIG_VERSION}")
  message(WARNING "Python_VERSION (>=3.11.0): ${Python_VERSION}")
  message(WARNING "CMAKE_VERSION (>=3.26): ${CMAKE_VERSION}")
  message(
    WARNING
    "Development.SABIModule_FOUND: ${Development.SABIModule_FOUND}"
  )
  message(
    FATAL_ERROR
    "Python limited API is not supported for this Python version and SWIG version."
  )
  set(SimpleITK_PYTHON_USE_LIMITED_API OFF)
endif()

set_source_files_properties(
  SimpleITK.i
  PROPERTIES
    CPLUSPLUS
      ON
)

# Run swig
set(
  CMAKE_SWIG_FLAGS
  ${CMAKE_SWIG_GLOBAL_FLAGS}
  -features
  autodoc=1
  -keyword
)
if(SimpleITK_PYTHON_THREADS)
  set(
    CMAKE_SWIG_FLAGS
    ${CMAKE_SWIG_FLAGS}
    -threads
  )
endif()
if(
  SimpleITK_PYTHON_FLATSTATICMETHOD
  AND
    SWIG_VERSION
      VERSION_GREATER_EQUAL
      "4.1.0"
)
  set(
    CMAKE_SWIG_FLAGS
    ${CMAKE_SWIG_FLAGS}
    -flatstaticmethod
  )
endif()
set(CMAKE_SWIG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR}/SimpleITK)
set(
  SWIG_MODULE_SimpleITK_EXTRA_DEPS
  ${SWIG_EXTRA_DEPS}
  ${CMAKE_CURRENT_SOURCE_DIR}/Python.i
  ${CMAKE_CURRENT_SOURCE_DIR}/sitkImage.i
  ${CMAKE_CURRENT_SOURCE_DIR}/sitkTransform.i
  ${CMAKE_CURRENT_SOURCE_DIR}/sitkPathType.i
)
swig_add_module( SimpleITK python
  SimpleITK.i
  sitkPyCommand.cxx
  sitkImageBuffer.cxx
)
set(
  SWIG_MODULE_SimpleITKPython_TARGET_NAME
  "${SWIG_MODULE_SimpleITK_TARGET_NAME}"
)
target_link_libraries(
  ${SWIG_MODULE_SimpleITKPython_TARGET_NAME}
  ${SimpleITK_LIBRARIES}
)
if(NOT Python_DEBUG_LIBRARY AND MSVC)
  # If there is not a specified debug library use the release library,
  # via a special sitkPython.h header.
  target_compile_definitions(
    ${SWIG_MODULE_SimpleITKPython_TARGET_NAME}
    PRIVATE
      $<$<CONFIG:Debug>:SWIG_PYTHON_INTERPRETER_NO_DEBUG>
  )
endif()

get_property(
  _suffix
  TARGET ${SWIG_MODULE_SimpleITKPython_TARGET_NAME}
  PROPERTY SUFFIX
)
if(NOT _suffix)
  set(_suffix "${CMAKE_SHARED_MODULE_SUFFIX}")
endif()
if(SimpleITK_PYTHON_USE_LIMITED_API)
  # https://docs.python.org/3/c-api/stable.html

  sitk_target_link_libraries_with_dynamic_lookup( ${SWIG_MODULE_SimpleITKPython_TARGET_NAME} Python::SABIModule)
  target_compile_definitions(
    ${SWIG_MODULE_SimpleITKPython_TARGET_NAME}
    PRIVATE
      -DPy_LIMITED_API=0x030b0000
  )

  message(
    STATUS
    "Setting limited ABI suffix for Python module to: '${Python_SOSABI}${_suffix}' libraries: ${Python_LIBRARIES}"
  )
  if(NOT Python_SOSABI STREQUAL "")
    set_property(
      TARGET
        ${SWIG_MODULE_SimpleITKPython_TARGET_NAME}
      PROPERTY
        SUFFIX
          ".${Python_SOSABI}${_suffix}"
    )
  endif()
else()
  sitk_target_link_libraries_with_dynamic_lookup( ${SWIG_MODULE_SimpleITKPython_TARGET_NAME} Python::Module)
  message(
    STATUS
    "Setting ABI suffix for Python module to: '${Python_SOABI}${_suffix}' "
  )
  if(NOT Python_SOABI STREQUAL "")
    set_property(
      TARGET
        ${SWIG_MODULE_SimpleITKPython_TARGET_NAME}
      PROPERTY
        SUFFIX
          ".${Python_SOABI}${_suffix}"
    )
  endif()
endif()

target_include_directories(
  ${SWIG_MODULE_SimpleITKPython_TARGET_NAME}
  PRIVATE
    ${Python_INCLUDE_DIRS}
)
target_include_directories(
  ${SWIG_MODULE_SimpleITKPython_TARGET_NAME}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(
  ${SWIG_MODULE_SimpleITK_TARGET_NAME}
  PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY
      "${CMAKE_SWIG_OUTDIR}"
)
if(MSVC)
  foreach(CMAKE_CONFIGURATION_TYPE ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${CMAKE_CONFIGURATION_TYPE} CMAKE_CONFIGURATION_TYPE)
    set_target_properties(
      ${SWIG_MODULE_SimpleITK_TARGET_NAME}
      PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY_${CMAKE_CONFIGURATION_TYPE}
          "${CMAKE_SWIG_OUTDIR}"
    )
    set_target_properties(
      ${SWIG_MODULE_SimpleITK_TARGET_NAME}
      PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_${CMAKE_CONFIGURATION_TYPE}
          "${CMAKE_SWIG_OUTDIR}"
    )
  endforeach()
endif()

# TODO add check to determine if compiler support linker script
if(UNIX AND NOT APPLE AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(VERSION_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/symbols.map")
  set_target_properties(
    ${SWIG_MODULE_SimpleITK_TARGET_NAME}
    PROPERTIES
      LINK_DEPENDS
        "${VERSION_SCRIPT}"
  )
  set_property(
    TARGET
      ${SWIG_MODULE_SimpleITK_TARGET_NAME}
    APPEND_STRING
    PROPERTY
      LINK_FLAGS
        " -Wl,--version-script=${VERSION_SCRIPT}"
  )
endif()

target_compile_options(${SWIG_MODULE_SimpleITKPython_TARGET_NAME} PRIVATE -w)
sitk_strip_target( ${SWIG_MODULE_SimpleITKPython_TARGET_NAME} )

# Installation
set(SimpleITK_PYTHON_PACKAGE_DIR "${CMAKE_CURRENT_BINARY_DIR}")
file(
  TO_NATIVE_PATH
  "${SimpleITK_PYTHON_PACKAGE_DIR}"
  SimpleITK_PYTHON_PACKAGE_DIR
)

include(sitkPythonVersion)
sitk_get_pep440_version(SITK_PYTHON_VERSION)
message(STATUS "Python version: ${SITK_PYTHON_VERSION}")
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/SimpleITK/_version.py.in"
  "${CMAKE_CURRENT_BINARY_DIR}/SimpleITK/_version.py"
)

set(
  SimpleITK_Py_Files
  "__init__.py"
  "extra.py"
  "_pixel_types.py"
  "py.typed"
)
# for each file in SimpleITK_Py_Files, prefix with "${CMAKE_CURRENT_SOURCE_DIR}/SimpleITK/"
list(
  TRANSFORM SimpleITK_Py_Files
  PREPEND
    "${CMAKE_CURRENT_SOURCE_DIR}/SimpleITK/"
)

# Currently this installation
install(
  FILES
    ${CMAKE_SWIG_OUTDIR}/SimpleITK.py
    ${SimpleITK_DOC_FILES}
    "${CMAKE_CURRENT_BINARY_DIR}/SimpleITK/_version.py"
    ${SimpleITK_Py_Files}
  DESTINATION SimpleITK
  COMPONENT Python
  EXCLUDE_FROM_ALL
)

install(
  TARGETS
    ${SWIG_MODULE_SimpleITKPython_TARGET_NAME}
  RUNTIME
    DESTINATION SimpleITK
    COMPONENT Python
    EXCLUDE_FROM_ALL
  LIBRARY
    DESTINATION SimpleITK
    COMPONENT Python
    EXCLUDE_FROM_ALL
)
include(sitkPythonTestingEnvironment)
include(LegacyPackaging.cmake)

set(PYPROJECT_TOML_EXTRA "")

if(SimpleITK_PYTHON_USE_LIMITED_API)
  set(
    PYPROJECT_TOML_EXTRA
    "${PYPROJECT_TOML_EXTRA}\n[tool.scikit-build]\nwheel.py-api = \"cp311\"\n"
  )
endif()

if(CMAKE_OSX_DEPLOYMENT_TARGET)
  set(
    PYPROJECT_TOML_EXTRA
    "${PYPROJECT_TOML_EXTRA}\n
    [tool.scikit-build.cmake.define]\nCMAKE_OSX_DEPLOYMENT_TARGET=${CMAKE_OSX_DEPLOYMENT_TARGET}\n"
  )
endif()

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/Packaging/pyproject.toml.in"
  "${CMAKE_CURRENT_BINARY_DIR}/pyproject.toml"
)
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/scikit-build-Packaging.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/CMakeLists.txt"
  COPYONLY
)

if(BUILD_TESTING)
  add_subdirectory(tests)
endif()

if(NOT CMAKE_PROJECT_NAME STREQUAL "SimpleITK" AND BUILD_TESTING)
  if(BUILD_EXAMPLES)
    add_subdirectory(
      "${SimpleITK_SOURCE_DIR}/Examples"
      "${CMAKE_BINARY_DIR}/Examples"
    )
  endif()

  if(COMMAND ExternalData_Add_Target)
    ExternalData_Add_Target(SimpleITKData)
  endif()
endif()
