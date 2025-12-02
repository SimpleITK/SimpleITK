file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/MANIFEST.in" "")

if(SimpleITK_DOC_FILES)
  # Copy the documentation files into the python package
  # directory. And create a line in for the MANIFEST.in file.

  set(SimpleITK_DOC_FILES_AS_LIST "")

  set(MANIFEST_DOCS "include")

  foreach(d ${SimpleITK_DOC_FILES})
    get_filename_component(fn "${d}" NAME)
    set(_out "${CMAKE_CURRENT_BINARY_DIR}/${fn}")
    configure_file("${d}" "${_out}" COPYONLY)
    set(MANIFEST_DOCS "${MANIFEST_DOCS} ${fn}")
  endforeach()

  file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/MANIFEST.in" "${MANIFEST_DOCS}")
endif()

set(
  SimpleITK_PYTHON_PLAT_NAME
  ""
  CACHE STRING
  "Optional value passed to pip wheel with the '--platform' argument"
)
mark_as_advanced(SimpleITK_PYTHON_PLAT_NAME)

# Do file configuration during compilation with generator expressions
add_custom_command(
  TARGET ${SWIG_MODULE_SimpleITKPython_TARGET_NAME}
  POST_BUILD
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
  COMMAND
    ${CMAKE_COMMAND}
    "-DSimpleITK_BINARY_MODULE=$<TARGET_FILE_NAME:${SWIG_MODULE_SimpleITKPython_TARGET_NAME}>"
    "-DSimpleITK_PYTHON_USE_LIMITED_API=${SimpleITK_PYTHON_USE_LIMITED_API}"
    "-DSimpleITK_PYTHON_PLAT_NAME=${SimpleITK_PYTHON_PLAT_NAME}"
    "-DSimpleITK_PYTHON_USE_LIMITED_API=${SimpleITK_PYTHON_USE_LIMITED_API}"
    "-DCONFIGUREBUILDTIME_filename=${CMAKE_CURRENT_SOURCE_DIR}/Packaging/setup.py.in"
    "-DCONFIGUREBUILDTIME_out_filename=${CMAKE_CURRENT_BINARY_DIR}/setup.py" -P
    "${SimpleITK_SOURCE_DIR}/CMake/configure_file_build_time.cmake"
  COMMENT "Generating setup.py..."
)

# Use file(GENERATE) instead of configure_file to handle generator expressions
file(
  GENERATE OUTPUT
  "${CMAKE_CURRENT_BINARY_DIR}/pyproject.toml"
  INPUT "${CMAKE_CURRENT_SOURCE_DIR}/Packaging/pyproject.toml.in"
)

foreach(_file ${SimpleITK_Py_Files})
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/SimpleITK/${_file}"
    "${CMAKE_CURRENT_BINARY_DIR}/SimpleITK/${_file}"
    COPYONLY
  )
endforeach()

option(
  SimpleITK_PYTHON_USE_VIRTUALENV
  "Create a Python Virtual Environment for testing."
  ON
)
mark_as_advanced(SimpleITK_PYTHON_USE_VIRTUALENV)
sitk_legacy_naming(SimpleITK_PYTHON_USE_VIRTUALENV)

if(SimpleITK_PYTHON_USE_VIRTUALENV)
  #TODO Check python version

  #
  # Setup Python Virtual Environment for testing and packaging
  #
  set(
    PythonVirtualenvHome
    "${${CMAKE_PROJECT_NAME}_BINARY_DIR}/Testing/Installation/pyvenv"
  )
  get_filename_component(_Python_EXECUTABLE_NAME ${Python_EXECUTABLE} NAME)

  # virtualenv places the python executable in different
  # locations. Also note than on windows installations where python is
  # installed only for a single user the may be a missing dll issue.
  if(WIN32)
    set(
      VIRTUAL_PYTHON_EXECUTABLE
      "${PythonVirtualenvHome}/Scripts/${_Python_EXECUTABLE_NAME}"
    )
  else()
    set(
      VIRTUAL_PYTHON_EXECUTABLE
      "${PythonVirtualenvHome}/bin/${_Python_EXECUTABLE_NAME}"
    )
  endif()
  set(
    SimpleITK_PYTHON_TEST_EXECUTABLE
    "${VIRTUAL_PYTHON_EXECUTABLE}"
    CACHE INTERNAL
    "Python executable for testing."
    FORCE
  )

  set(PythonVirtualEnv_ALL "")
  if(BUILD_TESTING)
    set(PythonVirtualEnv_ALL "ALL")
  endif()

  add_custom_target(
    PythonVirtualEnv
    ${PythonVirtualEnv_ALL}
    DEPENDS
      "${VIRTUAL_PYTHON_EXECUTABLE}"
  )

  set(PYTHON_COMMAND_PREFIX "")
  # add extra command which may be needed on some systems
  if(CMAKE_OSX_ARCHITECTURES)
    list(GET CMAKE_OSX_ARCHITECTURES 0 test_arch)
    set(
      PYTHON_COMMAND_PREFIX
      arch
      -${test_arch}
    )
  endif()

  add_custom_command(
    OUTPUT
      "${VIRTUAL_PYTHON_EXECUTABLE}"
    COMMAND
      ${PYTHON_COMMAND_PREFIX} "${Python_EXECUTABLE}" "-m" "venv" "--clear"
      "${PythonVirtualenvHome}"
    COMMAND
      ${PYTHON_COMMAND_PREFIX} "${VIRTUAL_PYTHON_EXECUTABLE}" "-m" "pip"
      "install" "--upgrade" "pip"
    COMMAND
      ${PYTHON_COMMAND_PREFIX} "${VIRTUAL_PYTHON_EXECUTABLE}" "-m" "pip"
      "install" "numpy!=1.24.1,!=1.24.0" "pytest" "."
    WORKING_DIRECTORY "${SimpleITK_Python_BINARY_DIR}"
    DEPENDS
      "${SWIG_MODULE_SimpleITKPython_TARGET_NAME}"
    COMMENT "Creating python virtual environment..."
  )
endif()

# Packaging for distribution
add_subdirectory(dist)
