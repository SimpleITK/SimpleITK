if ( SimpleITK_DOC_FILES )
  # Copy the documentation files into the SimpleITK python package
  # directory under "docs" sub-directory. And create a list of the
  # copied files in the python list syntax.

  set( SimpleITK_DOC_FILES_AS_LIST "")

  foreach( d ${SimpleITK_DOC_FILES} )
    get_filename_component(fn "${d}" NAME)
    set(_out "${CMAKE_CURRENT_BINARY_DIR}/SimpleITK/docs/${fn}")
    configure_file(
      "${d}"
      "${_out}"
     COPYONLY )

    file(TO_NATIVE_PATH "${_out}" d )
    if (SimpleITK_DOC_FILES_AS_LIST STREQUAL "")
        set( SimpleITK_DOC_FILES_AS_LIST "${SimpleITK_DOC_FILES_AS_LIST}[r'${_out}'")
    else()
        set( SimpleITK_DOC_FILES_AS_LIST "${SimpleITK_DOC_FILES_AS_LIST},r'${_out}'")
    endif()
  endforeach()

  set( SimpleITK_DOC_FILES_AS_LIST "${SimpleITK_DOC_FILES_AS_LIST}]")

endif()

# Step 1:
# Do initial configuration of setup.py with variable a available
# at configuration time.
set(SimpleITK_BINARY_MODULE "@SimpleITK_BINARY_MODULE@")
configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/Packaging/setup.py.in"
  "${CMAKE_CURRENT_BINARY_DIR}/Packaging/setup.py.in" )
set(SimpleITK_BINARY_MODULE)

# Step 2:
# Do file configuration during compilation with generator expressions
add_custom_command(
  TARGET ${SWIG_MODULE_SimpleITKPython_TARGET_NAME}
  POST_BUILD
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
  COMMAND ${CMAKE_COMMAND}
    "-DSimpleITK_BINARY_MODULE=$<TARGET_FILE_NAME:${SWIG_MODULE_SimpleITKPython_TARGET_NAME}>"
    "-DCONFIGUREBUILDTIME_filename=${CMAKE_CURRENT_BINARY_DIR}/Packaging/setup.py.in"
    "-DCONFIGUREBUILDTIME_out_filename=${CMAKE_CURRENT_BINARY_DIR}/setup.py"
    -P "${SimpleITK_SOURCE_DIR}/CMake/configure_file_build_time.cmake"
  COMMENT "Generating setup.py..."
  )


foreach( _file ${SimpleITK_Py_Files})

   configure_file(
     "${CMAKE_CURRENT_SOURCE_DIR}/SimpleITK/${_file}"
     "${CMAKE_CURRENT_BINARY_DIR}/SimpleITK/${_file}"
     COPYONLY )
endforeach()

option(SimpleITK_PYTHON_USE_VIRTUALENV "Create a Python Virtual Environment for testing." ON)
mark_as_advanced(SimpleITK_PYTHON_USE_VIRTUALENV)
sitk_legacy_naming(SimpleITK_PYTHON_USE_VIRTUALENV)

if (SimpleITK_PYTHON_USE_VIRTUALENV)

  #TODO Check python version

  #
  # Setup Python Virtual Environment for testing and packaging
  #
  set( PythonVirtualenvHome "${${CMAKE_PROJECT_NAME}_BINARY_DIR}/Testing/Installation/pyvenv" )

  # virtualenv places the python executable in different
  # locations. Also note than on windows installations where python is
  # installed only for a single user the may be a missing dll issue.
  if( WIN32 )
    file(TO_NATIVE_PATH "${PythonVirtualenvHome}/Scripts/python.exe" VIRTUAL_PYTHON_EXECUTABLE)
    file(TO_NATIVE_PATH "${PythonVirtualenvHome}" PythonVirtualenvHome)
  else( )
    set( VIRTUAL_PYTHON_EXECUTABLE "${PythonVirtualenvHome}/bin/python" )
  endif()
  set( PythonVirtualEnv_ALL "" )
  if ( BUILD_TESTING )
    set( PythonVirtualEnv_ALL "ALL" )
  endif()

  add_custom_target( PythonVirtualEnv ${PythonVirtualEnv_ALL}
    DEPENDS "${VIRTUAL_PYTHON_EXECUTABLE}" )

  file(MAKE_DIRECTORY "${PythonVirtualenvHome}")

  if (Python_FOUND)
    set(_Python_EXECUTABLE ${Python_EXECUTABLE})
  else()
    set(_Python_EXECUTABLE ${PYTHON_EXECUTABLE})
  endif()

  add_custom_command( OUTPUT "${VIRTUAL_PYTHON_EXECUTABLE}"
    COMMAND "${_Python_EXECUTABLE}" "-m" "venv" "${PythonVirtualenvHome}"
    WORKING_DIRECTORY "${SimpleITK_Python_BINARY_DIR}"
    DEPENDS
    "${SWIG_MODULE_SimpleITKPython_TARGET_NAME}"
    COMMENT "Creating python virtual environment..."
    )

  add_custom_command( TARGET PythonVirtualEnv
    POST_BUILD
    COMMAND "${VIRTUAL_PYTHON_EXECUTABLE}" "setup.py" install
    COMMAND "${VIRTUAL_PYTHON_EXECUTABLE}" -m pip --disable-pip-version-check install numpy wheel
)

  # Use above to resolve Python vs PYTHON naming
  set(SimpleITK_PYTHON_TEST_EXECUTABLE "${VIRTUAL_PYTHON_EXECUTABLE}"  CACHE INTERNAL "Python executable for testing." FORCE)

else()

  if (Python_FOUND)
    set(SimpleITK_PYTHON_TEST_EXECUTABLE "${Python_EXECUTABLE}" CACHE INTERNAL "Python executable for testing." FORCE)
  else()
    set(SimpleITK_PYTHON_TEST_EXECUTABLE "${PYTHON_EXECUTABLE}" CACHE INTERNAL "Python executable for testing." FORCE)
  endif()

endif()

# Packaging for distribution
add_subdirectory(dist)
